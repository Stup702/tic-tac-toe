#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
struct cell {
	int x;
	int y;
	char data;
};

int gtccnt=0;
int checkwinmv();
int gamecnt();
int randomnumber();
bool x;

struct cell matrix[9]=	{
					//    a1     b1     c1
						{1,1,0}, {1,2,0}, {1,3,0},
					//    a2     b2     c2
						{2,1,0}, {2,2,0}, {2,3,0},
					//    a3     b3     c3						
						{3,1,0}, {3,2,0}, {3,3,0}
						};


			  
			
			
int main(){
	int  userin=0;;
	int alreadytaken[9]={9,9,9,9,9,9,9,9,9};
	int arrin=0;
	printf("The tic tac toe grid looks like this\n");
	printf("       a    b    c  \n");
	printf("    ---------------- \n");
	printf("  1 | 0 | 1 | 2 | \n");
	printf("    ---------------- \n");
	printf("  2 | 3 | 4 | 5 | \n");
	printf("    ---------------- \n");
	printf("  3 | 6 | 7 | 8 | \n");
	printf("    ---------------- \n");
	
	printf("%d\n",gamecnt());
	while(gamecnt()==1){
		x= true;
		while(x){
			scanf("%d", &userin);
			
			if(userin >=0 && userin <=8){
				x=false;
				
			}
			else{
				printf("input must be within 0-8");
			}
			
			for(int i=0; i<8;i++){
				if(userin==alreadytaken[i]){
					x=true;
					printf("already taken");
					
				}
			}
		}
		
		matrix[userin].data='x'; //userinput
		alreadytaken[arrin]=userin;
		arrin++;

		
		
		printf("your move\n");
		printf("       a    b    c  \n");
		printf("    ---------------- \n");
		printf("  1 | %c  | %c  | %c  | \n", matrix[0].data,matrix[1].data, matrix[2].data);
		printf("    ---------------- \n");
		printf("  2 | %c  | %c  | %c  | \n", matrix[3].data,matrix[4].data, matrix[5].data);
		printf("    ---------------- \n");
		printf("  3 | %c  | %c  | %c  | \n", matrix[6].data,matrix[7].data, matrix[8].data);
		printf("    ---------------- \n");
			
		if(gamecnt()!=1){
			printf("you win");
			return 0;
		}
			
		printf("%d",checkwinmv());
		
			matrix[randomnumber()].data='o';	
		
		
		printf("the computer makes its it move\n");
		printf("       a    b    c  \n");
		printf("    ---------------- \n");
		printf("  1 | %c  | %c  | %c  | \n", matrix[0].data,matrix[1].data, matrix[2].data);
		printf("    ---------------- \n");
		printf("  2 | %c  | %c  | %c  | \n", matrix[3].data,matrix[4].data, matrix[5].data);
		printf("    ---------------- \n");
		printf("  3 | %c  | %c  | %c  | \n", matrix[6].data,matrix[7].data, matrix[8].data);
		printf("    ---------------- \n");
		if(gamecnt()!=1){
			printf("compu wins");
			return 0;
		}
}
return 0;
}

