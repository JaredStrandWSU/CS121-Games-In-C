#include "Header.h"

//Asks the user for what they would like to do and only accepts 1 2 or 3
int menu()
{
	int choice = 0;

	while(choice != 1 && choice != 2 && choice != 3)
	{
		printf("Main Menu:\n\n\t");
		printf("1. Print game rules\n\t2. Start a game of Yahtzee\n\t3. Exit\n>>>");
		scanf("%d", &choice);
	}
	return choice;
}

//Prints the rules for Yahtzee
void print_rules(void)
{
	printf("\nThe Rules of Yahtzee:\n\n");
	printf("The scorecard used for Yahtzee is composed of two sections. A upper section and a lower section. A total of thirteen boxes or thirteen scoring combinations are divided amongst the sections. The upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box. If a player rolls four 3's, then the score placed in the 3's box is the sum of the dice which is 12. Once a player has chosen to score a box, it may not be changed and the combination is no longer in play for future rounds. If the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are added to the players overall score as a bonus. The lower section contains a number of poker like combinations. See the table provided below:\n\n\t");
	printf("NAME\t\tCOMBINATION\t\tSCORE\n\t");
	printf("3-of-a-kind\tThree dice, same face\tSum of 5 dice\n\t");
	printf("4-of-a-kind\tFour dice, same face\tSum of 5 dice\n\t");
	printf("Full house\tPair + 3-of-a-kind\t25\n\t");
	printf("Small straight\tA sequence of four dice\t30\n\t");
	printf("Large straight\tA sequence of five dice\t40\n\t");
	printf("Yahtzee\t\tFive dice, same face\t50\n\t");
	printf("Chance\t\tAny sequence/catch all\tSum of 5 dice\n\n");
	return;
}

