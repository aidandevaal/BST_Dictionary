/*
 * Dictionary.cpp
 * 
 * Description: Dictonary data collection ADT class.
 *              BST-based implementation.
 *              Duplicated elements not allowed.
 * 
 * Author: Aidan de Vaal
 * Date of last modification: Oct. 2023
 */
 
#include "BST.h"
#include "Dictionary.h"
#include "WordPair.h"
#include <iostream>

// You cannot change the prototype of the public methods of this class.
// Remember, if you add public methods to this class, our test driver 
// - the one we will use to mark this assignment - will not know about them
// since we will use these public method prototypes to create our test driver.

/* Constructors and destructor */

   // Default constructor
   Dictionary::Dictionary() { 
      //allocate space for BST
      keyValuePairs = new BST();
   }            

   // Destructor 
   Dictionary::~Dictionary() {
      //call helper recursive delete function
      deleteDictionary(keyValuePairs->root);
      // to do
   }                
   
   
/* Getters and setters */

   // Description: Returns the number of elements currently stored in the Dictionary.   
   // Time efficiency: O(1)   
   unsigned int Dictionary::getElementCount() const {     
     return keyValuePairs->elementCount;
   }
   

/* Dictionary Operations */

   // Description: Puts "newElement" (association of key-value) into the Dictionary.
   // Precondition: "newElement" does not already exist in the Dictionary.
   //               This is to say: no duplication allowed.
   // Exception: Throws the exception "UnableToInsertException" 
   //            when newElement cannot be inserted in the Dictionary.  
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the Dictionary.   
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
      if(!keyValuePairs->insertR(newNode, keyValuePairs->root)){
         throw(ElementAlreadyExistsException("Element already exists."));
      }
      // to do
   } 

   // Description: Gets "newElement" (i.e., the associated value of a given key) 
   //              from the Dictionary.
   // Precondition: Dictionary is not empty.
   // Exception: Throws the exception ElementDoesNotExistException
   //            if the key is not found in the Dictionary.
   // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
   WordPair& Dictionary::get(WordPair & targetElement) const {
      
     if (keyValuePairs->elementCount == 0)  
        throw EmptyDataCollectionException("Binary search tree is empty.");
	
     WordPair& translated = keyValuePairs->retrieveR(targetElement, keyValuePairs->root);
	 
     return translated;
   }
   
   // Description: Prints the content of the Dictionary.
   // Precondition: Dictionary is not empty.
   // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.   
   void Dictionary::displayContent(void visit(WordPair &)) const {
      //empty exception
     if (keyValuePairs->elementCount == 0)  
       throw EmptyDataCollectionException("Binary search tree is empty.");
     //call BST traverse (public) function from Dictionary's BST
     keyValuePairs->traverseInOrder(visit);
     
     return;
   }

   // Description: Helper function to destruct Dictionary.
   // Precondition: Dictionary keyValuePairs has been initialized.
   // Time Efficiency: O(n)
   void Dictionary::deleteDictionary(BSTNode * node){
      //while there's a node, post-order traverse
      if(node!=nullptr){
         //delete left child elements
         deleteDictionary(node->left);
         //delete right child elements
         deleteDictionary(node->right);
         //delete roots
         delete node;
      }
      //set root to nullptr
      keyValuePairs->root = nullptr;
   }