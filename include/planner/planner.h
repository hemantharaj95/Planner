#pragma once
#include <../include/environment/environment.h>
#include <memory>
#include <unordered_map>
#include <queue>
#include <chrono>

template<typename state>
struct Node
{
    long long g;
    long long h;
    long long parent;
    state s;
    Node()
    {
        //this->state = -1;
        this->parent = -1;
        this->g = 0;
        this->h = 0;
    }
    Node(state s_, long long parent_, long long g_, long long h_ = 0)
    {
        this->s = s_;
        this->parent = parent_;
        this->g = g_;
        this->h = h_;
    }

    bool operator<(const Node& n)const
    {
        return (this->g + this->h) >= (n.g + n.h);
    }
};

template<typename state>
class Planner
{
    protected:
        int timeout; //In millisec
        std::chrono::system_clock::time_point start_time;
        state start;
        state goal;
        std::shared_ptr<Environment<state>> env;
        std::vector<state> soln;
        Node<state> curr_node;
        std::unordered_map<state, Node<state>> close_list;
        std::priority_queue<Node<state>> open_list;
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
        virtual bool is_goal(state node)
        {
            return this->goal == node;
        }

        virtual bool is_timeout()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->start_time).count() > this->timeout;
        }

        virtual void initiate()
        {
            this->close_list.clear();
            this->open_list = std::priority_queue<Node<state>>();
            this->soln.clear();
            this->start_time = std::chrono::system_clock::now();
        }

        virtual std::vector<state> get_soln()
        {
            return this->soln;
        }
        virtual bool solve() = 0;
        
        virtual bool plan() = 0;
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
        this->initiate();
        Node<state> start_node(this->start, -1, 0);
        this->open_list.push(start_node);
        while (not this->is_timeout()){
            this->curr_node = this->open_list.top();
            this->open_list.pop();
            //Lazy removal
            auto itr = this->close_list.find(this->curr_node.s);
            if(itr != this->close_list.end()){
                continue;
            }
            this->close_list[this->curr_node.s] = this->curr_node;
            //Goal reachability condition
            if(this->is_goal(this->curr_node.s)){
                return true;
            }
            //Explore
            for(auto neigh: this->env->neighbor(this->curr_node.s))
            {
                itr = this->close_list.find(neigh);
                if(itr != this->close_list.end()){
                    continue;
                }
                this->open_list.push(Node<state>(neigh, this->curr_node.s, this->curr_node.g + 1));
            }
        }
        std::cout << "Time limit exceed " << std::endl;
        return false;
    }

    bool plan()
    {
        if(not this->env->is_valid_state(this->start)){
            std::cout << "Not valid start " << this->start << std::endl;
            return false;
        }

        if(not this->env->is_valid_state(this->goal)){
            std::cout << "Not valid goal " << this->goal << std::endl;
            return false;
        }

        if(not this->solve())
        {
            return false;
        }
        this->backtrack();
        return true;
    }

    void backtrack()
    {
        this->soln.clear();
        auto itr = this->close_list.find(this->goal);
        if(itr == this->close_list.end()){
            return;
        }

        Node<state> node = itr->second; 
        while (node.parent != -1)
        {
            this->soln.push_back(node.s);
            itr = this->close_list.find(node.parent);
            if(itr == this->close_list.end())
            {
                return;
            }

            node = itr->second;
        }

        if(node.parent == -1){
            this->soln.push_back(node.s);
        }
    }

    ~Dijkstra()
    {

    }
};