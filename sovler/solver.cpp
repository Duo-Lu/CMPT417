#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 

using namespace std;



void read_filedata(int number , int& num)
{
	string line;
    ifstream myfile ("data/solverData_num_" + std::to_string(number) +  ".txt");
    if (myfile.is_open())
    {
        getline (myfile,line);
        
        getline (myfile,line);

        char read_number[line.size() + 1];
        strcpy(read_number , line.c_str());
        
        string temp_num = "";
        for (int i = 0; i < strlen(read_number); i++)
        {
        	//cout << "line:" << read_number[i] << endl;
        	if (isdigit(read_number[i]) == true)
        		temp_num += read_number[i];
        	cout << temp_num << endl;
        }
        num = std::stoi(temp_num);
        //cout << "num is: " << num << endl; 
        //cout << "The type of num is:" << std::typeof(num) <<endl;


        getline (myfile,line);
        getline (myfile,line);
        getline (myfile,line);

        cout << line << endl;

        char read_fun[line.size() + 1];
        strcpy(read_fun , line.c_str());

        string temp_fun = "";
        for (int i = 0; i < strlen(read_fun); i++)
        {
        	cout << "read_fun:" << read_fun[i] << endl;
   	        if (isdigit(read_fun[i]) == true)
        		temp_fun += read_number[i];
        	cout << temp_fun << endl;
        }
    }
    
    myfile.close();
}



int main() {

	/***********************************************************************/
	int num;

	const int cap = 5;
	const int refill = 2;

	const int fun[num] = {-11, -8, 14, -3, 20, -17, -8, -18, -9, 17, -9, -14, 4, -7, -8, -10, -16, -13, -11,
	                         10, 2, 7, -11, 2, 13, -5, -17, -5, 16, -3, -20, 6, -1, -14, -8, 13, -7, 20, -10, 12, -13, 9, -11, -10, 4};

	int token[num] = {};
	int play[num] = {0};

	/***********************************************************************/

    int current_token = cap;
    int future_token = 0;
    int total_fun = 0;
    int reserve = 0;
    int i = 0;

    read_filedata(20, num);

    time_t start, end; 

    time(&start); 
    ios_base::sync_with_stdio(false); 


    //cout << "In main num: " << num <<endl;

    for (; i < num; i++)
    {
        // for every game, we play it first. Therefore, minus minus before current_token
        token[i] = current_token--;
        play[i]++;

        // negative fun game, we just play it once
        if (fun[i] < 0)
        {
            total_fun += fun[i];
            current_token = min(current_token + refill , cap);
        }
        // positive fun games 
        else
        {
            int next_game;
            future_token = refill;
            next_game = i + 1;
            // if future_token less than capacity, that means tokens reach the capacity but we don't find 
            // the fun games which fun value greater than now. Therefore, current games can play all the 
            // current tokens
            while (future_token < cap)
            {
                // if we have the next game
                if (next_game < num)
                {
                    // we find a game which fun value greater than current game
                    if (fun[next_game] > fun[i])
                    {
                        // the next game have at least more qualificaiton to play the capacity.
                        // In other words, the next game has potenital to play the capacity.
                        // Therefore, we reserve at least (cap - future_token) to next game
                        reserve = cap - future_token;
                        // if we need reserve more than current token, we just play it once only
                        if (reserve > current_token)
                        {
                            reserve = current_token;
                        }
                        break;
                    }
                }
                else
                {
                    break;
                }
                next_game++;
                future_token += refill - 1;
            }

            current_token -= reserve;
            play[i] += current_token;
            total_fun += (play[i] * fun[i]);
            current_token = min(reserve + refill , cap);
            reserve = 0;
        }
    }

    time(&end); 

    // cout << "fun for each game:   ";
    // for (int i = 0; i < num; i++)
    // {
    //     cout << fun[i] << "  "; 
    // }
    // cout << endl;

    // cout << "tokens for each game: ";
    // for (int i = 0; i < num; i++)
    // {
    //     cout << token[i] << "  "; 
    // }
    // cout << endl;

    // cout << "play for each game:   ";
    // for (int i = 0; i < num; i++)
    // {
    //     cout << play[i] << "  ";
    // }
    // cout << endl;

    // cout << "The total fun is " << total_fun << endl;

    // double time_taken = double(end - start); 
    // cout << "Time taken by program is : " << fixed 
    //      << time_taken << setprecision(5); 
    // cout << " sec " << endl; 
}