#include "sol4.h"



int recursive_sln(int i, int j, char**& arr1, char**& arr2, int nrow, int ncol1, int ncol2, int &number_of_calls){ //direct recursive
    number_of_calls+=1;
    
    if (i == 0) {
        if (j == 0)
            return 0;   // never goes here
        else {
            int num_of_insertions = 0;
            // count the number of cells in arr2
            for (int n = 0; n < j; n++) {
                for (int m = 0; m < nrow; m++) {
                    if (arr2[m][n] == '-')
                        continue;
                    else
                        num_of_insertions ++;  // num of insertions
                }
            }
            return num_of_insertions;
        }
    }
    else if (j == 0) {
        int num_of_deletions = 0;
        // count the number of cells in arr1
        for (int n = 0; n < i; n++) {
            for (int m = 0; m < nrow; m++) {
                if (arr1[m][n] == '-')
                    continue;
                else
                    num_of_deletions ++;  // num of deletions
            }
        }
        return num_of_deletions;
    }
    else {
        
        // DELETION
         int num_of_deletions = 0;
        // count the number of cells in arr1
        for (int m = 0; m < nrow; m++) {
            if (arr1[m][i-1] == '-')
                continue;
            else
                num_of_deletions ++; 
        }
        
        int x = recursive_sln(i-1, j, arr1, arr2, nrow, ncol1, ncol2, number_of_calls);
        int cost = x + num_of_deletions;  // cost of deletions

        // INSERTION            
        int num_of_insertions = 0;
        // count the number of cells in arr2
        for (int m = 0; m < nrow; m++) {
            if (arr2[m][j-1] == '-')
                    continue;
            else
                num_of_insertions ++; 
        }

        int y = recursive_sln(i, j-1, arr1, arr2, nrow, ncol1, ncol2, number_of_calls);
        if (cost > y + num_of_insertions) 
            cost = y + num_of_insertions; // cost of insertions
        
        // REPLACEMENT    
        int cost_of_replacements = 0;
        // check for the same items in arr1 and arr2
        for (int m = 0; m < nrow; m++) {
            if (arr1[m][i-1] == arr2[m][j-1])
                continue;
            else if (arr1[m][i-1] == '-' || arr2[m][j-1] == '-')
                cost_of_replacements += 2;
            else
                cost_of_replacements ++;
        }
        int z = recursive_sln(i-1, j-1, arr1, arr2, nrow, ncol1, ncol2, number_of_calls);
        if (cost > z + cost_of_replacements)
            cost = z + cost_of_replacements;
        
        // REORDERING
        int cost_of_reordering = 0;
        std::string order1 = "";
        std::string order2 = "";
        for (int m = 0; m < nrow; m++) {
            order1 += arr1[m][i-1];
            order2 += arr2[m][j-1];
        }
        bool equivalent = true;
        for (int m = 0; m < nrow; m++) {
            std::size_t found = order2.find(order1[m]);
            if (found!=std::string::npos)
                order2 = order2.substr(0, found) + order2.substr(found+1);
            else {
                equivalent = false;
                break;
            }
        }
            
        if (equivalent) {
            for (int m = 0; m < nrow; m++) {
                if (arr1[m][i-1] == arr2[m][j-1])
                    continue;
                else
                    cost_of_reordering += 1;
            }
            if (cost > z + cost_of_reordering)
                cost = z + cost_of_reordering;
        }
        
        return cost;
    }

}



int memoization_sln(int i, int j, char**& arr1, char**& arr2, int nrow, int ncol1, int ncol2, int**& mem){ //memoization

    // mem is (ncol1+1) x (ncol2+1)
    
    // initialize trivial parts of mem
    if (i == 0) {
        if (j == 0)
            mem[i][j] = 0;  // never goes here
        else {
            mem[0][j] = 0;
            // count the number of cells in arr2
            for (int n = 0; n < j; n++) {
                for (int m = 0; m < nrow; m++) {
                    if (arr2[m][n] == '-')
                        continue;
                    else
                        mem[0][j] ++;  // num of insertions
                }
            }
            mem[0][0] = 0;
        }
    }
    else if (j == 0) {
        mem[i][0] = 0;
        // count the number of cells in arr1
        for (int n = 0; n < i; n++) {
            for (int m = 0; m < nrow; m++) {
                if (arr1[m][n] == '-')
                    continue;
                else
                    mem[i][0] ++;  // num of deletions
            }
        }
    }
    
    // for the nontrivial parts of mem
    else {
        // DELETION 
        int num_of_deletions = 0;
        // count the number of cells in arr1
        for (int m = 0; m < nrow; m++) {
            if (arr1[m][i-1] == '-')
                continue;
            else
                num_of_deletions ++; 
        }
         
        if (mem[i-1][j] == -1)
            memoization_sln(i-1, j, arr1, arr2, nrow, ncol1, ncol2, mem);
        int cost = mem[i-1][j] + num_of_deletions;  // cost of deletions
        
        // INSERTION     
        int num_of_insertions = 0;
        // count the number of cells in arr2
        for (int m = 0; m < nrow; m++) {
            if (arr2[m][j-1] == '-')
                    continue;
            else
                num_of_insertions ++; 
        }
        
        if (mem[i][j-1] == -1)
             memoization_sln(i, j-1, arr1, arr2, nrow, ncol1, ncol2, mem);
        if (cost > mem[i][j-1] + num_of_insertions) 
            cost = mem[i][j-1] + num_of_insertions; // cost of insertions
                
        // REPLACEMENT    
        int cost_of_replacements = 0;
        // check for the same items in arr1 and arr2
        for (int m = 0; m < nrow; m++) {
            if (arr1[m][i-1] == arr2[m][j-1])
                continue;
            else if (arr1[m][i-1] == '-' || arr2[m][j-1] == '-')
                cost_of_replacements += 2;
            else
                cost_of_replacements ++;
        }
        if (mem[i-1][j-1] == -1)
            memoization_sln(i-1, j-1, arr1, arr2, nrow, ncol1, ncol2, mem);
        if (cost > mem[i-1][j-1] + cost_of_replacements)
            cost = mem[i-1][j-1] + cost_of_replacements;
        
        // REORDERING
        int cost_of_reordering = 0;
        std::string order1 = "";
        std::string order2 = "";
        for (int m = 0; m < nrow; m++) {
            order1 += arr1[m][i-1];
            order2 += arr2[m][j-1];
        }
        bool equivalent = true;
        for (int m = 0; m < nrow; m++) {
            std::size_t found = order2.find(order1[m]);
            if (found!=std::string::npos)
                order2 = order2.substr(0, found) + order2.substr(found+1);
            else {
                equivalent = false;
                break;
            }
        }
        
        if (equivalent) {
            for (int m = 0; m < nrow; m++) {
                if (arr1[m][i-1] == arr2[m][j-1])
                    continue;
                else
                    cost_of_reordering += 1;
            }
            if (cost > mem[i-1][j-1] + cost_of_reordering)
                cost = mem[i-1][j-1] + cost_of_reordering;
        }

        mem[i][j] = cost;
    }
    
    return mem[i][j];
}



