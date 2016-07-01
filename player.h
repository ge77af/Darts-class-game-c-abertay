class Player
{
private:
	//class variables and constants
	int tempScore;
	int score;
	int state;
	int throw_count;
	int aiming; //what is the player aiming for.


	//class functions
	void State();				 //based on score remaining, chance state of the player.
	void Aim();					//find what to aim for to get 50 the fastest
	int Throw();				//use the Aim value and try to hit it.
	void Score_Update();			//function to update score for each player.
	int throw_single(int d);
	int throw_double(int d);
	int throw_treble(int d);
	int GetSets(int j);

public:
	//class variables and constants
	
	Player(); //constructor
	int GetScore();
	void NewSet();
	void NewGame();
	void Play();
	int gamesPlayed;
	int drawsOnSets;
	int wins;
	int setsWon;
};