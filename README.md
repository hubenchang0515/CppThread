# CppThread
Simple Thread Mutex and CoRoutine class of C++ on UNIX-like OS.  
```
using namespace KKM;
```

# Thread
An abstract class of thread controller based on POSIX thread.You have to override it
## pure virtual function
It is the fact function which will run in thread controlled by this object.
```
virtual void* thread(void)=0;
```
## public member
```
/* thread's return value */
void* result;

/* thread id (thread_t) */
pthread_t id();

/* to start this thread */
void start(void);

/* to wait this thread finish */
int join(void);

/* to detach this thread */
int detach(void);

/* try to cancel this thread */
int cancel(void);
```

# Mutex
A class of mutex based on POSIX thread.
## public member
```
/* lock this mutex */
int lock();

/* try to lock this mutex */
int trylock();

/* unlock this mutex */
int unlock();
```

# CoRoutine
An abstract class of coroutine controller based on ucontext.h.
## pure virtual function
It is the fact function which will run in coroutine controlled by this object.You have to override it.
```
virtual void coroutine(void)=0;
```
## public member
```
/* coroutine id */
size_t id();

/* resume this coroutine */
bool resume(void);

/* yield this coroutine */
void yield(void);
```
# Example
```
/* This code print 12121212... in order.*/

#include <Thread.h>
#include <Mutex.h>
#include <iostream>
#include <string>

using namespace KKM;

Mutex mutex1,mutex2;

class Thread1 : public Thread
{  
    protected:
        
        void* thread(void)
        {
            for(int i = 0; i < 10; i++)
            {
                mutex1.lock();
                std::cout << "1\n";
                mutex2.unlock();
            }
        }
};

class Thread2 : public Thread
{
    protected:
        
        void* thread(void)
        {
            for(int i = 0; i < 10; i++)
            {
                mutex2.lock();
                std::cout << "2\n";
                mutex1.unlock();
            }
                
        }
};


int main()
{
    mutex2.lock();

    Thread1 thread1;
    Thread2 thread2;

    thread1.start();
    thread2.start();

    thread1.join();
    thread2.join();
    
}
```
```
/* This code print coroutine 10 times. */

#include <CoRoutine.h>
#include <iostream>

using namespace KKM;

class print : public CoRoutine
{
    protected:
        void coroutine(void)
        {
            for(int i = 0; i < 10; i++)
            {
                std::cout << "coroutine\n";
                yield();
            }
        }
};


int main()
{
    print p;
    while(p.resume());
}
```