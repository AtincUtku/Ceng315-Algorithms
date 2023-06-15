#include "the7.h"

// Implement your solution after this line

int dijkstra(int n, std::vector<std::vector<std::pair<int, int>>> road_map, int s, int d, std::vector<int> &path)
{
    std::vector<bool> visited(n, false);
    std::vector<int> dist(n, INT_MAX);
    dist[s] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    std::pair<int, int> start = std::make_pair(0, s);
    q.push(start);
    
    while (!q.empty())
    {
        int v = q.top().second;
        
        q.pop();
        
        if (visited[v]) continue;
        
        visited[v] = true;
        
        for (auto r : road_map[v])
        {
            int u = r.first;
            int w = r.second;
            
            if (dist[u] > dist[v] + w)
            {
                dist[u] = dist[v] + w;
                path[u] = v;
                
                std::pair<int ,int> temp = std::make_pair(dist[u], u);
                q.push(temp);
                
            }
        }
    }
    
    return dist[d];
    
}

void CanCatch(int n, std::vector<Road> roads, int s, int d, int x, int y, int l, int printPath) {
    // You can change these variables. These are here for demo only.
    std::vector<int> path;
    int total_time = 0;
    int can_catch = -1; // -1 => IMPOSSIBLE, 0 => YES BOTH, 1 => YES PRINTER, 2 => YES DORM, 3 => YES DIRECTLY
    
    std::vector<std::vector<std::pair<int, int>>> road_map(n);
    
    for (auto r : roads)
    {
        std::pair<int, int> first_pair = std::make_pair(r.buildings.second, r.time);
        road_map[r.buildings.first].push_back(first_pair);
        
        std::pair<int, int> second_pair = std::make_pair(r.buildings.first, r.time);
        road_map[r.buildings.second].push_back(second_pair);
    }
    
    
    // goes to x then y the d
    std::vector<int> path_s_x(n, -1);
    std::vector<int> path_x_y(n, -1);
    std::vector<int> path_y_d(n, -1);
    
    // goes to y then x the d
    std::vector<int> path_s_y(n, -1);
    std::vector<int> path_y_x(n, -1);
    std::vector<int> path_x_d(n, -1);
    
    // unlucky, just s and d
    std::vector<int> path_s_d(n, -1);
    
    // both x y
    int s_to_x = dijkstra(n, road_map, s, x, path_s_x);
    int s_to_y = dijkstra(n, road_map, s, y, path_s_y);
    int x_to_y = dijkstra(n, road_map, x, y, path_x_y);
    int y_to_x = dijkstra(n, road_map, y, x, path_y_x);
    int x_to_d = dijkstra(n, road_map, x, d, path_x_d);
    int y_to_d = dijkstra(n, road_map, y, d, path_y_d);
    
    
    int bothxy = s_to_x + x_to_y + y_to_d;
    int bothyx = s_to_y + y_to_x + x_to_d;
    
    int sxd = s_to_x + x_to_d;
    int syd = s_to_y + y_to_d;
    
    
    
    if (bothxy <= l || bothyx <= l)
    {
        
        if (bothxy == bothyx)
        {
            can_catch = 0;
            total_time = bothxy;
            path.push_back(d);
            int i = d;
            path_y_d[y] = -1;
            path_x_y[x] = -1;
            path_s_x[s] = -1;
            
            while (path_y_d[i] != -1)
            {
                path.insert(path.begin(), path_y_d[i]);
                i = path_y_d[i];
            }
            
            while (path_x_y[i] != -1)
            {
                path.insert(path.begin(), path_x_y[i]);
                i = path_x_y[i];
            }
            
            while (path_s_x[i] != -1)
            {
                path.insert(path.begin(), path_s_x[i]);
                i = path_s_x[i];
            }
        }
        
        else if (bothxy < bothyx)
        {
            can_catch = 0;
            total_time = bothxy;
            path.push_back(d);
            int i = d;
            path_y_d[y] = -1;
            path_x_y[x] = -1;
            path_s_x[s] = -1;
            
            while (path_y_d[i] != -1)
            {
                path.insert(path.begin(), path_y_d[i]);
                i = path_y_d[i];
            }
            
            while (path_x_y[i] != -1)
            {
                path.insert(path.begin(), path_x_y[i]);
                i = path_x_y[i];
            }
            
            while (path_s_x[i] != -1)
            {
                path.insert(path.begin(), path_s_x[i]);
                i = path_s_x[i];
            }
        }
        
        else if (bothyx < bothxy)
        {
            can_catch = 0;
            total_time = bothyx;
            path.push_back(d);
            int i = d;
            path_x_d[x] = -1;
            path_y_x[y] = -1;
            path_s_y[s] = -1;
            
            while (path_x_d[i] != -1)
            {
                path.insert(path.begin(), path_x_d[i]);
                i = path_x_d[i];
            }
            
            while(path_y_x[i] != -1)
            {
                path.insert(path.begin(), path_y_x[i]);
                i = path_y_x[i];
            }
            
            while (path_s_y[i] != -1)
            {
                path.insert(path.begin(), path_s_x[i]);
                i = path_s_x[i];
            }
            
        }
    
    }
    
    else 
    {
        if (sxd <= l || syd <= l)
        {
            if (sxd == syd)
            {
                can_catch = 1;
                total_time = sxd;
                path.push_back(d);
                int i = d;
                path_x_d[x] = -1;
                path_s_x[s] = -1;
                
                while (path_x_d[i] != -1)
                {
                    path.insert(path.begin(), path_x_d[i]);
                    i = path_x_d[i];
                }
                
                while(path_s_x[i] != -1)
                {
                    path.insert(path.begin(), path_s_x[i]);
                    i = path_s_x[i];
                }               
            }
            
            else if (sxd < syd)
            {
                can_catch = 1;
                total_time = sxd;
                path.push_back(d);
                int i = d;
                path_x_d[x] = -1;
                path_s_x[s] = -1;
                
                while (path_x_d[i] != -1)
                {
                    path.insert(path.begin(), path_x_d[i]);
                    i = path_x_d[i];
                }
                
                while(path_s_x[i] != -1)
                {
                    path.insert(path.begin(), path_s_x[i]);
                    i = path_s_x[i];
                }
            }
            
            else if (syd < sxd)
            {
                can_catch = 2;
                total_time = syd;
                path.push_back(d);
                int i = d;
                path_y_d[y] = -1;
                path_s_y[s] = -1;
                
                while (path_y_d[i] != -1)
                {
                    path.insert(path.begin(), path_y_d[i]);
                    i = path_y_d[i];
                }
                
                while(path_s_y[i] != -1)
                {
                    path.insert(path.begin(), path_s_y[i]);
                    i = path_s_y[i];
                }
            }
        }
        
        else
        {
            int s_to_d = dijkstra(n, road_map, s, d, path_s_d);
            
            if (s_to_d < l)
            {
                can_catch = 3;
                total_time = s_to_d;
                path.push_back(d);
                int i = d;
                path_s_d[s] = -1;
                
                while(path_s_d[i] != -1)
                {
                    path.insert(path.begin(), path_s_d[i]);
                    i = path_s_d[i];
                }
            }
            
            else
            {
                can_catch = -1;
            }
        }
    }
    
    if (can_catch == -1)
    {
        std::cout<<"IMPOSSIBLE";
    }
    
    else if (can_catch == 0)
    {
        std::cout<<"YES BOTH ";
    }
    
    else if (can_catch == 1)
    {
        std::cout<<"YES PRINTER ";
    }
    
    else if (can_catch == 2)
    {
        std::cout<<"YES DORM ";
    }
    
    else if (can_catch == 3)
    {
        std::cout<<"YES DIRECTLY ";
    }
    
    if (can_catch != -1)
    {
        std::cout<<total_time<<"MINUTES"<<std::endl;
    }
    
    if (printPath == 1)
    {
        PrintRange(path.begin(), path.end());
        std::cout<<std::endl;
    }
    
    
    // You can use the PrintRange function to print the path.
    // It helps you print elements of containers with iterators (e.g., std::vector).
    // Usage: PrintRange(path.begin(), path.end());
    
}