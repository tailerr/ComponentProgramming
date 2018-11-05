#include <project/Task02/Vector.h>
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>


using namespace std;

int main(){
	
	Vector<ofstream> v1 = Vector<ofstream>();
	
	v1.push_back(ofstream("1.txt", ios_base::out | ios_base::trunc));
	v1.push_back(ofstream("2.txt", ios_base::out | ios_base::trunc));
	v1.push_back(ofstream("3.txt", ios_base::out | ios_base::trunc));

	random_device rd;
	shuffle(v1.begin(), v1.end(), rd);

	int n = 1;
	for (auto& iter : v1){
		iter << n;
		n++;
		iter.close();
	}

	return 0;
}
