//Trie_node.h

#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include <map>

class TrieNode {
public:
    std::map<char, TrieNode*> children;
    bool is_end_of_word;
    

    TrieNode() : is_end_of_word(false) {}
};

#endif