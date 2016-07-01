//DISCLAIMER: YOU CAN USE THIS CODE FREELY AND EDIT IT ON YOUR OWN, EVEN CLAIM IT TO BE YOURS.
//AS OF THIS MOMENT THE CODE IS CONSIDERED OPEN SOURCE . (ignore some giberrish comments as they are in greek)

// Declare players
// Start while loop (while nobody has won)
// -- Iterate a for loop 3 times, throwing Cid's darts
// -- Iterate a for loop 3 times, throwing Joe's darts
// End while loop (someone has one)
// Output name of winner 
// μεσα στo Player φτιαχνω μεταβλητη sets, ekei apothikevontai ta sets won tou kathe paixth
//for (j) trexei 13 fores ektws


#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include "player.h"
#include <cstdlib>

using namespace std;

int main()
{
	int player_switch = 0;
	Player joe;
	Player sid;
	

	for (int i = 0; i < 100; i++) //game loops
	{

		cout << "Starting new Match" << endl;
		joe.NewGame();
		sid.NewGame();
		for (int j = 0; j <13; j++)
		{
			cout << "Starting new Set" << endl;
			sid.NewSet();
			joe.NewSet();
			while (joe.GetScore()>0 && sid.GetScore() > 0) //countdown loop
			{
				if (player_switch == 0)
				{
					cout << endl << "Joe's turn" << endl;
					cout << "Joe has " << joe.GetScore() << " points left" << endl;
					joe.Play(); //Playing function

					player_switch = 1;
				}

				else
				{
					cout << endl << "Sid's turn" << endl;
					cout << "Sid has " << sid.GetScore() << " points left" << endl;
					sid.Play(); //Playing function
					player_switch = 0;
				}
			}

			if (joe.GetScore() == 0 && sid.GetScore() == 0)
			{
				joe.drawsOnSets++;
				sid.drawsOnSets++;
			}
			else if (joe.GetScore() == 0)
				joe.setsWon++;
			else
				sid.setsWon++;

			cout << "Set finished" << endl;
			cout << "joe sets won: " << joe.setsWon << endl;
			cout << "sid sets won: " << sid.setsWon << endl;
		
			//an kapoios ftasei ta 7 sets win , break for
			// telos for me j
			//allagh games-wins se sets-wins  ///   If someone wins 7 sets he wins the game because its over 50% of the games in 13 games  hence the other player 
			//cant win no matter what
			if (joe.setsWon == 7 || sid.setsWon == 7)
				break;

		}
		if (joe.setsWon > sid.setsWon)
			joe.wins++;
		else
			sid.wins++;

		//update match wins
		cout << "-------------------------------------------------" << endl;
		cout << "match " << i+1 << " finished" << endl;
		cout << "joe wins: " << joe.wins << endl;
		cout << "sid wins: " << sid.wins << endl;
		cout << "-------------------------------------------------" << endl;


	
	}
	getchar();
	return 0;
}