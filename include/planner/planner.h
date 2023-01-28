#pragma once
#include <../include/environment/environment.h>
#include <memory>
#include <unordered_map>
template<typename state>
class Planner
{
    protected:
        int timeout;
        state start;
        state goal;
        std::shared_ptr<Environment<state>> env;
        std::vector<state> soln;

    public:
        void set_timeout(int time)
        {
            this->timeout = time;
        }
        virtual void set_start(state start_)
        {
            this->start = start_;
        }
        virtual void set_goal(state goal_)
        {
            this->goal = goal_;
        }

        bool is_goal(state node)
        {
            return this->goal == node;
        }

        virtual void get_soln(state)
        {

        }
        virtual bool solve() = 0;
}; 

template<typename state>
class Dijkstra : public Planner<state>
{
private:
    /* data */
public:
    Dijkstra()
    {
        this->env = nullptr;
    }
    
    Dijkstra(std::shared_ptr<Environment<state>> env_)
    {   
        this->env = env_;
    }

    bool solve()
    {
        
    }

    ~Dijkstra()
    {

    }
};