
#include <iostream>
using namespace std; 

#define SIDE 3 // Length of the board 
char board[SIDE][SIDE];

int count=1;
int match=0;
char player_1_move=' ';
char player_2_move=' ';
int whoseTurn=0;
int moves=0;
int moveIndex = 0, x, y; 
bool gameOver=false;

pthread_mutex_t mutex_1;   //mutux variable
pthread_t threadID[9];
pthread_t player_1_threadID;
pthread_t player_2_threadID;
pthread_t checkResult_threadID;
int p_1_wins=0;
int p_1_loss=0;
int p_2_wins=0;
int p_2_loss=0;
int Draws=0;

// A function to show the current board status 
void showBoard(char board[][SIDE]) 
{ 
	printf("\n\n"); 
	
	printf("\t\t\t %c | %c | %c \n", board[0][0], 
							board[0][1], board[0][2]); 
	printf("\t\t\t--------------\n"); 
	printf("\t\t\t %c | %c | %c \n", board[1][0], 
							board[1][1], board[1][2]); 
	printf("\t\t\t--------------\n"); 
	printf("\t\t\t %c | %c | %c \n\n", board[2][0], 
							board[2][1], board[2][2]); 

	return; 
} 

// A function to show the instructions 
void showInstructions() 
{ 
	printf("\t\t\t Tic-Tac-Toe\n\n"); 
	printf("Choose a cell numbered from 1 to 9 as below"
			" and play\n\n"); 
	
	printf("\t\t\t 1 | 2 | 3 \n"); 
	printf("\t\t\t--------------\n"); 
	printf("\t\t\t 4 | 5 | 6 \n"); 
	printf("\t\t\t--------------\n"); 
	printf("\t\t\t 7 | 8 | 9 \n\n"); 
	
	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n"); 

	return; 
} 


// A function to initialise the game 
void initialise(char board[][SIDE]) 
{ 

	// Initially the board is empty 
	for (int i=0; i<SIDE; i++) 
	{ 
		for (int j=0; j<SIDE; j++) 
			board[i][j] = ' '; 
	} 
	
} 


// A function that returns true if any of the row 
// is crossed with the same player's move 
bool rowCrossed_X(char board[][SIDE]) 
{ 
	for (int i=0; i<SIDE; i++) 
	{ 
		if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] == 'X') 
			return (true); 
	} 
	return(false); 
} 
bool rowCrossed_O(char board[][SIDE]) 
{ 
	for (int i=0; i<SIDE; i++) 
	{ 
		if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] == 'O') 
			return (true); 
	} 
	return(false); 
} 
// A function that returns true if any of the column 
// is crossed with the same player's move 
bool columnCrossed_X(char board[][SIDE]) 
{ 
	for (int i=0; i<SIDE; i++) 
	{ 
		if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] == 'X') 
			return (true); 
	} 
	return(false); 
} 
bool columnCrossed_O(char board[][SIDE]) 
{ 
	for (int i=0; i<SIDE; i++) 
	{ 
		if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] == 'O') 
			return (true); 
	} 
	return(false); 
} 


// A function that returns true if any of the diagonal 
// is crossed with the same player's move 
bool diagonalCrossed_X(char board[][SIDE]) 
{ 
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] == 'X') {
		return(true); 
	}
		
		
	if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] && 
		board[0][2] == 'X') 
		return(true); 

	return(false); 
} 
bool diagonalCrossed_O(char board[][SIDE]) 
{ 
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] == 'O') 
		return(true); 
		
	if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] && 
		board[0][2] == 'O') 
		return(true); 

	return(false); 
} 


// A function that returns true if any of the diagonal/column/row 
// is crossed with the same player's move 

bool boradCrossed_X(){
	if(columnCrossed_X(board)==true || 
		diagonalCrossed_X(board)==true || 
		rowCrossed_X(board)==true){
		
			return true;
	}else{
		
		return false;
	}
}

bool boradCrossed_O(){
	if(columnCrossed_O(board)==true || 
		diagonalCrossed_O(board)==true || 
		rowCrossed_O(board)==true){
			return true;
	}else{
		return false;
	}
}

//a func to calculate result

void *checkResultThread(void * args){
	pthread_t myID=pthread_self()+(rand()%20);
	cout<<"RESULT Thread ID : "<<myID<<endl;
	if(boradCrossed_X()==true){
		if(player_1_move=='X'){
			cout<<"\nPLAYER 1 WINS\n";
			gameOver=true;
			p_1_wins++;
			p_2_loss++;
			pthread_exit(NULL);
		}else{
			cout<<"\nPLAYER 2 WINS\n";
			gameOver=true;
			p_2_wins++;
			p_1_loss++;
			pthread_exit(NULL);
		}
	}else if(boradCrossed_O()==true){
		if(player_1_move=='O'){
			cout<<"\nPLAYER 1 WINS\n";
			gameOver=true;
			p_1_wins++;
			p_2_loss++;
			pthread_exit(NULL);
		}else{
			cout<<"\nPLAYER 2 WINS\n";
			gameOver=true;
			p_2_wins++;
			p_1_loss++;
			pthread_exit(NULL);
		}
	}
	else if(boradCrossed_X()==false and boradCrossed_O()==false and moves==9){
		cout<<"\nIT's DRAW\n";
		gameOver=true;
		Draws++;
		pthread_exit(NULL);
	}
	pthread_exit(NULL);
}

//get index as input from user to place its item

int getIndex(){
	int block;
	bool goo=true;
	while(goo==true){
		cout<<"Enter Block(1-9) : ";
		cin>>block;
		if(block>=1 && block<=9){
			goo=false;
		}else{
			goo=true;
		}
	}
	return block;
}

//func to perfrom PLAYER 1 

