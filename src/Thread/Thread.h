#ifndef __THREAD_H__
#define __THREAD_H__

#include <thread>

class Thread{
	private:
		std::thread thread;

	protected:
		bool running;

	public:
		Thread();
		virtual ~Thread();

		//Inicia la ejecucion del thread
		void start();

		//Hace join con el thread
		void join();

		//Devuelve true si el thread esta ejecutandose, 
		// false si ya termino
		bool isRunning() const;

		//Metodo de ejecucion del thread
		virtual void run() = 0;

		//Termina abruptamente la ejecucion del thread
		virtual void stop() = 0;


		Thread(const Thread&) = delete;
		Thread& operator=(const Thread&) = delete;

		Thread(Thread&& other) = delete;
		Thread& operator=(Thread&& other) = delete;
};

#endif
