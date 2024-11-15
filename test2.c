#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 40
#define CAR_POS_Y (HEIGHT - 2)
#define CONSOLE_WIDTH 115  // Assumed console width

int car_pos_x = WIDTH / 2;
int score = 0;
int traffic_x[HEIGHT];  // X positions of traffic cars
int traffic_y[HEIGHT];  // Y positions of traffic cars
int traffic_count = 0;  // Number of traffic cars on the road

// Double buffer for storing the screen content
char screenBuffer[HEIGHT][WIDTH];

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setup() {
    system("cls");
    srand(time(NULL));

    // Initialize the traffic positions
    for (int i = 0; i < HEIGHT; i++) {
        traffic_x[i] = -1;
        traffic_y[i] = -1;
    }
}

void clearBuffer() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screenBuffer[y][x] = ' ';
        }
    }
}

void draw() {
    clearBuffer();

    // Place player's car in the buffer
    screenBuffer[CAR_POS_Y][car_pos_x] = 'A';

    // Place traffic cars in the buffer
    for (int i = 0; i < traffic_count; i++) {
        if (traffic_y[i] >= 0 && traffic_y[i] < HEIGHT && traffic_x[i] >= 0 && traffic_x[i] < WIDTH) {
            screenBuffer[traffic_y[i]][traffic_x[i]] = 'V';
        }
    }

    // Render the buffer to the console
    gotoxy(0, 0);  // Move cursor to the top left
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", screenBuffer[y][x]);
        }
        printf("\n");
    }

    // Display score at the bottom
    printf("Score: %d\n", score);
}

void update_traffic() {
    // Move existing traffic downward
    for (int i = 0; i < traffic_count; i++) {
        if (traffic_y[i] < HEIGHT - 1) {
            traffic_y[i]++;
        } else {
            // If traffic is out of the screen, reset position
            traffic_x[i] = -1;
            traffic_y[i] = -1;
        }
    }

    // Add new traffic car
    if (rand() % 5 == 0) {  // Add traffic at random intervals
        traffic_x[traffic_count] = rand() % WIDTH;
        traffic_y[traffic_count] = 0;
        traffic_count++;
    }
}

void check_collision() {
    for (int i = 0; i < traffic_count; i++) {
        if (traffic_y[i] == CAR_POS_Y && traffic_x[i] == car_pos_x) {
            printf("Game Over! Final score: %d\n", score);
            exit(0);
        }
    }
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
            case 'a':
                if (car_pos_x > 0) car_pos_x--;  // Move left
                break;
            case 'd':
                if (car_pos_x < WIDTH - 1) car_pos_x++;  // Move right
                break;
        }
    }
}

// Function to print centered text
void printCentered(char* text) {
    int padding = (CONSOLE_WIDTH - strlen(text)) / 2;  // Calculate padding
    for (int i = 0; i < padding; i++) {
        printf(" ");  // Print padding spaces
    }
    printf("%s\n", text);  // Print the centered text
}

void startGame() {
    printf("\033[32mStarting the game...\033[0m\n");  // Green text
    setup();

    while (1) {
        draw();
        input();
        update_traffic();
        check_collision();

        score++;
        Sleep(100);  // Control game speed
    }
}

int main() {
    startGame();
    return 0;
}
