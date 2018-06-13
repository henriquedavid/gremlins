#include "../include/slpool.h"
#include <iostream>
SLPool::SLPool(size_t size)
{
    // Aloca espaco para armazenar a lista de blocos
    m_pool = new Block();
    // O block Pool[0] não terá próximo bloco livre, pois ele é o começo de uma área
    m_pool->m_lenght = std::ceil(size / Block::BlockSize);

    // sentinela aponta para o primeiro bloco
    m_sentinel.m_next = m_pool;
    m_free_area.push_front(m_pool);
}
SLPool::~SLPool()
{
    m_free_area.clear();
}

void* SLPool::Allocate(size_t size)
{

    // Iteradores
    auto curr_before(m_free_area.before_begin());
    auto curr(m_free_area.begin());
    auto end(m_free_area.cend());
    unsigned int blocks_required = std::ceil( ( size + sizeof(Header) ) / Block::BlockSize);

    // Procura a primeira área livre com tamanho suficiente
    while(curr != end)
    {
        if((*curr)->m_lenght >= blocks_required)
        {
            // Endereço onde será colocado o conteúdo
            Block* new_block = *curr;

            // Tamanho da aréa antes da inserção
            auto old_lenght = new_block->m_lenght;
            // Atribui o novo tamanho da área
            new_block->m_lenght = blocks_required;
            // Endereço da nova área livre
            Block* new_block_after = nullptr;

            if((*curr)->m_lenght != old_lenght)
            {
                // Nova área livre
                new_block_after = new Block();
                // O tamanho da área é o que sobrou da área antiga
                new_block_after->m_lenght = old_lenght - blocks_required;
                // O next do novo bloco aponta para a nova área livre
                new_block->m_next = new_block_after;
                // o next aponta para proxima àrea livre, se existir
                auto next_area = curr;
                ++next_area;
                if(next_area != m_free_area.end())
                {
                    new_block_after->m_next = *next_area;
                }
                else
                {
                    // Se não tiver próxima área livre e a lista tiver apenas um elemento a pŕoxima área livre será nula
                    if(curr == m_free_area.begin())
                        new_block_after->m_next = nullptr;
                    // Senão ela será o começo da lista
                    else
                        new_block_after->m_next = *m_free_area.begin();
                }
            }
            // Se o novo bloco for o inicio, estão o sentinela aponta para a nova área livre, se existir
            // Se for no começo muda o sentinela
            if(curr == m_free_area.begin())
            {
                // Se dividiu a área, a primeira área livre é a nova área livre
                if(new_block_after != nullptr)
                    m_sentinel.m_next = new_block_after;
                // Senão, será a próxima área livre, se exitir
            }
            // Tira a área da lista de áreas livres
            m_free_area.erase_after(curr_before);
            return new_block;

        }
        curr_before = curr;
        ++curr;
    }
    throw std::bad_alloc();
}

void SLPool::Free(void *)
{

}

void SLPool::Release(void *)
{
    return;
}

void SLPool::_insert(Block* new_block)
{
    // inicializa os iteradores que serão usados
    list::iterator new_block_prev = m_free_area.before_begin();
    list::iterator current_block = m_free_area.begin();
    // realiza a busca pelo primeiro endereço maior do que new_block e guarda o anterior a ele
    while(*current_block < new_block)
    {
        new_block_prev = current_block;
        ++new_block_prev;
    }
    // insere na lista imediatamente após o último elemento maior que pos
    m_free_area.insert_after(new_block_prev, new_block);

}
