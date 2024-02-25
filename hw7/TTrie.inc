// TODO: implement TTrie member functions and friend functions

// Helper function to recursively delete the trie
template <typename DataType>
void TTrie<DataType>::deleteTrie(TrieNode<DataType>* node) {
    if (!node) {
        return;
    }

    // Use iterator to loop through the children
    typename std::map<DataType, TrieNode<DataType>*>::iterator it;
    for (it = node->children.begin(); it != node->children.end(); ++it) {
        TrieNode<DataType>* childNode = it->second;
        deleteTrie(childNode);
    }

    delete node;
}

// Helper function to recursively copy the trie
template <typename DataType>
TrieNode<DataType>* TTrie<DataType>::copyTrie(const TrieNode<DataType>* node) {
    if (!node) {
        return nullptr;
    }

    TrieNode<DataType>* newNode = new TrieNode<DataType>();
    newNode->isEndOfWord = node->isEndOfWord;

    // Use iterator to loop through the children
    typename std::map<DataType, TrieNode<DataType>*>::const_iterator it;
    for (it = node->children.begin(); it != node->children.end(); ++it) {
        const DataType& value = it->first;
        const TrieNode<DataType>* childNode = it->second;
        newNode->children[value] = copyTrie(childNode);
    }

    return newNode;
}

/**
 * Copy Constructor.
 * param rhs A const reference to the input to copy.
 */
template <typename DataType>
TTrie<DataType>::TTrie(const TTrie& rhs) {
    root = copyTrie(rhs.root);
}

// TTrie destructor
template <typename DataType>
TTrie<DataType>::~TTrie() {
    deleteTrie(root);
}

// Helper function to recursively count the number of children
template <typename DataType>
unsigned countChildren(const TrieNode<DataType>* node) {
    unsigned count = 0;

    // Use iterator to loop through the children
    typename std::map<DataType, TrieNode<DataType>*>::const_iterator it;
    for (it = node->children.begin(); it != node->children.end(); ++it) {
        const TrieNode<DataType>* childNode = it->second;
        count += countChildren(childNode);
    }

    return count;
}

// TTrie numChildren function
template <typename DataType>
unsigned TTrie<DataType>::numChildren() const {
    return countChildren(root);
}

// TTrie hasChild function
template <typename DataType>
bool TTrie<DataType>::hasChild() const {
    return !root->children.empty();
}

// TTrie hasChild function with a specific value
template <typename DataType>
bool TTrie<DataType>::hasChild(const DataType& value) const {
    return root->children.find(value) != root->children.end();
}

// Helper function to recursively get the child TTrie
template <typename DataType>
const TTrie<DataType>* TTrie<DataType>::getChildTrie(TrieNode<DataType>* node, const DataType& value) const {
    typename std::map<DataType, TrieNode<DataType>*>::iterator it = node->children.find(value);
    if (it != node->children.end()) {
        TTrie<DataType>* childTrie = new TTrie<DataType>();
        childTrie->root = it->second; 
        return childTrie;
    }
    return nullptr;
}

// TTrie getChild function 
template <typename DataType>
const TTrie<DataType>* TTrie<DataType>::getChild(const DataType& value) const {
    return getChildTrie(root, value);
}

// TTrie isEndpoint function
template <typename DataType>
bool TTrie<DataType>::isEndpoint() const {
    return root->isEndOfWord;
}

template <typename DataType>
bool TTrie<DataType>::compareTries(const TrieNode<DataType>* node1, const TrieNode<DataType>* node2) const {
    if (!node1 && !node2) {
        return true;  // Both nodes are nullptr, and equal
    }

    if (!node1 || !node2) {
        return false;  // One of the nodes is nullptr, and they are not equal
    }

    // Check if the current nodes have the same isEndOfWord value
    if (node1->isEndOfWord != node2->isEndOfWord) {
        return false;
    }

    // Check the children nodes recursively
    for (typename std::map<DataType, TrieNode<DataType>*>::const_iterator it1 = node1->children.begin(); it1 != node1->children.end(); ++it1) {
        const DataType& value = it1->first;
        const TrieNode<DataType>* childNode1 = it1->second;
        const TrieNode<DataType>* childNode2 = nullptr;

        typename std::map<DataType, TrieNode<DataType>*>::const_iterator it2 = node2->children.find(value);
        if (it2 != node2->children.end()) {
            childNode2 = it2->second;
        }

        if (!compareTries(childNode1, childNode2)) {
            return false;  // The subtrees are not equal
        }
    }

    // Check if node2 has any children not present in node1
    for (typename std::map<DataType, TrieNode<DataType>*>::const_iterator it2 = node2->children.begin(); it2 != node2->children.end(); ++it2) {
        const DataType& value = it2->first;
        const TrieNode<DataType>* childNode2 = it2->second;

        typename std::map<DataType, TrieNode<DataType>*>::const_iterator it1 = node1->children.find(value);
        if (it1 == node1->children.end()) {
            // There is a child in node2 that is not present in node1
            if (childNode2) {
                return false;
            }
        }
    }

    return true;
}

