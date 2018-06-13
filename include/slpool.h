#ifndef SLPOOL_H
#define SLPOOL_H

#include <new>      // std::ceil()
#include <cmath>    // std::bad_alloc()

#include <forward_list>

#include "StoragePool.h"
#include "../include/list/list.h"

class SLPool : public StoragePool
{
public:

    // Construtores e destrutor

    explicit SLPool(size_t);
    ~SLPool();

    // Métodos que podem ser chamados pelo cliente

    /*!
     * Requisita uma quantidade de memória expressa em bytes e 
     * passada como argumento. O retorno é um ponteiro para a região reservada.
     */
    void * Allocate( size_t );
    /*!
     * Recebe um ponteiro para uma região reservada e a libera para uso posterior
     * pelo GM, no caso o memory pool.
     */
    void Free( void * );
    void Release(void *);

private:

    // Estruturas internas (desconhecidas pelo cliente)

    struct Header
    {
        /// Quantidade reservada.
        unsigned int m_lenght;
        Header() : m_lenght(0u) {}
    };

    struct Block : public Header
    {
        /// Quantidade padrão utilizado de um bloco, ou seja, cada bloco tem 16 bytes.
        enum { BlockSize = 16 };

        union{
            /// Apontador para o próximo bloco, ou nullptr.
            Block *m_next;
            /// Quantidade de espaço de dados cedido ao cliente.
            byte m_raw[ BlockSize - sizeof(Header)];
        };

        Block() : Header(), m_next( nullptr ){ /* Empty */}
    };

    // Apelidos para tipos definidos
    using list = std::forward_list<Block*>;

    // Métodos utilitários
    void _insert(Block * block);

    // Membros da classe

    /// Lista de blocos.
    ls::list<Block> m_Free_Memory;
    /// Cabeça da lista.
    Block m_sentinel;
    /// Fim da lista.
    Block* m_pool;


};

#endif // SLPOOL_H
