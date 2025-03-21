#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX 3

char board[MAX][MAX];
char player, computer;

void typeEffect(int lines, int cols, const char *str){
    while(*str){
        mvaddch(lines, cols++, *str++);
        refresh();
        usleep(50000);
    }
}

void barProgress(int progress){
    init_pair(1,-1, COLOR_RED);
    init_pair(2, COLOR_GREEN, -1);
    attron(COLOR_PAIR(2));
    mvprintw(LINES/2, COLS/2 -5,"LOADING... %d%%", progress);
    attroff(COLOR_PAIR(2));
    int width=COLS-10;
    int run= width*progress/100;
    for(int i=0; i< run; i++){
        attron(COLOR_PAIR(1));
        mvaddch(LINES/2 +1,i+5,' ');
        attroff(COLOR_PAIR(1));
    }
}

void printBar(){
    clear();
    typeEffect(LINES/2,COLS/2-10, "GAME OVER!!!");
    refresh();
    sleep(2);
    clear();

    for(int i=1; i<=100; i++){
        clear();
        barProgress(i);
        refresh();
        usleep(50000);
    }
    clear();
    sleep(1);
    refresh();
}

void playerChoice() {
    cbreak();
    refresh();
    noecho();
start: 
    printw("PLAYER CHOOSE SYMBOL: X OR O: ");
    refresh();
    int ch = getch();
    switch (ch) {
        case 'x':
        case 'X':  
            player = 'X';
            computer = 'O';
            break;
        case 'o':
        case 'O':  
            player = 'O';
            computer = 'X';
            break;
        default: 
            clear(); 
            printw("INVALID CHOICE!!!\n");
            refresh();
            sleep(1);
            clear();
            goto start;
    }
}

void initBoard() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    clear();
    int start_y = (LINES - (MAX * 2 - 1)) / 2;
    int start_x = (COLS - (MAX * 4 - 1)) / 2;
    for (int i = 0; i < MAX; i++) {
        move(start_y + i * 2, start_x);
        for (int j = 0; j < MAX; j++) {
            printw(" %c ", board[i][j]);
            if (j < MAX - 1) printw("|");
        }
        if (i < MAX - 1) {
            move(start_y + i * 2 + 1, start_x);
            printw("---|---|---");
        }
    }
    refresh();
}

void playerMove() {
    int x = 0, y = 0;
    int ch;
    int start_y = (LINES - (MAX * 2 - 1)) / 2;
    int start_x = (COLS - (MAX * 4 - 1)) / 2;
    move(start_y, start_x);
    refresh();
    while (1) {
        ch = getch();
        switch (ch) {
            case KEY_UP:
                if (y > 0) y--;
                break;
            case KEY_DOWN:
                if (y < MAX - 1) y++;
                break;
            case KEY_LEFT:
                if (x > 0) x--;
                break;
            case KEY_RIGHT:
                if (x < MAX - 1) x++;
                break;
            case '\n': // Enter key
                if (board[y][x] == ' ') {
                    board[y][x] = player;
                    return;
                }
                break;
        }
        printBoard();
        move(start_y + y * 2, start_x + x * 4); // Adjust cursor position
        refresh();
    }
}

void computerMove() {
    int y, x;
    do {
        y = rand() % MAX;
        x = rand() % MAX;
    } while (board[y][x] != ' ');
    board[y][x] = computer;
}

bool isValidMove(int row, int col) {
    return row >= 0 && row < MAX && col >= 0 && col < MAX && board[row][col] == ' ';
}

bool checkFullBoard() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

bool checkWinner(char currentPlayer) {
    for (int i = 0; i < MAX; i++) {
        // Check rows
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) {
            return true;
        }
        // Check columns
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
        return true;
    }
    return false;
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    use_default_colors();
    curs_set(1); // Show cursor
    srand(time(NULL)); // Seed the random number generator
    
    refresh();
    playerChoice();
    clear();
    initBoard();
    printBoard();
    refresh();
    
    while (1) {
        playerMove();
        printBoard();
        refresh();
        if (checkWinner(player)) {
            clear();
            printBar();
            typeEffect(LINES / 2, (COLS / 2) - 6, "PLAYER WON !!!");
            refresh();
            break;
        }
        if (checkFullBoard()) {
            clear();
            printBar();
            typeEffect(LINES / 2, (COLS / 2) - 6, "IT'S A DRAW !!!");
            refresh();
            break;
        }
        computerMove();
        printBoard();
        refresh();
        if (checkWinner(computer)) {
            clear();
            printBar();
            typeEffect(LINES / 2, (COLS / 2) - 6, "COMPUTER WON !!!");
            refresh();
            break;
        }
        if (checkFullBoard()) {
            clear();
            printBar();
            typeEffect(LINES / 2, (COLS / 2) - 6, "IT'S A DRAW !!!");
            refresh();
            break;
        }
    }
    sleep(2);
    refresh();
    endwin();
    return 0;
}
