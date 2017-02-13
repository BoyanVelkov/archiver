#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <vector>
#include <iostream>
#include <string>
using std::cout;
using std::endl;

#include "Treenode.h"
#include "Code.h"

template< typename NODETYPE >
std::ostream& operator<< (std::ostream& out, const Tree<NODETYPE>& tree);

template< typename NODETYPE > class Tree
{
public:

    Tree();

    void insertNode( const NODETYPE & );

    void preOrderTraversal() const;

    void inOrderTraversal() const;

    void postOrderTraversal() const;

    void createRootFromNodes(NODETYPE &valueForLeftChild, NODETYPE &valueForRightChild);

    void createRootFromTrees(Tree< NODETYPE > &leftChild, Tree< NODETYPE > &rightChild);

    void addLeftSubtree(NODETYPE value = 0);
    void addRightSubtree(NODETYPE value = 0);

    bool operator< (Tree tree) const;
    bool operator> (Tree tree) const;

    TreeNode< NODETYPE >* getRootPtr() const;

    void getAllElements(std::vector<Code>* codedChars,std::string);
    void getAllElementsHelper(std::vector<Code>* codedChars, TreeNode< NODETYPE >* ptr,std::string);

    friend std::ostream& operator<< <> (std::ostream& out, const Tree<NODETYPE>& tree);
    void inOrderTraversalAndPrint(std::ostream& out, const Tree<NODETYPE>& tree) const;
    void inOrderPrintHelper(std::ostream& out, TreeNode< NODETYPE > *ptr ) const;

private:
    TreeNode< NODETYPE > *rootPtr;

    void insertNodeHelper( TreeNode< NODETYPE > **, const NODETYPE & );
    void preOrderHelper( TreeNode< NODETYPE > * ) const;
    void inOrderHelper( TreeNode< NODETYPE > * ) const;
    void postOrderHelper( TreeNode< NODETYPE > * ) const;
};

template< typename NODETYPE >
Tree< NODETYPE >::Tree()
{

    rootPtr = 0; // indicate tree is initially empty

}

template< typename NODETYPE >
TreeNode< NODETYPE >* Tree< NODETYPE >::getRootPtr() const
{
    return rootPtr;
}

// insert node in Tree
template< typename NODETYPE >
void Tree< NODETYPE >::insertNode( const NODETYPE &value )
{

    insertNodeHelper( &rootPtr, value );
}

template< typename NODETYPE >
void Tree< NODETYPE >::insertNodeHelper(TreeNode< NODETYPE > **ptr, const NODETYPE &value )
{
    if ( *ptr == 0 )// subtree is empty; create new TreeNode containing value
    {
        *ptr = new TreeNode< NODETYPE >( value );
    }
    else // subtree is not empty
    {
        if ( value < ( *ptr )->data )// data to insert is less than data in current node
        {
            insertNodeHelper( &( ( *ptr )->leftPtr ), value );
        }
        else
        {
            if ( value > ( *ptr )->data )// data to insert is greater than data in current node
            {
                insertNodeHelper( &( ( *ptr )->rightPtr ), value );
            }
            //else duplicate data value ignored
        }

    }
}

template< typename NODETYPE >
void Tree< NODETYPE >::preOrderTraversal() const
{
    preOrderHelper( rootPtr );
}

template< typename NODETYPE >
void Tree< NODETYPE >::preOrderHelper( TreeNode< NODETYPE > *ptr ) const
{
    if ( ptr != 0 )
    {
        cout << ptr->data << ' '; // process node
        preOrderHelper( ptr->leftPtr ); // traverse left subtree
        preOrderHelper( ptr->rightPtr ); // traverse right subtree
    }
}

template< typename NODETYPE >
void Tree< NODETYPE >::inOrderTraversal() const
{
    inOrderHelper( rootPtr );
}

template< typename NODETYPE >
void Tree< NODETYPE >::inOrderHelper( TreeNode< NODETYPE > *ptr ) const
{
    if ( ptr != 0 )
    {
        inOrderHelper( ptr->leftPtr ); // traverse left subtree
        cout << ptr->data << ' '; // process node
        inOrderHelper( ptr->rightPtr ); // traverse right subtree

    }
}

//==============================================================================================================PRINT TREE
template< typename NODETYPE >
std::ostream& operator<< (std::ostream& out, const Tree<NODETYPE>& tree)
{
    tree.inOrderTraversalAndPrint(out, tree);
    return out;
}

// print for test
template< typename NODETYPE >
void Tree< NODETYPE >::inOrderTraversalAndPrint(std::ostream& out, const Tree<NODETYPE>& tree) const
{
    inOrderPrintHelper(out, rootPtr );
}

