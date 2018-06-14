#include "slpool.h"
#include <iostream>

SLPool::SLPool(size_t size)
{
    // Determina a quantidade de blocos necessários a partir de size
    unsigned int blocks_required = std::ceil(size / Block::BlockSize);
    // Aloca espaco para armazenar a lista de blocos
    m_pool = new Block [blocks_required];
    // Configura o espaço do sentilena
    m_sentinel.m_next = m_pool;
    // Armazena a quantidade de blocos no primeiro bloco, m_pool[0] ou *m_pool
    m_pool->m_lenght = blocks_required;
    // sentinela aponta para o primeiro bloco
    m_sentinel.m_next = m_pool;
    m_sentinel.m_lenght = 0;
    // Coloca o primeiro bloco na lista de áreas livres
    m_free_area.insert(m_pool);
}

SLPool::~SLPool()
{
    m_free_area.clear();
    if(m_pool != nullptr)
        delete [] m_pool;
}

void* SLPool::Allocate(size_t size)
{

    // Iteradores
    auto curr(m_free_area.begin());
    auto end(m_free_area.cend());
    // Calcula os blocos necessários para guardar o header e o ponteiro do usuário
    unsigned int blocks_required = std::ceil( ( size + sizeof(Header) ) / Block::BlockSize);
    // Procura a primeira área livre com tamanho suficiente
    while(curr != end)
    {
        // FIRST-FIT
        if((*curr)->m_lenght >= blocks_required)
        {
            // Endereço onde será colocado o conteúdo
            Block* new_block = *curr;
            // Tamanho da aréa antes da alocação
            auto old_lenght = new_block->m_lenght;
            // Atribui o novo tamanho da área
            new_block->m_lenght = blocks_required;
            // Verifica se o cliente não ocupou o tamanho da área livre
            if(new_block->m_lenght != old_lenght)
            {
                // Nova área livre criada
                Block* new_block_after = new_block + blocks_required;
                // Tamanho da área livre criada
                new_block_after->m_lenght = old_lenght - blocks_required;
                // O next do novo bloco é o mesmo do bloco antigo
                new_block_after->m_next = new_block->m_next;
                // O endereço do next antigo não deve ser acessível ao cliente
                new_block->m_next = nullptr;
                //  Insere no container ordenado
                auto it = m_free_area.insert(new_block).first;
                /// \todo: Procura pelo bloco que apontava para new_block e muda o next dele

                auto it_after = it;
                ++it_after;
                if(it != m_free_area.begin())
                {
                    auto it_before = it;
                    --it_before;
                    (*it_before)->m_next = new_block_after;
                }
                else
                {
                    m_sentinel.m_next = new_block_after;
                }
                if(it_after != m_free_area.end())
                {
                    new_block_after->m_next = *it_after;
                }
                else
                {
                    new_block_after->m_next = nullptr;
                }
            }
            return new_block;

        }
        ++curr;
    }
    throw std::bad_alloc();

}

void SLPool::Free(void * block)
{

    // Iterador para o bloco
    auto ptReserved = m_free_area.find(reinterpret_cast<Block*>(block));
    // Iterador para o elemento após o bloco
    auto ptPostReserved = ptReserved;
    ++ptPostReserved;
    // Verifica a área precede uma área livre
    if(ptPostReserved != m_free_area.end())
    {
        // Caso 1: Juntar os blocos
        if(*ptPostReserved == (*ptReserved) + (*ptReserved)->m_lenght + 1)
        {
            // Tamanho: Muda
            (*ptReserved)->m_lenght += (*ptPostReserved)->m_lenght;
            // Next: Muda
            (*ptReserved)->m_next = (*ptPostReserved)->m_next;
            // Mudaça no endereço da área livre: remove o antigo e insere o novo
            m_free_area.erase(ptPostReserved);
            m_free_area.insert(*ptReserved);
        }
        // Caso 2: Encadear os blocos
        else
        {
            // Tamanho: Permanece
            // Next: Muda
            (*ptReserved)->m_next = (*ptPostReserved);
            // Encadeamento insere sempre na lista ordenada
            m_free_area.insert(*ptReserved);
        }
    }
    // Verifica se há uma área livre posterior ao bloco liberado
    if(ptReserved != m_free_area.begin())
    {
        auto ptPrevReserved = ptReserved;
        ++ptPrevReserved;
        // Caso 1: Juntar os blocos
        if(*ptReserved == (*ptPrevReserved) + (*ptPrevReserved)->m_lenght + 1)
        {
            // Tamanho: Muda anterior
            (*ptPrevReserved)->m_lenght += (*ptReserved)->m_lenght;
            // Next: Permanece anterior
        }
        // Caso 2: Encadear os blocos
        else
        {
            // Tamanho: Permanece anterior
            // Next: Muda
            (*ptReserved)->m_next = (*ptPrevReserved)->m_next;
            // Next: Muda anterior
            (*ptPrevReserved)->m_next = (*ptReserved);
            // Encadeamento insere sempre na lista ordenada
            m_free_area.insert(*ptReserved);
        }
    }
}
