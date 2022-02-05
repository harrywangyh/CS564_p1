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
    int temp;
    //compare the length of two string
    if(strlen(str1)>strlen(str2)){
        //str1 is longer than str2, iterate through both string with the length of 2
        //so if it's a tie after the loop, str1 is greater then 2
        for(int x = 0; x < int(strlen(str2)); x++){
        //check if one of the string is greater than the other
        //check if the current index
            temp = compareChar(str1[x],str2[x]);
            if(temp != 0)
                return temp;
        }
        return 1;
    }else if(strlen(str1)<strlen(str2)){
        for(int x = 0; x < int(strlen(str1)); x++){
        //check if one of the string is greater than the other
        //check if the current index
            temp = compareChar(str1[x],str2[x]);
            if(temp != 0)
                return temp;
        }
        return -1;
    }
    //now compare each character
    for(int x = 0; x < int(strlen(str1)); x++){
        //check if one of the string is greater than the other
        //check if the current index
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

bool isNumber(std::string& str)
{
    for (char &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

class Node {
 public:
    Node* left;       ///< Member Pointer to left subtree of this node.
    Node* right;      ///< Member Pointer to right subtree of this node.
    char* word;       ///< Member for Word stored in this node.
    std::vector<int>* index;  ///< Indices of this word in the input document

    /// @brief Default constructor which sets all member pointers to NULL
    Node():left(NULL), right(NULL), word(NULL), index(NULL) {}
    Node(char* word,int position): left(NULL), right(NULL), word(word), index(new std::vector<int>{position}) {}
    /// @brief Destructor for memory deallocation.
    ~Node() {
      if (NULL != word) delete[] word;
      if (NULL != left) delete left;
      if (NULL != right) delete right;
      if (NULL != index)  delete index;
    }
};

Node* insert_help(Node* root, char* word, int position){
    if (root == NULL){

        root = new Node(word,position);
        //at this point, index is empty
        //rebalancing here
        return root;
    }
    Node * ret;
    int isGreater = case_compare(root->word,word);
    //cur > insert_node (go left)
    if(isGreater > 0){
          ret = insert_help(root->left,word,position);
          root->left = ret;
    }else if(isGreater < 0){
        ret = insert_help(root->right,word,position);
        root->right = ret;
    }else{
        delete[] word;
        //equal, insert a new position
        root->index->push_back(position);
    }
    return root;
}

Node* insert(Node* root, char* word, int position){
    root = insert_help(root, word, position);
    //color root to black
    return root;
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
          return look_up(root->left,word,occurance);
    }else if(isGreater < 0){
    	return look_up(root->right,word,occurance);
    }
    //equal, check if the occurance is in range
    if(occurance > int(root->index->size())){
	return -1;
    }
    return root->index->at(occurance-1);
}
