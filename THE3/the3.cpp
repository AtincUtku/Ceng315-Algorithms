#include "the3.h"



int recursive_sln(int i, char**& arr, int*& len, int &number_of_calls) { //direct recursive
    number_of_calls+=1;

    //your code here
    
   
    
    if (i == 0)
    {
        return len[0];
    }
    
    
    if (number_of_calls == 1)
    {
        int a,b;
        int c = 0;
        
        
        for (int y = i-1; y >=0 ; y--)
        {
            a = recursive_sln(y, arr, len, number_of_calls);
            if(a > c)
            {
                c = a;
            }
            
        }
        
        
        for (int x = i-1; x >= 0; x--)
        {
            
            if ((arr[i][0] == 'O' && arr[x][1] == 'I') || (arr[i][0] == 'I' && arr[x][1] == 'O') || (arr[i][0] == 'S' && arr[x][1] == 'S'))
            {
                
                
                
                return fmax(c,recursive_sln(x, arr, len, number_of_calls) + len[i]);
                
            }
            
            
        }  
        return fmax(c,len[i]);
       

        
    }
    
    
    else
    {
        int a,b;
        a = len[i];
        for (int x = i-1; x >= 0; x--)
        {
           
            if (arr[i][1] == arr[x][1])
            {
                
               
               a = recursive_sln(x, arr, len, number_of_calls);
               
               break;
                
            }
            
           
        }  
        
        for (int y = i-1; y >= 0; y--)
        {
            
            if ((arr[i][0] == 'O' && arr[y][1] == 'I') || (arr[i][0] == 'I' && arr[y][1] == 'O') || (arr[i][0] == 'S' && arr[y][1] == 'S'))
            {
                
                
                
                return fmax(a,len[i] + recursive_sln(y, arr, len, number_of_calls));
            }
            
           
        }
        return a;
        
    }
    
    
}



int memoization_sln(int i, char**& arr, int*& len, int**& mem) 
{ 
    //memoization
    
    if (i == 0)
    {
        for (int x=0; x < 3; x++)
        {
            mem[0][x] = 0;
        }
        
        if (arr[0][1] == 'I')
        {
            mem[0][0] = len[0];
        }
        
        else if (arr[0][1] == 'O')
        {
            mem[0][1] = len[0];
        }
        
        else if (arr[0][1] == 'S')
        {
            mem[0][2] = len[0];
        }
        
        
        return 0;
        
    }
    

        memoization_sln(i-1, arr, len, mem);
   
    
    mem[i][0] = mem[i-1][0];
        mem[i][1] = mem[i-1][1];
        mem[i][2] = mem[i-1][2];
        
        int control = 0;
        
        if (arr[i][0] == 'I')
        {
            
            if (mem[i-1][1] > 0)
            {
                if (arr[i][1] == 'I')
                {
                    int temp = len[i] + mem[i-1][1];
                    if (temp > mem[i-1][0]) mem[i][0] = temp;
                }
                
                if (arr[i][1] == 'O')
                {
                    int temp = len[i] + mem[i-1][1];
                    if (temp > mem[i-1][1]) mem[i][1] = temp;
                }
                
                if (arr[i][1] == 'S')
                {
                    int temp = len[i] + mem[i-1][1];
                    if (temp > mem[i-1][2]) mem[i][2] = temp;
                }
            }
            
            else
            {
                if (arr[i][1] == 'I')
                {
                    if (mem[i-1][0] < len[i]) mem[i][0] = len[i];
                }
                
                if (arr[i][1] == 'O')
                {
                    if (mem[i-1][1] < len[i]) mem[i][1] = len[i];
                }
                
                if (arr[i][1] == 'S')
                {
                    if (mem[i-1][2] < len[i]) mem[i][2] = len[i];
                }
            }
        }
        
        else if (arr[i][0] == 'O')
        {
            if (mem[i-1][0] > 0)
            {
                if (arr[i][1] == 'I')
                {
                    int temp = len[i] + mem[i-1][0];
                    if (temp > mem[i-1][0]) mem[i][0] = temp;
                }
                
                if (arr[i][1] == 'O')
                {
                    int temp  = len[i] + mem[i-1][0];
                    if (temp > mem[i-1][1]) mem[i][1] = temp;
                }
                
                if (arr[i][1] == 'S')
                {
                    int temp  = len[i] + mem[i-1][0];
                    if (temp > mem[i-1][2]) mem[i][2] = temp;
                }
                
            }
            
            else
            {
                if (arr[i][1] == 'I')
                {
                    if (mem[i-1][0] < len[i]) mem[i][0] = len[i];
                }
                
                if (arr[i][1] == 'O')
                {
                    if (mem[i-1][1] < len[i]) mem[i][1] = len[i];
                }
                
                if (arr[i][1] == 'S')
                {
                    if (mem[i-1][2] < len[i]) mem[i][2] = len[i];
                }
            }
        }
        
        else if (arr[i][0] == 'S')
        {
            if (mem[i-1][2] > 0)
            {
                if (arr[i][1] == 'I')
                {
                    int temp = len[i] + mem[i-1][2];
                    if (temp > mem[i-1][0]) mem[i][0] = temp;
                }
                
                if (arr[i][1] == 'O')
                {
                    int temp = len[i] + mem[i-1][2];
                    if (temp > mem[i-1][1]) mem[i][1] = temp;
                }
                
                if (arr[i][1] == 'S')
                {
                    int temp  = len[i] + mem[i-1][2];
                    if (temp > mem[i-1][2]) mem[i][2] = temp;
                }
                
            }
            
            else
            {
                if (arr[i][1] == 'I')
                {
                    if (mem[i-1][0] < len[i]) mem[i][0] = len[i];
                }
                
                if (arr[i][1] == 'O')
                {
                    if (mem[i-1][1] < len[i]) mem[i][1] = len[i];
                }
                
                if (arr[i][1] == 'S')
                {
                    if (mem[i-1][2] < len[i]) mem[i][2] = len[i];
                }
            }
        }
    
    
    int m1 = mem[i][0];
    int m2 = mem[i][1];
    int m3 = mem[i][2];
    
    int max = fmax(fmax(m1,m2),m3);

    return max; // this is a dummy return value. YOU SHOULD CHANGE THIS!

    

}



