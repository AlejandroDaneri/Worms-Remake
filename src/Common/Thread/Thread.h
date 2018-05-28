#ifndef __THREAD_H__
#define __THREAD_H__

#include <thread>

class Thread{
	private:
		std::thread thread;

	protected:
		bool running;

	public:
		/* Constructor */
		Thread();

		/* Destructor */
		virtual ~Thread();

		/* Constructor por copia */
        Thread(const Thread&) = delete;

        /* Operador = por copia */
        Thread& operator=(const Thread&) = delete;

        /* Constructor por movimiento */
        Thread(Thread&& other) = delete;

        /* Operador = por movimiento */
        Thread& operator=(Thread&& other) = delete;


		/* Inicia la ejecucion del thread */
		void start();

		/* Hace join con el thread */
		void join();

		/* Devuelve true si el thread esta ejecutandose,
		 * false si ya termino*/
		bool isRunning() const;

		/* Metodo de ejecucion del thread */
		virtual void run() = 0;

		/* Termina abruptamente la ejecucion del thread */
		virtual void stop();
};

#endif
