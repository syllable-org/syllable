/* ANSI-C code produced by gperf version 2.7.1 (19981006 egcs) */
/* Command-line: gperf -L ANSI-C -E -C -n -o -t -k * -NfindValue -Hhash_val -Wwordlist_value -D cssvalues.gperf  */
/* This file is automatically generated from cssvalues.in by makevalues, do not edit */
/* Copyright 1999 W. Bastian */
#include "cssvalues.h"
struct css_value {
    const char *name;
    int id;
};
/* maximum key range = 1544, duplicates = 1 */

#ifdef __GNUC__
__inline
#endif
static unsigned int
hash_val (register const char *str, register unsigned int len)
{
  static const unsigned short asso_values[] =
    {
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598,    0, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598,  190,    9,  112,
        30,  154,  190,  215,  200,   20,    0,    5,  115,   19,
         4,    0,   89,   15,   15,   25,   20,   20,   60,  220,
       145,    5,   60, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598, 1598,
      1598, 1598, 1598, 1598, 1598, 1598
    };
  register int hval = 0;

  switch (len)
    {
      default:
      case 20:
        hval += asso_values[(unsigned char)str[19]];
      case 19:
        hval += asso_values[(unsigned char)str[18]];
      case 18:
        hval += asso_values[(unsigned char)str[17]];
      case 17:
        hval += asso_values[(unsigned char)str[16]];
      case 16:
        hval += asso_values[(unsigned char)str[15]];
      case 15:
        hval += asso_values[(unsigned char)str[14]];
      case 14:
        hval += asso_values[(unsigned char)str[13]];
      case 13:
        hval += asso_values[(unsigned char)str[12]];
      case 12:
        hval += asso_values[(unsigned char)str[11]];
      case 11:
        hval += asso_values[(unsigned char)str[10]];
      case 10:
        hval += asso_values[(unsigned char)str[9]];
      case 9:
        hval += asso_values[(unsigned char)str[8]];
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      case 2:
        hval += asso_values[(unsigned char)str[1]];
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

#ifdef __GNUC__
__inline
#endif
const struct css_value *
findValue (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 189,
      MIN_WORD_LENGTH = 3,
      MAX_WORD_LENGTH = 20,
      MIN_HASH_VALUE = 54,
      MAX_HASH_VALUE = 1597
    };

  static const struct css_value wordlist_value[] =
    {
      {"sub", CSS_VAL_SUB},
      {"run-in", CSS_VAL_RUN_IN},
      {"bottom", CSS_VAL_BOTTOM},
      {"top", CSS_VAL_TOP},
      {"icon", CSS_VAL_ICON},
      {"ltr", CSS_VAL_LTR},
      {"rtl", CSS_VAL_RTL},
      {"blink", CSS_VAL_BLINK},
      {"bold", CSS_VAL_BOLD},
      {"none", CSS_VAL_NONE},
      {"loud", CSS_VAL_LOUD},
      {"cross", CSS_VAL_CROSS},
      {"mix", CSS_VAL_MIX},
      {"disc", CSS_VAL_DISC},
      {"solid", CSS_VAL_SOLID},
      {"menu", CSS_VAL_MENU},
      {"crop", CSS_VAL_CROP},
      {"inset", CSS_VAL_INSET},
      {"continuous", CSS_VAL_CONTINUOUS},
      {"both", CSS_VAL_BOTH},
      {"auto", CSS_VAL_AUTO},
      {"move", CSS_VAL_MOVE},
      {"soft", CSS_VAL_SOFT},
      {"outset", CSS_VAL_OUTSET},
      {"block", CSS_VAL_BLOCK},
      {"thin", CSS_VAL_THIN},
      {"inside", CSS_VAL_INSIDE},
      {"dotted", CSS_VAL_DOTTED},
      {"pre", CSS_VAL_PRE},
      {"medium", CSS_VAL_MEDIUM},
      {"outside", CSS_VAL_OUTSIDE},
      {"once", CSS_VAL_ONCE},
      {"invert", CSS_VAL_INVERT},
      {"justify", CSS_VAL_JUSTIFY},
      {"code", CSS_VAL_CODE},
      {"avoid", CSS_VAL_AVOID},
      {"pointer", CSS_VAL_POINTER},
      {"super", CSS_VAL_SUPER},
      {"x-loud", CSS_VAL_X_LOUD},
      {"inline", CSS_VAL_INLINE},
      {"bolder", CSS_VAL_BOLDER},
      {"double", CSS_VAL_DOUBLE},
      {"digits", CSS_VAL_DIGITS},
      {"oblique", CSS_VAL_OBLIQUE},
      {"low", CSS_VAL_LOW},
      {"silent", CSS_VAL_SILENT},
      {"text", CSS_VAL_TEXT},
      {"normal", CSS_VAL_NORMAL},
      {"thick", CSS_VAL_THICK},
      {"slow", CSS_VAL_SLOW},
      {"embed", CSS_VAL_EMBED},
      {"middle", CSS_VAL_MIDDLE},
      {"portrait", CSS_VAL_PORTRAIT},
      {"x-soft", CSS_VAL_X_SOFT},
      {"scroll", CSS_VAL_SCROLL},
      {"static", CSS_VAL_STATIC},
      {"list-item", CSS_VAL_LIST_ITEM},
      {"marker", CSS_VAL_MARKER},
      {"visible", CSS_VAL_VISIBLE},
      {"hide", CSS_VAL_HIDE},
      {"text-bottom", CSS_VAL_TEXT_BOTTOM},
      {"above", CSS_VAL_ABOVE},
      {"behind", CSS_VAL_BEHIND},
      {"square", CSS_VAL_SQUARE},
      {"hand", CSS_VAL_HAND},
      {"fast", CSS_VAL_FAST},
      {"n-resize", CSS_VAL_N_RESIZE},
      {"ridge", CSS_VAL_RIDGE},
      {"caption", CSS_VAL_CAPTION},
      {"hidden", CSS_VAL_HIDDEN},
      {"wider", CSS_VAL_WIDER},
      {"groove", CSS_VAL_GROOVE},
      {"show", CSS_VAL_SHOW},
      {"text-top", CSS_VAL_TEXT_TOP},
      {"wait", CSS_VAL_WAIT},
      {"s-resize", CSS_VAL_S_RESIZE},
      {"open-quote", CSS_VAL_OPEN_QUOTE},
      {"center", CSS_VAL_CENTER},
      {"no-open-quote", CSS_VAL_NO_OPEN_QUOTE},
      {"small", CSS_VAL_SMALL},
      {"right", CSS_VAL_RIGHT},
      {"italic", CSS_VAL_ITALIC},
      {"left", CSS_VAL_LEFT},
      {"x-low", CSS_VAL_X_LOW},
      {"konq-center", CSS_VAL_KONQ_CENTER},
      {"table", CSS_VAL_TABLE},
      {"below", CSS_VAL_BELOW},
      {"lower", CSS_VAL_LOWER},
      {"x-slow", CSS_VAL_X_SLOW},
      {"condensed", CSS_VAL_CONDENSED},
      {"status-bar", CSS_VAL_STATUS_BAR},
      {"underline", CSS_VAL_UNDERLINE},
      {"nowrap", CSS_VAL_NOWRAP},
      {"overline", CSS_VAL_OVERLINE},
      {"bidi-override", CSS_VAL_BIDI_OVERRIDE},
      {"circle", CSS_VAL_CIRCLE},
      {"slower", CSS_VAL_SLOWER},
      {"absolute", CSS_VAL_ABSOLUTE},
      {"spell-out", CSS_VAL_SPELL_OUT},
      {"fixed", CSS_VAL_FIXED},
      {"compact", CSS_VAL_COMPACT},
      {"help", CSS_VAL_HELP},
      {"static-position", CSS_VAL_STATIC_POSITION},
      {"x-fast", CSS_VAL_X_FAST},
      {"e-resize", CSS_VAL_E_RESIZE},
      {"ne-resize", CSS_VAL_NE_RESIZE},
      {"faster", CSS_VAL_FASTER},
      {"upper-roman", CSS_VAL_UPPER_ROMAN},
      {"armenian", CSS_VAL_ARMENIAN},
      {"level", CSS_VAL_LEVEL},
      {"crosshair", CSS_VAL_CROSSHAIR},
      {"se-resize", CSS_VAL_SE_RESIZE},
      {"x-small", CSS_VAL_X_SMALL},
      {"narrower", CSS_VAL_NARROWER},
      {"close-quote", CSS_VAL_CLOSE_QUOTE},
      {"no-close-quote", CSS_VAL_NO_CLOSE_QUOTE},
      {"repeat", CSS_VAL_REPEAT},
      {"no-repeat", CSS_VAL_NO_REPEAT},
      {"repeat-y", CSS_VAL_REPEAT_Y},
      {"dashed", CSS_VAL_DASHED},
      {"smaller", CSS_VAL_SMALLER},
      {"high", CSS_VAL_HIGH},
      {"decimal", CSS_VAL_DECIMAL},
      {"w-resize", CSS_VAL_W_RESIZE},
      {"nw-resize", CSS_VAL_NW_RESIZE},
      {"baseline", CSS_VAL_BASELINE},
      {"sw-resize", CSS_VAL_SW_RESIZE},
      {"large", CSS_VAL_LARGE},
      {"right-side", CSS_VAL_RIGHT_SIDE},
      {"larger", CSS_VAL_LARGER},
      {"left-side", CSS_VAL_LEFT_SIDE},
      {"upper-latin", CSS_VAL_UPPER_LATIN},
      {"default", CSS_VAL_DEFAULT},
      {"table-row", CSS_VAL_TABLE_ROW},
      {"transparent", CSS_VAL_TRANSPARENT},
      {"relative", CSS_VAL_RELATIVE},
      {"semi-condensed", CSS_VAL_SEMI_CONDENSED},
      {"lower-roman", CSS_VAL_LOWER_ROMAN},
      {"lighter", CSS_VAL_LIGHTER},
      {"always", CSS_VAL_ALWAYS},
      {"hebrew", CSS_VAL_HEBREW},
      {"xx-small", CSS_VAL_XX_SMALL},
      {"table-column", CSS_VAL_TABLE_COLUMN},
      {"repeat-x", CSS_VAL_REPEAT_X},
      {"x-high", CSS_VAL_X_HIGH},
      {"repeat-none", CSS_VAL_REPEAT_NONE},
      {"katakana", CSS_VAL_KATAKANA},
      {"expanded", CSS_VAL_EXPANDED},
      {"collapse", CSS_VAL_COLLAPSE},
      {"higher", CSS_VAL_HIGHER},
      {"inline-table", CSS_VAL_INLINE_TABLE},
      {"georgian", CSS_VAL_GEORGIAN},
      {"x-large", CSS_VAL_X_LARGE},
      {"separate", CSS_VAL_SEPARATE},
      {"uppercase", CSS_VAL_UPPERCASE},
      {"lower-latin", CSS_VAL_LOWER_LATIN},
      {"far-right", CSS_VAL_FAR_RIGHT},
      {"ultra-condensed", CSS_VAL_ULTRA_CONDENSED},
      {"far-left", CSS_VAL_FAR_LEFT},
      {"small-caps", CSS_VAL_SMALL_CAPS},
      {"small-caption", CSS_VAL_SMALL_CAPTION},
      {"landscape", CSS_VAL_LANDSCAPE},
      {"table-caption", CSS_VAL_TABLE_CAPTION},
      {"center-right", CSS_VAL_CENTER_RIGHT},
      {"message-box", CSS_VAL_MESSAGE_BOX},
      {"center-left", CSS_VAL_CENTER_LEFT},
      {"rightwards", CSS_VAL_RIGHTWARDS},
      {"leftwards", CSS_VAL_LEFTWARDS},
      {"line-through", CSS_VAL_LINE_THROUGH},
      {"capitalize", CSS_VAL_CAPITALIZE},
      {"xx-large", CSS_VAL_XX_LARGE},
      {"table-cell", CSS_VAL_TABLE_CELL},
      {"lowercase", CSS_VAL_LOWERCASE},
      {"semi-expanded", CSS_VAL_SEMI_EXPANDED},
      {"hiragana", CSS_VAL_HIRAGANA},
      {"extra-condensed", CSS_VAL_EXTRA_CONDENSED},
      {"lower-greek", CSS_VAL_LOWER_GREEK},
      {"table-row-group", CSS_VAL_TABLE_ROW_GROUP},
      {"table-column-group", CSS_VAL_TABLE_COLUMN_GROUP},
      {"upper-alpha", CSS_VAL_UPPER_ALPHA},
      {"ultra-expanded", CSS_VAL_ULTRA_EXPANDED},
      {"cjk-ideographic", CSS_VAL_CJK_IDEOGRAPHIC},
      {"table-footer-group", CSS_VAL_TABLE_FOOTER_GROUP},
      {"katakana-iroha", CSS_VAL_KATAKANA_IROHA},
      {"lower-alpha", CSS_VAL_LOWER_ALPHA},
      {"extra-expanded", CSS_VAL_EXTRA_EXPANDED},
      {"hiragana-iroha", CSS_VAL_HIRAGANA_IROHA},
      {"table-header-group", CSS_VAL_TABLE_HEADER_GROUP},
      {"decimal-leading-zero", CSS_VAL_DECIMAL_LEADING_ZERO}
    };

  static const short lookup[] =
    {
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,    0,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,    1,
        -1,   -1,   -1,   -1,    2,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,    3,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
         4,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1, -341, -184,
        -2,    7,    8,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,    9,   -1,   -1,   10,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   11,   -1,   -1,   -1,   -1,   -1,   -1,
        12,   -1,   -1,   13,   -1,   -1,   14,   -1,
        -1,   -1,   -1,   -1,   -1,   15,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        16,   -1,   -1,   -1,   -1,   -1,   -1,   17,
        -1,   18,   -1,   -1,   -1,   19,   20,   -1,
        -1,   21,   -1,   22,   -1,   -1,   -1,   23,
        -1,   24,   -1,   -1,   25,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   26,   27,   -1,
        -1,   -1,   28,   -1,   -1,   -1,   29,   -1,
        -1,   -1,   -1,   -1,   -1,   30,   31,   -1,
        -1,   32,   -1,   -1,   -1,   -1,   -1,   -1,
        33,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        34,   -1,   -1,   -1,   35,   -1,   36,   37,
        -1,   -1,   -1,   -1,   -1,   -1,   38,   -1,
        -1,   -1,   -1,   -1,   -1,   39,   -1,   -1,
        -1,   -1,   -1,   40,   -1,   -1,   -1,   -1,
        41,   -1,   42,   -1,   -1,   43,   -1,   44,
        -1,   -1,   45,   46,   -1,   -1,   -1,   47,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   48,   -1,   -1,
        49,   -1,   -1,   -1,   -1,   -1,   50,   -1,
        51,   52,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   53,   -1,   54,   -1,
        -1,   -1,   -1,   55,   -1,   -1,   -1,   -1,
        -1,   56,   -1,   -1,   -1,   -1,   57,   -1,
        -1,   -1,   -1,   58,   59,   -1,   -1,   60,
        -1,   -1,   -1,   -1,   -1,   61,   -1,   -1,
        -1,   62,   -1,   63,   -1,   -1,   -1,   -1,
        64,   65,   -1,   -1,   -1,   -1,   -1,   -1,
        66,   -1,   67,   68,   -1,   -1,   69,   70,
        -1,   -1,   -1,   -1,   71,   72,   -1,   -1,
        73,   -1,   74,   -1,   -1,   75,   -1,   -1,
        76,   -1,   -1,   77,   78,   -1,   -1,   -1,
        79,   -1,   -1,   -1,   -1,   -1,   80,   -1,
        -1,   -1,   -1,   -1,   -1,   81,   -1,   82,
        83,   -1,   -1,   84,   -1,   -1,   -1,   -1,
        85,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   86,   -1,   -1,   -1,   -1,   -1,
        87,   88,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   89,   90,   -1,   91,   -1,   92,   -1,
        -1,   -1,   93,   -1,   -1,   -1,   -1,   94,
        95,   96,   -1,   -1,   -1,   97,   -1,   -1,
        -1,   -1,   98,   99,   -1,   -1,  100,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  101,   -1,
        -1,   -1,   -1,   -1,   -1,  102,   -1,   -1,
        -1,   -1,  103,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  104,   -1,
        -1,   -1,  105,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,  106,  107,  108,   -1,  109,   -1,
        -1,   -1,  110,   -1,   -1,   -1,   -1,  111,
        -1,  112,   -1,   -1,   -1,  113,   -1,  114,
        -1,   -1,   -1,  115,   -1,   -1,  116,   -1,
        -1,   -1,  117,  118,   -1,  119,   -1,   -1,
        -1,  120,   -1,  121,   -1,   -1,   -1,   -1,
       122,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
       123,   -1,   -1,   -1,  124,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  125,
        -1,  126,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,  127,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  128,   -1,   -1,   -1,   -1,
       129,   -1,   -1,   -1,  130,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,  131,   -1,   -1,  132,
        -1,   -1,   -1,  133,   -1,   -1,  134,   -1,
       135,   -1,   -1,  136,  137,   -1,   -1,   -1,
        -1,   -1,   -1,  138,   -1,   -1,   -1,   -1,
        -1,  139,   -1,   -1,   -1,   -1,   -1,   -1,
       140,   -1,  141,   -1,   -1,   -1,  142,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  143,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,  144,   -1,   -1,   -1,
       145,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,  146,   -1,  147,   -1,   -1,   -1,
       148,   -1,   -1,   -1,  149,  150,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,  151,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,  152,   -1,   -1,  153,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
       154,   -1,   -1,   -1,   -1,  155,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,  156,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,  157,  158,   -1,   -1,   -1,   -1,   -1,
       159,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  160,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,  161,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  162,   -1,   -1,   -1,   -1,
        -1,  163,   -1,   -1,   -1,   -1,   -1,   -1,
       164,   -1,  165,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  166,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  167,
        -1,   -1,   -1,  168,   -1,   -1,   -1,   -1,
        -1,   -1,  169,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  170,   -1,   -1,   -1,   -1,
       171,  172,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  173,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
       174,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,  175,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  176,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  177,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,  178,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  179,
        -1,   -1,   -1,   -1,  180,   -1,   -1,   -1,
        -1,   -1,  181,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  182,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  183,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
       184,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
       185,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,  186,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,  187,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,  188
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash_val (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int index = lookup[key];

          if (index >= 0)
            {
              register const char *s = wordlist_value[index].name;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist_value[index];
            }
          else if (index < -TOTAL_KEYWORDS)
            {
              register int offset = - 1 - TOTAL_KEYWORDS - index;
              register const struct css_value *wordptr = &wordlist_value[TOTAL_KEYWORDS + lookup[offset]];
              register const struct css_value *wordendptr = wordptr + -lookup[offset + 1];

              while (wordptr < wordendptr)
                {
                  register const char *s = wordptr->name;

                  if (*str == *s && !strcmp (str + 1, s + 1))
                    return wordptr;
                  wordptr++;
                }
            }
        }
    }
  return 0;
}
static const char * valueList[] = {
"",
"above", 
"absolute", 
"always", 
"armenian", 
"auto", 
"avoid", 
"baseline", 
"behind", 
"below", 
"bidi-override", 
"blink", 
"block", 
"bold", 
"bolder", 
"both", 
"bottom", 
"capitalize", 
"caption", 
"center", 
"center-left", 
"center-right", 
"circle", 
"cjk-ideographic", 
"close-quote", 
"code", 
"collapse", 
"compact", 
"condensed", 
"continuous", 
"crop", 
"cross", 
"crosshair", 
"dashed", 
"decimal", 
"decimal-leading-zero", 
"default", 
"digits", 
"disc", 
"dotted", 
"double", 
"e-resize", 
"embed", 
"expanded", 
"extra-condensed", 
"extra-expanded", 
"far-left", 
"far-right", 
"fast", 
"faster", 
"fixed", 
"georgian", 
"groove", 
"hand", 
"hebrew", 
"help", 
"hidden", 
"hide", 
"high", 
"higher", 
"hiragana", 
"hiragana-iroha", 
"icon", 
"inline", 
"inline-table", 
"inset", 
"inside", 
"invert", 
"italic", 
"justify", 
"katakana", 
"katakana-iroha", 
"landscape", 
"large", 
"larger", 
"left", 
"left-side", 
"leftwards", 
"level", 
"lighter", 
"line-through", 
"list-item", 
"loud", 
"low", 
"lower", 
"lower-alpha", 
"lower-greek", 
"lower-latin", 
"lower-roman", 
"lowercase", 
"ltr", 
"marker", 
"medium", 
"menu", 
"message-box", 
"middle", 
"mix", 
"move", 
"n-resize", 
"narrower", 
"ne-resize", 
"no-close-quote", 
"no-open-quote", 
"no-repeat", 
"none", 
"normal", 
"nowrap", 
"nw-resize", 
"oblique", 
"once", 
"open-quote", 
"outset", 
"outside", 
"overline", 
"pointer", 
"portrait", 
"pre", 
"relative", 
"repeat", 
"repeat-x", 
"repeat-y", 
"repeat-none", 
"ridge", 
"right", 
"right-side", 
"rightwards", 
"rtl", 
"run-in", 
"s-resize", 
"scroll", 
"se-resize", 
"semi-condensed", 
"semi-expanded", 
"separate", 
"show", 
"silent", 
"slow", 
"slower", 
"small", 
"smaller", 
"small-caps", 
"small-caption", 
"soft", 
"solid", 
"spell-out", 
"square", 
"static", 
"static-position", 
"status-bar", 
"sub", 
"super", 
"sw-resize", 
"table", 
"table-caption", 
"table-cell", 
"table-column", 
"table-column-group", 
"table-footer-group", 
"table-header-group", 
"table-row", 
"table-row-group", 
"text", 
"text-bottom", 
"text-top", 
"thin", 
"thick", 
"top", 
"transparent", 
"ultra-condensed", 
"ultra-expanded", 
"underline", 
"upper-alpha", 
"upper-latin", 
"upper-roman", 
"uppercase", 
"visible", 
"w-resize", 
"wait", 
"wider", 
"x-fast", 
"x-high", 
"x-large", 
"x-loud", 
"x-low", 
"x-slow", 
"x-small", 
"x-soft", 
"xx-large", 
"xx-small", 
"konq-center", 
    0
};
DOMString getValueName(unsigned short id)
{
    if(id >= CSS_VAL_TOTAL || id == 0)
      return 0;
    else
      return DOMString(valueList[id]);
};

