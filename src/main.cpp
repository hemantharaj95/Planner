#include <iostream>
#include <../include/environment/environment.h>
#include <../include/planner/planner.h>

int main()
{
    std::shared_ptr<Grid_Map<int>> env = std::make_shared<Grid_Map<int>>(); 

    std::vector<int> neigh = env->neighbor(10);

    for(int val : neigh){
        std::cout << "->" << val << std::endl; 
    }

    Dijkstra<int> dijk = Dijkstra<int>(env);
    dijk.set_timeout(60000);
    dijk.set_start(3);
    dijk.set_goal(17);
    dijk.plan();

    for(auto state: dijk.get_soln()){
        std::cout << "Plan " << state <<"->";
    }
    std::cout << std::endl;
}