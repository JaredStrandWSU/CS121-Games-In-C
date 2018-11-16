#include "Header.h"

//Runs the entire program until the end mark is reach which returns the program  back to main
int runGame()
{
	//All the variales 
	double bank_balance = 0.0, wager = 0.0, winnings = 0.0, initial_bank_balance = 0.0, current_bank_balance = 0;
	char choice = '/0', replay = 'y';
	int wager_in_bounds = 0, dice1 = 0, dice2 = 0, dice_sum = 0, point = 0, result = -1, number_rolls = 0, num_wins = 0,
		num_loss = 0, first_roll = 0, total_rounds = 0;

	//Needed for Random function
	srand(/*(unsigned int)*/ time(NULL));

	//Introduce the game
	print_game_rules();
	
	//Get/Set the current bank balance using the get_bank_balance function
	 bank_balance = get_bank_balance ();
	 initial_bank_balance = bank_balance;

//Main Game loop that checks the players balance and the response to play again
while(bank_balance != 0.00 && replay == 'y')
{
	//Resets game factors before each new round
	 point = 0;
	 result = -1;
	 number_rolls = 0;
	 wager = 0.00;

	 //prints out the players current stats if they still have money
	 printf("\n");
	 printf("GAME STATS: \n");
	 printf("Current Bank Balance: $%.2lf\n\n", bank_balance);

	 //Get the amount to wager on a particular roll
	  wager = get_wager_amount ();

	 //Checks that the wager is within the players balance
	 wager_in_bounds = check_wager_amount (wager, bank_balance);

	 //Plays the game/ Rolls the dice
	  dice1 = roll_die ();
	  dice2 = roll_die ();

	  //Prints out the results
	  printf("\n\nYou rolled a %d and a %d!\n\n\n", dice1, dice2);

	  //Calculates dice sum
	  dice_sum = calculate_sum_dice(dice1, dice2);

	  //assigns the value of the first roll to be tested in order to decide to continue with the program and detect if a win or loss
	  first_roll = is_win_loss_or_point (dice_sum);
	
	  //If first roll result is 1 then the program will excecute winning processes and jump out of the if statement
	  if(first_roll == 1)
	  {
		  printf("Congratulations you have won!\n");
		  bank_balance = adjust_bank_balance(bank_balance, wager, 1);
		  printf("Your new bank balance is: $%.2lf\n\n", bank_balance);
		  number_rolls++;
		  num_wins++;
	  }
	  //If the first roll result is 0 that mean the player got craps on the first roll and the game will procede with losing processes
	  else if(first_roll == 0)
	  {
		  printf("CRAPS, you are a loser!\n\n");
		  bank_balance = adjust_bank_balance(bank_balance, wager, 0);
		  printf("Your new bank balance is: $%.2lf\n\n", bank_balance);
		  number_rolls++;
		  num_loss++;
	  }
	  //If craps or a win was not determined based on the first roll the player now must roll again,
	  //the value of the first roll is assigned to a point and while the result of the function
	  //is_point_loss_or_neither is -1 the program will continue rolling until either the point is 
	  //met or a 7 is detected. 
	  else
	  {
		  point = dice_sum;
		  printf("Your point is %d", point);

		  while(result == -1)
		  {
			dice1 = roll_die ();
			dice2 = roll_die ();
			number_rolls++;
			dice_sum = calculate_sum_dice(dice1, dice2);
			printf("\n\nYou rolled a %d and a %d for a sum of %d on roll number %d!\n\n", dice1, dice2, dice_sum,number_rolls +1);
			result = is_point_loss_or_neither(dice_sum, point);
		  }
		  //Once a 1 or 0 is returned from the is_point_loss_or_neither function, this if else statement will
		  //proceed with winning or losing procedures and apply statistics accordingly.
		  if(result == 1)
		  {
			  printf("Congratulations you hit your point and won!\n\n");
			  bank_balance = adjust_bank_balance(bank_balance, wager, 1);
			  printf("Your new bank balance is: $%.2lf\n\n", bank_balance);
			  num_wins++;
		  }
		  else if(result == 0)
		  {
			  printf("\nHouse wins, you are a loser!\n\n");
			  bank_balance = adjust_bank_balance(bank_balance, wager, 0);
			  printf("Your new bank balance is: $%.2lf\n\n", bank_balance);
			  num_loss++;
		  }

	  }
	  //This block of code excecutes after every round and displays the players current statistical information
	  printf("***GAME STATS***\n");
	  printf("Games won: %d\n", num_wins);
	  printf("Games lost: %d\n", num_loss);
	  total_rounds = num_loss + num_wins;
	  printf("Percent won: %%%.2lf", ratio(num_wins, total_rounds));
	
	  //if the players balance is detected to be 0, the program will end and continue with end game message,
	  //otherwise the player will be asked if he or she would like to play another round. This process will
	  //repeat until the game loop conditions are no longer met or the user enters an 'n' to end the loop. 
	  if(bank_balance == 0.00)
	  {
		  	printf("\n\nTHANKS FOR PLAYING!!!\n\n");
			return 0;
	  }
	  else
	  {
		    printf("\n\nWould you like to play again?\nEnter 'y' for yes and 'n' for no.\n>>>");
			fflush(stdin);
			scanf(" %c", &replay);
	  }

	
}
//Returns to the Main() function.
return 0;
}
