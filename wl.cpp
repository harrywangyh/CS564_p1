#include "wl.h"

using namespace std; // this is a using directive telling the compiler to check the std namespace when resolving identifiers with no prefix
Node* root; 
bool deleted = true;

char* string_char(string str){
     return const_cast<char*>(str.c_str());
}

void print_tree(Node* root){
    if (root == NULL)
        return;
    print_tree(root->left);
    cout << "word: " << root->word <<" ";
    cout << "position ";
    for(int x =0; x < root->index->size(); x++){
        cout << root->index->at(x) << " ";
    }
    cout << endl;
    print_tree(root->right);
}


bool is_valid(string test){
    char* test_char = string_char(test);
    for(int x = 0; x < strlen(test_char); x++){
        if(isNewWord(test_char[x]))
            return false;
    }
    return true;
}
void insert_file(char* addr, int size){
    bool recent = false;
    vector<char> buffer;
    int wordCount = 0;
    for(int x = 0; x < size; x++){
        if(!isNewWord(addr[x])){
            buffer.push_back(addr[x]);
            recent = false;
        }else{
            if(!recent){
                char* newWord = new char[buffer.size()+1];
                copy(buffer.begin(),buffer.end(), newWord);
                //insert into tree
                wordCount++;
                root = insert(root,newWord,wordCount);
                recent = true;
                buffer.clear();
            }
        }
    }
    if(!recent){
        char* newWord = new char[buffer.size()+1];
        copy(buffer.begin(),buffer.end(), newWord);
        //insert here
        wordCount++;
        root = insert(root,newWord,wordCount);
        recent = true;
        buffer.clear();
    }
}

void load_file(std::string file){
    reset(root);
    string  myText;
    //converts file name to char*
    char* file_char = string_char(file);
    int fd = open(file_char, O_RDONLY);
    char * addr;
    if (fd == -1){
        cout<< "ERROR: Invalid command"<<endl;
        return;
    }
    struct stat sb;
    if (fstat(fd, &sb) == -1){           /* To obtain file size */
        cout<< "ERROR: Invalid command"<<endl;
        return;
    }
    addr = (char *)mmap(NULL, sb.st_size +1, PROT_READ,MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED){
        cout<< "ERROR: Invalid command"<<endl;
        return;
    }
    insert_file(addr,sb.st_size);
    munmap(addr, sb.st_size ); 
    close(fd);
    deleted = false;
}

void locate_word(string word, string occurance){
    char * test_word = string_char(word);
    if(!isNumber(occurance)){
        cout << "ERROR: Invalid command"<<endl;
        return;
    }
    if(!is_valid(word)){
        cout << "ERROR: Invalid command"<<endl;
        return;
    }
    //convert string to num
    int ocur_num = stoi(occurance);  
    Node* searchNode = root; 
    int index = look_up(searchNode, test_word,ocur_num);
    if(index == -1)
        cout << "No matching entry"<<endl;
    else
        cout << index << endl;
}

void reset_helper(Node* root){
    if(root == NULL)
        return;
    reset(root->left);
    reset(root->right);
    delete root;
}

void reset(Node* root){
    if(!deleted){
        root = NULL;//reset_helper(root);    
    }
    deleted = true;
}
//this function checks which command the input invokes
//then check if the input has the correct number of param
//return 0 -> load 1 -> locate 2 -> new 3 -> end -1 ->bad command
int check_command(vector<string> &niceString){
    string terminate = "end";
    string loader = "load";
    string locater = "locate";
    string reset = "new";
    if(case_compare(string_char(niceString.at(0)),string_char(loader)) == 0){
        if(niceString.size() == 2){
            return 0;
        }else{
            cout<< "ERROR: Invalid command"<<endl;
            return -1;
        }   
    }
    else if(case_compare(string_char(niceString.at(0)),string_char(locater))==0){
        if(niceString.size() == 3){
            return 1;
        }else{
            cout<< "ERROR: Invalid command"<<endl;
            return -1;
        }
    }
    else if(case_compare(string_char(niceString.at(0)),string_char(reset))==0){
        if(niceString.size() == 1){
            return 2;
        }else{
            cout<< "ERROR: Invalid command"<<endl;
            return -1;
        }
    }
    else if(case_compare(string_char(niceString.at(0)),string_char(terminate))==0){
        if(niceString.size() == 1){
            return 3;
        }else{
            cout<< "ERROR: Invalid command"<<endl;
            return -1;
        }
    }
    cout<< "ERROR: Invalid command"<<endl;
    return -1;
}

//this function parses the input string into array of strings
void parser(std::string raw_input, vector<string> &niceString){
    //use space to separate new char, then pushback to vector
    //stringstream ss(raw_input);
    stringstream ss(raw_input);
    string word;
    while (ss >> word) {
        niceString.push_back(word);
    }
}
int main()
{
    std::string input;
    string terminate = "end";
    vector<string> niceString;
    int check;
    do{
        std::cout << ">";
        getline (cin, input);
        parser(input,niceString);
        check = check_command(niceString);
        //insert(root, string_char("hello"), 3);
        
        switch(check){
            case 0:
                load_file(niceString.at(1));
                break;
            case 1:
                locate_word(niceString.at(1),niceString.at(2));
                break;
            case 2:
                reset(root);
                break;
        }
        //load_file(input);
        niceString.clear();
    } while(case_compare(string_char(input),string_char(terminate))!= 0);
    reset(root);
    return 0;
}
