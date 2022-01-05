/*
 *	Program that demonstrates the use of copy/move constructors/assignment
 *	operators to copy a sentence
 */

#include <iostream>
#include <cassert>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

class Sentence {
private:
	char* sentence = nullptr;
	std::vector<int> vsentence; //stores word offsets
	int populate_sentence(char* sent);
	int populate_vsentence(char* sent, int length, vector<int>& vsent);
public:
	Sentence (char* sent); //regular constructor
	//insert a deep copy constructor here
	Sentence(Sentence& s1);
	//insert a deep copy assignment operator here	
	Sentence& operator=(const Sentence& other);
	//insert a move constructor here
	Sentence(Sentence&& s1);
	//insert a move assignment operator here
	Sentence& operator=(Sentence&& other);
	char* data(); //returns the data for the sentence
	int num_words() const; //fetches the number of words
	std::string get_word(int n); //get nth word of sentence
	void replace(char* sent); //replace the sentence
	~Sentence(); //destroy allocated memory
};

//helper function that populates sentence from the char*
int Sentence::populate_sentence(char* sent){
	//set the private member
	int length = strlen(sent) + 1; // include the null temrinator
	sentence = new char[length];
	for (int i = 0; i < length; i++){
		sentence[i] = sent[i];
	}
	return length;
	
}
//private helper function that populates vsentence, just for code re-use in
//a couple places
int Sentence::populate_vsentence(char* sent, int length, vector<int>& vsent){
	bool inWord = false;
	for (int i = 0; i < length; i++){
		if (!inWord){
		 if (sent[i] != ' '){//not in a word, found a new word
			inWord = !inWord;
			vsent.push_back(i);
		 }
		}
		else{
			if (sent[i] == ' '){//in a word and found a space
				inWord = !inWord;
			}
				
		}
	}	
	
	return vsent.size();	
}

//definitions for functions
Sentence::Sentence (char* sent){
	cout << "Called parameterized constuctor" <<endl;
	int length = populate_sentence(sent);
	populate_vsentence(sentence, length, vsentence);

}

//deep copy constructor
Sentence::Sentence(Sentence& s1){
	cout << "Called deep copy constructor" << endl;
	//delete our data if it's being used
	if (this->sentence != nullptr){
		delete[] sentence;
		vsentence.clear();
	}
	//allocate for a new char[] and copy the sentence from s1
	int length = populate_sentence(s1.sentence);
	populate_vsentence(s1.sentence, length, vsentence);
	//populate vsentence
}

//move constructor
Sentence::Sentence(Sentence&& s1){
	cout << "Called move constructor" << endl;
	if (this->sentence != nullptr){
		delete[] sentence;
		vsentence.clear();
	}
	//now we steal all of s1's stuff
	sentence = s1.sentence;
	s1.sentence = nullptr;
	vsentence = std::move(s1.vsentence);
}

//deep copy assignment operator
Sentence& Sentence::operator=(const Sentence& other){
	cout << "Called copy assignment operator" << endl;
	if (this == &other) return *this;
	if (this->sentence != nullptr) {
		delete[] sentence;
		vsentence.clear();
	}
	int length = populate_sentence(other.sentence);
	populate_vsentence(other.sentence, length, vsentence);
	return *this;

}

// move assignment operator
Sentence& Sentence::operator=(Sentence&& other){
	cout << "Called move assignment operator" << endl;
	if (this == &other) return *this;
	if (this->sentence != nullptr) {
		delete[] sentence;
		vsentence.clear();
	}
	sentence = other.sentence;
	other.sentence = nullptr;
	vsentence = std::move(other.vsentence);
	return *this;
}

//just return the actual sentence, I'm assuming
char* Sentence::data(){
	return sentence;
}

//count the number of words by counting the spaces. This value would just
//be a data member in an ideal world.
int Sentence::num_words() const{
	return vsentence.size();
}

//get a particular word from the sentence. If there is no such word in
//the sentence, return an empty string (I'm not sure what behavior is
//desired here)
string Sentence::get_word(int n){
	//check the vector of offsets to make sure the nth word exists
	if (n > vsentence.size()){
	 return "";
	}
	//if it does, copy the word into it and return the word
	else{
		int wordStart = vsentence[n];
		if (n == vsentence.size()){//get the last word case
			int size = strlen(sentence) - wordStart;
			char res[size];
		     	strncpy(res, &sentence[wordStart], size);
			//make a string and return it
			string result(res);
			return result;
		}
		else{ //get a word in the middle case
			int size = vsentence[n + 1] - wordStart - 1;
			char res[size];
			strncpy(res, &sentence[wordStart], size);
			//make a string and return it
			string result(res);
			return result;

		}	
	}
	
	
}

//replace the entire sentence and reset vsentence
void Sentence::replace(char* sent){
	//just do everything the constructor does, except delete the old sentence
	//and clear the vector first
	delete[] sentence;
	vsentence.clear();
	int length = populate_sentence(sent);
	//find the offsets of each word and populate the vector
	populate_vsentence(sentence, length, vsentence);

	
}

//destructor
Sentence::~Sentence(){
	//empty the vector and delete it
	//delete sentence
	delete[] sentence;
	vsentence.clear(); // make sure this doesn't cause problems later
}



int main(){
	//test basic methods of the class
	char sentence[] = "The quick brown fox jumps over the lazy dog.";
	Sentence s1(sentence);
	assert(strlen(sentence) == strlen(s1.data()));
	assert(s1.num_words() == 9);
	char sentence2[] = "The slow orange fox jumps a lot.";
	s1.replace(sentence2);
	assert(strlen(sentence2) == strlen(s1.data()));
	assert(s1.num_words() == 7);
	
	//test copy constructor by explicitly calling it
	Sentence s2(s1);
	//the data should be exactly the same
	assert(!strcmp(s2.data(),s1.data()));
	//but changing s2 should not change s1's data	
	char sentence3[] = "Testing, one, two, three";
	s2.replace(sentence3);
	assert(strcmp(s2.data(),s1.data()));

	//test the copy assignment operator
	//have to initialize s3 first, then assign
	Sentence s3(sentence3);
	s3 = s2;
	//data is the same
	assert(!strcmp(s3.data(),s2.data()));
	//change s3's data but s2's is the same
	s3.replace(sentence);
	assert(strcmp(s3.data(), s2.data()));

	//test the move constructor by pulling from a temporary
	//doing this creates a warning about preventing copy elision.
	//After looking at the description of the warning, I think it's okay
	//so I leave it like this, but I had to disable the -Werror flag
	//I usually have on in my makefile. I'm not sure how important this
	//actually is
	Sentence s4(std::move(Sentence(sentence3)));
	assert(s4.num_words() == 4);
	assert(!strcmp(s4.data(),sentence3));

	//test the move assignment operator	
	//initiailize first
	Sentence s5(sentence);
	//now assign
	s5 = std::move(s4);
	//s4 is now empty
	assert(s4.num_words() == 0);
	assert(s4.data() == nullptr);
	//s5 has the data that used to live in s4
	assert(!strcmp(s5.data(),sentence3));	
	/* Before implementing the copy constructor,
	 * s2 just shallow copies s1's pointer, so when I replace
	 * s2's data, s1's data is changed as well.
	 * This also causes a double/multiple free  on program exit because s2's
	 * destructor deletes s1's pointer, which is then also deleted by s1's 
	 * pointer
	 */


	return 0;
}
