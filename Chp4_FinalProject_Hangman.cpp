// Chp4_FinalProject_Hangman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define NOMINMAX
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;


void rules();
string p1_turn();
int getLimit(string);
bool p2_turn(string, int);
char getGuess();
bool repeat(bool, int, string);
bool findRepeats(const vector<char>&, char);
int main() {
	bool playAgain = true;
	while (playAgain) {
		cout << "\t\t\t\t\t\t\tHANGMAN GAME" << endl;
		rules();
		string key = p1_turn();
		int limit = getLimit(key);
		playAgain = p2_turn(key, limit);
		if (!playAgain) {
			break;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	Sleep(2000);
	return 0;
}


void rules() {
	cout << "\nThis is a two-player hangman game.  Here are the rules: \n\n\n";
	cout << "\t\t\t\t\t\t\tRULES\n\n";
	cout << "1. Player1 will choose a word without spaces in it for player 2 to guess. Player 1 must pick a legal word which is not a proper noun - such as a place or brand.\n\n";
	cout << "2. Player 1 isn't allowed to use slang as their guessing word.\n\n";
	cout << "3. Player 2 will then starting guessing individual characters from Player 1's secret word. The amount of guesses they are allowed to have is dependent on the length of the word Player 1 enters.\n\n";
	cout << "4. If Player 2 guesses correctly, the master key will be updated. At any point in the game, Player 2 has the option to guess the word outright. If they miss this guess, it will count as a normal miss.\n\n";
	cout << "5. Once Player 2 is out of guesses, they are 'hanged', and Player 1 will win. If Player guesses the word correctly before they hit their guess limit, then Player 2 will win.\n\n";
}

string p1_turn() {
	string key;
	cout << "Player 1, it's your turn! Enter a word under 50 characters. Use only letters in your word and no spaces: ";
	// The next 4 lines will configure the default settings for stdin so that the console input from the user is hidden. 
	// The purpose of hiding the console input from player 1 here is so that player 2 won't be able to see the secret hangman word which they will be trying to guess after player 1 
	// finishes typing. 
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	int const stringSize = 50;
	char charArray[stringSize];
	bool canBreak = false;
	string ret;
	while (!canBreak) {
		cin.getline(charArray, stringSize, '\n');
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nYou can only enter up to 50 characters. Try again: ";
			continue;
		}
		canBreak = true;
		ret = charArray;
		for (int x = 0; x < ret.length(); ++x) {
			char a = ret[x];
			int check = a;
			if ((check > 90 && check < 97) || check < 65 || check > 122) {
				cout << "\nSpecial characters are not allowed! Try again: ";
				canBreak = false;
				break;
			}
		}
		if (ret.length() == 0) {
			cout << "\nYou must enter at least one character! Try again: ";
			canBreak = false;
		}
	}
	// Manually clean up the stdin settings so that the console input will now appear on screen. 
	SetConsoleMode(hStdin, mode);
	for (int i = 0; i < ret.length(); i++) {
		ret[i] = toupper(ret[i]);
	}
	return ret;
}

int getLimit(string keys) {
	return keys.length() + 5;
}

bool p2_turn(string keys, int turnsLeft) {
	cout << "\n\nPlayer 2, it's your turn now!\n";
	int counter = 0;
	string display((turnsLeft - 5), '_');
	int numberCorrect = 0;
	vector<char> guesses;
	guesses.reserve(55);
	vector<char>::const_iterator myIter;
	bool again = true;
	bool p2Wins = false;
	
	while (counter <= turnsLeft && again == true) {
		cout << "\nHere is your current progress so far: \n";
		cout << display << endl;

		cout << "\nPlayer 2, enter a character to guess, or press '#' to try and guess the entire word: ";
		char guess = getGuess();
		guess = toupper(guess);

		if (guess == '#') {
			string lucky;
			cout << "\n\nEnter your guess for the completed hidden word: ";
			cin >> lucky;
			if (lucky == keys) {
				p2Wins = true;
				again = repeat(p2Wins, counter, keys);
				break;
			}
			else {
				cout << "\nYour guess was incorrect. You will be deducted a guess.\n";
				counter++;
				continue;
			}
		}

		bool foundRepeats = findRepeats(guesses, guess);
		if (foundRepeats) {
			cout << "\nYou've already guessed this character once. Try using a different one!";
			continue;
		}

		guesses.push_back(guess);
		int timesFound = 0;
		for (int i = 0; i < keys.length(); i++) {
			if (guess == keys[i]) {
				cout << "\nCongrats! You guessed the hidden character, " << keys[i] << " correctly!\n";
				display[i] = keys[i];
				numberCorrect++;
				timesFound++;
			}
		}
		if (timesFound == 0) {
			cout << "\nYour guess of " << guess << " wasn't found in the string." << endl;
		}
		cout << "\nYou have " << (turnsLeft - counter) << " guesses remaining.\n";
		counter++;
		if (numberCorrect == (turnsLeft - 5)) {
			p2Wins = true;
			again = repeat(p2Wins, counter, keys);
			break;
		}
	}
	
	if (!p2Wins) {
		again = repeat(p2Wins, counter, keys);
	}
	return again;
}

char getGuess() {
	char c [2];
	while (true) {
		cin.getline(c, 2, '\n');
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nYou can only enter one character. Try again: ";
			continue;
		}
		char a = c[0];
		int check = a;
		if (check == 0) {
			cout << "\nYou need to enter at least one character! Try again: ";
		}
		else if ((check > 90 && check < 97) || check < 65 || check > 122) {
			cout << "\nYou can't guess any special characters. Try again: ";
		}
		else {
			break;
		}
	}
	char retValue = c[0];
	return retValue;
}

bool repeat(bool p2Won, int totalMoves, string target) {
	if (!p2Won) {
		char again;
		cout << "\nPlayer 1 Wins! Better luck next time, Player 2. The hidden word was: " << target << endl;
		cout << "\nPress y if you would like a rematch: ";
		cin >> again;
		if (again == 'y' || again == 'Y') {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		cout << "Congratulations Player 2! You guessed the hidden word, " << target << " correctly in " << totalMoves << " turns!";
		char again;
		cout << "\nPress y if you would like a rematch: ";
		cin >> again;
		if (again == 'y' || again == 'Y') {
			return true;
		}
		else {
			return false;
		}
	}
}

bool findRepeats(const vector<char>& search, char current) {
	for (int x = 0; x < search.size(); ++x) {
		if (search[x] == current) {
			return true;
		}
	}
	return false;
}
