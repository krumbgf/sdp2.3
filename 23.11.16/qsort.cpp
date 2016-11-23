#include <iostream>
#include <time.h>
#include <random>
#include <algorithm>

using namespace std;

template <typename T>
int partition(T* arr, int first, int last)
{
    swap(arr[first],arr[first+(last-first)/2]);
    int  p = first;
    T pivot = arr[first];
    for(int i=first+1; i<=last;i++)
    {
        if(arr[i] <= pivot)
        {
            p++;
            swap(arr[i], arr[p]);
        }
    }
    swap(arr[p], arr[first]);
    return p;
}

template <typename T>
void QuickSort(T* arr, int first, int last)
{
    if(first < last)
    {
        int p = partition(arr, first, last);
        QuickSort(arr, first, p-1);
        QuickSort(arr, p+1, last);
    }
}

int main()
{
	const int SIZE = 50000000;
	int* a = new int[SIZE];
	mt19937 random(time(0));
	uniform_int_distribution<int> gen(-SIZE,SIZE);
	auto rnd = [&random,&gen](){return gen(random);};
	generate_n(a,SIZE,rnd);
    long start = clock();

	QuickSort(a,0,SIZE-1);

	cout<<(clock()-start)/1000.0<<endl;

	for(int i=0;i<SIZE-1;i++)
	{
        if(a[i]>a[i+1])
            cout<<a[i]<<" ";
	}
    delete []a;
	return 0;
}


