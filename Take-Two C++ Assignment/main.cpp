/*
    Program that reads in a list of words from a file and outputs
    all the unique words and the frequencies with which they occur
    in the file using std::set
*/
#include <iostream>
#include <set>
#include <utility>
#include <functional>
#include <fstream>
#include <algorithm>
#include <cassert>

/*
    class that holds the data so we don't have to have ugly pair set templates
*/
struct countWord{
    std::string str;
    //we want this to be modifiable even through a set iterator
    mutable int count;
    //default constructor
    countWord():str(""),count(0){
    }
    //param constructor for return from find
    countWord(const std::string& str, const int& count):str(str),count(count){
    }
};

/*
     comparator for sorting by freq and then name, used for final display
*/
typedef struct fComp{
    bool operator()(const countWord& l, const countWord& r) const{
        if (l.count == r.count){
            return l.str < r.str;
        }
        return l.count > r.count;
    }
} fComp;

/*
    comparator for sorting by name for set find
*/

typedef struct aComp{
    bool operator()(const countWord& l, const countWord& r) const{
        return l.str < r.str;
    }
} aComp;

/*
    change a string into it's lower case equivalent so we're case insensitive
*/
std::string myToLower(std::string str){
    char* cstr = str.data();
    int strsize = str.length();
    for (int i = 0; i < strsize; ++i){
        if (cstr[i] <= 'Z'){cstr[i] += ('a'-'A');}
    }
    std::string res(cstr);
    return res;
}


/*
    Here is the naive solution: a single-threaded version of the program
*/
std::set<countWord, aComp> countWords(std::ifstream& stream){
    std::set<countWord, aComp> result;
    std::string str;
    //unsigned int wordCount = 0;
    while (stream >> str){
        //wordCount++;
        //convert the word to all lower case
        std::string lilString = myToLower(str);
        //check if it's in the set
        std::set<countWord>::iterator it;
        countWord word(lilString,1);
        it = result.find(word);
        //if it is, add the frequencies into the one in the set
        if (it != result.end()){
            it->count++;
        }
        //if it isn't, add a new pair to the set
        else{
            result.insert(word);
        } 
    }
    //std::cout<< "Word count was "<<wordCount<<std::endl;
    return result;

}

/*
    main program calls the different program versions and compares their
    output
*/
int main(int argc, char** argv){
    //check invocation
    if (argc != 2){
        std::cout << "Incorrect usage. Must provide an input file as arg"<<std::endl;
        return 1;
    }
    std::ifstream inputFile;
    //open the input file or fail
    inputFile.open(argv[1]);
    if (!inputFile.is_open()){
        std::cout << "Failed to open file " << argv[1] << std::endl;
        return 2;
    }
    //call naive on it
    std::set<countWord, aComp> alphaSet = countWords(inputFile);
    //resort the result set into a new set that's sorted by frequency
    //using a new less and iterators into the old set
    std::set<countWord, fComp> freqSet(alphaSet.begin(),alphaSet.end());
    //print out freqSet to the output file
    std::ofstream outputFile;
    outputFile.open("result1.txt",std::ostream::out);
    for (const countWord& pair : freqSet){
        outputFile << pair.str <<" "<< pair.count << std::endl;
    }
    //close resources and we're done
    inputFile.close();
    outputFile.close();
    return 0;
}
