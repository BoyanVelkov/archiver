#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <iostream>
#include "Listnode.h"

using std::cout;


template<typename NODETYPE>
class List
{
public:

    List();

    ~List();

    void insertAtBack( const NODETYPE & );

    bool removeFromBack( NODETYPE & );

    bool isEmpty() const;

    void print() const;

    ListNode< NODETYPE >* getIterator();

    unsigned int getListSize() const;

    void removeByNumber(unsigned int number);

    void renumber(ListNode< NODETYPE >* nodeToStart);

    void sortList();

private:

    ListNode< NODETYPE > *firstPtr;

    ListNode< NODETYPE > *lastPtr;

    ListNode< NODETYPE > *getNewNode( const NODETYPE & );

    unsigned int listSize;
};

template< typename NODETYPE >
List< NODETYPE >::List()
    : firstPtr( 0 ), lastPtr( 0 ), listSize ( 0 ) {};


template< typename NODETYPE >
List< NODETYPE >::~List()
{
    if ( !isEmpty() )
    {
        ListNode< NODETYPE > *currentPtr = firstPtr;
        ListNode< NODETYPE > *tempPtr;
        while ( currentPtr != 0 )
        {
            tempPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
            delete tempPtr;
        }
    }
}

template< typename NODETYPE >
void List< NODETYPE >::insertAtBack( const NODETYPE &value )
{
    ListNode< NODETYPE > *newPtr = getNewNode( value );

    if ( isEmpty() )
    {
        firstPtr = lastPtr = newPtr;
    }
    else
    {
        lastPtr->nextPtr = newPtr;
        newPtr->prevPtr = lastPtr;
        newPtr->number = lastPtr->number + 1;
        lastPtr = newPtr;
    }
    listSize++;
}

template< typename NODETYPE >
bool List< NODETYPE >::removeFromBack( NODETYPE &value )
{
    if ( isEmpty() )
    {
        return false;
    }
    else
    {
        ListNode< NODETYPE > *tempPtr = lastPtr;
        if ( firstPtr == lastPtr )
        {
            firstPtr = lastPtr = 0;
            value = tempPtr->data;
        }
        else
        {
            ListNode< NODETYPE > *currentPtr = firstPtr;

            while ( currentPtr->nextPtr != lastPtr )
            {
                currentPtr = currentPtr->nextPtr;
            }
            lastPtr = currentPtr;
            lastPtr->prevPtr = currentPtr->prevPtr;
            value = tempPtr->data;
            currentPtr->nextPtr = 0;
        }
    }
    listSize--;
    return true;
}

template< typename NODETYPE >
bool List< NODETYPE >::isEmpty() const
{
    return firstPtr == 0;
}

template< typename NODETYPE >
ListNode< NODETYPE > *List< NODETYPE >::getNewNode(const NODETYPE &value )
{
    return new ListNode< NODETYPE >( value );
}

template< typename NODETYPE >
void List< NODETYPE >::print() const
{
    if ( isEmpty() )
    {
        cout << "The list is empty\n\n";
        return;
    }

    ListNode< NODETYPE > *currentPtr = firstPtr;
    cout << "The list is: ";
    while ( currentPtr != 0 )
    {
        cout << currentPtr->data << ' ' << currentPtr->number << '\n';
        currentPtr = currentPtr->nextPtr;
    }
    cout << "\n\n";
}

template< typename NODETYPE >
unsigned int List< NODETYPE >::getListSize() const
{
    return this->listSize;
}
template< typename NODETYPE >
ListNode< NODETYPE >* List< NODETYPE >::getIterator()
{
    return firstPtr;
}

template< typename NODETYPE >
void List< NODETYPE >::removeByNumber(unsigned int number)
{
    ListNode< NODETYPE > *currentPtr = firstPtr;
    ListNode< NODETYPE > *tempFirstPtr = firstPtr;
    ListNode< NODETYPE > *tempLastPtr = lastPtr;

    if ( firstPtr == lastPtr )
    {
        firstPtr = lastPtr = 0;
    }

    while ( currentPtr != 0 )
    {
        if(currentPtr->number == number)
        {
            if(currentPtr != tempFirstPtr)
            {
                currentPtr->prevPtr->nextPtr = currentPtr->nextPtr;
            }
            else
            {
                firstPtr = currentPtr->nextPtr;
            }
            if (currentPtr != tempLastPtr)
            {
                currentPtr->nextPtr->prevPtr = currentPtr->prevPtr;
            }
            else
            {
                lastPtr = currentPtr->prevPtr;
            }

            renumber(currentPtr->nextPtr);

            delete currentPtr;
            listSize--;
            break;
        }
        currentPtr = currentPtr->nextPtr;
    }

}

template< typename NODETYPE >
void List< NODETYPE >::renumber(ListNode< NODETYPE >* nodeToStart)
{

    while(nodeToStart != 0)
    {

        nodeToStart->number = nodeToStart->number - 1;
        nodeToStart = nodeToStart->nextPtr;
    }
}

//descending 4 3 2 1
template< typename NODETYPE >
void List< NODETYPE >::sortList()
{
    if ( isEmpty() )
    {
        cout << "The list is empty\n\n";
        return;
    }

    ListNode< NODETYPE >* currentPtr = firstPtr;

    while(currentPtr->nextPtr != 0)
    {
        ListNode< NODETYPE >* currentNextPtr = currentPtr->nextPtr;

        while(currentNextPtr != 0)
        {
            if (currentPtr->getData() < currentNextPtr->getData() )
            {
                NODETYPE temp = currentNextPtr->getData();
                currentNextPtr->setData(currentPtr->getData() );
                currentPtr->setData(temp);
            }
            currentNextPtr = currentNextPtr->nextPtr;
        }
        currentPtr = currentPtr->nextPtr;
    }
}
#endif // LIST_H_INCLUDED
