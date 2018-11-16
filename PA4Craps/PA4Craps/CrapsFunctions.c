#include "Header.h"

//Prints out the game rules to the player and returns void
void print_game_rules()
{

	printf("Welcome to the Craps game!\n");
	printf("The rules:\n\n");
	printf("You will roll two dice. Each die has six faces. These faces contain 1, 2, 3, 4,\n5, and 6 spots. After the dice have come to rest, the sum of the spots on the \ntwo upward faces is calculated. If the sum is 7 or 11 on the first throw, you \nwin. If the sum is 2, 3, or 12 on the first throw (called ""craps""), you lose (i.e.the ""house"" wins). If the sum is 4, 5, 6, 8, 9, or 10 on your first throw, then\nthe sum becomes your ""point."" To win, you must continue rolling the dice until you""make your point."" You lose by rolling a 7 before making your point.\n\n");

	return;
}

//Gets the initial bank balance from the user and determines if it is valid input.
 double get_bank_balance (void)
 {
	 double bank_balance = 0.0;

	 printf("Please enter your initial bank balance as a double (Ex. 100.00).\n$");
	 scanf("%lf", &bank_balance);
	 fflush(stdin);

	 //Chump proofing
	 while(bank_balance < 0.01)
	 {
		 fflush(stdin);
		 printf("Can't gamble with no money chump. Try again.\n");
		 scanf("%lf", &bank_balance);
	 }


	 return bank_balance;

 }

 //Gets the wager amount from the user and returns the value as the wager for the current roll.
 double get_wager_amount (void)
 {
	 double wager = 0.0;

	 printf("WAGER: $");
	 scanf("%lf", &wager);
	 fflush(stdin);

	 return wager;
 }

 //Checks that the input for the wager was a valid input and checks if the wager is within the amount of the total balance
 int check_wager_amount (double wager, double balance)
 {
	 int wager_within_bounds = 1;
	 double temp = 0.0;
	 temp = balance;

	 while(wager > temp || wager == 0 || wager < 0)
	 {
		 fflush(stdin);
		 if(wager > temp)
		 {
			printf("\nSorry, I don't take IOU's. Wager with what you've got bub. Try again.\nWAGER: $");
		 }
		 else if(wager == 0)
		 {
			printf("\nYou gotta pay to play kid. Try again.\nWAGER: $");
		 }
		 else
		 {
			 printf("\nWho taught you how to do math kid? Try again.\nWAGER: $");
		 }
		 scanf("%lf", &wager);
	 }

	 return wager_within_bounds;
 }

 //Rolls the dice and calculates a rand number between 1 and 6 and return the result as an integer.
 int roll_die()
 {
	 int die = 0;

	 die = (rand ()%6) + 1;
	 
	 return die;
 }

 //calculates the sum of the returned values from two calls to the roll_die() functions, returns the sum of the dice roll
 int calculate_sum_dice (int die1_value, int die2_value)
 {
	 int sum = 0;

	 sum = die1_value + die2_value;

	 return sum;
 }

 //Determines the status of the current game and returns a decision based on the result of the dice sum function
 int is_win_loss_or_point (int sum_dice)
 {
	 int decision = -1;

	 if(sum_dice == 7 || sum_dice == 11)
	 {
		 decision = 1;
		 return decision;
	 }
	 else if(sum_dice == 2 || sum_dice == 3 || sum_dice == 12)
	 {
		 decision = 0;
		 return decision;
	 }
	 else
	 {
		 return decision;
	 }
 }

 //if the previous play was not an instant win, after the point value is assigned, all succesive rolls are processed here
 //in order to determine if the point is equal to the roll or if the house wins with a 7.
 int is_point_loss_or_neither (int sum_dice, int point_value)
  {
	  int result = -1;

	  if(sum_dice == point_value)
	  {
		  return 1;
	  }
	  else if(sum_dice == 7)
	  {
		  return 0;
	  }
	  else
	  {
		  return result;
	  }
  }

 //Adjusts the bank balance depending on the result of the game and the current wager and bank balance
  double adjust_bank_balance (double bank_balance, double wager_amount, int add_or_subtract)
  {
	  double new_balance = 0.0;

	  if(add_or_subtract == 1)
	  {
		  new_balance = bank_balance + wager_amount;
	  }
	  else if(add_or_subtract == 0)
	  {
		  new_balance = bank_balance - wager_amount;
	  }

	  return new_balance;
  }

  //Returns the ration of wins/games after each round. 
  double ratio(int num_wins, int total)
  {
	  double ratio = 0.0;

	  ratio = ((double)num_wins/(double)total) * 100;

	  return ratio;
  }

  //I implemented this function into the program via other functions and counters/statistical information.
  void chatter_messages (int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance)
  {
	  
  }
