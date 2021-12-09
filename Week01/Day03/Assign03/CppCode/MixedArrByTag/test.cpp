#include <iostream>
#include <cassert>

using namespace std;

int main(){
	int x = 5;
	float y = 100.10;
	uint32_t* ptr;
	x = static_cast<int>(y);
	ptr = reinterpret_cast<uint32_t*>(y);
	cout << x << endl;
	cout << ptr << endl;
	return 0;
}
