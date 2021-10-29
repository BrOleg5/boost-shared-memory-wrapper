#include "sharedmemory.hpp"
#include <iostream>
#ifdef WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

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
        //sleeps for 1 second
        #ifdef WIN32
            Sleep(1000);
        #else
            usleep(1 * microsecond);
        #endif
    }
    return 0;
}