#include <bits/stdc++.h>
using namespace std;

int n_cores;
int n_pins;
int n_partitions;
#define n_generations 13
#define total_parent_population 1000
#define total_children_population 1000

int sd=73,x,y,z,t,w;

int hash[100000001];

int parent_population [total_parent_population+1] [103];

int children_population [total_children_population+1] [103];

int parent_children [total_parent_population+total_children_population+1] [103];

vector < pair < int , int > > parent_fitness (total_parent_population+1);

vector < pair < int , int > > children_fitness (total_children_population+1);

vector < pair < int , int > > both_fitness (total_parent_population+total_children_population+1);

int parent_cummulative_fitness [total_parent_population+1];

int children_cummulative_fitness [total_children_population+1];

int core_data [1000] [103];

void read_problem (const char *filename)
{
	FILE *file;
	
	int i, j;
	
	char comma;
	
	file = fopen(filename, "r");
	
	for (i = 1; i <= n_pins; i++)
	{
		int tmp = 0;
		
		fscanf(file, "%d", &tmp);
		//printf("tmp = %d\n", tmp);
		
		for (j = 1; j <= n_cores; j++)
		{
			fscanf(file, "%c", &comma);
			fscanf(file, "%d", &(core_data[i][j]));	
		}
		tmp = getc(file);
		if (isdigit(tmp))
			ungetc(tmp, file);
	}
}

void random_seed(int s)
{
	x=s;
  y = x * s;
  z = y * s;
  w = z * s;
}

int random_number()
{	 
	t = x ^ (x << 11);
  x = y; y = z; z = w;                       
  return w = abs((w ^ (w >> 19)) ^ (t ^ (t >> 8))); 
}

int hash_value(int a[])
{
	int h=0;
	for(int j=n_cores+n_partitions;j>=1;j--)
	{
		h+=((a[j]*(pow(2,j-1)))+a[j]);
	}
	return h;
}

void make_population()
{
	int a1[103];
	int i=1;
	while(i<=total_parent_population)
	{cout<<i<<endl;
		sd=sd+i;
		random_seed(sd);         int y=n_pins-n_partitions+1;        int x;        int counter=0;
		for(int j=1;j<=n_partitions-1;j++)
		{
			x=random_number()%y;
			x++;
			parent_population[i][j]=x;          a1[j]=x;          counter+=x;
			y=y-x+1;//cout<<"x="<<x<<"y="<<y<<endl;
		}
		parent_population[i][n_partitions]=n_pins-counter;//cout<<"x="<<n_pins-counter<<endl;
		for(int j=n_partitions+1;j<=n_cores+n_partitions;j++)
		{
			x=random_number()%n_partitions;
			x++;
			parent_population[i][j]=x;
			a1[j]=x;
		}
		int h=hash_value(a1);//cout<<h;
		if(hash[h]==0)
		{
			//i++;
			hash[h]=1;
		}i++;
	}
}

void clear_fitness()
{
	for(int i=1;i<=total_parent_population;i++)
	{
		parent_fitness[i].first=0;
		parent_fitness[i].second=0;
	}
}

void calculate_fitness()
{
	int sum[103];
	for(int i=1;i<=total_parent_population;i++)
	{
		int x,y;
		parent_fitness[i].second=i;
		
		for(int k=1;k<=n_partitions;k++)
		sum[k]=0;
		
		for(int j=n_partitions+1;j<=n_cores+n_partitions;j++)
		{
			x=parent_population[i][j];
			y=parent_population[i][x];
			sum[x]+=core_data[y][j-n_partitions];
		}
		
		int max_sum=0;
		for(int k=1;k<=n_partitions;k++)
		{
			if(max_sum<sum[k])
			max_sum=sum[k];
		}
		parent_fitness[i].first=max_sum;
	}
}

void arrange_parent_fitness()
{
	int temp[total_parent_population+1][n_cores+n_partitions+1];
	
	for(int i=1;i<=total_parent_population;i++)
	{
		int x=parent_fitness[i].second;
		
		for(int j=1;j<=n_cores+n_partitions;j++)
		{
			temp[i][j]=parent_population[x][j];
		}
	}
	
	for(int i=1;i<=total_parent_population;i++)
	{
		for(int j=1;j<=n_cores+n_partitions;j++)
		{
			parent_population[i][j] = temp[i][j];
		}
	}
	
}

