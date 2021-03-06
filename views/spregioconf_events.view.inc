<?php
$view = new view();
$view->name = 'spregioconf_events';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_event';
$view->human_name = 'Regioconferenties: overzicht';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Aanmelden afgevaardigden';
$handler->display->display_options['css_class'] = 'content';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = array(
  3 => '3',
  18 => '18',
  7 => '7',
);
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
$handler->display->display_options['header']['area']['content'] = '<p>Je kunt hier deelnemers voor regioconferenties en congressen bekijken, inschrijven en verwijderen.<br/>
Selecteer een conferentie om verder te gaan.</p>';
$handler->display->display_options['header']['area']['format'] = 'filtered_html';
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['label'] = 'Geen resultaten';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = '<p>Er zijn op dit moment geen regioconferenties, congressen of bijeenkomsten waarvoor je deelnemers kunt bekijken of inschrijven.</p>';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
/* Veld: CiviCRM Events: Event ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_event';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Veld: CiviCRM Events: Titel */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'civicrm_event';
$handler->display->display_options['fields']['title']['field'] = 'title';
/* Veld: CiviCRM Events: Start Date */
$handler->display->display_options['fields']['start_date']['id'] = 'start_date';
$handler->display->display_options['fields']['start_date']['table'] = 'civicrm_event';
$handler->display->display_options['fields']['start_date']['field'] = 'start_date';
$handler->display->display_options['fields']['start_date']['label'] = 'Datum';
$handler->display->display_options['fields']['start_date']['date_format'] = 'long_date';
$handler->display->display_options['fields']['start_date']['second_date_format'] = 'html5_tools_iso8601';
/* Veld: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = 'Acties';
$handler->display->display_options['fields']['nothing']['alter']['text'] = 'Deelnemersoverzicht';
$handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['path'] = 'regioconferenties/view/[id]';
/* Sort criterion: CiviCRM Events: Start Date */
$handler->display->display_options['sorts']['start_date']['id'] = 'start_date';
$handler->display->display_options['sorts']['start_date']['table'] = 'civicrm_event';
$handler->display->display_options['sorts']['start_date']['field'] = 'start_date';
/* Filter criterion: CiviCRM Events: Event Type */
$handler->display->display_options['filters']['event_type']['id'] = 'event_type';
$handler->display->display_options['filters']['event_type']['table'] = 'civicrm_event';
$handler->display->display_options['filters']['event_type']['field'] = 'event_type';
$handler->display->display_options['filters']['event_type']['value'] = array(
  8 => '8',
);
/* Filter criterion: CiviCRM Events: Start Date */
$handler->display->display_options['filters']['start_date']['id'] = 'start_date';
$handler->display->display_options['filters']['start_date']['table'] = 'civicrm_event';
$handler->display->display_options['filters']['start_date']['field'] = 'start_date';
$handler->display->display_options['filters']['start_date']['operator'] = '>=';
$handler->display->display_options['filters']['start_date']['value']['value'] = 'now';
$handler->display->display_options['filters']['start_date']['value']['type'] = 'offset';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'regioconferenties';
$translatables['spregioconf_events'] = array(
  t('Master'),
  t('Aanmelden afgevaardigden'),
  t('more'),
  t('Apply'),
  t('Opnieuw instellen'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Intro'),
  t('<p>Je kunt hier deelnemers voor regioconferenties en congressen bekijken, inschrijven en verwijderen.<br/>
Selecteer een conferentie om verder te gaan.</p>'),
  t('Geen resultaten'),
  t('<p>Er zijn op dit moment geen regioconferenties, congressen of bijeenkomsten waarvoor je deelnemers kunt bekijken of inschrijven.</p>'),
  t('Event ID'),
  t('.'),
  t('Titel'),
  t('Datum'),
  t('Acties'),
  t('Deelnemersoverzicht'),
  t('Page'),
);
