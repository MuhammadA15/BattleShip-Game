/*
===========================================================================
Author : Muhammad Azam
Description : This program displays the gameboard of a simplified version of
Battleship. It also generates ships onto the gameboard each being represented
as a different letter. User is then able to enter coordinates for torpedo shots 
to attempt to sink two ships 
============================================================================
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int ROWS = 10; // const ints define the size of the board
const int COLS = 10;

//enum to initialize the array and the objects it includes within the array; ships, and hit and miss markers
enum Board{blank = ' ', miss = 'O', hit = 'X', carrier = 'C', battleship = 'B', submarine = 'S', destroyer = 'D'};

struct Torpedo
{
	char RowCoord;         //Structure containing row and column coords, and hit counter for each type of ship
	int ColCoord;
	int Cship;
	int Bship;
	int Sship;
	int Dship;
};
typedef Board* gameboard;    //declares pointer used to make dynamic array

void Header(); //Generates the header
void GenerateShips(gameboard *board); //Generates two different random ships onto the array
void BoardDisplay(gameboard *board, bool reveal); //Generates and displays the gameboard
void ClearBoard(gameboard *board); //Initializes the gameboard with blank spaces
bool Check_Attack(gameboard *board, Torpedo &Check_Shot, int &sunk); //Checks for victory

int main()
{
        Header(); // displays header
	
	Torpedo Check_Shot;

        char difficulty; //Used to store input of user difficulty
        int turns = 0; // stores amount of turns user will get for each difficulty
        cout << "=============== W E L C O M E   T O   B A T T L E S H I P =============== " << endl;
        cout << "\n";
difficulty:
        //Prompts user for difficulty and gets the input
        cout << "Enter difficulty level (Easy, Normal, Hard) of game (E, N, H): ";
        cin.get(difficulty);
        cout << "\n";
        switch(difficulty) //switch statement to set different amount of turns depending on difficulty
        {
                case 'E':
                case 'e':
                        turns = 30;     //User will get 30 turns on Easy
                        cout << "------------------------------------------------------------" << endl;
    cout << "This program will randomly choose two ships from your fleet \nmade up of the following vessels: Carrier, Battleship, Sub-\nmarine, and Destroyer. It will then randomly assign both of \nthe vessels to the board that are oriented either vertical-\nly or horizontally. As a player you will then have " << turns << " tries \nto sink both of the computer's vessels!" << endl;
                        cout << "------------------------------------------------------------" << endl;

                        break;
                case 'N':
                case 'n':
                        turns = 25;    //User will get 25 turns on Normal
                        cout << "------------------------------------------------------------" << endl;
                        cout << "This program will randomly choose two ships from your fleet \nmade up of the following vessels: Carrier, Battleship, Sub-\nmarine, and Destroyer. It will then randomly assign both of \nthe vessels to the board that are oriented either vertical-\nly or horizontally. As a player you will then have " << turns << " tries \nto sink both of the computer's vessels!" << endl;
                        cout << "------------------------------------------------------------" << endl;

                        break;
                case 'H':
                case 'h':
                        turns = 20;   //User will get 20 turns on Hard
                        cout << "------------------------------------------------------------" << endl;
                        cout << "This program will randomly choose two ships from your fleet \nmade up of the following vessels: Carrier, Battleship, Sub-\nmarine, and Destroyer. It will then randomly assign both of \nthe vessels to the board that are oriented either vertical-\nly or horizontally. As a player you will then have " << turns << " tries \nto sink both of the computer's vessels!" << endl;
                        cout << "------------------------------------------------------------" << endl;

                        break;
                default:
                        goto difficulty; //program will loop back to "difficulty:" if an invalid input is entered and start process over
                        break;
        }
        cout << endl;

        int Rpos, Cpos, Direction, ship1, ship2, i, j, sunk;
	bool reveal = false;  //sets ship reveal to hide
	Check_Shot.Dship = 0;   // Sets each hit counter in the struct to 0
	Check_Shot.Sship = 0;   
	Check_Shot.Bship = 0;
	Check_Shot.Cship = 0;

	sunk = 0;

        srand(time(0)); //initializes rand function
        cout << "Initializing board..." << endl;
        cout << "Assigning Vessels..." << endl;
        
	gameboard *board = new gameboard[ROWS];   //creates a dynamic array
	
	for(i = 0; i < ROWS; i++)
	{
		board[i] = new Board[COLS];
	}
	
        ClearBoard(board); //intializes board with blank spaces
        GenerateShips(board); //generates ships
        BoardDisplay(board,reveal); //displays gameboard

	for(i = 1; i <= turns; i++)   //Runs the game for the length of turns 
	{
		cout << "Select where you would like to shoot torpedoe #" << i << " (e.g., B7): ";  //Prompts user to enter torpedo shot
		Check_Attack(board,Check_Shot,sunk);  //Retrieves shot coords, checks to make sure its acceptable, checks for ships sunk, and checks for victory
		BoardDisplay(board,reveal); //Displays updated board
		if(sunk == 2)   
		{
			cout << "Congrats! You sank both ships in " << i << " turns!" << endl;    //Prints out victory message if victory is acheived
			i = 100;
		}
		if(i == turns)
		{
			reveal = true;  //sets ships to reveal
			BoardDisplay(board,reveal); //prints out board with ships shown
			cout << "GAME OVER. You were not able to sink all the ships." << endl;    //Prints out defeat message if both ships arent sunk in time
		}
	}
		for(i = 0; i < ROWS; i++) //returns memory back to the free store
		{
			delete []board[i];	
		}

	return 0;
}

/*
============================================================================
Function : GenerateShips
parameters : An enum data type representing the gameboard array
Return : void
Description : Generates two ships onto the gameboard horizontally or vertically, each a different type of ship and with
different locations in the array
============================================================================
*/
void GenerateShips(gameboard *board)
{
        int ship1, Rpos, Cpos; //ship1 represents the length of the first ship, Rpos represents the row coordinate, Cpos represents the column coordinate
        int Direction; //used to set the ship randomly horizontal and vertical

        ship1 = rand() % 4 + 2; //randomly generates the length of the ship between 2-5

        Rpos = rand() % ROWS; //randomly generates the row coordinate
        Cpos = rand() % COLS; //randomly generates the column coordinate
        Direction = rand() % 2; //randomly generates whether the ship will be horizontal or vertical using 1 and 0

        if(Direction == 0) // Vertical orientation
        {
                //checks to see if the ship will fit in the array, if not then will randomly generate a new row coordinate
                while(Rpos + ship1 >= ROWS)
                {
                         Rpos = rand() % ROWS;
                }
                for(int i = 0; i < ship1; i++)
                {
                        switch(ship1)
                        {
                                case 2:
                                        board[Cpos][Rpos + i] = destroyer;
                                        break;
                                case 3:
                                        board[Cpos][Rpos + i] = submarine; //submarine
                                        break;
                                case 4:
                                        board[Cpos][Rpos + i] = battleship; //battleship
                                        break;
                                case 5:
                                        board[Cpos][Rpos + i] = carrier; //carrier
                                        break;
                        }			
                }
        }
        if(Direction == 1) //horizontal orientation
        {
                //checks to see if ship fits in array, if not generates new column coords
                while(Cpos + ship1 >= COLS)
                {
                        Cpos = rand() % COLS;
                }
                for(int i = 0; i < ship1; i++)
                {
                        switch(ship1)
                        {
                                case 2:
                                        board[Cpos + i][Rpos] = destroyer; //destroyer
                                        break;
                                case 3:
                                        board[Cpos + i][Rpos] = submarine; //submarine
                                        break;
                                case 4:
                                        board[Cpos + i][Rpos] = battleship; //battleship
                                        break;
                                case 5:
                                        board[Cpos + i][Rpos] = carrier; //carrier
                                        break;
                        }
                }

        }

        int ship2, Rpos2, Cpos2; //ship2 = the length of the second ship, Rpos2 = rows position of second ship, Cpos2 = column position of second ship
        do
        {
                ship2 = rand() % 4 + 2;   //runs loop until ship 2 has a different length than ship 1
        }while(ship2 == ship1);

        //generates ship2 coordinates
        Rpos2 = rand() % ROWS;
        Cpos2 = rand() % COLS;

        Direction = rand() % 2; //generates ship 2 orientation

        if(Direction == 0) //vertical
        {
                while(Rpos2 + ship2 >= ROWS)
                {
                         Rpos2 = rand() % ROWS;   //checks to see if ship fits on array
                }
                for(int j = 0; j < Rpos2; j++)
                {
                        if(board[Cpos2][Rpos2 + j] != ' ')
                        {
                                Rpos2 = rand() % ROWS;    //checks to see if the coordinates of ship 2 are occupied by ship 1
                                Cpos2 = rand() % COLS;    //if occupied will generate a new coord for  position
                        }
                }
                for(int i = 0; i < ship2; i++)
                {
                        switch(ship2)
                        {
                                case 2:
                                        board[Cpos2][Rpos2 + i] = destroyer; //destroyer
                                        break;
                                case 3:
                                        board[Cpos2][Rpos2 + i] = submarine; //submarine
                                        break;
                                case 4:
                                        board[Cpos2][Rpos2 + i] = battleship; //battleship
                                        break;
                                case 5:
                                        board[Cpos2][Rpos2 + i] = carrier; //carrier
                                        break;
                        }
                }
        }
        if(Direction == 1) //horizontal
        {
                while(Cpos2 + ship2 >= COLS)
                {
                        Cpos2 = rand() % COLS;   //checks to see if ship2 fits in array
                }
                for(int j = 0; j < Cpos2; j++)
                {
                        if(board[Cpos2 + j][Rpos2] != ' ')
                        {
                                Cpos2 = rand() % COLS;  //checks for blank space on the coords ship2 will entail
                                Rpos2 = rand() % ROWS;  //generates new  coords if occupied
                        }
                }
                for(int i = 0; i < ship2; i++)
                {
                        switch(ship2)
                        {
                                case 2:
                                        board[Cpos2 + i][Rpos2] = destroyer; //destroyer
                                        break;
                                case 3:
                                        board[Cpos2 + i][Rpos2] = submarine; //submarine
                                        break;
                                case 4:
                                        board[Cpos2 + i][Rpos2] = battleship; //battleship
                                        break;
                                case 5:
                                        board[Cpos2 + i][Rpos2] = carrier; //carrier
                                        break;
                        }
                }

        }


}

