#include<iostream>
#include<vector>
class SchAlg
{
	public:
		SchAlg(){ std::cout<<"Da khoi tao doi tuong\n";}
		SchAlg(int lim):limit(lim){waiting_time.push_back(0);}
		~SchAlg(){std::cout<<"Da giai phong\n";}
		void setVector(std::vector<int> &vec)
		{
			for(int i=0; i<limit; i++)
			{
				int a;
				std::cin>>a;
				vec.push_back(a);
			}
		}
		void getTable()
		{
			for(int i=0; i<limit; i++)
				std::cout<<burst_time[i]<<"\t"<<waiting_time[i]<<"\t"<<turn_around_time[i]<<std::endl;
		}
		std::vector<int> &getBurst(){return burst_time;}
		std::vector<int> &getWaiting(){return waiting_time;}
		std::vector<int> &getTurnAround(){return turn_around_time;}
		int totalTime(std::vector<int> time_array)
		{
			int total=0;
			for(int i=0;i<limit;i++) total+=time_array[i];
			return total;
		}
		float averageTime(int total)
		{
			if(limit!=0)	return (float)total/limit;
			else return -1;
		}
		virtual void runAlgorithm(){ std::cout<<"Chay thuat toan chon tien trinh\n";}
	protected:
		int limit;
		std::vector<int> burst_time, waiting_time, turn_around_time;
		void tableProcess()
		{
			turn_around_time.push_back(burst_time[0]);
			for(int i=1;i<limit;i++)
			{
				waiting_time.push_back(turn_around_time[i-1]);
				turn_around_time.push_back(burst_time[i]+waiting_time[i]);
			}
		}
		template <typename T>
			void swap_(T &a, T &b)
			{	T temp = a; a = b; b = temp; }
		void exchangeSortAsc(std::vector<int> &vec)
		{
			for(int i=0;i<limit-1;i++)
				for(int j=i+1;j<limit;j++)
					if(vec[i]>vec[j])
						swap_(vec[i], vec[j]);
		}
		void exchangeSortAsc(std::vector<int> &vec1, std::vector<int> &vec2)
		{
			for(int i=0;i<limit-1;i++)
				for(int j=i+1;j<limit;j++)
					if(vec1[i]>vec1[j])
					{
						swap_(vec1[i], vec1[j]);
						swap_(vec2[i], vec2[j]);
					}
		}
};
class FCFS:public SchAlg
{
	public:
		FCFS(){ std::cout<<"Da khoi tao FCFS\n";}
		FCFS(int lim): SchAlg(lim){}
		~FCFS(){std::cout<<"Da giai phong FCFS\n";}
		void runAlgorithm(){tableProcess();}
};
class SJF: public SchAlg
{
	public:
		SJF(){}
		SJF(int lim):SchAlg(lim){}
		~SJF(){std::cout<<"Da giai phong SJF\n";}
		void runAlgorithm()
		{
			exchangeSortAsc(burst_time);
			tableProcess();
		}
};
class Priority:public SchAlg
{
	public:
		Priority(){}
		Priority(int lim):SchAlg(lim){}
		~Priority(){std::cout<<"Da giai phong Priority\n";}
		std::vector<int> &getPriority(){return priority;}
		void runAlgorithm()
		{
			exchangeSortAsc(priority, burst_time);
			tableProcess();
		}
	private:
		std::vector<int> priority;
};
class RR:public SchAlg
{
	public:
		RR(){ time_slice = 0; index_burst = 0; }

		RR(int lim):SchAlg(lim){ index_burst = 0; }

		~RR(){std::cout<<"Da giai phong Round Robin\n";}
		
		void setTimeSlice(int a){ time_slice = a;}
		
		void getTableFromTo()
		{
			for(int i=0;i<to_time.size();i++)
				std::cout<<from_time[i]<<"\t"<<to_time[i]<<"\n";
		}
		
		void runAlgorithm()
		{
			tableFromTo();
			tableProcessRR();
		}
	private:
		int time_slice, index_burst;
		
		std::vector<int> from_time, to_time, process, solve, burst;
		
		int solveTimeSlice()
		{
			int a = burst_time[index_burst];
			if(a >= time_slice)
				a = time_slice;
			burst_time[index_burst] -= a;
			if(a!=0)
			{
				process.push_back(index_burst + 1);
				solve.push_back(a);
				burst.push_back(burst_time[index_burst]);
			}
			index_burst = index_burst == limit - 1 ? 0 : index_burst + 1;
			return a;
		}
		void tableFromTo()
		{
			from_time.push_back(0);
			bool check = true;
			do
			{
				int temp = solveTimeSlice();
				if(temp != 0)
				{
					temp += from_time.back();
					to_time.push_back(temp);
					if(totalTime(burst_time)!=0) from_time.push_back(temp);
					else check = false;
				}
			}while(check);
		}
		void tableProcessRR()
		{
			for(int i=0;i<limit;i++)
				for(int j=0;j<to_time.size();j++)
					if(process[j] != ( i + 1)) waiting_time[i]+=solve[j];
					else if(burst[j]==0)
					{
						turn_around_time.push_back(to_time[j]);
						break;
					}
		}
};
int main()
{
	RR *scheduling = new RR(3);
	scheduling->setVector(scheduling->getBurst());
	scheduling->setTimeSlice(3);
	scheduling->runAlgorithm();
	scheduling->getTableFromTo();
	scheduling->getTable();
	delete scheduling;
	return 0;
}
