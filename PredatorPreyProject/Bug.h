#pragma once
//
//  Bug.h
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Kristjan Thorsteinsson on 01/04/14.
//  Copyright (c) 2014 Kristjan Thorsteinsson. All rights reserved.
//

#ifndef INHERITANCE_AND_POLYMORPHISM_Bug
#define INHERITANCE_AND_POLYMORPHISM_Bug

#include <iostream>
#include "World.h"
#include "Organism.h"

class Bug : public Organism
{
public:
    //Constructor for Bug objects 
    Bug(World* aWorld, int xcoord, int ycoord);

    //adds one count to death_tik and breedTicks
    //will check up, down, left, right to eat an Ant
    //If an Ant was eaten, will reset the death_tik
    //if an Ant was not eaten, then it will move just like the Ant (random directon)
    void move();

    // Makes this organism breed.
    void breed();

    // Returns the type of this organism.
    OrganismType getType() const;

    // The character representation of this organism.
    char representation() const;

    // The size of this organism.
    int size() const;
    // Returns true if organism is dead, false otherwise.
    bool isDead() const;

    //Determines of the cordinates (xx,yy) are in the range of the array/simulation
    bool in_range(int xx, int yy);

private:
    //function that generates offspring for the Bug at (x,y) locatoin on the array
    void generateOffspring(int whereX, int whereY);
    //Is the timer when the Bug has not eaten, that will kill the Bug if it gets to a certain value 
    int death_tik;
};

#endif /* defined(__INHERITANCE_AND_POLYMORPHISM__Bug__) */