/*
============================================================================
Function : BoardDisplay
Parameters : An enum data type representing the gameboard array 
	     A bool that represents the reveal of ships
Return : void
Description : Generates the array with blank spaces with coordinate system of letters
A-J going up and down, and 1-10 going left to right
============================================================================
*/

void BoardDisplay(gameboard *board, bool reveal)
{		
        cout << "    1 2 3 4 5 6 7 8 9 10 " << endl;
        cout << "  +---------------------+" << endl;
        for(int i = 0; i < ROWS; i++)
        {
                cout << static_cast<char>(65 + i) << " | ";     //Prints out the letter accoring to the ASCII value per row
                for(int j = 0; j < COLS; j++)
                {
			if(reveal == false) //Prints out a blank space if reveal is set to false for all ships
			{
				if(board[i][j] == destroyer || board[i][j] == submarine || board[i][j] == battleship || board[i][j] == carrier)
				{	
					cout << static_cast<char>(board[i - 1][j - 1]) << ' ';  //prints blank space for ships
				
				}
                        	else
				{
	        			cout << static_cast<char>(board[i][j]) << " ";   // prints out array normally if array doesnt come across any ships
                		}
			}
			if(reveal == true) //prints out ships normally if reveal set to true
			{
				 cout << static_cast<char>(board[i][j]) << " ";  //prints out array with normal values for ships 
			}
		}
                cout << "|";
                cout << endl;
        }
        cout << "  +---------------------+" << endl;
}

