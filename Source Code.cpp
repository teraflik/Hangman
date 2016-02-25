/*
GNU GENERAL PUBLIC LICENSE (Version 3, 29 June 2007)
©TeraFlik,2015 http://www.teraflik.com
This version of the source code has been originally released at www.teraflik.com/p/hangman.html.
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation version 3 of the License.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU General Public License for more details: http://opensource.org/licenses/GPL-3.0.
*/

/*Anyone with a basic understanding of programming and little knowledge
of C++ can understand the following code and feel free to modify it in the
way you want, as it is open source... yeah! you are looking at the source.*/

/*The code has been written as per ANSI C++ standard and can be run only on 
modern C++ compilers like Orwell Dev C++, or Visual Studio 2010 and later. 
This code cannot be compiled on older compilers like Turbo C++.*/

/*The current version of program is bug free and totally stable.
But if anyone finds any bug in it please report me immediately at :
admin@teraflik.com or teraflik.com/p/contact.html */

//The standard library files used
#include<iostream> //for basic input and output
#include<cstdlib> //for exit() and system(“cls”) functions
#include<ctime> //for seeding srand() for random values
#include<cstring> //for all string functions
#include<fstream> //for handling the file "words.txt"
#include<conio.h> //for getch() function
using namespace std;

void ShowCategory(); //all the function prototypes
void ChangeLevel();
void Game();
void HowToPlay();
void ShowHeader();
void ShowMenu();
void LoadFile();
void LoadWBank();
void ReturnLevel();
void SelectWord();
int LetterFill (char, char []);
char Input();

/*All the global variables*/

const int MaxL = 30; //The max length of a word
const int MaxW = 200; //Max words in the word bank

char FileContent[2000]; //The text file will be read into this
int NoTries = 7; //No of tries depends on the level selected
int NewLineCount = 0; // to count the number of words in text file

int CurrentW; //to store which word is in process
int UsedW[MaxW]; //to store all the SrNo of used words
int NoUsedW = 0; //to store no of used words

class WBank //class to store all the words
{
public:
	char W[MaxL]; //the word
	WBank() //constructor 
	{
		strcpy_s(W,"null");
	}
};
WBank Word[MaxW];

int main() //The main function
{
	srand(time(NULL)); //to randomize the random function
	LoadFile();
	LoadWBank();
	ShowMenu();
	_getch();
	return 0;
}

void ShowMenu() //this is the main menu of the program
{
	char cho; //to store choice
	ShowHeader();
	cout<<"Select an Option: ";
	cout<<"\n1. Start Game";
	cout<<"\n2. Change level";
	cout<<"\n3. How to play";
	cout<<"\n4. Exit";
	cout<<endl<<"\t\tChoice: ";
	cho = Input(); //Input function returns input values
	
	if(cho == '1') Game(); //start game
	else if(cho == '2') ChangeLevel(); //change level
	else if(cho == '3') HowToPlay(); //how to play option
	else if(cho == '4') //exit program
	{
		cout<<"\t\tExited succesfully!";
		_getch();
		exit(0);
	}
	else
	{
		cout<<"\t\tInvalid Input! Try again.";
		_getch();
		ShowMenu();
	}
}

void SelectWord() //Word Selection Engine
{
	/*generate a random int and compare it to all the previously 
	selected words, so that the same word is not put up again*/
	int i=0;
	int n = rand()% NewLineCount;
	for(i=0;i<NoUsedW;i++)
	{ 
		if(UsedW[i] == n) 
		{
			i=0;
			Game();
		}
	}
	UsedW[NoUsedW] = n;
	NoUsedW++;
	CurrentW = n;
}

void Game() //The main code for the execution of game
{
	SelectWord();
	ShowHeader();
	char Unknown[MaxL]; //the secret word is stored in it
	char Letter; //user's guessed letter
	int NoWrongGuess=0; //no of wrong guesses
	int i;
	int length = strlen(Word[CurrentW].W);

	for (i = 0; i < length; i++) // to generate the secret word
	{
		Unknown[i]='*';
		if(Word[CurrentW].W[i] == ' ') 
		{
			Unknown[i] = ' ';
		}
	}
	Unknown[i]='\0';
	if(NewLineCount == 120) 
		cout<<"Category: Countries ";
	else 
		cout<<"====================";
	cout<<"================== Level: "; ReturnLevel();
	cout<<"== No of Tries: "<<NoTries<<" "<<endl;
	if(NewLineCount == 120) 
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

	while (NoWrongGuess < NoTries) //condition for running program
	{
		cout<<endl<<endl<<Unknown;
		cout<<endl<<"\tYour Guess: ";

		while(!( Letter=Input() )) //if user provides invalid input
		{
			cout<<"\tInvalid input! Try again: ";
		}

		if (LetterFill(Letter, Unknown)==0) //if user provides wrong guess
		{
			cout<<"\tOops! Your guess is wrong!";
			NoWrongGuess++;
		}
		else //else he will find the letter
		{
			cout<<"\tYou found a letter!";
		}

		cout<<" Now You have "<<NoTries-NoWrongGuess<<" tries left.";

		if (strcmp(Word[CurrentW].W, Unknown) == 0) //checking if he guessed the word
		{
			cout<<endl<<endl<<"Yeah! You got it! The word was: "<<Word[CurrentW].W;
			cout<<endl<<endl;
			break;
		}
	}
	if(NoWrongGuess == NoTries) //condition for user to lose
	{
		cout<<endl<<endl<<"\nSorry, you lose...you've been hanged.";
		cout<<" The word was: "<<Word[CurrentW].W<<endl<<endl;
	}
	_getch();
	ShowMenu();
	return;
}

