#include "sharedmemory.hpp"
#include <iostream>
#include <unistd.h>

using namespace shm;

int main() {
    shm::Receiver<float>  receiver("SMF");
    unsigned int microsecond = 1000000;
    while (true)
    {
        for (size_t j = 0; j < 7; j++)
        {
            std::cout << receiver.data->at(j) << "  ";
        }
        std::cout << std::endl;
        usleep(1 * microsecond);//sleeps for 1 second
    }
    return 0;
}