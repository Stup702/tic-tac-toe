/*
 * Unbeatabletictactoe.c
 *
 * Copyright 2024 Animesh <stup@Excaliper>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA. 
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

const char c='.';


#define newl printf("\n\n");


#ifdef _WIN32
    #define clear "cls"
#endif

#ifdef __linux__
    #define clear "clear"
#endif
int getcrncnt=0;

int edge[4]= {1,3,5,7};



char human, compu, cells[9]= {	'.','.','.',
                                '.','.','.',
                                '.','.','.'
                             };//const expressions somehow doesnt work in mingw.Well whatever

int gui(void);//graphical interface

int checkwinmv(char player);// check win move(cwm)

int gamecnt();//check if anybody won

int randomnumber();//get a random number from 0-8

int draw();//check if its a draw

int getthecorners(char player);//getting the corners first to win

int theoneandonly(char player);//To foil the only possible winning moves


int main()
{
    system(clear);
    printf("         WELCOME TO ANIMESH'S CHALLENGE\n\n");
    printf("You win only when you win. If it's a draw, you lose\n\n");
    printf("!!!While playing only input single numbers\n\n");
    while(1) {
        getcrncnt=0;

        for(int i=0; i<9; i++) { //reallocate for new game+
            cells[i]=c;
        }

        bool x;


        int l=0,pr=0;




        int  userin=0,t=0;
        char go, gofirst='0';





        int alreadytaken[9]= {9,9,9,9,9,9,9,9,9}; //do not change these, while taking input, it compares inputs to these.

        int arrin=0;

        while(1) { //check if player wants to play as x or o with error handling
            printf("what would you like to play as?(x or o)\n");
            scanf(" %c", &human);
            if(human=='x') {
                compu='o';
                break;
            } else if(human=='o') {
                compu='x';
                break;
            } else {
                printf("Wrong response. Try again\n");
            }
        }
        while(1) { //check if player wants to go first or not
            printf("Would you like to go first?(y/n)\n");
            scanf(" %c",&gofirst);
            if(gofirst=='y') {
                break;
            } else if(gofirst=='n') {
                getthecorners(compu);
                printf("The computer has gone first\n");
                break;
            } else {
                printf("Wrong response. Try again\n");
            }


        }




        printf("The tic tac toe grid looks like this\n");
        gui();

        while(gamecnt()==1) { //taking input
            x= true;
            while(x) {

                printf("Make your move\n");

                if(scanf("%d", &userin)!=1) {
                    continue;
                }

                if(userin >=0 && userin <=8) {
                    x=false;

                } else {
                    printf("input must be within 0-8\n");
                    continue;
                }

                for(int i=0; i<8; i++) {
                    if(userin==alreadytaken[i]) {
                        x=true;
                        printf("already taken\n");

                    }
                }
                if(userin==0 ||userin==2 || userin== 6 ||userin==8 ) {

                    l++;

                }

            }



            cells[userin]=human; //userinput

            alreadytaken[arrin]=userin;

            arrin++;

            printf("your move\n");

            gui();

            if(gamecnt()!=1) {
                printf("you win\n");
                t=1;
                goto gg;
            } 
            else if(draw()==1) {
                printf("It's a draw. So, you lose.\n");
                t=1;
                goto gg;
            }



            //main part

            if(checkwinmv(compu)!= 69) {
                alreadytaken[arrin]=checkwinmv(compu);
                arrin++;
                cells[checkwinmv(compu)]=compu;
            } else if(checkwinmv(human)!= 69) {
                alreadytaken[arrin]=checkwinmv(human);
                arrin++;
                cells[checkwinmv(human)]=compu;

            }


            else if(l==1 && cells[4]==c) {
                if(userin==0 ||userin==2 || userin== 6 ||userin==8 ) {

                    cells[4]=compu;
                    alreadytaken[arrin]=4;
                    arrin++;
                    l++;

                }
            } else if(theoneandonly(human)!=69&& pr==0) {
                pr++;
                alreadytaken[arrin++]=theoneandonly(human);
                cells[theoneandonly(human)]=compu;
            } else if(l==3) {
                for(int i=0; i<4; i++) {
                    if(cells[edge[i]]==c ) {
                        cells[edge[i]]=compu;
                        l++;
                        alreadytaken[arrin]=edge[i];
                        arrin++;
                        break;

                    }
                }
            }

            else {
                if(cells[4]==c) {
                    cells[4]=compu;
                    alreadytaken[arrin]=4;
                    arrin++;
                } else if(getcrncnt<=3) {

                    alreadytaken[arrin]=getthecorners(compu);
                    arrin++;
                } else {
                    cells[randomnumber()]=compu;

                }

            }


            printf("the computer makes its move\n");

            gui();

            if(gamecnt()!=1) {
                printf("compu wins\n");
                t=1;
                goto gg;

            } else if(draw()==1) {
                printf("It's a draw. So, you lose\n");
                t=1;
                goto gg;


            }
		}
		gg:
		if(t==1) {
			printf("Are you unsatisfied?\nWanna have another go?(y or n)\n\n");
			while(1) {
				scanf(" %c",&go);
				if(go=='y') {
					
					break;
				} else if(go=='n') {
					return 0;
				} else {
					printf("Wrong response. Please try again\n");
				}
			}
			t=0;
		}



        

    }
}

int theoneandonly(char player)
{

    if(cells[1]==player) {
        if(cells[0]==c) {
            return 0;
        } else if(cells[2]==c) {
            return 2;
        }
    }
    if(cells[3]==player) {
        if(cells[0]==c) {
            return 0;
        } else if(cells[6]==c) {
            return 6;
        }
    }
    if(cells[5]==player) {
        if(cells[2]==c) {
            return 2;
        } else if(cells[8]==c) {
            return 8;
        }
    }
    if(cells[7]==player) {
        if(cells[6]==c) {
            return 6;
        } else if(cells[8]==c) {
            return 8;
        }
    }
    return 69;

}

int randomnumber()
{
    srand(time(0));
    while(1) {
        int r =rand() %9;
        if(cells[r]==c) {

            return r;
        }
    }

}

int gui(void)
{
    system("clear");
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

int draw()
{
    int cnt0=0;
    for(int i=0; i<9; i++) {
        if(cells[i]==c) {
            cnt0++;

        }
    }
    if(cnt0==1) {
        return 1;
    }
    return 0;
}

int checkwinmv(char player)
{
    char enemy;
    if(player=='o') {
        enemy='x';
    } else if(player=='x') {
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
    for(int i=0; i<9; i++) {
        if(i==3 || i==6) {
            cnt=0;
        }

        if(cells[i]==player) {
            cnt++;
        }
        if(cells[i]!=player) {
            free=i;
        }
        if(i==2||i==5||i==8) {
            if(cells[free]!=enemy) {
                if(cnt==2) {
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
    for(int j=0; j<3; j++) {

        for(int i=j; i<9; i+=3) {
            if(i==0||i==1 || i==2) {
                cnt=0;
            }

            if(cells[i]==player) {
                cnt++;
            }
            if(cells[i]!=player) {
                free=i;
            }
            if(i==6||i==7||i==8) {
                if(cells[free]!=enemy) {
                    if(cnt==2) {
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
    for(int i=0; i<9; i+=4) {


        if(cells[i]==player) {
            cnt++;
        }
        if(cells[i]!=player) {
            free=i;
        }
        if(i==8 && cnt==2) {

            if(cells[free]!=enemy) {
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
    for(int i=2; i<7; i+=2) {
        if(i==2) {
            cnt=0;
        }
        if(cells[i]==player) {
            cnt++;
        }
        if(cells[i]!=player) {
            free=i;
        }
        if(i==6 && cnt==2) {
            if(cells[free]!=enemy) {
                return free;
            }

        }
    }
    return 69;
}
int gamecnt()
{
    /*reference
     * 0 1 2
     * 3 4 5
     * 6 7 8
     */

    for(int i=0; i<7; i+=3) {
        if(cells[i]!=c) {
            if(cells[i]== cells[i+1] && cells[i+1]==cells[i+2]) {
                return 0;
            }
        }

    }
    for(int i=0; i<3; i++) {
        if(cells[i]!=c) {

            if(cells[i]== cells[i+3] && cells[i+3]==cells[i+6]) {
                return 0;
            }
        }
    }

    if(cells[4]!=c) {
        if(cells[0]== cells[4] && cells[4]==cells[8]) {
            return 0;
        }

        else if(cells[2]== cells[4] && cells[4]==cells[6]) {
            return 0;
        }
    }
    return 1;
}

int getthecorners(char player) //if there are 3 getcrncnt dont call this function
{

    srand(time(0));


    while(1) {
        int r =rand()%4;
        if(r==0) {
            r=0;
        } else if(r==1) {
            r=2;
        } else if(r==2) {
            r=6;
        } else if(r==3) {
            r=8;
        }

        if(cells[r]==c) {
            getcrncnt++;
            cells[r]=player;
            return r;
        }
    }
}
