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
(\/\/)[^\n\r\r\n]* {return COMMENT;}
({DQ})([^\"\\\n\r\0]|(\\.))*({DQ}) {return STRING;}
({DQ})([^\"\\\n\r\0]|((\\.)?))*([^({DQ})\n\r\r\n]|(\\({DQ})))? {return UNCLOSED_STRING;}
{WS} {return WS;}
. { return -1; /* ERROR */ }
%%
int yywrap() {return 1;}

