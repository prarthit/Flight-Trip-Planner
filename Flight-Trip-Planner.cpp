#include<iostream>
#include<fstream>
using namespace std;

int i,cities;

struct adjNode
{
	int dest;
	int depTime;
	int arrTime;
	int price;
	string flightName;
	struct adjNode *next;
};

struct graph
{
//	int cityNo;
	struct adjNode *head;
};

struct djk
{
	int cost;
	int visited;
	int time;
};

struct adjNode *createAdjNode(int dest,int depTime,int arrTime,int price,string flightName)
{
	struct adjNode *tempNode;
	tempNode = new adjNode;
	tempNode->arrTime = arrTime;
	tempNode->depTime = depTime;
	tempNode->dest = dest;
	tempNode->flightName = flightName;
	tempNode->price = price;
	tempNode->next = NULL;
	
	return tempNode;
}

void addFlight(struct graph graphArr[],int cityNo,int dest,int depTime,int arrTime,int price,string flightName)
{
	struct adjNode *temp1Node;
	temp1Node = createAdjNode(dest,depTime,arrTime,price,flightName);
	
	temp1Node->next = graphArr[cityNo].head;
	graphArr[cityNo].head = temp1Node;
}

int findmin(struct djk dArr[],int cities)
{
	int min,size,mi=-1;
	min = INT_MAX;
	
	for(i = 1;i<cities+1;i++)
	{
		if(dArr[i].cost<min && dArr[i].visited == -1)
		{
			min = dArr[i].cost;
			mi = i;
		}
	}
	
	return mi;
}

int t1,t2;

int timecheck(struct adjNode *temp1Node,struct djk dArr[])
{
	if((temp1Node->depTime)>=t1 && (temp1Node->arrTime<=t2))
	{
		
		dArr[temp1Node->dest].time = temp1Node->arrTime + 30;
	
	int newtime = dArr[temp1Node->dest].time;	 
	int	tt=newtime % 100;
	if(tt>=60)
	{
		newtime = newtime/100;
		newtime = ((newtime)*100)+100 + tt-60;
	
		if(newtime/100 == 2400)
		{
			newtime = newtime - 2400;
		}
		
		dArr[temp1Node->dest].time = newtime;
	}
		
		return 1;	 
	}
	
	else
		return 0;

}


void dijkstra(struct graph graphArr[],struct djk dArr[],int cities,int city1,int city2)
{
	
	dArr[city1].cost = 0;
	dArr[city1].time = t1;
		
	int count=1;
	
	while(count<=cities)
	{
	
	int mincity_i;
	mincity_i = findmin(dArr,cities);

	if(mincity_i!=-1)
	{
	t1 = dArr[mincity_i].time;
	
	dArr[mincity_i].visited = 1;
	
	count++;

	
	struct adjNode *temp1Node;
	temp1Node = graphArr[mincity_i].head;
	
	
	while(temp1Node!=NULL)
	{
		if(dArr[temp1Node->dest].visited ==-1 && dArr[temp1Node->dest].cost>=(dArr[mincity_i].cost+temp1Node->price))
		{
			int t_check = timecheck(temp1Node,dArr);

			if(t_check==1)
			{
				dArr[temp1Node->dest].cost = (dArr[mincity_i].cost+temp1Node->price);
			}
		}
		
		temp1Node=temp1Node->next;
	
	}
	
	}
	else
		count++;
}

	if(dArr[city2].cost==INT_MAX)
	{
		cout<<"-1"<<endl;
	}
	else
	cout<<dArr[city2].cost<<endl;
	
	
}

void printGraph(struct graph graphArr[])
{
	for(i=1;i<=cities+1;i++)
	{
		cout<<"\nFor city "<<i<<" :\nhead ";
		struct adjNode *p;
		p=graphArr[i].head;
		while(p!=NULL)
		{
			cout<<"-> "<<p->dest<<" ";
			p = p->next;
		}
	}
}

int main()
{
	ifstream inp("test.txt");
	int flights;
	
	inp >> cities;
	inp >> flights;
	
	int src,des,tDep,tArr,fprice;
	string fname;
	
	struct djk dArr[cities+1];
	struct graph graphArr[cities+1];//city+1
	
	for(i=0;i<cities+1;i++)
	{	
		graphArr[i].head = NULL;
	}
	
	for(i=0;i<flights;i++)
	{
		inp >> src;
		inp >> des;
		inp >> tDep;
		inp >> tArr;
		inp >> fname;
		inp >> fprice;
	
		addFlight(graphArr,src,des,tDep,tArr,fprice,fname);
	}

	//printGraph(graphArr);
	
	int queries,c1,c2;
	
	inp>>queries;
	
	for(int n=1;n<=queries;n++)
	{
		inp>>c1;
		inp>>c2;
		inp>>t1;
		inp>>t2;
		
		for(i=0;i<cities+1;i++)
		{
		dArr[i].visited = -1;
		dArr[i].cost = INT_MAX;
		dArr[i].time = -1;
		}
		
		dijkstra(graphArr,dArr,cities,c1,c2);	
	}
	
	return 0;
}
