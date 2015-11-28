/*Libraries used in program*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*Structures*/
typedef struct
{
	char Name[10];
	char Token[1];
	int Score;
}Player;

/*Function prototypes*/
void PreviousWinner();
void DisplayInstructions(Player Player);
void DisplayBoard(char Board[6][6], char Select[6][6]);
void PlayerInfo(Player Player[4]);
void AssignDefaultBoardValue(Player Player[4], char Board[6][6], char Select[6][6], int row, int col);
void MovementFunction(int *row,int *col,char Select[6][6],char Board[6][6],char *Key, Player Player, int *Valid);
int CheckFunction(int *row,int *col,char Select[6][6],char Board[6][6],char *Key, Player Player, int *Valid);
void SavePlayerScore(Player Player[4]);


void PreviousWinner()
{
	/*Find and scan the Players.txt file then display the scores and names of previous players.*/
	FILE *File = fopen("Players.txt","r");
	
	char Name[90];
	int Steps = 0;

	system("cls");

	if(File == NULL)
	{
		printf("No Previous Record Found.\n");
	}
	else
	{
		printf("\t      Score BOARD\n\n");

		while (fscanf(File,"%s%i", Name,&Steps) == 2)
		{
			printf("\tName:%s\t Steps:%i\n", Name,Steps);
		}
	}
	fclose(File);

}

void DisplayInstructions(Player Player)
{
	/*Function to display instructions*/
	printf("\nScore: %i\n", Player.Score);
	printf("\nPlayer: %s\n", Player.Name);
	printf("\nToken: %s\n", Player.Token);
	printf("\nPress W to move up. \n");
	printf("Press A to move down. \n");
	printf("Press S to move left. \n");
	printf("Press D to move right. \n");
	printf("Press ENTER to select a slot. \n");
	printf("Press P to pass. \n");
	printf("Press Q to quit. \n");
}

void DisplayBoard(char Board[6][6], char Select[6][6])
{
	int x, y;

	/*Function to display the board*/
	for(x=0; x < 6; x++)
	{	
		printf("\n");	
		for(y=0; y < 6; y++)
		{
			printf("%c", Select[x][y]);
			printf("%c", Board[x][y]);
			printf("%c", Select[x][y]);
		}
		printf("\n");  	    	
	}
}

void PlayerInfo(Player Player[4])
{	
	int x;
	for(x=0; x!=4; x++)
	{
		printf("\nPlease enter player %i's name:",x+1);
		scanf(" %s",Player[x].Name);
		fflush(stdin);

		printf("Hello %s,please choose a token:",Player[x].Name);
		scanf(" %c",Player[x].Token);
		fflush(stdin);
		Player[x].Score = 0;
	}
} 

void AssignDefaultBoardValue(Player Player[4], char Board[6][6], char Select[6][6], int row, int col)
{
	int x, y;

	//assign value to board
	for(x=0;x<6;x++)
	{
		for(y=0;y<6;y++)
		{
		  	Board[x][y]=' ';
		  	Select[x][y]=' ';
		}
	}

	Board[0][0] = *Player[0].Token;
 	Board[0][5] = *Player[1].Token;
 	Board[5][0] = *Player[2].Token;
	Board[5][5] = *Player[3].Token;

	// printf("%s\n",*Player[0].Token );
	// printf("%s\n",*Player[1].Token );
	// printf("%s\n",*Player[2].Token );
	// printf("%s\n",*Player[3].Token );

	Select[row][col]= '|';	 
}

