#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3


// main game
char board[SIZE][SIZE];
char player, computer;

void choose() {
    int a;
    printf("1 for X\n2 for O\n");
    scanf("%d", &a);
    if (a == 1) {
        player = 'X';
        computer = 'O';
    } else if (a == 2) {
        player = 'O';
        computer = 'X';
    }
}
// initialize board game
void create_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void printboard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < SIZE - 1) {
            printf("---|---|---\n");
        }
    }
}
// how game works

// valid move
bool valid_move(int row, int col) {
    return (row < SIZE && row >= 0 && col < SIZE && col >= 0 && board[row][col] == ' ');
}

// check whether board is full or not
bool full_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}


// check win
bool regime(char currentPlayer) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) {
            return true;
        }
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) {
            return true;
        }
    }
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) {
        return true;
    }
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) {
        return true;
    }
    return false;
}

// initialize the move of computer
void computer_move() {
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!valid_move(row, col));
    board[row][col] = computer;
}

// how to play 
void poppy_playgame() {
    while (!full_board()) {
        int row, col;
        printboard();

        do {
            printf("PLEASE LOCATE YOUR MOVE [row][colum] range from 0 to 2: ");
            scanf("%d%d", &row, &col);
            if (!valid_move(row, col)) {
                printf("TRY AGAIN!!!\n");
                continue;
            }
        } while (!valid_move(row, col));
        board[row][col] = player;

        if (regime(player)) {
            printboard();
            printf("YOU ARE THE WINNER!!!\n");
            return;
        }

        if (full_board()) {
            printboard();
            printf("IT IS A DRAW!!!\n");
            return;
        }

        computer_move();

        if (regime(computer)) {
            printboard();
            printf("YOU LOSE\n");
            return;
        }

        if (full_board()) {
            printboard();
            printf("IT IS A DRAW!!!\n");
            return;
        }
    }
    printboard();
}

// main working space
int main() {
    srand(time(NULL));
    choose();
    create_board();
    poppy_playgame();
    return 0;
}