/*
============================================================================
Function : ClearBoard
Parameters : An enum data type representing the gameboard array
Return : void
Description : Sets each value of the array as a blank space so that the board
may print out those blank spaces later to display the board
============================================================================
*/

void ClearBoard(gameboard *board)
{
        for(int i = 0; i < ROWS; i++)
        {
                for(int j = 0; j < COLS; j++)
                {
                        board[i][j] = blank;   //nested for-loop sets every value of board[i][j] as a blank space character
                }
        }
}

/*
============================================================================
Function : Header
Parameters : none
Return : void
Description : Displays department, section, name, euid, and email
============================================================================
*/

void Header()
{
	
}

/*
============================================================================
Function: Check_Attack
Parameters: Enum representing the gameboard array 
	     Structure containing the hit counter and user-entered coordinates
Return: Boolean True or False  
Description: Gets user inputed shot coordinates and converts them to useable position in the board array. Updates hits on each ship
	      and prints out message if a ship is sunk and if both ships are sunk will return true for victory
============================================================================
*/

bool Check_Attack(gameboard *board, Torpedo &Check_Shot, int &sunk)
{
TorpedoCoord:
        cin >> Check_Shot.RowCoord;  //Gets row coord
        cin >> Check_Shot.ColCoord;  //Gets column coord
        switch(Check_Shot.RowCoord)  //Converts the row coord into a useable value for the board array
        {
        	case 'A':
                case 'a':
                	 Check_Shot.RowCoord = 1;
                         break;
                case 'B':
                case 'b':
                         Check_Shot.RowCoord = 2;
                         break;
                case 'C':
                case 'c':
                         Check_Shot.RowCoord = 3;
                         break;
                case 'D':
                case 'd':
                         Check_Shot.RowCoord = 4;
                         break;
                case 'E':
                case 'e':
                         Check_Shot.RowCoord = 5;
                         break;
                case 'F':
                case 'f':
                         Check_Shot.RowCoord = 6;
                         break;
                case 'G':
                case 'g':
                         Check_Shot.RowCoord = 7;
                         break;
                case 'H':
                case 'h':
                         Check_Shot.RowCoord = 8;
                         break;
                case 'I':
                case 'i':
                         Check_Shot.RowCoord = 9;
                         break;
                case 'J':
                case 'j':
                         Check_Shot.RowCoord = 10;
                         break;
                default:
                        cout << "Torpedo cannot be fired at " << Check_Shot.RowCoord << Check_Shot.ColCoord << ". Try Again: ";  //Print out message if coordinate is outside range of array                
                        goto TorpedoCoord;  //makes user input another coordinate
                        break;
	}
	switch(Check_Shot.ColCoord)  //Sets a specific set of values useable to column coordinates
        {
                case 1:
                         Check_Shot.ColCoord = 1;
                         break;
                case 2:
                         Check_Shot.ColCoord = 2;
                         break;
                case 3:
                         Check_Shot.ColCoord = 3;
                         break;
                case 4:
                         Check_Shot.ColCoord = 4;
                         break;
                case 5:
                         Check_Shot.ColCoord = 5;
                         break;
                case 6:
                         Check_Shot.ColCoord = 6;
                         break;
                case 7:
                         Check_Shot.ColCoord = 7;
                         break;
                case 8:
                         Check_Shot.ColCoord = 8;
                         break;
                case 9:
                         Check_Shot.ColCoord = 9;
                         break;
                case 10:
                         Check_Shot.ColCoord = 10;
                         break;
                default:
                        cout << "Torpedo cannot be fired at " << Check_Shot.RowCoord << Check_Shot.ColCoord << ". Try Again: "; //prints out message if col is outside array range
                        goto TorpedoCoord; //makes user input valid coords
                        break;
        }
      	if(board[Check_Shot.RowCoord - 1][Check_Shot.ColCoord - 1] == hit || board[Check_Shot.RowCoord - 1][Check_Shot.ColCoord - 1] == miss) 
        {
                cout << "You have already fired at this coordinate, please choose another coordinate: "; //Checks to see if user has already shot at the entered coordinates
                goto TorpedoCoord;  //Sends user back to re-enter coordinates if repeated shot
        }
        if(board[Check_Shot.RowCoord - 1][Check_Shot.ColCoord - 1] == destroyer || board[Check_Shot.RowCoord - 1][Check_Shot.ColCoord - 1] == submarine || board[Check_Shot.RowCoord - 1][Check_Shot.ColCoord - 1] == battleship || board[Check_Shot.RowCoord - 1][Check_Shot.ColCoord - 1] == carrier)
        {
                if(board[Check_Shot.RowCoord - 1][Check_Shot.ColCoord - 1] == destroyer)   //checks to see if entered coordinates hit a Destroyer
                {
                        Check_Shot.Dship = Check_Shot.Dship + 1; //updates hit counter if Destroyer is hit
                }
                if(board[Check_Shot.RowCoord - 1][Check_Shot.ColCoord - 1] == submarine)  //checks to see if entered coordinates hit a Submarine
                {
                        Check_Shot.Sship = Check_Shot.Sship + 1; //updates hit counter if Submarine is hit
                }
                if(board[Check_Shot.RowCoord - 1][Check_Shot.ColCoord - 1] == battleship)  //checks to see if entered coordinates hit a Battleship
                {
                        Check_Shot.Bship = Check_Shot.Bship + 1; //updates hit counter if Battleship is hit
                }
                if(board[Check_Shot.RowCoord - 1][Check_Shot.ColCoord - 1] == carrier)   //checks to see if entered coordinates hit a Carrier
                {
                        Check_Shot.Cship = Check_Shot.Cship + 1; //updates hit counter if Carrier is hit
                }

                board[Check_Shot.RowCoord - 1][Check_Shot.ColCoord - 1] = hit;  //Prints out message if a ship is hit and prints out 'x' on array
                cout << "You made a hit!" << endl;

                if(Check_Shot.Dship == 2)
                {
                        cout << "You sank my Destroyer!" << endl;  //Prints out message when destroyer is sunk
                        Check_Shot.Dship = 10; //gets rid of message so it doesnt appear on the next shot
			sunk = sunk + 1; //counter for how many ships have been sunk updated
                }
                if(Check_Shot.Sship == 3)
                {
                        cout << "You sank my Submarine!" << endl;  //prints out message if submarine is sunk
			Check_Shot.Sship = 10; //gets rid of message so it doesnt appear on next shot
			sunk = sunk + 1;
                }
                if(Check_Shot.Bship == 4)
                {
                        cout << "You sank my Battleship!" << endl;  //prints out message if battleship is sunk
			Check_Shot.Bship = 10;  //gets rid of message so it doesnt appear on next shot
			sunk = sunk + 1;
                }
                if(Check_Shot.Cship == 5)
                {
                        cout << "You sank my Aircraft Carrier!" << endl;  //prints out message if carrier is sunk
			Check_Shot.Cship = 10;  //gets rid of message so it doesnt appear on next shot
			sunk = sunk + 1;
                }
        }
        else
        {
                board[Check_Shot.RowCoord - 1][Check_Shot.ColCoord - 1] = miss;  //Prints out message if entered coordinates miss a ship and print out 'O' on the array
                cout << "miss..." << endl;           
        }  
	if(sunk == 2)    //function returns true if two ships have been sunk
	{
		return true;
	}
	else   //Returns false if 2 ships havent sank yet
	{		
		return false;
    	}
}           