void calculate_cummulative_fitness()
{
	int sum=0;
	for(int i=1;i<=total_parent_population;i++)
	{
		sum+=parent_fitness[i].first;
		parent_cummulative_fitness[i]=sum;
	}
}

int total_fitness()
{
	int sum=0; 
	for(int i=1;i<=total_parent_population;i++)
	{
		sum+=parent_fitness[i].first;//cout<<"sum="<<sum1;
	}
	return sum;
}

int select_chromosomes()
{
	//cout<<"total_fitness="<<total_fitness()<<endl;
	sd++;
	random_seed(sd);
	int x = random_number () % total_fitness();  
	int y = lower_bound ( parent_cummulative_fitness+1 , parent_cummulative_fitness + total_parent_population , x ) - parent_cummulative_fitness;
	y=total_parent_population-y+1;
   	//cout<<"x="<<x<<"y="<<y<<endl;
	return y;
}
///////////////////////////////////////////////////////////////////////////
void crossover()
{
	int a1[103],a2[103];             cout<<"h";
	int k1=1,k2=2,i=1;
	while(i<=total_children_population/2)
	{
		int chromosome1=select_chromosomes();          int chromosome2=select_chromosomes();
		sd++;
		random_seed(sd);
		int position=random_number()%n_cores;
		position+=n_partitions+1;         //cout<<"position="<<position<<endl;     

		for(int j=1;j<position;j++)
		{
			children_population[k1][j] = parent_population[chromosome1][j];
			children_population[k2][j] = parent_population[chromosome2][j];
		}
		
		for(int j=position;j<=n_cores+n_partitions;j++)
		{
			children_population[k2][j] = parent_population[chromosome1][j];
			children_population[k1][j] = parent_population[chromosome2][j];
		}
		
		for(int j=1;j<=n_cores+n_partitions;j++)
		{
			a1[j]=children_population[k1][j];
			a2[j]=children_population[k2][j];
		}
		
		int h1=hash_value(a1);
		int h2=hash_value(a2);
		if(hash[h1]==0&&hash[h2]==0)
		{
			i++;
			k1+=2;
			k2+=2;
			hash[h1]=1;
			hash[h2]=1;
		}
	}	
	/*for(int i=1;i<=total_children_population;i++)
		{
			for(int j=1;j<=n_cores+2;j++)
			{
				cout<<children_population[i][j]<<"  ";
			}
			cout<<endl;
		}*/ 
}

void combine_both_generations()
{
	for(int i=1;i<=total_parent_population;i++)
	{
		for(int j=1;j<=n_cores+n_partitions;j++)
		{
			parent_children[i][j]=parent_population[i][j];
		}
	}
	for(int i=1;i<=total_children_population;i++)
	{
		for(int j=1;j<=n_cores+n_partitions;j++)
		{
			parent_children[total_parent_population+i][j]=children_population[i][j];
		}
	}
/*	for(int i=1;i<=total_children_population;i++)
		{
			for(int j=1;j<=n_cores+2;j++)
			{
				cout<<children_population[i][j]<<"  ";
			}
			cout<<endl;
		}*/
	
/*	for(int i=1;i<=total_parent_population+total_children_population;i++)
		{
			for(int j=1;j<=n_cores+2;j++)
			{
				cout<<parent_children[i][j]<<"  ";
			}
			cout<<endl;
		}*/
}

void clear_both_fitness()
{
	for(int i=1;i<=total_parent_population+total_children_population;i++)
	{
		both_fitness[i].first=0;
		both_fitness[i].second=0;
	}
}

void calculate_both_fitness()
{
	int sum[103];
	for(int i=1;i<=total_parent_population + total_children_population;i++)
	{
				int x,y;
		both_fitness[i].second=i;
		
		for(int k=1;k<=n_partitions;k++)
		sum[k]=0;
		
		for(int j=n_partitions+1;j<=n_cores+n_partitions;j++)
		{
			x=parent_children[i][j];
			y=parent_children[i][x];
			sum[x]+=core_data[y][j-n_partitions];
		}
		
		int max_sum=0;
		for(int k=1;k<=n_partitions;k++)
		{
			if(max_sum<sum[k])
			max_sum=sum[k];
		}
		both_fitness[i].first=max_sum;
	}
}

