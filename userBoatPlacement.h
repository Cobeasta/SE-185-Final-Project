#include <stdio.h>
#include <ncurses.h>

void userBoatPlacement(char playerShips[6][6]){
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
