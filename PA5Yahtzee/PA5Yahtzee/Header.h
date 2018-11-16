#ifndef HEADER_H // Guard Code
#define HEADER_H // Guard Code
#define NUM_ITEMS 5

//Eliminates security warnings
#define _CRT_SECURE_NO_WARNINGS

//Libraries
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

//Protoypes
 int runYahtzee(void);
 int menu(void);
 void print_rules(void);
 int play_Yahtzee_Game(void);
 void roll_dice (int dice_values[5], int num_items);
 void display_dice (int dice[5], int num_items);
 void reroll_dice (int dice_values[5], int num_items);
 void select_combination_player_1(int dice_values[5],int num_values[6], int scores[13], int comb_used[13], int *p1_sum_ptr);
 void select_combination_player_2(int dice_values[5],int num_values[6], int scores[13], int comb_used[13], int *p2_sum_ptr);
 void populate_num_dice (int dice_values[5], int num_values[5]);

#endif // !HEADER_H		Guard code