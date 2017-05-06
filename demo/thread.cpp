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