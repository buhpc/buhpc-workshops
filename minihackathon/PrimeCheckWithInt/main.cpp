#include<string>
#include<fstream>
#include<iostream>
#include<math.h>
#include<chrono>


const std::string fileName = "primeList.txt";
using namespace std;
//#include<fstream.h>

int main()
{
	//opening list of number for processing
	std::string intBuf;
	std::ifstream filein (fileName);
	//error check
	if(!filein.is_open())
	{
		cout<<"Failed to open file\n";
		return 0;
	}

	int primeCount=0; //initialize counter

	//start clock
	auto start = std::chrono::system_clock::now();

	//Begin itertion
	while(std::getline(filein, intBuf))
	{
		unsigned long long int num = atoll(intBuf.c_str());
		cout<<"line: "<<intBuf<<" :done \n";

		if(num%2!=0)	//check for even number
		{
			bool isPrime=true;
			unsigned long long int targetNum = sqrt(num);
			unsigned long long int counter=3;
			
			for(counter=3; targetNum >= counter; counter+=2)
			{
				if(num%counter==0)
				{
					isPrime=false;
					break;
				}
			}
			if(isPrime)
				primeCount++;
		}//else
	}
	//end clock
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

	cout<<"Number of prime in List: "<<primeCount<<"\n";
	cout<<"total time used: "<<elapsed.count()<<" ms\n";

	return 0;
}
