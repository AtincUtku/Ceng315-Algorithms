#include "the5.h"

/* 
    in the5.h "struct Room" is defined as below:
    
    struct Room {
        int id;
        char content;
        vector<Room*> neighbors;
    };

*/
void maze_trace_visit(vector<Room*> maze, vector<int> &color, vector<int> &path, int current, int parent, vector<Room*> &parent_list, int &terminate);
vector<int> maze_trace(vector<Room*> maze);
int find_index_in_graph(vector<Room*> maze, vector<Room*> neighbours, int index);
int find_index_in_graph_with_id(vector<Room*> maze, int id);


vector<int> maze_trace(vector<Room*> maze) 
{ 

    vector<int> path;
    vector<int> color; // 0 white , 1 gray, 2 black
    vector<Room*> parent_list;
    //your code here
    
    int size = maze.size();
    
    // initialize color list
    for (int i=0; i<size; i++)
    {
        color.push_back(0);
    }
    
    int terminate = 0;

    maze_trace_visit(maze, color, path, 0, -1, parent_list, terminate);


    
    
    return path; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}



void maze_trace_visit(vector<Room*> maze, vector<int> &color, vector<int> &path, int current, int parent, vector<Room*> &parent_list, int &terminate)
{
 
    color[current] = 1;
    path.push_back(maze[current]->id);
    
    // found, then backtrack
    if (maze[current]->content == '*')
    {
        
        int size = parent_list.size();
        for (int i=size-1; i>=0; i--)
        {
            // if the parent is grey then it should be in the path
            if (color[parent_list[i]->id]==1)
            {
                color[parent_list[i]->id] = 2;  // turn it black afterwards
                path.push_back(parent_list[i]->id);
            }
        }
        
        // termination condition. without it can loop afterwards and look for other neighbours
        terminate = 1;
        return;
    }
    
    int count_visited = 0;
    
    for (int i=0; i<maze[current]->neighbors.size(); i++)
    {
        // key is found so terminate
        if (terminate)
        {
            break;
        }
        
        int next = find_index_in_graph(maze, maze[current]->neighbors, i);
        
        if (next == current)
        {
            continue;
        }
        
        // if it is not visited
        if (color[next] == 0)
        {
            // put it in the parent list
            parent_list.push_back(maze[current]);
            maze_trace_visit(maze, color, path, next, maze[current]->id, parent_list, terminate);
        }
        
        if (color[next] == 1 || color[next] == 2)
        {
            // if the neighbor are visited or done, increment visited number 
            count_visited++;
        }
        
    }
    
    
    
    // if not first time
    if (parent != -1)
    {
        // find the real index;
        int parent_index = find_index_in_graph_with_id(maze, parent);
        
        // if all of the neighbours visited add parent to the path
        if (count_visited == maze[current]->neighbors.size() && color[parent_index] == 1)
        {
            path.push_back(parent);
        }
        
    }
    
    // when all the operation done, make the current node black
    color[current] = 2;
    
}


// helper for finding neighbors index in graph
int find_index_in_graph(vector<Room*> maze, vector<Room*> neighbors, int index)
{
    for (int i=0; i<maze.size(); i++)
    {
        if (maze[i]->id == neighbors[index]->id)
        {
            return i;
        }
    }

    return -1;
}

// helper for finding index in graph with id
int find_index_in_graph_with_id(vector<Room*> maze, int id)
{
    for (int i=0; i<maze.size(); i++)
    {
        if (maze[i]->id == id)
        {
            return i;
        }
    }

    return -1;
}



