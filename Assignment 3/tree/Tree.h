// Fig. 19.22: Tree.h
// Template Tree class definition.
#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include <iostream>

using namespace std;

// Tree class-template definition
template <typename NODETYPE>
class Tree
{
public:
    // constructor
    Tree() : rootPtr(nullptr)
    { /* empty body */
    }

    // insert node in Tree
    void insertNode(const NODETYPE &value)
    {
        insertNodeHelper(&rootPtr, value);
    } // end function insertNode

    // begin preorder traversal of Tree
    void preOrderTraversal() const
    {
        preOrderHelper(rootPtr);
    } // end function preOrderTraversal

    // begin inorder traversal of Tree
    void inOrderTraversal() const
    {
        inOrderHelper(rootPtr);
    } // end function inOrderTraversal

    // begin postorder traversal of Tree
    void postOrderTraversal() const
    {
        postOrderHelper(rootPtr);
    } // end function postOrderTraversal

    // Member function of Tree that searches the (binary search) tree for a key value.
    // @param key The key value that should be found.
    // @returns the pointer that points to the substructure of the tree that contains the key value.
    TreeNode<NODETYPE> *search(NODETYPE key)
    {
        return searchHelper(key, rootPtr);
    } // end function search

    // Member function of tree that displays the structure of the (binary search) tree.
    void outputTree()
    {
        outputTreeHelper(rootPtr);
    }

private:
    TreeNode<NODETYPE> *rootPtr;

    // utility function called by insertNode; receives a pointer
    // to a pointer so that the function can modify pointer's value
    void insertNodeHelper(TreeNode<NODETYPE> **ptr, const NODETYPE &value)
    {
        // subtree is empty; create new TreeNode containing value
        if (*ptr == nullptr)
            *ptr = new TreeNode<NODETYPE>(value);
        else // subtree is not empty
        {
            // data to insert is less than data in current node
            if (value < (*ptr)->data)
                insertNodeHelper(&((*ptr)->leftPtr), value);
            else
            {
                // data to insert is greater than data in current node
                if (value > (*ptr)->data)
                    insertNodeHelper(&((*ptr)->rightPtr), value);
                else // duplicate data value ignored
                    std::cout << value << " dup" << std::endl;
            } // end else
        }     // end else
    }         // end function insertNodeHelper

    // utility function to perform preorder traversal of Tree
    void preOrderHelper(TreeNode<NODETYPE> *ptr) const
    {
        if (ptr != nullptr)
        {
            std::cout << ptr->data << ' '; // process node
            preOrderHelper(ptr->leftPtr);  // traverse left subtree
            preOrderHelper(ptr->rightPtr); // traverse right subtree
        }                                  // end if
    }                                      // end function preOrderHelper

    // utility function to perform inorder traversal of Tree
    void inOrderHelper(TreeNode<NODETYPE> *ptr) const
    {
        if (ptr != nullptr)
        {
            inOrderHelper(ptr->leftPtr);   // traverse left subtree
            std::cout << ptr->data << ' '; // process node
            inOrderHelper(ptr->rightPtr);  // traverse right subtree
        }                                  // end if
    }                                      // end function inOrderHelper

    // utility function to perform postorder traversal of Tree
    void postOrderHelper(TreeNode<NODETYPE> *ptr) const
    {
        if (ptr != nullptr)
        {
            postOrderHelper(ptr->leftPtr);  // traverse left subtree
            postOrderHelper(ptr->rightPtr); // traverse right subtree
            std::cout << ptr->data << ' ';  // process node
        }                                   // end if
    }                                       // end function postOrderHelper

    // utility function for searching the (binary search) tree
    // @param key The key value that the tree is being searched for
    // @param ptr The pointer that points to the current substructure of the tree
    // @returns the pointer that points to the substructure of the tree that contains the key value
    TreeNode<NODETYPE> *searchHelper(NODETYPE key, TreeNode<NODETYPE> *ptr) const
    {
        if (ptr == nullptr) // Check whether the tree is empty or not
        {
            cout << "Key has not been found, returning nullptr\n";
            return ptr;
        }
        NODETYPE middle = ptr->data; // Define middle as the current location in the tree
        if (middle == key) // if the middle is the key
        {
            return ptr; // return pointer of the found value
        }
        else if (key < middle) // check whether the key is smaller or larger than the middle value
        {
            return searchHelper(key, ptr->leftPtr); // if the key is smaller, discard the right half of the tree
        }
        else
        {
            return searchHelper(key, ptr->rightPtr); // if the key is larger, discard the left half of the tree
        }
    }

    // utility function for displaying the structure of the tree
    // @param ptr The pointer that points to the current substructure of the tree.
    // @param level The integer that indicates the depth of the tree.
    void outputTreeHelper(TreeNode<NODETYPE> *ptr, int level = 0) const
    {
        if (ptr->rightPtr != nullptr)
        {
            outputTreeHelper(ptr->rightPtr, level + 1);
        }
        for (int depth = 0; depth < level; depth++)
        {
            cout << "\t";
        }
        cout << ptr->data << "\n";
        if (ptr->leftPtr != nullptr)
        {
            outputTreeHelper(ptr->leftPtr, level + 1);
        }
        return;        
    }
}; // end class Tree

#endif

/**************************************************************************
 * (C) Copyright 1992-2014 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/