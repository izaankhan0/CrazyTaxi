#include <stdio.h>
#include <conio.h>  // For _kbhit() and _getch() in Windows

#define CONSOLE_WIDTH 80  // Assumed console width

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
    printCentered("  #####   #####    ###   #####   ##   ##    ####   ######    ##   ##");
    printCentered(" ##      ##   ##   ###  ##   ##  ###  ##   ##       ##   ##   ###  ##");
    printCentered(" ##      ##   ##    #   ##       #### ##    ####    ##   ##   #### ##");
    printCentered(" ##  ### #######    #   ##  ###  ## ####       ##   ######    ## ####");
    printCentered(" ##   ## ##   ##    #   ##   ##  ##  ###   ##   ##  ##   ##   ##  ###");
    printCentered("  #####  ##   ##   ###   #####   ##   ##    ####   ##   ##   ##   ##");

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
    _getch();  // Pause for the user to see the message
}
void instructions(){
    system("cls");
    printf("\033[32mJOOS PILADOOOOOOOOO\033[0m\n");
    _getch();
}
void score(){
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
                score();  // Show score
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