//Plays the entire game and then returns to the main menu
int play_Yahtzee_Game()
{
	//MAIN GAME FUNCTION
	int round = 1; //Establishes that this is the first round
	int dice[5] = {0}; //array to hold the dice roll //array to hold the number of values of the specified dice.
	int combinations_scores_player_1[13] = {0}; //Holds the players score when that combination is used.
	int combinations_used_player_1[13] = {0}; //parralel array used to store whether the combination has been used.
	int combinations_scores_player_2[13] = {0}; //Holds the players score when that combination is used.
	int combinations_used_player_2[13] = {0}; //parralel array used to store whether the combination has been used.
	int reroll_array[5] = {0}; //parralel array to store which dice should be rerolled
	int num_values_p1[6] = {0}; //array that holds the number of a certain dice from the roll for player 1
	int num_values_p2[6] = {0}; //array that holds the number of a certain dice from the roll for player 2
	int roll = 0; //keeps track of the current roll
	int reroll_choice = 1; //Determines whether the user would like to reroll the dice
	int combo_choice = 0; //Determines which combonition the user would like to use for the specified round
	int index1 = 0, index2 = 0, index3 = 0, index4 = 0; //Keeps track of loops
	int p1_sum = 0; //Running total for player 1
	int p2_sum = 0; //Running total for player 2
	int *p1_sum_ptr = NULL; //Pointer to access the value scored
	int *p2_sum_ptr = NULL; //Pointer to access the value scored
	p1_sum_ptr = &p1_sum; // assigns the pointer to the correct variable
	p2_sum_ptr = &p2_sum; // assigns the pointer to the ccorrect variable
	
	//Needed for randomization of dice rolls
	srand ((unsigned int) time (NULL));

	//Plays the game for a set number of rounds
	while(round < 14)
	{
		//Player1 // Resets the roll roll choice combo choice and indexes for the game
		roll = 0;
		reroll_choice = 1;
		combo_choice = 0;
		index1 = 0, index2 = 0, index3 = 0, index4 = 0;

		//Prints a prompt for the user
		printf("\nThis is round number %d.\n\n", round);
		printf("PLAYER ONE\n");
		printf("Press any key to roll the dice.\n");
		system("pause");
		printf("\n");

		//Roll the dice for the player for the first time
		roll_dice (dice, NUM_ITEMS);
		roll++;

		//Display the values of the dice rolled
		display_dice (dice, NUM_ITEMS);

		//ask user if they want to reroll any dice 
		printf("Would you like to reroll any of the dice?(Enter 1 for yes and 0 for no)\n");
		scanf("%d", &reroll_choice);

		//Determines if the user would like to reroll and rerolls specific dice
		if(reroll_choice == 1)
		{
			printf("Please enter 1 for yes and 0 for no for each choice.\n");
			for(index1 = 0; index1 < 5; index1++)
			{
				printf("Would you like to reroll dice #%d? ", index1+1);
				scanf("%d", &reroll_array[index1]);
			}

			for (index2 = 0; index2 < 5; index2++)
			{
				if(reroll_array[index2] == 1)
				{
					dice[index2] = rand () % 6 + 1;
				}
			}

			//Displays the dice
			display_dice (dice, NUM_ITEMS);

			//ask user if they want to reroll any dice 
			printf("\nWould you like to reroll any of the dice?(Enter 1 for yes and 0 for no)\n");
			scanf("%d", &reroll_choice);

			//Determines if the user would like to reroll the dice again
			if(reroll_choice == 1)
			{
				printf("Please enter 1 for yes and 0 for no for each choice.\n");
				for(index1 = 0; index1 < 5; index1++)
				{
					printf("Would you like to reroll dice #%d? ", index1+1);
					scanf("%d", &reroll_array[index1]);
				}

				for (index2 = 0; index2 < 5; index2++)
				{
					if(reroll_array[index2] == 1)
					{
						dice[index2] = rand () % 6 + 1;
					}
				}

				//displays the dice
				display_dice (dice, NUM_ITEMS);

			}
			//Determines how many of each dice value was rolled and stores the corresponding values in the correct positions
			populate_num_dice(dice, num_values_p1); //store the values of the dice in the dice calues array
		}

		//Display and get a game combination from the user.
		select_combination_player_1(dice, num_values_p1, combinations_scores_player_1, combinations_used_player_1, p1_sum_ptr);
		
		//resets the values contained in the num_values_p1 array so that the user can re enter new values next time
		num_values_p1[0] = 0;
		num_values_p1[1] = 0;
		num_values_p1[2] = 0;
		num_values_p1[3] = 0;
		num_values_p1[4] = 0;
		num_values_p1[5] = 0;


		//Player 2 //Resets the values for player two to use
		roll = 0;
		reroll_choice = 1;
		combo_choice = 0;
		index1 = 0, index2 = 0;

		//Prompts the user of the round and to roll the dice
		printf("\nPLAYER TWO\n", round);
		printf("Press any key to roll the dice.\n");
		system("pause");
		printf("\n");

		//Roll the dice for the player for the first time
		roll_dice (dice, NUM_ITEMS);
		roll++;

		//Display the values of the dice rolled
		display_dice (dice, NUM_ITEMS);

		//ask user if they want to reroll any dice 
		printf("Would you like to reroll any of the dice?(Enter 1 for yes and 0 for no)\n");
		scanf("%d", &reroll_choice);

		//If reroll is selected the user is prompted for which dice they would like to reroll
		if(reroll_choice == 1)
		{
			printf("Please enter 1 for yes and 0 for no for each choice.\n");
			for(index1 = 0; index1 < 5; index1++)
			{
				printf("Would you like to reroll dice #%d? ", index1+1);
				scanf("%d", &reroll_array[index1]);
			}

			for (index2 = 0; index2 < 5; index2++)
			{
				if(reroll_array[index2] == 1)
				{
					dice[index2] = rand () % 6 + 1;
				}
			}

			//Displays the dice
			display_dice (dice, NUM_ITEMS);

			//ask user if they want to reroll any dice 
			printf("\nWould you like to reroll any of the dice?(Enter 1 for yes and 0 for no)\n");
			scanf("%d", &reroll_choice);

			//Asks the user if they want to reroll the dice again
			if(reroll_choice == 1)
			{
				printf("Please enter 1 for yes and 0 for no for each choice.\n");
				for(index1 = 0; index1 < 5; index1++)
				{
					printf("Would you like to reroll dice #%d? ", index1+1);
					scanf("%d", &reroll_array[index1]);
				}

				for (index2 = 0; index2 < 5; index2++)
				{
					if(reroll_array[index2] == 1)
					{
						dice[index2] = rand () % 6 + 1;
					}
				}

				//Displays the dice
				display_dice (dice, NUM_ITEMS);

			}
			//Stores the number of a specific dice from the roll into an array to be used to determine scoring choice
			populate_num_dice(dice, num_values_p2); //store the values of the dice in the dice calues array
		}

		//Display and get a game combination from the user.
		select_combination_player_2(dice, num_values_p2, combinations_scores_player_2, combinations_used_player_2, p2_sum_ptr);
		
		//Resets the values in num_values_p2 to be entered in again later
		num_values_p2[0] = 0;
		num_values_p2[1] = 0;
		num_values_p2[2] = 0;
		num_values_p2[3] = 0;
		num_values_p2[4] = 0;
		num_values_p2[5] = 0;
	
	//Prints that the round has ended and the next round is to follow, also adds one to the counters that determine
	//if the game has gone through all required rounds and ends the game after 13 rounds.
	printf("THIS IS THE END OF ROUND %d.", round);
	if(round < 14)
	{
		printf("THIS IS THE END OF ROUND %d.", round);
	}
	if(round < 13)
	{
		round++;
	}
	else //if game has no more rounds prints out the players scores and exits the game 
	{
		for(index3 = 0; index3 < 14; index3++)
		{
			system("cls");
			printf("\n\nFinal scores:\nPLAYER 1: %d\nPLAYER 2: %d\n", p1_sum, p2_sum);
			printf("\nTHANK YOU FOR PLAYING YAHTZEE!!!\n\n");
		}
		system("pause");
		return 0;
	}
  }
}

