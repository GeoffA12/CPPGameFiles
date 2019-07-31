// Chapter9_FInalProjectGameLobbyREDO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

//Player class contains the data necessary for GameLobby class to create a linked list of Players to manage the lobby list. 
class Player {
public:
	Player(const string& name);
	~Player();
	void setNextPlayer(Player* p);
	Player* getNextPlayer();
	string getName() const;
private:
	string* name;
	//string d;
	Player* nextPlayer;
};

// Player class constructor takes in a constant string value from the user. 
Player::Player(const string& n) {
	//Here, we are allocating memory to store a string on the heap and assigning a value of 'n', or the player name to this memory address on the heap. We are 
	// also the string property 'name' to point to this heap address storing the allocated space for the string. Simply put, this process allocates memory to store a string,
	// assigns a name to it, and points name to that chunk of memory on the heap. 
	name = new string(n);
	// We'll initially set the nextPlayer pointer to null or 0 and later manipulate this pointer so that we can perform several methods. 
	nextPlayer = 0;
}

// Getter method which returns the nextPlayer pointer property from the current instance. 
Player* Player::getNextPlayer() {
	return nextPlayer;
}

void Player::setNextPlayer(Player* p) {
	nextPlayer = p; 
}

// Getter method which returns the by dereferencing the player instance's name property.  
inline string Player::getName() const {
	return *name;
}

 /*Destructors acn be used to avoid memory leaks because they perform necessary cleanup before objects are removed. Default destructors 
 don't attempt to free any memory on the heap that a data member might point to. This destructor will free the string pointer to the name of the player stored on 
 the heap because we want to free the memory on the heap associated with the object we're removing before it dissapears.*/
Player::~Player() {
	delete name;
	nextPlayer = 0;
}

//GameLobby Class uses Player object pointers and a linked list structure to manage the lobby. 
class GameLobby {
	friend ostream& operator<<(ostream& os, const GameLobby& gl); 
public:
	GameLobby();
	~GameLobby();
	void deletePlayer();
	void addPlayer();
	void clearList();
	void listPlayers();
private:
	Player* head;
	Player* tail;
};

// Game Loby constructor doesn't take any values from the user. An empty game lobby will assign both head and tail player object pointers to null, or 0. 
// This is because the lobby is empty, so the linked list structure shouldn't contain a head, or starting player node quite yet. 
GameLobby::GameLobby() {
	head = 0;
	tail = 0;
}

// Logic to add a player when the user presses add a player in the menu option
void GameLobby::addPlayer() {
	cout << "\nEnter the name of the new player: ";
	string n;
	cin >> n;
	// f is the pointer to the new player instance we're going to add to this game lobby linked list. 
	Player* f = new Player(n);
	// If head is null, then assign the new player as the head. Assign tail pointer to head pointer. 
	if (head == 0) {
		head = f;
		tail = f;
	}
	else {
		tail->setNextPlayer(f);
		tail = f;
	}
}

//You can only delete from the top of the linked list(the tail, in this case.)
void GameLobby::deletePlayer() {
	// Display an alert when the user presses delete player option in the menu when the game lobby linked list is empty. 
	if (head == 0) {
		cout << "\nYou can't delete a player because the lobby is empty.";
		return;
	}
	// This branch should handle the case in which there is only one player instance in the game lobby, and they need to be deleted. 
	else if (head->getNextPlayer() == 0){
		Player* y = head->getNextPlayer();
		head = 0;
		delete y;
	}
	else {
		Player* u = head->getNextPlayer();
		head->setNextPlayer(u->getNextPlayer());
		delete u;
	}
}

// Clear the entire list, or set the head pointer to null. 
void GameLobby::clearList() {
	Player* start = head;
	// If the game lobby instance is null, then this while loop won't execute. 
	while (start != 0) {
		Player* after = start->getNextPlayer();
		cout << "\ndeleting a node.";
		delete start;
		start = after;
		// This is code which will result in an nullptr exception
		//after = after->getNextPlayer();
		//delete start;
	}
	head = 0;
	tail = 0;
}

// Basic implementation of a Java toString() method which prints out all player instances in the game lobby. 
void GameLobby::listPlayers(){
	Player* t = head;
	while (t != 0) {
		cout << t->getName() << endl;
		t = t->getNextPlayer();
	}
}

GameLobby::~GameLobby() {
	clearList();
}
ostream& operator<<(ostream& os, const GameLobby& gl);
int main()
{
	GameLobby myLobby;
	int choice;
	bool isExit = false;
	do {
		cout << "\nGAME LOBBY\n";
		cout << "0 - Exit the program\n";
		cout << "1 - Add a player to lobby\n";
		cout << "2 - Delete a player from lobby\n";
		cout << "3 - Clear the entire lobby\n";
		cout << "4 - List out the lobby\n";
		cout << "Enter a choice 1-4: ";
		cin >> choice;
		switch (choice) {
		case 0:
			cout << "\nGoodbye!";
			isExit = true;
			break;

		case 1:
			myLobby.addPlayer();
			break;
		case 2:
			myLobby.deletePlayer();
			break;
		case 3:
			myLobby.clearList();
			break;
		case 4:
			myLobby.listPlayers();
			break;
		default:
			cout << "That's not a valid option. Try again.\n";
		}
	} while (isExit == false);
    return 0;
}


// this is the overloaded assignment operator definition. In this case, we want the << operator to return us a list of all of the player instances 
// currently in the game lobby linked list. 
ostream& operator<<(ostream& os, const GameLobby& gl) {
	os << "GameLobby Object - ";
	os << "Top of the player list: \n";
	Player* p = gl.head;
	if (p == 0) {
		os << "The list is currently empty.\n";
	}
	else {
		while (p != 0) {
			os << p->getName() << endl;
			p = p->getNextPlayer();
		}
	}
	return os;
}

