#include "wl.h"

using namespace std; // this is a using directive telling the compiler to check the std namespace when resolving identifiers with no prefix


char* string_char(string str){
     return const_cast<char*>(str.c_str());
}
void load_file(std::string file){
    string  myText;
    //converts file name to char*
    char* file_char = string_char(file);
    int fd = open(file_char, O_RDONLY);
    if (fd == -1){
        cout<< "ERROR: Invalid command"<<endl;
    }
    close(fd);
}

int locate_word(string word, string occurance){
    return 0;

}

void reset(){

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
        if(check == -1)
            continue;
        switch(check){
            case 0:
                load_file(niceString.at(1));
                break;
            case 1:
                locate_word(niceString.at(1),niceString.at(2));
            case 2:
                reset();
        }
        //load_file(input);
        niceString.clear();
    } while(case_compare(string_char(input),string_char(terminate))!= 0);
    return 0;
}
