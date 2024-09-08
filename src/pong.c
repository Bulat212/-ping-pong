#include <stdio.h>
#include <math.h>
#include <unistd.h> // Для функции sleep()

#define WIDTH 80
#define HEIGHT 25

int main() {
    int left_paddle = HEIGHT / 2;
    int right_paddle = HEIGHT / 2;
    int ball_x = WIDTH / 2, ball_y = HEIGHT / 2;
    int ball_dx = 1, ball_dy = 1;
    int left_score = 0, right_score = 0;

    while (1) {
        // Очистка экрана
        printf("\033c");

        // Отображение счета
        printf("Score: %d - %d\n", left_score, right_score);

        // Отображение игрового поля
        for (int row = 0; row < HEIGHT; row++) {
            for (int col = 0; col < WIDTH; col++) {
                if (col == 0 && row >= left_paddle - 1 && row <= left_paddle + 1)
                    printf("|");
                else if (col == WIDTH - 1 && row >= right_paddle - 1 && row <= right_paddle + 1)
                    printf("|");
                else if (col == ball_x && row == ball_y)
                    printf("o");
                else
                    printf(" ");
            }
            printf("\n");
        }

        // Обработка ввода
        if (getchar() == 'w' && left_paddle > 1) left_paddle--;
        if (getchar() == 's' && left_paddle < HEIGHT - 2) left_paddle++;
        if (getchar() == 'o' && right_paddle > 1) right_paddle--;
        if (getchar() == 'l' && right_paddle < HEIGHT - 2) right_paddle++;

        // Обновление позиции мяча
        ball_x += ball_dx;
        ball_y += ball_dy;

        // Проверка столкновений
        if (ball_y <= 0 || ball_y >= HEIGHT - 1) ball_dy = -ball_dy; // Удар о стену
        if (ball_x == 1 && (ball_y >= left_paddle - 1 && ball_y <= left_paddle + 1)) ball_dx = -ball_dx; // Удар о левую ракетку
        if (ball_x == WIDTH - 2 && (ball_y >= right_paddle - 1 && ball_y <= right_paddle + 1)) ball_dx = -ball_dx; // Удар о правую ракетку

        // Проверка выхода за границы
        if (ball_x < 0) {
            right_score++;
            ball_x = WIDTH / 2; ball_y = HEIGHT / 2; // Возврат мяча в центр
        }
        if (ball_x > WIDTH) {
            left_score++;
            ball_x = WIDTH / 2; ball_y = HEIGHT / 2; // Возврат мяча в центр
        }

        // Задержка
        //usleep(100000); // 100 миллисекунд
    }

    return 0;
}