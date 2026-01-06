#include <stdio.h>

void swap(int *a,int *b){
    int t=*a;
    *a=*b;
    *b=t;
}

int partition(int arr[],int left,int right){
    int pivot=arr[right];
    int i=left-1;
    int j;

    for(j=left;j<right;j++){
        if(arr[j]<=pivot){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    
    swap(&arr[i+1],&arr[right]);
    return i+1;
}

void quickSort(int arr[],int left,int right){
    if(left<right){
        int pi=partition(arr,left,right);
        quickSort(arr,left,pi-1);
        quickSort(arr,pi+1,right);
    }
}

int main(){
    int n,i;
    int arr[50];
    printf("Enter number of elements:");
    scanf("%d",&n);
    printf("Enter elements:\n");

    for(i=0;i<n;i++)
        scanf("%d",&arr[i]);

    quickSort(arr,0,n-1);
    printf("Sorted array:\n");

    for(i=0;i<n;i++)
        printf("%d ",arr[i]);
    return 0;
}
