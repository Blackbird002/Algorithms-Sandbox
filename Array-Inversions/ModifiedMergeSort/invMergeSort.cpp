/*
Riad Shash (Ray)
Modified Merge Sort that counts the number of Inversions.

Inversion: Let A[1..n] be an array of size n. If index i < j &
A[i] > A[j] then the pair (A[i],A[j]) is an inversion

O(nlog(n)) - Much better! We can still do better...
*/

#include <iostream>
#include <cassert>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>

//The number of random numbers to generate...
const int MaxNum = 10000;

template <class T>
void printArray(T array[], const int& arraySize);
template <class T>
void compareArray(T actual[], T expected[], const int& n);
template <class T>
int mergeCountInv(T array[], int p, int q, int r, T sentinelVal);
template <class T>
int mergeSortCountInv(T array[], int p, int r, T sentinelVal);
void testMerge();
void testMergeSortCase1();
void testMergeSortCase2();
void testMergeSortCase3();

template <class T>
void printArray(T array[], const int& arraySize) {
	std::cout << "{ ";
	for (int i = 0; i < arraySize; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << "}";
}

template <class T>
void compareArray(T actual[], T expected[], const int& n) {
	for (int i = 0; i < n; i++)
		assert(actual[i] == expected[i]);
}

/*
	Axiliary function in Merge Sort Count Inversions 
	p,q,r are indices into the array (int)
	sentinelVal is the value that is greater than all the elements
 */
template <class T>
int mergeCountInv(T array[], int p, int q, int r, T sentinelVal) {

	int n1 = q - p + 1;
	int n2 = r - q;
	//std::cout << "n1 = " << n1 << " n2 = " << n2 << std::endl;
	T* L = new T[n1 + 1];
	T* R = new T[n2 + 1];
	for (int i = 0; i < n1; i++)
		L[i] = array[p + i];
	for (int j = 1; j <= n2; j++)
		R[j - 1] = array[q + j];
	L[n1] = sentinelVal;
	R[n2] = sentinelVal;
	//printArray<T>(L, n1 + 1);
	//printArray<T>(R, n2 + 1);
	int i = 0;
	int j = 0;
	int invCount = 0;
	for (int k = p; k <= r; k++) {
		if (L[i] <= R[j]) {
			array[k] = L[i];
			i++;
		}
		else {
			array[k] = R[j];
			j++;
			invCount += n1 - i;
		}
	}
	delete[] L;
	delete[] R;
	return invCount;
}

//Modified Merge Sort that counts the number of Inversions
template <class T>
int mergeSortCountInv(T array[], int p, int r, T sentinelVal) {
	int invCount = 0;
	if (p < r) {
		int q = floor((p + r) / 2);
		invCount += mergeSortCountInv<T>(array, p, q, sentinelVal);
		invCount += mergeSortCountInv<T>(array, q + 1, r, sentinelVal);
		invCount += mergeCountInv<T>(array, p, q, r, sentinelVal);
	}
	return invCount;
}

void testMerge() {
	int actArray[8] = { 2,4,5,7,1,2,3,6 };
	int expArray[8] = { 1,2,2,3,4,5,6,7 };
	int x = mergeCountInv<int>(actArray, 0, 3, 7, 1000);
	compareArray<int>(actArray, expArray, 8);
	std::cout << "Merge Test passed!\n";
	std::cout << "Number of Inversions: " <<x <<std::endl;
}

void testMergeSortCase1() {
	int actual[10] = { 9,4,2,5,7,8,1,0,6,3 };
	int expected[10] = { 0,1,2,3,4,5,6,7,8,9 };
	int x = mergeSortCountInv<int>(actual, 0, 9, 10000);
	compareArray<int>(actual, expected, 10);
	std::cout << "Merge Sort Test passed!\n";
	std::cout << "Number of Inversions: " <<x <<std::endl;
}

void testMergeSortCase3() {
	int actual[8] = { 1,20,6,7,5,8,11,3 };
	int expected[8] = { 1,3,5,6,7,8,11,20 };
	int x = mergeSortCountInv<int>(actual, 0, 7, 10000);
	compareArray<int>(actual, expected, 8);
	std::cout << "Merge Sort Case 3 passed!\n";
	std::cout << "Number of Inversions: " <<x <<std::endl;
}

void testMergeSortCase2() {
	double randomNum = 0;
	double actual[MaxNum];
	double expected[MaxNum];

	//Generates a seed based on elapsed time since Coordinated Universal Time (UTC) 
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//Uses the 32 - bit Mersenne Twister Random Number Engine
	std::mt19937 randomEngine(seed);
	std::uniform_real_distribution<double> myDistribution(-100000, 100000);

	for (int i = 0; i < MaxNum; i++)
	{
		randomNum = myDistribution(randomEngine);
		actual[i] = randomNum;
		expected[i] = randomNum;
	}
	//Actual array is sorted here
	int x = mergeSortCountInv<double>(actual, 0, MaxNum - 1, 200000);

	//Expected Array is sorted here
	int n = sizeof(expected) / sizeof(expected[0]);
	std::sort(expected, expected + n);

	//Checks if array contents are exactly in the same order
	compareArray<double>(actual, expected, MaxNum);
	std::cout << "Merge Sort Case 2 passed!\n";
	std::cout << "Number of Inversions: " <<x <<std::endl;
}

int main(int argc, char** argv) {
	std::cout << "Inversions (modified Merge Sort)\n";
	testMerge();
	testMergeSortCase1();
	testMergeSortCase2();
	testMergeSortCase3();
	return 0;
}