void arrange_both_fitness()
{
	int temp[total_parent_population+total_children_population+1][n_cores+n_partitions+1];
	
	for(int i=1;i<=total_parent_population+total_children_population;i++)
	{
		int x=both_fitness[i].second;
		
		for(int j=1;j<=n_cores+n_partitions;j++)
		{
			temp[i][j]=parent_children[x][j];
		}
	}
	
	for(int i=1;i<=total_parent_population+total_children_population;i++)
	{
		for(int j=1;j<=n_cores+n_partitions;j++)
		{
			parent_children[i][j] = temp[i][j];
		}
	}
	
	/*for(int i=1;i<=total_parent_population+total_children_population;i++)
		{
			for(int j=1;j<=n_cores+2;j++)
			{
				cout<<parent_children[i][j]<<"  ";
			}
			cout<<endl;
		}*/
}

void find_next_generation_parent_population()
{
	for(int i=1;i<=total_parent_population;i++)
	{
		for(int j=1;j<=n_cores+n_partitions;j++)
		{
			parent_population[i][j]=parent_children[i][j];
		}
	}
}

void select_next_generation()
{
	combine_both_generations();
	clear_both_fitness();
	calculate_both_fitness();
	sort(both_fitness.begin(),both_fitness.end());
	/*for(int i=1;i<=total_parent_population+total_children_population;i++)
		{
			cout<<both_fitness[i].first<<"  "<<both_fitness[i].second<<endl;
		}*/
	arrange_both_fitness();
	find_next_generation_parent_population();
}

int main()
{
	cout<<"enter the number of pins and number of cores and number of partitions\n";
	cin>>n_pins>>n_cores>>n_partitions;
	
	read_problem("d695.csv");
	/*for(int i=1;i<=n_pins;i++)
	{
		for(int j=1;j<=n_cores;j++)
		{
			cout<<core_data[i][j]<<"\t";
		}
		cout<<endl;
	}*/
	
	make_population();
	/*for(int i=1;i<=total_parent_population;i++)
	{
		for(int j=1;j<=n_cores+n_partitions;j++)
		{
				cout<<parent_population[i][j]<<"  ";
		}
		cout<<endl;
	}*/
	
	for(int i=0;i<=n_generations;i++)
	{
		cout<<i<<endl;
		
		clear_fitness();
		
	
		calculate_fitness();

		
		sort(parent_fitness.begin()+1,parent_fitness.end());
		/*for(i=1;i<=total_parent_population;i++)
		{
			cout<<parent_fitness[i].first<<"  "<<parent_fitness[i].second<<endl;
		}  */                                                            
		
		arrange_parent_fitness();
		/*for(int i=1;i<=total_parent_population;i++)
		{
			for(int j=1;j<=n_cores+n_partitions;j++)
			{
				cout<<parent_population[i][j]<<"  ";
			}
			cout<<endl;
		}*/
		if(i==n_generations)
		break;
		
		calculate_cummulative_fitness();
		/*for(i=1;i<=total_parent_population;i++)
		{
			cout<<parent_cummulative_fitness[i]<<endl;
		}*/
		
		crossover();
		
		select_next_generation();
/*		for(int i=1;i<=total_parent_population;i++)
		{
			for(int j=1;j<=n_cores+n_partitions;j++)
			{
				cout<<parent_population[i][j]<<"  ";
			}
			cout<<endl;
		}*/
	}
	ofstream output("output.csv");
	for(int i=1;i<=total_parent_population;i++)
	{
		output << parent_fitness[i].first << ",";
		for(int j=1;j<=n_cores+n_partitions;j++)
		{
				output<<parent_population[i][j]<<",";
		}
		output<<endl;
	}
	output.close();
	
	cout<<" final optimized test time = "<< parent_fitness[1].first<<endl;
	
	cout<<" pins used in the partition are    "<<endl;
	
	for(int j=1;j<=n_partitions;j++)
	cout<<parent_population[1][j]<<"   ";
	cout<<endl;
	
	cout<<" arrangement of pins = "<<endl;
	
	for(int j=n_partitions+1;j<=n_cores+n_partitions;j++)
	{
		cout<<parent_population[1][j]<<"   ";
	}
	
	
	return 0;
}
