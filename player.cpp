#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include "player.h"
#include <cstdlib>



//Constructor
Player::Player()
{
	state = 0;
	score = 501; //Initialize the Score at start of the game.
	aiming = 0; // Player is aiming at nothing.
	throw_count = 0;
	wins = 0;
	tempScore = 0;
	drawsOnSets = 0;
	gamesPlayed = 0;
	setsWon = 0;
}	

void Player::Aim()
{
	if (state == 0)
		aiming = 60;
	else if( (state == 1 && score >=70) || state ==4) 
	{
		aiming = 20;
	}
	else if (state == 1 && score < 70)
	{
		aiming = score - 50;
	}
	else if (state == 2)
	{
		int currentScore = score - tempScore;
		if (currentScore > 40)
			aiming = currentScore - 40;
		else if (currentScore % 2 == 0)
			aiming = currentScore / 2;
		else
			aiming = 1;
	}
	else if (state == 3)
	{
		aiming = (score - tempScore) - 50;
	}
	else if (state == 5)
	{
		aiming = score - tempScore;
	}
	else if (state == 6)
	{
		aiming = 0;
	}
}

void Player::State()
{
	{
	int currentScore = score - tempScore;
	if (currentScore == 0)
		state = 6;
	else if (currentScore == 50 || (currentScore >= 2 && currentScore <= 40 && currentScore % 2 == 0))
		state = 5; //hit the double to finish
	else if (score >= 90)
		state = 0;		// max possible aim  to lower score fast
	else if (throw_count == 0) {
		if (score >= 50)
			state = 1;			// try to round the score up to 50 to end with a bull (final dart)
		else
			state = 2;    //  try to round the score up to be able to finish with a double
	}
	else
	{
		if (throw_count == 1 && currentScore <= 70 && currentScore >= 51)//2nd dart 51 < currentScore < 70
			state = 3;		//try to round the score up to 50 to end with a bull(next dart)
		else
			state = 4;			// just lower the score to finish it the next turn
	}
	//std::cout <<"currentScore: "<<currentScore <<" State: "<<state<< std::endl;
}
}


int Player::Throw()
{ 
	int hit = -1;
	if ((aiming <= 20 && aiming >= 1) || aiming == 25 || aiming == 50)// single throw
	{
		hit =throw_single(aiming);
	}
	else if (aiming<=40 && aiming>=2 && aiming%2==0)// throwing for all doubles
	{
		hit = throw_double(aiming / 2);
	}

	else if (aiming !=0)// discards final darts if score is achieved
	{
		hit = throw_treble(aiming / 3);  //throwing triple
	}
	else
	{
		hit = 0;
	}
	tempScore += hit;  //temp+hit
	return hit;
}
int Player::throw_single(int d)
{// return result of throwing for single d with accuracy 88% (or 80% for the outer bull)
		//d is the score that the player is aiming for
		// Board neighbours ignoring slot zero – this might be better stored in a board class
		int bd[2][21] = { { 0, 20, 15, 17, 18, 12, 13, 19, 16, 14, 6, 8, 9, 4, 11, 10, 7, 2, 1, 3, 5 },
	{ 0, 18, 17, 19, 13, 20, 10, 16, 11, 12, 15, 14, 5, 6, 9, 2, 8, 3, 4, 7, 1 } };
	int r = rand() % 100;
	if (d == 50){
		//inner bull 70% accuracy
		if (r < 70){
			return 50;
		}
		else if (r < 95){
			return 25;
		}
		else {
			return 1 + rand() % 20;
		}

	}

	else 
		if (d == 25){
		// outer bull 80% accuracy
		if (r<80)
		{
			return 25;
		} //throw was successful
				else if (r<90)
		{
			return 50;
		} //red inner bull hit instead
				else
		{
			return 1 + rand() % 20;
		} //return a random score between 1 and 20
	}
		else
			// 1 to 20 single
	if (r<88)
			{
		return d;
	} //return score
	
	else if (r<92)
	{
		return bd[0][d];
	} //return score to the left
		else if (r<96)
	{
		return bd[1][d];
	} //return score to the right
		else if (r<98)
	{
		return 3 * d;
	}//return random score?? Improve this?
	else
	{
		return 2 * d;
	} //return random score?? Improve this?


}



int Player::throw_double(int d)
{
	// return result of throwing for double d with accuracy 80%
	// Board neighbours ignoring slot zero
	int bd[2][21] = { { 0, 20, 15, 17, 18, 12, 13, 19, 16, 14, 6, 8, 9, 4, 11, 10, 7, 2, 1, 3, 5 },
	{ 0, 18, 17, 19, 13, 20, 10, 16, 11, 12, 15, 14, 5, 6, 9, 2, 8, 3, 4, 7, 1 } };
	int r = rand() % 100;
	if (r < 80)
	{
		return 2 * d;
	}
	else if (r < 85)
	{
		return 0;
	}
	else if (r < 90)
	{
		return d;
	}
	else if (r < 93)
	{
		return 2 * bd[0][d];
	}
	else if (r < 96)
	{
		return 2 * bd[1][d];
	}
	else if (r < 98)
	{
		return bd[0][d];
	}
	else
	{
		return bd[1][d];
	}


}

int Player::throw_treble(int d) {
		// return result of throwing for treble d with accuracy p% (o<90)
		// Board neighbours ignoring slot zero
		int bd[2][21] = { { 0, 20, 15, 17, 18, 12, 13, 19, 16, 14, 6, 8, 9, 4, 11, 10, 7, 2, 1, 3, 5 },
	{ 0, 18, 17, 19, 13, 20, 10, 16, 11, 12, 15, 14, 5, 6, 9, 2, 8, 3, 4, 7, 1 } };
		int r = rand() % 100;
	if (r<75)
	{
		return 3 * d;
	} //treble hit
		else if (r<90)
	{
		return d;
	} //single hit
		else if (r<93)
	{
		return 3 * bd[0][d];
	} //treble of left hand score hit
	else if (r<96)
	{
		return 3 * bd[1][d];
	}//treble of right hand score hit
	else if (r<98)
	{
		return bd[0][d];
	}//single of left hand score hit
	else
	{
		return bd[1][d];
	}//single of left hand score hit

}

void Player::Score_Update()
{
	int currentScore = score - tempScore;
	std::cout << "score: " << score<< std::endl;
	std::cout << "Temp score:" << tempScore << std::endl;
	if (currentScore >= 0 && currentScore != 1)
		score = currentScore;


}
	
//Play function 
void Player::Play()
{
	

	tempScore = 0;
	//3 times for the arrows for every throw
	for (throw_count = 0; throw_count < 3; throw_count++)
	{
		State();
		Aim();
		int hit = Throw();
		std::cout << "He aims for " << aiming << ", he hits " << hit << "\n\n";
	}
	


	Score_Update();
}

int Player::GetScore() { return score; }
void Player::NewSet()
{
	score = 501;

}

void Player::NewGame()
{
	setsWon = 0;
	drawsOnSets = 0;
	NewSet();
}