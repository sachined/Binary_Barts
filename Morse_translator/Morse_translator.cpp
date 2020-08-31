#include "Morse_translator.h"

Morse_translator::Morse_translator()
{
	fill_table_dashdot();
}


Morse_translator::~Morse_translator()
{
}

// This function will fill a table that can be used 
void Morse_translator::fill_table_dashdot() 
{
	for (int i = 0; i < 4; i++)
		dash_dot[i] = i;

	//std::cout << "^ is " << dash_dot[0] << std::endl;
	//std::cout << "- is " << dash_dot[1] << std::endl;
	//std::cout << ". is " << dash_dot[2] << std::endl;
	//std::cout << "@ is " << dash_dot[3] << std::endl;
} 

/*
This will read into please_translate and 
*/
void Morse_translator::splits_ones_zeros(vector<string> please_translate) 
{
	void change_into_a_number(string binary, int & result);
	
	//vector<int> value_morse;
	int value_result = 0;
	string translator = "";
	bool done = 0;
	
	for (string ascii_value : please_translate)
	{
		if (ascii_value == please_translate.back())
		{
			//cout << "I am the last element!" << endl;
			break;
		}
		// translator will save dots and dashes in order unless encountered by 00 or 11
		
		for (unsigned int i = 0; i < ascii_value.size(); i++)
		{
			if (ascii_value[i] == '1' && !done)
			{
				//cout << "1, next makes @ (11) or . (10)" << endl;

				i++;

				if (ascii_value[i] == '0')
				{
					//cout << "Dot" << endl;
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
				//cout << "0, next - (01) or ^ (00)" << endl;
				i++;
				if (ascii_value[i] == '0')
				{
					//cout << "LS" << endl;
					change_into_a_number(translator, value_result);
					//cout << "Morse " << translator << " is valued at " << value_result << endl;
					value_morse.push_back(value_result);
					value_result = 0;
					value_morse.push_back(0);
					translator = "";
					done = 1;
				}
				else // if it is dash (01)
				{
					//cout << "Dash!" << endl;
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
*/
void change_into_a_number(string binary, int &result)
{
	string temp;
	unsigned int size = binary.size();
	//bitset<14> digits(binary);

	temp += binary;

	for (int i = 0; i < (int)temp.size(); i++)
	{
		size--;
		result += ((temp[i] - '0')*(int)pow(2, size));
	}
	temp.clear();
}

// This will get the letter associated with
// such int value
void give_letter(int i, string &sentence, list<Morser> & holder)
{
	for (auto it : holder)
	{
		//it.getmorse();
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
	//cout << "This is a perfectly good sentence" << endl;
	for (int expression : value_morse)
	{
		give_letter(expression, sentence, temp);
	}
	cout << sentence << endl;
	return sentence;
}