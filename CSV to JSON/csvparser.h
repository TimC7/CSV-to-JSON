/*
 File: csvparser.h
 Description: Class for an object that can parse a CSV file and convert it to JSON format.
 Created: 6/5/20
 Author: Tim Chester
 email: chestert@student.vvc.edu
*/

#ifndef CSVPARSER_H
#define CSVPARSER_H

#include<map>
#include<string>
#include<vector>
#include <iostream>
#include<fstream>
#include<sstream>

class CSVParser
{
private:
	std::map <std::string, std::map<std::string, std::vector <std::string>>> code_map; //The map all data from a CSV file is put into
	
	std::vector<std::string> headers; //Stores the headers for a CSV file

public:

	CSVParser(); //Default constructor, does nothing

	/**
	*splits a line into individual strings
	*@param s is the line to be split
	*@param delimiter used to separate objects on the line
	*@return vector filled with individual strings from the line
	*/
	std::vector<std::string> split(const std::string& s, char delimiter); 

	/**
	*Initializes the maps
	*@param line used to set the 2 dimensional map and vector
	*/
	void set_maps(std::string line);

	/**
	*@param _headers sets the headers
	*/
	void set_headers(std::vector<std::string> _headers);
	
	/**
	*Gets a specific header
	*@param index of the desired header
	*@return the string at that index in the headers vector
	*/
	std::string get_header(int index);

	/**
	*Reads a CSV file
	*@param file is read from
	*/
	void read_csv(std::ifstream& file);

	 //search_map();

	/**
	*Prints the code_map in JSON format
	*/
	void print_json();

	/**
	*For extra credit. Allows the user to search for a country, using the iso_code, and specific date.
	*/
	void search_interface();

	/**
	*For extra credit. Prints the data tied to the country and date.
	*@param iso_code the iso_code, which is the country, the user searched for
	*@param date the date the user searched for
	*/
	void print_search(std::string iso_code, std::string date);
};

#endif