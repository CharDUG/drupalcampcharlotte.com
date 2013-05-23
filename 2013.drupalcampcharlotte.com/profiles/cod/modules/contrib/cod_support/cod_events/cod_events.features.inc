<?php
/**
 * @file
 * cod_events.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cod_events_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "panels" && $api == "layouts") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cod_events_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cod_events_node_info() {
  $items = array(
    'event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('Provides free and paid event registration on the Event content type.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_default_registration_type().
 */
function cod_events_default_registration_type() {
  $items = array();
  $items['free_event'] = entity_import('registration_type', '{
    "name" : "free_event",
    "label" : "Free Event",
    "locked" : "0",
    "weight" : "0",
    "data" : null
  }');
  return $items;
}
