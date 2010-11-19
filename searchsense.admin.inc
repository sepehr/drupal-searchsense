<?php
// $Id$

/**
 * @file
 * Searchsense administration callbacks.
 */

/**
 * Form callback for administration form.
 */
function searchsense_admin() {
  $form = array();
  global $_searchsense;

  $form['searchsense'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search Autocompletion'),
    '#weight' => 0,
  );

  $form['searchsense']['searchsense_options'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enable autocompletion for'),
    '#default_value' => $_searchsense,
    '#options' => array(
      'user' => t('User search form'),
      'block' => t('Search block form'),
      'theme' => t('Theme search form'),
      'advanced' => t('Advanced search form'),
    ),
  );

  $js_enabled = module_exists('js');
  $form['searchsense']['searchsense_use_js'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make use of <a href="!link">High performance JS callback handler</a>. <em>(recommended)</em>',
      array('!link' => 'http://drupal.org/project/js')
    ),
    '#default_value' => variable_get('searchsense_use_js', FALSE),
    '#return_value' => 1,
    '#disabled' => !$js_enabled,
  );

  $form['searchsense']['searchsense_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of suggestions'),
    '#default_value' => variable_get('searchsense_limit', 10),
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
}


/**
 * Submission callback for administration form.
 */
function searchsense_admin_submit($form, &$form_state) {
  variable_set('searchsense_limit', $form_state['values']['searchsense_limit']);
  variable_set('searchsense_use_js', $form_state['values']['searchsense_use_js']);
  variable_set('searchsense_options', $form_state['values']['searchsense_options']);

  // Presave searchsense js.module bootstrap
  // dependencies, since we cannot find searchsense API
  // implementer modules when the hook_js() gets triggered.
  if ($form_state['values']['searchsense_use_js']) {
    variable_set('searchsense_js_deps', array_merge(
      array('locale', 'user', 'searchsense'), module_implements('searchsense')
    ));
  }
}

