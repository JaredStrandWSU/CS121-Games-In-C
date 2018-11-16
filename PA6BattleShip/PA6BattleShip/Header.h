#ifndef HEADER_H // Guard Code
#define HEADER_H // Guard Code

//Eliminates security warnings
#define _CRT_SECURE_NO_WARNINGS
#define ROWS 10
#define COLS 10
#define CARRIER_SIZE 5
#define BATTLESHIP_SIZE 4
#define CRUSIER_SIZE 3
#define SUBMARINE_SIZE 3
#define DESTROYER_SIZE 2
#define MAX_HITS 17

//Libraries
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

//enumerated type of hit or miss
typedef enum hit_or_miss
{
	miss, hit
} Hit_or_miss;

//Protoypes
//Runs the main game function
int run_battleship(void);

//Fun splash screen graphics
void splash_screen(void);

//Gam menu
int menu(void);

//Initializes a new game of battleship
int play_battleship_game(void);

//Prints the rules of battleship
void print_rules(void);

//Initializes the player and computer boards as arrays
void init_player_board (char board[][10], int rows, int cols);
void init_computer_board (char board[][10][10], int rows, int cols);

//Randomly generates a starting point for the computers attack within the bounds
void gen_start_point(int length_of_ship, int direction, int *row_start_ptr, int *col_start_ptr);

//Prints out the boards in a visual manner for the player to keep track of the game
void print_computer_board (char board[][10][10], int rows, int cols);
void print_computer_board_no_ships (char board[][10][10], int rows, int cols);
void print_player_board(char player_board[][10]);

//Allows the user to manually place the ships on the computer generated board
void manually_place_carrier_on_board(char player_board[][10]);
void manually_place_battleship_on_board(char player_board[][10]);
void manually_place_submarine_on_board(char player_board[][10]);
void manually_place_destroyer_on_board(char player_board[][10]);
void manually_place_patrolboat_on_board(char player_board[][10]);


//Allows the option of having all the peices randomly placed on the players board
void automatically_place_carrier_on_board(char player_board[][10], int direction);
void automatically_place_battleship_on_board(char player_board[][10], int direction);
void automatically_place_submarine_on_board(char player_board[][10], int direction);
void automatically_place_destroyer_on_board(char player_board[][10], int direction);
void automatically_place_patrolboat_on_board(char player_board[][10], int direction);

//Automatically generates postions and places the peices on the computer generated board
void automatically_place_carrier_on_comp_board(char computer_board[][10][10], int direction);
void automatically_place_battleship_on_comp_board(char computer_board[][10][10], int direction);
void automatically_place_submarine_on_comp_board(char computer_board[][10][10], int direction);
void automatically_place_destroyer_on_comp_board(char computer_board[][10][10], int direction);
void automatically_place_patrolboat_on_comp_board(char computer_board[][10][10], int direction);

//Excecutes neccesary incrementations and performs actions if player ones attack is a hit
void player_one_hit (unsigned int *row_guess,	      unsigned int *col_guess,				    
							  int *player_one_total_hits,      int *player_one_total_misses, 
							  int *player_one_total_shots,     int *player_one_carrier_hits, 
							  int *player_one_battleship_hits, int *player_one_submarine_hits, 
							  int *player_one_destroyer_hits,  int *player_one_patrol_boat_hits, 
							  char computer_board[][10][10],   FILE *outfile, char *ship_hit);

//Excecutes neccesary incrementations and performs actions if computers attack is a hit
void computer_hit(  unsigned int *x,                 unsigned int *y, 
							 int *player_two_total_hits,      int *player_two_total_misses,
							 int *player_two_total_shots,     int *player_two_carrier_hits,	
							 int *player_two_battleship_hits, int *player_two_submarine_hits,  
							 int *player_two_destroyer_hits,  int *player_two_patrol_boat_hits, 
							 char player_board[][10],         FILE *outfile, char *ship_hit);

//Determines if the attack on the current position is a hit or miss and sends back the enumerated typed indicated the result
Hit_or_miss player_one_is_hit_or_miss(int row_guess, int col_guess, char comp_board[][10][10], char *ship_hit);
Hit_or_miss computer_is_hit_or_miss(int x, int y, char player_board[][10], char *ship_hit);

//Generates random cooardinates for the computers attack
void generate_computer_shot(unsigned int *x, unsigned int *y);

#endif // !HEADER_H		Guard code