int dp_sln(char**& arr1, char**& arr2, int nrow, int ncol1, int ncol2, int**& mem){ //memoization

    // mem is (ncol1+1) x (ncol2+1)
    
    // initialize trivial parts of mem
    mem[0][0] = 0;
    for (int i = 1; i <= ncol1; i++) {
        mem[i][0] = 0;
        // count the number of cells in arr1
        for (int n = 0; n < i; n++) {
            for (int m = 0; m < nrow; m++) {
                if (arr1[m][n] == '-')
                    continue;
                else
                    mem[i][0] ++;  // num of deletions
            }
        }
    }
    for (int j = 1; j <= ncol2; j++) {
        mem[0][j] = 0;
        // count the number of cells in arr2
        for (int n = 0; n < j; n++) {
            for (int m = 0; m < nrow; m++) {
                if (arr2[m][n] == '-')
                    continue;
                else
                    mem[0][j] ++;  // num of insertions
            }
        }
    }
    
    // now start dynamic programming
    for (int i = 1; i <= ncol1; i++)
        for (int j = 1; j <= ncol2; j++) {
            
            // DELETION 
            int num_of_deletions = 0;
            // count the number of cells in arr1
            for (int m = 0; m < nrow; m++) {
                if (arr1[m][i-1] == '-')
                    continue;
                else
                    num_of_deletions ++; 
            }
            
            int cost = mem[i-1][j] + num_of_deletions;  // cost of deletions
            
            // INSERTION 
            int num_of_insertions = 0;
            // count the number of cells in arr2
            for (int m = 0; m < nrow; m++) {
                if (arr2[m][j-1] == '-')
                    continue;
                else
                    num_of_insertions ++; 
            }
            
            if (cost > mem[i][j-1] + num_of_insertions) 
                cost = mem[i][j-1] + num_of_insertions; // cost of insertions
            
             // REPLACEMENT    
            int cost_of_replacements = 0;
            // check for the same items in arr1 and arr2
            for (int m = 0; m < nrow; m++) {
                if (arr1[m][i-1] == arr2[m][j-1])
                    continue;
                else if (arr1[m][i-1] == '-' || arr2[m][j-1] == '-')
                    cost_of_replacements += 2;
                else
                    cost_of_replacements ++;
            }
            if (cost > mem[i-1][j-1] + cost_of_replacements)
                cost = mem[i-1][j-1] + cost_of_replacements;
                
            // REORDERING
            int cost_of_reordering = 0;
            std::string order1 = "";
            std::string order2 = "";
            for (int m = 0; m < nrow; m++) {
                order1 += arr1[m][i-1];
                order2 += arr2[m][j-1];
            }
            bool equivalent = true;
            for (int m = 0; m < nrow; m++) {
                std::size_t found = order2.find(order1[m]);
                if (found!=std::string::npos)
                    order2 = order2.substr(0, found) + order2.substr(found+1);
                else {
                    equivalent = false;
                    break;
                }
            }
            
            if (equivalent) {
                for (int m = 0; m < nrow; m++) {
                    if (arr1[m][i-1] == arr2[m][j-1])
                        continue;
                    else
                        cost_of_reordering += 1;
                }
                if (cost > mem[i-1][j-1] + cost_of_reordering)
                    cost = mem[i-1][j-1] + cost_of_reordering;
            }
                
            mem[i][j] = cost;
        }
    
    return mem[ncol1][ncol2];   
}



