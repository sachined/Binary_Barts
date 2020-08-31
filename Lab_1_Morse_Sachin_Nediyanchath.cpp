/*======== Lab 1 ==============
CIS 29, Larkin (Spring 2018)
Lab 1 :  Morsey Doe from Jersey

Name: Sachin Nediyanchath
IDE: VS 2017

This will read a binary file, which will then be read and
converted into integers... this can be matched with the int part
of tuples that populate the Morse chart (read from a text file)
The associated char part will be added to a string
Once complete, this string will be displayed on screen and inserted into a text file as well
========== Lab 1 =============*/

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include <bitset>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

/*--------- 1 -------1----------
GENERIC PROGRAMMING
Template structure for Morser character tuple
----------- 1 -------1--------*/
template <typename X, typename Y, typename Z>
struct Data_Morse {
public:
	// Setters
	void set(X variable_one) { get<X>(morning_tuple) = variable_one; }
	void set(Y variable_two) { get<Y>(morning_tuple) = variable_two; }
	void set(Z variable_three) { get<Z>(morning_tuple) = variable_three; }
	void settuple(X one, Y two, Z three) { set(one); set(two); set(three); }
	// Getters
	X getfirst()const { return get<X>(morning_tuple); }
	Y getsecond()const { return get<Y>(morning_tuple); }
	Z getthird()const { return get<Z>(morning_tuple); }
	// Shows the traits of tuple
	void getmorse()
	{
		X first = getfirst();
		Y second = getsecond();
		Z third = getthird();
		cout << "Tuple Summary\n" << first << "\n"
			<< second << "\n" << third << endl;
	}
private:
	tuple<X, Y, Z> morning_tuple;
};

// Defines 'Morser' as a Data_Morse (CSI) object
// (symbol (char),series of . and - (string) & unique integer)
typedef Data_Morse<char, string, int> Morser;

/*%%%%% 1 %%%%%%%%%%2%%%%%%
Morse_read class (Polymorphism)
This is inheriting Morser structure using their public functions
since it's a list of Morsers
%%%%% 1 %%%%%%%%%%%%2%%%%%%*/
class Morse_read : public Morser
{
private:
	// List of Morse data class objects
	list<Morser> character_chart;
public:
	// Constructor is set to a certain value to ensure the existence of Morse object
	Morse_read();
	// This is part of put_into_list function (made public, since it needs to use Morser set functions)
	void read_from_file(string& line, int & result);
	// Reads a text file that has the pair of data per line
	void put_into_list();
	// This will convert the second attribute of morse code into int 
	friend int convert_string_int(string morse_code);
	// This will display the error when text file was moved (most likely) or erased (NEVER)
	friend void info_file_MIA();
	// Returns the character chart 
	list<Morser> give_vector() { return character_chart; };
};

/*&&&&&&&&&& 1 &&&&&&&&3&&&&&&&
Morse_translator class
This will be used to translate the binary strings from Binary_translator
into series of dots and dashes along with @ (word space)  and ^ (letter space)
&&&&& 1 &&&&&&&&&&&&&&&&3&&&&&&*/
class Morse_translator
{
private:
	// An array of bitsets that represent . , - , @ , ^ 
	bitset<2> dash_dot[4];
	// This Morse object will store one instance of character_chart (translator) 
	Morse_read carrier;
	// This vector of ints will be used in comparison to int value of tuple from Morse_read
	vector<int> value_morse;
	// This is destination for value_morse's translated process
	string final_sentence;
public:
	// This will populate the bitset array for later calculation
	Morse_translator();
	// Used in the constructor
	void fill_table_dashdot();
	// This will be used in Binary_translator class to split the binary file into morse
	void splits_ones_zeros(vector<string> please_translate);
	// This is used to convert the items of value_morse vector into chars (last step of translation)
	string make_a_sentence();
	// This will create a text file and save the result of translation
	void create_story();
	// This will retrieve assoc. char part of int part
	friend void give_letter(int i, string & sentence, list<Morser> & holder);
};

