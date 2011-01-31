// $Id$

/**
 * @file
 * Contains necessary Drupal JS behaviors to make the searchsense
 * dynamically interact with Custom Search module's content types dropdown.
 */

/**
 * Defines dynosense mother object.
 */
Drupal.dynosense = Drupal.dynosense || {};

/**
 * Dynamically updates the searchsense autocompletion path.
 *
 * @param context
 *   Context!
 * @param $typeSelector
 *   jQuery object of custom search type selector.
 * @param $sense
 *   jQuery object of searchsense textfield.
 * @param $sensePath
 *   jQuery object of that hidden autocomplete textfield.
 *
 * @return
 *   The new path for searchsense.
 */
Drupal.dynosense.updatePath = function(context, $typeSelector, $sense, $sensePath) {
  var newPath = Drupal.settings.basePath,
      lookupType = $typeSelector.val().substr(2);

  switch (lookupType) {
    case 'all':
      newPath += Drupal.settings.searchsense.path;
      break;

    case 'user':
      newPath += 'user/autocomplete';
      break;

    default:
      newPath += Drupal.settings.searchsense.path + '/' + lookupType;
  }

  // Set it.
  $sensePath
    .val(newPath)
    .removeClass('autocomplete-processed');
  // Unbind to prevent trigger duplication.
  $sense
    .unbind('keyup')
    .unbind('keydown');
  // Reattach the autocomplete behavior.
  Drupal.behaviors.autocomplete(document);

  // And return the new path.
  return newPath;
};

/**
 * Binds and performs dynosense.updatePath() where required.
 */
Drupal.behaviors.dynosense = function(context) {
  $(context).find('.custom-search-types').each(function() {
    var $this = $(this),
        $sense =  $this.parents('form').find('.form-autocomplete'),
        $sensePath = $sense.parent().next('.autocomplete');

    // Perform on document ready.
    Drupal.dynosense.updatePath(context, $this, $sense, $sensePath);
    // And on change.
    $this.bind('change', function() {
      Drupal.dynosense.updatePath(context, $this, $sense, $sensePath);
      $sense.trigger('focus');
    });
  });
};

