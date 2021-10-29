/**
 * Wrappers is based on official Quick Guide for Impatient, in section Creating vectors in shared memory
 * @link https://www.boost.org/doc/libs/1_38_0/doc/html/interprocess/quick_guide.html
 */

#ifndef SHAREDMEMORY_HPP
#   define SHAREDMEMORY_HPP

#ifdef WIN32
    #include <boost/interprocess/managed_windows_shared_memory.hpp>
#else
    #include <boost/interprocess/managed_shared_memory.hpp>
#endif
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

using namespace boost::interprocess;

/**
 * For cross communication between x86 and x64 application.
 * From stackoverflow @link https://stackoverflow.com/questions/18533527/boostinterprocess-shared-memory-between-32-and-64-bit-processes
 */
#ifdef WIN32
using ManagedShMem = basic_managed_windows_shared_memory
    <char,
    boost::interprocess::rbtree_best_fit<
        boost::interprocess::mutex_family,
        boost::interprocess::offset_ptr<
            void,
            __int64,
            unsigned __int64,
            0>,
        0>,
    boost::interprocess::iset_index>;
#endif

namespace shm
{
    /**
     * @class Transmitter
     * @brief Boost shared memory wrapper.
     */
    template<class T>
    class Transmitter
    {
        private:

        const char *filename;
        #ifdef WIN32
            ManagedShMem segment;
        #else
            managed_shared_memory segment;
        #endif

        //Alias an STL compatible allocator of ints that allocates ints from the managed
        //shared memory segment.  This allocator will allow to place containers
        //in managed shared memory segments
        #ifdef WIN32
            typedef allocator<T, ManagedShMem::segment_manager> ShmemAllocator;
        #else
            typedef allocator<T, managed_shared_memory::segment_manager> ShmemAllocator;
        #endif

        //Alias a vector that uses the previous STL-like allocator
        typedef vector<T, ShmemAllocator> MyVector;

        public:

        MyVector *data;

        /**
         * Initialize shared memory.
         * 
         * @param file_name name of shared memory file.
         * @param file_size size of shared memory file.
         * @param data_size
         */
        Transmitter(const char *file_name, int file_size) : filename(file_name) {
            //First remove any old shared memory of the same name, create 
            //the shared memory segment and initialize needed resources
            #ifndef WIN32
                shared_memory_object::remove(filename);
            #endif
            #ifdef WIN32
                segment = ManagedShMem(create_only, filename, file_size);
            #else
                segment = managed_shared_memory(create_only, filename, file_size);
            #endif
            //Initialize shared memory STL-compatible allocator
            const ShmemAllocator alloc_inst (segment.get_segment_manager());

            //Construct a shared memory
            data = segment.construct<MyVector>("MyVector") (alloc_inst);
        }
        ~Transmitter() {
            segment.destroy<MyVector>("MyVector");
            #ifndef WIN32
                shared_memory_object::remove(filename);
            #endif
        }
    };

    /**
     * @class Receiver
     * @brief Boost shared memory wrapper.
     */
    template<class T>
    class Receiver
    {
        private:

        const char *filename;
        #ifdef WIN32
            ManagedShMem segment;
        #else
            managed_shared_memory segment;
        #endif
        //Alias an STL compatible allocator of ints that allocates ints from the managed
        //shared memory segment.  This allocator will allow to place containers
        //in managed shared memory segments
        #ifdef WIN32
            typedef allocator<T, ManagedShMem::segment_manager> ShmemAllocator;
        #else
            typedef allocator<T, managed_shared_memory::segment_manager> ShmemAllocator;
        #endif

        //Alias a vector that uses the previous STL-like allocator
        typedef vector<T, ShmemAllocator> MyVector;

        public:

        MyVector* data;

        /**
         * Initialize shared memory.
         * 
         * @param file_name name of shared memory file.
         * @param data_size element number of array type T.
         */
        Receiver(const char *file_name) : filename(file_name) {
            //Connect to the already created shared memory segment
            //and initialize needed resources
            #ifdef WIN32
                segment = ManagedShMem(open_only, file_name);
            #else
                segment = managed_shared_memory(open_only, file_name);
            #endif
            //Find the array
            data = segment.find<MyVector>("MyVector").first;
        }
        ~Receiver() {
            // segment.destroy<MyVector>("MyVector");
            // shared_memory_object::remove(filename);
        }
    };
}

#endif