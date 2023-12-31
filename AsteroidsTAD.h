#include "Structs.h"
#define ASTEROIDS_ARRAY_QUANTITY 4

Object_transformation **asteroidsArraysArray = (Object_transformation**) malloc(
  sizeof(Object_transformation*) * ASTEROIDS_ARRAY_QUANTITY
);

int ASTEROIDS_DEEP_LEVEL = 4;
int ASTEROIDS_LENGTH_ARRAY = (int) pow(2, ASTEROIDS_DEEP_LEVEL) - 1;

Object_transformation* clearAsteroidsEnables(
	Object_transformation *asteroidsArray
) {
	for(int i = 0; i < ASTEROIDS_LENGTH_ARRAY; i++) {
		asteroidsArray[i].enable = false;
	}

	return asteroidsArray;
}

int getLeftChildrenIndex(int asteroidIndex) {
	asteroidIndex += 1;
	return asteroidIndex * 2 - 1;
}

int getRightChildrenIndex(int asteroidIndex) {
	asteroidIndex += 1;
	return asteroidIndex * 2;
}

Object_transformation* divideAsteroid(int asteroidIndex, Object_transformation *asteroidsArray) {

	int left = getLeftChildrenIndex(asteroidIndex);
	int right = getRightChildrenIndex(asteroidIndex);
	printf("Left: %d e Right: %d\n", left, right);

	// Habilitando/Desabilitando asteroides
	asteroidsArray[asteroidIndex].enable = false;

	if(left < ASTEROIDS_LENGTH_ARRAY) {
		asteroidsArray[left].enable = true;
		// Setando posições para o filho esquerdo
		asteroidsArray[left].angle = asteroidsArray[asteroidIndex].angle + 30;
		asteroidsArray[left].Tx = asteroidsArray[asteroidIndex].Tx;
		asteroidsArray[left].Ty = asteroidsArray[asteroidIndex].Ty;
		asteroidsArray[left].xStep = cos(
			convertDegreesToRadians(asteroidsArray[left].angle)
		) * ASTEROID_VELOCITY;
		asteroidsArray[left].yStep = sin(
			convertDegreesToRadians(asteroidsArray[left].angle)
		) * ASTEROID_VELOCITY;
	}

	if(right < ASTEROIDS_LENGTH_ARRAY) {
		asteroidsArray[right].enable = true;
		// Setando posições para o filho direito
		asteroidsArray[right].angle = asteroidsArray[asteroidIndex].angle - 30;
		asteroidsArray[right].Tx = asteroidsArray[asteroidIndex].Tx;
		asteroidsArray[right].Ty = asteroidsArray[asteroidIndex].Ty;
		asteroidsArray[right].xStep = cos(
			convertDegreesToRadians(asteroidsArray[right].angle)
		) * ASTEROID_VELOCITY;
		asteroidsArray[right].yStep = sin(
			convertDegreesToRadians(asteroidsArray[right].angle)
		) * ASTEROID_VELOCITY;
	}

  return asteroidsArray;
}