#include <ncurses.h>
#include <string.h>

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int y = 10, x = 30;  
    WINDOW *win = newwin(5, 25, y, x);  
    box(win, 0, 0);
    wrefresh(win);

    char str[100];
    echo();
    mvwgetnstr(win, 1, 1, str, sizeof(str) - 1);  // Nhập chuỗi an toàn
    noecho();

    int len = strlen(str);
    int ch;

    while (len > 0) {  // Khi chuỗi chưa rỗng
        ch = getch();  
        clear();
        refresh();
        switch (ch) {
            case KEY_UP:    y--; break;
            case KEY_DOWN:  y++; break;
            case KEY_RIGHT: x++; break;
            case KEY_LEFT:  x--; break;
        }

        // Xóa 1 ký tự cuối chuỗi sau mỗi lần di chuyển
        if (len > 0) {
            str[len - 1] = '\0';
            len--;
        }

        werase(win);  // Xóa nội dung cửa sổ con
        mvwin(win, y, x);
        box(win, 0, 0);
        mvwprintw(win, 1, 1, "%s", str);  // In lại chuỗi đã bị rút gọn
        wrefresh(win);
    }

    getch();
    delwin(win);
    endwin();
    return 0;
}
