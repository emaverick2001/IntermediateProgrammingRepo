//Trie_node.h

#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include <map>

template <typename DataType>
class TrieNode {
public:
    bool isEndOfWord;
    std::map<DataType, TrieNode<DataType>*> children;

    TrieNode() { isEndOfWord = false; }    
};

#endif