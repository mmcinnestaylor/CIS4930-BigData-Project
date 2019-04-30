#include<chrono>
#include<iomanip>
#include<ctime>
#include<iostream>
#include<omp.h>
using namespace std::chrono;

// Function to find contiguous sub-array with the largest sum
// in given set of integers

int kadane(int arr[], int n)
{

	// stores maximum sum sub-array found so far
	int max_so_far = 0;

	// stores maximum sum of sub-array ending at current position
	int max_ending_here = 0;

	#pragma omp parallel for default (none) shared(arr,n,max_so_far) private(max_ending_here)
	// traverse the given array
	for (int i = 0; i < n; i++)
	{
		// update maximum sum of sub-array "ending" at index i (by adding
		// current element to maximum sum ending at previous index i-1)

		max_ending_here = max_ending_here + arr[i];
		
		// if maximum sum is negative, set it to 0 (which represents
		// an empty sub-array)
		max_ending_here = std::max(max_ending_here, 0);

		// update result if current sub-array sum is found to be greater
		#pragma omp critical
		{
		max_so_far = std::max(max_so_far, max_ending_here);
		}
	}

	return max_so_far;

}

// main function
int main()
{
	//int arr[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	//int n = sizeof(arr)/sizeof(arr[0]);
	high_resolution_clock::time_point t1, t2;
  duration<double> time_span;

	int i=0, n=0;

	std::cin >> n;

	int * arr = new int[n];

	for(i=0; i < n; i++)
	    std::cin >> arr[i];
	t1 = high_resolution_clock::now();
	std::cout << "The sum of contiguous sub-array with the largest sum is " <<
			kadane(arr, n);
	t2 = high_resolution_clock::now();
	time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout << std::endl << std::fixed << std::showpoint << std::setprecision(8)
		<< "Runtime: " << time_span.count() << std::endl;

	delete [] arr;

	return 0;
}
