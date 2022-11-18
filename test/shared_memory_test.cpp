#define BOOST_TEST_MODULE shared_memory_test

#include <iostream>

#include <boost/test/included/unit_test.hpp>

#include "sharedmemory.hpp"

BOOST_AUTO_TEST_CASE(test_communication) {
    const int N = 10;
    float sample_vector[N] = {12.4f, -89.452f, 0.15f, 20.f, -7351.25f, 52.154f, 2.5f, 5.0001f, -99.99f, 0.0f};

    const char shm_name[] = "SMF";

    shm::Transmitter<float> transmitter;
    transmitter.create(shm_name, 1000);

    shm::Receiver<float> receiver(shm_name);

    for (int i = 0; i < N; i++) {
        transmitter.data->push_back(sample_vector[i]);
    }
    
    for (int i = 0; i < N; i++) {
        BOOST_TEST(receiver.data->at(i) == sample_vector[i]);
    }
}