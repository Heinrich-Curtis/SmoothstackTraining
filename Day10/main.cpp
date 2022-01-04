/*
 * Program that demonstrates the singleton and factory design patterns
 */	
#include <iostream>
#include <cassert>
using namespace std;


class Person {
	private:
		int index;	
		//default construction is not allowed, so delete it here
		Person() = delete;
		
		//construct a person with a name and an index, used when
		//we actually allocate for a unique person
		Person(string newName,int newIndex):index(newIndex), 
			name(newName),count(1){
			//empty body, initializer list did it
		}

		//construct a person from another person, used to replace 
		//an existing person and increment their count
		Person(Person* p): index(p->index),name(p->name),
			count(++(p->count)){
			//empty body
			}
	public:
		string name;
		int count;
		static Person* persons[10];
		static Person* getPerson(string name){
			//check the array for a person with the same name. If we find
			//one, construct a new Person from the old person that has an
			//incremented count, then delete the old one from the array and
			//put the new one in it's place
			int lastIndex = 0;
			for (int i =0; i < 10; i++){
				if (persons[i] == nullptr) {
					lastIndex = i;
				break;	
				}
		
				if (persons[i]->name == name){
					//here's where we construct a new one
					//from the old one, 
					Person* p = new Person (persons[i]);
					delete persons[i];
					persons[i] = p;
					return p;
				}
			}
			//if we're here, the name isn't in the array and lastIndex
			//points to the first open slot in the array
			Person* p = new Person(name,lastIndex);
			persons[lastIndex] = p;
			return p;	
		}
		
};

//have to define this outside the class definition
Person* Person::persons[10];

int main(){
	//declare an array of names here
	string names[5] = {"Jeff", "Bob", "Jill", "Steve", "Bob"}; 
	assert(Person::persons[0] == nullptr);
	for (int ii = 0; ii < 5 ; ii++){
		//get all the people
		Person::getPerson(names[ii]);
	}
	
	//check the persons array, and clean it up when we're done
	for (Person* p : Person::persons){
		if (p == nullptr) break;
		cout << p->name << " : " << p->count <<endl; 
	}
	//clean up heap memory
	int i = 0;
	while (Person::persons[i] != nullptr){
		delete Person::persons[i];
		i++;
	}
	

}
