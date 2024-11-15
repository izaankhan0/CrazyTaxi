#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define OFTEN 3
#define SPEED 5
#define WIDTH 80  // Total width including lane separators
#define HEIGHT 20
#define CAR_POS_Y (HEIGHT - 2)
#define CONSOLE_WIDTH 115  // Assumed console width

int lanes[8] = {0, 10, 20, 30, 40, 50, 60, 70};  // X positions of the lanes
int car_lane = 1;  // Player starts in the middle lane (index 1)
int score = 0;
char *taxi_designs[5] = {"{<..>}", "{oOOo}", "{8<>8}", "{:TT:}", "{*oO*}"};

typedef struct {
    int x;
    int y;
    int lane;
    int active;
    char *design;  // New attribute to hold the design of the car
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
        traffic[i].design = NULL;
    }
    car_lane = 1;  // Reset player position to the middle lane
    score = 0;     // Reset score
}

void draw() {
    system("cls");

    for (int y = 0; y < HEIGHT; y++) {
        // Left border
        printf("\e[1;31m...\033[0m");

        for (int x = 0; x < WIDTH; x++) {
            if (y == CAR_POS_Y && x == lanes[car_lane] + 1) {
                printf("\e[0;33m[:TAXI:]\033[0m");
                x += 7;  // Skip over player's car width
            } else {
                int is_traffic = 0;
                for (int i = 0; i < HEIGHT; i++) {
                    if (traffic[i].y == y && traffic[i].active && x == traffic[i].x + 2) {
                        printf("\e[0;32m%s\033[0m", traffic[i].design);
                        is_traffic = 1;
                        x += 5;  // Skip over traffic car width
                        break;
                    }
                }
                if (!is_traffic) {
                    // Check if current position `x` is a lane separator
                    int is_lane_separator = 0;
                    for (int j = 0; j < 7; j += 2) {
                        if (j < 8 && x == lanes[j]) {
                            printf("\e[1;31m|\033[0m");
                            is_lane_separator = 1;
                            break;
                        }
                    }
                    if (!is_lane_separator) {
                        printf(" ");
                    }
                }
            }
        }
        printf("\e[1;31m|...\033[0m\n");
    }

    // Display score at the bottom
    printf("\e[1;31mScore: %d\033[0m\n", score);
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
    if (rand() % OFTEN == 0) {  // Adjust frequency to control traffic density
        for (int i = 0; i < HEIGHT; i++) {
            if (!traffic[i].active) {  // Find an inactive slot
                int lane = rand() % 8;  // Choose a random lane
                traffic[i].x = lanes[lane];
                traffic[i].y = 0;  // Start at the top of the screen
                traffic[i].lane = lane;
                traffic[i].active = 1;
                traffic[i].design = taxi_designs[rand() % 5];  // Randomly assign a design
                break;
            }
        }
    }
}

void check_collision() {
    for (int i = 0; i < HEIGHT; i++) {
        if (traffic[i].active && traffic[i].y == CAR_POS_Y && traffic[i].lane == car_lane) {
            system("cls");
            printf("\033[31mGame Over!\033[0m Final score: %d\n", score);

            // Display retry and return to main menu options
            printf("Press 'r' to retry or 'm' to return to the main menu.\n");

            // Wait for user input to choose option
            while (1) {
                char choice = _getch();
                if (choice == 'r') {
                    setup();  // Restart the game
                    return;
                } else if (choice == 'm') {
                    main();
                }
            }
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
    setup();

    while (1) {
        draw();
        input();
        update_traffic();
        check_collision();

        score++;
        Sleep(SPEED);
    }
}

void instructions() {
    system("cls");
    printf("\033[32mJOOS PILADOOOOOOOOO\033[0m\n");
    _getch();
}

void levels() {
    system("cls");
    printf("\033[32mGame to banalee pehle\033[0m\n");
    _getch();
}

void credits() {
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
            printCentered("\033[36m    -> Choose Level\033[0m");  // Cyan for selected option
        } else {
            printCentered("   Choose Level");
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
                levels();  // Show score
            }
            if (choice == 3) {
                credits();  // Show credits
            }
            if (choice == 4) {
                printf("\033[31mExiting the game. Goodbye!\033[0m\n");  // Red text
                return;  // Exit menu loop
            }
        }
    }

    return 0;
}