/*&&&&&&&&&& 1 &&&&&&&&4&&&&&&&
Binary translator is used to read the binary file provided by professor
This will give a char block that will have the entire file content
This will be used to translate the char into ascii (int...bitset for morse translator class)
&&&&& 1 &&&&&&&&&&&&&&&&4&&&&&&*/
class Binary_translator
{
private:
	// This will store every letter read from binary file 
	vector<char> please_translate;
	// This will store 8-bit rep (string since this will be further split in Morse_translator)
	vector<string> translated_text;
public:
	// This is public, since this will be working with translated_text
	Morse_translator Allen;
	// Asks user for binary file and it will be processed accordingly
	Binary_translator();
	// Comes upon termination of program (suggested for clarity)
	~Binary_translator();
	// Read the binary file
	void BinaryEntry(string datafile);
	// Split the char block into char for vector please_translate to store 
	void split_and_store(unsigned char* lines, streampos size_file);
	// Convert the char into 8 bit ASCII rep and stored into translated_text
	void convert_letter_ubit();
	// Morse_translator object will access translated_text, and save results into a vector of ints
	void split_into_morse();
	//  This can be used for Morse_translator 
	vector<string> show_translated_text()const { return translated_text; }
};

//++++++++++++++1+++++++Morse_read+++++++++
// makes the chart for translating the Morse (Decoder for Lab 1)
Morse_read::Morse_read()
{
	put_into_list();
}

// reads a line of data from text file that also returns a result from a friend function of the class
void Morse_read::read_from_file(string& line, int & result)
{
	int convert_string_int(string);

	Morser temp;
	stringstream ss;
	string morse, first;
	size_t size;

	// Feeds a line of text into a stringstream
	ss << line;
	// Convert from stringstream to string 
	first = ss.str();
	// Counts characters until hitting space
	size = first.find(' ');
	// Sets 1 of 3 traits of temp Morser 
	temp.set(first[0]);
	// This will be a symbol per usual  
	morse = first.substr(0, size);
	// This will go beyond first space to . and -'s
	morse = line.substr(size + 1);
	// Sets 2 of 3 Morser
	temp.set(morse);
	// This is where one can make values of dot and dashes for each character (result)
	result = convert_string_int(morse);
	// This will set the final attribute of Morse temp (integer key)
	temp.set(result);
	// This will push temp into a list of Morser objects
	character_chart.push_back(temp);
	line = "";
}

// Reads morse_map.txt and puts the info into vector of tuple<char,string,int>
void Morse_read::put_into_list()
{
	void info_file_MIA();

	string line;
	int result;
	ifstream read_text("morse_map.txt");

	if (read_text.is_open())
	{
		cout << "File is found! Reading file now...\n";

		while (!read_text.eof())
		{
			while (getline(read_text, line, '\n'))
				read_from_file(line, result);
		}
	}
	else
	{
		info_file_MIA();
	}
	read_text.close();
}

/*^^^^^^^ 1 ^^^^^5^^^^^^
When encountering - , replace with 01
When encountering . , replace with 10
This will change the dash or dot into 1 or 2 (2 bits)
Used in convert_string_int
Last two parameters are references since this is embedded, so values are constantly different
^^^^^^^^1 ^^^^^5^^^^^^*/
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
Algorithm that changes series of dots and dashes into int value
(always different due to order and variety for each character)
Example: -.-- -> 01100101 -> 101
(Part of decoder && friend)
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

// display the error message if text file is not in directory (FRIEND)
void info_file_MIA() {
	cerr << "The file is not in the directory... Must have been moved" << endl;
	system("pause");
	exit(1);
}

//++++++++++++++2+++++++Morse_translator+++++++++
Morse_translator::Morse_translator()
{
	fill_table_dashdot();
}

// This function will fill an array from 0-3
void Morse_translator::fill_table_dashdot()
{
	for (int i = 0; i < 4; i++)
		dash_dot[i] = i;
}