void MovementFunction(int *row,int *col,char Select[6][6],char Board[6][6],char *Key, Player Player, int *Valid)
{
	system("cls");
	DisplayBoard(Board, Select);
	DisplayInstructions(Player);

	/*Function to get user input and move selection accordingly*/
	/*Loops until 'q', 'p' or Enter key is pressed*/
	do
	{
		
		*Key = getch();
		
		if((*Key == 115 || *Key == 83) && *row != 6) 
		{
			system("cls");
			*row = *row + 1;
			Select[*row][*col]= '|';
			Select[*row-1][*col]= ' ';

			DisplayBoard(Board, Select);
			DisplayInstructions(Player);

			fflush(stdin);
		}
		else if((*Key == 119 || *Key == 87) && *row != 0 )
		{
			system("cls");
			*row = *row - 1;
			Select[*row][*col]= '|';
			Select[*row+1][*col]= ' ';

			DisplayBoard(Board, Select);
			DisplayInstructions(Player);

			fflush(stdin);
		}
		else if((*Key == 97 || *Key == 65) && *col != 0)
		{
			system("cls");
			*col = *col - 1;
			Select[*row][*col]= '|';
			Select[*row][*col+1]= ' ';

			DisplayBoard(Board, Select);
			DisplayInstructions(Player);
			

			fflush(stdin);
		}
		else if((*Key == 100 || *Key == 68) && *col != 6)
		{
			system("cls");
			*col = *col + 1;
			Select[*row][*col]= '|';
			Select[*row][*col-1]= ' ';

			DisplayBoard(Board, Select);
			DisplayInstructions(Player);

			fflush(stdin);

		}

		else if(*Key == 113 || *Key == 81)
		{
			// PlayerFunction(Name,Score);
			// ReadPlayerFunction();
			// exit(0);
			*Valid = 1;
			break;
		}
		else if(*Key == 112 || *Key == 80)
		{
			*Valid = 1;
			break;
		}
	}while(*Key != 13);
}

int CheckFunction(int *row,int *col,char Select[6][6],char Board[6][6],char *Key, Player Player, int *Valid)
{

	//(Board[*row][*col] == ' ' && (Board[*row-1][*col] == *Player.Token  || Board[*row+1][*col] == *Player.Token  || Board[*row][*col-1] == *Player.Token  || Board[*row][*col+1] == *Player.Token))
	//Above is vertical and horizontal checks


	if (Board[*row][*col] == ' ' && (Board[*row-1][*col-1] == *Player.Token  || Board[*row+1][*col+1] == *Player.Token  || Board[*row+1][*col-1] == *Player.Token  || Board[*row-1][*col+1] == *Player.Token))
	{
		Board[*row][*col] = *Player.Token;
		Player.Score = Player.Score + 1;
		*Valid = 1;
	}
	else if(*Valid == 1)
	{
		*Valid = 1;
	}
	else
	{
		*Valid = 0;
		printf("Invalid Move\n");
	}

	return Player.Score;
}

void SavePlayerScore(Player Player[4])
{
	/*Save a .txt file called Players which stores the name and score of people who have played.*/
	FILE *File = fopen("Players.txt","a");

	int HighScore = 0;

	int x;

	for (x = 0; x < 4; ++x)
	{
		if (Player[x].Score > HighScore)
		{
			HighScore = Player[x].Score;
		}
	}

	for (x = 0; x < 4; ++x)
	{
		if (Player[x].Score == HighScore)
		{
			fprintf(File,"%s\t\t%i\t\n", Player[x].Name, Player[x].Score);
		}
	}

	fclose(File);
}

int main()
{
	/*Set colour to green*/
	system("Color 2");

	char Board[6][6];
	char Select[6][6];
	Player Players[4];

	char Key;
	int Valid = 0;
	int col = 3,row=3 ;
	int PlayerNumber;

	PreviousWinner();
	PlayerInfo(Players);
	AssignDefaultBoardValue(Players, Board, Select, row, col);

	do
	{

		Valid = 0;

		for (PlayerNumber = 0; PlayerNumber < 4; ++PlayerNumber)
		{
			do
			{
				MovementFunction(&row, &col, Select, Board, &Key, Players[PlayerNumber], &Valid);
				Players[PlayerNumber].Score = CheckFunction(&row, &col, Select, Board, &Key, Players[PlayerNumber], &Valid);
			}while(Valid == 0);
		}

	}while (Key != 113);

	SavePlayerScore(Players);

	
	
	printf("Thank You For Playing!!!\n");

	getch();
	return 0;
}
