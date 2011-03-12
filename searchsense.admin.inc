<?php

/**
 * @file
 * Searchsense administration callbacks.
 */

/**
 * Form callback for administration form.
 */
function searchsense_admin() {
  $form = array();
  $configs = _searchsense_configs();

  $form['searchsense'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search Autocompletion'),
    '#weight' => 0,
  );

  $form['searchsense']['searchsense_options'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enable autocompletion for'),
    '#default_value' => $configs['options'],
    '#options' => array(
      'user' => t('User search form'),
      'block' => t('Search block form'),
      'theme' => t('Theme search form'),
      'advanced' => t('Advanced search form'),
    ),
  );

  $enabled = module_exists('js');
  $form['searchsense']['searchsense_use_js'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make use of <a href="!link">High performance JS callback handler</a>. <em>(recommended)</em>',
      array('!link' => 'http://drupal.org/project/js')
    ),
    '#return_value' => 1,
    '#disabled' => !$enabled,
    '#default_value' => $enabled ? $configs['use_js'] : 0,
  );
  unset($enabled);

  $form['searchsense']['searchsense_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of suggestions'),
    '#default_value' => $configs['limit'],
  );

  $form['searchsense']['searchsense_min'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum number of characters'),
    '#description' => t('Minimum number of characters to show suggestions for.'),
    '#default_value' => $configs['min'],
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#weight' => 10,
  );

  return $form;
}

/**
 * Validation callback for administration form.
 */
function searchsense_admin_validate($form, &$form_state) {
  if (!ctype_digit($form_state['values']['searchsense_limit'])) {
    form_set_error('searchsense_limit', t('The suggestion list limit value must be numeric.'));
  }

  if (!ctype_digit($form_state['values']['searchsense_min']) || intval($form_state['values']['searchsense_min']) < 1) {
    form_set_error('searchsense_min', t('The minimum characters must be numeric value greater than 1.'));
  }

  if ($form_state['values']['searchsense_use_js'] && !module_exists('js')) {
    form_set_error('searchsense_use_js', t('The <a href="!link">High performance JS callback handler</a> module is not yet installed.',
      array('!link' => 'http://drupal.org/project/js')
    ));
  }
}

/**
 * Submission callback for administration form.
 */
function searchsense_admin_submit($form, &$form_state) {
  variable_set('searchsense_configs', array(
    'min' => $form_state['values']['searchsense_min'],
    'limit' => $form_state['values']['searchsense_limit'],
    'use_js' => $form_state['values']['searchsense_use_js'],
    'options' => $form_state['values']['searchsense_options'],
  ));

  // Presave searchsense js.module bootstrap
  // dependencies, since we cannot catch the searchsense
  // API implementers when the hook_js() gets triggered.
  if ($form_state['values']['searchsense_use_js']) {
    variable_set('searchsense_js_deps', array_merge(
      array('user', 'searchsense'),
      module_implements('searchsense'),
      module_implements('searchsense_alter')
    ));
  }

  // Set a message.
  drupal_set_message(t('Configuration options has been saved.'));
}

