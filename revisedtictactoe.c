#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

const char c='.';

char human, compu, cells[9]={	c,c,c,
								c,c,c,
								c,c,c };
bool x;


int gui(void);//graphical interface

int checkwinmv(char player);// check win move(cwm)

int gamecnt();//check if anybody won

int randomnumber();//get a random number from 0-8

int draw();//check if its a draw

int main(){
	int  userin=0;;
		int alreadytaken[9]={9,9,9,9,9,9,9,9,9};//do not change these, while taking input, it compares inputs to these. 
		int arrin=0;
		
		printf("what would you like to play as?(x or o)\n");
		scanf("%c", &human);
		if(human=='x'){
			compu='o';
		}
		else if(human=='o'){
			compu='x';
		}
		
		
		printf("The tic tac toe grid looks like this\n");
		gui();
		
		while(gamecnt()==1){//taking input
			x= true;
			while(x){
				scanf("%d", &userin);
				
				if(userin >=0 && userin <=8){
					x=false;
					
				}
				else{
					printf("input must be within 0-8\n");
				}
				
				for(int i=0; i<8;i++){
					if(userin==alreadytaken[i]){
						x=true;
						printf("already taken\n");
						
					}
				}
			}
			
			cells[userin]=human; //userinput
			alreadytaken[arrin]=userin;
			arrin++;
			
			printf("your move\n");
			
			gui();
				
			if(gamecnt()!=1){
				printf("you win");
				return 0;
			}
			else if(draw()==1){
				printf("It's a draw");
			}
				

			if(checkwinmv(compu)!= 69){
				alreadytaken[arrin]=checkwinmv(compu);
				arrin++;
				cells[checkwinmv(compu)]=compu;
			}
			else if(checkwinmv(human)!= 69){
				alreadytaken[arrin]=checkwinmv(human);
				arrin++;
				cells[checkwinmv(human)]=compu;
			}		
			else{
				
				cells[randomnumber()]=compu;	
			}
			
			
			printf("the computer makes its it move\n");
			
			gui();
			
			if(gamecnt()!=1){
				printf("compu wins");
				return 0;
			}
			else if(draw()==1){
				printf("It's a draw");
			}
		}
		
return 69;
}

int randomnumber(){
	srand(time(0));
	while(1){
		int r =rand() %9;
		if(cells[r]==c){
		
			return r;
		}
	}
	
}

int gui(void){
			printf("       0    1    2  \n");
			printf("    ----------------\n");
			printf("  0 | %c  | %c  | %c  | 2 \n", cells[0],cells[1], cells[2]);
			printf("    ---------------- \n");
			printf("  3 | %c  | %c  | %c  | 5 \n", cells[3],cells[4], cells[5]);
			printf("    ---------------- \n");
			printf("  6 | %c  | %c  | %c  | 8 \n", cells[6],cells[7], cells[8]);
			printf("    ---------------- \n");
			printf("       6    7    8  \n");
	return 0;
}

int draw(){
	int cnt0=0;
	for(int i=0;i<9;i++){
		if(cells[i]==c){
			cnt0++;

		}
	}
	if(cnt0==1){
		return 1;
	}
	return 0;
}

int checkwinmv(char player){
	char enemy;
	if(player=='o'){
		enemy='x';
	}
	else if(player=='x'){
		enemy='o';
	}
	int free=0;
	int cnt=0;
	//left to right
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 */	
	for(int i=0;i<9;i++){
		if(i==3 || i==6){
			cnt=0;
		}
		
		if(cells[i]==player){
			cnt++;
		}
		if(cells[i]!=player){
			free=i;
		}
		if(i==2||i==5||i==8){
			if(cells[free]!=enemy){
				if(cnt==2){
					return free;
				}
			}
		}
	}
	//top to bottom
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 */	
	for(int j=0;j<3;j++){
		
		for(int i=j;i<9;i+=3){
			if(i==0||i==1 || i==2){
				cnt=0;
			}
			
			if(cells[i]==player){
				cnt++;
			}
			if(cells[i]!=player){
				free=i;
			}
			if(i==6||i==7||i==8){
				if(cells[free]!=enemy){
					if(cnt==2){
						return free;
					}
				}
				
			}
		}
	}
	//left top to right bot cornering
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 */	
	 cnt=0;
	 for(int i=0;i<9;i+=4){
		 
		
		if(cells[i]==player){
			cnt++;
		}
		if(cells[i]!=player){
			free=i;
		}
		if(i==8 && cnt==2){
			
			if(cells[free]!=enemy){
				return free;
			}
			
		}
	}
	//right top to left bot cornering
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 */	
	 cnt=0;
	 for(int i=2;i<7;i+=2){
		  if(i==2){
			cnt=0;
		}
		if(cells[i]==player){
			cnt++;
		}
		if(cells[i]!=player){
			free=i;
		}
		if(i==6 && cnt==2){
			if(cells[free]!=enemy){
				return free;
			}
			
		}
	}
	return 69;
}
int gamecnt(){
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 */
	
	for(int i=0;i<7;i+=3){
		if(cells[i]!=c){
			if(cells[i]== cells[i+1] && cells[i+1]==cells[i+2]){
				return 0;
			}
		}
		
	}
	for(int i=0;i<3;i++){
		if(cells[i]!=c){

			if(cells[i]== cells[i+3] && cells[i+3]==cells[i+6]){
				return 0;
			}
		}
	}
	
	if(cells[4]!=c){
		if(cells[0]== cells[4] && cells[4]==cells[8]){
			return 0;
		}

		else if(cells[2]== cells[4] && cells[4]==cells[6]){
			return 0;
		}
	}
	return 1;
}