template< typename NODETYPE >
void Tree< NODETYPE >::inOrderPrintHelper(std::ostream& out, TreeNode< NODETYPE > *ptr) const
{
    if ( ptr != 0 )
    {
        inOrderPrintHelper(out, ptr->leftPtr ); // traverse left subtree
        out << ptr->data.getValue() << ' ' << ptr->data.getSeries() << ' '; // process node

        inOrderPrintHelper(out, ptr->rightPtr ); // traverse right subtree
    }
}
//=================================================================================================================================

template< typename NODETYPE >
void Tree< NODETYPE >::postOrderTraversal() const
{
    postOrderHelper( rootPtr );
}

template< typename NODETYPE >
void Tree< NODETYPE >::postOrderHelper(TreeNode< NODETYPE > *ptr ) const
{
    if ( ptr != 0 )
    {
        postOrderHelper( ptr->leftPtr ); // traverse left subtree
        postOrderHelper( ptr->rightPtr ); // traverse right subtree
        cout << ptr->data << ' '; // process node

    }
}
template< typename NODETYPE >
void Tree< NODETYPE >::createRootFromNodes(NODETYPE &valueForLeftChild, NODETYPE &valueForRightChild)
{
    // create new node with value equal to sum of function arguments
    NODETYPE value = valueForLeftChild + valueForRightChild;
    // use it for first element(root) in new tree
    insertNodeHelper( &rootPtr, value );

    // create two nodes for left and right child of new tree
    TreeNode< NODETYPE > *leftChild = new TreeNode< NODETYPE >( valueForLeftChild );
    TreeNode< NODETYPE > *rightChild = new TreeNode< NODETYPE >( valueForRightChild );
    // set them to root child pointers
    rootPtr->leftPtr = leftChild;
    rootPtr->rightPtr = rightChild;

}

template< typename NODETYPE >
void Tree< NODETYPE >::createRootFromTrees(Tree< NODETYPE > &leftChild, Tree< NODETYPE > &rightChild)
{
    // get data from rood node of trees
    NODETYPE leftChildNode = leftChild.rootPtr->getData();
    NODETYPE rightChildNode = rightChild.rootPtr->getData();

    // create new node with value equal to sum of value of two roots
    NODETYPE value = leftChildNode + rightChildNode;
    // use it for first element(root) in new tree
    insertNodeHelper( &rootPtr, value );

    // set root child pointers to root nodes of trees submitted to arguments
    rootPtr->leftPtr = leftChild.rootPtr;
    rootPtr->rightPtr = rightChild.rootPtr;

}

template< typename NODETYPE >
bool Tree< NODETYPE >::operator< (Tree tree) const
{
    return this->rootPtr->getData() < tree.rootPtr->getData();
}

template< typename NODETYPE >
bool Tree< NODETYPE >::operator> (Tree tree) const
{
    return this->rootPtr->getData() > tree.rootPtr->getData();
}

//===============================================================================================================================================

//make vector from tree
template< typename NODETYPE >
void Tree< NODETYPE >::getAllElements(std::vector<Code>* codedChars,std::string s)
{
   getAllElementsHelper(codedChars, rootPtr,s);
}

template< typename NODETYPE >
void Tree< NODETYPE >::getAllElementsHelper(std::vector<Code>* codedChars, TreeNode< NODETYPE >* ptr, std::string s)
{
    Code tempCode;
    if ( ptr != 0 )
    {
        getAllElementsHelper(codedChars, ptr->leftPtr, s + '0' ); // traverse left subtree

        if(ptr->data.getSeries())
        {
            ///cout << "ptr->data.getSeries(): " << ptr->data.getSeries()<<" ==== mysStr: "<< s << endl;
            tempCode.setChar(ptr->data.getSeries());
            tempCode.setBits(s);
            codedChars->push_back(tempCode);
        }

        getAllElementsHelper(codedChars, ptr->rightPtr, s+'1' ); // traverse right subtree
    }
}



template< typename NODETYPE >
void Tree< NODETYPE >::addLeftSubtree(NODETYPE value)
{
    ///don't use tree root, function must accept pointer to node, and add subtree to it
    /// future...

    if(0 == rootPtr->leftPtr)
    {
        TreeNode< NODETYPE > *leftChild = new TreeNode< NODETYPE >( value );
        rootPtr->leftPtr = leftChild;
    }
}

template< typename NODETYPE >
void Tree< NODETYPE >::addRightSubtree(NODETYPE value)
{
    if(0 == rootPtr->rightPtr)
    {
        TreeNode< NODETYPE > *rightChild = new TreeNode< NODETYPE >( value );
        rootPtr->rightPtr = rightChild;
    }
}

#endif // TREE_H_INCLUDED
