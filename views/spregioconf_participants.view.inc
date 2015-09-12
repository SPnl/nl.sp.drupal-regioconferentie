<?php
$view = new view();
$view->name = 'spregioconf_participants';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_participant';
$view->human_name = 'Regioconferenties: deelnemers';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Aanmelden afgevaardigden';
$handler->display->display_options['css_class'] = 'content';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'views_access_callback';
$handler->display->display_options['access']['views_access_callback'] = 'spregioconf_check_event_access';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Opnieuw instellen';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'table';
/* Kop: Global: Text area */
$handler->display->display_options['header']['area']['id'] = 'area';
$handler->display->display_options['header']['area']['table'] = 'views';
$handler->display->display_options['header']['area']['field'] = 'area';
$handler->display->display_options['header']['area']['label'] = 'Intro';
$handler->display->display_options['header']['area']['empty'] = TRUE;
$handler->display->display_options['header']['area']['content'] = '<p><a href="/regioconferenties/add/%1">Deelnemer toevoegen</a></p>';
$handler->display->display_options['header']['area']['format'] = 'filtered_html';
$handler->display->display_options['header']['area']['tokenize'] = TRUE;
/* Kop: Entity: Rendered entity */
$handler->display->display_options['header']['entity']['id'] = 'entity';
$handler->display->display_options['header']['entity']['table'] = 'entity__global';
$handler->display->display_options['header']['entity']['field'] = 'entity';
$handler->display->display_options['header']['entity']['entity_id'] = 'regioconferenties/add/1';
$handler->display->display_options['header']['entity']['bypass_access'] = 0;
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['label'] = 'Geen resultaten';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = '<p>Er zijn nog geen deelnemers aangemeld voor deze conferentie.</p>';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
/* Relationship: CiviCRM Participants: Event ID */
$handler->display->display_options['relationships']['event_id']['id'] = 'event_id';
$handler->display->display_options['relationships']['event_id']['table'] = 'civicrm_participant';
$handler->display->display_options['relationships']['event_id']['field'] = 'event_id';
$handler->display->display_options['relationships']['event_id']['label'] = 'Participant';
$handler->display->display_options['relationships']['event_id']['required'] = TRUE;
/* Veld: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = 'Lidnummer';
$handler->display->display_options['fields']['id']['separator'] = '';
/* Veld: CiviCRM Contacts: Sort Name */
$handler->display->display_options['fields']['sort_name']['id'] = 'sort_name';
$handler->display->display_options['fields']['sort_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['sort_name']['field'] = 'sort_name';
$handler->display->display_options['fields']['sort_name']['label'] = 'Sorteernaam';
$handler->display->display_options['fields']['sort_name']['exclude'] = TRUE;
$handler->display->display_options['fields']['sort_name']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['sort_name']['link_to_civicrm_contact'] = 0;
/* Veld: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['label'] = 'Naam';
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
/* Veld: CiviCRM Participants: Participant Role */
$handler->display->display_options['fields']['role']['id'] = 'role';
$handler->display->display_options['fields']['role']['table'] = 'civicrm_participant';
$handler->display->display_options['fields']['role']['field'] = 'role';
$handler->display->display_options['fields']['role']['label'] = 'Rol';
/* Veld: CiviCRM Participants: Participant Status */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'civicrm_participant';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['label'] = 'Status';
/* Veld: CiviCRM Participants: Text Link */
$handler->display->display_options['fields']['text_link']['id'] = 'text_link';
$handler->display->display_options['fields']['text_link']['table'] = 'civicrm_participant';
$handler->display->display_options['fields']['text_link']['field'] = 'text_link';
$handler->display->display_options['fields']['text_link']['label'] = 'Acties';
$handler->display->display_options['fields']['text_link']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['text_link']['link_to_civicrm_participant'] = 'custom';
$handler->display->display_options['fields']['text_link']['custom_link'] = 'regioconferenties/delete/';
$handler->display->display_options['fields']['text_link']['link_text'] = 'Afmelden';
/* Sort criterion: CiviCRM Participants: Participant Role */
$handler->display->display_options['sorts']['role']['id'] = 'role';
$handler->display->display_options['sorts']['role']['table'] = 'civicrm_participant';
$handler->display->display_options['sorts']['role']['field'] = 'role';
$handler->display->display_options['sorts']['role']['expose']['label'] = 'Participant Role';
/* Sort criterion: CiviCRM Participants: Participant Status */
$handler->display->display_options['sorts']['status']['id'] = 'status';
$handler->display->display_options['sorts']['status']['table'] = 'civicrm_participant';
$handler->display->display_options['sorts']['status']['field'] = 'status';
$handler->display->display_options['sorts']['status']['expose']['label'] = 'Participant Status';
/* Sort criterion: CiviCRM Contacts: Sort Name */
$handler->display->display_options['sorts']['sort_name']['id'] = 'sort_name';
$handler->display->display_options['sorts']['sort_name']['table'] = 'civicrm_contact';
$handler->display->display_options['sorts']['sort_name']['field'] = 'sort_name';
/* Contextual filter: CiviCRM Events: Event ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_event';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['relationship'] = 'event_id';
$handler->display->display_options['arguments']['id']['default_action'] = 'not found';
$handler->display->display_options['arguments']['id']['exception']['title'] = 'Alle';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'regioconferenties/view';
$translatables['spregioconf_participants'] = array(
  t('Master'),
  t('Aanmelden afgevaardigden'),
  t('more'),
  t('Apply'),
  t('Opnieuw instellen'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Intro'),
  t('<p><a href="/regioconferenties/add/%1">Deelnemer toevoegen</a></p>'),
  t('Geen resultaten'),
  t('<p>Er zijn nog geen deelnemers aangemeld voor deze conferentie.</p>'),
  t('Participant'),
  t('Lidnummer'),
  t('.'),
  t('Sorteernaam'),
  t('Naam'),
  t('Rol'),
  t('Status'),
  t('Acties'),
  t('Participant Role'),
  t('Participant Status'),
  t('Alle'),
  t('Page'),
);
