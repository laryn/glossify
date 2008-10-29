# Glossify.module -- Link terms to definitions

ea.Farris <eric@eafarris.com>
<http://drupal.org/user/812>

## What It Is

Glossify.module links content on your site with other content on your
site. Specifically, if you have a content type for terms and their
defintions, glossify.module will search other content on your site for
those terms and link them to their defintions, in configurable ways.

This module is similar to glossary.module and g2.module, except that it
offers more configurability, and can work with content types instead of
taxonomy.

## Installing and Enabling It

Drop the glossify/ folder into your sites/<drupalsite>/modules or
sites/all/modules. Then visit admin/build/modules to enable glossify.
You'll find it in the "Other" group.

## How to Use It

Glossify wants to have one or more content type that is used for terms.
Typically this is used in a glossary-type fashion, where there are
jargon requiring clarification, or in wiki-type fashion, where terms
are used to provide additional information about a topic.

This "glossary term" content type (there could be more than one) needs
be only as simple as a CCK-created content type with only title and body
fields, or can be as complex as necessary, with additional fields and
rich media. This module concerns itself only with title and body.

On each node view (and optionally on teaser view) the content is
searched for each glossary term's title and linked if found. There are
several ways the content can be linked; see "Customizing It," below.

## Customizing It

Glossify.module is very configurable. Upon visiting
admin/settings/glossify, you are presented with the Glossify settings
page, which contains the fields below:

Node types holding glossary terms

This is a list of content types on your system. Select one or more of
these content types to serve as the "glossary" for your site. 

Search the content of these types

This is also a list of content types on your system. The types selected
here will have their content looked through for the terms specified in
"Node types holding glossary terms," above. Using this list, you can
exempt one or more of your content types from being searched. For
example, you may have a "wiki" content type that you want cross-linked
with other content from "wiki," but don't want glossify to mark up your
"blog entry" content.

Only link first occurance of term

By selecting this checkbox, glossify will link the term when it finds
it, but only the first time. Subsequent uses of the term within the
content won't be touched. Some people prefer this type of markup, and it
can help to elminate some "link-happy" pieces of text, when the same
term is used over and over in the text.

Link content in teaser

You can choose, by selecting this checkbox, to have the teasers searched
through for terms. If off, only the full view of a node is searched, and
terms found in the teaser are never linked.

Style of glossary terms

Glossify has several ways to display the definitions of the terms when
found:

  Hovertips
  
  This requires the hovertip.module
  <http://drupal.org/project/hovertip>, which uses jQuery to provide
  pop-up windows with terms and their definitions (titles and bodies,
  respectively).

  Links

  This style creates links that go to the node itself, as a wiki would.

  Reference section under content

  This style creates a "Terms referenced" area that lists the terms used
  in the content (titles) along with their definitions (bodies). This
  section is then placed under the body of the main content. It is
  themeable -- see "How to Theme It," below.

## How to Theme It

If you wish to change the looks of the display of glossary terms and
their definitions, you have several options:

* When using the 'hovertip' style, styling of the pop-up window is handled by the
  hovertip module. In addition:

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

## Problems with It

As *every* node body is searched for *every* glossary term's title on
*every* node view, this module could cause a performance hit on sites
with large glossaries. Drupal's caching mechanism should compensate for
most of this, and the actual hit should be negligible; nevertheless it's
something to think about.
      
## Sponsorship

Development of this module was sponsored by leptree.net.