//Rolls the dice and stores the value in dice[5]
void roll_dice (int dice[5], int num_items)
{
	int index = 0;

	for (index = 0; index < num_items; ++index)
	{
		dice[index] = rand () % 6 + 1;
	}
}

//Displays the dice
void display_dice (int dice[5], int num_items)
{
	int index = 0;
	printf("\n");
	while (index < num_items)
	{
		printf ("Dice# %d rolled a -->  %d  <--\n",index+1, dice[index]);

		index++;
	}
}

//Rerolls specific dice chosen by the player
void reroll_dice (int dice[5], int num_items)
{
	int num_reroll = 0, position = 0, count = 0;

	while(num_reroll < 0 || num_reroll > 5)
	{	
		printf ("How many dice would you like to reroll? ");
		scanf ("%d", &num_reroll);
	}

	for (count = 0; count < num_reroll; count++)
	{
		printf ("Which die would you like to reroll (position number): ");
		scanf ("%d", &position);
		dice[position - 1] = rand () % 6 + 1; // opportunity call roll_die () function
	}
}

//Selects the combinations to be used and added to the players score for player 1
void select_combination_player_1 (int dice[5], int num_values_p1[6], int scores_p1[13], int comb_used_p1[13], int *p1_sum_ptr)
{
	//Variables needed to operate choices need to be reset upon each call
	int option = 0, check_flag = 0, index = 0, temp = 1, temp2 = 1, index2 = 0;

	//prints out the possible combinations for the user to select from and checks that the selected combination has not 
	//already been selected. If already selected then repeats the question to select a different option
	do
	{
		//prints out the list of options and takes in the option selected
		check_flag = 0;
		printf("\t\t1. Sum of 1's\t7. Three-of-a-kind\n\t\t2. Sum of 2's\t8. Four-of-a-kind\n\t\t3. Sum of 3's\t9. Full house\n\t\t4. Sum of 4's\t10. Small straight\n\t\t5. Sum of 5's\t11. Large straight\n\t\t6. Sum of 6's\t12. Yahtzee\n\t\t13. Chance\n\n");
		printf ("Enter the combination you would like to use: \n");
		scanf ("%d", &option); // option 1 - 13

		//checks if the combination has been selected previously
		if (comb_used_p1[option - 1] == 1)
		{
			// combination has been used before
			check_flag = 1;
			printf("Sorry that option has already been chosen so please enter an unused value.\n");
			scanf ("%d", &option); // option 1 - 13
		}
	} while (check_flag); //check flag will continue to flag until changed when valid option is not selected

	// selected a valid combination to use
	comb_used_p1[option - 1] = 1; // now combination has been used
	populate_num_dice (dice, num_values_p1);

	//if a valid option has been selected the correct choice will be added to the players score
	switch (option)
	{
	case 1: scores_p1[0] = num_values_p1[0]; // contains the number of one's
		*p1_sum_ptr += scores_p1[0];
		printf("You have chosen sum of 1's, this has been added to your score.\n");
		break;
	case 2: scores_p1[1] = num_values_p1[1]*2; // contains the number of two's
			*p1_sum_ptr += scores_p1[1];
		printf("You have chosen sum of 2's, this has been added to your score.\n");
		break;
	case 3: scores_p1[2] = num_values_p1[2]*3; //contains the number of three's
		*p1_sum_ptr += scores_p1[2];
		printf("You have chosen sum of 3's, this has been added to your score.\n");
		break;
	case 4: scores_p1[3] = num_values_p1[3]*4; //contains the number of four's
		*p1_sum_ptr += scores_p1[3];
		printf("You have chosen sum of 4's, this has been added to your score.\n");
		break;
	case 5: scores_p1[4] = num_values_p1[4]*5; //contains the number of five's
		*p1_sum_ptr += scores_p1[4];
		printf("You have chosen sum of 5's, this has been added to your score.\n");
		break;
	case 6: scores_p1[5] = num_values_p1[5]*6; //contains the number of sixes
		*p1_sum_ptr += scores_p1[5];
		printf("You have chosen sum of 6's, this has been added to your score.\n");
		break;
	case 7: //calculates score of 3 of a kind
			while(temp)
			{
				if(num_values_p1[index] == 3)
				{
					scores_p1[6] = (index+1)*3;
					*p1_sum_ptr += scores_p1[6];
					temp = 0;
				}
				index++;
			}
			printf("You have chosen 3 of a kind, the sum of the three dice of a kind has been added to your score.");
		break;
	case 8: //calculates the score of 4 of a kind
			while(temp2)
			{
				if(num_values_p1[index2] == 4)
				{
					scores_p1[7] = (index2+1)*4;
					*p1_sum_ptr += scores_p1[7];
					temp2 = 0;
				}
				index2++;
			}
			printf("You have chosen 4 of a kind, the sum of the four dice of a kind has been added to your score.");
		break;
	case 9: scores_p1[8] = 25; //adds score for a full house
		*p1_sum_ptr += 25;
		printf("You have chosen full house, 25 points have been added to your score.");
		break;
	case 10: scores_p1[9] = 30; //adds score for a small straight
		*p1_sum_ptr += 30;
		printf("You have chosen small straight, 30 points have been added to your score.");
		break;
	case 11: scores_p1[10] = 40; //adds score for a large straight
		*p1_sum_ptr += 40;
		printf("You have chosen large straight, 40 points have been added to your score.");
		break;
	case 12: scores_p1[11] = 50; //adds score for yahtzee
		*p1_sum_ptr += 50;
		printf("You have chosen Yahtzee, 50 points have been added to your score.");
		break;
	case 13: scores_p1[12] = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
		*p1_sum_ptr += scores_p1[12]; //adds score for a chance
		printf("You have chosen chance, the sum of the dice values have been added to your score.");
		break;
	}

	//pauses and then clears screen
	system ("pause");
	system ("cls"); // clear screen
}

