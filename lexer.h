#ifndef LEXER_H
#define LEXER_H


#include <string>
#include <deque>
#include "token.h"

class Lexer {
	static bool str_isnum(std::string S);
	static bool str_isop(std::string S);
	static bool str_iswhitespace(std::string S);

public:
	static std::deque<Token> parse(std::string input);
};

#endif
