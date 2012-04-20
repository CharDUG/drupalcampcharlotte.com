<?php

/**
 * Implementation of hook_default_features_overrides().
 */
function cod_sponsors_override_default_features_overrides() {
  $export = array();

  $features_override = new stdClass;
  $features_override->disabled = FALSE; /* Edit this to true to make a default features_override disabled initially */
  $features_override->api_version = 1;
  $features_override->name = 'fo_sponsor_logo';
  $features_override->description = '';
  $features_override->component_type = 'content';
  $features_override->component_id = 'sponsor-field_logo';
  $features_override->value = array(
    'additions' => array(
      0 => array(
        'keys' => array(
          0 => array(
            'type' => 'array',
            'key' => 'display_settings',
          ),
          1 => array(
            'type' => 'array',
            'key' => 'weight',
          ),
        ),
        'value' => '3',
      ),
      1 => array(
        'keys' => array(
          0 => array(
            'type' => 'array',
            'key' => 'list_field',
          ),
        ),
        'value' => '0',
      ),
      2 => array(
        'keys' => array(
          0 => array(
            'type' => 'array',
            'key' => 'widget',
          ),
          1 => array(
            'type' => 'array',
            'key' => 'default_image',
          ),
        ),
        'value' => NULL,
      ),
      3 => array(
        'keys' => array(
          0 => array(
            'type' => 'array',
            'key' => 'widget',
          ),
          1 => array(
            'type' => 'array',
            'key' => 'weight',
          ),
        ),
        'value' => '3',
      ),
    ),
    'deletions' => array(
      0 => array(
        'keys' => array(
          0 => array(
            'type' => 'array',
            'key' => 'widget',
          ),
          1 => array(
            'type' => 'array',
            'key' => 'default_image',
          ),
        ),
      ),
    ),
  );
  $export['fo_sponsor_logo'] = $features_override;

  $features_override = new stdClass;
  $features_override->disabled = FALSE; /* Edit this to true to make a default features_override disabled initially */
  $features_override->api_version = 1;
  $features_override->name = 'fo_sponsorhip_level';
  $features_override->description = '';
  $features_override->component_type = 'content';
  $features_override->component_id = 'sponsor-field_sponsorship_level';
  $features_override->value = array(
    'additions' => array(
      0 => array(
        'keys' => array(
          0 => array(
            'type' => 'array',
            'key' => 'allowed_values',
          ),
        ),
        'value' => 'Platinum
Gold
Silver
Bronze
Media
Community Sponsor',
      ),
      1 => array(
        'keys' => array(
          0 => array(
            'type' => 'array',
            'key' => 'display_settings',
          ),
          1 => array(
            'type' => 'array',
            'key' => 'weight',
          ),
        ),
        'value' => 0,
      ),
      2 => array(
        'keys' => array(
          0 => array(
            'type' => 'array',
            'key' => 'widget',
          ),
          1 => array(
            'type' => 'array',
            'key' => 'default_value_php',
          ),
        ),
        'value' => NULL,
      ),
      3 => array(
        'keys' => array(
          0 => array(
            'type' => 'array',
            'key' => 'widget',
          ),
          1 => array(
            'type' => 'array',
            'key' => 'weight',
          ),
        ),
        'value' => 0,
      ),
    ),
    'deletions' => array(
      0 => array(
        'keys' => array(
          0 => array(
            'type' => 'array',
            'key' => 'widget',
          ),
          1 => array(
            'type' => 'array',
            'key' => 'default_value_php',
          ),
        ),
      ),
    ),
  );
  $export['fo_sponsorhip_level'] = $features_override;

  return $export;
}
