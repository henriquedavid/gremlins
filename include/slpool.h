#ifndef SLPOOL_H
#define SLPOOL_H

#include <new>      // std::bad_alloc()
#include <cmath>    // std::ceil()
#include <set>      // std::set
#include <iomanip>

#include "StoragePool.h"

#define BLOCKSIZE 16

class SLPool : public StoragePool
{
public:

    // Construtores e destrutor

    explicit SLPool(size_t);
    ~SLPool();

    // Métodos que podem ser chamados pelo cliente

    void * Allocate( size_t );
    void Free( void * );

    // Métodos de depuração
    ///
    /// \brief print_memory_pool
    /// Imprimi todas as aréas e blocos do memory pool
    void print_memory_pool() const;

private:

    // Estruturas internas (desconhecidas pelo cliente)

    struct Header
    {
        unsigned int m_lenght;
        Header() : m_lenght(0u) {}
    };

    struct Block : public Header
    {
        union{
            Block* m_next;
            char m_raw[ BLOCKSIZE - sizeof(Header)];
        };

        Block() : Header(), m_next( nullptr ){ /* Empty */}
    };

    // Apelidos para tipos definidos
    using set_ = std::set<Block*>;

    // Membros da classe
    set_ m_free_area;
    Block* m_sentinel;
    Block* m_pool;

};

#endif // SLPOOL_H
