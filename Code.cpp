#include "Code.h"

Code::Code()
{

}

Code::~Code()
{

}

void Code::setChar(char newChar)
{
    this->codedChar = newChar;
}

void Code::setBits(std::string newCode)
{
    this->codeBits = newCode;
}

char Code::getChar() const
{
    return this->codedChar;
}

std::string Code::getBits() const
{
    return this->codeBits;
}

std::ostream& operator<< (std::ostream& out, const Code& data)
{
    out << data.getChar() << ' ' << data.getBits();
    return out;
}
