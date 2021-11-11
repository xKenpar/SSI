#include "bits/stdc++.h"

enum tokenType {INTEGER, PLUS, MINUS, MULT, DIV, LPAREN, RPAREN, EOFILE};

class TOKEN
{
    public:
        tokenType type;
        int value;

        TOKEN(){};
        TOKEN(tokenType type, int value);
};

class SSI
{
    private:
        std::string text;
        char currentChar;
        unsigned int pos;
        TOKEN currentToken;

        void error(std::string errText);
        void advance();
        void skipWhitespace();
        void eat(tokenType eatType);
        TOKEN getNextToken();
        int getInt();
        int toInt(char ch);
        int term();
        int factor();

    public:
        SSI(std::string newText);
        int expr();
};