#ifndef SLPOOL_H
#define SLPOOL_H

#include <new>      // std::bad_alloc()
#include <cmath>    // std::ceil()
#include <set>      // std::set
#include <iomanip>  // std::setw(), std::setfill()

#include "StoragePool.h"
#include "set.h"

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
    void storageView() const;

private:

    // Estruturas internas (desconhecidas pelo cliente)

    struct Header
    {
        unsigned m_lenght;
        Header() : m_lenght(0u) {}
    };
    struct Block : Header
    {
        enum {BlockSize = 16};
        union{
            Block* m_next;
            unsigned char m_raw[BlockSize - sizeof(Header)];
        };

        Block() : m_next( nullptr ) { /* Empty */}
    };

    // Apelidos para tipos definidos
    using set_ = set<Block*>;

    // Membros da classe
    set_ m_free_area;
    Block* m_sentinel;
    Block* m_pool;

};

#endif // SLPOOL_H
