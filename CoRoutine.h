/*
 * Author : PlanC
 * E-mail : hubenchang0515@outlook.com
 * Blog   : www.kurukurumi.com
 *
 * File   : CoRoutine.h
 * Data   : 2017-5-6
 */

#ifndef COROUTINE_H
#define COROUTINE_H

#include <cstddef> 

namespace KKM
{
    class CoRoutine
    {
        public:
            CoRoutine();
            ~CoRoutine();

            size_t id();
            bool resume(void);
            void yield(void);

        protected:
            virtual void coroutine(void)=0;

        private:
            size_t handle;
            static void run(void* _this);
    };
};

#endif // COROUTINE