int randomnumber(){
	srand(time(0));
	while(1){
		int r =rand() %9;
		if(matrix[r].data==0){
		
			return r;
		}
	}
	
}

	
int checkwinmv(){
	//***********another feature :>>>>?>>>>>> check for enemy winmvs as well 
				//checks if there are two similar characters on the same line horizontally, vertically and recined
				// if none found, will return 69 
	int free=0;
	
	//comp
	
	
	//left to right
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 */	
	for(int i=0; i<8; i=i+3){
		printf("i is %d\n",i);
		//if i=0, i+1=1,i+2=2 if i=3, i+1=4,i+2=5, if i=6, i+1=7,i+2=8
	
		if(matrix[i].data=='o' && matrix[i].data==matrix[i+1].data){
			free = i+2;
			if(matrix[free].data==0){
				return free;
				
			}
			
		}
		else if(matrix[i].data=='o' && matrix[i].data==matrix[i+2].data){
			free = i+1;
			if(matrix[free].data==0){
				return free;
				
			}
		}
		else if(matrix[i+1].data=='o' && matrix[i+1].data==matrix[i+2].data){
			free = i;
			if(matrix[free].data==0){
				return free;
				
			}
		}
	}
	//top to bottom`
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 **/
	for(int i=0; i<3; i++){
		
		//if i=0, i+3 = 3, i+6= 5.   if i=1, i+3= 4, i+6=7	
		if(matrix[i].data=='o' && matrix[i].data==matrix[i+3].data){
			free = i+6;
			if(matrix[free].data==0){
				return free;
				
			}
		}
		else if(matrix[i].data=='o' && matrix[i].data==matrix[i+6].data){
			free = i+3;
			if(matrix[free].data==0){
				return free;
				
			}
		}
		else if(matrix[i+3].data=='o' && matrix[i+3].data==matrix[i+6].data){
			free = i;
			if(matrix[free].data==0){
				return free;
				
			}
		}
	}
	
	//top left to bot right corner 0-8
	
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 */	
	
	
		if(matrix[0].data=='o' && matrix[0].data==matrix[4].data){
			free = 8;
			if(matrix[free].data==0){
				return free;
				
			}
			
		}
		else if(matrix[0].data=='o' && matrix[0].data==matrix[8].data){
			free = 4;
			if(matrix[free].data==0){
				return free;
				
			}
		}
		else if(matrix[4].data=='o' && matrix[4].data==matrix[8].data){
			free = 0;
			if(matrix[free].data==0){
				return free;
				
			}
		}
		//top right to bot left corner 
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 */	
	
	
		if(matrix[2].data=='o' && matrix[2].data==matrix[4].data){
			free = 6;
			if(matrix[free].data==0){
				return free;
				
			}
			
		}
		else if(matrix[2].data=='o' && matrix[2].data==matrix[6].data){
			free = 4;
			if(matrix[free].data==0){
				return free;
				
			}
		}
		else if(matrix[4].data=='o' && matrix[4].data==matrix[6].data){
			free = 2;
			if(matrix[free].data==0){
				return free;
				
			}
		}


//enemy mv
	//left to right
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 */	
	for(int i=0; i<8; i=i+3){
		printf("i is %d\n",i);
		//if i=0, i+1=1,i+2=2 if i=3, i+1=4,i+2=5, if i=6, i+1=7,i+2=8
	
		if(matrix[i].data=='x' && matrix[i].data==matrix[i+1].data){
			free = i+2;
			if(matrix[free].data==0){
				return free;
				
			}
			
		}
		else if(matrix[i].data=='x' && matrix[i].data==matrix[i+2].data){
			free = i+1;
			if(matrix[free].data==0){
				return free;
				
			}
		}
		else if(matrix[i+1].data=='x' && matrix[i+1].data==matrix[i+2].data){
			free = i;
			if(matrix[free].data==0){
				return free;
				
			}
		}
	}
	//top to bottom`
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 **/
	for(int i=0; i<3; i++){
		
		//if i=0, i+3 = 3, i+6= 5.   if i=1, i+3= 4, i+6=7	
		if(matrix[i].data=='x' && matrix[i].data==matrix[i+3].data){
			free = i+6;
			if(matrix[free].data==0){
				return free;
				
			}
		}
		else if(matrix[i].data=='x' && matrix[i].data==matrix[i+6].data){
			free = i+3;
			if(matrix[free].data==0){
				return free;
				
			}
		}
		else if(matrix[i+3].data=='x' && matrix[i+3].data==matrix[i+6].data){
			free = i;
			if(matrix[free].data==0){
				return free;
				
			}
		}
	}
	
	//top left to bot right corner 0-8
	
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 */	
	
	
		if(matrix[0].data=='x' && matrix[0].data==matrix[4].data){
			free = 8;
			if(matrix[free].data==0){
				return free;
				
			}
			
		}
		else if(matrix[0].data=='x' && matrix[0].data==matrix[8].data){
			free = 4;
			if(matrix[free].data==0){
				return free;
				
			}
		}
		else if(matrix[4].data=='x' && matrix[4].data==matrix[8].data){
			free = 0;
			if(matrix[free].data==0){
				return free;
				
			}
		}
		//top right to bot left corner 
	/*reference
	 * 0 1 2 
	 * 3 4 5
	 * 6 7 8
	 */	
	
	
		if(matrix[2].data=='x' && matrix[2].data==matrix[4].data){
			free = 6;
			if(matrix[free].data==0){
				return free;
				
			}
			
		}
		else if(matrix[2].data=='x' && matrix[2].data==matrix[6].data){
			free = 4;
			if(matrix[free].data==0){
				return free;
				
			}
		}
		else if(matrix[4].data=='x' && matrix[4].data==matrix[6].data){
			free = 2;
			if(matrix[free].data==0){
				return free;
				
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
		if(matrix[i].data=='o' || matrix[i].data=='x'){

		
			if(matrix[i].data== matrix[i+1].data && matrix[i+1].data==matrix[i+2].data){
				return 0;
			}
		}
		
	}
	for(int i=0;i<3;i++){
		if(matrix[i].data=='o' || matrix[i].data=='x'){

			if(matrix[i].data== matrix[i+3].data && matrix[i+1].data==matrix[i+6].data){
				return 0;
			}
		}
	}
	
	if(matrix[0].data=='o' || matrix[0].data=='x'){
		if(matrix[0].data== matrix[4].data && matrix[4].data==matrix[8].data){
			return 0;
		}
	}
	if(matrix[2].data=='o' || matrix[2].data=='x'){

		if(matrix[2].data== matrix[4].data && matrix[4].data==matrix[6].data){
			return 0;
		}
	}
	return 1;
}
	
