#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 21  // Total width including lane separators
#define HEIGHT 20
#define CAR_POS_Y (HEIGHT - 2)

int lanes[3] = {5, 10, 15};  // X positions of the 3 lanes (adjusted to fit visual space)
int car_lane = 1;  // Player starts in the middle lane (index 1)
int score = 0;
int traffic_x[HEIGHT];  // X positions of traffic cars
int traffic_y[HEIGHT];  // Y positions of traffic cars
int traffic_lane[HEIGHT]; // Traffic car lane
int traffic_count = 0;  // Number of traffic cars on the road

void setup() {
    system("cls");
    srand(time(NULL));

    // Initialize traffic positions
    for (int i = 0; i < HEIGHT; i++) {
        traffic_x[i] = -1;
        traffic_y[i] = -1;
        traffic_lane[i] = -1;
    }
}

void draw() {
    system("cls");

    // Draw road and traffic
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y == CAR_POS_Y && x == lanes[car_lane]) {
                printf("A");  // Player's car
            } else {
                int is_traffic = 0;
                for (int i = 0; i < traffic_count; i++) {
                    if (traffic_x[i] == x && traffic_y[i] == y) {
                        printf("V");  // Traffic vehicle
                        is_traffic = 1;
                        break;
                    }
                }
                if (!is_traffic) {
                    if (x == lanes[0] || x == lanes[1] || x == lanes[2]) {
                        printf("|");  // Lane marker
                    } else {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }

    // Display score
    printf("Score: %d\n", score);
}

void update_traffic() {
    // Move existing traffic downward
    for (int i = 0; i < traffic_count; i++) {
        if (traffic_y[i] < HEIGHT - 1) {
            traffic_y[i]++;
        } else {
            // If traffic is out of the screen, remove it
            traffic_x[i] = -1;
            traffic_y[i] = -1;
            traffic_lane[i] = -1;
        }
    }

    // Add new traffic car in random lanes
    if (rand() % 5 == 0) {  // Add traffic at random intervals
        int lane = rand() % 3;  // Random lane 0, 1, or 2
        traffic_x[traffic_count] = lanes[lane];  // Assign the X position based on lane center
        traffic_y[traffic_count] = 0;  // Start at the top
        traffic_lane[traffic_count] = lane;  // Store lane number for collision check
        traffic_count++;
    }
}

void check_collision() {
    for (int i = 0; i < traffic_count; i++) {
        if (traffic_y[i] == CAR_POS_Y && traffic_lane[i] == car_lane) {
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
                if (car_lane > 0) car_lane--;  // Move left to previous lane
                break;
            case 'd':
                if (car_lane < 2) car_lane++;  // Move right to next lane
                break;
        }
    }
}

int main() {
    setup();

    while (1) {
        draw();
        input();
        update_traffic();
        check_collision();

        score++;
        Sleep(100);  // Control game speed
    }

    return 0;
}
