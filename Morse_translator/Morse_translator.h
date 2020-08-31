/*
Morse translator
This will be used to translate the binary strings from Binary_translator
into series of dots and dashes along with @ (word space)  and ^ (letter space)   
*/
#ifndef MOR_H_
#define MOR_H_

#include <vector>
#include "Morse.h"
#include <cmath>

class Morse_translator
{
private:
	// An array of bitsets that represent . , - , @ , ^ 
	bitset<2> dash_dot[4]; 
	// This vector of ints will be used in comparison to int key value of a character tuple
	vector<int> value_morse;
	string final_sentence;
	// This Morse object will store one instance of character_chart
	Morse_read carrier;	
public:	
	
	Morse_translator();
	~Morse_translator();
	
	void fill_table_dashdot();
	void splits_ones_zeros(vector<string> please_translate);
	string make_a_sentence();

	friend void give_letter(int i, string & sentence, list<Morser> & holder);
};

#endif // MOR_H
