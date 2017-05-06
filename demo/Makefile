target : thread coroutine

thread : thread.cpp ../Thread.cpp ../Thread.h ../Mutex.cpp ../Mutex.h
	g++ -o thread thread.cpp ../Thread.cpp ../Mutex.cpp -I .. -lpthread -w -Wall

coroutine : coroutine.cpp ../CoRoutine.cpp ../CoRoutine.h
	g++ -o coroutine coroutine.cpp ../CoRoutine.cpp -I.. -W -Wall

clean :
	rm thread coroutine