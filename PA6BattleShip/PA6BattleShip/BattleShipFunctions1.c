#include "Header.h"

//MAIN GAME FUNCTIONS INCLUDING MENU AND RUNGAME
int run_battleship(void)
{
	int game_path = 0;
	//**************
	//splash screen intro
	splash_screen();
	//********
	while(1)
	{
	//display menu options and run the course according to the option
	game_path = menu();

	//Clear Screen
	system("cls");

	//Switch stament that controlls the path of the game
	switch(game_path){
    case 1 : /*Print Rules*/
		{
			print_rules();
			system("pause");
			system("cls");
			break;
		}
    case 2 : /*Main Game loop*/
		{
			play_battleship_game();
			printf("\n\nReturning to the main menu.\n\n");
			break; /* optional */
		}
	case 3 : /*Exits Yahtzee*/
		{
			printf("\n\nThanks for playing Battleship!\n\n");
			return 0;
		}
	   }
	}
}

void splash_screen()
{
	int i = 0;
	
	while(i < 35)
	{
		system("mode 400");
		system("color 1a");
		printf("\n\n\n\n\n\t\t\t\t    W E L C O M E \n\n\n\n\n\n");
		system("color 04");
		printf("\n\n\n\t\t\t\t    T O  \n\n\n\n\n\n");
		printf("\n\n\n\t\t\t\t    B A T T L E S H I P \n\n\n\n");
		i++;
	}
	printf("Please enter fullscreen mode.\n");
	/*{
	system("mode 400");
	system("color 1a");
	printf("\n\n\n\n\n\t\t\t\t    H I T \n\n\n\n\n\n");
	system("color 04");
	printf("\n\n\n\t\t\t\t    H I T \n\n\n\n\n\n");
	printf("\n\n\n\t\t\t\t    H I T \n\n\n\n");
	i++;
	}*/
	system("pause");
	system("cls");
	system("color 1a");
}

int menu()
{
	int choice = 0;

	while(choice != 1 && choice != 2 && choice != 3)
	{
		printf("Main Menu:\n\n\t");
		printf("1. Print game rules\n\t2. Start a game of BattleShip\n\t3. Exit\n>>>");
		scanf("%d", &choice);
	}
	return choice;
}

