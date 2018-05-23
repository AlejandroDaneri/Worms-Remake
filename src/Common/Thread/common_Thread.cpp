#include "Thread.h"


Thread::Thread(): running(false){}
		
Thread::~Thread(){}

void Thread::start(){
	this->running = true;
	this->thread = std::thread(&Thread::run, this);
}
		
void Thread::join(){
	if(this->thread.joinable()){
		this->thread.join();
	}
}
		
bool Thread::isRunning() const{
	return this->running;
}

void Thread::stop(){
	this->running = false;
}
