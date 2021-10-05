//Uniform Cost Searh
#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include "GratH.h"
class UCS: public TheGrath
{
    public:
        UCS(){std::cout<<"Da khoi tao UCS\n";}
        ~UCS(){std::cout<<"Da gia phong UCS\n";}
        void runUCS()
        {
            trace[start] = -1;
            prio_queue.push(std::make_pair(0, start));
            do
            {
                std::pair<int, int> check = prio_queue.top();// pair<cost, node>
                prio_queue.pop();
                if(check.second == goal)
                    break;
                for(int column = 0; column < no_node; column++)
                {
                    int a = matrix[check.second][column];
                    if(a != 0)
                    {
                        prio_queue.push(std::make_pair(check.first + a*(-1), column));
                        trace[column] = check.second;
                    }
                }
            }
            while(!prio_queue.empty());
            getTrace();
        }
    private:
        std::priority_queue<std::pair<int, int>> prio_queue;
        std::vector<int> trace = {0};
        void getPrioQueue()
        {
            std::priority_queue<std::pair<int, int>> temp = prio_queue;
            while(!temp.empty())
            {
                std::cout<<temp.top().first*(-1)<<" : "<<temp.top().second<<"\t";
                temp.pop();
            }
            std::cout<<"\n";
        }
        void getTrace()
        {
            int node = goal;
            std::cout<<node<<"<-";
            while(node != start)
            {
                node=trace[node];
                if(node != start)
                    std::cout<<node<<"<-";
                else
                    std::cout<<node<<"\n";
            }
        }
};
