#include "the1.h"
#include <climits>


//You can add your own helper functions
struct HeapNode {
    // The element to be stored
    int element;
 
    // index of the array from which the element is taken
    int i;
 
    // index of the next element to be picked from the array
    int j;
};

void insertionSort(int* arr, int* output, long &comparison, long & swap, int size, int begin, int end);
void mergeRecursion(int* arr, int* output, int K, int size, long& comparison, long& swap, int& number_of_calls, int begin, int end, int offset, int realSize);
void merge(int *arr, int K, int *output, int offset, int size, long& comparison, long& swap, int& number_of_calls, int begin, int end, int scenario);
void swapMe(HeapNode* x, HeapNode* y);
int rval(int j, int* arr, int key, long &comparison, int begin);
long c;
long s;
class MinHeap
{
    public:
        HeapNode *heapArray;
        int heapSize;

    
        MinHeap(HeapNode *a, int size);
        void heapify(int);
        int left(int i) {return (2*i+1);}
        int right(int i) {return (2*i+2);}

        HeapNode getMin() {return heapArray[0];}

        void replaceMin(HeapNode x)
        {
            heapArray[0].element = x.element;
            heapArray[0].i = x.i;
            heapArray[0].j = x.j;
            heapify(0);

            

        }
};

// A utility function to swap two elements





  


MinHeap::MinHeap(HeapNode* a, int size)
{
    heapSize = size;
    heapArray = a;
    
    int i = (heapSize - 1) / 2;

    while (i >= 0)
    {
        heapify(i);
        i--;
    }

    
}

void MinHeap::heapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    
    if (l < heapSize)
    {
        
        if (heapArray[l].element != INT_MAX) c++;
        if (heapArray[l].element < heapArray[i].element) smallest = l;
    }

    
    if (r < heapSize)
    {
        
        if (heapArray[r].element != INT_MAX) c++;
        if (heapArray[r].element < heapArray[smallest].element) smallest = r;
    }

    if (smallest != i)
    {
        swapMe(&heapArray[i], &heapArray[smallest]);
        s++;
        
        heapify(smallest);
    }

}

void swapMe(HeapNode* x, HeapNode* y)
{
    HeapNode temp = *x;
    *x = *y;
    *y = temp;
    
   
}

void merge(int *arr, int K, int *output, int offset, int size, long& comparison, long& swap, int& number_of_calls, int begin, int end, int scenario)
{
    if (scenario == 0)
    {
        return;
    }
    HeapNode *heapArray;
    
    heapArray = new HeapNode[K];
    
    int index = 0;
    for (int i=0; i<K; i++)
    {
        
        heapArray[i].element = arr[index];
        heapArray[i].i = index;
        
        heapArray[i].j = index + 1;
        
        
        index+=offset;

        

    }

    

    

    MinHeap heap(heapArray, K);
    
    for (int i=0; i<K*offset; i++)
    {
        
        HeapNode root = heap.getMin();
        if (root.element != INT_MAX) output[i] = root.element;
       
        if (root.j < (root.i+offset))
        {
            root.element = arr[root.j];
            root.j++;
        }

        else
        {
            root.element = INT_MAX;
            
        }

        //heap.replaceMin(root);
        heap.heapArray[0] = root;
        
        heap.heapify(0);
        

    }

    

    

    delete [] heapArray;
}

int rval(int j, int* arr, int key, long &comparison, int begin)
{
    if (j>=begin)
    {
        comparison++;
        
        if (arr[j] > key) 
        {
            return 1;
        }
    }
    
    return 0;
}

void insertionSort(int* arr, int* output, long &comparison, long & swap, int size, int begin, int end) 
{
    
    //Your Code Here
    int i, key, j;
    
    
    for (i = begin+1; i < end+1; i++)
    {
        key = arr[i];
        
        j = i-1;
        
        while (rval(j, arr, key, comparison, begin))
        {
            
            
            
            arr[j+1] = arr[j];
            j = j-1;
            
            swap++;
        }
        
        
        
        arr[j+1] = key;
        
        
        
       
        
    }
    
    
}




void mergeRecursion(int* arr, int* output, int K, int size, long& comparison, long& swap, int& number_of_calls, int begin, int end, int offset, int realSize)
{
   
    if (size == 1)
    {
        return;
    }
    
    
    if (size < K)
    {
        
        insertionSort(arr, output, comparison, swap, size, begin, end);
        
        
        return;
    }

    else if (size == K)
    {
        
        offset = size / K;
        
        

        

        for (int i = 0; i < K; i+=1)
        {
            number_of_calls++;
            
            mergeRecursion(arr, output, K, 1, comparison, swap, number_of_calls, i, i+offset-1, offset, realSize);
            
        }

        merge(arr, K, output, offset, size, comparison, swap, number_of_calls, 0,size, 1);

        
    }
    
    
    else
    {
        
        
        for (int i = 0; i<(offset*K); i+=offset)
        {
            
            
            mergeRecursion(arr, output, K, offset, comparison, swap, number_of_calls, i, i+offset-1, offset, realSize);
            number_of_calls++;
        }
        
        
        
            
        // merge(arr, K, output, offset, comparison, swap, number_of_calls, begin, end);
        merge(arr, K, output, offset, size, comparison, swap, number_of_calls, 0,size, 1);
        
    }
  
}

int kWayMergeSortWithHeap(int* arr, int K, int size, long& comparison, long& swap)
{
  
    int number_of_calls = 1;
    c = 0;
    s = 0;
    if (size == 0) return number_of_calls;

    
    
    // MinHeap(size/K);
    
    int *output = new int[size];
    int offset = size / K;
    
    mergeRecursion(arr, output, K, size, comparison, swap, number_of_calls, 0, size-1, offset, size);
    // merge(arr, K, output, offset, size, comparison, swap, number_of_calls, 0,size, 1);
    if (size >= K)
    {
        for (int i = 0; i < size ; i++)
        {
            arr[i] = output[i];
        }
            
    }
	
	comparison+=c;
    swap+=s;
            
	//Your code here
    delete [] output;
	return number_of_calls;
}