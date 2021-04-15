%{
#include "tokens.hpp"
%}
SPACE [ ]
TAB \t
CR \r
DQ \"
LF (\n)
WS ({SPACE}|{TAB}|{CR}|{LF})
LETTER [a-zA-Z]
DIGIT [0-9]
ID {LETTER}({LETTER}|{DIGIT})*
relop (==|!=|<=|>=|<|>)
binop [\*\+\-\/]
%%
void {return VOID;}
int {return INT;}
byte {return BYTE;}
bool {return BOOL;}
and {return AND;}
or {return OR;}
not {return NOT;}
true {return TRUE;}
false {return FALSE;}
return {return RETURN;}
if {return IF;}
else {return ELSE;}
while {return WHILE;}
break {return BREAK;}
continue {return CONTINUE;}
switch {return SWITCH;}
case {return CASE;}
default {return DEFAULT;}
{relop} {return RELOP;}
: {return COLON;}
; {return SC;}
, {return COMMA;}
\( {return LPAREN;}
\) {return RPAREN;}
\{ {return LBRACE;}
\} {return RBRACE;}
= {return ASSIGN;}
b {return B;}
{binop} {return BINOP;}
0|[1-9]{DIGIT}* {return NUM;}
{ID} {return ID;}
\n { yylineno++; return WS;}
(\/\/)[^\n\r]* {return COMMENT;}
({DQ})([\x20-\x5B\x5D-\x7E]|(\\\\)|(\\({DQ}))|(\\n)|(\\r)|(\\t)|(\\0)|(\\x([a-fA-F0-9]{2})))*({DQ}) {return STRING;}
({DQ})([\x20-\x5B\x5D-\x7E]|(\\\\)|(\\({DQ}))|(\\n)|(\\r)|(\\t)|(\\0)|(\\x([a-fA-F0-9]{2})))*\\x[^\"] {return UNDEFINED_ESCAPE_SEQ_HEX_1;}
({DQ})([\x20-\x5B\x5D-\x7E]|(\\\\)|(\\({DQ}))|(\\n)|(\\r)|(\\t)|(\\0)|(\\x([a-fA-F0-9]{2})))*\\x[^\"]{2} {return UNDEFINED_ESCAPE_SEQ_HEX_2;}
({DQ})([\x20-\x21\x23-\x5B\x5D-\x7E]|(\\\\)|(\\({DQ}))|(\\n)|(\\r)|(\\t)|(\\0)|(\\x([a-fA-F0-9]{2})))*([\x20-\x21\x23-\x7E]|(\\({DQ}))) {return UNCLOSED_STRING;}
({DQ})([\x20-\x21\x23-\x7E])*\n {return UNCLOSED_STRING;}
({DQ})([\x20-\x5B\x5D-\x7E]|(\\\\)|(\\({DQ}))|(\\n)|(\\r)|(\\t)|(\\0)|(\\x([a-fA-F0-9]{2})))*\\. {return UNDEFINED_ESCAPE_SEQ;}
{WS} {return WS;}
. { return -1; /* ERROR */ }
%%
int yywrap() {return 1;}

