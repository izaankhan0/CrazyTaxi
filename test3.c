#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20
#define CAR_POS_Y (HEIGHT - 2)

int car_pos_x = WIDTH / 2;
int score = 0;
int traffic_x[HEIGHT];  // X positions of traffic cars
int traffic_y[HEIGHT];  // Y positions of traffic cars
int traffic_count = 0;  // Number of traffic cars on the road

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setup() {
    system("cls");
    srand(time(NULL));

    for (int i = 0; i < HEIGHT; i++) {
        traffic_x[i] = -1;
        traffic_y[i] = -1;
    }
}

void draw_player_car() {
    gotoxy(car_pos_x, CAR_POS_Y);
    printf("A");
}

void clear_player_car(int x) {
    gotoxy(x, CAR_POS_Y);
    printf(" ");
}

void draw_traffic() {
    for (int i = 0; i < traffic_count; i++) {
        if (traffic_y[i] >= 0 && traffic_y[i] < HEIGHT) {
            gotoxy(traffic_x[i], traffic_y[i]);
            printf("V");
        }
    }
}

void clear_traffic() {
    for (int i = 0; i < traffic_count; i++) {
        if (traffic_y[i] >= 1 && traffic_y[i] < HEIGHT) {
            gotoxy(traffic_x[i], traffic_y[i] - 1);
            printf(" ");
        }
    }
}

void update_traffic() {
    for (int i = 0; i < traffic_count; i++) {
        traffic_y[i]++;
        if (traffic_y[i] >= HEIGHT) {
            traffic_x[i] = rand() % WIDTH;
            traffic_y[i] = 0;
        }
    }

    if (rand() % 5 == 0 && traffic_count < HEIGHT) {
        traffic_x[traffic_count] = rand() % WIDTH;
        traffic_y[traffic_count] = 0;
        traffic_count++;
    }
}

void check_collision() {
    for (int i = 0; i < traffic_count; i++) {
        if (traffic_y[i] == CAR_POS_Y && traffic_x[i] == car_pos_x) {
            gotoxy(0, HEIGHT + 1);
            printf("Game Over! Final score: %d\n", score);
            exit(0);
        }
    }
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        int old_car_pos_x = car_pos_x;

        switch (key) {
            case 'a':
                if (car_pos_x > 0) car_pos_x--;  // Move left
                break;
            case 'd':
                if (car_pos_x < WIDTH - 1) car_pos_x++;  // Move right
                break;
        }

        if (car_pos_x != old_car_pos_x) {
            clear_player_car(old_car_pos_x);
            draw_player_car();
        }
    }
}

void startGame() {
    setup();
    draw_player_car();

    while (1) {
        clear_traffic();
        update_traffic();
        draw_traffic();
        check_collision();
        input();

        score++;
        gotoxy(0, HEIGHT);
        printf("Score: %d", score);

        Sleep(50);  // Adjust speed as needed
    }
}

int main() {
    startGame();
    return 0;
}
