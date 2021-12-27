#include <iostream>
using namespace std;

void Merge(int a[], int s, int m, int e, int temp[]) {
    int pb = 0;
    int p1 = s, p2 = m+1;
    while (p1 <= m && p2 <= e) {
        if (a[p1] < a[p2])
            temp[pb++] = a[p1++];
        else
            temp[pb++] = a[p2++];
    }
    while (p1 <= m) 
        temp[pb++] = a[p1++];
    while (p2 <= e)
        temp[pb++] = a[p2++];
    for (int i=0; i<e-s+1; i++)
        a[s+i] = temp[i];
}

void MergeSort(int a[], int s, int e, int temp[]) {
    if (s < e) {
        int m = s + (e-s)/2;
        MergeSort(a, s, m, temp);
        MergeSort(a, m +1, e, temp);
        Merge(a, s, m, e, temp);
    }
}

int a[10] = {25,96,65,48,51,24,12,39,91,24};
int b[10];
int main()
{
    int size = sizeof(a)/sizeof(int);
    MergeSort(a,0,size-1,b);//进行归并排序
    for(int i= 0; i<size; ++i)
    {
        cout << a[i] << ",";
    }
    cout << endl;
    return 0;
}