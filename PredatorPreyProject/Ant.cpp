//
//  Ant.cpp
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Kristjan Thorsteinsson on 01/04/14.
//  Copyright (c) 2014 Kristjan Thorsteinsson. All rights reserved.
//
#include <cstdlib>

#include <iostream>
#include "Ant.h"
#include "Organism.h"
#include "World.h"
#include <Windows.h>
using namespace std;

//Constructor for Ant as explained in .h 
Ant::Ant(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{

}


//will select a random directoin from UP, DOWN, LEFT, RIGHT to move to and if it is a cell in range
//of the map and also not already occupied, will move there
void Ant::move()
{
    breedTicks++;
    Move mover = world->randomMove();
    switch (mover) {
    case UP:
        if (world->getAt(x, y + 1) == NULL && in_range(x, y + 1))
        {
            movesTo(x, y + 1);
        }
        break;
    case DOWN:
        if (world->getAt(x, y - 1) == NULL && in_range(x, y - 1))
        {
            movesTo(x, y - 1);
        }
        break;
    case LEFT:
        if (world->getAt(x - 1, y) == NULL && in_range(x - 1, y))
        {
            movesTo(x - 1, y);
        }
        break;
    case RIGHT:
        if (world->getAt(x + 1, y) == NULL && in_range(x + 1, y))
        {
            movesTo(x + 1, y);
        }
        break;
    default:
        break;
    }
}

//Breeds the ant when the timer has reached a specificed value 
void Ant::breed()
{
    if (breedTicks >= BREED_ANTS)
    {
        breedAtAdjacentCell();
    }
}

//The function that generates a new Ant object in the cell (x,y)
//resets the breedticks down to 0 
void Ant::generateOffspring(int whereX, int whereY)
{
    new Ant(this->world, whereX, whereY);
    breedTicks = 0;
}

//returns the Object type (ANT)
OrganismType Ant::getType() const
{
    return ANT;
}

//returns the representation of the Ant (the character that it is associated with)
char Ant::representation() const
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    return 'A';
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

//returns the size of the object
int Ant::size() const
{
    return 10;
}

//determines if the cell (xx,yy) is in the range of the World
bool Ant::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}
