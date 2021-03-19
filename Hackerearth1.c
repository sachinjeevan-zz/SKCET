/*
Roy is trying to develop a widget that shows Trending Topics (similar to Facebook) on the home page of HackerEarth Academy.
He has gathered a list of N Topics (their IDs) and their popularity score (say z-score) from the database. Now z-score change everyday according to the following rules:

When a topic is mentioned in a 'Post', its z-score is increased by 50.
A 'Like' on such a Post, increases the z-score by 5.
A 'Comment' increases z-score by 10.
A 'Share' causes an increment of 20.
Now the Trending Topics are decided according to the change in z-score. One with the highest increment comes on top and list follows.
Roy seeks your help to write an algorithm to find the top 5 Trending Topics.
If change in z-score for any two topics is same, then rank them according to their ID (one with higher ID gets priority). It is guaranteed that IDs will be unique.

Input format:
First line contains integer N
N lines follow
Each contains 6 space separated numbers representing Topic ID, current z-score - Z, Posts - P, Likes - L, Comments - C, Shares - S

Output format:
Print top 5 Topics each in a new line.
Each line should contain two space separated integers, Topic ID and new z-score of the topic.

Constraints:
1 ≤ N ≤ 106
1 ≤ ID ≤ 109
0 ≤ Z, P, L, C, S ≤ 109

Sample Test Explanation:
enter image description here

Now sort them according to the change in z-score. Change in z-score for IDs 999, 1001, 1002, 1003 is 100, so sort them according to their ID (one with the higher ID gets priority). Similarly proceed further.

After you get the top 5 list of Topic IDs according to the above criteria, find the new z-score from the table for each ID.

Sample Input
8
1003 100 4 0 0 0
1002 200 6 0 0 0
1001 300 8 0 0 0
1004 100 3 0 0 0
1005 200 3 0 0 0
1006 300 5 0 0 0
1007 100 3 0 0 0
999 100 4 0 0 0

Sample Output
1003 200
1002 300
1001 400
999 200
1007 150


*/
#include<stdio.h>
#include<stdlib.h>
struct BHeap
{
    long long int *arr;
    long long int *zscore;
    long long int *id;
    long long int size;
    long long int n;
};
void BinaryHeap(struct BHeap* heap,long long int child,long long int parent)
{
    if(child!=0 && heap->arr[parent] < heap->arr[child])
    { 
        long long int temp = heap->arr[parent];
        heap->arr[parent] = heap->arr[child];
        heap->arr[child] = temp;

        temp = heap->id[parent];
        heap->id[parent] = heap->id[child];
        heap->id[child] = temp;

        temp = heap->zscore[parent];
        heap->zscore[parent] = heap->zscore[child];
        heap->zscore[child] = temp;

        BinaryHeap(heap,parent,(parent-1)/2);
    }
    else if(child!=0 && heap->arr[parent] == heap->arr[child])
    {
        if(heap->id[parent] < heap->id[child])
        {
            long long int temp = heap->arr[parent];
        heap->arr[parent] = heap->arr[child];
        heap->arr[child] = temp;

        temp = heap->id[parent];
        heap->id[parent] = heap->id[child];
        heap->id[child] = temp;

        temp = heap->zscore[parent];
        heap->zscore[parent] = heap->zscore[child];
        heap->zscore[child] = temp;

        BinaryHeap(heap,parent,(parent-1)/2);
        }
    }
}
long long int extractMax(struct BHeap* heap,long long int parent)
{// 
    if(parent==0)
    {
       long long int temp = heap->arr[0];
       heap->arr[0] = heap->arr[heap->n-1];
       heap->arr[heap->n-1] = temp;

       temp = heap->id[0];
       heap->id[0] = heap->id[heap->n-1];
       heap->id[heap->n-1] = temp;

       temp = heap->zscore[0];
       heap->zscore[0] = heap->zscore[heap->n-1];
       heap->zscore[heap->n-1] = temp;

       heap->n -=1 ;
    }
    long long int max;
    long long int left = (parent*2)+1;
    long long int right = (parent*2)+2;
    if(left<heap->n && right<heap->n)
    {
        if(heap->arr[left]==heap->arr[right])
        {
            if(heap->id[left]>heap->id[right])
            {
                max = left;
            }
            else
            {
                max = right;
            }
        }
        else{
            max = heap->arr[left]>heap->arr[right]?left:right;
        }
    }
    else if(left<heap->n)
    {
        max = left;
    }
    else
    {
        return heap->arr[heap->n];
    }
    if(heap->arr[parent] < heap->arr[max])
    {
        long long int temp = heap->arr[parent];
        heap->arr[parent] = heap->arr[max];
        heap->arr[max] = temp;

        temp = heap->id[parent];
        heap->id[parent] = heap->id[max];
        heap->id[max] = temp;

        temp = heap->zscore[parent];
        heap->zscore[parent] = heap->zscore[max];
        heap->zscore[max] = temp;

        extractMax(heap,max);
    }
    else if(heap->arr[parent] == heap->arr[max])
    {
        if(heap->id[parent] < heap->id[max])
        {
        long long int temp = heap->arr[parent];
        heap->arr[parent] = heap->arr[max];
        heap->arr[max] = temp;

        temp = heap->id[parent];
        heap->id[parent] = heap->id[max];
        heap->id[max] = temp;

        temp = heap->zscore[parent];
        heap->zscore[parent] = heap->zscore[max];
        heap->zscore[max] = temp;
        extractMax(heap,max);
        }
    }
    else
    {
        return heap->arr[heap->n];
    }
}
int main()
{
    struct BHeap heap;
    scanf("%lld",&(heap.size));
    heap.n = 0;
    heap.arr = (long long int*)malloc(sizeof(long long int)*heap.size);
    heap.zscore = (long long int*)malloc(sizeof(long long int)*heap.size);
    heap.id = (long long int*)malloc(sizeof(long long int)*heap.size);
    long long int a,b,c,d,e,f;
    for(long long int i=0;i<heap.size;i++)
    {
        scanf("%lld %lld %lld %lld %lld %lld",&a,&b,&c,&d,&e,&f);
        long long int curr_zcore = (c*50 + d*5 + e*10 + f*20);
        heap.arr[i] = curr_zcore - b;
        heap.id[i] = a;
        heap.zscore[i] = curr_zcore;
        heap.n += 1;
        BinaryHeap(&heap,i,(i-1)/2);
    }
   for(long long int i=0;i<5&&heap.n!=0;i++)
   {
   extractMax(&heap,0);
   printf("%lld %lld\n",heap.id[heap.n],heap.zscore[heap.n]);
   }


}
