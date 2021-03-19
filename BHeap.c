#include<stdio.h>
#include<stdlib.h>
struct BHeap
{
    int *arr;
    int size;
    int n;
};
void BinaryHeap(struct BHeap* heap,int child,int parent)
{
    if(child!=0 && heap->arr[parent] > heap->arr[child])
    { 
        int temp = heap->arr[parent];
        heap->arr[parent] = heap->arr[child];
        heap->arr[child] = temp;
        BinaryHeap(heap,parent,(parent-1)/2);
    }
}
int extractMin(struct BHeap* heap,int parent)
{// 
    if(parent==0)
    {
       int temp = heap->arr[0];
       heap->arr[0] = heap->arr[heap->n-1];
       heap->arr[heap->n-1] = temp;
       heap->n -=1 ;
    }
    int min;
    int left = (parent*2)+1;
    int right = (parent*2)+2;
    if(left<heap->n && right<heap->n)
    {
        min = heap->arr[left]<heap->arr[right]?left:right;
    }
    else if(left<heap->n)
    {
        min = left;
    }
    else
    {
        return heap->arr[heap->n];
    }
    if(heap->arr[parent] > heap->arr[min])
    {
        int temp = heap->arr[parent];
        heap->arr[parent] = heap->arr[min];
        heap->arr[min] = temp;
        extractMin(heap,min);
    }
    else
    {
        return heap->arr[heap->n];
    }
}
int main()
{
    struct BHeap heap;
    scanf("%d",&(heap.size));
    heap.n = 0;
    heap.arr = (int*)malloc(sizeof(int)*heap.size);
    int x;
    for(int i=0;i<heap.size;i++)
    {
        scanf("%d",&x);
        heap.arr[i] = x;
        heap.n += 1;
        BinaryHeap(&heap,i,(i-1)/2);
    }

    for(int i=0;i<heap.n;i++)
    {
        printf("%d ",heap.arr[i]);
    }
    while(heap.n>0)
    {
    int ans = extractMin(&heap,0);
    }
     for(int i=0;i<heap.size;i++)
    {
        printf("%d ",heap.arr[i]);
    }

}
