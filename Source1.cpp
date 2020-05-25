#include <cilk/cilk.h>
#include <cilk/reducer_ostream.h> 
#include <iostream>
#include <string>
#include <chrono>
#include <math.h>
#include <cilk/reducer.h>
#include <cilk/cilk_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

cilk::reducer<cilk::op_ostream> r(std::cerr);
using namespace std;

int main()
{
	int size = 10, multiplicator = 5;
	vector <int> myVector(size);
	srand(time(NULL));
	generate(myVector.begin(), myVector.end(), []() { return rand() % 20; });

	cilk_for(int i = 0; i < myVector.size(); i++) {
		myVector[i] *= multiplicator;
	}
	cout << "Vector after calculating" << endl;

	cilk_for(int i = 0; i < myVector.size(); i++) {
		*r << myVector[i] << "\t";
	}
	return 0;
}
