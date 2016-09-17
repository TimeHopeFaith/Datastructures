/**************************************************************
* File: SplayTree.h
* Author: James Guan
* Homework: CMSC 341 Project3, Fall 2014
* Version Date: 11/4/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
* This is the SplayTree.h file that has all the functions of a splay tree
// SplayTree class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted
// ******************ADDED*********************************
// int size ( ) 	     --> Return the number of Nodes contained
// Comparable getRoot( )  --> Returns the root of the SplayTree
// int getSplayCount ( )  --> Returns the number of Splays that took place with the tree
// 
// Note: I also added a new variable called splayCount to make counting the splays easier
*************************************************************/
#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "dsexceptions.h"
#include <iostream>        // For NULL
using namespace std;

template <typename Comparable>
class SplayTree
{
  public:
    /**
     * Default constructor.
     */
    SplayTree( )
    {
	 splayCount = 0;
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
    }//end Constructor

    /**
     * Copy constructor for SplayTree with splayCount copy ability as well
     */
    SplayTree( const SplayTree & rhs )
    {
	 splayCount = rhs.getSplayCount();
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
        *this = rhs;
    }// end Constructor

    /**
     * Destructor for the splay tree
     */
    ~SplayTree( )
    {
        makeEmpty( );
        delete nullNode;
    }// end Destructor

    /**
     * Find the smallest item in the tree.
     * Not the most efficient implementation (uses two passes), but has correct
     *     amortized behavior.
     * A good alternative is to first call find with parameter
     *     smaller than any item in the tree, then call findMin.
     * Return the smallest item or throw UnderflowException if empty.
     */
    const Comparable & findMin( )
    {
        if( isEmpty( ) )
            throw UnderflowException( );

        BinaryNode *ptr = root;

        while( ptr->left != nullNode )
            ptr = ptr->left;

        splay( ptr->element, root );
        return ptr->element;
    }

    /**
     * Find the largest item in the tree.
     * Not the most efficient implementation (uses two passes), but has correct
     *     amortized behavior.
     * A good alternative is to first call find with parameter
     *     larger than any item in the tree, then call findMax.
     * Return the largest item or throw UnderflowException if empty.
     */
    const Comparable & findMax( )
    {
        if( isEmpty( ) )
            throw UnderflowException( );

        BinaryNode *ptr = root;

        while( ptr->right != nullNode )
            ptr = ptr->right;

        splay( ptr->element, root );
        return ptr->element;
    }

    /**
     * Searches for a Node equivalent to the passed in Node.	
     */	
    bool contains( const Comparable & x )
    {
        if( isEmpty( ) )
            return false;
        splay( x, root );
        return root->element == x;
    }

    /**
     *	Returns the root.
     * Throws an UnderflowException if the tree is empty. 
     */ 
    Comparable & getRoot( )
    {
        if( isEmpty( ) )
            throw UnderflowException( );

        return root->element;
    }// end getRoot

    /** 
     * Checks if the Splay tree is empty and returns a boolean
     */
    bool isEmpty( ) const
    {
        return root == nullNode;
    }// end isEmpty

    /**
     * This will call a recursive print tree function and it will print 
     * the tree in infix order.
     */ 
    void printTree( ) const
    {
        if( isEmpty( ) ){
            cout << "Empty tree" << endl;
	}
        else
            printTree( root );
    }// end printTree

    /**
     * Added Function!
     * This will call a recursive size ( root ) function that will count 
     * every time there is a Node present in the tree and return that number
     */ 
    int size( ) const
    {
	if ( isEmpty( ) ){
		return 0;
	}// end if
	return size( root );
    }// end size

    /**
     * Added Function! 
     * This will return the number of splays that took place
     * with this splay tree!
     */
    int getSplayCount() const
    {
	return splayCount;
    }// end getSplayCount

    void makeEmpty( )
    {
    /******************************
     * Comment this out, because it is prone to excessive
     * recursion on degenerate trees. Use alternate algorithm.
        
        reclaimMemory( root );
        root = nullNode;
     *******************************/
        while( !isEmpty( ) )
        {
            findMax( );        // Splay max item to root
            remove( root->element );
        }
    }
    
