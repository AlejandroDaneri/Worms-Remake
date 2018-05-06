#include "World.h"
#include "Worm.h"

int main(int argc, char* argv[]){

	World world(b2Vec2(0.0f, 10.0));

	physical_object_ptr worm(new Worm(world, 1));
	world.addObject(worm, b2Vec2(500, 500));

	physical_object_ptr worm2(new Worm(world, 2));
	world.addObject(worm2, b2Vec2(600, 500));

	world.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	world.stop();
	world.join();

	return 0;
}