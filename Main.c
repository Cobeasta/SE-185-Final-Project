/*
imports
*/
#include <stdio.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include<unistd.h>
#include<time.h>

/*
prototypes
*/

	int game_loop(); // for controlling the portion of the game where the game is in play
	int player_turn();//for organizing events while it is the player's turn
	int cpu_turn(); // for organizing events while it is the computer's turn
	int cpu_win(); //for checking if the computer won the game
	int human_win(); //for checking if the player won the game
	int shoot(); //"shoots" the inputted array of ships, returns if it is hit, or miss
	int printArrays();

	int PLAYER = 0;
	int CPU = 1;
	//grids for playing
	char playerShips[6][6];
	char cpuShips[6][6];
	char playerGuesses[6][6];
	char cpuGuesses[6][6];
	
int main(){
		initscr();
		
}

/**

@return -1 if the player loses
 1 if the player wins. 
 0 if the game draws
**/
int game_loop(){

	int turn = 0; // 0 for human turn, 1 for cpu turn
	int i = player_turn();
	while(1){
		if(turn == PLAYER){
			i = player_turn();
		}
		else{
			i = cpu_turn();
		}	
		
		//player hits
		if(i == 0 && turn == PLAYER){
			//player has another turn, grid is already updated
			continue;
		}
		//player misses
		else if(i == -1 && turn == PLAYER){
			turn = CPU;
		}
		//player wins
		else if(i == 1 && turn == PLAYER){
			return 1;
		}
		//cpu hits
		else if(i == 0 && turn == CPU){
			//cpu has another turn, grid is already updated
			continue;
		}
		//cpu misses
		else if(i == -1 && turn == CPU){
			turn = PLAYER;
		}
		//cpu wins
		else{
			return -1;
		}
			
	}
}

/**
return -1 if they miss
return 0 if they hit
return 1 if they win
**/
int player_turn(){
	int left, right, up, down, x = 0;
	
	while(1){
		
	//read controller, use this to move the pointers location along the screen.	
	//then call shoot to update the grids and return the output.
	}
}

/**
return -1 if they miss
return 0 if they hit
return 1 if they win
**/
int cpu_turn(){
	
}

/**
updates the map and 
	return -1 for miss
	return 1 for hit
**/
int shoot(int player char * grid[][]]){
	
}


void cpu_win(){
	
}
void human_win(){
	
}

//TODO Set us mvprintw
int printArrays(){
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 6; j++){
			printf("%c   ", playerShips[i][j]; //prints the array for the player ships
		}
		printf("\n\n");
	}
	printf("\n\n\n");
	for (int k = 0; i < 6; i++){
		for (int m = 0; j < 6; j++){
			printf("%c   ", playerGuesses[i][j]; //prints the array for player guesses
		}
		printf("\n\n");
	}
	return 0;
}

