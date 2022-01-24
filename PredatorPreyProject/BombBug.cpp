#include "BombBug.h"
#include <Windows.h>
using namespace std;


//constructor for BombBug as described in .h
BombBug::BombBug(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
//how many turns until the BombBug explodes
	explodeTimer = 5;
}


//returns the Object type (BOMBBUG)
OrganismType BombBug::getType() const
{
	return BOMBBUG;
}

//returns the representation of the BombBug (the character that it is associated with)
char BombBug::representation() const
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    char c = (char)explodeTimer +48;
	return c;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

//returns the size of the object
int BombBug::size() const
{
	return 40;
}
//determines if the cell (xx,yy) is in the range of the World
bool BombBug::in_range(int xx, int yy)
{
	return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}

//empty breeding function
//was included as a pure virtual function in Organism parent class, therefore it must be 
//in the child class, even if it has no function
void BombBug::breed()
{

}

//Bombbug does not generate offspring, so for the same reasons as the breed function,
//this will be left empty
void BombBug::generateOffspring(int whereX, int whereY) {

}

//determnines if the BombBug has exploded, and is therefore dead
bool BombBug::isDead() const
{
    if (explodeTimer <= 0) { 
        return true;
    }
    else
        return false;
}


//is the BombBug function of moving, which is the same as the Ant, but also explodes
//deleting all Organisms in adjecent cells and turning them to NULL
//decrements the explodeTimer no matter if the BombBug has moved or not 
void BombBug::move() {
    if (explodeTimer <= 1) {
        if (world->getAt(x, y + 1) != NULL && in_range(x, y +1)) {
                delete world->getAt(x, y + 1);
                world->setAt(x, y + 1, NULL);
        }
        if (world->getAt(x, y - 1) != NULL && in_range(x,y-1)) {
                delete world->getAt(x, y - 1);
                world->setAt(x, y - 1, NULL);
        }
        if (world->getAt(x - 1, y) != NULL && in_range(x-1, y )) {
                delete world->getAt(x - 1, y);
                world->setAt(x-1, y , NULL);
            }
        }
        if (world->getAt(x + 1, y) != NULL && in_range(x + 1, y)) {
                delete world->getAt(x + 1, y);
                world->setAt(x +1 , y , NULL);
            }
    Move mover = world->randomMove();
    switch (mover) {
    case UP:
        if (world->getAt(x, y + 1) == NULL && in_range(x, y + 1))
        {
            movesTo(x, y + 1);
            explodeTimer--;
        }
        else
            explodeTimer--;
        break;
    case DOWN:
        if (world->getAt(x, y - 1) == NULL && in_range(x, y - 1))
        {
            movesTo(x, y - 1);
            explodeTimer--;
        }
        else
            explodeTimer--;
        break;
    case LEFT:
        if (world->getAt(x - 1, y) == NULL && in_range(x - 1, y))
        {
            movesTo(x - 1, y);
            explodeTimer--;
        }
        else
            explodeTimer--;
        break;
    case RIGHT:
        if (world->getAt(x + 1, y) == NULL && in_range(x + 1, y))
        {
            movesTo(x + 1, y);
            explodeTimer--;
        }
        else
            explodeTimer--;
        break;
    default:
        break;
    }
    }
