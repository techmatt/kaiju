
//
// standard includes
//
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

//
// when verbose is true, the game state is outputted to the console.
// should never be true when actually optimizing.
//
const bool verbose = true;

//
// Kaiju-specific includes
//
#include "util.h"
#include "parameters.h"
#include "deck.h"
#include "monster.h"
#include "player.h"
#include "game.h"