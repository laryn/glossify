$Id$

glossify.module -- Link nodes with text to nodes with titles that are terms
---------------------------------------------------------------------------

Autors
----------
- ea.Farris <eric@eafarris.com> - <http://drupal.org/user/812>
- rsvelko - vladimir@segments.at - http://segments.at/


What It Is
-----------
See proect page for an up to date and detailed intro.


INSTALL
-----------
- download, enable and set up via admin/settings/glossify

Styles of link display/ modes of bondage
-----------------

Glossify has several ways to display the definitions of the terms when
found:

  Hovertips
-------------  
  This requires the hovertip.module
  <http://drupal.org/project/hovertip>, which uses jQuery to provide
  pop-up windows with terms and their definitions (titles and bodies,
  respectively).

  Links
-----------
  This style creates links that go to the node itself, as a wiki would.

  Reference section under content
-----------
  This style creates a "Terms referenced" area that lists the terms used
  in the content (titles) along with their definitions (bodies). This
  section is then placed under the body of the main content. It is
  themeable -- see "How to Theme It," below.



How to Theme It
-----------------
If you wish to change the looks of the display of glossary terms and
their definitions, you have several options:

* When using the 'hovertip' style, styling of the pop-up window is 
handled by the hovertip module. In addition:

    * The term is wrapped in a <span> with a class of "glossify-term".
    * The hovertip itself is created via the overrideable function
      theme_glossify_term().

* When using the 'links' style, all links have a class of
  'glossify-term' added to the anchor tag, which can be defined in CSS.
  By default, terms are italicized in glossify.css.

* When using the 'reference' style, all terms are wrapped in a <span>
  with a class of "glossify-term". By default, terms are italicized in
  glossify.css. 

  In addition, the reference section itself is themeable. By default:
  
    * The entire section is wrapped in a <div id="glossify_reference">.
    * The terms and definitions are a standard HTML definition list
      (<dl><dt><dd>) hierarchy.
    * Each term is created via the overrideable function
      theme_glossify_term().
    * The section is created via the overrideable function
      theme_glossify_reference_section(). 

Problems with It
-------------------
    As *every* node body is searched for *every* glossary term's title on
*every* node view, this module could cause a performance hit on sites
with large glossaries. Drupal's caching mechanism should compensate for
most of this, and the actual hit should be negligible; nevertheless it's
something to think about.

    Since v2.0 major improvements in the functionality and 
performance were made.
      
Sponsorship
--------------

Development of this module was sponsored by leptree.net. (eafarris)

And from the middle of 2009 the development was 
further sponsored by http://segments.at/ (rsvelko).




