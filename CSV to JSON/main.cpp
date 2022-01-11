/*
 File: main.cpp
 Description: Reads a CSV file and converts it to JSON format. 
            For extra credit, the program also allows the user to search for a specific country and date, and then prints data pertaining to country and date.
 Created: 6/5/20
 Author: Tim Chester
 email: chestert@student.vvc.edu
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<sstream>
#include "csvparser.h"

using namespace std;

/**
*This was moved into csvparser as a member function
*/
std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{
    CSVParser data;

    ifstream data_file("owid_covid_data.csv");

    data.read_csv(data_file);
    
    data_file.close();

    data.print_json();
    
    data.search_interface();

    return 0;
}

