#ifndef CTRIE_H
#define CTRIE_H

#include <map>
#include <vector>
#include <string>
#include "Trie_node.h"

class CTrie {

private:
  // TODO: fields
  TrieNode* root;
  
  // TODO: helper functions

  // Helper function to delete a subtree starting from the specified node
  void deleteSubTrie(TrieNode* node) {
    // Base case: if the current node is nullptr, return
    if (node == nullptr) {
        return;
    }

    // Recursively delete the children nodes first
    for (std::map<char, TrieNode*>::iterator it = node->children.begin(); it != node->children.end(); ++it) {
        deleteSubTrie(it->second);
    }

    // Delete the current node after its children have been deleted
    delete node;
  }  
  
  // Helper function to recursively copy the Trie
  //srcNode = root we want to copy
  //destNode = our root/ root taking the copy of the srcNode
  void deepCopy(const TrieNode* srcNode, TrieNode* destNode) {
      // Base case: if the source node is nullptr, return
      if (!srcNode) {
          return;
      }

      // Copy the is_end_of_word flag
      destNode->is_end_of_word = srcNode->is_end_of_word;

      // Recursively copy the children nodes
      for (std::map<char, TrieNode*>::const_iterator it = srcNode->children.begin(); it != srcNode->children.end(); ++it) {
          char key = it->first;//store key
          const TrieNode* srcChild = it->second;//store child node as a value
          TrieNode* destChild = new TrieNode();
          destNode->children[key] = destChild; // Link the child to the parent node
          deepCopy(srcChild, destChild); // Recursively copy the child node
      }
  }

      // Helper function to print the trie
  void printTrie(std::ostream& os, const TrieNode* node, std::string word) const;
  
public:
  /**
   * Default Constructor.
   */
  CTrie();

  /**
   * Copy Constructor.
   * \param rhs A const reference to the input to copy.
   */
  CTrie(const CTrie& rhs);

  // Destructor
  ~CTrie() {
      // Call the helper function to perform the recursive deletion starting from the root node
      deleteSubTrie(root);
  }

  /**
   * Assignment operator.
   */
  CTrie& operator=(const CTrie &rhs);

  /**
   * Overloaded addition/assignment operator to input a new string into the Trie.
   * \param word is the word to input into the operator.
   * \return a reference to the CTrie object
   */
  CTrie& operator+=(const std::string& word);

  /**
   * Overloaded carat operator to check whether a given word exists in the object.
   * \param word the word to find.
   * \return true if the word is a member of the trie, false otherwise
   */
  bool operator^(const std::string &word) const;

  /**
   * Overloaded equality operator to check whether two Trie objects are equal.
   * \param rhs A const reference to the CTrie object to compare.
   * \return true if the other object represents exactly the same set of words,
   *         false otherwise
   */
  bool operator==(const CTrie& rhs) const;

  /**
   * \brief Overloaded output stream operator<< to print the CTrie in 
   * this format a word by line in alphabetical order
   *   e.g. if we have a CTrie with three words 'johns', 'hopkins', 'university'
   *    it will print "hopkins\njohns\nuniversity\n"
   * \param os A reference to the output stream object
   * \param q A constant reference to the input CTrie object
   * \return A reference to the output stream object
  */
  friend std::ostream& operator<<(std::ostream& os, const CTrie& ct);

  /**
   * \return the number of children
   */
  unsigned numChildren() const;

  /**
   * \return true if there are any children, false otherwise
   */
  bool hasChild() const;

  /**
   * Check whether a child linked by a specific character exists.
   * \param character a character
   * \return true if there is a link to a child labeled with the character,
   *         false otherwise
   */
  bool hasChild(char character) const;

  /**
   * Get pointer to child node reachable via link labeled with
   * the specified character.
   * \param character a character
   * \return pointer to child node, or nullptr if there is no such child
   */
  const CTrie* getChild(char character) const;

  /**
   * \return true if this node is an endpoint, false otherwise
   */
  bool isEndpoint() const; 
};

#endif // CTRIE_H
