//Grath header
#include<iostream>
#include<vector>
#include<fstream>
#define MAX 200
std::ifstream fi("InputGrath.txt");
class TheGrath
{
    public:
        TheGrath(){setMatrix(); std::cout<<"Da khoi tao TheGrath\n";}
        ~TheGrath(){std::cout<<"Da giai phong TheGrath\n";}
        void getMatrix()
        {
            for(int i = 0; i < no_node; i++)
                std::cout<<"\t"<<i;
            std::cout<<"\n";
            for(int row = 0; row < no_node; row++)
            {
                std::cout<<row;
                for(int column = 0; column < no_node; column++)
                    std::cout<<"\t"<<matrix[row][column];
                std::cout<<"\n";
            }   
        }
        void getSequence()
        {
            for(int i = 0; i < sequence.size(); i++)
                std::cout<<sequence[i]<<"\t";
            std::cout<<"\n";
        }
    protected:
        int matrix[MAX][MAX], no_node, start, goal;
        std::vector<int> sequence;
        std::vector<bool> visit = {false};
        void setMatrix()
        {
            fi>>no_node;
            for(int row = 0; row < no_node; row++)
                for(int column = 0; column < no_node; column++)
                    fi>>matrix[row][column];
            fi>>start>>goal;
        }
};
typedef TheGrath TG;
