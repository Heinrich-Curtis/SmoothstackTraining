#include <iostream>
#include <cassert>

using namespace std;

int main(){
	int x = 5;
	float y = 100.10;
	float* py = &y;
	int z = *((int*)py);
	uint32_t* ptr;
	//x = (0xFFFFFFFF & y);
	
	//x = static_cast<int>(y);
	//ptr = reinterpret_cast<uint32_t*>(y);
	cout << "z" << z << endl;
	assert(~(z^y)); 
	cout << "x" << x << endl;
	cout << ptr << endl;
	return 0;
}
