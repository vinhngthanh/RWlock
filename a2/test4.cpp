#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <mutex>
#include "myMutex.cpp"

using namespace std;

MyMutex mtx;
int value;

struct Instruction {
	int read; //0 is write, 1 is read
	int n;
};

bool isPrime(int n)
{
	for(int i = 2; i*i <= n; i++)
	{
		if(n % i == 0)
		{
			return false;
		}
	}
	return true;
}


void parallelOp(int n, Instruction* instructions)
{
	for(int i=0; i<n; i++)
	{
		Instruction curr = instructions[i];
		if(curr.read == 0)
		{
			mtx.lock();
			int localv = value;
			isPrime(curr.n);
			if(value != localv)
			{
				cout << "ERROR - value written during write lock" << endl;
			}
			value = curr.n;
			mtx.unlock();
		}
		else
		{
			mtx.lock();
			int localv = value;
			isPrime(curr.n);
			if(value != localv)
			{
				cout << "ERROR - value written during read lock" << endl;
			}
			mtx.unlock();
		}
	}
}

int main()
{
	using chrono::high_resolution_clock;
	using chrono::duration;
	
	auto start = high_resolution_clock::now();
	
	int p;
	cin >> p;
	
	Instruction** instructions = new Instruction*[p];
	int* count = new int[p];
	for(int i = 0; i < p; i++)
	{
		int n;
		cin >> n;
		count[i] = n;
		instructions[i] = new Instruction[n];
		for(int j = 0; j < n; j++)
		{
			int read, number;
			cin >> read;
			cin >> number;
			instructions[i][j].read = read;
			instructions[i][j].n = number;
		}
	}

	mtx.init();

	thread* threads = new thread[p];
	value = 0;
	
	for(int i=0; i<p; i++)
	{
		threads[i] = thread(parallelOp, count[i], instructions[i]);
	}
	
	
	for(int i=0; i<p; i++)
	{
		threads[i].join();
	}
	
	auto end = high_resolution_clock::now();
	duration<double, milli> time = end - start;
	
	cout<<"Duration: "<<time.count() <<" miliseconds."<<endl;
}