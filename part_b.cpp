#include "tokens.hpp"
#include "iostream"
#include "stack"

using namespace std;
//extern int yylex();
extern char* yytext;
extern FILE *yyin;
extern int yylex();



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
    stack<int> bracket_history;
	int token;
	while((token = yylex())) {
        if(token == ERROR){
            cout << "Error " << yytext << endl;
            exit(0);
        }
        else if(token == WS) {
            continue;
        }
        else if(token != LPAREN && token != RPAREN && token != LBRACE && token != RBRACE){
            cout << "Error: " << stringifyToken(token) << endl;
            exit(0);
        }
        else if(token == LPAREN || token == LBRACE){
            bracket_history.push(token);
            for(int i = 0; i < int(bracket_history.size())-1; i++)
                cout << "\t";
            cout << yytext << endl;
        }
        else if(token == RPAREN || token == RBRACE){
            if((token == RPAREN && (bracket_history.empty() || bracket_history.top() != LPAREN)) ||
                (token == RBRACE && (bracket_history.empty() || bracket_history.top() != LBRACE))){
                cout << "Error: Bad Expression" << endl;
                exit(0);
            }
            for(int i = 0; i < int(bracket_history.size())-1; i++)
                cout << "\t";
            cout << yytext << endl;
            bracket_history.pop();
        }
	}
	if(!bracket_history.empty()){
        cout << "Error: Bad Expression" << endl;
        exit(0);
	}
	return 0;
}
