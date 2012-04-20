<?php

/**
 * Implementation of hook_content_default_fields().
 */
function cod_sponsors_override_content_default_fields() {
  $fields = array();

  // Exported field: field_logo_white
  $fields['sponsor-field_logo_white'] = array(
    'field_name' => 'field_logo_white',
    'type_name' => 'sponsor',
    'display_settings' => array(
      'weight' => '4',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '',
    'list_default' => '',
    'description_field' => '',
    'widget' => array(
      'file_extensions' => NULL,
      'file_path' => NULL,
      'progress_indicator' => NULL,
      'max_filesize_per_file' => NULL,
      'max_filesize_per_node' => NULL,
      'max_resolution' => NULL,
      'min_resolution' => NULL,
      'alt' => NULL,
      'custom_alt' => NULL,
      'title' => NULL,
      'custom_title' => NULL,
      'title_type' => NULL,
      'default_image' => NULL,
      'use_default_image' => NULL,
      'label' => 'Logo (white)',
      'weight' => '4',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Logo (white)');

  return $fields;
}
