#pragma once
#include <iostream>
#include <vector>
#include <tuple>

template<typename state>
class Environment
{
    public:
        virtual std::vector<state> neighbor(state) = 0;
        virtual bool is_valid_state(state) = 0;
        //virtual long long key(state) = 0;      
};

//Grid Map
/**
 * grid Map index {{0,3,6},
 *                 {1,4,7},
 *                 {2,5,8}}
*/
template <typename state = int>
class Grid_Map : public Environment<state>
{
    private:
        std::vector<std::vector<int>> neigh; 
        std::vector<std::vector<int>> grid;
    public:
        Grid_Map()
        {
            std::cout << "Grid map called " << std::endl;
            neigh = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
            grid = {{0,0,0, 0},{1, 1, 1, 1},{1, 0, 1, 1},{1,1,0,1},{0,0,0,0}};
        }

        std::tuple<int, int> get_index(int state_)
        {
            return std::tuple<int,int>{state_ / grid.size(), state_ % grid.size()};
        }

        state to_state(int x , int y)
        {
            return (y * grid.size()) + x;
        }

        bool is_valid_state(state s)
        {
            int c,r;
            std::tie(c, r) = get_index(s);
            return is_valid_cell(r,c);
        }
        
        bool is_valid_cell(int x, int y)
        {
            //Valid boundary
            if((x < 0) || (x >= grid.size())){
                return false;
            }
            if((y < 0) || (grid.size() < 0) ||  (y >= grid.at(0).size())){
                return false;
            }
            //obstacle-free
            if(grid.at(x).at(y) == 0){
                return false;
            }
            return true;
        }

        std::vector<int> neighbor(int state_)
        {
            int c, r;
            std::tie(c,r) = get_index(state_);
            std::vector<state> valid_neigh = {};
            int x, y;
            for(auto &n: neigh){
                x = r + n.at(0);
                y = c + n.at(1);
                if(not is_valid_cell(x,y)){
                    continue;
                }
                valid_neigh.push_back(to_state(x,y));
            }

            return valid_neigh;
        }

        // long long key(int state_)
        // {
        //     return 10;
        // }
};