#include "slpool.h"
#include <iostream>
SLPool::SLPool(size_t size)
{
    // Determina a quantidade de blocos necessários a partir de size
    unsigned int blocks_required = std::ceil(size / Block::BlockSize);
    // Aloca espaco para armazenar a lista de blocos
    m_pool = new Block [blocks_required];
    // Armazena a quantidade de blocos no primeiro bloco, m_pool[0] ou *m_pool
    m_pool->m_lenght = blocks_required;
    // sentinela aponta para o primeiro bloco
    m_sentinel.m_next = m_pool;
    // Coloca o primeiro bloco na lista de áreas livres
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
    // Calcula os blocos necessários para guardar o header e o ponteiro do usuário
    unsigned int blocks_required = std::ceil( ( size + sizeof(Header) ) / Block::BlockSize);
    // Procura a primeira área livre com tamanho suficiente
    while(curr != end)
    {
        if((*curr)->m_lenght >= blocks_required)
        {
            // Endereço onde será colocado o conteúdo
            Block* new_block = *curr;
            // Tamanho da aréa antes da alocação
            auto old_lenght = new_block->m_lenght;
            // Atribui o novo tamanho da área
            new_block->m_lenght = blocks_required;
            // Verifica se o cliente ocupou o tamanho da área livre
            if((*curr)->m_lenght != old_lenght)
            {
                // Nova área livre criada
                Block* new_block_after = new_block + blocks_required;
                // Tamanho da área livre criada
                new_block_after->m_lenght = old_lenght - blocks_required;
                // O next do novo bloco é o mesmo do bloco antigo
                new_block_after->m_next = new_block->m_next;
                /// \todo: Procura pelo bloco que apontava para *curr e muda o next dele
                {
                    /// \todo: se achou: muda o next
                    /// \todo: se não achou: muda o sentinela
                }

            }

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
