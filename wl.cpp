#include "wl.h"

using namespace std; // this is a using directive telling the compiler to check the std namespace when resolving identifiers with no prefix


void load_file(std::string file){
    std::string myText;

    // Read from the text file
    ifstream myReadFile(file);
    if(myReadFile.fail()){
        //File does not exist code here
        cout<< "ERROR: Invalid command"<<endl;
    }
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (myReadFile, myText)) {
        // Output the text from the file
        std::cout << myText;
    }
    myReadFile.close();
}


//this function checks which command the input invokes
//then check if the input has the correct number of param
//return 0 -> load 1 -> locate 2 -> new 3 -> end -1 ->bad command
int check_command(vector<string> &niceString){
    string terminate = "end";
    string loader = "load";
    string locater = "locate";
    string reset = "new";
    if(case_compare(niceString.at(0),loader)){
        if(niceString.size() == 2){
            return 0;
        }else{
            cout<< "ERROR: Invalid command"<<endl;
            return -1;
        }   
    }
    else if(case_compare(niceString.at(0),locater)){
        if(niceString.size() == 3){
            return 1;
        }else{
            cout<< "ERROR: Invalid command"<<endl;
            return -1;
        }
    }
    else if(case_compare(niceString.at(0),reset)){
        if(niceString.size() == 1){
            return 2;
        }else{
            cout<< "ERROR: Invalid command"<<endl;
            return -1;
        }
    }
    else if(case_compare(niceString.at(0),terminate)){
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
    do{
        std::cout << ">";
        getline (cin, input);
        parser(input,niceString);
        check_command(niceString);
        Node* myNode = new Node(const_cast<char*>(terminate.c_str()),3);
        cout << myNode->index->at(0) << endl;
        //string test[3] = parser(input);
        //load_file(input);
        niceString.clear();
    } while(!case_compare(input,terminate));
    return 0;
}
