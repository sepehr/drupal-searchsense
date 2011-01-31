// $Id$

Description
===========
Provides extensible, configurable search autocompletion ability for Drupal.

NOTICE
======
IT'S ON DEVELOPMENT STAGE AND STILL NOT READY FOR PRODUCTION.

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

Author and Maintainer
=====================
sepehr (Sepehr Lajevardi)

