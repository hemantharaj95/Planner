#include <iostream>
#include <vector>

template<typename state>
class Environment
{
    public:
        virtual std::vector<state> neighbor(state) = 0;
        virtual long long key(state) = 0;      
};

//Grid Map
template <typename state = int>
class Grid_Map : public Environment<state>
{
    public:
        Grid_Map()
        {
            std::cout << "Grid map called " << std::endl;
        }

        std::vector<int> neighbor(int state_)
        {
            return std::vector<int>{};
        }

        long long key(int state_)
        {
            return 10;
        }
};