<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function cod_sponsors_override_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "features_override" && $api == "features_override") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function cod_sponsors_override_imagecache_default_presets() {
  $items = array(
    'sponsor_logo_community' => array(
      'presetname' => 'sponsor_logo_community',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '145',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'sponsor_logo_community_color' => array(
      'presetname' => 'sponsor_logo_community_color',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '200',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'sponsor_logo_gold_color' => array(
      'presetname' => 'sponsor_logo_gold_color',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '240',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'sponsor_logo_platinum_color' => array(
      'presetname' => 'sponsor_logo_platinum_color',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '290',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'sponsor_logo_silver_color' => array(
      'presetname' => 'sponsor_logo_silver_color',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '200',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'sponsor_logo_white_community' => array(
      'presetname' => 'sponsor_logo_white_community',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '145',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'sponsor_logo_white_gold' => array(
      'presetname' => 'sponsor_logo_white_gold',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '145',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'sponsor_logo_white_platinum' => array(
      'presetname' => 'sponsor_logo_white_platinum',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '310',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'sponsor_logo_white_silver' => array(
      'presetname' => 'sponsor_logo_white_silver',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '145',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function cod_sponsors_override_views_api() {
  return array(
    'api' => '2',
  );
}
