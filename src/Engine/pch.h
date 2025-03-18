#ifndef PCH_H
#define PCH_H

//#define DEEP_PROFILER
#define ENTITY_BASE_MAXIMUM 1024;
#define FIXED_DT 0.008333f

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <vector>
#include <list>
#include <queue>
#include <unordered_map>

#include <Windows.h>
#include <timeapi.h>

struct TRANSFORM;

#include "Transform.h"
#include "GameTimer.h"

#endif