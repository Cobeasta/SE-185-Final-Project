	#include <stdio.h>
	#include <math.h>
	#include <ncurses.h>
	#include <time.h>
	#include <stdlib.h>

	int game_loop(); // for controlling the portion of the game where the game is in play
	int player_turn();//for organizing events while it is the player's turn
	int cpu_turn(); // for organizing events while it is the computer's turn
	void cpu_win(); //for checking if the computer won the game
	void human_win(); //for checking if the player won the game
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
	
	srand(time(NULL));
	
	initscr();
	
	game_loop();
		
	endwin();
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
	int left, right, up, down, x, triangle, circle, square = 0;
	int prevLeft, prevRight, prevUp, prevDown, prevX, prevTriangle, prevCircle, prevSquare = 0;
int timer;
	
	
	
	while(1){
		scanf("%d %d %d %d %d %d %d %d %d", &timer, &left, &right, &up, &down, &x, &triangle, &circle, &square);
	//read controller, use this to move the pointers location along the screen.	
	//then call shoot to update the grids and return the output.
	
	prevLeft = left;
	prevRight = right;
	prevUp = up;
	prevDown = down;
	
	if(left && prevLeft != left){
		mvprintw(2, 2, "Left");
	}
	else if(right && prevRight != right){
		mvprintw(2, 2, "Right");
	}
	else if(down && prevDown != down){
		mvprintw(2, 2, "Down");
	}
	else if(up && prevUp != up){
		mvprintw(2, 2, "Up");
	}

	if(x && prevX != x){
		
	}
	else if(triangle && prevTriangle != triangle){
		
	}
	else if(square && prevSquare != square){
		
	}
	else if(circle && prevCircle != circle){
		
	}
	
	
	prevX = x;
	prevTriangle = triangle;
	prevCircle = circle;
	prevSquare = square;
	}
}

/** 
return -1 if they miss
return 0 if they hit
return 1 if they win
**/
int cpu_turn(){
	int tempRow;
	int tempCol;
	
	while (1) {
		tempRow = rand() % 6;
		tempCol = rand() % 6; //random guess on grid
	
		if ((playerShips[tempRow][tempCol] == 'X')|| (playerShips[tempRow][tempCol] == '*')) //if the computer has already guessed there
			continue;
		} else {
			if (playerShips[tempRow][tempCol] == 'O'){ //hit- change boat to hit boat
				playerShips[tempRow][tempCol] = 'X';
				if (cpu_win){
					return 1;
				} else {
					return 0;
				}
			} else if (playerShips[tempRow][tempCol] == '-') { //miss- change empty space to missed empty space
				playerShips[tempRow][tempCol] = '*';
				return 0;
			}
		}
	}
	return 0;
}

/**
updates the map and 
	return -1 for miss
	return 1 for hit
**/
int shoot(int player, char * grid[6][6], int row, int column){ //grid is the computer's boat array
	if (grid[row][column] == 'O'){
		playerGuesses[row][column] = 'X'; //symbol for hit
		printArrays();
		return 1;
	} else {
		playerGuesses[row][column] = '*'; //symbol for miss
		printArrays();
		return -1;
	}
}


void cpu_win(){
	int count = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (playerShips[i][j] == 'X') //count all of the computer's hits
				count += 1;
			}
		}
	}
	if (count < 6){ //haven't won yet
		return 0;
	} else if (count == 6) { //hit all ships
		return 1;
	}
}
void human_win(){
	int count = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (playerGuesses[i][j] == 'X') //count all of the player's hits
				count += 1;
			}
		}
	}
	if (count < 6){ //haven't won yet
		return 0;
	} else if (count == 6) { //hit all ships
		return 1;
	}
}


int printArrays(){
	initscr();
	int row = 5;
	int column = 5;
	
	mvprintw(row - 1, column, "Your Boats");
	
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 6; j++){

			mvprintw(row, column, "%c", playerShips[i][j]); //prints the array for the player ships
			refresh();
			column += 4;
		}
		row += 2;
		column = 5;
	}


	column = 35;
	row = 5;
	
	mvprintw(row - 1, column, "Your Guesses");

	for (int g = 0; g < 6; g++){
		for (int h = 0; h < 6; h++){
			mvprintw(row, column, "%c", playerGuesses[i][j]); //prints the array for player guesses
			refresh();
			column += 4;
		}
		row += 2;
		column = 35;
	}
	
	refresh();
	return 0;
}

