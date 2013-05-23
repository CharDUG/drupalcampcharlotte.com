<?php
/**
 * @file
 * cod_bof.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cod_bof_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cod_bof_schedule';
  $view->description = 'Conference Organizing Scheduler Admin View';
  $view->tag = 'cod';
  $view->base_table = 'node';
  $view->human_name = 'cod_bof_schedule';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'BoFs';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'quicktabs';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_slot_datetime',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
  );
  $handler->display->display_options['style_options']['tab_style'] = 'Basic';
  $handler->display->display_options['style_options']['tab_title_field'] = 'field_slot_datetime';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Date and time */
  $handler->display->display_options['fields']['field_slot_datetime']['id'] = 'field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['table'] = 'field_data_field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['field'] = 'field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['label'] = '';
  $handler->display->display_options['fields']['field_slot_datetime']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_slot_datetime']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_slot_datetime']['settings'] = array(
    'format_type' => 'date_no_time_',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Global: View */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['view'] = 'cod_session_schedule_entity';
  $handler->display->display_options['fields']['view']['display'] = 'block';
  $handler->display->display_options['fields']['view']['arguments'] = '[!nid]/bof_session';
  /* Sort criterion: Content: Date and time (field_slot_datetime) */
  $handler->display->display_options['sorts']['field_slot_datetime_value']['id'] = 'field_slot_datetime_value';
  $handler->display->display_options['sorts']['field_slot_datetime_value']['table'] = 'field_data_field_slot_datetime';
  $handler->display->display_options['sorts']['field_slot_datetime_value']['field'] = 'field_slot_datetime_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'time_slot' => 'time_slot',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'program/schedule/bofs';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Broken/missing handler */
  $handler->display->display_options['arguments']['field_session_room_target_id']['id'] = 'field_session_room_target_id';
  $handler->display->display_options['arguments']['field_session_room_target_id']['table'] = 'field_data_field_session_room';
  $handler->display->display_options['arguments']['field_session_room_target_id']['field'] = 'field_session_room_target_id';
  $handler->display->display_options['arguments']['field_session_room_target_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_session_room_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_session_room_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_session_room_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_session_room_target_id']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Broken/missing handler */
  $handler->display->display_options['arguments']['field_session_slot_target_id']['id'] = 'field_session_slot_target_id';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['table'] = 'field_data_field_session_slot';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['field'] = 'field_session_slot_target_id';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bof_session' => 'bof_session',
  );
  $export['cod_bof_schedule'] = $view;

  return $export;
}
