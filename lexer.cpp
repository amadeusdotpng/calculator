#include <cctype>
#include <stdexcept>

#include "token.h"
#include "lexer.h"

bool Lexer::str_isnum(std::string S) {
	for(char c : S) {
		if(!('0' <= c && c <= '9')) return false;
	}
	return true;
}

bool Lexer::str_isop(std::string S) {
	return S == "+"
		|| S == "-"
		|| S == "*"
		|| S == "/"
		|| S == "("
		|| S == ")";
}

bool Lexer::str_iswhitespace(std::string S) {
	for(char c : S) {
		if(!std::isspace(c)) return false;
	}
	return true;
}

std::deque<Token> Lexer::parse(std::string input) {
	int position = 0;
	int lookahead = 1;

	std::deque<Token> tokens;

	TokenKind kind_buffer = ERROR;
	std::string substring_buffer = "";


	while(true) {
		if(position >= input.size()) {
			tokens.push_back(Token {.lexeme = "$", .kind = END});
			break;
		}

		if(lookahead >= input.size()) {
			tokens.push_back(Token {.lexeme = substring_buffer, .kind = kind_buffer});
			tokens.push_back(Token {.lexeme = "$", .kind = END});
			break;
		}
		
		std::string substring = input.substr(position, lookahead);
		TokenKind kind;
		if(str_isnum(substring)) kind = NUM;
		else if(str_isop(substring)) {
			// optimize later
			if     (substring == "+") kind = ADD;
			else if(substring == "-") kind = SUB;
			else if(substring == "*") kind = MUL;
			else if(substring == "/") kind = DIV;
			else if(substring == "(") kind = LPAREN;
			else if(substring == ")") kind = RPAREN;
			else kind = ERROR;
		} else if(str_iswhitespace(substring)) kind = WHITESPACE;
		else kind = ERROR;

		if(kind == ERROR) {
			position += lookahead-1;
			lookahead = 1;
			if(kind_buffer == ERROR) throw std::logic_error(std::string("bad symbol: " + substring));
			else if(kind_buffer == WHITESPACE) { 
				kind_buffer = ERROR;
				substring_buffer = "";
				continue;
			} else {
				tokens.push_back(Token {.lexeme = substring_buffer, .kind = kind_buffer});
				kind_buffer = ERROR;
				substring_buffer = "";
			}
		} else {
			lookahead++;
			kind_buffer = kind;
			substring_buffer = substring;
		}
	}
	return tokens;
}
