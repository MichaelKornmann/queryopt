#ifndef NODELEXER_HH
#define NODELEXER_HH

#include <iostream>
#include <string>
#include <cstring>

class NodeLexer{

    public:
        NodeLexer(std::istream& ais);
        ~NodeLexer(){}
    public:
        enum token_et {kInitial_t, kLparen_t, kRparen_t, kDouble_t, kInt_t, kIdentifier_t, kInvalid_t};
    public:
        void nextToken();
    public:    
        struct token_t {
            token_et _token;
            std::string _string;
            token_t() : _token(kInitial_t){}

        } _res;
          

	private:			
        std::istream& _is; 
    private:
        bool skipWhiteSpace();
		inline bool advance();
		inline bool getNextCharImmediate(unsigned char& c);
        inline void rollback(unsigned char& c){_is.putback(c);}
        void readIdentifier();
		void readNumber();
        inline bool isDot(const unsigned char& c){return c == '.';}
        inline bool isHyphen(const unsigned char& c){return c == '-';}
        inline bool isSpace(const unsigned char& c){return c == ' ';}
        inline bool isLparen(const unsigned char& c){return c == '(';}
        inline bool isRparen(const unsigned char& c){return c == ')';}
        inline bool followedByDigit(){return isdigit(_is.peek());}
        inline bool followedByAlpha(){return isalpha(_is.peek());}
		inline bool followedByAscii(){return isascii(_is.peek());}
        inline bool followedBy(char c){return _is.peek() == c;}
};

NodeLexer::NodeLexer(std::istream& ais) : _is(ais)
{

}

void
NodeLexer::nextToken()
{
    _res._string = ""; //flush
	if(!followedByAscii())
	{
		_res._token = kInvalid_t;
		return;
	}
	if(followedBy(' '))
	{
		skipWhiteSpace();
	}
    //lparen
    if(followedBy('('))
    {
        _res._token = kLparen_t;
		advance();
        return;
    }
    //rparen
    if(followedBy(')'))
    {
        _res._token = kRparen_t;
		advance();
        return;
    }
    //identifier
    if(followedByAlpha())
    {
        readIdentifier();
        return;
    }
    // number
    if(followedByDigit())
    {
		readNumber();
    }
    
}

void 
NodeLexer::readNumber()
{
	_res._token = kInt_t;
	unsigned char c;
    while(getNextCharImmediate(c))
	{
		if(followedBy('(') || followedBy(')') || followedBy(' '))
		{
			break;
		}
		if(isdigit(c))
        {
			_res._string+=c;
        }
        else
        if(isDot(c))
        {
            _res._string+=c;
            if(_res._token == kInt_t && followedByDigit())
			{
                _res._token = kDouble_t;
            }
            else
            {
                _res._token = kInvalid_t;
				return;
            }
        }
            
	}
}

void
NodeLexer::readIdentifier()
{
	unsigned char c;
    _res._token = kIdentifier_t;
    while(getNextCharImmediate(c))
    {
        if(followedBy('(') || followedBy(')') || followedBy(' '))
		{
			break;
		}
		if(isalpha(c)||isdigit(c)||isHyphen(c))
        {
            _res._string+=c;
        }
        //else
        //if(isLparen(c)||isRparen(c)||isSpace(c))
        //{
            //rollback(c);
            //break;                
        //}

    }
}


bool
NodeLexer::skipWhiteSpace()
{
    unsigned char c;
	do
	{
		if(advance())
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	while(followedBy(' '));
}

bool
inline NodeLexer::getNextCharImmediate(unsigned char& c)
{
	if(followedByAscii())
	{
		c = _is.get();
		return true;
	}
	else
	{
		return false;
	}
}

bool 
inline NodeLexer::advance()
{
	if(followedByAscii())
	{
		_is.get();
		return true;
	}
	else
	{
		return false;
	}
}

#endif
