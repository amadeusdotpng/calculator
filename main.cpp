#include <exception>
#include <iostream>
#include <string>
#include "parser.h"

int main() {
	std::string expression;
	std::cout << "Enter an expression > ";
	std::getline(std::cin, expression);

	try {
		double out = Parser::parse(expression);
		std::cout << expression + " = " << out << std::endl;
	} catch(std::exception e){
		std::cout << e.what();
	}
    return 0;
}
