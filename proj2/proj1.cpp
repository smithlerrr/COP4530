#include <iostream>
#include <algorithm>
#include <list>
#include <cctype>
#include <string>
#include <functional>
#include <map>
#include <iterator>
#include <set>

using namespace std;

struct Char
{
	char aChar;
	int charCount = 0;
};

struct Word
{
	string aWord;
	int wordCount = 0;
};

struct Numb
{
	string aNum;
	int numCount = 0;
};

void FindChars(string&, list<Char>&);
void FindWord(string&, list<Word>&);
void FindNums(string&, list<Numb>&);
void SortChar(list<Char>&);
void SortWord(list<Word>&);
void SortNum(list<Numb>&);
void OutputChar(list<Char>&);
void OutputWord(list<Word>&);
void OutputNumb(list<Numb>&);
void makeLower(string&);

int main()
{
	string input;

	list<Char>chars;
	list<Word>words;
	list<Numb>nums;
	
	int mostUsedChars=0, mostUsedWords=0, mostUsedNums=0;
	int differentChars=0, differentWords=0, differentNums=0;

	while(getline(std::cin, input))
	{	
		input += '\n';
		FindChars(input, chars);
		FindWord(input, words);
		FindNums(input, nums);
	}

	SortChar(chars);
	SortWord(words);
	SortNum(nums);


	OutputChar(chars);
	OutputWord(words);
	OutputNumb(nums);

	return 0;
}

void FindChars(string& __in, list<Char>& c)
{
	Char temp;
	char tempChar;

	for (unsigned int i = 0; i < __in.length(); ++i) 
	{
		if (isprint(__in[i]) || isspace(__in[i])) 
		{
			tempChar = (__in[i]);
			temp.aChar = tempChar;	
			temp.charCount = 1;
			bool found = false;
			for (list<Char>::iterator I = c.begin(); I != c.end(); ++I)
			{
				if (I->aChar == temp.aChar)
				{
					++I->charCount;
					found = true;
				}
			}
			if (!found)
				c.push_back(temp);
		}
	}	
}

void FindWord(string& __in, list<Word>& w)
{
	bool foundFirstIndex = false; 
	bool foundSecondIndex = false;
	int __fi, __si;
	string tempstr;
	Word temp;
	int j = 0;

	for (unsigned int i = 0; i < __in.length(); i++) 
	{
		if (isalpha(__in[i]) && !foundFirstIndex) 
		{
			__fi = i;
			foundFirstIndex = true;
		}
		if (!isalpha(__in[i]) && foundFirstIndex) 
		{
			__si = i;
			__si -= __fi;
			tempstr = __in.substr(__fi, __si);
			temp.aWord = tempstr;
			temp.wordCount = 1;
			foundSecondIndex = true;
		}
		if(foundSecondIndex)
		{
			makeLower(temp.aWord);
			bool found = false;
			for (list<Word>::iterator I = w.begin(); I != w.end(); ++I)
			{
				if (!I->aWord.compare(temp.aWord))
				{
					++I->wordCount;
					found = true;
				}
			}
			if (!found)
				w.push_back(temp);
			foundFirstIndex = false;
			foundSecondIndex = false;
			tempstr = "";
			temp.aWord = "";
			temp.wordCount = 0;
			__fi = 0;
			__si = 0;
		}
	}
}

void FindNums(string& __in, list<Numb>& n)
{
	bool foundFirstIndex = false, foundSecondIndex = false;
	int __fi, __si;
	string tempstr;
	Numb temp;

	for (unsigned int i = 0; i < __in.length(); i++) 
	{
		if (isdigit(__in[i]) && !foundFirstIndex) 
		{
			__fi = i;
			foundFirstIndex = true;
		}
		if (!isdigit(__in[i]) && foundFirstIndex) 
		{
			__si = i;
			__si -= __fi;
			tempstr = __in.substr(__fi, __si);
			temp.aNum = tempstr;
			temp.numCount = 1;
			foundSecondIndex = true;
		}
		
		if(foundSecondIndex)
		{
			bool found = false;
			for (list<Numb>::iterator I = n.begin(); I != n.end(); ++I)
			{
				if (!I->aNum.compare(temp.aNum))
				{
					++I->numCount;
					found = true;
				}
			}
			if (!found)
				n.push_back(temp);
			foundFirstIndex = false;
			foundSecondIndex = false;
			tempstr = "";
			temp.aNum = "";
			temp.numCount = 0;
			__fi = 0;
			__si = 0;			
		}
	}	
}


void SortChar(list<Char>& c)
{
	bool made_swap = true;
	while (made_swap) 
	{
		made_swap = false;
		list<Char>::iterator I = c.begin(), J;
		for(J = I++; I != c.end(); ++J, ++I)
		{
			if(J->charCount < I->charCount)
			{
				swap(*J, *I);
				made_swap = true;
			}
		}
	}
}



void SortWord(list<Word>& w)
{
	bool made_swap = true;
	while (made_swap) 
	{
		made_swap = false;
		list<Word>::iterator I = w.begin(), J;
		for(J = I++; I != w.end(); ++J, ++I)
		{
			if(J->wordCount < I->wordCount)
			{
				swap(*J, *I);
				made_swap = true;
			}
		}
	}
}

void SortNum(list<Numb>& n)
{
	bool made_swap = true;
	while (made_swap) 
	{
		made_swap = false;
		list<Numb>::iterator I = n.begin(), J;
		for(J = I++; I != n.end(); ++J, ++I)
		{
			if(J->numCount < I->numCount)
			{
				swap(*J, *I);
				made_swap = true;
			}
		}
	}
}

void OutputChar(list<Char>& c)
{
	int mChars, dChars;
	dChars = c.size();

	if(dChars > 10)
		mChars = 10;
	else
		mChars = dChars;

	cout << "Total " << dChars << " different characters, " << 
	mChars << " most used characters:\n"; 

	list<Char>::iterator I = c.begin();
	for (unsigned int i = 0; i < mChars && I != c.end(); i++, ++I)
       	cout << "No. " << i << ": " << (I->aChar == '\n' ? "\\n" : string(1, I->aChar)) << "\t\t" << I->charCount
       << endl;
}

void OutputWord(list<Word>& w)
{
	int mWords, dWords;
	dWords = w.size();

	if(dWords > 10)
		mWords = 10;
	else
		mWords = dWords;

	cout << "\nTotal " << dWords << " different words, " << mWords <<
	 " most used words:\n"; 

	list<Word>::iterator I = w.begin();
	for (unsigned int i = 0; i < mWords && I != w.end(); i++, ++I)
       	cout << "No. " << i << ": " << I->aWord << "\t\t" << I->wordCount
       	 << endl;
}

void OutputNumb(list<Numb>& n)
{
	int mNums, dNums;
	dNums = n.size();

	if(dNums > 10)
		mNums = 10;
	else
		mNums = dNums;

	cout << "\nTotal " << dNums << " different numbers, " << mNums <<
	 " most used numbers:\n"; 
	
	list<Numb>::iterator I = n.begin();
	for (unsigned int i = 0; i < mNums && I != n.end(); i++, ++I)
       	cout << "No. " << i << ": " << I->aNum << "\t\t" << I->numCount
       	 << endl;
}

void makeLower(string& s)
{
	for (int i = 0; i < s.size(); i ++)
	{
		s[i] = tolower(s[i]);
	}
}