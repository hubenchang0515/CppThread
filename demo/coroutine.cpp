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