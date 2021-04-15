#include "tokens.hpp"
#include "string"
#include "iostream"

using namespace std;
extern int yylineno;
extern char* yytext;
extern int yyleng;
//extern int yylex();
//extern int yyget_lineno();
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

void ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}

void CutString(std::string& subject) {
    size_t pos = 0;
    while ((pos = subject.find("\\0", pos)) != std::string::npos) {
        subject = subject.substr(0,pos);
    }
}
void UNDEFINED_ESCAPE_SEQ_HEX(string& text, int token){
    int shift = token == UNDEFINED_ESCAPE_SEQ_HEX_2 ? 3 : 2;
    text = text.substr(text.length()-shift,text.length());
    cout << "Error undefined escape sequence " << text <<endl;
    exit(0);
}

void ReplaceAscii(std::string& subject) {
    size_t pos = 0;
    while ((pos = subject.find("\\x", pos)) != std::string::npos) {
        string nums = subject.substr(pos+2,2);
        unsigned int x = std::stoul(nums, nullptr, 16);
        if(x>=40 && x<=176) {
            string s(1, char(x));
            subject.replace(pos, 4, s);
        }
        else{
            subject = subject.substr(0,pos+4);
            UNDEFINED_ESCAPE_SEQ_HEX(subject, UNDEFINED_ESCAPE_SEQ_HEX_2);
        }
    }
}




int main()
{
    //yyin = fopen("../part1Tests/tests/t4.in", "r");
    yyin = fopen("../part_a_tests/tests/hw1_test138.in", "r");
    int token;
    while((token = yylex())) {
        string text(yytext);
        text.assign(yytext, yyleng);
        if(token == COMMENT){
            text = "//";
        }
        else if(token == STRING){
            text = text.substr(1,yyleng-2);
            ReplaceStringInPlace(text, "\\n", "\n");
            ReplaceStringInPlace(text, "\\r", "\r");
            ReplaceStringInPlace(text, "\\t", "\t");
            ReplaceStringInPlace(text, "\\\\", "\\");
            ReplaceStringInPlace(text, "\\\"", "\"");
            ReplaceStringInPlace(text, "\\x", "\\x");
            CutString(text);
            ReplaceAscii(text);


        }
        else if(token == WS) {
            continue;
        }
        else if(token==UNCLOSED_STRING) {
            cout << "Error unclosed string" << endl;
            exit(0);
        }
        else if(token==UNDEFINED_ESCAPE_SEQ_HEX_1 || token == UNDEFINED_ESCAPE_SEQ_HEX_2){
            UNDEFINED_ESCAPE_SEQ_HEX(text, token);
        }
        else if(token==UNDEFINED_ESCAPE_SEQ){
            cout << "Error undefined escape sequence " << text[text.length()-1] <<endl;
            exit(0);
        }
        else if(token == ERROR){
            cout << "Error " << text << endl;
            exit(0);
        }
        cout << yyget_lineno() << " " << stringifyToken(token) << " "
             << text << endl;
    }
    fclose(yyin);
	return 0;
}
