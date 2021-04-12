#include "tokens.hpp"
#include "string"
#include "iostream"

using namespace std;
extern int yylineno;
extern char* yytext;
extern int yyleng;
//extern int yylex();
extern FILE *yyin;

extern "C" {
int yylex();
int yyget_lineno();
};

string stringifyToken(int token){
    switch(token) {
        case VOID : return "VOID";
        case INT : return "INT";
        case BYTE : return "BYTE";
        case B : return "B";
        case BOOL : return "BOOL";
        case AND : return "AND";
        case OR : return "OR";
        case NOT : return "NOT";
        case TRUE : return "TRUE";
        case FALSE : return "FALSE";
        case RETURN : return "RETURN";
        case IF : return "IF";
        case ELSE : return "ELSE";
        case WHILE : return "WHILE";
        case BREAK : return "BREAK";
        case CONTINUE : return "CONTINUE";
        case SWITCH : return "SWITCH";
        case CASE : return "CASE";
        case DEFAULT : return "DEFAULT";
        case COLON : return "COLON";
        case SC : return "SC";
        case COMMA : return "COMMA";
        case LPAREN : return "LPAREN";
        case RPAREN : return "RPAREN";
        case LBRACE : return "LBRACE";
        case RBRACE : return "RBRACE";
        case ASSIGN : return "ASSIGN";
        case RELOP : return "RELOP";
        case BINOP : return "BINOP";
        case COMMENT : return "COMMENT";
        case ID : return "ID";
        case NUM : return "NUM";
        case STRING : return "STRING";
    }
}

int main()
{
    yyin = fopen("../hw1-tests/ta2.in", "r");
    int token;
    string text;
    while((token = yylex())) {
        text.assign(yytext, yyleng);
        if(token == COMMENT){
            text = "//";
        }
        else if(token == STRING){
            text = text.substr(1,yyleng-2);
        }
        else if(token == WS) {
            continue;
        }
        cout << yyget_lineno() << " " << stringifyToken(token) << " "
             << text << endl;
    }
    fclose(yyin);
	return 0;
}
