#ifndef PARSER_H
#define PARSER_H

#include <deque>
#include <string>

#include "token.h"

struct BindingPower {
	unsigned int l_bp;
	unsigned int r_bp;
	bool some;
};

class Parser {
	static BindingPower infix_bp(TokenKind op);
	static BindingPower prefix_bp(TokenKind op);
	static bool is_op(TokenKind op);
	static double pratt(std::deque<Token> &tokens, unsigned int min_bp);

public:
	static double parse(std::string input);
};

#endif
