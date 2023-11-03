/*
 * BST.cpp
 * 
 * Description: Binary Search Tree data collection ADT class.
 *              Link-based implementation.
 *              Duplicated elements are not allowed.
 *
 * Class invariant: It is always a BST.
 * 
 * Author: Inspired from our textbook
 * Date of last modification: Oct. 2023
 */
 
#include "BST.h"
#include "Dictionary.h"
#include "WordPair.h"
#include <iostream>

using std::cout;
using std::endl;

// You cannot change the prototype of the public methods of this class.
// Remember, if you add public methods to this class, our test driver 
// - the one we will use to mark this assignment - will not know about them
// since we will use these public method prototypes to create our test driver.

/* Constructors and destructor */

   // Default constructor
   Dictionary::Dictionary() { 
      keyValuePairs = new BST();
   }            

   // Destructor 
   Dictionary::~Dictionary() {
      deleteDictionary(keyValuePairs->root);
      // to do
   }                
   
   
/* Getters and setters */

   // Description: Returns the number of elements currently stored in the binary search tree.   
   // Time efficiency: O(1)   
   unsigned int Dictionary::getElementCount() const {     

     return keyValuePairs->elementCount;
   }
   

/* BST Operations */

   // Description: Inserts an element into the binary search tree.
   //              This is a wrapper method which calls the recursive insertR( ).
   // Precondition: "newElement" does not already exist in the binary search tree.
   // Exception: Throws the exception "UnableToInsertException" when newElement 
   //            cannot be inserted because the "new" operator failed. 
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the binary search tree.
   // Time efficiency: O(log2 n)   
   void Dictionary::put(WordPair & newElement) {
      BSTNode * newNode = new BSTNode(newElement);
      newNode->left = nullptr; newNode->right = nullptr; newNode->element = newElement;
      if(newNode == nullptr){
         throw UnableToInsertException("'new' operator failed.");
      }
      else if(keyValuePairs->elementCount == 0){
         keyValuePairs->root = newNode;
         keyValuePairs->elementCount++;
         return;
      }
      keyValuePairs->insertR(newNode, keyValuePairs->root);
      // to do
	  
   } 

   // Description: Retrieves "targetElement" from the binary search tree.
   //           This is a wrapper method which calls the recursive retrieveR( ).
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Exception: Throws (propagates) the exception "ElementDoesNotExistException" 
   //            thrown from the retrieveR(...)
   //            if "targetElement" is not in the binary search tree.
   // Time efficiency: O(log2 n)
   WordPair& Dictionary::get(WordPair & targetElement) const {
      
     if (keyValuePairs->elementCount == 0)  
        throw EmptyDataCollectionException("Binary search tree is empty.");
	
     WordPair& translated = keyValuePairs->retrieveR(targetElement, keyValuePairs->root);
     cout << translated << endl;
	 
     return translated;
   }
   
   // Description: Traverses the binary search tree in order.
   //           This is a wrapper method which calls the recursive traverseInOrderR( ).
   //           The action to be done on each element during the traverse is the function "visit".
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //         if the binary search tree is empty.
   // Time efficiency: O(n)     
   void Dictionary::displayContent(void visit(WordPair &)) const {
     if (keyValuePairs->elementCount == 0)  
       throw EmptyDataCollectionException("Binary search tree is empty.");
     
     keyValuePairs->traverseInOrder(visit);
     
     return;
   }

   void Dictionary::deleteDictionary(BSTNode * node){
      if(node!=nullptr){
         deleteDictionary(node->left);
         deleteDictionary(node->right);
         delete node;
      }
      keyValuePairs->root = nullptr;
   }