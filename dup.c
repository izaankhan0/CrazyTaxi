#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 60  // Total width including lane separators
#define HEIGHT 20
#define CAR_POS_Y (HEIGHT - 2)

int lanes[8] = {10, 21, 32, 42, 52, 62, 72, 82};  // X positions of the lanes
int car_lane = 1;  // Player starts in the middle lane (index 1)
int score = 0;

typedef struct {
	int x;
	int y;
	int lane;
	int active;
} TrafficCar;

TrafficCar traffic[HEIGHT];  // Array of traffic cars to simulate multiple traffic items

void setup() {
	system("cls");
	srand(time(NULL));

	// Initialize all traffic cars as inactive
	for (int i = 0; i < HEIGHT; i++) {
		traffic[i].x = -1;
		traffic[i].y = -1;
		traffic[i].lane = -1;
		traffic[i].active = 0;
	}
}

void draw() {
	system("cls");

	for (int y = 0; y < HEIGHT; y++) {
		
		for (int x = 0; x < WIDTH; x++) {
			if (y == CAR_POS_Y && x == lanes[car_lane] + 3) {
				printf("[CAR]");  // Player's car
				x += 4;  // Skip over player's car width
			} else {
				int is_traffic = 0;
				for (int i = 0; i < HEIGHT; i++) {
					if (traffic[i].y == y && traffic[i].active && x == traffic[i].x + 3) {
						printf("\e[0;32m{<..>}\033[0m");
						is_traffic = 1;
						x += 5;  // Skip over traffic car width
						break;
					}
				}
				if (!is_traffic) {
					if (x == lanes[0] || x == lanes[2] || x == lanes[4] || x == lanes[6] || x == lanes[8]) {
						printf("|");
					} else {
						printf(" ");
					}
				}
			}
		}
		printf("\n");
	}

	printf("Score: %d\n", score);
}

void update_traffic() {
	// Move existing traffic downward
	for (int i = 0; i < HEIGHT; i++) {
		if (traffic[i].active) {
			traffic[i].y++;
			if (traffic[i].y >= HEIGHT) {
				// Deactivate if it moves out of bounds
				traffic[i].active = 0;
			}
		}
	}

	// Add new traffic car at random intervals
	if (rand() % 5 == 0) {  // Adjust frequency to control traffic density
		for (int i = 0; i < HEIGHT; i++) {
			if (!traffic[i].active) {  // Find an inactive slot
				int lane = rand() % 8;  // Choose a random lane
				traffic[i].x = lanes[lane];
				traffic[i].y = 0;  // Start at the top of the screen
				traffic[i].lane = lane;
				traffic[i].active = 1;
				break;
			}
		}
	}
}

void check_collision() {
	for (int i = 0; i < HEIGHT; i++) {
		if (traffic[i].active && traffic[i].y == CAR_POS_Y && traffic[i].lane == car_lane) {
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
				if (car_lane > -5) car_lane--;  // Move left
				break;
			case 'd':
				if (car_lane < 3) car_lane++;  // Move right
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
		Sleep(50);
	}

	return 0;
} 