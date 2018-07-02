/**
 * @file test_mp_integrity.cpp
 *
 * @description
 * Test the MP's data integrity after basic allocate/free operations.
 *
 *
 * @autho	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2018, July 1st.
 */

//#include "storage_pool.h"
#include "../include/singly_linked_pool.h"
#include "../include/mempool_common.h"

int main( )
{
    using chunk = char; // a bytes
    const int n_chunks(31); // 31 bytes per piece.
    // We need MP large enough to hold 7 separate chunks of memory.
    auto how_many(7); // 7 pieces of 31 bytes

    {
        // Set up 7 chunks of data. The allocation bellow should
        // make the GM reserve 14 blocks, assuming that a block
        // has 16 bytes.
        MemoryPool::SLPool p( sizeof(chunk) * n_chunks * how_many );
        //std::cout << p << std::endl;

        bool passed(false);
        chunk*  vet[ how_many ];  // Array of chunk pointer to be allocated.

        // Define the chunk length so that it corresponds to two blocks of memory.
        auto chunk_len(32-8-8) ; // 32 - 8 (tag) - 8 (header) bytes.

        // Reference value.
        chunk reference[ ] = "123456789012345";

        // Fill up the MP.
        for( auto i(0) ; i < how_many ; ++i )
        {
            vet[i] = new (p) chunk [chunk_len];
            strcpy( vet[i], "123456789012345" );
        }

        // Test each position.
        for( auto i(0) ; i < how_many ; ++i )
        {
            passed = strcmp( reference, vet[i] ) == 0;
            if ( not passed ) break;
        }

        std::cout << ">>> Testing pool integrity after writing the entire pool... ";
        std::cout << ((passed) ? "passed!" : "failed!") << std::endl;
    }

    {
        // Set up 7 chunks of data.
        MemoryPool::SLPool p( sizeof(chunk) * n_chunks * how_many );
        //std::cout << p << std::endl;

        bool passed(false);
        chunk*  vet[ how_many ];  // Array of chunk pointer to be allocated.

        // Define the chunk length so that it corresponds to two blocks of memory.
        auto chunk_len(32-8-8) ; // 32 - 8 (tag) - 8 (header) bytes.

        // Reference value.
        chunk reference_a[ ] = "abcdefghijklmno";
        chunk reference_b[ ] = "123456789012345";

        // Fill up the MP.
        for( auto i(0) ; i < how_many ; ++i )
        {
            vet[i] = new (p) chunk [chunk_len];
            strcpy( vet[i], reference_a );
        }


        for( auto i(0) ; i < how_many ; ++i )
        {
            if ( i % 2 == 0 )
                strcpy( vet[i], reference_b );
        }

        // Test each position.
        for( auto i(0) ; i < how_many ; ++i )
        {
            if ( i%2 == 0 )
                passed = strcmp( reference_b, vet[i] ) == 0;
            else
                passed = strcmp( reference_a, vet[i] ) == 0;
            if ( not passed ) break;
        }

        std::cout << ">>> Testing pool integrity after interleaved writing... ";
        std::cout << ((passed) ? "passed!" : "failed!") << std::endl;
    }

    {
        // Set up 7 chunks of data.
        MemoryPool::SLPool p( sizeof(chunk) * n_chunks * how_many );
        //std::cout << p << std::endl;

        bool passed(false);
        chunk*  vet[ how_many ];  // Array of chunk pointer to be allocated.

        // Define the chunk length so that it corresponds to two blocks of memory.
        auto chunk_len(32-8-8) ; // 32 - 8 (tag) - 8 (header) bytes.

        // Reference value.
        chunk reference_a[ ] = "abcdefghijklmno";

        // Fill up the MP.
        for( auto i(0) ; i < how_many ; ++i )
        {
            vet[i] = new (p) chunk [chunk_len];
            strcpy( vet[i], reference_a );
        }

        // Write a different value on odd locations.
        for( auto i(0) ; i < how_many ; ++i )
        {
            if ( i % 2 == 0 )
                delete [] vet[i];
        }

        // Test each position against references.
        for( auto i(0) ; i < how_many ; ++i )
        {
            if ( i % 2 != 0 )
            {
                passed = strcmp( reference_a, vet[i] ) == 0;
                if ( not passed ) break;
            }
        }

        std::cout << ">>> Testing pool integrity after deleting even interleaved areas... ";
        std::cout << ((passed) ? "passed!" : "failed!") << std::endl;
    }
    {
        // Set up 7 chunks of data.
        MemoryPool::SLPool p( sizeof(chunk) * n_chunks * how_many );
        //std::cout << p << std::endl;

        bool passed(false);
        chunk*  vet[ how_many ];  // Array of chunk pointer to be allocated.

        // Define the chunk length so that it corresponds to two blocks of memory.
        auto chunk_len(32-8-8) ; // 32 - 8 (tag) - 8 (header) bytes.

        // Reference value.
        chunk reference_a[ ] = "abcdefghijklmno";

        // Fill up the MP.
        for( auto i(0) ; i < how_many ; ++i )
        {
            vet[i] = new (p) chunk [chunk_len];
            strcpy( vet[i], reference_a );
        }

        // Write a different value on odd locations.
        for( auto i(0) ; i < how_many ; ++i )
        {
            if ( i % 2 != 0 )
                delete [] vet[i];
        }

        // Test each position against references.
        for( auto i(0) ; i < how_many ; ++i )
        {
            if ( i % 2 == 0 )
            {
                passed = strcmp( reference_a, vet[i] ) == 0;
                if ( not passed ) break;
            }
        }

        std::cout << ">>> Testing pool integrity after deleting odd interleaved areas... ";
        std::cout << ((passed) ? "passed!" : "failed!") << std::endl;
    }
    {
        // Set up 7 chunks of data.
        MemoryPool::SLPool p( sizeof(chunk) * n_chunks * how_many );
        //std::cout << p << std::endl;

        bool passed(false);
        chunk*  vet[ how_many ];  // Array of chunk pointer to be allocated.

        // Define the chunk length so that it corresponds to two blocks of memory.
        auto chunk_len(32-8-8) ; // 32 - 8 (tag) - 8 (header) bytes.

        // Reference value.
        chunk reference_a[ ] = "abcdefghijklmno";
        chunk reference_b[ ] = "012345678901234";

        // Fill up the MP.
        for( auto i(0) ; i < how_many ; ++i )
        {
            vet[i] = new (p) chunk [chunk_len];
            strcpy( vet[i], reference_a );
        }

        // Free memory of odd positions with the array.
        for( auto i(0) ; i < how_many ; ++i )
        {
            if ( i % 2 != 0 )
                delete [] vet[i];
        }

        // Reallocate the odd locations.
        for( auto i(0) ; i < how_many ; ++i )
        {
            if ( i % 2 != 0 )
            {
                vet[i] = new (p) chunk [chunk_len];
                // new value
                strcpy( vet[i], reference_b );
            }
        }

        // Test each position against references.
        for( auto i(0) ; i < how_many ; ++i )
        {
            if ( i % 2 == 0 )
                passed = strcmp( reference_a, vet[i] ) == 0;
            else
                passed = strcmp( reference_b, vet[i] ) == 0;
            if ( not passed ) break;
        }

        std::cout << ">>> Testing pool integrity after deleting and realocating interleaved areas... ";
        std::cout << ((passed) ? "passed!" : "failed!") << std::endl;
    }

    return EXIT_SUCCESS;
}
