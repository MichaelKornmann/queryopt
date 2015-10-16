#ifndef NODEPARSER_HH
#define NODEPARSER_HH

#include "NodeLexer.hh"

class NodeParser{

	public:
		NodeParser(NodeLexer& lexer);
		~NodeParser(){}
	public:
		void node();
	private:
		NodeLexer& _nLexer;		
	private:
		inline bool accept(const NodeLexer::token_et token);
};

NodeParser::NodeParser(NodeLexer& lexer) : _nLexer(lexer)
{

} 

bool
NodeParser::accept(const NodeLexer::token_et token)
{
	//_nLexer.nextToken();
	if(_nLexer._res._token == token)
	{
		_nLexer.nextToken();
		return true;
	}
	else
	{
		return false;
	}
}

void
NodeParser::node()
{
	// ( ID ID_LEFT ID_RIGHT )
	// ( 1 2 3 )
    // ( 1 ( 2 3 4 ) 5)
	// cost, selectivity, cardinality 
	// join hat selektivitaet
	// 'join' einlesen
	// schemadatei, tpc-h

	if(accept(NodeLexer::kInitial_t))
	{
		if(accept(NodeLexer::kLparen_t))
		{
			std::cout << "(" << std::endl;
		}
	}
	
	if(accept(NodeLexer::kInt_t))
	{
		std::cout << "int" << std::endl;
	}

	if(accept(NodeLexer::kInt_t))
	{
		std::cout << "int" << std::endl;
	}
	else
	if(accept(NodeLexer::kLparen_t))
	{
		std::cout << "(" << std::endl;
		node();
	}

	if(accept(NodeLexer::kInt_t))
	{
		std::cout << "int" << std::endl;
	}

	if(accept(NodeLexer::kRparen_t))
	{
		std::cout << ")" << std::endl;
	}
}

#endif
