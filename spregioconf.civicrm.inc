<?php

/**
 * Class SPRegioconf_Civi
 * Functies voor CiviCRM-integratie regioconferentie-aanmelding. Zie \SPCivi voor initialisatie en basisfuncties.
 */
class SPRegioconf_Civi extends \SPCivi {

  // Mapping van veldnamen naar interne namen. Deze zijn een beetje historisch...
  private $customEventGroup = 'regioconf_options';
  private $customEventFields = [
    'regions'            => 'regioconf_regios_toegang',
    'guests'             => 'regioconf_aantal_gasten',
    'ratio'              => 'regioconf_ratio',
    'registration_until' => 'regioconf_registration_until',
  ];

  // Cachen van events en custom groups/fields binnen request
  private $eventDataCache = [];
  private $geoInfoCache = [];

  /**
   * Get a single field value from the CiviCRM event data. Supports mapped names for custom fields
   * @param int $event_id Event ID
   * @param string $field Field name
   * @return mixed Field value
   */
  public function getEventValue($event_id, $field) {

    $eventData = $this->getEventData($event_id);
    if ($eventData) {

      if (array_key_exists($field, $eventData)) {
        return $eventData[$field];
      }

      if (array_key_exists($field, $this->customEventFields)) {
        $fieldName = 'custom_' . $this->getCustomFieldId($this->customEventGroup, $this->customEventFields[$field]);
        if (isset($eventData[$fieldName])) {
          return $eventData[$fieldName];
        }
      }
    }

    return NULL;
  }

  /**
   * Get and cache CiviCRM event data
   * @param int $event_id Event ID
   * @return mixed|bool Event data or false
   */
  public function getEventData($event_id) {

    if (empty($this->eventDataCache[$event_id])) {
      try {
        $this->eventDataCache[$event_id] = $this->api('Event', 'getsingle', [
          'id' => $event_id,
        ]);
      } catch (\CiviCRM_API3_Exception $e) {
        drupal_set_message('Kon evenementinformatie niet ophalen: ' . $e->getMessage(), 'error');
        return FALSE;
      }
    }

    return $this->eventDataCache[$event_id];
  }

  /**
   * Controleert of een gebruiker kan inschrijven voor een specifiek evenement.
   * Op dit moment worden hier ook events uitgesloten die niet specifiek regio's hebben gedefinieerd
   * -> voorlopig security-dingetje om te voorkomen dat andere evenementen ook open kunnen komen te staan.
   * @param int $drupal_uid Drupal UID
   * @param int $event_id Event ID
   * @return bool Has access
   */
  public function checkEventAccess($drupal_uid, $event_id) {

    $userRegio   = $this->getUserRegio($drupal_uid);
    $eventRegios = $this->getEventValue($event_id, 'regions');

    return (count($eventRegios) > 0 && in_array($userRegio, $eventRegios));
  }

  /**
   * Controleert of een gebruiker toegang heeft tot een specifiek contact.
   * @param int $contact_id Contact ID
   * @return bool Has access
   */
  public function checkContactAccess($contact_id) {
    return CRM_Contact_BAO_Contact_Permission::allow($contact_id, CRM_Core_Permission::VIEW);
  }

  /**
   * Get participant data
   * @param int $participant_id Participant ID
   * @return mixed|bool Participant data or false
   */
  public function getParticipantData($participant_id) {
    try {
      return $this->api('Participant', 'getsingle', [
        'id' => $participant_id,
      ]);
    } catch (\CiviCRM_API3_Exception $e) {
      drupal_set_message('Kon deelnemersinformatie niet ophalen: ' . $e->getMessage(), 'error');
      return FALSE;
    }
  }

  /**
   * Add participant
   * Controleert nu eerst of een aanmelding met zelfde event/contact/rol al bestaat, regardless of participant status.
   * Overschrijft deze als dit het geval is, maakt anders nieuw record aan.
   * @param int $event_id Event ID
   * @param int $contact_id Contact ID
   * @param int $role_id Participant Role ID
   * @return array|bool Return array or false
   */
  public function addParticipant($event_id, $contact_id, $role_id) {
    try {
      return $this->api('Participant', 'create', [
        'event_id'       => $event_id,
        'contact_id'     => $contact_id,
        'role_id'        => $role_id,
        'participant_id' => $this->getParticipant($event_id, $contact_id, $role_id),
        'status_id'      => $this->api('ParticipantStatusType', 'getvalue', ['name' => 'Registered', 'return' => 'id']),
      ]);
    } catch (\CiviCRM_API3_Exception $e) {
      drupal_set_message('Kon deelnemer niet aanmelden: ' . $e->getMessage(), 'error');
      return FALSE;
    }
  }

