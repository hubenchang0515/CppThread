/*
 * Author : PlanC
 * E-mail : hubenchang0515@outlook.com
 * Blog   : www.kurukurumi.com
 *
 * File   : CoRoutine.cpp
 * Data   : 2017-5-6
 */

#include <cstddef>
#include <stdint.h>
#include <ucontext.h>
#include <csignal>
#include <cstdlib>
#include <vector>

#include <CoRoutine.h>

typedef void (*CoFunc)(void*);
static int CoResume(size_t handle,int yield_rvalue);
static int CoYield(size_t handle,int resume_rvalue);
static size_t CoCreate(CoFunc func,void* param);

#include <iostream>

namespace KKM
{
    CoRoutine::CoRoutine()
    {
        CoCreate(CoRoutine::run,this);
    }

    CoRoutine::~CoRoutine()
    {

    }

    size_t CoRoutine::id()
    {
        return this->handle;
    }

    bool CoRoutine::resume(void)
    {
        return CoResume(this->handle,1) > 0;
    }

    void CoRoutine::yield(void)
    {
        CoYield(this->handle,1);
    }



    void CoRoutine::run(void* _this)
    {
        ((CoRoutine*)_this)->coroutine();
    }

};



/********************** cotoutine of program language C ********************** 
     Get more infomation from https://github.com/hubenchang0515/coroutine
******************************************************************************/

// max quantity of coroutine of one scheduler
#define COROUTINE_MAX_QUANTITY (SIZE_MAX - 1)

// the stack size of every coroutine
#define COROUTINE_STACK_SZIE (10240)

// type of scheduler
typedef struct Scheduler Scheduler_t;

// handle of coroutine
typedef size_t CoHandle_t;

// coroutine funcrions pointer
typedef void (*CoFunc)(void*);


/* states of coroutine
 * CoState_NotStart		: coroutine has been created but hasn't bigun to run
 * CoState_Running		: coroutine is running
 * CoState_Yielded		: coroutine has yielded
 * CoState_Terminated	: coroutine has terminated
 */
typedef enum CoStateEnum
{
	CoState_NotStart,
	CoState_Running,
	CoState_Yielded,
	CoState_Terminated,
}CoStateEnum_t;


/* informaion of every coroutine
 * func 	: function of the coroutine
 * param	: parameter of coroutine function
 * context 	: context of the coroutine , to resume coroutine
 * state 	: state of the coroutrine
 * stack 	: stack of the coroutine
 * rvalue 	: return value of CoResume and CoYield
 */
typedef struct CoInfo
{
	CoFunc func;
	void* param;
	ucontext_t context;
	CoStateEnum_t state;
	unsigned char stack[COROUTINE_STACK_SZIE];
	int rvalue;
}CoInfo_t;

/* type of scheduler 
 * length 		: quantity of coroutine in this scheduler
 * maxlength 	: max quantity of coroutine in this scheduler
 * list 		: coroutines' list
 * context		: context of scheduler , to back to CoResume and return
 */
typedef struct Scheduler
{
	size_t length;
	size_t maxlength;
	std::vector<CoInfo_t> list;
	ucontext_t context;
}Scheduler_t;

static Scheduler_t Scheduler = {0,COROUTINE_MAX_QUANTITY};

static int CoResume(CoHandle_t handle,int yield_rvalue)
{
    Scheduler_t* scheduler = &Scheduler;
	// if yield_rvalue is 0 ,  CoYield will return 1
	scheduler->list[handle].rvalue = yield_rvalue ? yield_rvalue : 1;
	CoFunc func = scheduler->list[handle].func;
	void* param = scheduler->list[handle].param;

	switch(scheduler->list[handle].state)
	{
		case CoState_NotStart: // start the coroutine
				// change state of coroutine to be CoState_Running
				scheduler->list[handle].state = CoState_Running;
				// make a context to invoke starter , go back to &scheduler->context after starter return
				getcontext(&scheduler->list[handle].context);
				scheduler->list[handle].context.uc_stack.ss_sp = scheduler->list[handle].stack;
				scheduler->list[handle].context.uc_stack.ss_size = COROUTINE_STACK_SZIE;
				scheduler->list[handle].context.uc_link = &scheduler->context;
				makecontext(&scheduler->list[handle].context , (void(*)(void))func , 1 , param);
				// invoke starter by scheduler and handle to start the coroutine and save current context
				swapcontext(&scheduler->context,&scheduler->list[handle].context);
				// if coroutine come back without CoYield , that means coroutine has terminated
				if(scheduler->list[handle].state != CoState_Yielded)
				{
					scheduler->list[handle].state = CoState_Terminated;
				}
				
				return scheduler->list[handle].rvalue;

		case CoState_Yielded: // resume the coroutine
				// change state of coroutine to be CoState_Running
				scheduler->list[handle].state = CoState_Running;
				// if coroutine come back without CoYield , that means coroutine has terminated
				swapcontext(&scheduler->context,&scheduler->list[handle].context);
				if(scheduler->list[handle].state != CoState_Yielded)
				{
					scheduler->list[handle].state = CoState_Terminated;
				}
				
				return scheduler->list[handle].rvalue;

		case CoState_Running:
				return 0;

		case CoState_Terminated:
				return 0;

		default:
				return -1; // return -1 means exceptional
	}
}


static int CoYield(CoHandle_t handle,int resume_rvalue)
{
    Scheduler_t* scheduler = &Scheduler;
	// if resume_rvalue is 0 , CoResume  will return 1
	scheduler->list[handle].rvalue = resume_rvalue ? resume_rvalue : 1;
	// change state of coroutine to be CoState_Yielded
	scheduler->list[handle].state = CoState_Yielded;
	// go back to CoResume
	swapcontext(&scheduler->list[handle].context,&scheduler->context);

	return scheduler->list[handle].rvalue;
}


static CoHandle_t CoCreate(CoFunc func,void* param)
{
    Scheduler_t* scheduler = &Scheduler;
	if(scheduler->length <= scheduler->maxlength)
	{
		CoInfo_t co;
        co.func = func;
        co.param = param;
        co.state = CoState_NotStart;

        scheduler->list.push_back(co);
		return scheduler->length-1;
	}
	else
		return -1;
}


