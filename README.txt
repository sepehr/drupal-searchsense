Description
===========
A module suite providing extensible, configurable and fast typeahead ability for the core search. Also it might be used as an API.

Disclaimer
==========
This module is in an early development stage, It is not intended to be used in production.

Installation
============
Enable the module and goto admin/settings/search/autocomplete to configure your sense!

How to develop a Searchsense Provider
=====================================
- If required, Alter Searchsense's administration form by implementing hook_form_searchsense_admin_alter().
- If required, attach proper form validation and submission callbacks.
- Implement hook_searchsense() and return a privider-id-keyed array of keyed suggestions, if you want to extend its suggestions.
- Implement hook_searchsense_alter() if you're interested in modifying the suggestions.
- Checkout submodules for code examples.

API Usage Example
=================
<?php
	/**
	 * Implements hook_searchsense().
	 */
	function nodesense_searchsense($a1 = '', $a2 = '', $limit = 10) {
	  $matches = array();

	  if ($a1 && ($query = variable_get('nodesense_query', FALSE))) {
		$results = db_query_range($query, $a1, 0, (int) $limit);
		while ($result = db_fetch_object($results)) {
		  $matches[$result->type][$result->title] = check_plain($result->title);
		}
	  }
	  return array('nodesense' => $matches);
	}
?>

Author and Maintainer
=====================
Sepehr Lajevardi (http://drupal.org/user/668010)

