#include<iostream>
#define MAX 10
class Banker
{
    public:
        Banker(){ std::cout<<"Da khoi tao Banker's.\n"; }
        Banker(int n_pro, int n_res){ setNoProcess(n_pro); setNoResource(n_res); }
        ~Banker(){ std::cout<<"Da giai phong.\n"; }
        bool checkNo(int n) { return (n >= 0 && n <= MAX); }
        void setNoProcess(int n) { if(checkNo(n)) no_process = n; else no_process = 0; }
        void setNoResource(int n) { if(checkNo(n)) no_resource = n; else no_resource = 0; }
        void setTotal(){ for(int index = 0; index < no_resource; std::cin>>total[index++]); }
        void setAlloc(){setMatrix(allocation);}
        void setMax_(){setMatrix(max_need);}
        int getNoProcess() { return no_process; }
        int getNoResource() { return no_resource; }
        void getTotal()
        {
            for(int index = 0; index < no_resource; std::cout<<total[index++]<<"\t");
                std::cout<<"\n";
        }
        void getSequence()
        {
            for(int index = 0; index < no_process - 1; index++)
                    std::cout<<"P"<<sequence[index]<<"->";
            std::cout<<"P"<<sequence[no_process - 1]<<"\n";
        }
        void getAlloc(){ getMatrix(allocation); }
        void getMax_Need(){ getMatrix(max_need); }
        void runAlgorithm()
        {
            set_Need();
            currentTotal();
            setSequence();
        }
    private:
        int no_process, no_resource;
        int total[MAX], sequence[MAX], flag[MAX] = {0};
        int allocation[MAX][MAX], max_need[MAX][MAX];
        void setMatrix(int a[][MAX])
        {
            for(int row = 0; row < no_process; row++)
                for(int column = 0; column < no_resource; column++)
                    std::cin>>a[row][column];
        }
        void getMatrix(int a[][MAX])
        {
            for(int row = 0; row < no_process; row++)
            {
                for(int column = 0; column < no_resource; column++)
                    std::cout<<a[row][column]<<"\t";
                std::cout<<"\n";
            }
        }
        void set_Need()
        {
            for(int row = 0; row < no_process; row++)
                for(int column = 0; column < no_resource; column++)
                    max_need[row][column] -= allocation[row][column];
        }
        void currentTotal()
        {
            for(int column = 0; column < no_resource; column++)
                for(int row = 0; row < no_process; row++)
                    total[column] -= allocation[row][column];
        }
        void setSequence()
        {
            int row = 0, index = 0;
            while(index < no_process)
            {
                if(isSelect(row))
                    if(flag[row] == 0)
                    {
                        flag[row] = 1;
                        sequence[index++] = row + 1;
                        backTotal(row);
                    }
                row = row == no_process - 1 ? 0 : row + 1;
            }
        }
        bool isSelect(int row)
        {
            for(int column = 0; column < no_resource; column++)
                if(max_need[row][column] > total[column])
                    return false;
            return true;
        }
        void backTotal(int row)
        {
            for(int column = 0; column < no_resource; column++)
                total[column] += allocation[row][column];
        }
};
int main()
{
    int pro, res; 
    std::cout<<"Enter no of process: ";
    std::cin>>pro;
    std::cout<<"Enter no of resource: ";
    std::cin>>res;
    Banker bk(pro, res);
    std::cout<<"Enter total resource:\n";
    bk.setTotal();
    std::cout<<"Enter allocation:\n";
    bk.setAlloc();
    std::cout<<"Enter Max.Need:\n";
    bk.setMax_();
    std::cout<<"Run Banker Algorithm:\n";
    bk.runAlgorithm();
    std::cout<<"Following is the SAFE Sequence:\n";
    bk.getSequence();
    return 0;
}
