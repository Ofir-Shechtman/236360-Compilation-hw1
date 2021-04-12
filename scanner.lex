%{
#include "tokens.hpp"
%}
SPACE [ ]
TAB [\t]
CR [\r]
LF [\n]
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
{WS} {return WS;}
(\/\/)[^\n\r]* {return COMMENT;}
\"[^\"\n\\\r]*\" {return STRING;}
. { return -1; /* ERROR */ }
%%
int yywrap() {return 1;}

