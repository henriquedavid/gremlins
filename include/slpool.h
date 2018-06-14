#ifndef SLPOOL_H
#define SLPOOL_H

#include <new>      // std::ceil()
#include <cmath>    // std::bad_alloc()

#include <forward_list>

#include "StoragePool.h"
#include "list.h"

class SLPool : public StoragePool
{
public:

    // Construtores e destrutor

    explicit SLPool(size_t);
    ~SLPool();

    // Métodos que podem ser chamados pelo cliente

    void * Allocate( size_t );
    void Free( void * );
    void Release(void *);

private:

    // Estruturas internas (desconhecidas pelo cliente)

    struct Header
    {
        unsigned int m_lenght;
        Header() : m_lenght(0u) {}
    };

    struct Block : public Header
    {
        enum { BlockSize = 16 };

        union{
            Block* m_next;
            char m_raw[ BlockSize - sizeof(Header)];
        };

        Block() : Header(), m_next( nullptr ){ /* Empty */}
    };

    // Apelidos para tipos definidos
    using list = std::forward_list<Block*>;
//    using list = ls::list<Block*>;
    // Métodos utilitários
    void _insert(Block * block);

    // Membros da classe

    list m_free_area;
    Block m_sentinel;
    Block* m_pool;


};

#endif // SLPOOL_H
