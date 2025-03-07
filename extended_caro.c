#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define WIDTH 40
#define HEIGHT 20
#define DELAY 100000

typedef struct Snake {
    int x, y;
    struct Snake *next;
} Snake;

Snake *head, *tail;
int foodX, foodY;
int direction = 'd';

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

void initGame() {
    head = malloc(sizeof(Snake));
    head->x = WIDTH / 2;
    head->y = HEIGHT / 2;
    head->next = NULL;
    tail = head;
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}

void draw() {
    system("clear");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                printf("#");
            } else if (i == foodY && j == foodX) {
                printf("O");
            } else {
                int isSnake = 0;
                for (Snake *s = head; s != NULL; s = s->next) {
                    if (s->x == j && s->y == i) {
                        printf("*");
                        isSnake = 1;
                        break;
                    }
                }
                if (!isSnake) printf(" ");
            }
        }
        printf("\n");
    }
}

void update() {
    int newX = head->x, newY = head->y;
    switch (direction) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
    }
    if (newX <= 0 || newX >= WIDTH - 1 || newY <= 0 || newY >= HEIGHT - 1) {
        printf("Game Over!\n");
        exit(0);
    }
    Snake *newHead = malloc(sizeof(Snake));
    newHead->x = newX;
    newHead->y = newY;
    newHead->next = head;
    head = newHead;
    if (newX == foodX && newY == foodY) {
        foodX = rand() % (WIDTH - 2) + 1;
        foodY = rand() % (HEIGHT - 2) + 1;
    } else {
        Snake *temp = head;
        while (temp->next->next) temp = temp->next;
        free(temp->next);
        temp->next = NULL;
    }
}

int main() {
    initGame();
    while (1) {
        if (kbhit()) {
            char ch = getchar();
            if (ch == 'q') break;
            if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') direction = ch;
        }
        update();
        draw();
        usleep(DELAY);
    }
    return 0;
}
