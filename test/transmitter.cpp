#include "sharedmemory.hpp"
#include <iostream>
#include <unistd.h>

int main() {
    shm::Transmitter<float>  transmitter("SMF", 1000);
    unsigned int microsecond = 1000000;
    for (size_t j = 0; j < 7; j++)
    {
        transmitter.data->push_back((float)j);
        std::cout << transmitter.data->at(j) << "  ";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < 100; i++)
    {
        for (size_t j = 0; j < 7; j++)
        {
            ++transmitter.data->at(j);
            std::cout << transmitter.data->at(j) << "  ";
        }
        std::cout << std::endl;
        usleep(1 * microsecond);//sleeps for 1 second
    }
    return 0;
}