#include "slpool.h"
#include <iostream>

/// Construtor da SLPool (Gerenciador de Memória).
SLPool::SLPool(size_t size)
{
    // Determina a quantidade de blocos necessários a partir de size
    unsigned int blocks_required = std::ceil((size + sizeof(Header)) / Block::BlockSize);
    // Aloca espaco para armazenar a lista de blocos e o sentinela
    m_pool = new Block [blocks_required + 1];
    // Não tem próxima área livre
    m_pool->m_next = nullptr;
    // Armazena a quantidade de blocos header do primeiro bloco
    m_pool->m_lenght = blocks_required;
    // Configura o espaço do sentilena
    m_sentinel = m_pool+blocks_required;
    // Sentinela aponta para o primeiro bloco
    m_sentinel->m_next = m_pool;
    m_sentinel->m_lenght = 0;
}

/// Destrutor da SLPool (Gerenciador de Memória).
SLPool::~SLPool()
{
    delete [] m_pool;
    //delete [] m_sentinel;
}

/// Realiza a alocação de memória.
void* SLPool::Allocate(size_t size)
{

    // Quantidade de blocos necessários.
    unsigned int blocks_required = std::ceil((size+sizeof(Header)) / Block::BlockSize);

    // O próximo bloco.
    auto curr(m_sentinel->m_next);
    // O bloco atual.
    auto last(m_sentinel);

    // Enquanto haver espaço procure.
    while( m_sentinel != nullptr ){

        // Caso em que o bloco é exatamente igual ao necessário.
        if( curr->m_lenght == blocks_required ){

            // Desconecta o bloco da região.
            auto next_curr(curr->m_next);
            last->m_next = next_curr;

            // Retorna o bloco liberado da lista.
            return curr;
        }

        else if( curr->m_lenght > blocks_required ){

            auto curr_2(curr+(curr->m_lenght) + 1U);    // 1U significa para não haver a perda de 1 byte.
            
            Block* new_block = curr_2;
            new_block->m_lenght = curr->m_lenght - blocks_required - 1U;

            curr->m_lenght = blocks_required;

            // Desconecta o bloco anterior e conecta com o novo.
            last->m_next = new_block;

            return curr;
        } else{
                last = curr;
                curr = curr->m_next;
        }
        

    throw std::bad_alloc();
}

void SLPool::Free( void * pointer )
{
    auto pt = reinterpret_cast<Block*>(reinterpret_cast<byte*>(pointer) - sizeof(Block*));
    // Iteradores
    auto ptPrev = m_sentinel;
    auto ptMiddle = m_sentinel->m_next;
    // Objetivo procurar a área antes do bloco

    // Enquanto o atual for menor prossiga
    while(ptMiddle < pt)
    {
        ptPrev = ptMiddle;
        ptMiddle = ptMiddle->m_next;
    }
    // Nesse ponto, pt prev aponta para área anterior ou sentinel, entaõ seta o next
    pt->m_next = ptPrev->m_next;
    ptPrev->m_next = pt;
    // Se não tiver área livre, o sentinela (ptprev) irá apontar para o bloco liberado
    // e o bloco liberado iá apontar para nullptr
}