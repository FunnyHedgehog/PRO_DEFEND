#include <tbb/task_scheduler_init.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include <tbb/tick_count.h>
#include <limits>
#include <cstddef>
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <math.h>
using namespace tbb;
using namespace std;

class MultiplyService
{
public:
	MultiplyService(std::vector<int> myVector, int multiplicator) : myVector_(myVector.data()), multiplicator_(multiplicator){}

	void operator()(const blocked_range<size_t > &r) const
	{
		for (size_t i = r.begin(); i < r.end(); i++)
		{
			myVector_[i] *= multiplicator_;
		}
	}

private:
	int *const myVector_;
	int const multiplicator_;
};

int main()
{
	int size = 10, multiplicator = 5;
	vector <int> myVector(size);
	srand(time(NULL));
	generate(myVector.begin(), myVector.end(), []() { return rand() % 20; });

	task_scheduler_init init(3);
	parallel_for(blocked_range<size_t>(0, size), MultiplyService(myVector, multiplicator), auto_partitioner());
}