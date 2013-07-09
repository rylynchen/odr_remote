<?php

/**
 * Administration page for ODR remote settings.
 */
function odr_remote_settings_form($form, &$form_state) {
	$form = array();
  $form['#attributes'] = array('class' => array('odr_remote_settings_form'));
  $form['generate'] = array(
    '#type' => 'submit',
    '#value' => t('Generate a Key'),
    '#submit' => array('odr_remote_settings_form_generate_submit'),
    '#suffix' => '<div class="clear"></div>',
    '#validate' => array(),
    '#limit_validation_errors' => array(),
    '#ajax'=> array(
      'callback'=>'odr_remote_settings_form_generate_callback',
      'progress' => array(
        'type' => 'throbber',
        'message' => '',
      ),
    )
  );
  $form['msg'] = array(
    '#markup' => '<div class="odr_remote_msg"></div>',
  );
  $form['odr_remote_keys'] = array(
    '#type' => 'textarea',
    '#title' => t('Keys'),
    '#attributes' => array('class' => array('odr_remote_keys')),
    '#default_value' => variable_get('odr_remote_keys', ''),
  );
  $form['#attached']['css'][] = drupal_get_path('module', 'odr_remote').'/odr_remote.css';
  $form['#attached']['js'][] = drupal_get_path('module', 'odr_remote').'/odr_remote.js';
  return system_settings_form($form);
}

/**
 * Form  odr_remote_settings_form generate submit handler.
 */
function odr_remote_settings_form_generate_submit($form, &$form_state) {
	$str = trim($form_state['complete form']['odr_remote_keys']['#value']);
	$keys = empty($str) ? array() : explode("\n", $str);
  $new = odr_remote_generate_key($keys);
	$keys[] = $new;
  $form_state['storage']['new_key'] = $new;
	$form_state['storage']['keys'] = $keys;
	$form_state['rebuild'] = TRUE;
}

/**
 * Generate key.
 *
 * @param $keys
 */
function odr_remote_generate_key($keys) {
	do{
		$key = user_password(16);
	}while (in_array($key, $keys));
	return $key;
}

/**
 * Form  odr_remote_settings_form generate submit callback.
 */
function odr_remote_settings_form_generate_callback($form, $form_state) {
	$text = implode("\n", $form_state['storage']['keys']);
	$commands = array();
  $msg = t('Add a new key : '.$form_state['storage']['new_key']);
  $commands[] = ajax_command_append('.odr_remote_msg', $msg);
  $commands[] = array(
    'command' => 'odrUpdateKeys',
    'data' => array('selector' => '.odr_remote_keys', 'val' => $text),
  );
	return array('#type' => 'ajax', '#commands' => $commands);
}