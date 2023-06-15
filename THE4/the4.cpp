#include "the4.h"

int dp_sln(char**& arr1, char**& arr2, int nrow, int ncol1, int ncol2, int**& mem)
{ //dynamic programming

    //your code here
    
    mem[0][0] = 0;
    
    int insertionCount = 0;
    int deletionCount = 0;
    
    for (int i=0; i<ncol2; i++)
    {
        for (int j=0; j<nrow; j++)
        {
            if (arr2[j][i] == '-')
            {
                continue;
            }
            
            insertionCount++;
        }
        
        mem[0][i+1] = insertionCount;
    }
    
    for (int i=0; i<ncol1; i++)
    {
        for (int j=0; j<nrow; j++)
        {
            if (arr1[j][i] == '-')
            {
                continue;
            }
            
            deletionCount++;
        }
        
        mem[i+1][0] = deletionCount;
    }

    
    
    // 1 arr1 more arr2
    
    // mem[col1+1][col2+1]
    
    for (int col1 = 0; col1 < ncol1; col1++)
    {
        for (int col2 = 0; col2 < ncol2; col2++)
        {
            // reorder
            int reorderCount = 0;
            int canBeOrdered = 0;
            bool isOrder = false;
            int orderArr[nrow] = {0};
            
            for (int row1=0; row1 < nrow; row1++)
            {
                for (int row2=0; row2 < nrow; row2++)
                {
                    
                    if (arr1[row1][col1] == arr2[row2][col2])
                    {
                        if (orderArr[row2] == 1)
                        {
                            continue;
                        }
                        orderArr[row2] = 1;
                        canBeOrdered++;
                        
                        if (row1 != row2)
                        {
                            reorderCount++;
                        }
                        
                        break;
                        
                    }
                }
            }
            

            
            // replace
            int replaceCount = 0;
            
            for (int row=0; row<nrow; row++)
            {
                if (arr1[row][col1] == arr2[row][col2])
                {
                    continue;
                }
                
                else
                {

                    if (arr1[row][col1] == '-' || arr2[row][col2] == '-')
                    {
                        replaceCount+=2;
                    }
                    
                    else
                    {
                        replaceCount++;
                    }
                }
            }            
            
            
            if (canBeOrdered != nrow)
            {
                
                
                int minimum = fmin(mem[0][col2+1]-mem[0][col2]+mem[col1+1][col2], mem[col1+1][0]-mem[col1][0]+mem[col1][col2+1]);
                
                
             
                
              
                
                //if (replaceCount + mem[col1+1][col2])
                
                //int tempo = fmin(mem[col1+1][col2] + mem[col1][col2+1] - mem[col1][col2], mem[col1+1][col2] + mem[0][col2+1] - mem[0][col2]);
                
                if (replaceCount + mem[col1][col2] < minimum)
                {
                  
                    
                    int temp =  fmin(replaceCount + mem[col1][col2], mem[col1+1][0]+mem[0][col2+1]);
                    mem[col1+1][col2+1] = temp;
                }
                
                else
                {
                   
                    
                    mem[col1+1][col2+1] = fmin(minimum, mem[col1+1][0]+mem[0][col2+1]);
                    //mem[col1+1][col2+1] = fmin(temp, mem[col1+1][col2]+mem[col1][col2+1]-mem[col1][col2]);
                    //mem[col1+1][col2+1] = fmin(mem[col1+1][col2]+mem[0][col2+1]-mem[0][col2], mem[col1+1][0]+mem[0][col2+1]);
                }
                
                
            }
            
            else
            {
                int minimum = fmin(mem[0][col2+1]-mem[0][col2]+mem[col1+1][col2], mem[col1+1][0]-mem[col1][0]+mem[col1][col2+1]);
                if (replaceCount < reorderCount)
                {
                    if (replaceCount + mem[col1][col2] < minimum)
                    {

                        
                        int temp =  fmin(replaceCount + mem[col1][col2], mem[col1+1][0]+mem[0][col2+1]);
                        mem[col1+1][col2+1] = temp;
                    }
                    
                    else
                    {
                        
                        mem[col1+1][col2+1] = fmin(minimum, mem[col1+1][0]+mem[0][col2+1]);
                    }
                }
                
                else
                {
                    if (reorderCount + mem[col1][col2] < minimum)
                    {

                        
                        int temp =  fmin(reorderCount + mem[col1][col2], mem[col1+1][0]+mem[0][col2+1]);
                        mem[col1+1][col2+1] = temp;
                    }
                    
                    else
                    {
                        
                        mem[col1+1][col2+1] = fmin(minimum, mem[col1+1][0]+mem[0][col2+1]);
                    }
                                    
                }
            }
            
            
        }
        
        
    }

    
    
    // more arr1 1 arr2
    
    
    
    
    
    

    return mem[ncol1][ncol2] ; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}
