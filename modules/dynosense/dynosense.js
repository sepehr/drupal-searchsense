// $Id

/**
 * @file
 * Contains necessary Drupal JS behaviors to make the searchsense
 * dynamically interact with Custom Search module's content types dropdown.
 */

/**
 * Dynamically changes the searchsense autocompletion path in a search block.
 *
 * @todo Fix/Improve!
 */
Drupal.behaviors.dynosense = function(context) {
  var newPath = Drupal.settings.basePath,
      $types = $('#edit-custom-search-types'),
      $sense = $('#edit-search-block-form-1'),
      $sensepath = $('#edit-search-block-form-1-autocomplete');

  $types.bind('change', function() {
    nodeType = $types.val().substr(2);

    // Set the new path.
    newPath += (nodeType == 'all') ?
      Drupal.settings.searchsense.path :
      Drupal.settings.searchsense.path + '/' + nodeType;
    $sensepath
      .val(newPath)
      .removeClass('autocomplete-processed');

    // Unbind to prevent trigger duplication.
    $sense
      .unbind('blur')
      .unbind('keyup')
      .unbind('keydown');

    // Reattach the autocomplete behavior.
    Drupal.behaviors.autocomplete(document);
  });
};

