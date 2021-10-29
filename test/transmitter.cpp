#include "sharedmemory.hpp"
#include <iostream>
#ifdef WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

int main() {
    // #ifdef WIN32
    //     if (sizeof(char) != 2) throw std::exception("Set your chars right!");
    // #endif

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
            std::cout << ++transmitter.data->at(j) << "  ";
        }
        std::cout << std::endl;
        //sleeps for 1 second
        #ifdef WIN32
            Sleep(1000);
        #else
            usleep(1 * microsecond);
        #endif
    }
    return 0;
}