//This will split be read into please_translate and
void Morse_translator::splits_ones_zeros(vector<string> please_translate)
{
	void change_into_a_number(string binary, int & result);

	int value_result = 0;
	string translator = "";
	bool done = 0;

	for (string ascii_value : please_translate)
	{
		// If reaching end of vector
		if (ascii_value == please_translate.back())	break;
		// translator will save dots and dashes in order unless encountered by 00 or 11
		for (unsigned int i = 0; i < ascii_value.size(); i++)
		{
			if (ascii_value[i] == '1' && !done)
			{
				i++;
				if (ascii_value[i] == '0')
				{
					translator += dash_dot[2].to_string();
					done = 1;
				}
				else// if it is word space (11)
				{
					value_morse.push_back(3);
					done = 1;
				}
			}
			else if (ascii_value[i] == '0' && !done)
			{
				i++;
				if (ascii_value[i] == '0')
				{
					change_into_a_number(translator, value_result);
					value_morse.push_back(value_result);
					value_result = 0;
					value_morse.push_back(0);
					translator = "";
					done = 1;
				}
				else // if it is dash (01)
				{
					translator += dash_dot[1].to_string();
					done = 1;
				}
			}
			done = 0;
		}
	}
}

/*
change into a number
this will change the patterns of 1 and 0 into int
Internal function (non-member)
*/
void change_into_a_number(string binary, int &result)
{
	string temp;
	unsigned int size = binary.size();

	temp += binary;

	for (int i = 0; i < (int)temp.size(); i++)
	{
		size--;
		result += ((temp[i] - '0')*(int)pow(2, size));
	}
	temp.clear();
}

// This will get the letter associated with the int value (friend)
void give_letter(int i, string &sentence, list<Morser> & holder)
{
	for (auto it : holder)
	{
		if (i == 0) break;

		else if (i == 3)
		{
			sentence += " ";
			break;
		}
		else if (it.getthird() == i)
		{
			sentence += it.getfirst();
			break;
		}
	}
}

string Morse_translator::make_a_sentence()
{
	string sentence;
	list<Morser> temp = carrier.give_vector();
	
	for (int expression : value_morse)
	{
		give_letter(expression, sentence, temp);
	}
	temp.clear();
	cout << sentence << endl;
	return sentence;
}

/*+++++++++++++++++++++++++++++++
void create_story()
final_sentence (string) will be
added into a text file for easy reading
+++++++++++++++++++++++++++++++*/
void Morse_translator::create_story()
{
	string filename = "Morse_story.txt";

	cout << "\nSaving this story into a text file called " << filename << " now...\n" << endl;

	ofstream file_written(filename);

	file_written << make_a_sentence() << endl;

}
//++++++++++++++3+++++++Morse_translator+++++++++

Binary_translator::Binary_translator()
{
	string filename;

	cout << "Give the file's name:" << endl;
	getline(cin, filename);
	BinaryEntry(filename);
}


Binary_translator::~Binary_translator()
{
	cout << "This is the end of the file...thanks for using!" << endl;
}

void Binary_translator::BinaryEntry(string datafile)
{
	streampos filesize;
	unsigned char * datablock;
	ifstream morse_file(datafile, ios::in | ios::binary);

	if (morse_file.is_open())
	{
		morse_file.seekg(0, ios::end);
		filesize = morse_file.tellg();
		datablock = new unsigned char[(unsigned int)filesize];
		morse_file.seekg(0, ios::beg);
		morse_file.read((char*)datablock, filesize);
		cout << "Let us start the process of decyphering through secret code" << endl;
		split_and_store(datablock, filesize);
		split_into_morse();
		system("pause");
		morse_file.close();
		delete[] datablock;
	}
	else
	{
		cout << "Are you sure this file exists?\n PLEASE RECOMPILE!" << endl;
		system("pause");
		exit(1);
	}
}

void Binary_translator::split_and_store(unsigned char* lines, streampos file_size)
{
	vector<unsigned char> temp_holder;
	for (int i = 0; i < file_size; i++)
	{
		//cout << "The letter is " << lines[i] << endl;
		please_translate.push_back(lines[i]);
	}
	convert_letter_ubit();
}

void Binary_translator::convert_letter_ubit()
{
	string binary;
	for (char s : please_translate)
	{
		bitset<8> b((unsigned int)s);
		binary += b.to_string();
		translated_text.push_back(binary);
		binary = "";
	}
}

void Binary_translator::split_into_morse()
{
	Allen.splits_ones_zeros(translated_text);
	Allen.create_story();
}

/*
entry for program
Only two lines are used!!
Amazing
*/
int main()
{
	Binary_translator Jerry;

	return 0;
}