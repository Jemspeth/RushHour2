/** @file board.h
@author Arush Prashar
@version Revision 1.1
@brief The board.h file provides decleration of supporting vehicle struct and board class for the rushhour.cpp program. 
@date Tuesday, October 03, 2017
*/


//
//  Precompiler Directives ////////////////////////////////////////
//
#ifndef BOARD_H
#define BOARD_H


//
// Header Files ///////////////////////////////////////////////////
//
#include <iostream>
#include <map>
#include <queue>
#include <string>
using namespace std;


//
// Struct /////////////////////////////////////////////////////////
//
struct vehicle
{
	int size;	/**<length of the vehicle Determines whether vehicle is a car or truck*/
	char orientation;	/**< Determines whether vehicle is horizontal 'H' or vertical 'V'.*/
	int row;	/**< Denotes the row in which the vehicle is placed or its top most point on the board.*/
	int column;	/**< Denotes the column in which the vehicle is placed or its left most point on the board.*/
};


//
// Class //////////////////////////////////////////////////////////
//
class board
{
  public:
  	//The required methods.
	bool didWeWin();	/**< This function checks that did we win by checking if veh[0] is at the edge*/
	bool moveFwd(int car);  /**< This function moves the vehicle forward if there is empty space in front (right or down) of the vehicle.*/
	bool moveBwd(int car);  /**< This function moves the vehicle backward if there is empty space behind (left or up) the vehicle.*/
	void solve(int& level, int cap, bool& win);	/**< This function makes recursive calls to itself and tries to solve the board in least moves.*/
	void setCars(int numVehicle);	/**< This function sets the cars data member for the numbers of cars on the board*/
	void setVehicle(int sz, char ornt, int rw, int col, int vehNum);	/**< This function set up the veh array with details about each vehicle...*/
	void setBoard();	/**< This function sets the board according to data in veh array.*/
	
		void createLevel(int level,bool&win);
		void generateBoard(string str);
		void generateString( string &str );
		void getVehicle();	//this function can be removed
		void getVhBoard();	//this function can be removed
  private:
  	//the required data members.
  	vehicle veh[10];	/**< Stores the data of all the vehicles on the board.*/
  	int cars;	/**< Stores the total number of vehicles in a given scenario.*/
  	char vhBoard[8][8];	/**< This is the rush hour problem board that needs to be solved.*/
  	map <string,int> boardStrings; 
  	queue <string> boardHash;
};


//
//  Terminating Precompiler Directives ///////////////////////////////
//
#endif	// BOARD_H
