#include "World.h"
#include "Worm.h"

int main(int argc, char* argv[]){

	World world(b2Vec2(0.0f, 10.0));

	Worm worm(world);
	worm.addToWorld(b2Vec2(500, 500));

	Worm worm2(world);
	worm2.addToWorld(b2Vec2(600, 500));

	return 0;
}