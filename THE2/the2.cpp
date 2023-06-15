#include "the2.h"
#include <cmath>
// You may write your own helper functions here

void radixSortAsc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, long& numberOfIterations);
void radixSortDesc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, long& numberOfIterations);
void countSortAsc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, int exp, long& numberOfIterations);
void countSortDesc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, int exp, long& numberOfIterations);
void multiRadixSortAsc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, long& numberOfIterations);
void multiRadixSortDesc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, long& numberOfIterations);
void multiCountSortAsc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, int exp, long& numberOfIterations);
void multiCountSortDesc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, int exp, long& numberOfIterations);
void multiRadixSortAscRemainder(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, long& numberOfIterations);
void multiRadixSortDescRemainder(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, long& numberOfIterations);
void multiCountSortAscRemainder(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, int exp, long& numberOfIterations);
void multiCountSortDescRemainder(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, int exp, long& numberOfIterations);
int getMaxVal(int *arr, int arraySize);


long multiDigitRadixSort(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength){
    long numberOfIterations = 0;
    
    if (arraySize == 0)
    {
        return numberOfIterations;
    }
    
    if (groupSize == 0)
    {
        return numberOfIterations;
    }
    
    if (groupSize == 1)
    {
        if (ascending)
        {
            radixSortAsc(arr, ascending, arraySize, groupSize, maxDigitLength, numberOfIterations);
        }
        
        else
        {
            radixSortDesc(arr, ascending, arraySize, groupSize, maxDigitLength, numberOfIterations);
        }
    }
    
    else
    {
        if (maxDigitLength % groupSize == 0)
        {
            if (ascending)
            {
                multiRadixSortAsc(arr, ascending, arraySize, groupSize, maxDigitLength, numberOfIterations);
            }
            
            else
            {
                multiRadixSortDesc(arr, ascending, arraySize, groupSize, maxDigitLength, numberOfIterations);
            }
        }
        
        else
        {
            if (ascending)
            {
                multiRadixSortAscRemainder(arr, ascending, arraySize, groupSize, maxDigitLength, numberOfIterations);
            }
            
            else
            {
                multiRadixSortDescRemainder(arr, ascending, arraySize, groupSize, maxDigitLength, numberOfIterations);
            }
        }
        
    }
    
    
    
    return numberOfIterations;
}

void multiRadixSortAscRemainder(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, long& numberOfIterations)
{
    int max = getMaxVal(arr, arraySize);
    int length = maxDigitLength;
    int size = groupSize;
    int digit = pow(10, groupSize);
    long bos=0;
    
    int e = 1;
    multiCountSortAscRemainder(arr, ascending, arraySize, size, maxDigitLength, e, numberOfIterations);

    e *= pow(10, groupSize);
    multiCountSortAscRemainder(arr, ascending, arraySize, size, maxDigitLength, e, bos);
    

    e *= pow(10, length-size);
    multiCountSortAscRemainder(arr, ascending, arraySize, length-size, maxDigitLength, e, numberOfIterations);
    
    
    
}

void multiCountSortAscRemainder(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, int e, long& numberOfIterations)
{
    int *output = new int[arraySize];
    int i;
    int digit = pow(10, groupSize);
    int count[digit];
    
    for (int j=0; j<digit; j++)
    {
        count[j] = 0;
    }
    
    for (i = 0; i < arraySize; i++)
    {
        numberOfIterations++;
        count[(arr[i] / e) % digit]++;
    }
    
    for (i = 1; i < digit; i++)
    {
        numberOfIterations++;
        count[i] += count[i-1];
    }
    
    for (i = arraySize - 1; i >= 0; i--)
    {
        numberOfIterations++;
        output[count[(arr[i] / e) % digit] - 1] = arr[i];
        count[(arr[i] / e) % digit]--;
    }
    
    for (i = 0; i < arraySize; i++)
    {
        numberOfIterations++;
        arr[i] = output[i];
    }
    
    delete [] output;
    
}

void multiRadixSortDescRemainder(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, long& numberOfIterations)
{
    int max = getMaxVal(arr, arraySize);
    int length = maxDigitLength;
    int size = groupSize;
    int digit = pow(10, groupSize);
    long bos=0;
    
    int e = 1;
    multiCountSortDescRemainder(arr, ascending, arraySize, size, maxDigitLength, e, numberOfIterations);

    e *= pow(10, groupSize);
    multiCountSortDescRemainder(arr, ascending, arraySize, size, maxDigitLength, e, bos);
    

    e *= pow(10, length-size);
    multiCountSortDescRemainder(arr, ascending, arraySize, length-size, maxDigitLength, e, numberOfIterations);
    
    
}

void multiCountSortDescRemainder(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, int e, long& numberOfIterations)
{
    int *output = new int[arraySize];
    int i;
    int digit = pow(10, groupSize);
    int count[digit];
    
    for (int j=0; j<digit; j++)
    {
        count[j] = 0;
    }
    
    for (i = 0; i < arraySize; i++)
    {
        numberOfIterations++;
        count[(digit - 1) - (arr[i] / e) % digit]++;
    }
    
    for (i = 1; i < digit; i++)
    {
        numberOfIterations++;
        count[i] += count[i-1];
    }
    
    for (i = arraySize - 1; i >= 0; i--)
    {
        numberOfIterations++;
        output[count[(digit - 1) - (arr[i] / e) % digit] - 1] = arr[i];
        count[(digit - 1) - (arr[i] / e) % digit]--;
    }
    
    for (i = 0; i < arraySize; i++)
    {
        numberOfIterations++;
        arr[i] = output[i];
    }
    
    delete [] output;
    
}


