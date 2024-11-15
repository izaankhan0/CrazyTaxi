#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 81  // Total width including lane separators
#define HEIGHT 20
#define CAR_POS_Y (HEIGHT - 2)
#define CONSOLE_WIDTH 115  // Assumed console width


int lanes[8] = {0, 10, 20, 30, 40, 50, 60, 70};  // X positions of the lanes
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
        // Left border
        printf("...");

        for (int x = 0; x < WIDTH; x++) {
            if (y == CAR_POS_Y && x == lanes[car_lane] + 3) {
                printf("[CAR]");  // Player's car
                x += 4;  // Skip over player's car width
            } else {
                int is_traffic = 0;
                for (int i = 0; i < HEIGHT; i++) {
                    if (traffic[i].y == y && traffic[i].active && x == traffic[i].x + 2) {
                        printf("\e[0;32m{<..>}\033[0m");
                        is_traffic = 1;
                        x += 5;  // Skip over traffic car width
                        break;
                    }
                }
                if (!is_traffic) {
                    // Check if current position `x` is a lane separator
                    int is_lane_separator = 0;
                    for (int j = 0; j < 7; j+=2) {
                    	if(j < 8){
                        if (x == lanes[j]) {
                        	printf("|");
                            is_lane_separator = 1;
                            break;
                        }
						}                  
                    }
                    if (!is_lane_separator) {
                        printf(" ");
                    }
                }
            }
        }
        printf("|...\n");

        // Right border
    }

    // Display score at the bottom
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
				if (car_lane > 0) car_lane--;  // Move left
				break;
			case 'd':
				if (car_lane < 7) car_lane++;  // Move right
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

// Function to display the large "CRAZY TAXI" heading and racing car ASCII art
void displayArt() {
    // Escape sequences to set text color (yellow for the heading)
    printf("\033[33m");  // Yellow color
    printCentered("  #######  ########    #####   ######## ##        ##  ");
    printCentered(" ##        ##     ##  #     #       ##   ##      ##   ");
    printCentered(" ##        ##     ## ##     ##     ##     ##    ##    ");
    printCentered(" ##        ########  #########    ##       ##  ##     ");
    printCentered(" ##     ## ##     ## ##     ##   ##          ##       ");
    printCentered(" ##     ## ##     ## ##     ##  ##           ##       ");
    printCentered("  #######  ##     ## ##     ## ########      ##       ");
    printCentered("\n");
    printCentered(" ############   #####   ##     ##  ########## ");
    printCentered("      ##       #     #   ##   ##       ##     ");
    printCentered("      ##      ##     ##   ## ##        ##     ");
    printCentered("      ##      #########    ###         ##     ");
    printCentered("      ##      ##     ##   ## ##        ##     ");
    printCentered("      ##      ##     ##  ##   ##       ##     ");
    printCentered("      ##      ##     ## ##     ##   ########  ");

    // Reset to default color and add a newline for spacing
    printf("\033[0m\n");

    // Display a racing car under the title in yellow
    printf("\033[33m");
    printCentered("   ______");
    printCentered("  //  ||\\ \\ ");
    printCentered(" ____||_ ||_\\___");
    printCentered("'  _     _      O  _");
    printCentered("'-(_)---(_)------(_)-'");
    printf("\033[0m\n");
}

void startGame() {
    printf("\033[32mStarting the game...\033[0m\n");  // Green text
    // Add your game logic here
    
    
	setup();

	while (1) {
		draw();
		input();
		update_traffic();
		check_collision();

		score++;
		Sleep(30);
	}


  
   
    
    _getch();  // Pause for the user to see the message
}
void instructions(){
    system("cls");
    printf("\033[32mJOOS PILADOOOOOOOOO\033[0m\n");
    _getch();
}
void scores(){
    system("cls");
    printf("\033[32mGame to banalee pehle\033[0m\n");
    _getch();
}
void credits(){
    system("cls");
    printf("\033[32mIzaan Khan\033[0m\n");
    printf("\033[32mTalha Avasti\033[0m\n");
    _getch();
}

int main() {
    int choice = 0;  // 0: Start Game, 1: Quit
    char input;

    while (1) {
        // Clear the screen
        system("cls");  // Use "clear" on Linux/Mac

        // Display ASCII art
        displayArt();

        if (choice == 0) {
            printCentered("\033[36m  -> Start Game\033[0m");  // Cyan for selected option
        } else {
            printCentered("   Start Game");
        }
        
        if (choice == 1) {
            printCentered("\033[36m     -> Instructions\033[0m");  // Cyan for selected option
        } else {
            printCentered("   Instructions");
        }

        if (choice == 2) {
            printCentered("\033[36m    -> Score\033[0m");  // Cyan for selected option
        } else {
            printCentered("   Score");
        }

        if (choice == 3) {
            printCentered("\033[36m      -> Credits\033[0m");  // Cyan for selected option
        } else {
            printCentered("   Credits");
        }

        if (choice == 4) {
            printCentered("\033[36m     -> Quit\033[0m");  // Cyan for selected option
        } else {
            printCentered("   Quit");
        }

        // Wait for user input (w = up, s = down, enter to select)
        input = _getch();  // Get user input without Enter

        if (input == 'w') {
            if (choice > 0) {
                choice--;  // Move cursor up
            }
        } else if (input == 's') {
            if (choice < 4) {
                choice++;  // Move cursor down
            }
        } else if (input == '\r') {  // '\r' is the Enter key
            // Perform selected action
            if (choice == 0) {
                startGame();  // Start the game
            }
            if (choice == 1) {
                instructions();  // Show instructions
            }
            if (choice == 2) {
                scores();  // Show score
            }
            if (choice == 3) {
                credits();  // Show credits
            }
            if (choice == 4) {
                printf("\033[31mExiting the game. Goodbye!\033[0m\n");  // Red text
                break;  // Exit menu loop
            }
        }
    }

    return 0;
}
