#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <sstream>
#include <cstring>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int compareChar(char c1, char c2)
{
    return (std::toupper(c1) -std::toupper(c2));
}


//compares string based on the perspective of str1
//if str1 is greater than str2 in any way, > 0
//if equal return 0
//if str1 < sr2 in anyway < 0
int case_compare(char* str1, char* str2)
{
    //compare the length of two string
    if(strlen(str1)>strlen(str2)){
        return 1;
    }else if(strlen(str1)<strlen(str2)){
        return -1;
    }
    int temp;
    //now compare each character
    for(int x = 0; x < strlen(str1); x++){
        temp = compareChar(str1[x],str2[x]);
        if(temp != 0)
            return temp;
    }
    return 0;
}

bool isNewWord(char cur){
    //check if it's a valid char by checking its ascii number
    //check if it is a lowercase
    if((cur >= 97) && (cur <= 122))
        return false;
    //check if it is upper case
    if((cur >= 65) && (cur <= 90))
        return false;
    //check if it is number
    if((cur >= 48) && (cur <= 57))
        return false;
    //check if it is apo
    if(cur == 39)
        return false;
    //no match, terminating for new word
    return true;
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
    Node(char* word,int position): left(NULL), right(NULL), parent(NULL), color(red),word(word), index(new std::vector<int>{position}) {}
    /// @brief Destructor for memory deallocation.
    ~Node() {
      if (NULL != word) free(word);
      if (NULL != left) delete left;
      if (NULL != right) delete right;
      if (NULL != index)  delete index;
    }
} *root;



void insert_help(Node* root, char* word, int position){
    if (root == NULL){
        root = new Node(strdup(word),position);
        //at this point, index is empty
        //rebalancing here
        return;
    }
    int isGreater = case_compare(root->word,word);
    //cur > insert_node (go left)
    if(isGreater > 0){
          insert_help(root->left,word,position);
    }else if(isGreater < 0){
    	insert_help(root->right,word,position);
    }else{
    	//equal, insert a new position
    	root->index->push_back(position);
    }
}

void insert(Node* root, char* word, int position){
    insert_help(root, word, position);
    //color root to black
    root->color = black;
}
//returns the position, if -1, not found
int look_up(Node* root, char* word, int occurance){
   //if root doesn't exist
   if (root == NULL){
        return -1;
    }
   //get comparison
   int isGreater = case_compare(root->word,word);
   //cur > insert_node (go left)
    if(isGreater > 0){
          look_up(root->left,word,occurance);
    }else if(isGreater < 0){
    	insert_help(root->right,word,occurance);
    }
    //equal, check if the occurance is in range
    if(occurance > root->index->size()){
	return -1;
    }
    return root->index->at(occurance);
}