//*************PERFORMS SAME OPERATIONS AS SELECT_COMBINATION_PLAYER_1 EXCEPT FOR PLAYER 2 THIS TIME****************************
void select_combination_player_2 (int dice[5], int num_values_p2[6], int scores_p2[13], int comb_used_p2[13], int *p2_sum_ptr)
{
	int option = 0, check_flag = 0, index = 0, temp = 1, temp2 = 1, index2 = 0;

	do
	{
		check_flag = 0;
		printf("\t\t1. Sum of 1's\t7. Three-of-a-kind\n\t\t2. Sum of 2's\t8. Four-of-a-kind\n\t\t3. Sum of 3's\t9. Full house\n\t\t4. Sum of 4's\t10. Small straight\n\t\t5. Sum of 5's\t11. Large straight\n\t\t6. Sum of 6's\t12. Yahtzee\n\t\t13. Chance\n\n");
		printf ("Enter the combination you would like to use: \n");
		scanf ("%d", &option); // option 1 - 13

		if (comb_used_p2[option - 1] == 1)
		{
			// combination has been used before
			check_flag = 1;
			printf("Sorry that option has already been chosen so please enter an unused value.\n");
			scanf ("%d", &option); // option 1 - 13
		}
	} while (check_flag);

	// selected a valid combination to use
	comb_used_p2[option - 1] = 1; // now combination has been used
	populate_num_dice (dice, num_values_p2);

	//if (option == 1)
	switch (option)
	{
	case 1: scores_p2[0] = num_values_p2[0]; // contains the number of one's
			*p2_sum_ptr += scores_p2[0];
		printf("You have chosen sum of 1's, this has been added to your score.\n");
		break;
	case 2: scores_p2[1] = num_values_p2[1]*2; // contains the number of two's
			*p2_sum_ptr += scores_p2[1];
		printf("You have chosen sum of 2's, this has been added to your score.\n");
		break;
	case 3: scores_p2[2] = num_values_p2[2]*3; //contains the number of three's
		*p2_sum_ptr += scores_p2[2];
		printf("You have chosen sum of 3's, this has been added to your score.\n");
		break;
	case 4: scores_p2[3] = num_values_p2[3]*4;
		*p2_sum_ptr += scores_p2[3];
		printf("You have chosen sum of 4's, this has been added to your score.\n");
		break;
	case 5: scores_p2[4] = num_values_p2[4]*5;
		*p2_sum_ptr += scores_p2[4];
		printf("You have chosen sum of 5's, this has been added to your score.\n");
		break;
	case 6: scores_p2[5] = num_values_p2[5]*6;
		*p2_sum_ptr += scores_p2[5];
		printf("You have chosen sum of 6's, this has been added to your score.\n");
		break;
	case 7:
			while(temp)
			{
				if(num_values_p2[index] == 3)
				{
					scores_p2[6] = (index+1)*3;
					*p2_sum_ptr += scores_p2[6];
					temp = 0;
				}
				index++;
			}
			printf("You have chosen 3 of a kind, the sum of the three dice of a kind has been added to your score.");
		break;
	case 8:
			while(temp2)
			{
				if(num_values_p2[index2] == 4)
				{
					scores_p2[7] = (index2+1)*4;
					*p2_sum_ptr += scores_p2[7];
					temp2 = 0;
				}
				index2++;
			}
			printf("You have chosen 4 of a kind, the sum of the four dice of a kind has been added to your score.");
		break;
	case 9: scores_p2[8] = 25;
		*p2_sum_ptr += 25;
		printf("You have chosen full house, 25 points have been added to your score.");
		break;
	case 10: scores_p2[9] = 30;
		*p2_sum_ptr += 30;
		printf("You have chosen small straight, 30 points have been added to your score.");
		break;
	case 11: scores_p2[10] = 40;
		*p2_sum_ptr += 40;
		printf("You have chosen large straight, 40 points have been added to your score.");
		break;
	case 12: scores_p2[11] = 50;
		*p2_sum_ptr += 50;
		printf("You have chosen Yahtzee, 50 points have been added to your score.");
		break;
	case 13: scores_p2[12] = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
		*p2_sum_ptr += scores_p2[12];
		printf("You have chosen chance, the sum of the dice values have been added to your score.");
		break;
	}

	system ("pause");
	system ("cls"); // clear screen
}

//Calculates the number of dice values in the roll
void populate_num_dice (int dice[5], int num_values[6])
{
	int index = 0;

	for (index = 0; index < 5; index++)
	{
		num_values[dice[index] - 1]++;
	}
}
