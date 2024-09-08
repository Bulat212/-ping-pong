#include <math.h>
#include <ncurses.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25

void print_game_field(int left_racket, int right_racket, int ball_x, int ball_y) {
    // Отображение игрового поля
    for (int row = 0; row < 25; row++) {
        for (int col = 0; col < 80; col++) {
            if (col == 0 && row >= left_racket - 1 && row <= left_racket + 1)
                printw("|");
            else if (col == 80 - 1 && row >= right_racket - 1 && row <= right_racket + 1)
                printw("|");
            else if (col == ball_x && row == ball_y)
                printw("o");
            else if (row == 0 || row == 25 - 1)
                printw("-");
            else
                printw(" ");
        }
        printw("\n");
    }
}

int control_rackets(int mov_c, char up, char down, int rocket) {
    int update_y = 0;
    if (mov_c != ERR) {
        if (mov_c == up && rocket > 2) {
            update_y--;
        } else if (mov_c == down && rocket < HEIGHT - 3) {
            update_y++;
        }
    }
    return update_y;
}

int player_win(int left_score, int right_score) {
    int win = 0;
    if (left_score == 21) {
        clear();
        printw("Player 1 win!");
        refresh();
        win = 1;
    }
    if (right_score == 21) {
        clear();
        printw("Player 2 win!");
        refresh();
        win = 1;
    }
    return win;
}

int main() {
    initscr();
    int left_racket = HEIGHT / 2;
    int right_racket = HEIGHT / 2;
    int ball_x = WIDTH / 2, ball_y = HEIGHT / 2;
    int ball_dx = 1, ball_dy = 1;
    int left_score = 0, right_score = 0;
    int mov_c;

    while (1) {
        clear();
        printw("Score: %d - %d\n", ball_dy, right_score);  // Отображение счета
        print_game_field(left_racket, right_racket, ball_x, ball_y);

        refresh();
        timeout(100);
        mov_c = getch();

        left_racket += control_rackets(mov_c, 'A', 'Z', left_racket);
        right_racket += control_rackets(mov_c, 'K', 'M', right_racket);
        // Обновление позиции мяча
        ball_x += ball_dx;
        ball_y += ball_dy;

        // Проверка столкновений
        if (ball_y <= 0 || ball_y >= HEIGHT - 1) ball_dy = -ball_dy;  // Удар о стену
        if (ball_x == 1 && (ball_y >= left_racket - 1 && ball_y <= left_racket + 1))
            ball_dx = -ball_dx;  // Удар о левую ракетку
        if (ball_x == WIDTH - 2 && (ball_y >= right_racket - 1 && ball_y <= right_racket + 1))
            ball_dx = -ball_dx;  // Удар о правую ракетку

        // Проверка выхода за границы
        if (ball_x < 0) {
            right_score++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;  // Возврат мяча в центр
        }
        if (ball_x > WIDTH) {
            left_score++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;  // Возврат мяча в центр
        }
        if (player_win(left_score, right_score)) break;
    }
    
    getchar();
    endwin();
    return 0;
}