#include <string>
#include <deque>
#include <stdexcept>

#include "lexer.h"
#include "token.h"
#include "parser.h"

BindingPower Parser::infix_bp(TokenKind op) {
	switch(op) {
		case ADD: 
		case SUB: return BindingPower {.l_bp = 1, .r_bp = 2, .some = true};
		case MUL: 
		case DIV: return BindingPower {.l_bp = 3, .r_bp = 4, .some = true};
		default:
			return BindingPower {.l_bp = 0, .r_bp = 0, .some = false};
	}
}

BindingPower Parser::prefix_bp(TokenKind op) {
	switch(op) {
		case ADD: 
		case SUB: return BindingPower {.l_bp = 0, .r_bp = 5, .some = true};
		default:
			throw std::logic_error(std::string("bad prefix operator"));
	}
}

bool Parser::is_op(TokenKind op) {
	return ADD <= op && op <= RPAREN;
}

double Parser::pratt(std::deque<Token> &tokens, unsigned int min_bp) {
	double lhs;
	Token tok_lhs = tokens.front();
	tokens.pop_front();
	if(is_op(tok_lhs.kind)) {
		switch(tok_lhs.kind) {
			case LPAREN:
				lhs = pratt(tokens, 0);
				if(tokens.front().kind != RPAREN) throw std::logic_error(std::string("unbalanced parentheses"));
				tokens.pop_front();
				break;
			case ADD:
				lhs = pratt(tokens, prefix_bp(tok_lhs.kind).r_bp);
				break;
			case SUB:
				lhs = -1*pratt(tokens, prefix_bp(tok_lhs.kind).r_bp);
				break;
			default:
				throw std::logic_error(std::string("bad prefix operator"));
		}
	} else {
		lhs = std::stod(tok_lhs.lexeme);
	}

	while(true) {
		Token op = tokens.front();
		if(!is_op(op.kind)) {
			if(op.kind == END) break;
			throw std::logic_error(std::string("operand found instead of operator"));
		}

		BindingPower bp = infix_bp(op.kind);
		if(bp.some) {
			if(bp.l_bp < min_bp) break;

			tokens.pop_front();

			double rhs = pratt(tokens, bp.r_bp);
			switch(op.kind) {
				case ADD: lhs = lhs + rhs; break;
				case SUB: lhs = lhs - rhs; break;
				case MUL: lhs = lhs * rhs; break;
				case DIV: lhs = lhs / rhs; break;
				default:
					throw std::logic_error(std::string("bad infix operator"));
			}
			continue;
		}
		break;
	}
	return lhs;
}

double Parser::parse(std::string input) {
	std::deque<Token> tokens = Lexer::parse(input);
	return pratt(tokens, 0);
}
