#include <iostream>
#include <ctime>    // for time
#include "World.h"
#include <Windows.h>
#include <conio.h>
#include <string>
using namespace std;

//this  is a function that places the cursor on the specified (x,y) coordinates on the screen
//this was copied from the coding lecture video that the professor posted on his canavs, 
//so i did not come up with it myself
void gotoxy(int x, int y) {
    if (x >= 0 && y >= 0) {
        COORD kursor;
        kursor.X = x;
        kursor.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), kursor);
    }
}
int main()
{   //variables for the gotoxy function
    int x = 6;
    int y = 5;

    //strings the for password in the instructions menu
    string agreement;
    string password = "understood";
    World myWorld(time(0));

   //the code for the instructions menu, which displays before the simulation starts, and 
   //requires a password to get past
    gotoxy(x, y);
    //title print statement 
    cout << R"(

                                   _           _                   _   _                 
                                  (_)         | |                 | | (_)                
                                   _ _ __  ___| |_ _ __ _   _  ___| |_ _  ___  _ __  ___ 
                                  | | '_ \/ __| __| '__| | | |/ __| __| |/ _ \| '_ \/ __|
                                  | | | | \__ \ |_| |  | |_| | (__| |_| | (_) | | | \__ \
                                  |_|_| |_|___/\__|_|   \__,_|\___|\__|_|\___/|_| |_|___/
                                                        
                                                      
)";
    cout << endl << endl;
    //displaying the instructions 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "\t\t\t\t\t\t" <<"Press A or a for Ant" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "\t\t\t\t\t\t" << "Press E or e for Bug" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "\t\t\t\t\t\t" << "Press B or b for Bomb Bug" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << "\t\t\t\t\t\t" << "Press Spacebar to Pause/Unpause" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "\t\t\t\t\t\t" << "Press 'q' to quit the simulation" << endl; //this is talking about 
    //inside of the program. Pressing 'q' in the menu will do nothing.

    cout << endl << endl << "\t\t\t\t\t   " << "If this makes sense to you, type: 'understood'"<<endl;
    cout << "\t\t\t\t\t   ";
    //prompts the user to input the string 'understood' to enter the rest of the program
    //if the wrong input is entered, it will state that the answer is wrong, and that you must 
    //reread the instructions and try again
    cin >> agreement;
    if (agreement.compare(password) == 0) {//comparing user input to the password to enter simulation


        myWorld.display();
        bool pause = false;
        char ch;


        while (1) {   // q for quit
            system("cls");
            myWorld.simulateOneStep();
            myWorld.display();
            if (_kbhit()) {
                ch = _getch();
                if (ch == 'E' || ch == 'e')//pressing 'e' or 'E' adds a single Bug into the simulation
                {
                    system("cls");
                    myWorld.createOrganisms(BUG, 1);
    
                }
                if (ch == 'a' || ch == 'A')//presing 'a' or 'A' adds a single Ant into the simulation
                {
                    system("cls");
                    myWorld.createOrganisms(ANT, 1);

                }
                if (ch == 'b' || ch == 'B')//pressing 'b' or 'B' adds a single BombBug into the simulation
                {
                    system("cls");
                    myWorld.createOrganisms(BOMBBUG, 1);

                }
                if (ch == 'q') { //exits the program is q is pressed 
                    exit(0);
                }
                if (ch == 32) { //pauses the game is spacebar is pressed 
                    //while the game is paused, a person can still add Organisms to the world
                    //to ensure that these organisms are displayed in the world, the display()
                    //function will be ran right after a new Organism is placed in the world
                    pause = !pause;
                    while (pause) {
                        if (_kbhit()) {
                            ch = _getch();
                            if (ch == 'E' || ch == 'e')//pressing 'e' or 'E' adds a single Bug into the simulation
                            {
                                system("cls");
                                myWorld.createOrganisms(BUG, 1);
                                myWorld.display();
                            }
                            if (ch == 'a' || ch == 'A')//presing 'a' or 'A' adds a single Ant into the simulation
                            {
                                system("cls");
                                myWorld.createOrganisms(ANT, 1);
                                myWorld.display();
                            }
                            if (ch == 'b' || ch == 'B') {//pressing 'b' or 'B' adds a single BombBug into the simulation
                                system("cls");
                                myWorld.createOrganisms(BOMBBUG, 1);
                                myWorld.display();
                            }
                            if (ch == 'q')//exits the program is q is pressed 
                                exit(0);
                            if (ch == 32) {//unpauses the game 
                                pause = !pause;
                            }
                        }


                    }
                }
            }
            Sleep(350);
        }
    }
    else {//this is the text that is shown if the password for the menu is not put in correctly
        //will lead to the end of the program
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout <<endl<< endl<< endl<< "\t\t\t\t\t   Wrong. Exiting program. Restart to try again.";
        cout << endl << endl << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    }
