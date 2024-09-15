#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// =========================================VARIABLES
int table[9] = {
		0,0,0,
		0,0,0,
		0,0,0		
		};

/*
	1 => X
	2 => O
	0 => empty
*/

static int win[8][3] = { {0,1,2}, {3,4,5}, {6,7,8}, {0,4,8}, {2,4,6}, {0,3,6}, {1,4,7}, {2,5,8} };

// =========================================FUNC_DEC
int addValue(int,char,int); // third parameter check (if it's set 0) if one can win with putting in specific place (first param)
void createTable(void);
void emptySquares(void);
int wonOrLost(void);
void compMove(void);
// =========================================MAIN


int main(){
    printf("--------------------TIC-TAC-TOE--------------------\n");
    int choice;
    int result = -1;
    while(1){
	emptySquares();
	printf("your choice: ");
	scanf("%d",&choice);
	printf("\n");

	addValue(choice,'X',1);
	compMove();
	result = wonOrLost();	

	createTable();
	
	if(result == 0){
	    printf("DRAW :|\n");
	    break;
	}
	else if(result == 1){
	    printf("YOU WON :)\n");
	    break;
	}
	else if (result == 2){
	    printf("YOU LOST :(\n");
	    break;
	}
    }

}


// =========================================FUNC_DEF

int addValue(int place,char chr,int add){
    int res;
    for (int i=0;i<9;i++){
	if (i+1 == place && table[i] == 0){
	    switch(add){
		case 1:
		    if (chr == 'X')
			table[i] = 1;
		    else if (chr == 'O')
			table[i] = 2;
		    
		    break;
		
		case 0:
		    if (chr == 'X'){
			table[i] = 1;
			res = wonOrLost();
			table[i] = 0;
			return res;
		    }
		    else if (chr == 'O'){
			table[i] = 2;
			res = wonOrLost();
			table[i] = 0;
			return res;
		    }
		    
		    break;
	    }
	}
    }
}

void createTable(void){
    for (int i=0;i<9;i++){
	switch(table[i]){
	    case 1:
		printf("[X] ");
		break;
	    case 2:
		printf("[O] ");
		break;
	    default:
		printf("[ ] ");
		break;
	}
	if (i==2 || i==5 || i==8)
	    printf("\n");
    }
}

void emptySquares(void){
    printf("\nempty squares:\n\n");
    for (int i=0;i<9;i++){
	if (!table[i]) {
	    printf("[%d] ",i+1);
	}else{
	    printf("    ");
	}
	if (i==2 || i==5 || i==8)
	    printf("\n");
    }
    printf("\n");
}

int wonOrLost(void){
    int t=0;
    for (int i=0;i<8;i++){
	if (table[win[i][0]] ==1 && table[win[i][1]] == 1 && table[win[i][2]] == 1) {
	    return 1;
	}
	else if (table[win[i][0]] ==2 && table[win[i][1]] ==2 && table[win[i][2]] == 2){
	    return 2;
	}
    }
    for(int i=0;i<9;i++){
	if (table[i]==0)
	    t++;
    }
    if (t==0){
	return 0;
    }
    return -1;
}

void compMove(void){
    srand(time(0));
    
    int empty[9];
    int j = 0;
    for (int i=0;i<9;i++){
	if(table[i] == 0){
	    empty[j] = i;
	    j++;
	}
    }
    
    if (j==0)
	return;	
    
    int random = empty[rand() % j];


    // ============first check for O winning
    for (int i=0;i<j;i++){
	if(addValue(empty[i]+1,'O',0) == 2 ){
	    printf("\n\nwinning pos for [O]: [%d]\n\n",empty[i]+1);
	    addValue(empty[i]+1,'O',1);
	    return;
	}
    }

    // ============then check for X winning
    for (int i=0;i<j;i++){
	if( addValue(empty[i]+1,'X',0) == 1){
	    printf("\n\nwinning pos for [X]: [%d]\n\n",empty[i]+1);
	    addValue(empty[i]+1,'O',1);
	    return;
	}
    }

    addValue(random+1,'O',1);
}
