main: main.cpp parser.cpp lexer.cpp 
	clang++ lexer.cpp parser.cpp main.cpp -o main
