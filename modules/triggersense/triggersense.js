// $Id$

/**
 * @file
 * Searchsense Trigger JS behaviors.
 */

/**
 * Defines triggersense mother object.
 */
Drupal.triggersense = Drupal.triggersense || {};


/**
 * Helper method to perform a delayed form submission.
 *
 * @param $form
 *   jQuery object of target form.
 */
Drupal.triggersense.delayedSubmit = function($form) {
  window.setTimeout(function() {
    $form
      .find('.form-submit[type="submit"]')
      .trigger('click');
  }, 200);

  return false;
};


/**
 * Alters autocomplete fields behavior to accept Click/Enter events.
 */
Drupal.behaviors.triggersense = function(context) {
  $(context).find('.form-autocomplete').each(function() {
    // Preserve this.
    var $this = $(this);

    // Enter key submission trigger.
    $this
      .unbind('keypress')
      .bind('keypress', function(e) {
        if (e.keyCode == 13) {
          Drupal.triggersense.delayedSubmit($this.parents('form'));
        }
      });

    // Click submission trigger.
    $this
      .parents('form')
      .find('#autocomplete li')
      .bind('click', function(e) {
        Drupal.triggersense.delayedSubmit($this.parents('form'));
      });
  });
};


/**
 * Binds the triggersense behavior where required.
 */
Drupal.behaviors.triggersenseBinder = function(context) {
  $(document).bind('ajaxComplete', function() {
    Drupal.behaviors.triggersense(context);
  });
};

