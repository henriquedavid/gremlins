/**
 * @file test_mp_list.cpp
 *
 * @description
 * Test the MP's integrity after basic allocate/free operations.
 *
 * 1) Test the bad_alloc excepction (MP is full)
 * 2) Free an area between two free areas.
 * 3) Free an area between two reserved areas.
 * 4) Free an area between a reverved area (on the left) and a free area (on the right).
 * 5) Free an area between a free area (on the left) and a reserved area (on the right).
 * 6) Test if we get a single area after all memory has been freed.
 *
 * @autho	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2018, July 1st.
 */

//#include "storage_pool.h"
#include "../include/singly_linked_pool.h"
#include "../include/mempool_common.h"

int main( )
{
    // Each chunk is a 3 integer array.
    using chunk = char; // 16 bytes
    const int n_chunks(31);
    // We need MP large enough to hold 7 separate chunks of memory.
    auto how_many(7); // 7 pieces of 31 bytes

    {
        // Set up 7 chunks of data.
        MemoryPool::SLPool p( sizeof(chunk) * n_chunks * how_many );
        std::cout << p << std::endl;

        bool passed(false);
        chunk*  vet[ how_many ];  // Array of chunk pointer to be allocated.

        // Define the chunk length so that it corresponds to two blocks of memory.
        auto chunk_len(32-8-8) ; // 32 - 8 (tag) - 8 (header) bytes.

        // Fill up the MP.
        for( auto i(0) ; i < how_many ; ++i )
        {
            vet[i] = new (p) chunk [chunk_len];
            strcpy( vet[i], "123456789012345" );
            std::cout << ">>> vet = " << vet[i] << std::endl;
            std::cout << "length vet = " << strlen( vet[i] ) << std::endl;
            // Print pool
            std::cout << p << std::endl;
        }

        // Request an extra chunk to invoke an exception (overflow).
        chunk * temp(nullptr);
        try {
            temp = new (p) chunk[ chunk_len ];
        }
        catch( std::runtime_error & e )
        {
            passed = true;
        }
        catch( std::bad_alloc & e )
        {
            passed = true;
        }

        std::cout << ">>> Testing pool overflow... ";
        std::cout << ((passed) ? "passed!" : "failed!") << std::endl;
    }

    {
        // Set up 7 chunks of data.
        MemoryPool::SLPool p( sizeof(chunk) * n_chunks * how_many );
        std::cout << p << std::endl;

        chunk*  vet[ how_many ];  // Array of chunk pointer to be allocated.

        // Define the chunk length so that it corresponds to two blocks of memory.
        auto chunk_len(32-8-8) ; // 32 - 8 (tag) - 8 (header) bytes.

        // Fill up the MP.
        for( auto i(0) ; i < how_many ; ++i )
        {
            vet[i] = new (p) chunk [chunk_len];
            strcpy( vet[i], "123456789012345" );
            // Print pool
            std::cout << p << std::endl;
        }

        /*
         * Freeing up target 'x'.
         * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
         * | L | R | L | x | L | R | L |  ===>  | L | R |     L     | R | L |
         * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
         *   0   1   2   3   4   5   6            0   1   2   3   4   5   6
         */

        delete [] vet[0];
        delete [] vet[2];
        delete [] vet[4];
        delete [] vet[6];
        std::cout << p << std::endl;
        delete [] vet[3];
        std::cout << p << std::endl;
    }

    {
        // Set up 7 chunks of data.
        MemoryPool::SLPool p( sizeof(chunk) * n_chunks * how_many );
        std::cout << p << std::endl;

        chunk*  vet[ how_many ];  // Array of chunk pointer to be allocated.

        // Define the chunk length so that it corresponds to two blocks of memory.
        auto chunk_len(32-8-8) ; // 32 - 8 (tag) - 8 (header) bytes.

        // Fill up the MP.
        for( auto i(0) ; i < how_many ; ++i )
        {
            vet[i] = new (p) chunk [chunk_len];
            strcpy( vet[i], "123456789012345" );
            // Print pool
            std::cout << p << std::endl;
        }

        /*
         * Teste #2
         *
         * Freeing up target 'x'.
         * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
         * | R | L | R | x | R | L | R |  ===>  | R | L | R | L | R | R | L |
         * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
         *   0   1   2   3   4   5   6            0   1   2   3   4   5   6
         */

        delete [] vet[1];
        delete [] vet[5];
        std::cout << p << std::endl;
        delete [] vet[3];
        std::cout << p << std::endl;
    }

    {
        // Set up 7 chunks of data.
        MemoryPool::SLPool p( sizeof(chunk) * n_chunks * how_many );
        std::cout << p << std::endl;

        chunk*  vet[ how_many ];  // Array of chunk pointer to be allocated.

        // Define the chunk length so that it corresponds to two blocks of memory.
        auto chunk_len(32-8-8) ; // 32 - 8 (tag) - 8 (header) bytes.

        // Fill up the MP.
        for( auto i(0) ; i < how_many ; ++i )
        {
            vet[i] = new (p) chunk [chunk_len];
            strcpy( vet[i], "123456789012345" );
            // Print pool
            std::cout << p << std::endl;
        }

        /*
         * Teste #3
         *
         * Freeing up target 'x'.
         * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
         * | R | L | R | x | L | R | L |  ===>  | R | L | R |   L   | R | L |
         * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
         *   0   1   2   3   4   5   6            0   1   2   3   4   5   6
         */

        delete [] vet[1];
        delete [] vet[4];
        delete [] vet[6];
        std::cout << p << std::endl;
        delete [] vet[3];
        std::cout << p << std::endl;
    }

    {
        // Set up 7 chunks of data.
        MemoryPool::SLPool p( sizeof(chunk) * n_chunks * how_many );
        std::cout << p << std::endl;

        chunk*  vet[ how_many ];  // Array of chunk pointer to be allocated.

        // Define the chunk length so that it corresponds to two blocks of memory.
        auto chunk_len(32-8-8) ; // 32 - 8 (tag) - 8 (header) bytes.

        // Fill up the MP.
        for( auto i(0) ; i < how_many ; ++i )
        {
            vet[i] = new (p) chunk [chunk_len];
            strcpy( vet[i], "123456789012345" );
            // Print pool
            std::cout << p << std::endl;
        }

        /*
         * Teste #4
         *
         * Freeing up target 'x'.
         * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
         * | L | R | L | x | R | L | R |  ===>  | L | R |   L   | R | L | R |
         * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
         *   0   1   2   3   4   5   6            0   1   2   3   4   5   6
         */

        delete [] vet[0];
        delete [] vet[2];
        delete [] vet[5];
        std::cout << p << std::endl;
        delete [] vet[3];
        std::cout << p << std::endl;
    }

    {
        // Set up 7 chunks of data.
        MemoryPool::SLPool p( sizeof(chunk) * n_chunks * how_many );
        std::cout << p << std::endl;

        chunk*  vet[ how_many ];  // Array of chunk pointer to be allocated.

        // Define the chunk length so that it corresponds to two blocks of memory.
        auto chunk_len(32-8-8) ; // 32 - 8 (tag) - 8 (header) bytes.

        // Fill up the MP.
        for( auto i(0) ; i < how_many ; ++i )
        {
            vet[i] = new (p) chunk [chunk_len];
            strcpy( vet[i], "123456789012345" );
            // Print pool
            std::cout << p << std::endl;
        }

        /*
         * Teste #4
         *
         * Freeing up target 'x'.
         * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
         * | R | R | R | R | R | R | R |  ===>  |             L             |
         * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
         *   0   1   2   3   4   5   6            0   1   2   3   4   5   6
         */

        for( auto i(0) ; i < how_many ; i+=2 )
        {
            delete [] vet[i];
            // Print pool
            std::cout << p << std::endl;
        }
        for( auto i(1) ; i < how_many ; i+=2 )
        {
            delete [] vet[i];
            // Print pool
            std::cout << p << std::endl;
        }
    }


    return EXIT_SUCCESS;
}
