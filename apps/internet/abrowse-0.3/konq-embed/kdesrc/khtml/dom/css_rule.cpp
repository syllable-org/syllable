/**
 * This file is part of the DOM implementation for KDE.
 *
 * (C) 1999 Lars Knoll (knoll@kde.org)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * $Id$
 */
#include "css_ruleimpl.h"

#include "css_stylesheet.h"
#include "css_value.h"
#include "dom_exception.h"
#include "dom_string.h"

#include "css_rule.h"
using namespace DOM;

CSSRule::CSSRule()
{
    impl = 0;
}

CSSRule::CSSRule(const CSSRule &other)
{
    impl = other.impl;
    if(impl) impl->ref();
}

CSSRule::CSSRule(CSSRuleImpl *i)
{
    impl = i;
    if(impl) impl->ref();
}

CSSRule &CSSRule::operator = (const CSSRule &other)
{
    if(impl) impl->deref();
    impl = other.impl;
    if(impl) impl->ref();
    return *this;
}

CSSRule::~CSSRule()
{
    if(impl) impl->deref();
}

unsigned short CSSRule::type() const
{
    if(!impl) return 0;
    return ((CSSRuleImpl *)impl)->type();
}

DOMString CSSRule::cssText() const
{
    // ###
    if(!impl) return 0;
    //return ((ElementImpl *)impl)->getAttribute("cssText");
    return 0;
}

void CSSRule::setCssText( const DOMString &/*value*/ )
{
    // ###
    //if(impl) ((ElementImpl *)impl)->setAttribute("cssText", value);
}

CSSStyleSheet CSSRule::parentStyleSheet() const
{
    if(!impl) return CSSStyleSheet();
    return ((CSSRuleImpl *)impl)->parentStyleSheet();
}

CSSRule CSSRule::parentRule() const
{
    if(!impl) return 0;
    return ((CSSRuleImpl *)impl)->parentRule();
}


// ----------------------------------------------------------


CSSCharsetRule::CSSCharsetRule() : CSSRule()
{
}

CSSCharsetRule::CSSCharsetRule(const CSSCharsetRule &other) : CSSRule(other)
{
}

CSSCharsetRule::CSSCharsetRule(CSSCharsetRuleImpl *impl) : CSSRule(impl)
{
}

CSSCharsetRule &CSSCharsetRule::operator = (const CSSCharsetRule &other)
{
    CSSRule::operator = (other);
    return *this;
}

CSSCharsetRule::~CSSCharsetRule()
{
}

DOMString CSSCharsetRule::encoding() const
{
    if(!impl) return 0;
    //return ((ElementImpl *)impl)->getAttribute("encoding");
    return 0;
}

void CSSCharsetRule::setEncoding( const DOMString &/*value*/ )
{
    //if(impl) ((ElementImpl *)impl)->setAttribute("encoding", value);
}


// ----------------------------------------------------------


CSSFontFaceRule::CSSFontFaceRule() : CSSRule()
{
}

CSSFontFaceRule::CSSFontFaceRule(const CSSFontFaceRule &other) : CSSRule(other)
{
}

CSSFontFaceRule::CSSFontFaceRule(CSSFontFaceRuleImpl *impl) : CSSRule(impl)
{
}

CSSFontFaceRule &CSSFontFaceRule::operator = (const CSSFontFaceRule &other)
{
    CSSRule::operator = (other);
    return *this;
}

CSSFontFaceRule::~CSSFontFaceRule()
{
}

CSSStyleDeclaration CSSFontFaceRule::style() const
{
    if(!impl) return CSSStyleDeclaration();
    return ((CSSFontFaceRuleImpl *)impl)->style();
}


// ----------------------------------------------------------


CSSImportRule::CSSImportRule() : CSSRule()
{
}

CSSImportRule::CSSImportRule(const CSSImportRule &other) : CSSRule(other)
{
}

CSSImportRule::CSSImportRule(CSSImportRuleImpl *impl) : CSSRule(impl)
{
}

CSSImportRule &CSSImportRule::operator = (const CSSImportRule &other)
{
    CSSRule::operator = (other);
    return *this;
}

CSSImportRule::~CSSImportRule()
{
}

DOMString CSSImportRule::href() const
{
    if(!impl) return 0;
    return ((CSSImportRuleImpl *)impl)->href();
}

MediaList CSSImportRule::media() const
{
    if(!impl) return MediaList();
    return ((CSSImportRuleImpl *)impl)->media();
}

CSSStyleSheet CSSImportRule::styleSheet() const
{
    if(!impl) return CSSStyleSheet();
    return ((CSSImportRuleImpl *)impl)->styleSheet();
}


// ----------------------------------------------------------


CSSMediaRule::CSSMediaRule() : CSSRule()
{
}

CSSMediaRule::CSSMediaRule(const CSSMediaRule &other) : CSSRule(other)
{
}

CSSMediaRule::CSSMediaRule(CSSMediaRuleImpl *impl) : CSSRule(impl)
{
}

