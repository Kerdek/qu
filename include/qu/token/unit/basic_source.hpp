#ifndef H_8661BCFB_596F_4E22_9B7D_915D73B776BC
#define H_8661BCFB_596F_4E22_9B7D_915D73B776BC

namespace qu::token::unit
{

enum basic_source : char
{
    eof = 0,

    space = ' ',
    tab = '\t',
    cr = '\r',
    lf = '\n',

    underscore = '_',
    begin_id_alpha = 'a',
    end_id_alpha = 'z' + 1,

    paren_left = '(',
    paren_right = ')',
    bracket_left = '[',
    bracket_right = ']',
    brace_left = '{',
    brace_right = '}',

    quote_single = '\'',
    quote_double = '"',

    less = '<',
    greater = '>',
    equal = '=',

    hash = '#',
    at = '@',
    dot = '.',
    comma = ',',
    colon = ':',
    question = '?',
    bang = '!',
    tilde = '~',
    caret = '^',
    pipe = '|',
    amp = '&',
    plus = '+',
    minus = '-',
    star = '*',
    solidus = '/',
    reverse_solidus = '\\',
    percent = '%'
};

}

#endif