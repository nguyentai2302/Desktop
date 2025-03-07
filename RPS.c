#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define KEO 1
#define BUA 2
#define BAO 3
#define MAX 50000

int win_time = 0, lose_time = 0, set, numGamer, numComputer;

int isValidnumber(const char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] < '0' || string[i] > '9') return 0;
    }
    return 1;
}

void barProgress(int highlight) {
    init_pair(1, COLOR_RED, -1);
    init_pair(2, -1, COLOR_GREEN);
    attron(COLOR_PAIR(1));
    mvprintw(LINES / 2, COLS / 2 - 5, "LOADING %d ...\n", highlight);
    attroff(COLOR_PAIR(1));
    int width = COLS - 10;
    int progress = width * highlight / 100;
    for (int i = 0; i < width; i++) {
        if (i < progress)
            attron(COLOR_PAIR(2));
        addch(' ');
        if (i < progress)
            attroff(COLOR_PAIR(2));
    }
    refresh();
}

void typeEffect(const char *string, int delay) {
    while (*string) {
        addch(*string++);
        refresh();
        usleep(delay * MAX);
    }
}

const char *printBoard() {
    return "KEO IS 1\nBUA IS 2\nBAO IS 3\n";
}

int setNum() {
    char choice[100];
    do {
        typeEffect("ENTER YOUR SET: ", 1);
        getstr(choice);
        refresh();
        if (!isValidnumber(choice)) {
            clear();
            mvprintw(LINES / 2, COLS / 2 - 4, "ERROR!!!");
            refresh();
            napms(2000);
            clear();
        }
    } while (!isValidnumber(choice));
    return atoi(choice);
}

int computer() {
    return (rand() % 3) + 1;
}

int player() {
    char choice[100];
    int y, x;
    do {
        clear();
        typeEffect(printBoard(), 1);
        refresh();
        getyx(stdscr, y, x);
        move(y + 1, x);
        typeEffect("ENTER YOUR NUMBER: ", 1);
        getstr(choice);
        numGamer = atoi(choice);
        if (numGamer < 1 || numGamer > 3) {
            clear();
            mvprintw(LINES / 2, COLS / 2 - 4, "ERROR !!!");
            refresh();
            napms(2000);
            clear();
        }
    } while (numGamer < 1 || numGamer > 3);
    return numGamer;
}

void gameRule() {
    if (numGamer == numComputer) {
        printw("\nIT'S A TIE !!!");
    } else if ((numGamer == KEO && numComputer == BAO) ||
               (numGamer == BUA && numComputer == KEO) ||
               (numGamer == BAO && numComputer == BUA)) {
        printw("\nYOU WIN");
        win_time++;
    } else {
        printw("\nYOU LOSE");
        lose_time++;
    }
    refresh();
}

int main() {
    initscr();
    cbreak();
    start_color();
    use_default_colors();
    srand(time(NULL));
    init_pair(1,COLOR_RED, COLOR_GREEN);
    set = setNum();
    refresh();
    for (int i = 0; i < set; i++) {
        clear();
        numGamer = player();
        numComputer = computer();
        clear();
        mvprintw(LINES / 2, COLS / 2 - 6, "YOUR CHOICE WAS: %d\n", numGamer);
        refresh();
        mvprintw(LINES / 2 + 1, COLS / 2 - 6, "COMPUTER CHOSE: %d\n", numComputer);
        refresh();
        gameRule();
        napms(2000);
        refresh();
    }
    clear();
    refresh();

    curs_set(0);
    WINDOW *win = newwin(10, 40, LINES / 3, (COLS - 50) / 2);
    box(win, 0, 0);
    wbkgd(win,COLOR_PAIR(1));
    wattron(win,A_BOLD);
    mvwprintw(win, 5, 16, "GAME OVER!!!");
    wattroff(win,A_BOLD);
    wrefresh(win);
    napms(2000);
    refresh();
    clear();

    for (int i = 0; i < 100; i++) {
        barProgress(i);
        usleep(MAX);
        refresh();
    }
    clear();
    refresh();
    wclear(win);
    box(win, 0, 0);
    wrefresh(win);
    if (win_time > lose_time) {
        wbkgd(win,COLOR_PAIR(1));
        wattron(win,A_BOLD);
        mvwprintw(win, 5, 15, "YOU WIN IN THIS SET!!!");
        wattroff(win,A_BOLD);
    } else if (win_time < lose_time) {
        wbkgd(win,COLOR_PAIR(1));
        wattron(win,A_BOLD);
        mvwprintw(win, 5, 15, "YOU LOSE IN THIS SET !!!");
        wattroff(win,A_BOLD);
    } else {
        wbkgd(win,COLOR_PAIR(1));
        wattron(win,A_BOLD);
        mvwprintw(win, 5, 15, "IT'S A TIE");
        wattroff(win,A_BOLD);
    }
    wrefresh(win);
    napms (2000);
    refresh();
    delwin(win);
    endwin();
    return 0;
}
