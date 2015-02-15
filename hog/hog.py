"""The Game of Hog."""

from dice import four_sided, six_sided, make_test_dice
from ucb import main, trace, log_current_line, interact

GOAL_SCORE = 100 # The goal of Hog is to score 100 points.

######################
# Phase 1: Simulator #
######################

def roll_dice(num_rolls, dice=six_sided):
	"""Roll DICE for NUM_ROLLS times.  Return either the sum of the outcomes,
	or 1 if a 1 is rolled (Pig out). This calls DICE exactly NUM_ROLLS times.

	num_rolls:  The number of dice rolls that will be made; at least 1.
	dice:       A zero-argument function that returns an integer outcome.
	"""
	# These assert statements ensure that num_rolls is a positive integer.
	assert type(num_rolls) == int, 'num_rolls must be an integer.'
	assert num_rolls > 0, 'Must roll at least once.'
	i, score = 0, 0
	roll_one = False
	while i < num_rolls:
		outcome = dice()
		if outcome == 1:
			roll_one = True
		i, score = i + 1, score + outcome
	if roll_one:
		return 1
	return score


def take_turn(num_rolls, opponent_score, dice=six_sided):
	"""Simulate a turn rolling NUM_ROLLS dice, which may be 0 (Free bacon).

	num_rolls:       The number of dice rolls that will be made.
	opponent_score:  The total score of the opponent.
	dice:            A function of no args that returns an integer outcome.
	"""
	assert type(num_rolls) == int, 'num_rolls must be an integer.'
	assert num_rolls >= 0, 'Cannot roll a negative number of dice.'
	assert num_rolls <= 10, 'Cannot roll more than 10 dice.'
	assert opponent_score < 100, 'The game should be over.'
	if num_rolls == 0:
		return abs(opponent_score // 10 - opponent_score % 10) + 1
	return roll_dice(num_rolls, dice)
	

def select_dice(score, opponent_score):
	"""Select six-sided dice unless the sum of SCORE and OPPONENT_SCORE is a
	multiple of 7, in which case select four-sided dice (Hog wild).
	"""
	wild_or_not = (score + opponent_score) % 7 
	if wild_or_not == 0:
		return four_sided
	return six_sided

def bid_for_start(bid0, bid1, goal=GOAL_SCORE):
	"""Given the bids BID0 and BID1 of each player, returns three values:

	- the starting score of player 0
	- the starting score of player 1
	- the number of the player who rolls first (0 or 1)
	"""
	assert bid0 >= 0 and bid1 >= 0, "Bids should be non-negative!"
	assert type(bid0) == int and type(bid1) == int, "Bids should be integers!"
	if bid0 == bid1:
		return goal, goal, 0
	if bid0 == bid1 - 5:
		return 0, 10, 1
	if bid1 == bid0 - 5:
		return 10, 0, 0
	if bid0 > bid1:
		return bid1, bid0, 0
	else:
		return bid1, bid0, 1

def other(who):
	"""Return the other player, for a player WHO numbered 0 or 1.

	>>> other(0)
	1
	>>> other(1)
	0
	"""
	return 1 - who

def play(strategy0, strategy1, score0=0, score1=0, goal=GOAL_SCORE):
	"""Simulate a game and return the final scores of both players, with
	Player 0's score first, and Player 1's score second.

	A strategy is a function that takes two total scores as arguments
	(the current player's score, and the opponent's score), and returns a
	number of dice that the current player will roll this turn.

	strategy0:  The strategy function for Player 0, who plays first
	strategy1:  The strategy function for Player 1, who plays second
	score0   :  The starting score for Player 0
	score1   :  The starting score for Player 1
	"""
	who = 0  # Which player is about to take a turn, 0 (first) or 1 (second)
	while score0 < 100 and score1 < 100:
		if who == 0:
			dice_type = select_dice(score0, score1)
			score0 += take_turn(strategy0(score0, score1), score1, dice_type)
		else:
			dice_type = select_dice(score1, score0)
			score1 += take_turn(strategy1(score1, score0), score0, dice_type)
		if score0 == 2 * score1 or score1 == 2 * score0:
			score0, score1 = score1, score0
		who = other(who)
	return score0, score1  # You may want to change this line.

#######################
# Phase 2: Strategies #
#######################

def always_roll(n):
	"""Return a strategy that always rolls N dice.

	A strategy is a function that takes two total scores as arguments
	(the current player's score, and the opponent's score), and returns a
	number of dice that the current player will roll this turn.

	>>> strategy = always_roll(5)
	>>> strategy(0, 0)
	5
	>>> strategy(99, 99)
	5
	"""
	def strategy(score, opponent_score):
		return n
	return strategy

# Experiments

def make_averaged(fn, num_samples=1000):
	"""Return a function that returns the average_value of FN when called.

	To implement this function, you will have to use *args syntax, a new Python
	feature introduced in this project.  See the project description.

	>>> dice = make_test_dice(3, 1, 5, 6)
	>>> averaged_dice = make_averaged(dice, 1000)
	>>> averaged_dice()
	3.75
	>>> make_averaged(roll_dice, 1000)(2, dice)
	6.0

	In this last example, two different turn scenarios are averaged.
	- In the first, the player rolls a 3 then a 1, receiving a score of 1.
	- In the other, the player rolls a 5 and 6, scoring 11.
	Thus, the average value is 6.0.
	"""
	def aver(*args):
		i, total = 0, 0
		while i < num_samples:
			total += fn(*args)
			i += 1
		return total / num_samples
	return aver
	

def max_scoring_num_rolls(dice=six_sided):
	"""Return the number of dice (1 to 10) that gives the highest average turn
	score by calling roll_dice with the provided DICE.  Assume that dice always
	return positive outcomes.

	>>> dice = make_test_dice(3)
	>>> max_scoring_num_rolls(dice)
	10
	"""
	i = 1
	max_score = 0
	while i <= 10:
		current_score = make_averaged(roll_dice)(i, dice)
		if current_score > max_score:
			k = i
			max_score = current_score
		i += 1
	return k
			

def winner(strategy0, strategy1):
	"""Return 0 if strategy0 wins against strategy1, and 1 otherwise."""
	score0, score1 = play(strategy0, strategy1)
	if score0 > score1:
		return 0
	else:
		return 1

def average_win_rate(strategy, baseline=always_roll(5)):
	"""Return the average win rate (0 to 1) of STRATEGY against BASELINE."""
	win_rate_as_player_0 = 1 - make_averaged(winner)(strategy, baseline)
	win_rate_as_player_1 = make_averaged(winner)(baseline, strategy)
	return (win_rate_as_player_0 + win_rate_as_player_1) / 2 # Average results

def run_experiments():
	"""Run a series of strategy experiments and report results."""
	if True: # Change to False when done finding max_scoring_num_rolls
		six_sided_max = max_scoring_num_rolls(six_sided)
		print('Max scoring num rolls for six-sided dice:', six_sided_max)
		four_sided_max = max_scoring_num_rolls(four_sided)
		print('Max scoring num rolls for four-sided dice:', four_sided_max)

	if False: # Change to True to test always_roll(8)
		print('always_roll(8) win rate:', average_win_rate(always_roll(8)))

	if False: # Change to True to test bacon_strategy
		print('bacon_strategy win rate:', average_win_rate(bacon_strategy))

	if False: # Change to True to test swap_strategy
		print('swap_strategy win rate:', average_win_rate(swap_strategy))

	if True: # Change to True to test final_strategy
		print('final_strategy win rate:', average_win_rate(final_strategy))

	"*** You may add additional experiments as you wish ***"


# Strategies

def bacon_strategy(score, opponent_score, margin=8, num_rolls=5):
	"""This strategy rolls 0 dice if that gives at least MARGIN points,
	and rolls NUM_ROLLS otherwise.
	"""
	if abs(opponent_score // 10 - opponent_score % 10) + 1 >= margin:
		return 0
	else:
		return num_rolls

def swap_strategy(score, opponent_score, margin=8, num_rolls=5):
	"""This strategy rolls 0 dice when it would result in a beneficial swap and
	rolls NUM_ROLLS if it would result in a harmful swap. It also rolls
	0 dice if that gives at least MARGIN points and rolls
	NUM_ROLLS otherwise.
	"""
	bacon_score = abs(opponent_score // 10 - opponent_score % 10) + 1
	if 2 * (bacon_score + score) == opponent_score:
		return 0
	if bacon_score + score == 2 * opponent_score:
		return num_rolls
	if bacon_score >= margin:
		return 0
	return num_rolls  

def final_strategy(score, opponent_score):
	"""Write a brief description of your final strategy.

	First, apply free bacon and swap rules if it's beneficial
	Second, make opponent roll 4-sided more often
	Third, roll 4-sided dice and 6-sided dice differently
	Fourth, general strategies for leading position and of beginning of the game
	Last, general strategies based on the difference between score and opponent_score
	For detailed explanations, plz see the comments in the program.
	"""

	bacon_score = abs(opponent_score // 10 - opponent_score % 10) + 1
	scores_sum = score + opponent_score
	dif = score - opponent_score
	# If free bacon leads you to win, then roll 0 dice.
	if (100-score) <= bacon_score:
		return 0	
	# Beneficial applications of swap rule
	elif 2 * (bacon_score + score) == opponent_score:
		return 0
	elif bacon_score + score == 2 * opponent_score:
		return 4
	elif score == ((opponent_score // 2) - 1):
		return 10
	# Make opponent roll 4-sided dice more often
	elif (scores_sum+bacon_score) % 7 == 0:
		return 0
	elif scores_sum % 7 == 6:
		return 10
	# Best strategy for four_sided dice by max_scoring_num_rolls
	elif scores_sum % 7 == 0:
		return 4
	# Strategies for leading position and for beginning of the game
	elif score > 96:
		return 1
	elif score > 93:
		if score - opponent_score > 20:
			return 1
		return 2
	elif score < 35:
		return 6
	# Strategies of a polynomial regression varying by dif between score and opponent_score
	elif dif < 0: 
		return int( pow( dif / 10 + 10 , 2 ) * (- 1/ 20) + 10)
	elif dif >= 0:
		return int( pow( dif / 10 , 2 ) * ( -1/25 ) + 5)

print('final_strategy win rate:', average_win_rate(final_strategy))
##########################
# Command Line Interface #
##########################

# Note: Functions in this section do not need to be changed.  They use features
#       of Python not yet covered in the course.


@main
def run(*args):
	"""Read in the command-line argument and calls corresponding functions.

	This function uses Python syntax/techniques not yet covered in this course.
	"""
	import argparse
	parser = argparse.ArgumentParser(description="Play Hog")
	parser.add_argument('--run_experiments', '-r', action='store_true',
						help='Runs strategy experiments')
	args = parser.parse_args()

	if args.run_experiments:
		run_experiments()
