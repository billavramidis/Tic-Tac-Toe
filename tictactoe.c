#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int randomizeFirstPlayer(); //Orizei tyxaia poio tha einai to prwto symbolo
void giveInstructions(); //Dinei tis odhgeies ston paixth
void fillTempBoard(int temp[3][3]); //Gemizei ton parallhlo pinaka
void printBoard(char board[3][6]); //Typwnei ton pinaka me ta symbola
void setCoordinates(int *x1, int *y1, int *x2, int *y2, int choice); //Anathetei stous 2 pinakes tis syntetagmenes
void placeSymbol(char board[3][6], int temp[3][3], int choice, char current_player[2]); //Bazei to symbolo ston pinaka
bool checkIfAlreadyPlayed(int temp[3][3], int choice); //Koitaei an exei hdh ginei mia kinhsh
bool checkIfWin(int temp[3][3]); //Koitaei an yparxei nikh eite orizontia eite katheta eite sthn kyria diagwnio eite sthn deytereyousa diagwnio

int main(){
    int temp[3][3];
    int answer, round, choice, winner, points1, points2, horizontal_condition;
    int first_player;
    char first_symbol[2], second_symbol[2], current_player[2], first_name[15], second_name[15];


    giveInstructions();
    first_player = randomizeFirstPlayer();

    if (first_player == 1){
        first_symbol[0] = 'X';
        second_symbol[0] = 'O';
    }
    else{
        first_symbol[0] = 'O';
        second_symbol[0] = 'X';
    }
    printf("Give the name of the first player: ");
    gets(first_name);
    printf("Give the name of the second player: ");
    gets(second_name);

    points1 = 0;
    points2 = 0;

    do{
        round = 0; //Xrhsimopoiw round epeidh o megistos arithmos gyrwn poy mporoun na ginoun einai 9
        fillTempBoard(temp);
        char board[3][6] = {
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '}
        };

        do{
           round++;
           if (round % 2 == 1) //Ta symbola einai enallax opote apla koitaw an o arithmos tou gyrou einai monos h zygos
                current_player[0] = first_symbol[0];
           else
                current_player[0] = second_symbol[0];
           printf("Where do you want to put '%s'?\n",current_player);

           do{
               do{
                    scanf("%d",&choice);
                    if (choice<1 || choice > 9)
                        printf("Wrong choice!! It has to be between 1-9!!\n");
               }while(choice<1 || choice > 9); //Edw checkaroume an o paixths edwse swsth epilogh
               if (checkIfAlreadyPlayed(temp, choice))
                    printf("This box is already full!!\n");
           }while(checkIfAlreadyPlayed(temp, choice)); //Edw checkaroume an exei ginei hdh ayth h kinhsh

           placeSymbol(board, temp, choice, current_player);
           printBoard(board);

        }while(round<9 && checkIfWin(temp)); //Edw mpainoun oi synthikes pou teleiwnoun enan gyro

        if (round<9){
            if (current_player[0] == 'X')
                points1++;
            else
                points2++;
        }

        do{
            printf("Do you want to play again? Press 0 for Yes and 1 for No.\n");
            scanf("%d",&answer);
            if (answer != 1 && answer != 0)
                printf("Wrong answer!!\n");
        }while(answer != 1 && answer != 0);
    }while(answer == 0);

    if (points1 > points2){ //Edw pairnw periptwseis gia na bgalei swsta ta onomata twn nikhtwn
        if (first_symbol[0] == 'X')
            printf("The winner is %s with %d points!!\n", first_name, points1);
        else
            printf("The winner is %s with %d points!!\n", second_name, points1);
    }
    else if (points1 < points2){
        if (first_symbol[0] == 'X')
            printf("The winner is %s with %d points!!\n", second_name, points2);
        else
            printf("The winner is %s with %d points!!\n", first_name, points2);
    }
    else
        printf("It was a tie!! Both players had %d points.\n",points1);

    system("pause");
    return 0;
}

void giveInstructions(){
    int i;
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("To play insert the number of the box you want to put your symbol in as shown below:\n");
    for (i=1; i<10; i++){
        printf("%d ",i);
        if (i % 3 == 0)
            printf("\n");
    }
}

void fillTempBoard(int temp[3][3]){
    int i, j;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            temp[i][j] = 0;
}

int randomizeFirstPlayer(){
    srand(time(0));
    return (rand() % 2);
}

void printBoard(char board[3][6]){
    int i;
    for (i=0; i<3; i++)
        printf("%s\n", board[i]);
}

void setCoordinates(int *x1, int *y1, int *x2, int *y2, int choice){
    if (choice == 1)
        *x1 = 0, *y1 = 0, *x2 = 0, *y2 = 0;
    else if (choice == 2)
        *x1 = 0, *y1 = 2, *x2 = 0, *y2 = 1;
    else if (choice == 3)
        *x1 = 0, *y1 = 4, *x2 = 0, *y2 = 2;
    else if (choice == 4)
        *x1 = 1, *y1 = 0, *x2 = 1, *y2 = 0;
    else if (choice == 5)
        *x1 = 1, *y1 = 2, *x2 = 1, *y2 = 1;
    else if (choice == 6)
        *x1 = 1, *y1 = 4, *x2 = 1, *y2 = 2;
    else if (choice == 7)
        *x1 = 2, *y1 = 0, *x2 = 2, *y2 = 0;
    else if (choice == 8)
        *x1 = 2, *y1 = 2, *x2 = 2, *y2 = 1;
    else
        *x1 = 2, *y1 = 4, *x2 = 2, *y2 = 2;
}

void placeSymbol(char board[3][6], int temp[3][3], int choice, char current_player[2]){
    int x1, y1, x2, y2;
    setCoordinates(&x1, &y1, &x2, &y2, choice);
    board[x1][y1] = current_player[0];
    if (current_player[0] == 'X')
        temp[x2][y2] = 1;
    else
        temp[x2][y2] = 2;
}


bool checkIfAlreadyPlayed(int temp[3][3], int choice){
    int x1, y1, x2, y2;
    setCoordinates(&x1, &y1, &x2, &y2, choice);
    if (temp[x2][y2] != 0) return 1;
    return 0;
}

bool checkIfWin(int temp[3][3]){
    int i, j;
    for (i=0; i<3; i++){
        if (temp[i][0] == temp[i][1] && temp[i][1] == temp[i][2] && temp[i][0] != 0) return 0;  //Orizontia
        if (temp[0][i] == temp[1][i] && temp[1][i] == temp[2][i] && temp[0][i] != 0) return 0;  //Katheta
    }
    if (temp[0][0] == temp[1][1] && temp[1][1] == temp[2][2] && temp[0][0] != 0) return 0;  //Kyria diagwnios
    if (temp[0][2] == temp[1][1] && temp[1][1] == temp[2][0] && temp[0][2] != 0) return 0;  //Deytereyousa diagwnios
    return 1;
}
