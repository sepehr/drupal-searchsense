// $Id

/**
 * @file
 * Contains necessary Drupal JS behaviors to make the searchsense
 * dynamically interact with Custom Search module's content types dropdown.
 */

/**
 * Dynamically changes the searchsense autocompletion path.
 *
 * @param context
 *   Context!
 * @param $types
 *   jQuery object of content types dropdown element.
 * @param $sense
 *   jQuery object of searchsense textfield.
 * @param $sensePath
 *   jQuery object of that hidden autocomplete textfield.
 *
 * @return
 *   The new path for searchsense.
 */
Drupal.behaviors.dynosense = function(context, $types, $sense, $sensePath) {
  var $types = $types || $('#edit-custom-search-types'),
      $sense = $sense || $('#edit-search-block-form-1'),
      $sensePath = $sensePath || $('#edit-search-block-form-1-autocomplete'),
      nodeType = $types.val().substr(2);

  // Set the new path.
  var newPath = (nodeType == 'all') ?
    Drupal.settings.basePath + Drupal.settings.searchsense.path :
    Drupal.settings.basePath + Drupal.settings.searchsense.path + '/' + nodeType;
  $sensePath
    .val(newPath)
    .removeClass('autocomplete-processed');

  // Unbind to prevent trigger duplication.
  $sense
    .unbind('keyup')
    .unbind('keydown');

  // Reattach the autocomplete behavior.
  Drupal.behaviors.autocomplete(document);

  // Return the new path for the sake of glotha throbe!
  return newPath;
};


/**
 * Binds dynosense!
 */
Drupal.behaviors.dynosenseBinder = function(context) {
  var $types = $('#edit-custom-search-types'),
      $sense = $('#edit-search-block-form-1'),
      $sensePath = $('#edit-search-block-form-1-autocomplete');

  $types.bind('change', function() {
    $sense.trigger('focus');
    Drupal.behaviors.dynosense(context, $types, $sense, $sensePath);
  });
};

