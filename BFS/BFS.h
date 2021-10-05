#include<iostream>
#include<queue>
#include<vector>
#include "GratH.h"
class BFS:public TheGrath
{
    public:
        BFS(){std::cout<<"Da khoi tao BFS\n";}
        ~BFS(){std::cout<<"Da khoi tao BFS\n";}
        void runBFS()
        {
            node_queue.push(start);
            visit[start]=true;
            do
            {
                int node = node_queue.front();
                node_queue.pop();
                sequence.push_back(node);
                for(int column = 0; column < no_node; column++)
                    if(matrix[node][column] == 1 && visit[column] == false)
                    {
                        node_queue.push(column);
                        visit[column]=true;
                    }
            }
            while(!node_queue.empty());
            getSequence();
        }
    private:
        std::queue<int> node_queue;
        void getNodeQueue()
        {
            std::queue<int> temp = node_queue;
            while(!temp.empty())
            {
                std::cout<<temp.front()<<"\t";
                temp.pop();
            }
            std::cout<<"\n";
        }
};
