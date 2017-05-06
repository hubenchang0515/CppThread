/*
 * Author : PlanC
 * E-mail : hubenchang0515@outlook.com
 * Blog   : www.kurukurumi.com
 *
 * File   : Mutex.cpp
 * Data   : 2017-5-6
 */

 #include <Mutex.h>

 namespace KKM
 {

    Mutex::Mutex(const pthread_mutexattr_t* attr)
    {
        pthread_mutex_init(&this->mutex,attr);
    }

    Mutex::~Mutex()
    {
        pthread_mutex_destroy(&this->mutex);
    }

    int Mutex::lock()
    {
        return pthread_mutex_lock(&this->mutex);
    }

    int Mutex::trylock()
    {
        return pthread_mutex_trylock(&this->mutex);
    }

    int Mutex::unlock()
    {
        return pthread_mutex_unlock(&this->mutex);
    }

 };