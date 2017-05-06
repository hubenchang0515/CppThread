/*
 * Author : PlanC
 * E-mail : hubenchang0515@outlook.com
 * Blog   : www.kurukurumi.com
 *
 * File   : Thread.h
 * Data   : 2017-5-6
 */

#include <Thread.h> 

namespace KKM
{

    /* Return thread id. */
    pthread_t Thread::id(void)
    {
        return tid;
    }

    /* Create POSIX Thread by static member function and 'this' pointer. */
    void Thread::start(void)
    {
        pthread_create(&tid,NULL,Thread::run,this);
    }
    
    
    /* Wait for thread stop. */
    int Thread::join(void)
    {
        return pthread_join(tid,&result);
    }
    
    
    /* Detach the thread. */
    int Thread::detach(void)
    {
        return pthread_detach(tid);
    }
    
    
    /* Try to cancel thread. */
    int Thread::cancel(void)
    {
        return pthread_cancel(tid);
    }
    
    
    /* Static member function call non-static member function by 'this' pointer. */
    void* Thread::run(void* _this)
    {
        return ((Thread*)_this)->thread();
    }

};