void print_rules()
{
	printf("\n\n\n\t\t\1The Game is BATTLESHIP!!!\1\n\n");
	printf("\t\t1. Select who will go first.\n\n");
	printf("\t\t2. Place your pieces on the board.\n\n");
	printf("\t\t3. Select a position to attack.\n\n");
	printf("\t\t4. The first person to sink all ships wins.\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void init_player_board (char board[][10], int rows, int cols)
{
	int row_index = 0, col_index = 0;

	//rows
	for (row_index = 0; row_index < rows; row_index++)
	{
		//columns
		for (col_index = 0; col_index < cols; col_index++)
		{
			board[row_index][col_index] = '~';
		}

	}

}

void init_computer_board (char computer_board[][10][10], int rows, int cols)
{
	int row_index = 0, col_index = 0;

	//rows
	for (row_index = 0; row_index < rows; row_index++)
	{
		//columns
		for (col_index = 0; col_index < cols; col_index++)
		{
			computer_board[0][row_index][col_index] = '~';
			computer_board[1][row_index][col_index] = '~';
		}

	}

}

void print_computer_board (char board[][10][10], int rows, int cols)
{
	int row_index = 0, col_index = 0;

	//rows
	for (row_index = 0; row_index < rows; row_index++)
	{
		//columns
		for (col_index = 0; col_index < cols; col_index++)
		{
			printf(" %c ", board[0][row_index][col_index]);
		}
		putchar('\n');
	}

}

void print_computer_board_no_ships (char board[1][10][10], int rows, int cols)
{
	int index = 0, index2 = 0;

	printf("     0  1  2  3  4  5  6  7  8  9  \n   _______________________________");

	for(index = 0; index < 10; index++)
	{
		printf("\n   |\n %d |", index);
		for(index2 = 0; index2 < 10; index2++)
		{
			printf(" %c ", board[1][index][index2]);
		}
	
		printf("|");
	}
	printf("\n");
	return;
}

void gen_start_point(int length_of_ship, int direction, int *row_start_ptr, int *col_start_ptr)
{
	if (direction == 0) // VERTICAL
	{
		*col_start_ptr = rand () % 10;
		*row_start_ptr = rand () % (10 - length_of_ship + 1);//down from the start point
	}
	else                //HORIZONTAL
	{
		*col_start_ptr = rand () % (10 - length_of_ship + 1);
		*row_start_ptr = rand () % 10;
	}
}

void generate_computer_shot(unsigned int *x, unsigned int *y)
{
	*x = rand() % 10;
	*y = rand() % 10;

	return;
}

void print_player_board(char player_board[][10])
{
	int index = 0, index2 = 0;

	printf("     0  1  2  3  4  5  6  7  8  9  \n   _______________________________");

	for(index = 0; index < 10; index++)
	{
		printf("\n   |\n %d |", index);
		for(index2 = 0; index2 < 10; index2++)
		{
			printf(" %c ", player_board[index][index2]);
		}
	
		printf("|");
	}
	printf("\n");
	return;
}

void manually_place_carrier_on_board(char player_board[][10])
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	char orientation = '\0';

	print_player_board(player_board);

		printf("Would you like to place the CARRIER going down or right?\n('d' for down, 'r' for right)\n");
		scanf(" %c", &orientation);

		//check if overlapping occurs or off the board.
		if(orientation == 'r')
		{
			do
			{
				do
				{
					printf("Please enter the row and column of the starting point for the CARRIER.\n(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}while (start_row < 0 || start_col < 0 || start_row > 9 || start_col > 9);

				while(player_board[start_row][start_col] != '~')
				{
					printf("Please enter an address that has not been used.(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}

				while(player_board[start_row][start_col] == '~' && counter < 5)
				{
					start_col++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 5)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
			start_col -= 5;

			for(index2 = 0; index2 < 5; index2++)
			{
				player_board[start_row][start_col] = 'C';
				start_col++;
			}
			
			print_player_board(player_board);
			system("pause");
		}
		else
		{
			do
			{
				do
				{
					printf("Please enter the row and column of the starting point for the CARRIER.\n(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}while (start_row < 0 || start_col < 0 || start_row > 9 || start_col > 9);

				while(player_board[start_row][start_col] != '~')
				{
					printf("Please enter an address that has not been used.(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}

				while(player_board[start_row][start_col] == '~' && counter < 5)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 5)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
			start_row -= 5;

			for(index2 = 0; index2 < 5; index2++)
			{
				player_board[start_row][start_col] = 'C';
				start_row++;
			}
			
			print_player_board(player_board);
			system("pause");
		}

		print_player_board(player_board);
}
void manually_place_battleship_on_board(char player_board[][10])
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	char orientation = '\0';

		printf("Would you like to place the BATTLESHIP going down or right?\n('d' for down, 'r' for right)\n");
		scanf(" %c", &orientation);

		//check if overlapping occurs or off the board.
		if(orientation == 'r')
		{
			do
			{
				do
				{
					printf("Please enter the row and column of the starting point for the BATTLESHIP.\n(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}while (start_row < 0 || start_col < 0 || start_row > 9 || start_col > 9);

				while(player_board[start_row][start_col] != '~')
				{
					printf("Please enter an address that has not been used.(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}

				while(player_board[start_row][start_col] == '~' && counter < 4)
				{
					start_col++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 4)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
			start_col -= 4;

			for(index2 = 0; index2 < 4; index2++)
			{
				player_board[start_row][start_col] = 'B';
				start_col++;
			}
			
			print_player_board(player_board);
			system("pause");
		}
		else
		{
			do
			{
				do
				{
					printf("Please enter the row and column of the starting point for the BATTLESHIP.\n(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}while (start_row < 0 || start_col < 0 || start_row > 9 || start_col > 9);

				while(player_board[start_row][start_col] != '~')
				{
					printf("Please enter an address that has not been used.(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}

				while(player_board[start_row][start_col] == '~' && counter < 4)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 4)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
			start_row -= 4;

			for(index2 = 0; index2 < 4; index2++)
			{
				player_board[start_row][start_col] = 'B';
				start_row++;
			}
			
			print_player_board(player_board);
			system("pause");
		}

		print_player_board(player_board);
}
void manually_place_submarine_on_board(char player_board[][10])
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	char orientation = '\0';

		printf("Would you like to place the SUBMARINE going down or right?\n('d' for down, 'r' for right)\n");
		scanf(" %c", &orientation);

		//check if overlapping occurs or off the board.
		if(orientation == 'r')
		{
			do
			{
				do
				{
					printf("Please enter the row and column of the starting point for the SUBMARINE.\n(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}while (start_row < 0 || start_col < 0 || start_row > 9 || start_col > 9);

				while(player_board[start_row][start_col] != '~')
				{
					printf("Please enter an address that has not been used.(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}

				while(player_board[start_row][start_col] == '~' && counter < 3)
				{
					start_col++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 3)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
			start_col -= 3;

			for(index2 = 0; index2 < 3; index2++)
			{
				player_board[start_row][start_col] = 'S';
				start_col++;
			}
			
			print_player_board(player_board);
			system("pause");
		}
		else
		{
			do
			{
				do
				{
					printf("Please enter the row and column of the starting point for the SUBMARINE.\n(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}while (start_row < 0 || start_col < 0 || start_row > 9 || start_col > 9);

				while(player_board[start_row][start_col] != '~')
				{
					printf("Please enter an address that has not been used.(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}

				while(player_board[start_row][start_col] == '~' && counter < 3)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 3)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
			start_row -= 3;

			for(index2 = 0; index2 < 3; index2++)
			{
				player_board[start_row][start_col] = 'S';
				start_row++;
			}
			
			print_player_board(player_board);
			system("pause");
		}

		print_player_board(player_board);
}
void manually_place_destroyer_on_board(char player_board[][10])
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	char orientation = '\0';

		printf("Would you like to place the DESTROYER going down or right?\n('d' for down, 'r' for right)\n");
		scanf(" %c", &orientation);

		//check if overlapping occurs or off the board.
		if(orientation == 'r')
		{
			do
			{
				do
				{
					printf("Please enter the row and column of the starting point for the DESTROYER.\n(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}while (start_row < 0 || start_col < 0 || start_row > 9 || start_col > 9);

				while(player_board[start_row][start_col] != '~')
				{
					printf("Please enter an address that has not been used.(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}

				while(player_board[start_row][start_col] == '~' && counter < 3)
				{
					start_col++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 3)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
			start_col -= 3;

			for(index2 = 0; index2 < 3; index2++)
			{
				player_board[start_row][start_col] = 'D';
				start_col++;
			}
			
			print_player_board(player_board);
			system("pause");
		}
		else
		{
			do
			{
				do
				{
					printf("Please enter the row and column of the starting point for the DESTROYER.\n(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}while (start_row < 0 || start_col < 0 || start_row > 9 || start_col > 9);

				while(player_board[start_row][start_col] != '~')
				{
					printf("Please enter an address that has not been used.(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}

				while(player_board[start_row][start_col] == '~' && counter < 3)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 3)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
			start_row -= 3;

			for(index2 = 0; index2 < 3; index2++)
			{
				player_board[start_row][start_col] = 'D';
				start_row++;
			}
			
			print_player_board(player_board);
			system("pause");
		}

		print_player_board(player_board);
}
void manually_place_patrolboat_on_board(char player_board[][10])
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	char orientation = '\0';

		printf("Would you like to place the PATROL BOAT going down or right?\n('d' for down, 'r' for right)\n");
		scanf(" %c", &orientation);

		//check if overlapping occurs or off the board.
		if(orientation == 'r')
		{
			do
			{
				do
				{
					printf("Please enter the row and column of the starting point for the PATROL BOAT.\n(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}while (start_row < 0 || start_col < 0 || start_row > 9 || start_col > 9);

				while(player_board[start_row][start_col] != '~')
				{
					printf("Please enter an address that has not been used.(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}

				while(player_board[start_row][start_col] == '~' && counter < 2)
				{
					start_col++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 2)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
			start_col -= 2;

			for(index2 = 0; index2 < 2; index2++)
			{
				player_board[start_row][start_col] = 'P';
				start_col++;
			}
			
			print_player_board(player_board);
			system("pause");
		}
		else
		{
			do
			{
				do
				{
					printf("Please enter the row and column of the starting point for the PATROL BOAT.\n(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}while (start_row < 0 || start_col < 0 || start_row > 9 || start_col > 9);

				while(player_board[start_row][start_col] != '~')
				{
					printf("Please enter an address that has not been used.(row'space'column)\n");
					scanf("%d %d", &start_row, &start_col);
				}

				while(player_board[start_row][start_col] == '~' && counter < 2)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 2)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
			start_row -= 2;

			for(index2 = 0; index2 < 2; index2++)
			{
				player_board[start_row][start_col] = 'P';
				start_row++;
			}
			
			print_player_board(player_board);
			system("pause");
		}

		print_player_board(player_board);
}

void automatically_place_carrier_on_comp_board(char computer_board[][10][10], int direction)
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	int *row_start_ptr = &start_row, *col_start_ptr = &start_col;

		//check if overlapping occurs or off the board.
		if(direction == 1) //Horizontal
		{
				do
				{
					
					gen_start_point(5, direction, row_start_ptr, col_start_ptr);

					while(computer_board[0][start_row][start_col] != '~')
					{
						gen_start_point(5, direction, row_start_ptr, col_start_ptr);
					}

					while(computer_board[0][start_row][start_col] == '~' && counter < 5)
					{
						start_col++;
						counter++;
						//check == 1 if 5 slots have been checked and are good/clear to place a boat
						if(counter == 5)
						{
							check = 1;
						}
						else
						{
							check = 0;
						}

					}

				}while(check == 0);
			
			start_col -= 5;

			for(index2 = 0; index2 < 5; index2++)
			{
				computer_board[0][start_row][start_col] = 'C';
				start_col++;
			}
			/*printf("\n");
			print_computer_board(computer_board, ROWS, COLS);
			system("pause");*/
		}
		else //Vertical
		{
			do
			{
				gen_start_point(5, direction, row_start_ptr, col_start_ptr);

				while(computer_board[0][start_row][start_col] != '~')
				{
					gen_start_point(5, direction, row_start_ptr, col_start_ptr);
				}

				while(computer_board[0][start_row][start_col] == '~' && counter < 5)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 5)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
		start_row -= 5;

		for(index2 = 0; index2 < 5; index2++)
		{
			computer_board[0][start_row][start_col] = 'C';
			start_row++;
		}
			
		/*print_computer_board(computer_board, ROWS, COLS);
		system("pause");*/
	}
}
void automatically_place_battleship_on_comp_board(char computer_board[][10][10], int direction)
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	int *row_start_ptr = &start_row, *col_start_ptr = &start_col;

		//check if overlapping occurs or off the board.
		if(direction == 1) //Horizontal
		{
				do
				{
					
					gen_start_point(4, direction, row_start_ptr, col_start_ptr);

					while(computer_board[0][start_row][start_col] != '~')
					{
						gen_start_point(4, direction, row_start_ptr, col_start_ptr);
					}

					while(computer_board[0][start_row][start_col] == '~' && counter < 4)
					{
						start_col++;
						counter++;
						//check == 1 if 5 slots have been checked and are good/clear to place a boat
						if(counter == 4)
						{
							check = 1;
						}
						else
						{
							check = 0;
						}

					}

				}while(check == 0);
			
			start_col -= 4;

			for(index2 = 0; index2 < 4; index2++)
			{
				computer_board[0][start_row][start_col] = 'B';
				start_col++;
			}
			/*printf("\n");
			print_computer_board(computer_board, ROWS, COLS);
			system("pause");*/
		}
		else //Vertical
		{
			do
			{
				gen_start_point(4, direction, row_start_ptr, col_start_ptr);

				while(computer_board[0][start_row][start_col] != '~')
				{
					gen_start_point(4, direction, row_start_ptr, col_start_ptr);
				}

				while(computer_board[0][start_row][start_col] == '~' && counter < 4)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 4)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
		start_row -= 4;

		for(index2 = 0; index2 < 4; index2++)
		{
			computer_board[0][start_row][start_col] = 'B';
			start_row++;
		}
			
		//print_computer_board(computer_board, ROWS, COLS);
		//system("pause");
	}
}
void automatically_place_submarine_on_comp_board(char computer_board[][10][10], int direction)
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	int *row_start_ptr = &start_row, *col_start_ptr = &start_col;

		//check if overlapping occurs or off the board.
		if(direction == 1) //Horizontal
		{
				do
				{
					
					gen_start_point(3, direction, row_start_ptr, col_start_ptr);

					while(computer_board[0][start_row][start_col] != '~')
					{
						gen_start_point(3, direction, row_start_ptr, col_start_ptr);
					}

					while(computer_board[0][start_row][start_col] == '~' && counter < 3)
					{
						start_col++;
						counter++;
						//check == 1 if 5 slots have been checked and are good/clear to place a boat
						if(counter == 3)
						{
							check = 1;
						}
						else
						{
							check = 0;
						}

					}

				}while(check == 0);
			
			start_col -= 3;

			for(index2 = 0; index2 < 3; index2++)
			{
				computer_board[0][start_row][start_col] = 'S';
				start_col++;
			}
			/*printf("\n");
			print_computer_board(computer_board, ROWS, COLS);
			system("pause");*/
		}
		else //Vertical
		{
			do
			{
				gen_start_point(3, direction, row_start_ptr, col_start_ptr);

				while(computer_board[0][start_row][start_col] != '~')
				{
					gen_start_point(3, direction, row_start_ptr, col_start_ptr);
				}

				while(computer_board[0][start_row][start_col] == '~' && counter < 3)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 3)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
		start_row -= 3;

		for(index2 = 0; index2 < 3; index2++)
		{
			computer_board[0][start_row][start_col] = 'S';
			start_row++;
		}
			
		/*print_computer_board(computer_board, ROWS, COLS);
		system("pause");*/
	}
}
void automatically_place_destroyer_on_comp_board(char computer_board[][10][10], int direction)
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	int *row_start_ptr = &start_row, *col_start_ptr = &start_col;

		//check if overlapping occurs or off the board.
		if(direction == 1) //Horizontal
		{
				do
				{
					
					gen_start_point(3, direction, row_start_ptr, col_start_ptr);

					while(computer_board[0][start_row][start_col] != '~')
					{
						gen_start_point(3, direction, row_start_ptr, col_start_ptr);
					}

					while(computer_board[0][start_row][start_col] == '~' && counter < 3)
					{
						start_col++;
						counter++;
						//check == 1 if 5 slots have been checked and are good/clear to place a boat
						if(counter == 3)
						{
							check = 1;
						}
						else
						{
							check = 0;
						}

					}

				}while(check == 0);
			
			start_col -= 3;

			for(index2 = 0; index2 < 3; index2++)
			{
				computer_board[0][start_row][start_col] = 'D';
				start_col++;
			}
			/*printf("\n");
			print_computer_board(computer_board, ROWS, COLS);
			system("pause");*/
		}
		else //Vertical
		{
			do
			{
				gen_start_point(3, direction, row_start_ptr, col_start_ptr);

				while(computer_board[0][start_row][start_col] != '~')
				{
					gen_start_point(3, direction, row_start_ptr, col_start_ptr);
				}

				while(computer_board[0][start_row][start_col] == '~' && counter < 3)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 3)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
		start_row -= 3;

		for(index2 = 0; index2 < 3; index2++)
		{
			computer_board[0][start_row][start_col] = 'D';
			start_row++;
		}
			
		/*print_computer_board(computer_board, ROWS, COLS);
		system("pause");*/
	}
}
void automatically_place_patrolboat_on_comp_board(char computer_board[][10][10], int direction)
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	int *row_start_ptr = &start_row, *col_start_ptr = &start_col;

		//check if overlapping occurs or off the board.
		if(direction == 1) //Horizontal
		{
				do
				{
					
					gen_start_point(2, direction, row_start_ptr, col_start_ptr);

					while(computer_board[0][start_row][start_col] != '~')
					{
						gen_start_point(2, direction, row_start_ptr, col_start_ptr);
					}

					while(computer_board[0][start_row][start_col] == '~' && counter < 2)
					{
						start_col++;
						counter++;
						//check == 1 if 5 slots have been checked and are good/clear to place a boat
						if(counter == 2)
						{
							check = 1;
						}
						else
						{
							check = 0;
						}

					}

				}while(check == 0);
			
			start_col -= 2;

			for(index2 = 0; index2 < 2; index2++)
			{
				computer_board[0][start_row][start_col] = 'P';
				start_col++;
			}
			/*printf("\n");
			print_computer_board(computer_board, ROWS, COLS);
			system("pause");*/
		}
		else //Vertical
		{
			do
			{
				gen_start_point(2, direction, row_start_ptr, col_start_ptr);

				while(computer_board[0][start_row][start_col] != '~')
				{
					gen_start_point(2, direction, row_start_ptr, col_start_ptr);
				}

				while(computer_board[0][start_row][start_col] == '~' && counter < 2)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 2)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
		start_row -= 2;

		for(index2 = 0; index2 < 2; index2++)
		{
			computer_board[0][start_row][start_col] = 'P';
			start_row++;
		}
			
		/*print_computer_board(computer_board, ROWS, COLS);
		system("pause");*/
	}
}

void automatically_place_carrier_on_board(char player_board[][10], int direction)
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	int *row_start_ptr = &start_row, *col_start_ptr = &start_col;
	
	//print_player_board(player_board);

		//check if overlapping occurs or off the board.
		if(direction == 1) //Horizontal
		{
				do
				{
					
					gen_start_point(5, direction, row_start_ptr, col_start_ptr);

					while(player_board[start_row][start_col] != '~')
					{
						gen_start_point(5, direction, row_start_ptr, col_start_ptr);
					}

					while(player_board[start_row][start_col] == '~' && counter < 5)
					{
						start_col++;
						counter++;
						//check == 1 if 5 slots have been checked and are good/clear to place a boat
						if(counter == 5)
						{
							check = 1;
						}
						else
						{
							check = 0;
						}

					}

				}while(check == 0);
			
			start_col -= 5;

			for(index2 = 0; index2 < 5; index2++)
			{
				player_board[start_row][start_col] = 'C';
				start_col++;
			}
			//printf("\n");
			//print_player_board(player_board);
			//system("pause");
		}
		else //Vertical
		{
			do
			{
				gen_start_point(5, direction, row_start_ptr, col_start_ptr);

				while(player_board[start_row][start_col] != '~')
				{
					gen_start_point(5, direction, row_start_ptr, col_start_ptr);
				}

				while(player_board[start_row][start_col] == '~' && counter < 5)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 5)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
		start_row -= 5;

		for(index2 = 0; index2 < 5; index2++)
		{
			player_board[start_row][start_col] = 'C';
			start_row++;
		}
			
		//print_player_board(player_board);
		//system("pause");
	}
}
void automatically_place_battleship_on_board(char player_board[][10], int direction)
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	int *row_start_ptr = &start_row, *col_start_ptr = &start_col;
	
	//print_player_board(player_board);

		//check if overlapping occurs or off the board.
		if(direction == 1) //Horizontal
		{
				do
				{
					
					gen_start_point(4, direction, row_start_ptr, col_start_ptr);

					while(player_board[start_row][start_col] != '~')
					{
						gen_start_point(4, direction, row_start_ptr, col_start_ptr);
					}

					while(player_board[start_row][start_col] == '~' && counter < 4)
					{
						start_col++;
						counter++;
						//check == 1 if 5 slots have been checked and are good/clear to place a boat
						if(counter == 4)
						{
							check = 1;
						}
						else
						{
							check = 0;
						}

					}

				}while(check == 0);
			
			start_col -= 4;

			for(index2 = 0; index2 < 4; index2++)
			{
				player_board[start_row][start_col] = 'B';
				start_col++;
			}
			//printf("\n");
			//print_player_board(player_board);
			//system("pause");
		}
		else //Vertical
		{
			do
			{
				gen_start_point(4, direction, row_start_ptr, col_start_ptr);

				while(player_board[start_row][start_col] != '~')
				{
					gen_start_point(4, direction, row_start_ptr, col_start_ptr);
				}

				while(player_board[start_row][start_col] == '~' && counter < 4)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 4)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
		start_row -= 4;

		for(index2 = 0; index2 < 4; index2++)
		{
			player_board[start_row][start_col] = 'B';
			start_row++;
		}
			
		//print_player_board(player_board);
		//system("pause");
	}
}
void automatically_place_submarine_on_board(char player_board[][10], int direction)
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	int *row_start_ptr = &start_row, *col_start_ptr = &start_col;
	
	//print_player_board(player_board);

		//check if overlapping occurs or off the board.
		if(direction == 1) //Horizontal
		{
				do
				{
					
					gen_start_point(3, direction, row_start_ptr, col_start_ptr);

					while(player_board[start_row][start_col] != '~')
					{
						gen_start_point(3, direction, row_start_ptr, col_start_ptr);
					}

					while(player_board[start_row][start_col] == '~' && counter < 3)
					{
						start_col++;
						counter++;
						//check == 1 if 5 slots have been checked and are good/clear to place a boat
						if(counter == 3)
						{
							check = 1;
						}
						else
						{
							check = 0;
						}

					}

				}while(check == 0);
			
			start_col -= 3;

			for(index2 = 0; index2 < 3; index2++)
			{
				player_board[start_row][start_col] = 'S';
				start_col++;
			}
			//printf("\n");
			//print_player_board(player_board);
			//system("pause");
		}
		else //Vertical
		{
			do
			{
				gen_start_point(3, direction, row_start_ptr, col_start_ptr);

				while(player_board[start_row][start_col] != '~')
				{
					gen_start_point(3, direction, row_start_ptr, col_start_ptr);
				}

				while(player_board[start_row][start_col] == '~' && counter < 3)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 3)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
		start_row -= 3;

		for(index2 = 0; index2 < 3; index2++)
		{
			player_board[start_row][start_col] = 'S';
			start_row++;
		}
			
		//print_player_board(player_board);
		//system("pause");
	}
}
void automatically_place_destroyer_on_board(char player_board[][10], int direction)
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	int *row_start_ptr = &start_row, *col_start_ptr = &start_col;
	
	//print_player_board(player_board);

		//check if overlapping occurs or off the board.
		if(direction == 1) //Horizontal
		{
				do
				{
					
					gen_start_point(3, direction, row_start_ptr, col_start_ptr);

					while(player_board[start_row][start_col] != '~')
					{
						gen_start_point(3, direction, row_start_ptr, col_start_ptr);
					}

					while(player_board[start_row][start_col] == '~' && counter < 3)
					{
						start_col++;
						counter++;
						//check == 1 if 5 slots have been checked and are good/clear to place a boat
						if(counter == 3)
						{
							check = 1;
						}
						else
						{
							check = 0;
						}

					}

				}while(check == 0);
			
			start_col -= 3;

			for(index2 = 0; index2 < 3; index2++)
			{
				player_board[start_row][start_col] = 'D';
				start_col++;
			}
			//printf("\n");
			//print_player_board(player_board);
			//system("pause");
		}
		else //Vertical
		{
			do
			{
				gen_start_point(3, direction, row_start_ptr, col_start_ptr);

				while(player_board[start_row][start_col] != '~')
				{
					gen_start_point(3, direction, row_start_ptr, col_start_ptr);
				}

				while(player_board[start_row][start_col] == '~' && counter < 3)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 3)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
		start_row -= 3;

		for(index2 = 0; index2 < 3; index2++)
		{
			player_board[start_row][start_col] = 'D';
			start_row++;
		}
			
		//print_player_board(player_board);
		//system("pause");
	}
}
void automatically_place_patrolboat_on_board(char player_board[][10], int direction)
{
	int start_row = 0, start_col = 0, index = 0, index2 = 0, check = 0, counter = 0;
	int *row_start_ptr = &start_row, *col_start_ptr = &start_col;
	
	//print_player_board(player_board);

		//check if overlapping occurs or off the board.
		if(direction == 1) //Horizontal
		{
				do
				{
					
					gen_start_point(2, direction, row_start_ptr, col_start_ptr);

					while(player_board[start_row][start_col] != '~')
					{
						gen_start_point(2, direction, row_start_ptr, col_start_ptr);
					}

					while(player_board[start_row][start_col] == '~' && counter < 2)
					{
						start_col++;
						counter++;
						//check == 1 if 5 slots have been checked and are good/clear to place a boat
						if(counter == 2)
						{
							check = 1;
						}
						else
						{
							check = 0;
						}

					}

				}while(check == 0);
			
			start_col -= 2;

			for(index2 = 0; index2 < 2; index2++)
			{
				player_board[start_row][start_col] = 'P';
				start_col++;
			}
			/*printf("\n");
			print_player_board(player_board);
			system("pause");*/
		}
		else //Vertical
		{
			do
			{
				gen_start_point(2, direction, row_start_ptr, col_start_ptr);

				while(player_board[start_row][start_col] != '~')
				{
					gen_start_point(2, direction, row_start_ptr, col_start_ptr);
				}

				while(player_board[start_row][start_col] == '~' && counter < 2)
				{
					start_row++;
					counter++;
					//check == 1 if 5 slots have been checked and are good/clear to place a boat
					if(counter == 2)
					{
						check = 1;
					}
					else
					{
						check = 0;
					}

				}

			}while(check == 0);
			
		start_row -= 2;

		for(index2 = 0; index2 < 2; index2++)
		{
			player_board[start_row][start_col] = 'P';
			start_row++;
		}
			
		//print_player_board(player_board);
		//system("pause");
	}
}

Hit_or_miss player_one_is_hit_or_miss(int row_guess, int col_guess, char comp_board[][10][10], char *ship_hit)
{
	Hit_or_miss result;


	if(comp_board[0][row_guess][col_guess] == 'C' || comp_board[0][row_guess][col_guess] == 'B' || comp_board[0][row_guess][col_guess] == 'S' || comp_board[0][row_guess][col_guess] == 'D' || comp_board[0][row_guess][col_guess] == 'P')
	{
		result = hit;
		*ship_hit = comp_board[0][row_guess][col_guess];
	}
	else
	{
		result = miss;
	}

	return result;
}

Hit_or_miss computer_is_hit_or_miss(int x, int y, char player_board[][10], char *ship_hit)
{
	Hit_or_miss result;


	if(player_board[x][y] == 'C' || player_board[x][y] == 'B' || player_board[x][y] == 'S' || player_board[x][y] == 'D' || player_board[x][y] == 'P')
	{
		result = hit;

		*ship_hit = player_board[x][y];
	}
	else
	{
		result = miss;
	}

	return result;
}

void player_one_hit (unsigned int *row_guess,         unsigned int *col_guess,				    
							  int *player_one_total_hits,      int *player_one_total_misses, 
							  int *player_one_total_shots,     int *player_one_carrier_hits, 
							  int *player_one_battleship_hits, int *player_one_submarine_hits, 
							  int *player_one_destroyer_hits,  int *player_one_patrol_boat_hits, 
							  char computer_board[][10][10],   FILE *outfile, char *ship_hit)
{
//prints out a * on the player two board to signify a hit
	computer_board[1][*row_guess][*col_guess] = '*';

	switch(*ship_hit) 
	{
		case 'C'  :
			*player_one_carrier_hits += 1;
			*player_one_total_hits += 1;
			*player_one_total_shots += 1;

  			fprintf(outfile, "Player one: HIT CARRIER : ROW %d : COL : %d\n", *row_guess, *col_guess);
			printf("\nPlayer one: HIT : ROW %d : COL : %d\n", *row_guess, *col_guess);

			//print cooardinate and ship hit to file for player one
			if(*player_one_carrier_hits == 5)
			{
				//print sunk message to file
				fprintf(outfile, "Player one: SUNK CARRIER : ROW %d : COL : %d\n", *row_guess, *col_guess);
				printf("\nPlayer one: SUNK CARRIER : ROW %d : COL : %d\n", *row_guess, *col_guess);
			}

			break;
	
		case 'B'  :
			*player_one_battleship_hits += 1;
			*player_one_total_hits += 1;
			*player_one_total_shots += 1;

			fprintf(outfile, "Player one: HIT BATTLESHIP : ROW %d : COL : %d\n", *row_guess, *col_guess);
			printf("\nPlayer one: HIT : ROW %d : COL : %d\n", *row_guess, *col_guess);

			//print cooardinate and ship hit to file for player one
			if(*player_one_battleship_hits == 4)
			{
				//print sunk message to file
				fprintf(outfile, "Player one: SUNK BATTLESHIP : ROW %d : COL : %d\n", *row_guess, *col_guess);
				printf("\nPlayer one: SUNK BATTLESHIP : ROW %d : COL : %d\n", *row_guess, *col_guess);
			}

			break; /* optional */

		case 'S'  :
			*player_one_submarine_hits += 1;
			*player_one_total_hits += 1;
			*player_one_total_shots += 1;

			fprintf(outfile, "Player one: HIT SUBMARINE : ROW %d : COL : %d\n", *row_guess, *col_guess);
			printf("\nPlayer one: HIT : ROW %d : COL : %d\n", *row_guess, *col_guess);

			//print cooardinate and ship hit to file for player one
			if(*player_one_submarine_hits == 3)
			{
				//print sunk message to file
				fprintf(outfile, "Player one: SUNK SUBMARINE : ROW %d : COL : %d\n", *row_guess, *col_guess);
				printf("\nPlayer one: SUNK SUBMARINE : ROW %d : COL : %d\n", *row_guess, *col_guess);
			}

			break;
					   
		case 'D'  :
			*player_one_destroyer_hits += 1;
			*player_one_total_hits += 1;
			*player_one_total_shots += 1;

			fprintf(outfile, "Player one: HIT DESTROYER : ROW %d : COL : %d\n", *row_guess, *col_guess);
			printf("\nPlayer one: HIT : ROW %d : COL : %d\n", *row_guess, *col_guess);

			//print cooardinate and ship hit to file for player one
			if(*player_one_carrier_hits == 3)
			{
				//print sunk message to file
				fprintf(outfile, "Player one: SUNK DESTROYER : ROW %d : COL : %d\n", *row_guess, *col_guess);
				printf("\nPlayer one: SUNK DESTROYER : ROW %d : COL : %d\n", *row_guess, *col_guess);
			}

			break;

		case 'P'  :
			*player_one_patrol_boat_hits += 1;
			*player_one_total_hits += 1;
			*player_one_total_shots += 1;

			fprintf(outfile, "Player one: HIT PATROL BOAT : ROW %d : COL : %d\n", *row_guess, *col_guess);
			printf("\nPlayer one: HIT : ROW %d : COL : %d\n", *row_guess, *col_guess);

			//print cooardinate and ship hit to file for player one
			if(*player_one_patrol_boat_hits == 2)
			{
				//print sunk message to file
				fprintf(outfile, "Player one: SUNK PATROL BOAT : ROW %d : COL : %d\n", *row_guess, *col_guess);
				printf("\nPlayer one: SUNK PATROL BOAT : ROW %d : COL : %d\n", *row_guess, *col_guess);
			}

			break;
	}

	fflush (outfile);
	return;
}

void computer_hit(unsigned int *x,      unsigned int *y,    int *player_two_total_hits, 
						   int *player_two_total_misses,	int *player_two_total_shots,
						   int *player_two_carrier_hits,	int *player_two_battleship_hits, 
						   int *player_two_submarine_hits,  int *player_two_destroyer_hits,
						   int *player_two_patrol_boat_hits, 
						   char player_board[][10],         FILE *outfile, char *ship_hit)
{
//prints out a * on the player one board to signify a hit
	player_board[*x][*y] = '*';
					
	switch(*ship_hit) 
	{
		case 'C'  :
			*player_two_carrier_hits += 1;
			*player_two_total_hits += 1;
			*player_two_total_shots += 1;

			
  			fprintf(outfile, "Computer: HIT CARRIER : ROW %d : COL : %d\n", *x, *y);
			printf("\nComputer: HIT CARRIER : ROW %d : COL : %d\n", *x, *y);

			//print cooardinate and ship hit to file for player one
			if(*player_two_carrier_hits == 5)
			{
				//print sunk message to file
				fprintf(outfile, "Computer: SUNK CARRIER : ROW %d : COL : %d\n", *x, *y);
				printf("\nComputer: SUNK CARRIER : ROW %d : COL : %d\n", *x, *y);
			}

			break;
	
		case 'B'  :
			*player_two_battleship_hits += 1;
			*player_two_total_hits += 1;
			*player_two_total_shots += 1;

			fprintf(outfile, "Computer: HIT BATTLESHIP : ROW %d : COL : %d\n", *x, *y);
			printf("\nComputer: HIT BATTLESHIP : ROW %d : COL : %d\n", *x, *y);

			//print cooardinate and ship hit to file for player one
			if(*player_two_battleship_hits == 4)
			{
				//print sunk message to file
				fprintf(outfile, "Computer: SUNK BATTLESHIP : ROW %d : COL : %d\n", *x, *y);
				printf("\nComputer: SUNK BATTLESHIP : ROW %d : COL : %d\n", *x, *y);
			}

			break; /* optional */

		case 'S'  :
			*player_two_submarine_hits += 1;
			*player_two_total_hits += 1;
			*player_two_total_shots += 1;

			fprintf(outfile, "Computer: HIT SUBMARINE : ROW %d : COL : %d\n", *x, *y);
			printf("\nComputer: HIT SUBMARINE : ROW %d : COL : %d\n", *x, *y);

			//print cooardinate and ship hit to file for player one
			if(*player_two_submarine_hits == 3)
			{
				//print sunk message to file
				fprintf(outfile, "Computer: SUNK SUBMARINE : ROW %d : COL : %d\n", *x, *y);
				printf("\nComputer: SUNK SUBMARINE : ROW %d : COL : %d\n", *x, *y);
			}

			break;
					   
		case 'D'  :
			*player_two_destroyer_hits += 1;
			*player_two_total_hits += 1;
			*player_two_total_shots += 1;

			fprintf(outfile, "Computer: HIT DESTROYER : ROW %d : COL : %d\n", *x, *y);
			printf("\nComputer: HIT DESTROYER : ROW %d : COL : %d\n", *x, *y);

			//print cooardinate and ship hit to file for player one
			if(*player_two_carrier_hits == 3)
			{
				//print sunk message to file
				fprintf(outfile, "Computer: SUNK DESTROYER : ROW %d : COL : %d\n", *x, *y);
				printf("\nComputer: SUNK DESTROYER : ROW %d : COL : %d\n", *x, *y);
			}

			break;

		case 'P'  :
			*player_two_patrol_boat_hits += 1;
			*player_two_total_hits += 1;
			*player_two_total_shots += 1;

			fprintf(outfile, "Computer: HIT PATROL BOAT : ROW %d : COL : %d\n", *x, *y);
			printf("\nComputer: HIT PATROL BOAT : ROW %d : COL : %d\n", *x, *y);

			//print cooardinate and ship hit to file for player one
			if(*player_two_patrol_boat_hits == 2)
			{
				//print sunk message to file
				fprintf(outfile, "Computer: SUNK PATROL BOAT : ROW %d : COL : %d\n", *x, *y);
				printf("\nComputer: SUNK PATROL BOAT : ROW %d : COL : %d\n", *x, *y);
			}

			break;
	}
	fflush (outfile);
	return;
}
