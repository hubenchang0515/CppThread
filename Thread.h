/*
 * Author : PlanC
 * E-mail : hubenchang0515@outlook.com
 * Blog   : www.kurukurumi.com
 *
 * File   : Thread.h
 * Data   : 2017-5-6
 */

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

namespace KKM
{

    class Thread
    {
        public:
            void* result;
            pthread_t id();
            void start(void);
            int join(void);
            int detach(void);
            int cancel(void);

        protected:
            virtual void* thread(void)=0;

        private:
            pthread_t tid;
            static void* run(void* _this);
    };

};

#endif //THREAD_H