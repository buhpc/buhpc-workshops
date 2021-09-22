/**
 * Game of Life
 * 1.Any live cell with fewer than two live neighbours dies, as if caused by under-population.
 * 2.Any live cell with two or three live neighbours lives on to the next generation.
 * 3.Any live cell with more than three live neighbours dies, as if by over-population.
 * 4.Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 * 
 * I have programmed this game of life below. Although much like my own life, it seems much can still be optimized.
 * Try using OpenMP to parallelize parts of the code. I have left comments in ALL CAPS as hints.
 * change PRINT_ENABLE to true if you want to watch the game of life, but since printing is slow, keep it off while
 * testing your parallelization
 * */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <chrono>
#include <thread>
using namespace std;

#define NUMBER_OF_STEPS 100
#define GRID_SIZE 64
//set PRINT_ENABLE to true to see nice looking (and slow) graphics
#define PRINT_ENABLE false

int main()
{
    // start timer
    auto start = std::chrono::system_clock::now();
    srand(time(nullptr));
    bool grid[GRID_SIZE][GRID_SIZE];

    //LOOK HERE, COULD THIS BE PARALLELIZED? ******
    for(int i = 0;i<GRID_SIZE;i++)
        for(int j = 0;j<GRID_SIZE;j++)
            grid[i][j]=rand()%2;
    //*********************************************
    
    //print
    cout<<"----------\n";
    for(int i = 0;i<GRID_SIZE;i++){
        for(int j = 0;j<GRID_SIZE;j++){
            cout<<grid[i][j]?"  " : "\u2588\u2588";
        }
        cout<<endl;
    }
    cout<<"----------\n";
    //print
    cout<<"----------\n";
    cout<<0<<endl;
    for(int i = 0;i<GRID_SIZE;i++){
        for(int j = 0;j<GRID_SIZE;j++){
            if(grid[i][j])
                cout<<"  ";
            else cout<<"\u2588\u2588"; 
        }
        cout<<endl;
    }
    cout<<"----------\n";

    for(int t = 0;t<NUMBER_OF_STEPS;t++)
    {
        bool nextgrid[GRID_SIZE][GRID_SIZE];

        
        //LOOK HERE, THIS OUTER FOOR LOOP LOOKS MIGHTY PARALLELIZABLE IF YOU ASK ME********************

        for(int i = 0;i<GRID_SIZE;i++)
            for(int j = 0;j<GRID_SIZE;j++)
            {
                //Now check the rules for each individual square!
                //for all neighbors:
                int nliveneighbors = 0;

                for(int I = i-1;I<=i+1;I++)
                    for(int J = j-1;J<=j+1;J++)
                        if(I>=0&&I<GRID_SIZE&&J>=0&&J<GRID_SIZE&&!(I==i&&J==j))
                            nliveneighbors+=grid[I][J];
                //1.Any live cell with fewer than two live neighbours dies, as if caused by under-population
                //2.Any live cell with two or three live neighbours lives on to the next generation.
                //3.Any live cell with more than three live neighbours dies, as if by over-population.
                //If cell is dead
                if(grid[i][j])
                    nextgrid[i][j] = (nliveneighbors==2)||(nliveneighbors==3);
                //4.Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
                //If cell is dead
                else
                    nextgrid[i][j] = (nliveneighbors==3);
                
            }
        //LOOK HERE
        //copy nextgrid to grid
        for(int i = 0;i<GRID_SIZE;i++)
            for(int j = 0;j<GRID_SIZE;j++)
                grid[i][j]=nextgrid[i][j];
        //***************************************************************************************************

        //Only prints if PRINT_ENABLE is true
        if(PRINT_ENABLE){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        cout<<"----------\n"<<t+1<<endl;
        for(int i = 0;i<GRID_SIZE;i++){
            for(int j = 0;j<GRID_SIZE;j++){
                if(grid[i][j])
                    cout<<"\u2588\u2588";
                else cout<<"  "; 
            }
            cout<<endl;
        }
        cout<<"----------\n";
        }

    }
    // stop timer
    auto end = std::chrono::system_clock::now();
    // calculate runtime
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    //display runtime
    std::cout << "\nruntime:" << elapsed_seconds.count() << " ms\n\n";
    return 0;
}