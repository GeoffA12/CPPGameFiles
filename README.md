# GameLobbyImpl

This repisitory contains my C++ game lobby program which I wrote based on a previous assignment when I was learning C++ game programming. The basic idea behind the game lobby program is that a user is presented with a menu on the terminal in which they can either enter a new name into the game lobby, delete a player from the top of the lobby, list out all of the players currently in the lobby, or delete the entire list. 

A linked list, two classes, and heap storage were used to manage this project. One important lesson I learned from working on this project would be how to dynamically free memory allocated on the heap. I encountered many errors with null pointer exceptions, especially when working with the delete function in the GameLobby class, which I overcame through hours of research and practice. 

One other important concept present in this game project is the use of destructors, which I was previuosly unfamiliar with. In the future, I'd like to improve this program by adding a feature to the game menu which lets the user delete a user by name instead of always deletng the user at the top of the list. Also, another useful options to add to a game lobby would be to catch bad input when the user enters a number not on the menu. 
