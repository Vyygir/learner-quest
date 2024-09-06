#ifndef OPTIONS_H
#define OPTIONS_H

#include <tuple>
#include <string>
#include "SDL.h"

const char *TITLE = "LearnerQuest";
const std::tuple<int, int> RESOLUTION = std::make_tuple(1280, 720);
const int FRAME_RATE = 144;
const int ENGINE_SPEED = 60;
const Uint32 FIXED_INTERVAL = 1000 / ENGINE_SPEED;

#endif