void * player_1_thread(void * args)
{
	
	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}
	

	cout<<"\n\t\t\t PLAYER 1 and Move "<<player_1_move<<"\n\n";
	pthread_t myID=pthread_self()+(rand()%20);
	
	cout<<"PLAYER 1 Thread ID : "<<myID<<endl;
			bool goo=true;
			while(goo==true){
				//input index heere
				moveIndex=getIndex();
				moveIndex--; //to set according to array

				x = moveIndex / SIDE; 
				y = moveIndex % SIDE; 
				if(board[x][y]==' '){
					board[x][y] = player_1_move; 
					goo=false;
				}else{
					goo=true;
				}
			}
			
			printf("PLAYER 1 has put a %c in cell %d\n", 
					player_1_move, moveIndex); 
			showBoard(board); 
			
			moves++;
			cout<<"i am exiting , turn = "<<whoseTurn<<"\n";
		
	
		pthread_mutex_unlock(&mutex_1);
	pthread_exit(NULL);
}

//func to preform PLAYER 2

void * player_2_thread(void * args)
{
	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}

	cout<<"\n\t\t\t PLAYER 2 and Move "<<player_2_move<<"\n\n";
	pthread_t myID=pthread_self()+(rand()%20);
	cout<<"PLAYER 2 Thread ID : "<<myID<<endl;
			bool goo=true;
			while(goo==true){
				//input index heere
				moveIndex=getIndex();
				moveIndex--; //to set according to array

				x = moveIndex / SIDE; 
				y = moveIndex % SIDE; 
				if(board[x][y]==' '){
					board[x][y] = player_2_move; 
					goo=false;
				}else{
					goo=true;
				}
			}
			printf("PLAYER 2 has put a %c in cell %d\n", 
					player_2_move, moveIndex); 
			showBoard(board); 
			
			moves++;
		
		cout<<"i am exiting , turn = "<<whoseTurn<<"\n";
			
		pthread_mutex_unlock(&mutex_1);
	pthread_exit(NULL);
}
// A function to play Tic-Tac-Toe 
void playTicTacToe(int whoseTurn) 
{ 
	// A 3*3 Tic-Tac-Toe board for playing 
	 
	initialise(board); // Initialise the game 
	showInstructions(); // Show the instructions before playing 
	
	int it=0;
	
	// Keep playing till the game is over or it is a draw 
	while (moves<9) 
	{
		
		if (whoseTurn == 1 && count==1) 
		{ 
			printf("\nplayer 1 turn :  %d\n",whoseTurn); 
			pthread_create(&player_1_threadID,NULL,&player_1_thread,NULL);
			pthread_join(player_1_threadID,NULL);
			whoseTurn=2;
			
		} 
		else if (whoseTurn == 2 && count==1)
		{ 
			printf("\nVplayer 2 turn :  %d\n",whoseTurn); 
			pthread_create(&player_2_threadID,NULL,&player_2_thread,NULL);
			pthread_join(player_2_threadID,NULL);
			whoseTurn=1;
		} 

		//chek result here
		
		cout<<"iteration : "<<++it<<endl;
		pthread_create(&checkResult_threadID,NULL,&checkResultThread,NULL);
		pthread_join(checkResult_threadID,NULL);

		if(gameOver==true){
			break;
		}

	} 

	moves=0;
} 


/// A pree processing func to select random player at fisrt

void preProcessing(){
	srand(time(0));
	int player=(rand()%2)+1;

	cout<<"player "<<player<<" is starting the game\n";
	whoseTurn=player;
	
	char move=' ';
	bool goo=true;
	while(goo==true){
		cout<<"Select your move 'O' OR 'X'\n";
		cin>>move;
		if(move=='O' || move=='o'){
			if(player==1){
				player_1_move='O';
				player_2_move='X';
				//count=1;
			}else if(player==2){
				player_2_move='O';
				player_1_move='X';
				//count=0;
			}
			
			goo=false;
		}
		else if(move=='x' || move=='X'){
			if(player==1){
				player_1_move='X';
				player_2_move='O';
			}else if(player==2){
				player_2_move='X';
				player_1_move='O';
			}
			goo=false;
		}
		else{
			goo=true;
		}
	}

	goo=false;

}

// Driver program 
int main() 
{ 
	pthread_mutex_init(&mutex_1,NULL);
	bool Goo=true;
	bool play=true;
	while(play==true){

		Goo=true;
		preProcessing();
		playTicTacToe(whoseTurn); //play game

		cout<<"\n\tTOTAL NO OF GAMES "<<++match<<"\n\n";
		cout<<"\t\t |WINS \t LOST"<<endl;
		cout<<"\tPLAYER_1 |"<<p_1_wins<<"\t"<<p_1_loss<<"\n";
		cout<<"\tPLAYER_2 |"<<p_2_wins<<"\t"<<p_2_loss<<"\n";
		

		cout<<"\n\tTotal DRAWS : "<<Draws<<endl;

		// chek empty blocks
		int empty=0;
		for(int i=0;i<SIDE;++i){
			for(int j=0;j<SIDE;++j){
				if(board[i][j]==' '){
					empty++;
				}
			}
		}

		cout<<"\n\tTOTAL EMPTY BLOCKS : "<<empty<<endl;

		char ch=' ';
		if(gameOver==true){
			
			while(Goo==true){
				cout<<"\n\nIf want to play again press 'Y' else press 'N'\n";
				cin>>ch;

				if(ch=='Y'|| ch=='y'){
					play=true;
					Goo=false;
				}else if(ch=='N' || ch=='n'){
					play=false;
					Goo=false;
				}else{
					Goo=true;
				}
			}
			gameOver=false;
		}


	}


	pthread_mutex_destroy(&mutex_1);
	return (0); 
} 
