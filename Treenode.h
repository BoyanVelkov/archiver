#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

// forward declaration of class Tree
template< typename NODETYPE > class Tree;

// TreeNode class-template definition
template< typename NODETYPE >
class TreeNode
{
    friend class Tree< NODETYPE >;

public:


    TreeNode( const NODETYPE &d )
        : leftPtr( 0 ), // pointer to left subtree
          data( d ), // tree node data
          rightPtr( 0 ) // pointer to right substree
    {


    }
    NODETYPE getData() const
    {
        return data;
    }
    NODETYPE* getDataPointer()
    {
        return &data;
    }

private:

    TreeNode< NODETYPE > *leftPtr; // pointer to left subtree
    NODETYPE data;
    TreeNode< NODETYPE > *rightPtr; // pointer to right subtree
};

#endif // TREENODE_H_INCLUDED
