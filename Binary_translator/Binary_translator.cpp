#include "Binary_translator.h"

Binary_translator::Binary_translator()
{
	string filename;

	cout << "Give the file's name:" << endl;
	getline(cin, filename);
	BinaryEntry(filename);
}


Binary_translator::~Binary_translator()
{
	cout << "This is the end of the file..." << endl;
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
		//cout << datablock << endl;
		cout << "Let us start the process of decyphering through secret code\n" << endl;
		// 
		split_and_store(datablock, filesize);
		split_into_morse();
		morse_file.close();
		delete[] datablock;
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
	for(char s:please_translate)
	{
		bitset<8> b((unsigned int)s);
		binary += b.to_string();
		//cout << s << " has become\n" << dec << binary << endl;
		translated_text.push_back(binary);
		binary = "";
	}
}

void Binary_translator::split_into_morse() 
{
	Allen.splits_ones_zeros(translated_text);
	Allen.make_a_sentence();
}