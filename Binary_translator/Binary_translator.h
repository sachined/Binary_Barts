/*
Binary translator is used to read the binary file provided by professor
This will give a char block that will have the entire file content
This will be used to translate the char into ascii (int...bitset for morse translator class)

*/
#ifndef BIN_H_
#define BIN_H_

#include "Morse_translator.h"

using namespace std;

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

#endif // BIN_H_