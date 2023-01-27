#include <iostream>
#include <../include/environment/environment.h>
#include <../include/planner/planner.h>

int main()
{
    Grid_Map<int> env = Grid_Map<int>(); 

    std::vector<int> neigh = env.neighbor(10);

    for(int val : neigh){
        std::cout << "->" << val << std::endl; 
    }
}