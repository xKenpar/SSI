#include "ssi.hpp"


TOKEN::TOKEN(tokenType type, int value)
{
    this->type = type;
    this->value = value;
}

SSI::SSI(std::string text)
{
    this->text = text;
    pos = 0;
    currentChar = text[pos];
    currentToken = getNextToken();
}

void SSI::advance()
{
    pos++;

    if(pos>text.length() - 1)
    {
        currentChar = '\0';
    }
    else
    {
        currentChar = text[pos];
    }
}

void SSI::skipWhitespace()
{
    while(currentChar == ' ')
    {
        advance();
    }
}

int SSI::getInt()
{
    int result = 0;
    while(isdigit(currentChar))
    {
        result *= 10;
        result += toInt(currentChar);
        advance();
    }

    return result;
}

TOKEN SSI::getNextToken()
{

    while(currentChar)
    {
        if(currentChar == ' ')
        {
            skipWhitespace();
            continue;
        }

        if(isdigit(currentChar))
        {
            TOKEN token = TOKEN(INTEGER, getInt());

            return token;
        }

        if(currentChar == '+')
        {
            advance();

            return TOKEN(PLUS, '+');
        }
        else if(currentChar == '-')
        {
            advance();

            return TOKEN(MINUS, '-');
        }
        else if(currentChar == '*')
        {
            advance();

            return TOKEN(MULT, '*');
        }
        else if(currentChar == '/')
        {
            advance();

            return TOKEN(DIV, '/');
        }

        error("Unexpected Char At Index " + std::to_string(pos) + "!\nChar : " + currentChar);
    }

    return TOKEN(EOFILE, 0);
}

void SSI::eat(tokenType eatType)
{
    if(currentToken.type == eatType)
    {
        currentToken = getNextToken();
    }
    else
    {
        error("Unexpected Token Type");
    }
}

int SSI::term()
{
    int result = factor();

    while(currentToken.type == MULT || currentToken.type == DIV)
    {
        TOKEN op = currentToken;

        if(currentToken.type == MULT)
        {
            eat(MULT);

            result = result * factor();
        }
        else if(currentToken.type == DIV)
        {
            eat(DIV);

            result = result / term();
        }
    }

    return result;
}
int SSI::expr()
{   
    int result = term();

    while(currentToken.type == PLUS || currentToken.type == MINUS)
    {
        TOKEN op = currentToken;

        if(currentToken.type == PLUS)
        {
            eat(PLUS);

            result = result + term();
        }
        else if(currentToken.type == MINUS)
        {
            eat(MINUS);

            result = result - term();
        }
    }

    return result;
}

int SSI::factor()
{
    TOKEN token = currentToken;

    eat(INTEGER);

    return token.value;
}

int SSI::toInt(char ch)
{
    return ch - '0';
}

void SSI::error(std::string errText)
{
    throw std::invalid_argument(errText);
}