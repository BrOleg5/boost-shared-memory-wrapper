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
#include <stdexcept>

using namespace boost::interprocess;

#ifdef WIN32
/**
 * For cross communication between x86 and x64 application.
 * From stackoverflow: https://stackoverflow.com/questions/18533527/boostinterprocess-shared-memory-between-32-and-64-bit-processes
 */
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
        size_t filesize;
        bool allocated_memory_flag = false;
        #ifdef WIN32
            ManagedShMem segment;
        #else
            managed_shared_memory segment;
        #endif

        // Alias an STL compatible allocator of ints that allocates ints from the managed
        // shared memory segment.  This allocator will allow to place containers
        // in managed shared memory segments
        #ifdef WIN32
            typedef allocator<T, ManagedShMem::segment_manager> ShmemAllocator;
        #else
            typedef allocator<T, managed_shared_memory::segment_manager> ShmemAllocator;
        #endif

        // Alias a vector that uses the previous STL-like allocator
        typedef vector<T, ShmemAllocator> MyVector;

        public:

        /**
         * Data vector that is allocated in shared memory.
        */
        MyVector *data;

        /**
         * Default constructor.
         */
        Transmitter() {}

        /**
         * Initialize shared memory.
         * 
         * @param file_name name of shared memory file.
         * @param file_size size of shared memory file.
         */
        Transmitter(const char *file_name, size_t file_size) : filename(file_name), filesize(file_size) {
            create(file_name, file_size);
        }

        ~Transmitter() {
            if(allocated_memory_flag) {
                segment.destroy<MyVector>("MyVector");
            }
            #ifndef WIN32
                shared_memory_object::remove(filename);
            #endif
        }

        /**
         * Create shared memory.
         * 
         * @param file_name name of shared memory file.
         * @param file_size size of shared memory file.
         */
        void create(const char *file_name, size_t file_size) {
            filename = file_name;
            filesize = file_size;
            // First remove any old shared memory of the same name, create 
            // the shared memory segment and initialize needed resources
            #ifndef WIN32
                shared_memory_object::remove(filename);
            #endif
            #ifdef WIN32
                segment = ManagedShMem(open_or_create, filename, filesize);
            #else
                segment = managed_shared_memory(open_or_create, filename, filesize);
            #endif
            // Initialize shared memory STL-compatible allocator
            const ShmemAllocator alloc_inst (segment.get_segment_manager());

            // Construct a shared memory
            data = segment.construct<MyVector>("MyVector") (alloc_inst);
            allocated_memory_flag = true;
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

        /**
         * Data vector that is allocated in shared memory.
        */
        MyVector* data;

        /**
         * Default constructor.
         */
        Receiver() {}

        /**
         * Initialize shared memory.
         * 
         * @param file_name name of shared memory file.
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
            if (data == 0) {
                throw std::runtime_error("Don't find MyVector.\n");
            }
        }
        ~Receiver() {}

        /**
         * Copy assignment.
         * 
         * @param other Receiver object.
         */
        Receiver& operator=(const Receiver& other) {
            // Guard self assignment
            if (this == &other) {
                return *this;
            }

            filename = other.filename;
            // Connect to the already created shared memory segment
            // and initialize needed resources
            #ifdef WIN32
                segment = ManagedShMem(open_only, filename);
            #else
                segment = managed_shared_memory(open_only, filename);
            #endif
            // Find the array
            data = segment.find<MyVector>("MyVector").first;
            if (data == 0) {
                throw std::runtime_error("Don't find MyVector.\n");
            }
            return *this;
        }
    };
}

#endif