    /**
     * insert will insert the Node and it was splay to do so
     */
    void insert( const Comparable & x )
    {
        static BinaryNode *newNode = NULL;

        if( newNode == NULL )
            newNode = new BinaryNode;
        newNode->element = x;

        if( root == nullNode )
        {
            newNode->left = newNode->right = nullNode;
            root = newNode;
        }
        else
        {
            splay( x, root );
            if( x < root->element )
            {
                newNode->left = root->left;
                newNode->right = root;
                root->left = nullNode;
                root = newNode;
            }
            else
            if( root->element < x )
            {
                newNode->right = root->right;
                newNode->left = root;
                root->right = nullNode;
                root = newNode;
            }
            else
                return;
        }
        newNode = NULL;   // So next insert will call new
    }

    /**
     * Self-explanatory but it removes items from the Tree.
     */
    void remove( const Comparable & x )
    {
        BinaryNode *newTree;

            // If x is found, it will be at the root
        if( !contains( x ) )
            return;   // Item not found; do nothing

        if( root->left == nullNode )
            newTree = root->right;
        else
        {
            // Find the maximum in the left subtree
            // Splay it to the root; and then attach right child
            newTree = root->left;
            splay( x, newTree );
            newTree->right = root->right;
        }
        delete root;
        root = newTree;
    }

    /**
     * I don't know what this does. This is Lupoli's code so... I guess it's a clone method?
     */
    const SplayTree & operator=( const SplayTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }

        return *this;
    }

private:
    /////////////////////////
    /////    Struct    //////
    /////////////////////////
    struct BinaryNode
    {
        Comparable  element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( ) : left( NULL ), right( NULL ) { }
        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
            : element( theElement ), left( lt ), right( rt ) { }
    };
  
    ////////////////////////////
    // Pointers and variables //
    ////////////////////////////
    int splayCount; // This will hold the number of splays that occurred
    BinaryNode *root;
    BinaryNode *nullNode;

    /**
     * Internal method to reclaim internal nodes in subtree t.
     * WARNING: This is prone to running out of stack space.
     */
    void reclaimMemory( BinaryNode * t )
    {
        if( t != t->left )
        {
            reclaimMemory( t->left );
            reclaimMemory( t->right );
            delete t;
        }
    }
    
    /**
     * Internal method to print a subtree t in sorted order.
     * WARNING: This is prone to running out of stack space.
     */
   void printTree( BinaryNode *t ) const
    {
        if( t != t->left )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

   /**
    * size function that recursively calls itself to 
    * count the number of BinaryNodes in the tree 
    */
   int size( BinaryNode *t ) const 
   {
	if (t != t->left){

		if(t == NULL) { //This node doesn't exist. Therefore there are no nodes in this tree
			return 0;
    		}// end if
		else { //Add the size of the left and right trees, then add 1 (which is the current node)
        		return size( t->left ) + size(t->right) + 1;
    		}// end else
	}// end if
	return 0;
   }// end size

    /**
     * Internal method to clone subtree.
     * WARNING: This is prone to running out of stack space.
     */
    BinaryNode * clone( BinaryNode * t ) const
    {
        if( t == t->left )  // Cannot test against nullNode!!!
            return nullNode;
        else
            return new BinaryNode( t->element, clone( t->left ), clone( t->right ) );
    }

        // Tree manipulations
    void rotateWithLeftChild( BinaryNode * & k2 )
    {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
    }

    void rotateWithRightChild( BinaryNode * & k1 )
    {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
    }

    /**
     * Internal method to perform a top-down splay.
     * The last accessed node becomes the new root.
     * This method may be overridden to use a different
     * splaying algorithm, however, the splay tree code
     * depends on the accessed item going to the root.
     * x is the target item to splay around.
     * t is the root of the subtree to splay.
     */
    void splay( const Comparable & x, BinaryNode * & t )
    {
	 splayCount = splayCount + 1;
        BinaryNode *leftTreeMax, *rightTreeMin;
        static BinaryNode header;

        header.left = header.right = nullNode;
        leftTreeMax = rightTreeMin = &header;

        nullNode->element = x;   // Guarantee a match

        for( ; ; )
            if( x < t->element )
            {
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                if( t->left == nullNode )
                    break;
                // Link Right
                rightTreeMin->left = t;
                rightTreeMin = t;
                t = t->left;
            }
            else if( t->element < x )
            {
                if( t->right->element < x )
                    rotateWithRightChild( t );
                if( t->right == nullNode )
                    break;
                // Link Left
                leftTreeMax->right = t;
                leftTreeMax = t;
                t = t->right;
            }
            else
                break;

        leftTreeMax->right = t->left;
        rightTreeMin->left = t->right;
        t->left = header.right;
        t->right = header.left;
    }
};

#endif