int dp_sln(int size, char**& arr, int*& len, int**& mem) 
{ //dynamic programming
    
    // I O S
    
    //your code here
  
    
    for (int i=0; i < 3; i++)
    {
        mem[0][i] = 0;
    }
    
    if (arr[0][1] == 'I')
    {
        mem[0][0] = len[0];
    }
    
    else if (arr[0][1] == 'O')
    {
        mem[0][1] = len[0];
    }
    
    else if (arr[0][1] == 'S')
    {
        mem[0][2] = len[0];
    }
    
    
    for (int i=1; i<size; i++)
    {
        mem[i][0] = mem[i-1][0];
        mem[i][1] = mem[i-1][1];
        mem[i][2] = mem[i-1][2];
        
        int control = 0;
        
        if (arr[i][0] == 'I')
        {
            
            if (mem[i-1][1] > 0)
            {
                if (arr[i][1] == 'I')
                {
                    int temp = len[i] + mem[i-1][1];
                    if (temp > mem[i-1][0]) mem[i][0] = temp;
                }
                
                if (arr[i][1] == 'O')
                {
                    int temp = len[i] + mem[i-1][1];
                    if (temp > mem[i-1][1]) mem[i][1] = temp;
                }
                
                if (arr[i][1] == 'S')
                {
                    int temp = len[i] + mem[i-1][1];
                    if (temp > mem[i-1][2]) mem[i][2] = temp;
                }
            }
            
            else
            {
                if (arr[i][1] == 'I')
                {
                    if (mem[i-1][0] < len[i]) mem[i][0] = len[i];
                }
                
                if (arr[i][1] == 'O')
                {
                    if (mem[i-1][1] < len[i]) mem[i][1] = len[i];
                }
                
                if (arr[i][1] == 'S')
                {
                    if (mem[i-1][2] < len[i]) mem[i][2] = len[i];
                }
            }
        }
        
        else if (arr[i][0] == 'O')
        {
            if (mem[i-1][0] > 0)
            {
                if (arr[i][1] == 'I')
                {
                    int temp = len[i] + mem[i-1][0];
                    if (temp > mem[i-1][0]) mem[i][0] = temp;
                }
                
                if (arr[i][1] == 'O')
                {
                    int temp  = len[i] + mem[i-1][0];
                    if (temp > mem[i-1][1]) mem[i][1] = temp;
                }
                
                if (arr[i][1] == 'S')
                {
                    int temp  = len[i] + mem[i-1][0];
                    if (temp > mem[i-1][2]) mem[i][2] = temp;
                }
                
            }
            
            else
            {
                if (arr[i][1] == 'I')
                {
                    if (mem[i-1][0] < len[i]) mem[i][0] = len[i];
                }
                
                if (arr[i][1] == 'O')
                {
                    if (mem[i-1][1] < len[i]) mem[i][1] = len[i];
                }
                
                if (arr[i][1] == 'S')
                {
                    if (mem[i-1][2] < len[i]) mem[i][2] = len[i];
                }
            }
        }
        
        else if (arr[i][0] == 'S')
        {
            if (mem[i-1][2] > 0)
            {
                if (arr[i][1] == 'I')
                {
                    int temp = len[i] + mem[i-1][2];
                    if (temp > mem[i-1][0]) mem[i][0] = temp;
                }
                
                if (arr[i][1] == 'O')
                {
                    int temp = len[i] + mem[i-1][2];
                    if (temp > mem[i-1][1]) mem[i][1] = temp;
                }
                
                if (arr[i][1] == 'S')
                {
                    int temp  = len[i] + mem[i-1][2];
                    if (temp > mem[i-1][2]) mem[i][2] = temp;
                }
                
            }
            
            else
            {
                if (arr[i][1] == 'I')
                {
                    if (mem[i-1][0] < len[i]) mem[i][0] = len[i];
                }
                
                if (arr[i][1] == 'O')
                {
                    if (mem[i-1][1] < len[i]) mem[i][1] = len[i];
                }
                
                if (arr[i][1] == 'S')
                {
                    if (mem[i-1][2] < len[i]) mem[i][2] = len[i];
                }
            }
        }
    }
    
    
    int m1 = mem[size-1][0];
    int m2 = mem[size-1][1];
    int m3 = mem[size-1][2];
    
    int max = fmax(fmax(m1,m2),m3);

    return max; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}

