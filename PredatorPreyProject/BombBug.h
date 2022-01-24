#pragma once
//
//  BombBug.h
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Kristjan Thorsteinsson on 01/04/14.
//  Copyright (c) 2014 Kristjan Thorsteinsson. All rights reserved.
//

//#ifndef INHERITANCE_AND_POLYMORPHISM_BombBug
//#define INHERITANCE_AND_POLYMORPHISM_BombBug

#include <iostream>
#include "Organism.h"
#include "World.h"

class BombBug : public Organism
{
public:
	//constructor for BombBug objects 
	BombBug(World* aWorld, int xcoord, int ycoord);

	//In the given world moves this organism. And for the BombBug, will also allow it to explode
	//moves in the same fashion as the Ant when it is not exploding 
	//once the explodeTimer hits a certain value, the BombBug will explode
	void move();

	//Returns if the BombBug is dead or not 
	bool isDead() const;

	//Returns the type of this organism. 
	OrganismType getType() const;

	//The character representation of this organism.
	char representation() const;

	//The size of this organism.
	int size() const;

	//Determines of the cordinates (xx,yy) are in the range of the array/simulation
	bool in_range(int xx, int yy);

	//will not do anything because the BombBug does not breed
	void breed();

	//will not do anything because the BombBug does not generate offspring 
	void generateOffspring(int whereX, int whereY);

private:
	//Tells us how many turns until the BombBug explodes.
	int explodeTimer;



};
//#endif /* defined(__INHERITANCE_AND_POLYMORPHISM__Ant__) */