/* okay 
turns out we cannot enumerate all possibilities cause that would be such a huge number that isnt even representable even n = 10, 2^10 is a huge number

solution is we must use dp

we observe that in the knapsack problem the recurrence relation is as follows:

dp[k][c] = max(dp[k-1][c], dp[k-1][c-w[k]] + v[k] -> if is valid)

we note that in this solution, to obtain value at item k, we must know solution at item k-1
however to get solution at item k at capacity c, we do not need to know the solution at item k, capacity c-1
this means that we can compute the solutions of the same item with different capacities independently

ex.

let n = 3, maxW = 4
v = [4,5,1]
w = [1,2,3]

then dp table:

wi = 0 | 1 | 2 | 3
vi = 0 | 0 | 0 | 0
vi = 1 | 4 | 4 | 4 
vi = 2 | 4 | 5 | 9
vi = 3 | 4 | 5 | 9


*/


#include <iostream>
#include <thread>
#include <stdlib.h>
#include <chrono>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
using chrono::high_resolution_clock;
typedef chrono::duration<float> fsec;



int parallel_capacity(int start, int end, int** dp, int curr_item, int* w, int* v)
{

	for (int current_cap = start; current_cap < end; current_cap++)
	{	
		
		if(w[curr_item] <= current_cap)
			dp[curr_item+1][current_cap] = max(dp[curr_item][current_cap], dp[curr_item][current_cap-w[curr_item]] + v[curr_item]);
		else
			dp[curr_item+1][current_cap] = dp[curr_item][current_cap];
	}
	return 0;

	
}

int multithread_knapsack(int c, int n, int* w, int* v, int t)
{
	

	// for each element we check recurrence
	// initialize dp of size [n+1][c+1] and values should be initialized to -1 as thats the best originally
	

	int** dp = new int*[n+1];  // Create array of row pointers
	for (int i = 0; i <= n; i++)
    	dp[i] = new int[c+1]; 

	for(int i = 0; i < n+1; i++)
		for(int j = 0; j < c+1; j++)
			dp[i][j] = 0;


	// if c = 5 and t = 2 then we get block size  = 2 so we get two blocks and we skip the last capacity
	// bro we just need to figure out if were in the last block and if so just set end = c

	int block_size = c/t; 
	thread* threads = new thread[t];

	for (int i = 0; i < n; i++)
	{
		//each thread is responsible for a range
		for (int k = 0; k < t; k++)
		{

			int start = k * block_size;
			int end = min(c, (k + 1) * block_size);
			if (k == t-1)
				end = c+1;
			threads[k] = thread(parallel_capacity, start, end, dp, i, w,v);

		}

		for (int k = 0; k < t; k++)
		{
			threads[k].join();
		}

	}
	
	
	// for(int i = 0; i < n+1; i++)
	// {	for(int j = 0; j < c+1; j++)
	// 		cout << dp[i][j] << " ";
	// 	cout << "\n";
	// }
	

	return dp[n][c-1];
}


int main(int argc, char* argv[])
{
	
	int n;
	int c;
	int t;
	//cin >> n;  

	t = stoi(argv[1]);
	string filename = argv[2];
	ifstream file(filename);
	//cin >> c; 
	//cin >> t;

	file >> n >> c;

	int* w = new int[n];
	int* v = new int[n];

	


	


	for (int i = 0; i < n; i++)
	{
	    file >> w[i] >> v[i];
	}

	file.close();
	

	auto start_time = high_resolution_clock::now();
	// for single thread t = 0

	int ans = multithread_knapsack(c,n,w,v,t);
	

	auto end_time = high_resolution_clock::now();
	fsec secs = end_time - start_time;

	cout << "final ans is: " << ans;
	cout << "\nexecution time: " << secs.count();

//	for (int i = 0; i < t; i++)
//	{
//		cout << " thread " << i << " best is " << bestsums[i] << "\n";
//	}

	return 0;

}