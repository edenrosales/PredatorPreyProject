#include <iostream>
#include <cstdlib>  // for rand
#include "World.h"
#include "Ant.h"
#include "Bug.h"
#include "Bombbug.h"
#include <Windows.h>
using namespace std;

///////////////////
// Public functions
///////////////////

// Default constructor: creates and initializes the world
// the seed is used for seeding the random behaviour.
World::World(unsigned int seed) {
    // seed the random generator
    srand(seed);
    // Create an empty world
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            grid[i][j] = NULL;
        }
    }
    // creates the ants = 3
    createOrganisms(ANT, INITIAL_ANTS);
    // creates the bugs = 8
    createOrganisms(BUG, INITIAL_BUGS);
}

// Deallocate memory allocated to organisms in this world.
World::~World() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            if (grid[i][j] != NULL) {
                delete grid[i][j];
            }
        }
    }
}

// Return the organism at the given coordinates
// If the coordinates are not valid, returns NULL
Organism* World::getAt(int x, int y) const {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        return grid[x][y];
    }
    else {
        return NULL;
    }
}

// Sets the entry at x,y to the value passed in.
// Places an Organism at that coordinate 
void World::setAt(int x, int y, Organism* org) {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        grid[x][y] = org;
    }
}

// Displays the world in ASCII.
//Also includes the title or header for the simulation, printing as a string literal 
//some of the text has been modified with the use of formatting such as endl statements 
//and also the use of \t (tabs) and regular ' ' spaces 
//also has been modified to change the colors using SetConsoleTextAttribute
void World::display() const {
    int numAnts = 0;
    int numBugs = 0;
    int numBombBugs=0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); //change text color
    cout << 
        R"(
                            _                     _         _                 _       _             
                           (_)                   | |       (_)               | |     | |            
                            _ _ __  ___  ___  ___| |_   ___ _ _ __ ___  _   _| | __ _| |_ ___  _ __ 
                           | | '_ \/ __|/ _ \/ __| __| / __| | '_ ` _ \| | | | |/ _` | __/ _ \| '__|
                           | | | | \__ \  __/ (__| |_  \__ \ | | | | | | |_| | | (_| | || (_) | |   
                           |_|_| |_|___/\___|\___|\__| |___/_|_| |_| |_|\__,_|_|\__,_|\__\___/|_|   
                                                                           
                                                                          
)";
    //this and other statements like it are for changing the color of the text  
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    cout << endl;
    for (int j = 0; j < WORLDSIZE; j++) {
        cout << "\t\t\t\t\t\t   ";
        for (int i = 0; i < WORLDSIZE; i++) {
            //will print a . for all the NULL cells that are in world
            if (grid[i][j] == NULL) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                cout << " .";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
            }
            //will print the represenation of all Organisms in the world
            else {
                if (grid[i][j]->getType() == ANT) {
                    numAnts++;
                }
                else if (grid[i][j]->getType() == BUG) {
                    numBugs++;
                }
                else if (grid[i][j]->getType() == BOMBBUG) {
                    numBombBugs++;
                }
                cout<<" "<<grid[i][j]->representation();
            }
        }
        cout << endl;
    }
    //counts all the different types of Organisms and displays them as a count on the simulatoin screen
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "\t\t\t\t\t\t      " << "Ants count: " << numAnts << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "\t\t\t\t\t\t     " << " Bugs count: " << numBugs << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout<< "\t\t\t\t\t\t     " <<" Bomb Bugs count:  "<<numBombBugs<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void World::simulateOneStep() {
    // The main routine that simulates one turn in the world:
    // 1. move bugs
    // 2. move ants
    // 3. make bugs starve (which happends under a certain condition)
    // 4. make the organisms breed (again which happens under a certain
    // condition).



    // Reset all organisms to not moved
    resetOrganisms();


    // Move the bugs
    moveOrganism(BUG);

    // Move the ants
    moveOrganism(ANT);

    // Make the bugs starve
    cleanup();

    //Make them breed
    breedOrganisms();

    //Move the BombBugs, and also explode them if ready
    moveOrganism(BOMBBUG);

    // Make the bugs starve
    cleanup();
}

Position World::randomPosition() const {    // returns a random number in the range 0 to MAX-1
    Position p;
    p.x = rand() % WORLDSIZE;
    p.y = rand() % WORLDSIZE;
    return p;
}

//returns a random number between one and four 
Move World::randomMove() const {
    return static_cast<Move>(rand() % 4);
}

////////////////////
// Private functions
////////////////////

//creates the Organisms that will be in the simulation
//will take in the type of Organism and also the amount to make
void World::createOrganisms(OrganismType orgType, int count) {
    int orgCount = 0;
    while (orgCount < count) {
        Position p = randomPosition();

        // Only put ant in empty spot
        if (grid[p.x][p.y] == NULL) {
            orgCount++;
            if (orgType == ANT) {
                new Ant(this, p.x, p.y);   // Create an Ant and put it into the world
            }
            else if (orgType == BUG) {
                new Bug(this, p.x, p.y);   // Create a Bug and put it into the world
            }
            else if (orgType == BOMBBUG) {
                new BombBug(this, p.x, p.y);
            }
        }
    }
}

// Reset all organisms to not moved
void World::resetOrganisms() {
    for (int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if (grid[i][j] != NULL)
            {
                grid[i][j]->setMoved(false);
            }
        }
    }
}


// Move all organisms of type aType
void World::moveOrganism(OrganismType aType) {
    for (int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if (grid[i][j] != NULL)
            {
                if (grid[i][j]->getType() == aType && !(grid[i][j]->hasMoved()))
                {
                    grid[i][j]->move();
                }
            }
        }
    }
}

// Remove all dead organisms from this world.
void World::cleanup() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            // Kill off any organisms that haven't eaten recently
            if ((grid[i][j] != NULL) && grid[i][j]->isDead()) {
                delete grid[i][j];
                grid[i][j] = NULL;
            }
        }
    }
}

// Make the organisms breed
void World::breedOrganisms() {
    for (int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if (grid[i][j] != NULL)
            {
                grid[i][j]->breed();
            }
        }
    }
}
