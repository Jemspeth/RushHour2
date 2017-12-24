/** @file Board.cpp
@authors Arush Prashar and Jeremy Speth
@version Revision 1.4
@brief This file provides supporting functions for the rushhour program. 
@date Tuesday, December 5, 2017
*/


//
// Header Files ///////////////////////////////////////////////////
//
#include "Board.h"


/**
 * This function checks if the game has been won.
 * This function decides if we won or not by checking that the car# 0 is at the edge or not.
 * @param none
 * @pre none 
 * @post The value of win is true if we won else false.
 * @exception none
 * @return bool true if we win (car# 0 is at the edge) false otherwise
*/
bool board::didWeWin()
{
	if(vhBoard [ veh[0].row ] [ veh[0].column + veh[0].size ] == 'X')
	{
		return true;
	}
	else 
	{
		return false;
	}
}


/**
 * This function moves the vehicle forward if possible.
 * This function checks if there is empty space in front of the vehicle ( front => down if the car is
 * vertical and right if it is horizontal) if there is empty space then the car is moved.
 * @param j it tells the function which car is to be moved forward.
 * @pre none 
 * @post the car is moved forward if it is possible and the board is updated.
 * @exception none
 * @return bool true if the car is moved false otherwise.
*/
bool board::moveFwd(int j)
{
	if(veh[j].orientation == 'H' && vhBoard [ veh[j].row ] [ veh[j].column + veh[j].size ] == 'O')
	{
		vhBoard [ veh[j].row ] [ veh[j].column + veh[j].size ] = j + 97;//vhBoard [ veh[j].row ] [ veh[j].column ];
		vhBoard [ veh[j].row ] [ veh[j].column ] = 'O';
		++veh[j].column;
		return true;
	}
	else{
		if( veh[j].orientation == 'V' && vhBoard [ veh[j].row + veh[j].size ] [ veh[j].column ] == 'O')
		{
			vhBoard [ veh[j].row + veh[j].size ] [ veh[j].column ] = j + 97;//vhBoard [ veh[j].row ] [ veh[j].column ];
			vhBoard [ veh[j].row ] [ veh[j].column ]= 'O';
			++veh[j].row;
			return true;
		}
	}
	return false;
}


/**
 * This function moves the vehicle backward if possible.
 * This function checks if there is empty space at the back of the vehicle ( back => up if the car is
 * vertical and left if it is horizontal) if there is empty space then the car is moved.
 * @param j it tells the function which car is to be moved backward.
 * @pre none 
 * @post the car is moved backward if it is possible and the board is updated.
 * @exception none
 * @return bool true if the car is moved false otherwise.
*/
bool board::moveBwd(int j)
{
	if(veh[j].orientation == 'H' && vhBoard [ veh[j].row ] [ veh[j].column - 1 ] == 'O')
	{
		vhBoard [ veh[j].row ] [ veh[j].column + veh[j].size - 1 ] = 'O';
		vhBoard [ veh[j].row ] [ veh[j].column - 1 ] = j + 97;//vhBoard [ veh[j].row ] [ veh[j].column ];
		--veh[j].column;
		return true;
	}
	else{
		if( veh[j].orientation == 'V' && vhBoard [ veh[j].row - 1 ] [ veh[j].column ] == 'O')
		{
			vhBoard [ veh[j].row + veh[j].size - 1 ] [ veh[j].column ] = 'O';
			vhBoard [ veh[j].row + - 1 ] [ veh[j].column ] = j + 97;//vhBoard [ veh[j].row ] [ veh[j].column ];
			--veh[j].row;
			return true;
		}
	}
	return false;
}


/**
 * This function creates a  recursive loop to solve the rush hour problem.
 * This function takes help of createLevel function to solve the rush hour problem.
 * @param level passed by reference it tells how many moves have we used to reach the current board setup.
 * @param win passed in by reference it tells if we won or not.
 * @param win passed in by reference it is set as true if we win.
 * @pre none 
 * @post the board has been solved (if there is a solution).
 * @exception none
 * @return void
*/
void board::solve(int& level, bool& win)
{
	string str;
	if( didWeWin())
	{
		win = true;
		return;
	}
	generateString(str);
	boardHash.push(str);
	level++;
	for(; !boardHash.empty(); level++)
	{
		createLevel(win);
		if(win == true)
			return;
	}
	win = false;
}


/**
 * This function creates a recursive loop to create all boards that can be reached in given number of moves.
 * This function uses all the possible boards in the previous level and creates the boards that can be produced 
 * in just one move, if the function also checks if the board was ever created before if it was it is not stored
 * in the queue and during the creation of the new move if the winning board is created the function sets win to
 * true and returns.
 * @param win passed in by reference it is set as true if we win.
 * @pre none 
 * @post all the possible moves for the next level are pushed on the queue and the old values are discarded.
 * @exception none
 * @return void
*/
void board::createLevel(bool&win)
{
	string currStr,str;
	map <string, int> :: iterator it;
	queue <string> temp;
	while(!boardHash.empty())
	{
		currStr = boardHash.front();
		generateBoard(currStr);
		for(int i = 0; i < cars; i++)
		{
			if(moveFwd(i))
			{
				if(didWeWin() && i == 0)
				{
					win = true;
					return;
				}
				generateString(str);
				it = boardStrings.find(str);
				if( it == boardStrings.end() )
				{
					temp.push(str);
					boardStrings.insert(pair <string, int> (str, 1));
				}
				moveBwd(i);
			}
			if(moveBwd(i))
			{
				generateString(str);
				it = boardStrings.find(str);
				if( it == boardStrings.end() )
				{
					temp.push(str);
					boardStrings.insert(pair <string, int> (str, 1));
				}
				moveFwd(i);
			}
		}
		boardHash.pop();	
	}
	boardHash = temp;
}


