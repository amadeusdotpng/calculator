#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenKind {
	WHITESPACE,
	END,
	ERROR,
	NUM,
	ADD,
	SUB,
	MUL,
	DIV,
	LPAREN,
	RPAREN,
};

struct Token {
	std::string lexeme;
	TokenKind kind;
};

#endif
