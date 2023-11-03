/*
 * BSTTestDriver.cpp
 * 
 * Description: Driver for Dictionary BST ADT class. 
 *
 * Author: AL - Aidan de Vaal
 * Last Modification Date: Nov. 3, 2023
 */

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "BST.h"
#include "Dictionary.h"
#include "WordPair.h"
#include "ElementAlreadyExistsException.h"
#include "ElementDoesNotExistException.h"
#include "EmptyDataCollectionException.h"
#include "UnableToInsertException.h"

using std::cin;
using std::cout;
using std::ifstream;

void display(WordPair& anElement) {
  cout << anElement;
} 

int main(int argc, char *argv[]) {

  Dictionary * myWords = new Dictionary();

  string nextLine = "";
  string nextWord = "";
  string englishW = "";
  string frenchW = "";
  string filename = "dataFile.txt";
  string delimiter = ":";
  size_t pos = 0;
  WordPair translated;
 
  
  ifstream myfile (filename);
  if (myfile.is_open()) {
     cout << "Reading..." << endl; 
     while (getline(myfile,nextLine))
     {
        pos = nextLine.find(delimiter);
        englishW = nextLine.substr(0, pos);
        nextLine.erase(0, pos + delimiter.length());
        frenchW = nextLine;
        WordPair nextWordPair(englishW, frenchW);
        // insert nextWordPair into "myWords" using a try/catch block
        try {
           myWords->put(nextWordPair);
        }
        catch (ElementAlreadyExistsException& anException) {
           cout << "put() unsuccessful because " << anException.what() << endl;
        }
        catch (UnableToInsertException& anException) {
           cout << "put() unsuccessful because " << anException.what() << endl;
        }
     }
     myfile.close();
     cout << "Finished reading." << endl;

     // If user entered "display" with program call
     if ((argc>1) && (strcmp(argv[1], "display") == 0)) {
        try {
           myWords->displayContent(display);
        }
        catch (EmptyDataCollectionException& anException) {
           cout << "displayContent() unsuccessful because " << anException.what() << endl;
        }
     }
     else if (argc == 1) {
        // while not EOF
        while (getline(cin, nextWord)) {   
            WordPair nextWordPair(nextWord);
            // retrieve nextWordPair from "myWords" using a try/catch block and print it
            try {
              WordPair& check = myWords->get(nextWordPair);
              cout << check;
            }
            catch (EmptyDataCollectionException& anException) {
              cout << "get() unsuccessful because " << anException.what() << endl;
            }
            catch (ElementDoesNotExistException& anException) {
               cout << anException.what() << endl;
            }
            }
        }
  }
  else 
     cout << "Unable to open file"; 
  return 0;
}