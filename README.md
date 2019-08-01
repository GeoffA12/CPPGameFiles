# GameLobbyImpl

This repisitory contains both a C++ game lobby program and a C++ Hangman game which I wrote based on a previous assignments when I was learning C++. 

The basic idea behind the game lobby program is that a user is presented with a menu on the terminal in which they can either enter a new name into the game lobby, delete a player from the top of the lobby, list out all of the players currently in the lobby, or delete the entire list. 

A linked list, two classes, and heap storage were used to manage this project. One important lesson I learned from working on this project would be how to dynamically free memory allocated on the heap. I encountered many errors with null pointer exceptions, especially when working with the delete function in the GameLobby class, which I overcame through hours of research and practice. 

One other important concept present in this game project is the use of destructors, which I was previuosly unfamiliar with. In the future, I'd like to improve this program by adding a feature to the game menu which lets the user delete a user by name instead of always deletng the user at the top of the list. Also, another useful options to add to a game lobby would be to catch bad input when the user enters a number not on the menu. 

I developed  the C++ hangman project during my free time. The concept of the program follows a classic two-player approach to hangman, in which one player enters in a secret word in the console for the second player to guess. The second player enters in characters on the keyboard, and after each guess, is notified on whether or not the character they entered was a hit or miss. A progress string initially consisting of '_' was added so that the second player, or the player who is guessing the word, can view their progress as they guess correct characters.

I've refactred this program recently for two main reasons. The first is that I wanted to learn how I could implement an stdin buffer flush into input/output operations without consistently converting strings into arrays of characters and vice versa. You can see how the stdin buffer flush works in the getGuess function. I also wanted to learn how to hide input from the console when the user types in a message which should be hidden without clearing the console.