/**
 * This function sets the cars data member of board class.
 * This function sets cars to be equal to the number of vehicles that we have on the board.
 * @param numVehicle the number of vehicles on the board entered by the user.
 * @pre none 
 * @post cars is set equal to the number of vehicles on the board.
 * @exception none
 * @return void
*/
void board::setCars(int numVehicle)
{
	cars=numVehicle;
}


/**
 * This function sets the data members of the vehicle struct.
 * This function fills the veh array of type vehicle with the information abput the vehicle as entered
 * by the user.
 * @param sz passed by value tells the size of the vehicle it can be 2 or 3.
 * @param ornt passed by value it tells whether the vehicle is horizontal 'H' or vertical 'V'.
 * @param rw passed by value it tells the row in which the vehicle is placed or its 
 * top most point on the board.
 * @param col passed by value it tells the column in which the vehicle is placed or
 * its left most point on the board.
 * @param vehNum it tells the number of the car on the board and the position in the veh array where 
 * the data is to be entered.
 * @pre none 
 * @post the veh array is filled with the information of all the cars on the board.
 * @exception none
 * @return void
*/
void board::setVehicle(int sz, char ornt, int rw, int col, int vehNum)
{
	veh[vehNum].size = sz;
	veh[vehNum].orientation = ornt;
	veh[vehNum].row = rw + 1;
	veh[vehNum].column = col + 1;
}


/**
 * This function sets up the board.
 * This function sets the board according to the data in the veh array and it covers all the sides 
 * of the board with 'X' to mark the edges of the board and the empty spaces are filled with 'O'
 * the cars are denoted by 'C' and truck is denoted by 'T'.
 * @param none
 * @pre none 
 * @post the board is set up according to the information stored in the veh array.
 * @exception none
 * @return void
*/
void board::setBoard()
{
	int i = 0, j = 0;
	for( i = 0; i < 8; i++ )
	{
		for( j = 0; j < 8; j++ )
		{
			vhBoard [ i ] [ j ] = 'O';
			if( i == 0 || i == 7 || j == 0 || j == 7 )
				vhBoard [ i ] [ j ] = 'X';
		}
	}
	for( j = 0; j < cars; j++ )
	{
		char letter = j + 97;
		if( veh[j].size == 3 && veh[j].orientation == 'H')
		{
			vhBoard [ veh[j].row ] [ veh[j].column ] = letter;
			vhBoard [ veh[j].row ] [ veh[j].column + 1 ] = letter;
			vhBoard [ veh[j].row ] [ veh[j].column + 2 ] = letter;
		}
		else if( veh[j].size == 3 && veh[j].orientation == 'V')
		{
			vhBoard [ veh[j].row ] [ veh[j].column ] = letter;
			vhBoard [ veh[j].row + 1 ] [ veh[j].column ] = letter;
			vhBoard [ veh[j].row + 2 ] [ veh[j].column ] = letter;
		}
		else if( veh[j].size == 2 && veh[j].orientation == 'H')
		{
			vhBoard [ veh[j].row ] [ veh[j].column ] = letter;
			vhBoard [ veh[j].row ] [ veh[j].column + 1 ] = letter;
		}
		else if( veh[j].size == 2 && veh[j].orientation == 'V')
		{
			vhBoard [ veh[j].row ] [ veh[j].column ] = letter;
			vhBoard [ veh[j].row + 1 ] [ veh[j].column ] = letter;
		}
	}
}


/**
 * This function generates the string from the current board.
 * This function combines all the characters in the vehBoard array and forms a string
 * which is unique for every board state.
 * @param str a string passed in by reference to be set equal to current board state
 * @pre none 
 * @post the string now repersents the current board.
 * @exception none
 * @return void
*/
void board::generateString( string &str )
{
	str = *vhBoard;
	str + '\0';
}


/**
 * This function generates the board using the string parameter passed to it.
 * This function traverses the whole string and pulls characters form it to regenerate 
 * the board, it also updates the location of the cars based on the string.
 * @param str a string passed in by reference to be used to reproduce the board
 * @pre none 
 * @post the vhBoard and all the car locations are updated according to the string str.
 * @exception none
 * @return void
*/
void board::generateBoard( const string &str )
{
	bool* carSet = new bool(cars);
	int i = 0, j = 1;
	for(; i < cars; i++)
		carSet[i] = false;
	for(i = 1; i < 7; i++)
		for(j = 1; j < 7; j++)
		{
			vhBoard[i][j]=str[i*8+j];
			if( str[i*8+j] != 'O' && !carSet[str[i*8+j] - 97])
			{
				veh[str[i*8+j] - 97].row = i ;
				veh[str[i*8+j] - 97].column = j ;
				carSet[str[i*8+j] - 97] = true;
			}
		}
	delete [] carSet;
}


/**
 * This function resets the some of the data in the board class.
 * This function empties the boardHash queue and boardStrings map so that they can
 * be used for next scenarios.
 * @param none
 * @pre none 
 * @post boardHash and boardStrings are now empty.
 * @exception none
 * @return void
*/
void board::resetBoard()
{
	queue <string> empty;
	swap( boardHash, empty );
	boardStrings.clear();	
}
