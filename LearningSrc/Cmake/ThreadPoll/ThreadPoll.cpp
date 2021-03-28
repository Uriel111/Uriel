#include "ThreadPoll.h"
#include <iostream>
ThreadPoll::ThreadPoll()
{
    std::cout << "Construct ThreadPool Successfully" << std::endl;
}
ThreadPoll::~ThreadPoll()
{
    std::cout << "Desconstruct ThreadPoll Successfully " << std::endl;
}