  /**
   * Get single participant record from params
   * @param int $event_id Event ID
   * @param int $contact_id Contact ID
   * @param int $role_id Participant Role ID
   * @return array|bool Record or false
   */
  public function getParticipant($event_id, $contact_id, $role_id) {
    try {
      $participant = $this->api('Participant', 'getsingle', ['event_id' => $event_id, 'contact_id' => $contact_id, 'role_id' => $role_id]);
      return $participant['participant_id'];
    } catch (\CiviCRM_API3_Exception $e) {
      return FALSE;
    }
  }

  /**
   * Check if a participant is already registered for an event. (Gebruikt op aanmeldingsformulier)
   * Met query om even snel te filteren op aanmeldstatus. (-> mensen die je afmeldt kun je weer opnieuw aanmelden)
   * @param int $event_id Event ID
   * @param int $contact_id Contact ID
   * @return bool Exists
   */
  public function participantExists($event_id, $contact_id) {
    $count = CRM_Core_DAO::singleValueQuery(
      "SELECT COUNT(*) FROM civicrm_participant p
       LEFT JOIN civicrm_participant_status_type ps ON p.status_id = ps.id
       LEFT JOIN civicrm_contact c ON c.id = p.contact_id
       WHERE c.is_deleted = 0 AND c.id = %1 AND ps.class = 'Positive' AND p.event_id = %2", [
      1 => [$contact_id, 'Integer'],
      2 => [$event_id, 'Integer'],
    ]);
    return ($count > 0);
  }

  /**
   * Cancel participant registration for an event
   * @param int $participant_id Participant ID
   * @return array|bool Return array or false
   */
  public function cancelParticipant($participant_id) {
    try {
      $cancel_id = $this->api('ParticipantStatusType', 'getvalue', ['name' => 'Cancelled', 'return' => 'id']);
      return $this->api('Participant', 'create', [
        'participant_id' => $participant_id,
        'status_id'      => $cancel_id,
      ]);
    } catch (\CiviCRM_API3_Exception $e) {
      drupal_set_message('Kon deelnemersstatus niet wijzigen: ' . $e->getMessage(), 'error');
      return FALSE;
    }
  }

  public function getExtendedEventData($drupal_uid, $event_id) {

    try {

      $afdelingField = 'custom_' . $this->getCustomFieldId('Geostelsel', 'Afdeling');
      $regioField    = 'custom_' . $this->getCustomFieldId('Geostelsel', 'Regio');

      $contact_id = $this->api('UFMatch', 'getvalue', ['uf_id' => $drupal_uid, 'return' => 'contact_id']);
      $contact    = $this->api('Contact', 'getsingle', ['contact_id' => $contact_id, 'return' => [$afdelingField, $regioField]]);

      $afdeling_id = $contact[$afdelingField];
      $regio_id    = $contact[$regioField];

      if(!$contact || !$afdeling_id) {
        throw new \Exception('De ingelogde gebruiker heeft geen CiviCRM-contact of behoort niet tot een afdeling.');
      }

      $event = $this->getEventData($event_id);
      if (!$event) {
        throw new \Exception('Kon informatie voor dit evenement niet ophalen.');
      }

      $ratio              = $this->getEventValue($event_id, 'ratio');
      $guests             = $this->getEventValue($event_id, 'guests');
      $registration_ends  = $this->getEventValue($event_id, 'registration_until');
      $registration_until = strtotime($event['start_date']) - ($registration_ends ? $registration_ends : 0) * 86400;

      return array_merge($event, [
        'registrationOpen'     => ($registration_until >= time()),
        'registrationUntil'    => $registration_until,
        'ratio'                => $ratio,
        'maxRegistrations'     => (empty($ratio) ? NULL : ceil($this->getMemberCount($afdeling_id) / $ratio)),
        'maxGuests'            => $guests,
        'currentRegistrations' => $this->getParticipantCount($event_id, $afdeling_id, 'Deelnemer'),
        'currentGuests'        => $this->getParticipantCount($event_id, $afdeling_id, 'Gast'),
        'afdelingId'           => $afdeling_id,
        'regioId'              => $regio_id,
      ]);

    } catch (\CiviCRM_API3_Exception $e) {
      drupal_set_message('Kon afdelingsgegevens niet ophalen: ' . $e->getMessage(), 'error');
    } catch(\Exception $e) {
      drupal_set_message($e->getMessage(), 'error');
    }

    return FALSE;
  }

  /**
   * Tel aantal leden waar de huidige gebruiker toegang toe heeft. Dat gebruiken we even lekker makkelijk als reken-basis.
   * return int|bool Count
   */
  public function getMemberCount($afdeling_id) {

    return CRM_Core_DAO::singleValueQuery(
      "SELECT COUNT(*) FROM civicrm_membership m
       LEFT JOIN civicrm_membership_status ms ON m.status_id = ms.id
       LEFT JOIN civicrm_membership_type ct ON m.membership_type_id = ct.id
       LEFT JOIN civicrm_contact c ON c.id = m.contact_id
       LEFT JOIN civicrm_value_geostelsel g ON c.id = g.entity_id
       WHERE c.is_deleted = 0 AND m.is_test = 0 AND ms.is_current_member = 1 AND ct.name IN ('Lid SP', 'Lid SP en ROOD')
       AND g.afdeling = %1", [
      1 => [$afdeling_id, 'Integer'],
    ]);
  }

  /**
   * Tel het aantal deelnemers dat al is aangemeld voor dit evenement vanuit deze afdeling met rol X.
   * (Voor nu Deelnemer/Gast: te differentieren om bijv extra landelijke aanmeldingen toe te laten zonder afdelingen in de weg te zitten)
   * @param int $event_id Event ID
   * @param int $afdeling_id Afdeling ID
   * @param string $role Deelnemersrol
   * @return int|bool Count
   */
  public function getParticipantCount($event_id, $afdeling_id, $role) {

    $role_id = (int) array_search($role, CRM_Event_PseudoConstant::participantRole());
    return CRM_Core_DAO::singleValueQuery(
      "SELECT COUNT(*) FROM civicrm_participant p
       LEFT JOIN civicrm_participant_status_type ps ON p.status_id = ps.id
       LEFT JOIN civicrm_contact c ON c.id = p.contact_id
       LEFT JOIN civicrm_value_geostelsel g ON c.id = g.entity_id
       WHERE c.is_deleted = 0 AND ps.class = 'Positive' AND p.event_id = %1 AND g.afdeling = %2 AND p.role_id = %3", [
      1 => [$event_id, 'Integer'],
      2 => [$afdeling_id, 'Integer'],
      3 => [$role_id, 'Integer'],
    ]);
  }

  /**
   * Zoek SP-afdelings-ID van de huidige ingelogde gebruiker
   * Probeert het eerst op basis van relatie met de afdeling, als dat niet lukt op basis van geostelsel.
   * @param int $drupal_uid Drupal UID
   * @return int|bool ID or false
   */
  public function getUserAfdeling($drupal_uid) {

    if (isset($this->geoInfoCache['afdeling'])) {
      return $this->geoInfoCache['afdeling'];
    }

    try {

      $contact_id = $this->api('UFMatch', 'getvalue', ['uf_id' => $drupal_uid, 'return' => 'contact_id']);

      // Eerste poging: op basis van voorzittersrelatie met afdeling
      $vzRelatieId  = $this->getRelationshipTypeIdByNameAB('sprel_voorzitter_afdeling');
      $vvzRelatieId = $this->getRelationshipTypeIdByNameAB('sprel_vervangendvoorzitter_afdeling');
      $afdelingsId  = $this->api('Relationship', 'getvalue', [
        'return'               => 'contact_id_b',
        'relationship_type_id' => ['IN' => [$vzRelatieId, $vvzRelatieId]],
        'contact_id_a'         => $contact_id,
        'is_active'            => 1,
        'options'              => ['limit' => 1],
      ]);

      if ($afdelingsId) {
        $this->geoInfoCache['afdeling'] = $afdelingsId;
      }
      else {
        // Fallback: op basis van veld Geostelsel->Afdeling
        $afdelingField                  = $this->getCustomFieldId('Geostelsel', 'Afdeling');
        $this->geoInfoCache['afdeling'] = $this->api('Contact', 'getvalue', ['contact_id' => $contact_id, 'return' => 'custom_' . $afdelingField]);
      }

      return $this->geoInfoCache['afdeling'];

    } catch (\CiviCRM_API3_Exception $e) {
      drupal_set_message('Kon afdeling niet ophalen: ' . $e->getMessage(), 'error');
      return FALSE;
    }
  }

  /**
   * Zoek SP-regio-ID van de huidige ingelogde gebruiker.
   * Probeert het eerst op basis van relatie met de afdeling, als dat niet lukt op basis van geostelsel.
   * @param int $drupal_uid Drupal UID
   * @return int|bool ID or false
   */
  public function getUserRegio($drupal_uid) {

    if (!isset($this->geoInfoCache['regio'])) {
      $afdelingsId                 = $this->getUserAfdeling($drupal_uid);
      $this->geoInfoCache['regio'] = $this->getRegioIdByAfdelingId($afdelingsId);
    }

    return $this->geoInfoCache['regio'];
  }

  /**
   * Haal een SP-regio-ID op bij een SP-afdelings-ID
   * @param int $afd_contact_id Afdelings-id
   * @return int|bool ID or false
   */
  private function getRegioIdByAfdelingId($afd_contact_id) {
    try {
      $rel_type_id = $this->getRelationshipTypeIdByNameAB('sprel_afdeling_regio');
      return $this->api('Relationship', 'getvalue', [
        'return'               => 'contact_id_b',
        'relationship_type_id' => $rel_type_id,
        'contact_id_a'         => $afd_contact_id,
        'is_active'            => 1,
      ]);
    } catch (\CiviCRM_API3_Exception $e) {
      drupal_set_message('Kon regio niet ophalen: ' . $e->getMessage(), 'error');
      return FALSE;
    }
  }

}