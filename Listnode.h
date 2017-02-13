#ifndef LISTNODE_H_INCLUDED
#define LISTNODE_H_INCLUDED

template< typename NODETYPE > class List;

template< typename NODETYPE>
class ListNode
{

    friend class List< NODETYPE >;

public:

    ListNode( const NODETYPE & );

    NODETYPE getData();
    NODETYPE* getDataPointer();
    void setData(NODETYPE newData);
    ListNode< NODETYPE >* getNextPtr ();

    void setNumber(unsigned int number);
    unsigned int getNumber();
private:

    NODETYPE data;
    ListNode< NODETYPE > *nextPtr;
    ListNode< NODETYPE > *prevPtr;
    unsigned int number;
};

template< typename NODETYPE>
ListNode< NODETYPE >::ListNode( const NODETYPE &info )
    : data( info ), nextPtr( 0 ) {}


template< typename NODETYPE >
NODETYPE* ListNode< NODETYPE >::getDataPointer()
{
    return &data;
}

template< typename NODETYPE >
NODETYPE ListNode< NODETYPE >::getData()
{
    return data;
}

template< typename NODETYPE >
ListNode< NODETYPE >* ListNode< NODETYPE >::getNextPtr ()
{
    return nextPtr;
}

template< typename NODETYPE >
void ListNode< NODETYPE >::setNumber(unsigned int number)
{
    this->number = number;
}

template< typename NODETYPE >
unsigned int ListNode< NODETYPE >::getNumber()
{
    return this->number;
}

template< typename NODETYPE >
void ListNode< NODETYPE >::setData(NODETYPE newData)
{
    this->data = newData;
}

#endif // LISTNODE_H_INCLUDED
