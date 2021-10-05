//Depth First Search
#include<iostream>
#include<stack>
#include<vector>
#include "GratH.h"
class DFS:public TheGrath
{
    public:
        DFS(){std::cout<<"Da khoi tao DFS\n";}
        ~DFS(){std::cout<<"Da giai phong DFS\n";}
        void runDFS()
        {
            node_stack.push(start);
            sequence.push_back(start);
            visit[start] = true;
            do
            {
                int check = node_stack.top();
                int current = check;
                for(int column = 0; column < no_node; column++)
                    if(matrix[check][column] == 1 && visit[column] == false)
                    {
                        node_stack.push(column);
                        visit[column] = true;
                        check = column;
                        sequence.push_back(column);
                        break;
                    }
                if(check == current)
                    node_stack.pop();
            }
            while(!node_stack.empty());
            getSequence();
        }
    private:
        std::stack<int> node_stack;
        std::vector<int> trace;
        void getNodeStack()
        {
            std::stack<int> temp = node_stack;
            while(!temp.empty())
            {
                std::cout<<temp.top()<<"\t";
                temp.pop();
            }
            std::cout<<"\n";
        }
};
