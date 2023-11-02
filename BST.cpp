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
   BST::BST() { }            

   // Copy constructor
   BST::BST(const BST & aBST) {
      BST * cBST = new BST();
      root = aBST.root;
      elementCount = aBST.elementCount;
      BSTNode * curr = new BSTNode;
      BSTNode * temp = new BSTNode;
      curr = aBST.root;
      temp = cBST->root;
	  // to do
   }

   // Destructor 
   BST::~BST() {

      // to do
   }                
   
   
/* Getters and setters */

   // Description: Returns the number of elements currently stored in the binary search tree.   
   // Time efficiency: O(1)   
   unsigned int BST::getElementCount() const {     

     return this->elementCount;
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
   void BST::insert(WordPair & newElement) {
      BSTNode * newNode = new BSTNode(newElement);
      newNode->left = nullptr; newNode->right = nullptr;
      BSTNode * curr = this->root;
      if(newNode == nullptr){
         throw UnableToInsertException("'new' operator failed.");
      }
      if(!insertR(newNode, curr)){
         throw ElementAlreadyExistsException("Element already exists.");
      }
      // to do
	  
   } 

   // Description: Recursive insertion into a binary search tree.
   //              Returns true when "anElement" has been successfully inserted into the 
   //              binary search tree. Otherwise, returns false.
   bool BST::insertR(BSTNode * newBSTNode, BSTNode * current) {  
      if(newBSTNode->element > current->element){
         if(current->hasRight()){
            insertR(newBSTNode, current->right);
         }
         else{
            current->right = newBSTNode;
            elementCount++;
            return true;
         }
      }
      if(newBSTNode->element < current->element){
         if(current->hasLeft()){
            insertR(newBSTNode, current->left);
         }
         else{
            current->left = newBSTNode;
            elementCount++;
            return true;
         }
      }
      else{
         return false;
      }
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
   WordPair& BST::retrieve(WordPair & targetElement) const {
      
     if (elementCount == 0)  
        throw EmptyDataCollectionException("Binary search tree is empty.");
	
     WordPair& translated = retrieveR(targetElement, root);
	 
     return translated;
   }

   // Description: Recursive retrieval from a binary search tree.
   // Exception: Throws the exception "ElementDoesNotExistException" 
   //            if "targetElement" is not found in the binary search tree.
   WordPair& BST::retrieveR(WordPair & targetElement, BSTNode * current) const {
      if(targetElement > current->element){
         if(current->hasRight()){
            retrieveR(targetElement, current->right);
         }
      }
      if(targetElement < current->element){
         if(current->hasLeft()){
            retrieveR(targetElement, current->left);
         }
      }
      else if(current->element == targetElement){
         return current->element;
      }
      else{
         throw ElementDoesNotExistException("Element not found.");
      }
	  // to do
		
   } 
         
   
   // Description: Traverses the binary search tree in order.
   //           This is a wrapper method which calls the recursive traverseInOrderR( ).
   //           The action to be done on each element during the traverse is the function "visit".
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //         if the binary search tree is empty.
   // Time efficiency: O(n)     
   void BST::traverseInOrder(void visit(WordPair &)) const {
     
     if (elementCount == 0)  
       throw EmptyDataCollectionException("Binary search tree is empty.");

     traverseInOrderR(visit, root);
     
     return;
   }

   // Description: Recursive in order traversal of a binary search tree.   
   void BST::traverseInOrderR(void visit(WordPair &), BSTNode* current) const { 
      if(current->hasLeft()){
         traverseInOrderR(visit, current->left);
      }
      traverseInOrderR(visit, current);
      if(current->hasRight()){
         traverseInOrderR(visit, current->right);
      }
	  // to do
	  
   }
