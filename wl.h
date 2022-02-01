#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <sstream>
#include <cstring>

bool compareChar(char & c1, char & c2)
{
    if (c1 == c2)
        return true;
    else if (std::toupper(c1) == std::toupper(c2))
        return true;
    return false;
}

bool case_compare(std::string & str1, std::string &str2)
{
    return ( (str1.size() == str2.size() ) &&
             std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar) );
}

enum Color { red, black };
class Node {
 public:
    Node* left;       ///< Member Pointer to left subtree of this node.
    Node* right;      ///< Member Pointer to right subtree of this node.
    Node* parent;     ////pointer to the parent of the node
    char* word;       ///< Member for Word stored in this node.
    Color color;     ///color of the node
    std::vector<int>* index;  ///< Indices of this word in the input document

    /// @brief Default constructor which sets all member pointers to NULL
    Node():left(NULL), right(NULL), parent(NULL),word(NULL), index(NULL) {}
    Node(char* word,int position): left(NULL), right(NULL), parent(NULL),word(word), index(new std::vector<int>{position}) {}
    /// @brief Destructor for memory deallocation.
    ~Node() {
      if (NULL != word) free(word);
      if (NULL != left) delete left;
      if (NULL != right) delete right;
      if (NULL != index)  delete index;
    }
} *root;
/*
void insert(node* root, const char* word, int positon){
    if (root == NULL){
        root = new node(strdup(word));
        //at this point, index is empty
        root->index.push_back(position);
        return;
    }
    int isGreater = case_compare(root->word,word);
    if(isGreater > 0){
        
    }

}
*/
