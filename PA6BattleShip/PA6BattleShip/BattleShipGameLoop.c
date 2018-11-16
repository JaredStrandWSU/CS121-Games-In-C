#include "Header.h"

//Plays a game of battleship
int play_battleship_game(void)
{
	int ship_input_choice = 0, vert_or_horiz = 0;
	int player_one_win_or_lose = 0, computer_win_or_lose = 0;
	int player_one_carrier_hits = 0, player_one_battleship_hits = 0, player_one_submarine_hits = 0, player_one_destroyer_hits = 0, player_one_patrol_boat_hits = 0;
	int player_two_carrier_hits = 0, player_two_battleship_hits = 0, player_two_submarine_hits = 0, player_two_destroyer_hits = 0, player_two_patrol_boat_hits = 0;
	int player_one_total_hits = 0, player_two_total_hits = 0, player_one_total_misses = 0, player_two_total_misses = 0, player_one_total_shots = 0, player_two_total_shots = 0;
	int random_row_start_point = 0, random_col_start_point = 0, i = 0, goes_first = 0;
	int *row_start_ptr = &random_row_start_point, *col_start_ptr = &random_col_start_point;
	unsigned int x = 0, y = 0;
	unsigned int row_guess = 0, col_guess = 0, p = 0;
	Hit_or_miss target = miss;
	char ship_hit = '\0';
	char computer_board[2][10][10] = {0};
	char player_board[10][10] = {0};
	
	FILE *outfile = NULL;

	//open the Stats.txt file for writing
	outfile = fopen("Stats.txt", "w");

	//Seed rand
	srand((unsigned int)time(NULL));

	//initialize the boards
	init_player_board(player_board, ROWS, COLS);
	init_computer_board(computer_board, ROWS, COLS);

	printf("Please select from the following menu:\n\n1. Enter positions of ships manually.\n\n2. Allow the program to randomly select positions of ships.\n");
	scanf("%d", &ship_input_choice);

	//User has selected to manually input ships
	if(ship_input_choice == 1)
	{
		manually_place_carrier_on_board(player_board);
		manually_place_battleship_on_board(player_board);
		manually_place_submarine_on_board(player_board);
		manually_place_destroyer_on_board(player_board);
		manually_place_patrolboat_on_board(player_board);
		printf("\nYour ships are locked and loaded!\n");
		printf("\nPress enter to generate enemy ships!\n");
		system("pause");
	}
	//User has selected to automatically assign ships to the board
	else
	{	
		//Generate computers board with ships
		vert_or_horiz = rand() % 2;
		automatically_place_carrier_on_board(player_board, vert_or_horiz);
	
		vert_or_horiz = rand() % 2;
		automatically_place_battleship_on_board(player_board, vert_or_horiz);

		vert_or_horiz = rand() % 2;
		automatically_place_submarine_on_board(player_board, vert_or_horiz);

		vert_or_horiz = rand() % 2;
		automatically_place_destroyer_on_board(player_board, vert_or_horiz);

		vert_or_horiz = rand() % 2;
		automatically_place_patrolboat_on_board(player_board, vert_or_horiz);
		
		printf("\nYour ships are locked and loaded!\n");
		printf("\nPress enter to generate enemy ships!\n");
		system("pause");

		fflush(stdin);
	}		
		//Generate computers board with ships
		vert_or_horiz = rand() % 2;
		automatically_place_carrier_on_comp_board(computer_board, vert_or_horiz);

		vert_or_horiz = rand() % 2;
		automatically_place_battleship_on_comp_board(computer_board, vert_or_horiz);

		vert_or_horiz = rand() % 2;
		automatically_place_submarine_on_comp_board(computer_board, vert_or_horiz);

		vert_or_horiz = rand() % 2;
		automatically_place_destroyer_on_comp_board(computer_board, vert_or_horiz);

		vert_or_horiz = rand() % 2;
		automatically_place_patrolboat_on_comp_board(computer_board, vert_or_horiz);

		printf("Computers Board Generating!!!");
		
		while(i < 9986)
		{
			p = rand() % 2;
			printf("%d ", p);
			i++;
		}
		printf("\n\n\n\n\t\tCOMPUTERS SHIPS ARE LOCKED AND LOADED!!!\n\n\n\n\n\n\n");
		system("pause");

		//select who will go first randomly
		goes_first = rand() % 2;
		
		printf("SELECTING WHO SHOOTS FIRST (definetly han)");
		
		i = 0;
		while(i < 9979)
		{
			printf(". ");
			i++;
		}
		
			if(goes_first == 1)
			{
				printf("\n\n\n\n\t\tPLAYER ONE HAS WON THE TOSS!!!\n\n\n\n\n\n\n");
				system("pause");
				system("cls");
		    }
			else
			{
				printf("\n\n\n\n\t\tTHE COMPUTER HAS WON THE TOSS!!!\n\n\n\n\n\n\n");
				system("pause");
				system("cls");
			}

			
		//sentinel loop that alternates between 1 and 0 and returns 3 when hit count is the total value of ships
		while (goes_first != 3)
		{
			if(goes_first == 1)
			{
				printf("\t   ~~~Computer~~~\n\n");
				print_computer_board_no_ships(computer_board, ROWS, COLS);
				printf("\n\n");
				printf("\t   ~~~Player 1~~~\n\n");
				print_player_board(player_board);

				printf("*Player 1 select your target coordinates*\n");
				do
				{
					printf("ROW: ");
					scanf("%d", &row_guess);
					printf("COL: ");
					scanf("%d", &col_guess);
				}while(row_guess > 9 || row_guess < 0 || col_guess > 9 ||col_guess < 0 || computer_board[1][row_guess][col_guess] == 'M' ||  computer_board[1][row_guess][col_guess] == '*');


				//reset which ship has been hit last turn
				ship_hit = '\0';

				//determine if player ones coordinates are a hit or a miss on the computer board and return the result and ship hit
				target = player_one_is_hit_or_miss(row_guess, col_guess, computer_board, &ship_hit);

				//based on if hit or miss reveal a ship or display a miss symbol and add to the ship hit counters
				if(target == hit)
				{
					//Saves room in main game loop
					player_one_hit( &row_guess,					 &col_guess,
									&player_one_total_hits,      &player_one_total_misses,	
									&player_one_total_shots,     &player_one_carrier_hits,	
									&player_one_battleship_hits, &player_one_submarine_hits,  
									&player_one_destroyer_hits,  &player_one_patrol_boat_hits, 
									computer_board, outfile,    &ship_hit);
					
				}
				else
				{
					fprintf(outfile, "Player One : MISS : ROW %d : COL %d\n", row_guess, col_guess);
					fflush(outfile);
					computer_board[1][row_guess][col_guess] = 'M';
					player_one_total_misses += 1;
					player_one_total_shots += 1;
				}

				system("pause");

				//switch to player two
				goes_first = 0;

				if(player_one_total_hits == MAX_HITS)
				{
					player_one_win_or_lose = 1;
					goes_first = 3;
					printf("\n\n\n\n\nPLAYER ONE IS THE WINNER!!!\n\n\n\n\n");
					system("pause");
				}
			}
			else if (goes_first == 0)
			{
				//COMPUTER PLAYER MAKES A MOVE

				printf("\t   ~~~Computer~~~\n\n");
				print_computer_board_no_ships(computer_board, ROWS, COLS);
				printf("\n\n");
				printf("\t   ~~~Player 1~~~\n\n");
				print_player_board(player_board);

				printf("*Computer Player select your target coordinates*\n");

				//resets the computers random shot to 0, 0
				x = 0;
				y = 0;

				do
				{
					generate_computer_shot(&x, &y);

				}while(player_board[x][y] == 'M' ||  player_board[x][y] == '*');

				//reset which ship has been hit last turn
				ship_hit = '\0';

				//determine if computers coordinates are a hit or a miss on the player board and return the result and ship hit
				target = computer_is_hit_or_miss(x, y, player_board, &ship_hit);

				//based on if hit or miss reveal a ship or display a miss symbol and add to the ship hit counters
				if(target == hit)
				{
					//Saves room in main game loop
				   computer_hit(&x,						    &y,						
								&player_two_total_hits,     &player_two_total_misses,	
								&player_two_total_shots,    &player_two_carrier_hits,	
								&player_two_battleship_hits,&player_two_submarine_hits, 
								&player_two_destroyer_hits, &player_two_patrol_boat_hits, 
								player_board, outfile, &ship_hit);
					
				}
				else
				{
					fprintf(outfile, "Computer: MISS : ROW %d : COL %d\n", x, y);
					fflush(outfile);
					player_board[x][y] = 'M';
					player_two_total_misses += 1;
					player_two_total_shots += 1;
				}

				system("pause");

				//switch to player one
				goes_first = 1;
				
				if(player_two_total_hits == MAX_HITS)
				{
					computer_win_or_lose = 1;
					goes_first = 3;
					printf("\n\n\n\n\nCOMPUTER IS THE WINNER!!!\n\n\n\n\n");
					system("pause");
				}
			}
		}

		//Print the final results to the file including
		//total number of hits, total number of misses, total number of shots, hits to misses ratio (as a percentage), and won or lost the game
		
		//Player one stats print out
		fprintf(outfile, "PLAYER ONE STATS:\nTOTAL SHOTS: %d\nTOTAL HITS: %d\nTOTAL MISSES: %d\nHIT/MISS RATIO: %d\n", player_one_total_hits, player_one_total_hits, player_one_total_misses, (player_one_total_hits/player_one_total_misses));
		if(player_one_win_or_lose == 1)
		{
			fprintf(outfile, "WIN\n");
		}
		else
		{
			fprintf(outfile, "LOSE\n");
		}

		//Computer stats print out
		fprintf(outfile, "\nCOMPUTER STATS:\nTOTAL SHOTS: %d\nTOTAL HITS: %d\nTOTAL MISSES: %d\nHIT/MISS RATIO: %%d\n", player_two_total_hits, player_two_total_hits, player_two_total_misses, (player_two_total_hits/player_two_total_misses));
		if(computer_win_or_lose == 1)
		{
			fprintf(outfile, "WIN\n");
		}
		else
		{
			fprintf(outfile, "LOSE\n");
		}


		//Close the stats file
		fflush (outfile);
		fclose(outfile);

		//return to the main menu
		printf("\n\nRETURNING TO THE MAIN MENU!\n");
		system("pause");
		system("cls");

	return 0;
}
