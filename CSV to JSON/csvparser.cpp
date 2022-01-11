/*
 File: csvparser.cpp
 Description: Implementation for the CSVParser class
 Created: 6/5/20
 Author: Tim Chester
 email: chestert@student.vvc.edu
*/

#include "csvparser.h"

CSVParser::CSVParser()
{

}

std::vector<std::string> CSVParser::split(const std::string& s, char delimiter)
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


void CSVParser::set_maps(std::string line)
{
	std::string code, date; //Strings to hold the iso_code and the date
	std::vector<std::string> tempv = split(line, ','); //splits the line and puts it into a vector
	code = tempv[0]; //iso_code should be the first piece of data in a line
	date = tempv[3]; //the date should be the fourth

	if (code_map.find(code) == code_map.end()) //checks if the code already exists. Could probably be done with emplace instead
	{
		std::map<std::string, std::vector<std::string>> temp_map; //temp map to hold the date and the vector of all the data. should be used to initalize the second map in code map
		temp_map.insert(std::pair<std::string, std::vector<std::string>>(date, tempv)); //initalize the temp map with the date and the vector gotten from split

		code_map.insert(std::pair<std::string, std::map<std::string, std::vector<std::string>>>(code, temp_map)); //insert a new element into the first map, and initailizes the second map as well
	}
	else
	{
		code_map[code].emplace(std::pair<std::string, std::vector<std::string>>(date, tempv)); //if the code was found in the first map already, then a new element (date and data tied to it) is put into the second map
	}
}

void CSVParser::set_headers(std::vector<std::string> _headers)
{
	headers = _headers;
}

std::string CSVParser::get_header(int index)
{
	return headers[index];
}

void CSVParser::read_csv(std::ifstream& data_file)
{
	std::string line;
	getline(data_file, line); //gets the first line
	set_headers(split(line, ',')); //initalizes the headers from the first line
	 
	if (data_file.is_open()) 
	{
		while (getline(data_file, line))
		{
			if (!line.empty()) //if the line is empty it won't crash 
			{
				set_maps(line);
			}
		}
	}
}

void CSVParser::print_json()
{
	for (auto const& pair1 : code_map)
	{
		std::cout << "\"" << pair1.first << "\" :  {" << std::endl;
		for (auto const& pair2 : pair1.second)
		{
			std::cout << "    " << "\"" << pair2.first << "\" :  {"<< std::endl;
			for (int i = 0; i < pair2.second.size(); i++)
			{
				std::cout << "        " << "\"" << headers[i] << "\"" << " : " << "\"" << pair2.second[i] << "\"" << "," << std::endl;
			}
			std::cout << "    }," << std::endl;
		}
		std::cout << "}," << std::endl;
	}
}

void CSVParser::search_interface()
{
	char ans;
	std::string iso_code, date;
	do
	{
		std::cout << "Would you like to search for a specific country and date? (type y to proceed, and anything else to quit) ";
		std::cin >> ans;
		if (ans == 'y')
		{
			std::cout << "Enter the country code/iso code. (must be in all capital letters)" << std::endl;
			std::cin >> iso_code;
			if (code_map.find(iso_code) != code_map.end())
			{
				std::cout << "Enter the date. (must be in YYYY-MM-DD format)" << std::endl;
				std::cin >> date;
				if (code_map[iso_code].find(iso_code) != code_map[iso_code].end())
				{
					print_search(iso_code, date);
				}
				else
				{
					std::cout << "Date not found." << std::endl;
				}
			}
			else
			{
				std::cout << "Code not found." << std::endl;
			}
		}
	} while (ans == 'y');
}

void CSVParser::print_search(std::string iso_code, std::string date)
{
	std::cout << "\"" << code_map.find(iso_code)->first << "\" :  {" << std::endl << "    \"" << code_map[iso_code].find(date)->first << "\" :  {" << std::endl;
	
	std::vector<std::string> &temp = code_map[iso_code][date];
	for (int i = 0; i < temp.size(); i++)
	{
		std::cout << "    \"" << headers[i] << "\" : \"" << temp[i] << "\"," << std::endl;
	}
	std::cout << "    }," << std::endl << "}," << std::endl;
}