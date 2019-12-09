#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 
#include <time.h>

using namespace std;



/*
    read the file from the data file 
    please enter the exactly number of games 
    weak to deal bad user input 
*/
void read_filedata(int file_number , int& num, int* fun)
{
	string line;
    ifstream myfile ("data/solverData_num_" + std::to_string(file_number) +  ".txt");
    cout << "The open file is: " << "data/solverData_num_" + std::to_string(file_number) +  ".txt" << endl;
    if (myfile.is_open())
    {
    	//cout << "file open" << endl;
        getline (myfile,line);
        getline (myfile,line);

        // convert string to char array
        char read_number[line.size() + 1];
        strcpy(read_number , line.c_str());
        
        // get the number of file and then give this number to main file
        // included some type convert
        string temp_num = "";
        for (int i = 0; i < strlen(read_number); i++)
        {
        	if (isdigit(read_number[i]) == true)
        		temp_num += read_number[i];
        }
        // string to int 
        num = std::stoi(temp_num);

        getline (myfile,line);
        getline (myfile,line);
        getline (myfile,line);

        // convert string to char array
        char read_fun[line.size() + 1];
        strcpy(read_fun , line.c_str());

        // read the fun array in the file
        // if we meet a comma, push temp_fun to the main fun array 
        string temp_fun = "";
        int fun_index = 0;
        int insert_fun = 0;
        for (int i = 0; i < strlen(read_fun); i++)
        {
        	//cout << "read_fun:" << read_fun[i] << endl;
            // deal with negative number 
        	string check_minus = "";
        	check_minus += read_fun[i];
   	        if (isdigit(read_fun[i]) == true || check_minus == "-")
        		temp_fun += read_fun[i];
        	check_minus = "";

        	string check_commma  = "";
        	check_commma = read_fun[i+1];
        	if (check_commma == "," || check_commma == "]")
        	{
        		insert_fun = std::stoi(temp_fun);
        		//cout << "The value of insert_fun: " << insert_fun << endl;
        		fun[fun_index] = insert_fun;
        		//cout << "fun[fun_index] == " << fun[fun_index] << endl;
        		fun_index++;
        		temp_fun = "";
        		check_commma = "";
        	}
        	// if (check_commma == ";")
        	// 	fun[fun_index] = insert_fun;
        }
    }
    
    myfile.close();
}



int main() {

	/************************************************************************************************/
    int number_of_file = 0;
    cout << "Please enter the number games your want to play(exactly the number like 5,100,500): ";
    cin >> number_of_file;
	int num;

	const int cap = 5;
	const int refill = 2;

	int* fun = new int[number_of_file];

	int token[num] = {};
	int play[num] = {0};
	/************************************************************************************************/

    int current_token = cap;
    int future_token = 0;
    int total_fun = 0;
    int reserve = 0;
    int i = 0;

    read_filedata(number_of_file, num, fun);

    // cout << "In main num: " << num <<endl;
    // cout << "main fun: " << fun[0] << endl;
    // cout << "main fun: " << fun[1] << endl;
    // cout << "main fun: " << fun[2] << endl;
    // cout << "main fun: " << fun[3] << endl;
    // cout << "main fun: " << fun[4] << endl;
    // cout << "main fun: " << fun[5] << endl;
   	//int index_for_fun = 0;
    // for (; index_for_fun < num; index_for_fun++)
    // {
    // 	cout << "index_for_fun: " << index_for_fun << endl; 
    // 	cout << "for loop print fun: " << fun[index_for_fun] << endl;
    // }
    

    time_t start, end; 

    time(&start); 
    ios_base::sync_with_stdio(false); 



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

    cout << "tokens for each game: ";
    for (int index = 0; index < num; index++)
    {
        cout << token[index] << "  "; 
    }
    cout << endl;

    cout << "play for each game:   ";
    for (int i = 0; i < num; i++)
    {
        cout << play[i] << "  ";
    }
    cout << endl;

    cout << "The total fun is " << total_fun << endl;

    double time_taken = double(end - start); 
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5); 
    cout << " sec " << endl; 

    delete [] fun;
}