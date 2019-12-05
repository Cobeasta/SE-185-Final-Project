	#include <stdio.h>
	#include <math.h>
	#include <ncurses.h>
	#include <time.h>

	
	int game_loop();
	int player_turn();
	int cpu_turn();
	void cpu_win();
	void human_win();
	int shoot();
	void initGrid();

	const char EMPTY = '-';
	const char HIT = 'X';
	const char MISS = '*';
	const char BOAT = 'O';
	const char  SELECTION = 'W';

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
	
	//compile with gcc Main.c -o main.exe -lncurses
	//run with  ./ds4rd.exe -d 054c:05c4 -D DS4_BT -t -b -bd | ./main.exe
int main(){
	initscr();
	initGrid();
	printArrays();
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
int player_turn(char * playerGuesses[6][6]){
	int row = 5;
	int col = 35;
	int left, right, up, down, x, triangle, circle, square = 0;
	int prevLeft, prevRight, prevUp, prevDown, prevX, prevTriangle, prevCircle, prevSquare = 0;
	int timer;
	mvprintw(row, col, "%c", SELECTION);
	refresh();
	
	
	while(1){
		scanf("%d, %d,%d,%d,%d, %d,%d,%d,%d", &timer, &triangle, &circle, &x, &square, &up, &left, &down, &right);
	//read controller, use this to move the pointers location along the screen.	
	//then call shoot to update the grids and return the output.
	if(left && prevLeft != left){
		mvprintw(row +2, col+2, "  ");

		col -= 4;
		if(col < 35){
			col = 35;
		}
		printArrays();
		mvprintw(row, col, "%c", SELECTION);
	}
	else if(right && prevRight != right){
		mvprintw(row, col, "  ");

		col += 4;
		if(col > 56)
		{
			col = 55;
		}
		printArrays();
	mvprintw(row, col, "%c", SELECTION);

	}	
	else if(down && prevDown != down){
		mvprintw(row, col, "  ");

		row += 2;
		if(row > 15){
			row = 15;
		}
		printArrays();
	mvprintw(row, col, "%c", SELECTION);

	}
	else if(up && prevUp != up){
		mvprintw(row, col, "  ");

		row -= 2;
		if(row < 5){
			row = 5;
		}
		printArrays();
	mvprintw(row, col, "%c", SELECTION);
	
	}

	if(x && prevX != x){
		printArrays();
		return shoot(row, col);
		
	}
	else if(triangle && prevTriangle != triangle){
		
	}
	else if(square && prevSquare != square){
		
	}
	else if(circle && prevCircle != circle){
		
	}

	
	refresh();
	prevLeft = left;
	prevRight = right;
	prevUp = up;
	prevDown = down;
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
	
}

/**
updates the map and 
	return -1 for miss
	return 1 for hit
**/
int shoot(int player, int row, int col){ //grid is the computer's boat array
	if(player == PLAYER){
		if(cpuShips[row][col] == BOAT){
			cpuShips[row][col] = HIT;
			playerGuesses[row][col] = HIT;
			return 1;
		}
		else{
			cpuShips[row][col] = MISS;
			playerGuesses[row][col] = MISS;
			return -1;
		}
	}
	else{
		if(playerShips[row][col] == BOAT){
			playerShips[row][col] = HIT;
			cpuGuesses[row][col] = HIT;
			return 1;
		}
		else{
			playerShips[row][col] = MISS;
			cpuGuesses[row][col] = MISS;
			return -1;
		}
	}
	
	
}


void cpu_win(){
	
}
void human_win(){
	
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
			mvprintw(row, column, "%c", playerGuesses[g][h]); //prints the array for player guesses
			refresh();
			column += 4;
		}
		row += 2;
		column = 35;
	}
	
	refresh();
	return 0;
}

void initGrid(){
	for(int i = 0; i < 6; i++){
		for (int j = 0; j < 6; j++){
			playerShips[i][j] = '-';
			playerGuesses[i][j] = '-';
			cpuShips[i][j] = '-';
			cpuGuesses[i][j] = '-';
		}
	}
}

