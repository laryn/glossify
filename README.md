# Glossify

The Glossify module provides filters that scan and parse content and replace
terms in the text with links to their pages. It consists of 2 filters:

 - **Glossify with taxonomy** - links taxonomy terms appearing in content to
   their taxonomy term page. You can select which taxonomy vocabularies to use
   as the source for the terms.
 - **Glossify with content** - links titles of content appearing in other
   content to their page. You can select which content types to use as the
   source for the terms.

## Installation

- Install this module using the [official Backdrop CMS instructions](https://backdropcms.org/guide/modules)

## Usage

- Navigate to `admin/config/content/formats`.
- Click 'configure' for a text format to which you would like to add a glossify
  filter.
- Enable the desired filter in the "Enabled filters" section.
- Check the desired settings in the "Filter settings" vertical tab.

More detailed usage instructions can be
[viewed or edited in the Wiki](https://github.com/backdrop-contrib/glossify/wiki).

### Theming
The module provides a theme function (`theme_glossify_links`) and some basic css
which uses Backdrop's core icon API. Override and customize as desired.

## Issues

 - Bugs and Feature requests should be reported in the [Issue Queue](https://github.com/backdrop-contrib/glossify/issues).

## Current Maintainers

 - [Laryn Kragt Bakker](https://github.com/laryn).
 - Collaboration and co-maintainers welcome!

## Credits

 - Ported to Backdrop CMS by [Laryn Kragt Bakker](https://github.com/laryn).
 - Maintained for Drupal by [anybody](https://www.drupal.org/u/anybody),
   [sanduhrs](https://www.drupal.org/u/sanduhrs),
   [WorldFallz](https://www.drupal.org/u/worldfallz),
   and [grevil](https://www.drupal.org/u/grevil).

 ## License

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.
