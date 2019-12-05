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
	int printArrays();

	int PLAYER = 0;
	int CPU = 1;
	//grids for playing
	char playerShips[6][6];
	char cpuShips[6][6];
	char playerGuesses[6][6];
	char cpuGuesses[6][6];
	
int main(){
	
	game_loop();
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
	
}

/**
updates the map and 
	return -1 for miss
	return 1 for hit
**/
int shoot(int player){
	
}


void cpu_win(){
	
}
void human_win(){
	
}

int printArrays(){
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 6; j++){
			printf("%c   ", playerShips[i][j]); //prints the array for the player ships
		}
		printf("\n\n");
	}
	printf("\n\n\n");
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 6; j++){
			printf("%c   ", playerGuesses[i][j]); //prints the array for player guesses
		}
		printf("\n\n");
	}
	return 0;
}

