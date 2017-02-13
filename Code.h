#ifndef CODE_H
#define CODE_H

#include<ostream>

class Code
{
    public:
        Code();
        virtual ~Code();

        void setChar(char newChar);
        void setBits(std::string newCode);

        char getChar() const;
        std::string getBits() const;

        friend std::ostream& operator<< (std::ostream& out, const Code& data);

    private:
        char codedChar;
        std::string codeBits;

};

#endif // CODE_H