/**
 * Assignment operator.
 */
template <typename DataType>
TTrie<DataType>& TTrie<DataType>::operator=(const TTrie<DataType>& rhs) {
    // Check for self-assignment
    if (this == &rhs) {
        return *this;
    }

    // Delete the current trie to avoid memory leaks
    deleteTrie(root);

    // Copy the contents of rhs into this TTrie
    root = copyTrie(rhs.root);

    // Return a reference to this TTrie
    return *this;
}

/**
 * Overloaded addition/assignment operator to input a new vector into the TTrie.
 * param sequence is the vector to insert into the trie
 * return a reference to the TTrie object
 */
template <typename DataType>
TTrie<DataType>& TTrie<DataType>::operator+=(const std::vector<DataType>& sequence) {
    TrieNode<DataType>* current = root;

    for (typename std::vector<DataType>::const_iterator it = sequence.begin(); it != sequence.end(); ++it) {
        const DataType& value = *it;
        if (current->children.find(value) == current->children.end()) {
            current->children[value] = new TrieNode<DataType>();
        }
        current = current->children[value];
    }

    current->isEndOfWord = true;
    return *this;
}

/**
 * Overloaded carat operator to check whether a given sequence exists in the object.
 * param sequence is the sequence to find
 * return true if the sequence is a member of the trie, false otherwise
 */
template <typename DataType>
bool TTrie<DataType>::operator^(const std::vector<DataType>& sequence) const {
    const TrieNode<DataType>* current = root;

    for (typename std::vector<DataType>::const_iterator it = sequence.begin(); it != sequence.end(); ++it) {
        const DataType& value = *it;
        typename std::map<DataType, TrieNode<DataType>*>::const_iterator child_it = current->children.find(value);
        if (child_it == current->children.end()) {
            return false;  // The sequence doesn't exist in the TTrie
        }
        current = child_it->second;
    }

    return current->isEndOfWord;  // Check if the last node in the sequence is an endpoint
}

/**
 * Overloaded equality operator to check whether two TTrie objects are equal.
 * rhs A const reference to the TTrie object to compare.
 * true if the other object represents exactly the same set of sequences,
 *         false otherwise
 */
template <typename DataType>
bool TTrie<DataType>::operator==(const TTrie<DataType>& rhs) const {
    return compareTries(root, rhs.root);
}

// Helper function to recursively generate sequences and print them to the output stream
template <typename DataType>
void printTrieSequences(std::ostream& os, const TrieNode<DataType>* node, const std::vector<DataType>& sequence) {
    if (!node) {
        return;
    }

    if (node->isEndOfWord) {
        // Print the sequence when reaching the end of a word
        for (size_t i = 0; i < sequence.size(); ++i) {
            if (i > 0) {
                os << "-";
            }
            os << sequence[i];
        }
        os << std::endl;
    }

    for (typename std::map<DataType, TrieNode<DataType>*>::const_iterator it = node->children.begin(); it != node->children.end(); ++it) {
        const DataType& value = it->first;
        const TrieNode<DataType>* childNode = it->second;
        std::vector<DataType> newSequence = sequence;
        newSequence.push_back(value);
        printTrieSequences(os, childNode, newSequence);
    }
}

/**
 * Overloaded output stream operator<< to print the sequences
 *        in the TTrie one per line, with values separated by '-'
 *        (hyphen) characters, in lexicographical order (note that if
 *        you use a map to represent links to children, a recursive
 *        traversal should allow you to generate the sequences in
 *        sorted order very easily)
 * A reference to the output stream object
 * A constant reference to the input TTrie object
 * A reference to the output stream object
 */
template <typename U>
std::ostream& operator<<(std::ostream& os, const TTrie<U>& tt) {
  printTrieSequences(os, tt.root, std::vector<U>());
  return os;
}
