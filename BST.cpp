/*
 * BST.cpp
 * 
 * Description: Binary Search Tree data collection ADT class.
 *              Link-based implementation.
 *              Duplicated elements are not allowed.
 *
 * Class invariant: It is always a BST.
 * 
 * Author: Inspired from our textbook - Aidan de Vaal
 * Date of last modification: Nov. 3, 2023
 */
 
#include "BST.h"
#include "WordPair.h"
#include <iostream>


// You cannot change the prototype of the public methods of this class.
// Remember, if you add public methods to this class, our test driver 
// - the one we will use to mark this assignment - will not know about them
// since we will use these public method prototypes to create our test driver.

/* Constructors and destructor */

   // Default constructor
   BST::BST() { }            

   // Copy constructor
   BST::BST(const BST & aBST) {

      //recursive copy function starting at root of new BST
      root = copyTree(aBST.root);
      //copy elementCount
      elementCount = aBST.elementCount;
   }

   // Destructor 
   BST::~BST() {
      //recursive delete function
      deleteTree(root);
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

      //allocate space for newElement
      BSTNode * newNode = new BSTNode(newElement);
      //set children to null since it's being added and set element member
      newNode->left = nullptr; newNode->right = nullptr; newNode->element = newElement;
      
      //new failed throw exception
      if(newNode == nullptr){
         throw UnableToInsertException("'new' operator failed.");
      }
      //first element, set it to Dictionary's BST root and increment elementCount
      else if(elementCount == 0){
         this->root = newNode;
         this->elementCount++;
         return;
      }
      //if element already exists throw exception, otherwise insert recursively
      if(!insertR(newNode, this->root)){
         throw(ElementAlreadyExistsException("Element already exists."));
      }
      // to do
	  
   } 

   // Description: Recursive insertion into a binary search tree.
   //              Returns true when "anElement" has been successfully inserted into the 
   //              binary search tree. Otherwise, returns false.
   bool BST::insertR(BSTNode * newBSTNode, BSTNode * current) {
      //technically throws element already exists (would fail anyway)
      if(newBSTNode == nullptr || current == nullptr){
         return false;
      }

      //if new is greater than current, push it right
      if(newBSTNode->element > current->element){
         if(current->hasRight()){
            return insertR(newBSTNode, current->right);
         }
         //if no right leaf, set it as right leaf of current
         else{
            current->right = newBSTNode;
            elementCount++;
            return true;
         }
      }
      //if new is less than current, push it right
      else if(newBSTNode->element < current->element){
         if(current->hasLeft()){
            return insertR(newBSTNode, current->left);
         }
         //if no left leaf, set it as left leaf of current
         else{
            current->left = newBSTNode;
            elementCount++;
            return true;
         }
      }
      //element already exists
      else{
         return false;
      }	
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
      
      //empty exception
     if (elementCount == 0)  
        throw EmptyDataCollectionException("Binary search tree is empty.");
	
      //calls recursive retrieve BST function from Dictionary's BST and saves return to translated
     WordPair& translated = retrieveR(targetElement, root);
	 
     return translated;
   }

   // Description: Recursive retrieval from a binary search tree.
   // Exception: Throws the exception "ElementDoesNotExistException" 
   //            if "targetElement" is not found in the binary search tree.
   WordPair& BST::retrieveR(WordPair & targetElement, BSTNode * current) const {
      
      //if somehow current gets set to null, element not found
      if(current == nullptr){
         throw ElementDoesNotExistException("***Not Found!***");
      }

      //if target is greater than current, search right
      if(targetElement > current->element){
         if(current->hasRight()){
            return retrieveR(targetElement, current->right);
         }
         //if there isn't a right leaf of current and target is greater
         //element not found
         else{
            throw ElementDoesNotExistException("***Not Found!***");
         }
      }
      //if target is less than current, search left
      if(targetElement < current->element){
         if(current->hasLeft()){
            return retrieveR(targetElement, current->left);
         }
         //if there isn't a left leaf of current and target is less
         //element not found
         else{
            throw ElementDoesNotExistException("***Not Found!***");
         }
      }
      //if not greater than or less than, element is found and returned
      return current->element;	
   } 
         
   
   // Description: Traverses the binary search tree in order.
   //           This is a wrapper method which calls the recursive traverseInOrderR( ).
   //           The action to be done on each element during the traverse is the function "visit".
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //         if the binary search tree is empty.
   // Time efficiency: O(n)     
   void BST::traverseInOrder(void visit(WordPair &)) const {
     
     //empty exception
     if (elementCount == 0)  
       throw EmptyDataCollectionException("Binary search tree is empty.");

      //call recursive with function visit and root of BST
     traverseInOrderR(visit, root);
     
     return;
   }

   // Description: Recursive in order traversal of a binary search tree.   
   void BST::traverseInOrderR(void visit(WordPair &), BSTNode* current) const { 
      
      //first check left children/leaves
      if(current->hasLeft()){
         traverseInOrderR(visit, current->left);
      }
      //then check parent/root-of-left-children
      visit(current->element);
      //last check right children/leaves
      if(current->hasRight()){
         traverseInOrderR(visit, current->right);
      }
   }

   // Description: Helper function to deep copy BST.
   // Precondition: BST has been initialized.
   // Time Efficiency: O(n)
   BSTNode * BST::copyTree(BSTNode * node){

      //if node is null return nullptr
      if(node == nullptr){
         return nullptr;
      }
      else{
         //allocate new node space
         BSTNode * newNode = new BSTNode(node->element);
         //post-order traversal of tree copying each node
         return newNode->left = copyTree(node->left);
         return newNode->right = copyTree(node->right);
         return newNode;
      }
   }

   // Description: Helper function to destruct BST.
   // Precondition: BST has been initialized.
   // Time Efficiency: O(n)
   void BST::deleteTree(BSTNode * node){
      //if node isn't null delete in post-order
      if(node!=nullptr){
         deleteTree(node->left);
         deleteTree(node->right);
         delete node;
      }
      root = nullptr;
   }