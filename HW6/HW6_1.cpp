#include <iostream>
#include <vector>
using namespace std;

// 合并两个有序子序列，并统计逆序对个数
int merge(vector<int>& A, int left, int mid, int right) 
{
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    int count = 0;

    while (i <= mid && j <= right) {
        if (A[i] <= A[j]) {
            temp[k++] = A[i++];
        } else {
            temp[k++] = A[j++];
            count += (mid - i + 1); // 统计逆序对个数
        }
    }

    while (i <= mid) {
        temp[k++] = A[i++];
    }

    while (j <= right) {
        temp[k++] = A[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++) {
        A[i] = temp[k];
    }

    return count;
}

// 归并排序，并统计逆序对个数
int mergeSort(vector<int>& A, int left, int right) 
{
    if (left >= right) {
        return 0;
    }

    int mid = left + (right - left) / 2;
    int count = mergeSort(A, left, mid) + mergeSort(A, mid + 1, right);
    count += merge(A, left, mid, right);

    return count;
}

int main() 
{
    int n;
    cin>>n;
    while(n){
        vector<int> A(n);
        for(int i=0;i<n;i++){
            cin>>A[i];
        }
        cout<<mergeSort(A, 0, n - 1)<<endl;
        cin>>n;
    }

    return 0;
}