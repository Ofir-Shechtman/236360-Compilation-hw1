%{
#include <math.h>
int line_number = 1;
%}
WS [ \t]
LETTER [a-zA-Z]
DIGIT [0-9]
ID {LETTER}({LETTER}|{DIGIT})*
%%
{DIGIT}+ { printf("number: %d\n", atoi(yytext)); return 1; }
{ID} { return 2;}
{WS} { /* ignore */ }
\n { line_number++; /* and ignore */ }
. { return -1; /* ERROR */ }
%%
int main() { return yylex(); }
