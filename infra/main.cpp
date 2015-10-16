#include "NodeLexer.hh"
#include "NodeParser.hh"
#include <fstream>
#include <stdlib.h>

void parsertest()
{
    std::ifstream* ifs = new std::ifstream("Node_1.txt", std::ifstream::in);
    NodeLexer* lexer = new NodeLexer(*ifs);

	NodeParser* parser = new NodeParser(*lexer);
	parser->node();     
}

void lexertest()
{
    std::ifstream* ifs = new std::ifstream("test.txt", std::ifstream::in);
    NodeLexer* lexer = new NodeLexer(*ifs);
    
    lexer->nextToken();
    
    if(lexer->_res._token == NodeLexer::kLparen_t)
        std::cout << "yes" << std::endl;
    
    lexer->nextToken();
    
    if(lexer->_res._token == NodeLexer::kInt_t)
        std::cout << lexer->_res._string << std::endl;

    lexer->nextToken();

    if(lexer->_res._token == NodeLexer::kDouble_t)
         std::cout << lexer->_res._string << std::endl;

    lexer->nextToken();

    if(lexer->_res._token == NodeLexer::kIdentifier_t)
        std::cout << lexer->_res._string << std::endl;

    lexer->nextToken();

    if(lexer->_res._token == NodeLexer::kInt_t)
        std::cout << lexer->_res._string << std::endl;

    lexer->nextToken();

    if(lexer->_res._token == NodeLexer::kRparen_t)
        std::cout << "yes" << std::endl;


}

int main()
{
    parsertest();
	lexertest();
}