void multiRadixSortAsc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, long& numberOfIterations)
{
    int max = getMaxVal(arr, arraySize);
    
    int digit = pow(10, groupSize);
    
    for (int e = 1; max / e > 0; e *= digit)
    {
        multiCountSortAsc(arr, ascending, arraySize, groupSize, maxDigitLength, e, numberOfIterations);
    }
}

void multiCountSortAsc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, int e, long& numberOfIterations)
{
    int *output = new int[arraySize];
    int i;
    int digit = pow(10, groupSize);
    int count[digit];
    
    for (int j=0; j<digit; j++)
    {
        count[j] = 0;
    }
    
    for (i = 0; i < arraySize; i++)
    {
        numberOfIterations++;
        count[(arr[i] / e) % digit]++;
    }
    
    for (i = 1; i < digit; i++)
    {
        numberOfIterations++;
        count[i] += count[i-1];
    }
    
    for (i = arraySize - 1; i >= 0; i--)
    {
        numberOfIterations++;
        output[count[(arr[i] / e) % digit] - 1] = arr[i];
        count[(arr[i] / e) % digit]--;
    }
    
    for (i = 0; i < arraySize; i++)
    {
        numberOfIterations++;
        arr[i] = output[i];
    }
    
    delete [] output;
    
}

void multiRadixSortDesc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, long& numberOfIterations)
{
    int max = getMaxVal(arr, arraySize);
    
    int digit = pow(10, groupSize);
    
    for (int e = 1; max / e > 0; e *= digit)
    {
        multiCountSortDesc(arr, ascending, arraySize, groupSize, maxDigitLength, e, numberOfIterations);
    }
}

void multiCountSortDesc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, int e, long& numberOfIterations)
{
    int *output = new int[arraySize];
    int i;
    int digit = pow(10, groupSize);
    int count[digit];
    
    for (int j=0; j<digit; j++)
    {
        count[j] = 0;
    }
    
    for (i = 0; i < arraySize; i++)
    {
        numberOfIterations++;
        count[(digit - 1) - (arr[i] / e) % digit]++;
    }
    
    for (i = 1; i < digit; i++)
    {
        numberOfIterations++;
        count[i] += count[i-1];
    }
    
    for (i = arraySize - 1; i >= 0; i--)
    {
        numberOfIterations++;
        output[count[(digit - 1) - (arr[i] / e) % digit] - 1] = arr[i];
        count[(digit - 1) - (arr[i] / e) % digit]--;
    }
    
    for (i = 0; i < arraySize; i++)
    {
        numberOfIterations++;
        arr[i] = output[i];
    }
    
    delete [] output;
    
}


int getMaxVal(int *arr, int arraySize)
{
    int max = arr[0];
    
    for (int i=1; i < arraySize; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    
    return max;
    
}



void radixSortAsc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, long& numberOfIterations)
{
    int max = getMaxVal(arr, arraySize);
    
    for (int e = 1; max / e > 0; e *= 10)
    {
        countSortAsc(arr, ascending, arraySize, groupSize, maxDigitLength, e, numberOfIterations);
    }
    
    
    
}

void radixSortDesc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, long& numberOfIterations)
{
    int max = getMaxVal(arr, arraySize);
    
    for (int e = 1; max / e > 0; e *= 10)
    {
        countSortDesc(arr, ascending, arraySize, groupSize, maxDigitLength, e, numberOfIterations);
    }
    
}

void countSortAsc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, int e, long& numberOfIterations)
{
    int *output = new int[arraySize];
    int i;
    int count[10];
    
    for (int j=0; j<10; j++)
    {
        count[j] = 0;
    }
    
    for (i = 0; i < arraySize; i++)
    {
        numberOfIterations++;
        count[(arr[i] / e) % 10]++;
    }
    
    for (i = 1; i < 10; i++)
    {
        numberOfIterations++;
        count[i] += count[i-1];
    }
    
    for (i = arraySize - 1; i >= 0; i--)
    {
        numberOfIterations++;
        output[count[(arr[i] / e) % 10] - 1] = arr[i];
        count[(arr[i] / e) % 10]--;
    }
    
    for (i = 0; i < arraySize; i++)
    {
        numberOfIterations++;
        arr[i] = output[i];
    }
    
    delete [] output;
    
}

void countSortDesc(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength, int e, long& numberOfIterations)
{
    int *output = new int[arraySize];
    int i;
    int count[10];
    
    for (int j=0; j<10; j++)
    {
        count[j] = 0;
    }
    
    for (i = 0; i < arraySize; i++)
    {
        numberOfIterations++;
        count[9 - (arr[i] / e) % 10]++;
    }
    
    for (i = 1; i < 10; i++)
    {
        numberOfIterations++;
        count[i] += count[i-1];
    }
    
    for (i = arraySize - 1; i >= 0; i--)
    {
        numberOfIterations++;
        output[count[9 - (arr[i] / e) % 10] - 1] = arr[i];
        count[9 -(arr[i] / e) % 10]--;
    }
    
    for (i = 0; i < arraySize; i++)
    {
        numberOfIterations++;
        arr[i] = output[i];
    }
    
    delete [] output;
    
}