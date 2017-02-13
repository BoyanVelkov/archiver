#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "List.h"

template< typename VECTORTYPE >
class Vector : public List < VECTORTYPE >
{
public:
    void push( const VECTORTYPE &data )
    {
        this->insertAtBack( data );
    }

    bool pop( VECTORTYPE &value )
    {
        return this->removeFromBack(value);
    }

    bool isVectorEmpty() const
    {
        return this->isEmpty();
    }

    void printVector() const
    {
        this->print();
    }

    void removeElementNumber(unsigned int number)
    {
        this->removeByNumber(number);
    }

    ListNode< VECTORTYPE >* getIteratorVector()
    {
        return this->getIterator();
    }

    unsigned int getVectorSize()
    {
        return this->getListSize();
    }

    void sortVector()
    {
        this->sortList();
    }

};

#endif // VECTOR_H_INCLUDED
