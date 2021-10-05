//Depth Limited Search
#include<iostream>
#include<stack>
#include"GratH.h"
class DLS:public TheGrath
{
    public:
        DLS(){std::cout<<"Da khoi tao DLS\n";}
        ~DLS(){std::cout<<"Da giai phong DLS\n";}
        void runDLS()
        {
            node_stack.push(start);
            visit[start] = true;
            bool flag = false;
            trace[start] = -1;
            int depth = 0;
            do
            {
                getNodeStack();
                int check = node_stack.top();
                int current = check;
                for(int column = 0; column < no_node; column++)
                    if(matrix[check][column] == 1 && visit[column] == false)
                    {
                        node_stack.push(column);
                        visit[column] = true;
                        check = column;
                        trace[column] = check;
                        depth++;
                        break;
                    }
                if(check == current || depth == limit)
                {
                    depth--;
                    node_stack.pop();
                }
                if(check == goal)
                    break;
            }
            while(!node_stack.empty());
        }
    private:
        std::stack<int> node_stack;
        std::vector<int> trace = {0};
        int limit = 3;
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
        void getTrace()
        {
            int node = goal;
            std::cout<<node<<"<-";
            while(node != start)
            {
                node = trace[start];
                if(node == start)
                    std::cout<<node<<"\n";
                else
                    std::cout<<node<<"<-";
            }
        }
};
