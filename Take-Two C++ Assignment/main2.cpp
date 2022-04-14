/*
    Program that reads in a list of words from a file and outputs
    all the unique words and the frequencies with which they occur
    in the file using std::vector
*/
#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <fstream>
#include <algorithm>
#include <cassert>

/*
    comparator for sorting the pairs by frequency at the end
*/
struct countWord{
    std::string str;
    int count;

    //default
    countWord():str(""),count(0){
        
    }
    //param
    countWord(const std::string& str, const int& count):str(str),count(count){

    } 
};

/*
     comparator for sorting by freq and then name
*/
struct {
    bool operator()(const countWord& l, const countWord& r) const{
        if (l.count == r.count){
            return l.str < r.str;
        }
        return l.count > r.count;
    }
} fComp;

/*
    change a string into it's lower case equivalent
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
std::vector<countWord> naive(std::ifstream& stream){
    std::vector<countWord> result;
    std::string str;
    //unsigned int wordCount = 0;
    while (stream >> str){
        //wordCount++;
        //convert the word to all lower case
        std::string lilString = myToLower(str);
        //check if it's in the set
        std::vector<countWord>::iterator it;
        for(unsigned int i = 0; i < result.size(); ++i){
            it = result.end();
            std::string word = result[i].str;
            if (lilString == word){
                it = result.begin() + i;
                break;
            }
        }
        //if it is, add the frequencies into the one in the set
        if (it != result.end()){
            it->count += 1;
        }
        //if it isn't, add a new pair to the set 
        else{
            result.push_back(countWord(lilString, 1));
        }
    }
    //std::cout << "File had "<<wordCount <<" word in it."<<std::endl;
    return result;

}

/*
    main program calls the different program versions and compares their
    output
*/
int main(int argc, char** argv){
    if (argc != 2){
        std::cout << "Incorrect usage. Should be './wordCount <input file name>\
        '" <<std::endl;
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
    std::vector<countWord> alphaSet = naive(inputFile);
    countWord cW;
    std::sort(alphaSet.begin(),alphaSet.end(), fComp);
    //resort the result set into a new set that's sorted by frequency
    //using a new less and iterators into the old set
    std::vector<countWord> freqSet(alphaSet.begin(),alphaSet.end());
    //print out freqSet
    std::ofstream outputFile;
    outputFile.open("result2.txt",std::ofstream::out);
    for (const countWord& word : alphaSet){
        outputFile << word.str << " " << word.count << std::endl;
    }

    //close resources and we're done
    inputFile.close();
    outputFile.close();
    
    return 0;
}
