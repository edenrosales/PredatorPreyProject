//
//  Bug.cpp
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Kristjan Thorsteinsson on 01/04/14.
//  Copyright (c) 2014 Kristjan Thorsteinsson. All rights reserved.
//

#include "Bug.h"
#include "Organism.h"
#include <Windows.h>
using namespace std;

//constructor for Bug as described in .h
Bug::Bug(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
    death_tik = 0;
}

//will check all the spaces from down, up, left, rght to eat an Ant, if this 
//has not happened, it will move in a random directoin just like the Ant 
void Bug::move()
{
    breedTicks++;
    death_tik++;

    if (world->getAt(x, y + 1) != NULL)
    {
        if (world->getAt(x, y + 1)->getType() == ANT)
        {
            death_tik = 0;
            delete world->getAt(x, y + 1);
            movesTo(x, y + 1);
            return;
        }
    }

    if (world->getAt(x, y - 1) != NULL)
    {
        if (world->getAt(x, y - 1)->getType() == ANT)
        {
            death_tik = 0;
            delete world->getAt(x, y - 1);
            movesTo(x, y - 1);
            return;
        }
    }

    if (world->getAt(x - 1, y) != NULL)
    {
        if (world->getAt(x - 1, y)->getType() == ANT)
        {
            death_tik = 0;
            delete world->getAt(x - 1, y);
           movesTo(x - 1, y);
            return;
        }
    }
    if (world->getAt(x + 1, y) != NULL)
    {
        if (world->getAt(x + 1, y)->getType() == ANT)
        {
            death_tik = 0;
            delete world->getAt(x + 1, y);
            movesTo(x + 1, y);
            return;
        }
    }

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

//function that generates offspring for the Bug at (x,y) locatoin on the array
void Bug::generateOffspring(int whereX, int whereY)
{
    new Bug(this->world, whereX, whereY);
    breedTicks = 0;
}

// Makes this organism breed.
void Bug::breed()
{
    if (breedTicks >= BREED_BUGS)
    {
        breedAtAdjacentCell();
    }

}
// Returns true if organism is dead, false otherwise.
bool Bug::isDead() const
{
    if (death_tik >= STARVE_BUGS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Returns the type of this organism.
OrganismType Bug::getType() const
{
    return BUG;
}

// The character representation of this organism.
char Bug::representation()const
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    return 'B';
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

// The size of this organism.
int Bug::size() const
{
    return 30;
}

//Determines of the cordinates (xx,yy) are in the range of the array/simulation
bool Bug::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}
