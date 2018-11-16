#include "Header.h"

//Runs the main menu for the game
int runYahtzee(void)
{
	int game_path = 0;
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
			play_Yahtzee_Game();
			printf("\n\nReturning to the main menu.\n\n");
			break; /* optional */
		}
	case 3 : /*Exits Yahtzee*/
		{
			printf("\n\nThanks for playing Yahtzee!\n\n");
			return 0;
		}
	   }
	}
}
