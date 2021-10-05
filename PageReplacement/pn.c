#include<iostream>
using namespace std;
int main()
{
	int pg[]  = {7, 4, 5, 3, 2, 4, 8, 5, 9}; //8
	int pgn = sizeof(pg);
	int pgzero = sizeof(pg[0]);
	int pn = pgn/pgzero;
	cout<<pgn<<" "<<pgzero<<" "<<pn<<"\n";
}