int LetterFill (char guess, char guessword[]) //the function which checks each guess
{
	int i;
	int matches=0;
	for (i = 0; Word[CurrentW].W[i]!='\0'; i++)
	{

		// Did we already match this letter in a previous guess?
		if (guess == guessword[i])
			return 0;

		// Is the guess in the secret word?
		if (guess == Word[CurrentW].W[i])
		{
			guessword[i] = guess;
			matches++;
		}
	}
	return matches;
}

void ShowHeader() //the function which shows the header on each screen
{
	system("cls");
	cout<<endl<<"+-----------------------------------------------------------------------------+";
	cout<<endl<<"|                          Hangman Game - teraflik.com                        |";
	cout<<endl<<"+-----------------------------------------------------------------------------+";
	cout<<endl<<endl;
	return;
}

void HowToPlay() //how to play option
{
	ShowHeader();
	cout<<"What...You've never played hangman! Seriously? Sigh...";
	cout<<"\n\nHere's how to play: ";
	cout<<"\n - Try to solve the riddle before your chances run out.";
	cout<<"\n - Type in the letters you wish to guess. Careful! Wrong letters lose chances.";
	cout<<"\n - You can change the level from the Change Level option.";
	cout<<"\n - For more stuff, visit \"teraflik.com\"";
	cout<<"\n\n\t\t\t\t    Press any key to go back to main menu...";
	_getch();
	ShowMenu();
}

void LoadFile() //the function which loads the text file in memory
{
	char ch;
	int i=0;
	ifstream fin("Words.txt", ios::in); //open file
	fin.seekg(0);
	if(!fin) //if the file is not found there
	{
		ShowHeader();
		cout<<"\nError 701. Unable to open file!";
		_getch();
		cout<<"\n\n - This program needs the accompanying file \"Words.txt\" to run.";
		cout<<"\n - Please check that the file exists with program and restart again.";
		cout<<"\n - If you can\'t find the file then create a new text file with the same name.";
		cout<<"\n - Type the words to be asked in the hangman game in separate lines.";
		_getch();
		cout<<"\n\n - For further assistance contact me at: teraflik.com/p/contact.html"; 
		_getch();
		exit(1); //exit with 1 status
	}
	while(true) 
	{
		fin.get(ch);
		if( fin.eof() ) break;
		FileContent[i] = ch;
		i++;
	}
	fin.close();
	return;
}

void LoadWBank() //to load the read file into our class WBank
{
	int j=0, k=0;

	for(int i=0; FileContent[i]!='\0'; i++)
	{
		if(FileContent[i] == '\n') 
		{
			NewLineCount++;
			Word[j].W[k] = '\0';
			j++;
			k=0;
			continue;
		}
		Word[j].W[k] = FileContent[i];
		k++;
	}
	return;
}

void ChangeLevel() //function to change level
{
	ShowHeader();
	char cho;
	cout<<"Select a level: ";
	cout<<"\n1. Very Easy";
	cout<<"\n2. Easy";
	cout<<"\n3. Moderate";
	cout<<"\n4. Hard";
	cout<<"\n5. Extremely Hard";
	cout<<"\n\t\tChoice: ";
	cho = Input();
	if(cho == '1') NoTries = 15;
	else if(cho == '2') NoTries = 10;
	else if(cho == '3') NoTries = 7;
	else if(cho == '4') NoTries = 5;
	else if(cho == '5') NoTries = 3;
	else
	{
		cout<<"\t\tInvalid Input! Try again.";
		_getch();
		ChangeLevel();
	}
	cout<<"\t\tLevel Changed !";
	_getch();
	ShowMenu();
	return;
}

void ReturnLevel() //function to display which level is selected
{
	if(NoTries == 15)     cout<<"Very Easy =====";
	else if(NoTries == 10)cout<<"Easy ==========";
	else if(NoTries == 7) cout<<"Moderate ======";
	else if(NoTries == 5) cout<<"Hard ==========";
	else if(NoTries == 3) cout<<"Extremely Hard ";
	else
	{
		ShowHeader(); //if some invalid level is selected by user modification
		cout<<"Error 702. Invalid Level Selected";
		_getch();
		cout<<"\n - Some bug or unwanted reasons have caused conflicts in the program.";
		cout<<"\n - Please get a proper working program or code from available sources.";
		cout<<"\n\n - Seek further assistance at: teraflik.com/p/contact.html";
		_getch();
		exit(1);
	}
	return;
}

char Input() //function to take the input.
{
	/*This Input() function makes the input of the program
	bug free. Any invalid or unacceptable input will return value 0*/
	char cho1[40];
	cin>>cho1;
	cin.ignore();

	if(strlen(cho1)>1)
	{
		return '0';
	}
	else
	{
		return cho1[0];
	}
}

/*End of program. For more stuff, visit: teraflik.com */