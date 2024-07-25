#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#elif __linux__
    #define CLEAR_COMMAND "clear"
#else
    #define CLEAR_COMMAND ""
#endif

// game board array.
char table[6][7];
//value for control turns.
int turn = 1;

int main(){
    // clear cmd.
    system(CLEAR_COMMAND);
    printf("\t\t\t\t\t\tWelcome to %s4 in a row%s game!\n\t\t\t\t\t%s<<      Press Enter button to start      >>%s\n", YELLOW, RESET, CYAN, RESET);
    getchar();
    // first turn for red.
    turn = 1;
    initializeBoard();
    printboard();
    move();
    return 0;
}
// create empty board.
void initializeBoard() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            table[i][j] = ' ';
        }
    }
}
// print board in cmd.
void printboard(){
    system(CLEAR_COMMAND);
    printf("\n");
    for(int i = 0; i < 7 ; i++){
        printf("|%d|\t", i+1);
    }
    printf("\n\n");
    for(int i = 0 ; i < 6 ; i++){
        for(int j = 0 ; j < 7 ; j++){
            if(table[i][j] == ' '){
                printf("%s[%s%c%s]%s\t", CYAN, RESET, table[i][j], CYAN, RESET);
            } else if (table[i][j] == 'O'){
                printf("%s[%s%sO%s%s]%s\t", CYAN, RESET, RED, RESET, CYAN, RESET);
            } else {
                printf("%s[%s%sO%s%s]%s\t", CYAN, RESET, BLUE, RESET, CYAN, RESET);
            }
        }
        printf("\n\n%s", RESET);
     }

}
// function that users do their moves.
void move(){
    int column;
    if(turn == 1){
        printf("Its %sRed%s's turn (Please enter number of column you want add yours): ", RED, RESET);
    } else {
        printf("Its %sBlue%s's turn (Please enter number of column you want add yours): ", BLUE, RESET);
    }
    scanf("%i", &column);
    while(column < 1 || column > 7){
        if(turn == 1){
            printf("%sChoose a value in range 1 to 7!!!%s\nIts %sRed%s's turn (Please enter number of column you want add yours): ", RED, RESET, RED, RESET);
        } else {
            printf("%sChoose a value in range 1 to 7!!!%s\nIts %sBlue%s's turn (Please enter number of column you want add yours): ", RED, RESET, BLUE, RESET);
        }
        scanf("%i", &column);
    }
    for(int i = 6; i >= 0; i--){
        if(table[i][column - 1] == ' '){
            if(turn == 1){
                table[i][column - 1] = 'O';
            } else {
                table[i][column - 1] = 'X';
            }
            break;
        } else if(table[i][column - 1] != ' ' && i == 0){
            printf("%sColumn is full choose another please!%s\n", RED, RESET);
            move();
        }
    }
    printboard();
    winner();
}
// function that detect the answer of game.
 void winner(){
     // if table is full the game get draw.
     if(table[0][0] != ' ' && table[0][1] != ' ' && table[0][2] != ' ' && table[0][3] != ' ' && table[0][4] != ' ' && table[0][5] != ' ' && table[0][6] != ' '){
        draw();
     }
     // check row
     for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            if(table[i][j] != ' ' && table[i][j] == table[i][j+1] && table[i][j] == table[i][j+2] && table[i][j] == table[i][j+3]){
                win();
            }
        }
     }
     // check columns
     for(int i = 0; i < 5; i++){
        for(int j = 0; j < 7; j++){
            if(table[i][j] != ' ' && table[i][j] == table[i+1][j] && table[i][j] == table[i+2][j] && table[i][j] == table[i+3][j]){
                win();
            }
        }
     }
     // Check diagonal from top left to bottom right
     for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
                if(table[i][j] != ' ' && table[i][j] == table[i+1][j+1] && table[i][j] == table[i+2][j+2] && table[i][j] == table[i+3][j+3]){
                win();
            }
        }
     }
     // Check diagonal from top right to bottom left
     for(int i = 3; i < 6; i++){
        for(int j = 0; j < 4; j++){
            if(table[i][j] != ' ' && table[i][j] == table[i-1][j+1] && table[i][j] == table[i-2][j+2] && table[i][j] == table[i-3][j+3]){
                win();
            }
        }
     }
     // change turns if no one win
     turn += 1;
     turn %= 2;
     move();
 }

 void draw(){
     printf("\t\t\t%sDRAW%s\n\n", CYAN, RESET);
     playAgain();
 }

void win(){
    if(turn == 1){
        printf("\t\t\t%sWIN%s\n\n", RED, RESET);
    } else {
        printf("\t\t\t%sWIN%s\n\n", BLUE, RESET);
    }
    playAgain();
}

 void playAgain(){
     char playagain;
     printf("Do you want Play again?(if yes enter Y or y else enter N or n):");
     scanf("%s", &playagain);
     // if users want play again rerun app else close the app.
     if (playagain == 'y' || playagain == 'Y'){
        main();
     }
     else if (playagain == 'n' || playagain == 'N'){
         printf("%sThanks for spending your time with us.\nI wish see you again!\n%s", YELLOW, RESET);
         exit(0);
     } else {
         printf("\n%sI can't understand that%s\n", RED, RESET);
         playAgain();
     }
 }
