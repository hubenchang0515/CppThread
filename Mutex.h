/*
 * Author : PlanC
 * E-mail : hubenchang0515@outlook.com
 * Blog   : www.kurukurumi.com
 *
 * File   : Mutex.h
 * Data   : 2017-5-6
 */


#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

namespace KKM
{
    class Mutex
    {
        public:
            Mutex(const pthread_mutexattr_t* attr = NULL);
            ~Mutex();
            
            int lock();
            int trylock();
            int unlock();
        
        private:
            pthread_mutex_t mutex;
    };
};


#endif //MUTEX_H