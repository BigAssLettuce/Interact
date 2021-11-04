#pragma once
#include "../glm.h"
static enum COLORS {
	RED,
	ROSE,
	BLUE,
	CYAN,
	GREEN,
	WHITE,
	YELLOW,
	ORANGE
};

static glm::vec3 GetColor(COLORS color) {
	switch (color)
	{
	case RED:
		return glm::vec3(1, 0, 0);
		break;
	case ROSE:
		return glm::vec3(1, 0.25f, 0);
		break;
	case BLUE:
		break;
	case CYAN:
		break;
	case GREEN:
		return glm::vec3(0, 1, 0);
		break;
	case WHITE:
		return glm::vec3(1, 1, 1);
		break;
	case YELLOW:
		break;
	case ORANGE:
		break;
	default:
		break;
	}
}

