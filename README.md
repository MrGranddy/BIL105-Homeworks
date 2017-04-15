# BIL105 is a class to learn about programming more deeply than BIL103, the goal of the class is starting to learn how to program in a scientific manner and we are doing this with C Programming language.

# UPDATE: I deleted the question PDFs because it might be unethical, I'll ask if I can publish them, if they say yes I will include them again.

# Explanations:

# HW1: 

(1) Each team consists of N players. At the beginning, both teams have a score of 0 points. The game ends when a team's score reaches S points.
(2) A round starts with drawing lots to decide which team goes  rst. Each team has a 50% probability to start the round.
(3) A random player from the selected team starts the game.
(4) The current player tries to pass the ball to a next player from its team. The next player is randomly selected from the N-1 other players of the team. The current player can pass the ball successfully with a probability of P% and a random player from the opponent team catches the ball with a probability of (100-P)%.
(5) If a team can pass the ball to its W players consecutively, its score is increased by 1 points. If the team's new score is S points, then the game is over. Otherwise, the new round is started as in (2).
(6) When a pass is intercepted by the opponent team, it starts to attack as in (4).

# HW2:

The aim of this homework is producing a set of random numbers based on the random number generation functions specified by the user AND printing the histogram of these numbers in base 500. A pseudo-random number generator (PRNG) is used to generate a sequence of numbers that can't be predicted beforehand by its users.

# HW3:

The user enters a character sequence then some operations will be done on it.

# HW4:

Program reads a text file and outpust some BMI values, sorted.
./a.out N M threshold
N: Total number of people. This value is variable, so you have to allocate enough space at run time.
M: Number of people whose BMI values are the farthest from the threshold.
threshold: Normal value of the BMI value.
