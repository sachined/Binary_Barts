# pragma once
/*
Morse class - this is the basic level (most integral to Lab 1...took long time)
This will store a vector of pairs of char and string of ". and -" which can be converted 
into 1 and 0s for morse translation (done by Morse_translator)
Basic encryption key class This  
Used by Morse_translator to translate the bin file for checking with the character set vector
*/
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include <bitset>
//#include <utility>

using namespace std;

template<typename X, typename Y, typename Z >
struct Morse {
private:
	tuple<X, Y, Z> morning_tuple;
public:
	void set(X variable_one) { get<X>(morning_tuple) = variable_one; }
	void set(Y variable_two) { get<Y>(morning_tuple) = variable_two; }
	void set(Z variable_three) { get<Z>(morning_tuple) = variable_three; }
	void settuple(X one, Y two, Z three) { set(one); set(two); set(three); }
	X getfirst()const { return get<X>(morning_tuple); }
	Y getsecond()const { return get<Y>(morning_tuple); }
	Z getthird()const { return get<Z>(morning_tuple); }
	void getmorse()
	{ 
		X first = getfirst();
		Y second = getsecond();
		Z third = getthird();
		
		cout << "Show me the tuple\n" << first << "\n"
			<< second << "\n" << third << endl;
	}
};

typedef Morse<char, string, int> Morser;

class Morse_read : public Morser
{
	private:
		// List of Morse data class objects
		list<Morser> character_chart;

	public:
		// Constructor is set to a certain value to ensure the existence of Morse object
		Morse_read();

		// This is part of put_into_list function
		void read_from_file(string& line, int & result);

		// Reads a text file that has the pair of data per line
		void put_into_list();

		// Returns the character chart A, .- , 
		list<Morser> give_vector() {	return character_chart;	}
		
		// This will convert the second attribute of morse code into int 
		friend int convert_string_int(string morse_code);

		// This will display the error when text file was moved (most likely) or erased (NEVER)
		friend void info_file_MIA();

		// Show the character_chart (DUBUGGING)
		void show_vector();
};