#include <iostream>
#include <cassert>

template <class T>
int countInversions(T A[], int n, bool printInversions);
void testcountInversionsCase1();
void testcountInversionsCase2();
void testcountInversionsCase3();

/*
    A[] is the array
    n is the number of elements in array

    O(n^2) - basically brute force...
*/
template <class T>
int countInversions(T A[], int n, bool printInversions){
    int reverseCount = 0;
    for(int i=0; i < n; i++){
        for(int j=i+1; j < n; j++){
            if(A[i] > A[j]){
                reverseCount++;
                if(printInversions) std::cout<<"(" <<A[i] <<"," <<A[j] <<") ";
            }
        }
    }
    if(printInversions) std::cout<<std::endl;
    return reverseCount;
}

void testcountInversionsCase1(){
    int A[] = { 2,4,1,3,5 };
    int n = sizeof(A) / sizeof(A[0]); 
    int expected = 3;
    int actual = countInversions<int>(A,n,false);
    assert(expected == actual);
    std::cout<<"Case 1 passed! \n";
}

void testcountInversionsCase2(){
    int A[] = { 1,20,6,4,5 };
    int n = sizeof(A) / sizeof(A[0]); 
    int expected = 5;
    int actual = countInversions<int>(A,n,true);
    assert(expected == actual);
    std::cout<<"Case 2 passed! \n";
}

void testcountInversionsCase3(){
    int A[] = { 1,20,6,7,5,8,11,3 };
    int n = sizeof(A) / sizeof(A[0]); 
    int expected = 13;
    int actual = countInversions<int>(A,n,true);
    assert(expected == actual);
    std::cout<<"Case 3 passed! \n";
}

int main(int argc, char** argv){
    std::cout<<"Testing Simple array inversion algorithm...\n";
    testcountInversionsCase1();
    testcountInversionsCase2();
    testcountInversionsCase3();
    return 0;
}