CSSMediaRule &CSSMediaRule::operator = (const CSSMediaRule &other)
{
    CSSRule::operator = (other);
    return *this;
}

CSSMediaRule::~CSSMediaRule()
{
}

MediaList CSSMediaRule::media() const
{
    if(!impl) return MediaList();
    return ((CSSMediaRuleImpl *)impl)->media();
}

CSSRuleList CSSMediaRule::cssRules() const
{
    if(!impl) return CSSRuleList();
    return ((CSSMediaRuleImpl *)impl)->cssRules();
}

unsigned long CSSMediaRule::insertRule( const DOMString &rule, unsigned long index )
{
    if(!impl) return 0;
    return ((CSSMediaRuleImpl *)impl)->insertRule( rule, index );
}

void CSSMediaRule::deleteRule( unsigned long index )
{
    if(impl)
        ((CSSMediaRuleImpl *)impl)->deleteRule( index );
}


// ----------------------------------------------------------


CSSPageRule::CSSPageRule() : CSSRule()
{
}

CSSPageRule::CSSPageRule(const CSSPageRule &other) : CSSRule(other)
{
}

CSSPageRule::CSSPageRule(CSSPageRuleImpl *impl) : CSSRule(impl)
{
}

CSSPageRule &CSSPageRule::operator = (const CSSPageRule &other)
{
    CSSRule::operator = (other);
    return *this;
}

CSSPageRule::~CSSPageRule()
{
}

DOMString CSSPageRule::selectorText() const
{
    if(!impl) return 0;
    //return ((ElementImpl *)impl)->getAttribute("selectorText");
    return 0;
}

void CSSPageRule::setSelectorText( const DOMString &/*value*/ )
{
    //if(impl) ((ElementImpl *)impl)->setAttribute("selectorText", value);
}

CSSStyleDeclaration CSSPageRule::style() const
{
    if(!impl) return CSSStyleDeclaration();
    return ((CSSPageRuleImpl *)impl)->style();
}


// ----------------------------------------------------------

CSSStyleRule::CSSStyleRule() : CSSRule()
{
}

CSSStyleRule::CSSStyleRule(const CSSStyleRule &other) : CSSRule(other)
{
}

CSSStyleRule::CSSStyleRule(CSSStyleRuleImpl *impl) : CSSRule(impl)
{
}

CSSStyleRule &CSSStyleRule::operator = (const CSSStyleRule &other)
{
    CSSRule::operator = (other);
    return *this;
}

CSSStyleRule::~CSSStyleRule()
{
}

DOMString CSSStyleRule::selectorText() const
{
    if(!impl) return 0;
    //return ((ElementImpl *)impl)->getAttribute("selectorText");
    return 0;
}

void CSSStyleRule::setSelectorText( const DOMString &/*value*/ )
{
    //if(impl) ((ElementImpl *)impl)->setAttribute("selectorText", value);
}

CSSStyleDeclaration CSSStyleRule::style() const
{
    if(!impl) return CSSStyleDeclaration();
    return ((CSSStyleRuleImpl *)impl)->style();
}


// ----------------------------------------------------------


CSSUnknownRule::CSSUnknownRule() : CSSRule()
{
}

CSSUnknownRule::CSSUnknownRule(const CSSUnknownRule &other) : CSSRule(other)
{
}

CSSUnknownRule::CSSUnknownRule(CSSUnknownRuleImpl *impl) : CSSRule(impl)
{
}

CSSUnknownRule &CSSUnknownRule::operator = (const CSSUnknownRule &other)
{
    CSSRule::operator = (other);
    return *this;
}

CSSUnknownRule::~CSSUnknownRule()
{
}


// ----------------------------------------------------------

// ### need to create a CSSRuleListImpl class for this

CSSRuleList::CSSRuleList()
{
//    impl = 0;
}

CSSRuleList::CSSRuleList(const CSSRuleList &/*other*/)
{
//    impl = other.impl;
//    if(impl) impl->ref();
}

CSSRuleList::CSSRuleList(CSSRuleListImpl */*i*/)
{
//    impl = i;
//    if(impl) impl->ref();
}

CSSRuleList::CSSRuleList(StyleListImpl */*i*/)
{
//    impl = ?
}

CSSRuleList &CSSRuleList::operator = (const CSSRuleList &/*other*/)
{
//    if(impl) impl->deref();
//    impl = other.impl;
//    if(impl) impl->ref();
    return *this;
}

CSSRuleList::~CSSRuleList()
{
//    if(impl) impl->deref();
}

unsigned long CSSRuleList::length() const
{
    if(!impl) return 0;
    //return ((CSSRuleListImpl *)impl)->length();
    return 0;
}

CSSRule CSSRuleList::item( unsigned long /*index*/ )
{
    if(!impl) return CSSRule();
    //return ((CSSRuleListImpl *)impl)->item( index );
    return CSSRule();
}



