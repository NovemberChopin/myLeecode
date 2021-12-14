/*
 *快速排序：1、设k=a[0]，将k挪到适当位置，使得比k小的元素都在k左边，比k大的元素都在k右边，
                和k相等的，不关心在k左右出现均可(0(n)时间完成)
            2、把k左边的部分快速排序
            3、把k右边的部分快速排序
 */
#include <iostream>
using namespace std;

int Partition(int A[], int low, int high) {
    int povit = A[low];
    while (low < high) {
        while (low < high && A[high] >= povit) {
            high--;
        }
        A[low] = A[high];
        while (low < high && A[low] <= povit) {
            low++;
        }
        A[high] =  A[low];
    }
    A[low] = povit;
    return low;
}

void QuickSort(int A[], int low, int high) {
    if (low < high) {
        int pivot = Partition(A, low, high);
        QuickSort(A, low, pivot-1);
        QuickSort(A, pivot+1, high);
    }
}

int a[10] = {25,96,65,48,51,24,12,39,91,24};
int b[10];
int main()
{
    int size = sizeof(a)/sizeof(int);
    QuickSort(a,0,size-1);//进行快速排序
    for(int i= 0; i<size; ++i)
    {
        cout << a[i] << ",";
    }
    cout << endl;
    return 0;
}