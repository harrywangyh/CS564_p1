#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
using namespace std; // this is a using directive telling the compiler to check the std namespace when resolving identifiers with no prefix
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


void load_file(std::string file){
    std::string myText;

    // Read from the text file
    ifstream myReadFile(file);
    if(myReadFile.fail()){
        //File does not exist code here
        cout<< "ERROR: Invalid command\n";
    }
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (myReadFile, myText)) {
        // Output the text from the file
        std::cout << myText;
    }
    myReadFile.close();
}


//this function parses the input string into array of strings
void parser(std::string raw_input, vector<string> &niceString){
    return 0;


}
int main()
{
    std::string input;
    string terminate = "end";
    vector<string> niceString;
    do{
        std::cout << ">";
        std::cin >> input;
        parser(input,niceString);
        //string test[3] = parser(input);
        //load_file(input);
    }
    while(!case_compare(input,terminate));
    return 0;
}
