/** @file rushhour.cpp
@author Arush Prashar
@version Revision 1.1
@brief This program solves the Rush Hour Game. 
@date Tuesday, October 03, 2017
*/

/**
@mainpage
This program gets user input for the vehicles that are to be placed on the board
and after that using the board.cpp file the program sets up the board and solves 
it and it prints out the least number of moves required to solve the board,
there is a 10 vehicles and 10 moves cap on the program if the board can not be
solved or there is no solution under 11 moves the program outputs you didn't win.  
*/

//
// Header Files ///////////////////////////////////////////////////
//
#include "arushBoard.h"


//
// Main Function Implementation ///////////////////////////////////
//
int main()
{
	//variables for user input
	int numVehicles = 0, //this keeps track of the number of vehicles on the board.
	    sz = 0, //this is the size of the vehicle that can be 2 or 3.
	    rw = 0, //this tells in which row the vehicle is placed or the row with its topmost end
	    col = 0; //this tells in which column the vehicle is placed or the column with its leftmost end
	    board brd;  //this is the board which is created after getting user input. 
	char ornt;  //this tells whether the vehicle is horizontal 'H' or vertical 'V'
	//variables passed into to the functions for output handling operations.
	bool win = false; //this variable is marked true if their is a solution under 11 moves.
	int cap = 11,	//this is the maximum moves that the program can use to solve the board.
	    moves = 0;  //this variable is used to keep the number of moves that the program has used to solve the problem.
	int scenario=1; //this keeps track of the scenario number being solved currently
	string str;
	cin >> numVehicles;
	while( numVehicles != 0 )
	{
		brd.setCars( numVehicles );
		// this loop gets the information about the vehicles on the board from the user.
		for( int i = 0; i < numVehicles; i++ )
		{
			cin >> sz >> ornt >> rw >> col;
			brd.setVehicle( sz, toupper( ornt ), rw, col, i );
		}
		brd.setBoard();
		brd.b2string( str );
		cout << str << endl;
		brd.solve( moves, cap, win );
		if( win == true )
		{
			cout << "Scenario " << scenario << " requires " << cap << " moves" << endl;
		}
		else
		{
			cout << "You did not win" << endl;
		}
		// resetting the variables passed in to function with reference for use for next scenario. 
		win = false;
		cap = 11;
		++scenario;
		cin >> numVehicles;
	}
	return 0;
}