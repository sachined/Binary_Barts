/*
Code basis for Morse_read object 
*/
#include "Morse.h"

// display the error message if text file is not in directory (FRIEND)
void info_file_MIA(){
	cerr << "The file is not in the directory... Must have been moved" <<  endl;
	system("pause");
	exit(1);
}

// makes the chart for translating the Morse (Decoder for Lab 1)
Morse_read::Morse_read()
{
	put_into_list();
}

// reads a line of data from text file that also returns a result 
// from a friend function of the class
void Morse_read::read_from_file(string& line, int & result)
{
	int convert_string_int(string);

	Morser temp;
	stringstream ss;
	string morse, first;
	size_t size;

	ss << line;
	first = ss.str();

	size = first.find(' ');
	temp.set(first[0]);
	morse = first.substr(0, size);
	morse = line.substr(size + 1);
	temp.set(morse);
	// This is where one can make values of dot and dashes for each character (result)
	// int makes each character own significant number that ranges low to high, all positive
	result = convert_string_int(morse);
	// This will set the final attribute of Morse temp (integer key)
	temp.set(result);
	// This will push temp into a vector of Morser objects
	character_chart.push_back(temp);
	line = "";
}

/* 
put_into_vector()
Reads morse_map.txt and puts the info into vector of tuple<char,string,int> 
*/
void Morse_read::put_into_list()
{
	string line;
	int result;
	ifstream read_text("morse_map.txt");
	
	if (read_text.is_open())
	{
		cout << "File is found! Reading file now...\n";

		while (!read_text.eof())
		{
			while (getline(read_text, line,'\n'))
				read_from_file(line, result);
		}
	}
	else
	{
		info_file_MIA();
	}
	read_text.close();
}

/*
When encountering - , replace with 01
When encountering . , replace with 10
// This will change the dash or dot into 1 or 2 (2 bits)
// Is used in a algortithm (that translates sequences of dots and dashes into ints
// digit is */
void change_into_a_number(int digit, int &result, int& sizedown)
{
	string temp;

	bitset<2> digits(digit);

	temp += digits.to_string();

	for (int i = 0; i < (int)temp.size(); i++)
	{
		sizedown--;
		result += ((temp[i] - '0')*(int)pow(2, sizedown));
	}
	temp = "";
}

/*
*friend function*
Algorithm that changes series of dots and dashes into int value 
(always different due to order and variety for each character)
convert_string_int(string morse_code)
Example: -.-- -> 01100101 -> 101
*/
int convert_string_int(string morse_code) 
{
	int digit, result = 0;
	int sizeup = (int)morse_code.size(), sizedown = 2 * sizeup;

	for (int i = 0; i < sizeup; i++)
	{
		if (morse_code[i] == '.')
		{
			digit = 2;
		}
		else if (morse_code[i] == '-')
		{
			digit = 1;
		}
		change_into_a_number(digit, result, sizedown);
	}
	return result;
}

/*Not necessary for this lab. It was mainly debugging*/
void Morse_read::show_vector() 
{
	for (auto f : character_chart)
	{
		cout  << "\nThis is the character - " << f.getfirst()
			<< "\nfor the following morse " << f.getsecond() <<
			"\nThis is shown in int" << f.getthird() << endl;
	}
}