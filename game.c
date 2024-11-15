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

void setup() {
    system("cls");
    srand(time(NULL));

    // Initialize the traffic positions
    for (int i = 0; i < HEIGHT; i++) {
        traffic_x[i] = -1;
        traffic_y[i] = -1;
    }
}

void draw() {
    system("cls");

    // Draw the road and the traffic
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y == CAR_POS_Y && x == car_pos_x) {
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
                    printf(" ");
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
        Sleep(100);  // Control game speed
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
