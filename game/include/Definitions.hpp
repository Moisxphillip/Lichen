#ifndef GAME_DEFS
#define GAME_DEFS

//This file is meant to hold "global" access data needed for the game.

#include "Core/Enum.hpp"

//Custom defines for componentTypes, allowing requests for components outside of engine

#define COMPONENT_ATTACK ComponentType::Type01
#define COMPONENT_PLAYER ComponentType::Type02
#define COMPONENT_EQUIP ComponentType::Type03


//Defining Collision Masks to turn them usable between multiple files, making it
//easier to define new correct masks as spreading it through multiple files would 
//end up with confusion on the Type used for each, as they must be different;

#define PLAYER_MASK     CollisionMask::Type01
#define PLAYER_ATK_MASK CollisionMask::Type02

#define ENEMY_MASK      CollisionMask::Type03
#define ENEMY_ATK_MASK  CollisionMask::Type04

#define INTERACT_MASK   CollisionMask::Type05




#endif//GAME_DEFS