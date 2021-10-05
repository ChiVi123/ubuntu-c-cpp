#include<iostream>
#include<string>
#include<queue>
#include<vector>

class PagRep
{
	public:
	PagRep()
	{
		capacity = 0;
		miss = 0;
		hit = 0;
		std::cout << "Da khoi tao\n";
	}
	
	PagRep(const std::string &st, int cap) : str(st), capacity(cap)
	{
		miss = 0;
		hit = 0;
	}
	
	~PagRep() { std::cout << "Da giai phong\n";}
	
	virtual int pageDefault()
	{
		return -1;
	}
	
	protected:
	std::string str;
	int capacity;
	int miss;
	int hit;
};

class Fifo : public PagRep
{
	public:
	Fifo() : PagRep() {}
	
	Fifo(const std::string &st, int cap) : PagRep(st, cap) {}
	
	~Fifo() { std::cout<<"Da giai phong\n";}
	
	bool enQueue(char ch)
	{
		std::queue<char> qtemp = q;
		if(q.size() < capacity)
		{
			q.push(ch);
			return true;
		}
		//mot trang khong co trong queue thi danh loi trang
		while(!qtemp.empty())
		{
			if(ch == qtemp.front())
				return false;
			qtemp.pop();
		}
		q.pop();
		q.push(ch);
		return true;
	}
	
	void setQueue()
	{
		std::queue<char> qtemp = q;
		while(!qtemp.empty())
		{
			std::cout<<qtemp.front()<<" ";
			qtemp.pop();
		}
		std::cout<<std::endl;
	}
	
	int pageDefault()
	{
		int i = 0;
		while(str[i] != '\0')
		{
			if(enQueue(str[i]))
				miss++;
			i++;
			//setQueue();
		}
		return miss;
	}
	
	private:
	std::queue<char> q;
};

class Optimal : public PagRep
{
	public:
	
	Optimal(): PagRep(){}
	
	Optimal(const std::string st, int cap): PagRep(st, cap){}
	
	~Optimal() { std::cout<<"Da gia phong class Optimal\n";}
	
	bool isVectorFull()
	{
		return (vec.size() == capacity);
	}
	
	bool isPageExist(char ch)
	{
		for(int i = 0 ; i < vec.size(); i++)
			if(vec[i] == ch)
				return true;
		return false;
	}
	
	int getVector(int index)
	{
		int iselect = 0, max = 0, j;
		for(int i = 0; i < vec.size(); i++)
		{
			int range = 0;
			for(j = index + 1; str[j] != '\0';j++)
			{
				if(vec[i] == str[j])
					break;
				range++;
			}
			if(max < range)
			{
				max = range;
				iselect = i;
			}
			if(range >= 0 && str[j] == '\0')
			{
				iselect = i;
				break;
			}
		}
		return iselect;
	}
	
	void setVector()
	{
		for(int i=0; i < vec.size(); i++)
			std::cout << vec[i] << " ";
		std::cout << std::endl;
	}
	
	int pageDefault()
	{
		for(int i = 0; str[i]!='\0'; i++)
		{
			if(isVectorFull())
			{
				if(!isPageExist(str[i]))
				{
					vec[getVector(i)] = str[i];
					miss++;
				}
			}
			else
			{
				vec.push_back(str[i]);
				miss++;
			}
		}
		return miss;
	}
	
	private:
	std::vector<char> vec;
};

class Lru: public PagRep
{
	public:
	Lru():PagRep(){}
	
	Lru(const std::string &st, int cap): PagRep(st, cap){}
	
	~Lru(){}
	
	bool isVectorFull()
	{
		return (vec.size() == capacity);
	}
	
	bool isPageExist(char ch)
	{
		for(int i = 0; i < vec.size(); i++)
			if(vec[i] == ch)
				return true;
		return false;
	}
	
	int getVector(int index)
	{
		int max = 0, iselect = 0; 
		for(int i = 0; i < vec.size(); i++)
		{
			int range = 0, j;
			for(j = index - 1; j >= 0; j--)
			{
				if(vec[i] != str[j])
					range++;
				else
					break;
			}
			if(max < range)
			{
				max = range;
				iselect = i;
			}
		}
		return iselect;
	}
	
	int pageDefault()
	{
		for(int i = 0; str[i]!='\0';i++)
		{
			if(isVectorFull())
			{
				if(!isPageExist(str[i]))
				{
					vec[getVector(i)] = str[i];
					miss++;
				}
			}
			else
			{
				vec.push_back(str[i]);
				miss++;
			}
		}
		return miss;
	}
	
	private:
	std::vector<char> vec;
};

int main()
{
	//PagRep *fifo = new Fifo("021640103121", 4);
	//PagRep *otp = new Optimal("7012030423032", 4);
	PagRep *lru = new Lru("7012030423032", 4); 
	std::cout << lru->pageDefault() << std::endl;
	delete lru;
	return 0;
}
