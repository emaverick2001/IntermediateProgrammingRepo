#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
//TODO: check valgrind errors

#include "CTrie.h"

// CTrie constructor
CTrie::CTrie() : root(new TrieNode()){}

// Copy constructor
CTrie::CTrie(const CTrie& rhs) {
  
  // Create a new TrieNode for the root
    root = new TrieNode();

    // Call a recursive helper function to copy the Trie
    deepCopy(rhs.root, root);
}

//returns num of child nodes
unsigned CTrie::numChildren() const{
  return root->children.size();
}

  //return true if there are any children, false otherwise
bool CTrie::hasChild() const{
  return !root->children.empty();
}

//Check whether a child linked by a specific character exists.
bool CTrie::hasChild(char character) const {
    if (root->children.find(character) != root->children.end()) {
        return true;
    }
    return false;
}

//Get pointer to child curr reachable via link labeled with the specified character.
const CTrie* CTrie::getChild(char character) const{
  std::map<char, TrieNode*>::iterator it;
  if (root->children.find(character) != root->children.end()){
      it = root->children.find(character);
      CTrie* child = new CTrie();
      child->root = it->second;
      return child;
  }
  return nullptr;
}


 //return true if this curr is an endpoint, false otherwise
bool CTrie::isEndpoint() const{
  
  for (std::map<char, TrieNode*>::iterator it = root->children.begin(); it!= root->children.end(); ++it){
    if (it->second->is_end_of_word){
      return true;
    }
  }
  return false;
}

// operators

bool CTrie::operator==(const CTrie& rhs) const {
  // Base case: If both TrieNodes are nullptr, they are equal
  if (root == nullptr && rhs.root == nullptr) {
    return true;
  }

  // If one of the TrieNodes is nullptr and the other is not, they are not equal
  if (root == nullptr || rhs.root == nullptr) {
    return false;
  }

  // Check if the current nodes have the same is_end_of_word value
  if (root->is_end_of_word != rhs.root->is_end_of_word) {
    return false;
  }

  // Recursively check each child node
  for (std::map<char, TrieNode*>::const_iterator it = root->children.begin(); it != root->children.end(); ++it) {
    char key = it->first;
    if (!rhs.hasChild(key) || !(*getChild(key) == *rhs.getChild(key))) {
      return false;
    }
  }

  return true;
}

// Overloaded addition/assignment operator to input a new string into the Trie.
CTrie& CTrie::operator+=(const std::string& word){
  TrieNode* curr = root;
  for(int i =0;i < (int)word.length();i++){
    //have to check if character is already in CTrie
    // checks to see if char is not present
    if(curr->children.find(word[i])== curr->children.end()){
      curr->children[word[i]]= new TrieNode();
    }
    curr = curr->children[word[i]];
  }
  curr->is_end_of_word = true;

  return *this;
}

/**
 * Overloaded carat operator to check whether a given word exists in the object.
 * \param word the word to find.
 * \return true if the word is a member of the trie, false otherwise
 */

bool CTrie::operator^(const std::string &word) const {
    const TrieNode* curr = root;

    for (size_t i = 0; i < word.length(); ++i) {
        char c = word[i];
        std::map<char, TrieNode*>::const_iterator it = curr->children.find(c);

        if (it == curr->children.end()) {
            return false; // The character is not present in the trie
        }
        curr = it->second; // Move to the next node
    }

    // At this point, we have traversed the entire word
    // If the last node is an endpoint, then the word exists in the trie
    return curr->is_end_of_word;
}


//Assignment operator.
CTrie& CTrie::operator=(const CTrie& rhs) {
    if (this == &rhs) {
        return *this; // Self-assignment, no need to do anything
    }

    // Perform a deep copy of the rhs trie
    root = new TrieNode();
    deepCopy(rhs.root, root);

    return *this;
}


/**
   * \brief Overloaded output stream operator<< to print the CTrie in 
   * this format a word by line in alphabetical order
   *   e.g. if we have a CTrie with three words 'johns', 'hopkins', 'university'
   *    it will print "hopkins\njohns\nuniversity\n"
   * \param os A reference to the output stream object
   * \param q A constant reference to the input CTrie object
   * \return A reference to the output stream object
  */

// Overloaded output stream operator to print the CTrie
void CTrie::printTrie(std::ostream& os, const TrieNode* node, std::string word) const {
  if (node->is_end_of_word) {
    os << word << "\n";

  }

  // Explicitly specify the type of the iterator
  std::map<char, TrieNode*>::const_iterator it;
  for (it = node->children.begin(); it != node->children.end(); ++it) {
    char character = it->first;
    const TrieNode* childNode = it->second;
    std::string updatedWord = word + character;
    printTrie(os, childNode, updatedWord);

  }
}

std::ostream& operator<<(std::ostream& os, const CTrie& ct) {
  ct.printTrie(os, ct.root, "");
  return os;
}