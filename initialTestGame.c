#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

int OFTEN = 7;
int SPEED  = 10;
#define WIDTH 80  
#define HEIGHT 27
#define CAR_POS_Y (HEIGHT - 2)
#define CONSOLE_WIDTH 115  

int lanes[8] = {0, 10, 20, 30, 40, 50, 60, 70};  
int car_lane = 1;  
int score = 0;
char *taxi_designs[5] = {"{<..>}", "{oOOo}", "{8<>8}", "{:TT:}", "{*oO*}"};

typedef struct {
    int x;
    int y;
    int lane;
    int active;
    char *design;  
} TrafficCar;

TrafficCar traffic[HEIGHT];  

void setup() {
    system("cls");
    srand(time(NULL));

    for (int i = 0; i < HEIGHT; i++) {
        traffic[i].x = -1;
        traffic[i].y = -1;
        traffic[i].lane = -1;
        traffic[i].active = 0;
        traffic[i].design = NULL;
    }
    car_lane = 1;  
    score = 0;     
}

void draw() {
    system("cls");

    for (int y = 0; y < HEIGHT; y++) {

        printf("\033[30;1m..................\033[0m");

        for (int x = 0; x < WIDTH; x++) {
            if (y == CAR_POS_Y && x == lanes[car_lane] + 1) {
                printf("\e[0;33m[:TAXI:]\033[0m");
                x += 7;  
            } else {
                int is_traffic = 0;
                for (int i = 0; i < HEIGHT; i++) {
                    if (traffic[i].y == y && traffic[i].active && x == traffic[i].x + 2) {
                        printf("\e[0;32m%s\033[0m", traffic[i].design);
                        is_traffic = 1;
                        x += 5;  
                        break;
                    }
                }
                if (!is_traffic) {

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
        printf("\033[30;1m......................\033[0m\n");
    }

    printf("\e[1;31mScore: %d\033[0m\n", score);
}

void update_traffic() {

    for (int i = 0; i < HEIGHT; i++) {
        if (traffic[i].active) {
            traffic[i].y++;
            if (traffic[i].y >= HEIGHT) {

                traffic[i].active = 0;
            }
        }
    }

    if (rand() % OFTEN == 0) {  
        for (int i = 0; i < HEIGHT; i++) {
            if (!traffic[i].active) {  
                int lane = rand() % 8;  
                traffic[i].x = lanes[lane];
                traffic[i].y = 0;  
                traffic[i].lane = lane;
                traffic[i].active = 1;
                traffic[i].design = taxi_designs[rand() % 5];  
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

            printf("Press 'r' to retry or 'm' to return to the main menu.\n");

            while (1) {
                char choice = _getch();
                if (choice == 'r') {
                    setup();  
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
                if (car_lane > 0) car_lane--;  
                break;
            case 'd':
                if (car_lane < 7) car_lane++;  
                break;
        }
    }
}

void printCentered(char* text) {
    int padding = (CONSOLE_WIDTH - strlen(text)) / 2;  
    for (int i = 0; i < padding; i++) {
        printf(" ");  
    }
    printf("%s\n", text);  
}

void displayArt() {

    printf("\033[33m");  
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

    printf("\033[0m\n");

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
    printf("\033[32mUse A and D to maneuver your taxi\033[0m\n");
    printf("\n");
    printf("\033[32mThe score adds up every meter you go!\033[0m\n");
    printf("\n");
    printf("\033[32mYou die if you collide with upcoming traffic\033[0m\n");
    printf("\n");
    printf("\n");
    printf("\033[32mPsst... Just don't choose level impossible, and you're all set :D\033[0m\n");
    _getch();
}

void levels() {
    system("cls");
    int choice = 0;  
    char input;

    while (1) {

        system("cls");
        displayArt();
        printCentered("\033[32m\tChoose Your Level:\033[0m");

        if (choice == 0) {
            printCentered("\033[31m  -> Impossible Level\033[0m");  
        } else {
            printCentered("   Impossible Level");
        }

        if (choice == 1) {
            printCentered("\033[91m     -> Hard Level\033[0m");  
        } else {
            printCentered("   Hard Level");
        }

        if (choice == 2) {
            printCentered("\033[33m    -> Medium Level\033[0m");  
        } else {
            printCentered("   Medium Level");
        }

        if (choice == 3) {
            printCentered("\033[92m      -> Easy Level\033[0m");  
        } else {
            printCentered("   Easy Level");
        }

        if (choice == 4) {
            printCentered("\033[90m        -> Back\033[0m");  
        } else {
            printCentered("\033[90m   Back\033[0m");
        }

        input = _getch();

        if (input == 'w') {
            if (choice > 0) {
                choice--;
            }
        } else if (input == 's') {
            if (choice < 4) {
                choice++;
            }
        } else if (input == '\r') {  

            if (choice == 0) {
                OFTEN = 2;
                SPEED = 2;
            } else if (choice == 1) {
                OFTEN = 3;
                SPEED = 3;
            } else if (choice == 2) {
                OFTEN = 4;
                SPEED = 5;
            } else if (choice == 3) {
                OFTEN = 4;
                SPEED = 10;
            } else if (choice == 4) {
                return;  
            }

            system("cls");
            printCentered("\033[32mLevel Selected. Returning to Main Menu...\033[0m");
            return;
        }
    }
}

void credits() {
    system("cls");
    printf("\033[32mIzaan Khan\033[0m\n");
    printf("\033[32mTalha Mirza\033[0m\n");
    printf("\033[32mTushal Chhabbria\033[0m\n");
    _getch();
}

int main() {
    int choice = 0;  
    char input;

    while (1) {

        system("cls");  

        displayArt();

        if (choice == 0) {
            printCentered("\033[36m  -> Start Game\033[0m");  
        } else {
            printCentered("   Start Game");
        }

        if (choice == 1) {
            printCentered("\033[36m     -> Instructions\033[0m");  
        } else {
            printCentered("   Instructions");
        }

        if (choice == 2) {
            printCentered("\033[36m    -> Choose Level\033[0m");  
        } else {
            printCentered("   Choose Level");
        }

        if (choice == 3) {
            printCentered("\033[36m      -> Credits\033[0m");  
        } else {
            printCentered("   Credits");
        }

        if (choice == 4) {
            printCentered("\033[36m     -> Quit\033[0m");  
        } else {
            printCentered("   Quit");
        }

        input = _getch();  

        if (input == 'w') {
            if (choice > 0) {
                choice--;  
            }
        } else if (input == 's') {
            if (choice < 4) {
                choice++;  
            }
        } else if (input == '\r') {  

            if (choice == 0) {
                startGame();  
            }
            if (choice == 1) {
                instructions();  
            }
            if (choice == 2) {
                levels();  
            }
            if (choice == 3) {
                credits();  
            }
            if (choice == 4) {
                printf("\033[31mExiting the game. Goodbye!\033[0m\n");  
                return 0;  
            }
        }
    }

    return 0;
}
