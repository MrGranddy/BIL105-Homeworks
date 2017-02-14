// Name: Vahit Buðra Yeþilkaynak
// Student ID: 150150019
// E-mail: bugrayesilkaynak@gmail.com



 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>

 int main ( void )

{

	time_t t;
	srand((unsigned) time(&t));

	int N = 0;
	int P = 0;
	int W = 0;
	int S = 0;
	int scoreTeam1 = 0;
	int scoreTeam2 = 0;
        
	// Getting the values from the user

	printf("$ Enter number of players per team (N)\n$ ");
	scanf("%d", &N); 
	printf("$ Enter probability for a successful pass (P)\n$ ");
	scanf("%d", &P); 
	printf("$ Enter number of passes to win a single round (W)\n$ ");
	scanf("%d", &W); 
	printf("$ Enter target score (S)\n$ ");
	scanf("%d", &S); 
	
	// Declaring integer round to keep track of the round they are in

	int round = 0;

	/* This loop will simulate the rounds and print what happened
	 until one team reaches the target score */

	while (scoreTeam1 < S && scoreTeam2 < S)
	{	
		/* When a round starts the program increments round 
		so we know the number of the round we are in */

		round++;
		printf("Round-%d:\n\t", round);
	
		/* These integers are used only for checking which player has the ball.
		At the start of the round no team has the ball so the integers are starting with zero
		which means false */

		int B_t1Current = 0;
		int B_t2Current = 0;

		// This integer is a random number between [1, 100]

		int prob = (rand() % 100) + 1;
	
		/* There are 50 numbers smaller or greater than 50 in the range [1, 100] so
		the program is checking if the random number prob is smaller or equal to 50
		there are total of 100 numbers in the given range so the chances for this to
		be true is 50% */

		// Team1 has the ball
	
		if (prob <= 50)
		{
			printf("Team1 is selected\n\t");
			B_t1Current = 1;
		}

		/* In this situation the probability of getting this situation is 100 - 50%
		I could explain it better on the example below but I don't want to leave any 
		question marks. If there are 7 blue and 3 red balls, the chance for me to
		pick a blue one is 70%, the chance for me to pick a red one is 30%. As you see
		if there are two situations the sum of percentage of the probability of these two
		situations is 100. */  

		// Team 2 has the ball
	
		else
		{
			printf("Team2 is selected\n\t");
			B_t2Current = 1;
		}
	
		// Select a random player among N players

		int whichPlayer = (rand() % N) + 1;

		printf("Player%d", whichPlayer);

		/* They will start to pass in order to win so I declared this value to know how many 
		passes did they make. The round will end if a team passes W times. */

		int currentNumberOfPasses = 0;
	
		while (currentNumberOfPasses < W - 1)
		{

			// A random number between [1, 100]
			
			int passLuck = (rand() % 100) + 1;
			
			// If passLuck is bigger than P this means the player couldn't pass	
			
			if (passLuck > P)
			{

				// Swapping the values here because one team took the ball while the other lost it

				int temp = B_t1Current;
				B_t1Current = B_t2Current;
				B_t2Current = temp;
				
				// Printing which team took the ball

				if (B_t1Current){printf("\n\tTeam1 captured the ball!");}
				else {printf("\n\tTeam2 captured the ball!");} 	

				// Who is the player took the ball			

				whichPlayer = (rand() % N) + 1;

				printf("\n\tPlayer%d", whichPlayer);

				// Since enemy team took the ball the pass count resets

				currentNumberOfPasses = 0;
			}

			else
			{

				// I don't want a player to pass to himself so I'm storing which player passed the ball				

				int oldWP = whichPlayer;
				whichPlayer = (rand() % N) + 1;
				
				// If the passing player and the taking player are the same the program is selecting a new player

				while (oldWP == whichPlayer)
				{
					whichPlayer = (rand() % N) + 1;	
				}
				
				printf(" -> Player%d", whichPlayer);

				// The pass was successful so the program is incrementing currentNumberOfPasses by 1

				currentNumberOfPasses++;
			}
		}
		printf("\n");

		/* When the round ends this code looks which team has the ball
		 just before the round finished. If the round is finished this means
		a team reached the required number of passes W. So the program doesn't know
		which team did it yet. Since there is no team changes after the pass
		that finishes the game, the current team is the winner of the round.
		The winner of the round's score is incremented by 1 */

		if (B_t1Current) {printf("\tSuccess! New Score of Team1 is %d\n\n", (scoreTeam1 + 1)); scoreTeam1++;}
		else {printf("\tSuccess! New Score of Team2 is %d\n\n", (scoreTeam2 + 1)); scoreTeam2++;}
	
	}

	// If the first while loop ended this means one team reached the target score.
	// This code checks which team it is and writes who the winner team is

	if (scoreTeam1 == S) {printf("GAME OVER: Team1 reached the target score (%d) and won the game.\n", S);}
	else {printf("GAME OVER: Team2 reached the target score (%d) and won the game.\n", S);}
}
