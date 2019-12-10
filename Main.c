	#include <stdio.h>
	#include <math.h>
	#include <ncurses.h>
	#include <time.h>
	#include <stdlib.h>
	#include <string.h>


	
	
	
	
	

	const char EMPTY = '-';
	const char HIT = 'X';
	const char MISS = '!';
	const char BOAT = 'O';
	const char  SELECTION = 'W';


	int game_loop(); // for controlling the portion of the game where the game is in play
	int player_turn();//for organizing events while it is the player's turn
	int cpu_turn(); // for organizing events while it is the computer's turn
	int cpu_win(); //for checking if the computer won the game
	int human_win(); //for checking if the player won the game
	int shoot(); //"shoots" the inputted array of ships, returns if it is hit, or miss
	int printArrays();//prints the arrays
	void initGrid();//fills the arrays with empty spots
	void userBoatPlacement();
	int PLAYER = 0;
	int CPU = 1;
	//grids for playing
	char playerShips[6][6];
	char cpuShips[6][6];
	
	char playerGuesses[6][6];
	char cpuGuesses[6][6];
	
	//compile with gcc Main.c -o main.exe -lncurses
	//run with  ./ds4rd.exe -d 054c:05c4 -D DS4_BT -t -b -bd -bt | ./main.exe
int main(){
	
	srand(time(NULL));
	
	initscr();
	initGrid();
	userBoatPlacement();
	clear();
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
	printArrays();
	while(1){
		printArrays();
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
	int gridRow = 0;
	int gridCol = 0;
	int row = 5;
	int col = 35;
	int left, right, up, down, x, triangle, circle, square, button_R3,
		button_L3, button_options, button_share, button_R2, button_L2, button_R1, button_L1  = 0;
	int prevLeft, prevRight, prevUp, prevDown, prevX, prevTriangle, prevCircle, prevSquare = 0;
	int timer;
	mvprintw(row, col, "%c", SELECTION);
	refresh();
	
	
	while(1){
		scanf("%d, %d,%d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d, %d,%d,%d,%d", &timer, 
		&triangle, &circle, &x, &square, &button_R3, &button_L3, &button_options,
		&button_share, &button_R2, &button_L2, &button_R1, &button_L1, &up, &left, &down, &right);
	//read controller, use this to move the pointers location along the screen.	
	//then call shoot to update the grids and return the output.
	if(left && prevLeft != left){
		mvprintw(row +2, col+2, "  ");
		col -= 4;
		gridCol--;
		if(col < 35){
			col = 35;
			gridCol++;
		}
		printArrays();
		mvprintw(row, col, "%c", SELECTION);
	}
	else if(right && prevRight != right){
		mvprintw(row, col, "  ");
		col += 4;
		gridCol++;
		gridCol++;
		if(col > 56)
		{
			col = 55;
			gridCol--;
		}
		printArrays();
	mvprintw(row, col, "%c", SELECTION);

	}	
	else if(down && prevDown != down){
		mvprintw(row, col, "  ");
		row += 2;
		gridRow++;
		if(row > 15){
			row = 15;
			gridRow--;
		}
		printArrays();
	mvprintw(row, col, "%c", SELECTION);

	}
	else if(up && prevUp != up){
		mvprintw(row, col, "  ");
		
		row -= 2;
		gridRow--;		

		if(row < 5){
			row = 5;
			gridRow++;
		}
		printArrays();
	mvprintw(row, col, "%c", SELECTION);
	
	}

	if(x && prevX != x){
		return shoot(PLAYER, gridRow, gridCol);

		
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
	int tempRow;
	int tempCol;
	
	while (1) {
		tempRow = rand() % 6;
		tempCol = rand() % 6; //random guess on grid
	
		if ((playerShips[tempRow][tempCol] == 'X')|| (playerShips[tempRow][tempCol] == '*')){ //if the computer has already guessed there
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


int cpu_win(){
	int count = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (playerShips[i][j] == 'X'){ //count all of the computer's hits
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
int human_win(){
	int count = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (playerGuesses[i][j] == 'X'){ //count all of the player's hits
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
			playerShips[i][j] = EMPTY;
			playerGuesses[i][j] = EMPTY;
			cpuShips[i][j] = EMPTY;
			cpuGuesses[i][j] = EMPTY;
		}
	}
}

void userBoatPlacement(){
	int i, j;
	
	int millisec, triangle, circle, cross, square, button_R3, button_L3, button_options, button_share, button_R2, button_L2, button_R1, button_L1, dPad_up, dPad_left, dPad_down, dPad_right;
	int allignment = 0;
	int x_position = 3;
	int y_position = 3; 
	int shipLength = 3;
	int clear;
	
	for(i=0; i<=5; ++i){
		for (j=0; j<=5; ++j){
			//playerShips[i][j] = EMPTYSPACE;
			playerShips[i][j] = '*';
		}
	}//initialize all values
	
	while(1){
		
		scanf("%d, %d,%d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d, %d,%d,%d,%d", &millisec, &triangle, &circle, &cross, &square, &button_R3, &button_L3, &button_options, &button_share, &button_R2, &button_L2, &button_R1, &button_L1, &dPad_up, &dPad_left, &dPad_down, &dPad_right);
		if(dPad_up == 1){
			while(dPad_up==1){
				scanf("%d, %d,%d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d, %d,%d,%d,%d", &millisec, &triangle, &circle, &cross, &square, &button_R3, &button_L3, &button_options, &button_share, &button_R2, &button_L2, &button_R1, &button_L1, &dPad_up, &dPad_left, &dPad_down, &dPad_right);
			}//wait until button is not pressed
			
			if (allignment%2 && y_position >= shipLength){
				--y_position;
			}else if(!(allignment%2) && y_position > 0){
				--y_position;
			}
			
		}//if 
		if(dPad_left == 1){
			while(dPad_left==1){
				scanf("%d, %d,%d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d, %d,%d,%d,%d", &millisec, &triangle, &circle, &cross, &square, &button_R3, &button_L3, &button_options, &button_share, &button_R2, &button_L2, &button_R1, &button_L1, &dPad_up, &dPad_left, &dPad_down, &dPad_right);
			}//wait until button is not pressed
			
			if(x_position > 0){
				--x_position;
			}
			
		}//if 
		if(dPad_down == 1){
			while(dPad_down==1){
				scanf("%d, %d,%d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d, %d,%d,%d,%d", &millisec, &triangle, &circle, &cross, &square, &button_R3, &button_L3, &button_options, &button_share, &button_R2, &button_L2, &button_R1, &button_L1, &dPad_up, &dPad_left, &dPad_down, &dPad_right);
			}//wait until button is not pressed
			
			if(y_position < 5){
				++y_position;
			}
				
		}//if 
		if(dPad_right == 1){
			while(dPad_right==1){
				scanf("%d, %d,%d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d, %d,%d,%d,%d", &millisec, &triangle, &circle, &cross, &square, &button_R3, &button_L3, &button_options, &button_share, &button_R2, &button_L2, &button_R1, &button_L1, &dPad_up, &dPad_left, &dPad_down, &dPad_right);
			}//wait until button is not pressed
			
			if (!(allignment%2) && x_position < 6-shipLength){
				++x_position;
			}else if(allignment%2 && x_position < 5){
				++x_position;
			}		
			
		}//if 
		if(circle == 1){
			while(circle==1){
				scanf("%d, %d,%d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d, %d,%d,%d,%d", &millisec, &triangle, &circle, &cross, &square, &button_R3, &button_L3, &button_options, &button_share, &button_R2, &button_L2, &button_R1, &button_L1, &dPad_up, &dPad_left, &dPad_down, &dPad_right);
			}//wait until button is not pressed
			
				if (allignment%2 && x_position <= 6-shipLength){
					++allignment;
					//verticle to horizontal
				}else if (!(allignment%2) && y_position >= shipLength-1){
					++allignment;
					//horizontal to verticle
				}
				
				
			
		}//if
		if(cross == 1){
			while(cross==1){
				scanf("%d, %d,%d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d, %d,%d,%d,%d", &millisec, &triangle, &circle, &cross, &square, &button_R3, &button_L3, &button_options, &button_share, &button_R2, &button_L2, &button_R1, &button_L1, &dPad_up, &dPad_left, &dPad_down, &dPad_right);
			}//wait until button is not pressed
			
			--shipLength;
			
			if (shipLength == -1){
				break;
			}
			clear = 1;
			
			//check if boat is there
			if(allignment%2){
				for(i=0;i<=shipLength;++i){
					if(playerShips[y_position-i][x_position]=='='){
						clear = 0;
						++shipLength;
						break;
					}
				}
			}//check if boat verticle
			
			if(!(allignment%2)){
				for(i=0;i<=shipLength;++i){
					if(playerShips[y_position][x_position+i]=='='){
						clear = 0;
						++shipLength;
						break;
					}
				}
			}//check if boat Horizontal
			
			if(allignment%2 && clear){
				for(i=0;i<=shipLength;++i){
					playerShips[y_position-i][x_position]='=';
				}
			}//place boat verticle
	
			if(!(allignment%2) && clear){
				for(i=0;i<=shipLength;++i){
					playerShips[y_position][x_position+i]='=';
				}
			}//place boat horizontal
		
		}
		
	for(i=0; i<=5; ++i){
		for (j=0; j<=5; ++j){
			
			mvaddch(i*2, j*3, playerShips[i][j]);
			
		}
	}//Prints array
	refresh();
	
	if(allignment%2){
		for(i=0;i<shipLength;++i){
			mvaddch((y_position-i)*2, x_position*3, 'A');
		}
	}//showing where ship will be verticle
	
	if(!(allignment%2)){
		for(i=0;i<shipLength;++i){
			mvaddch(y_position*2, (x_position+i)*3, 'A');
		}
	}//showing where ship will be horizontal
	mvprintw(20, 0, "%d", allignment);
	refresh();
	
	}//while 1
}

