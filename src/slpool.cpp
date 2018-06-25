#include "slpool.h"
#include <iostream>

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
    // Coloca o primeiro bloco na lista de áreas livres
    m_free_area.insert(m_pool);
}

SLPool::~SLPool()
{
    delete [] m_pool;
    m_free_area.clear();
}

void* SLPool::Allocate(size_t size)
{

    // Iteradores
    auto curr(m_free_area.begin());
    auto end(m_free_area.cend());
    // Calcula os blocos necessários para guardar o header e o ponteiro do usuário
    unsigned int blocks_required = std::ceil((size + sizeof(Header)) / Block::BlockSize);
    // Procura a primeira área livre com tamanho suficiente
    while(curr != end)
    {
        // FIRST-FIT
        if((*curr)->m_lenght == blocks_required){
            Block * new_block = *curr;
            new_block->m_lenght = blocks_required;
            new_block->m_next = nullptr;
            
            m_free_area.erase(curr);

            m_sentinel->m_next = nullptr;

        }

        if((*curr)->m_lenght > blocks_required)
        {
            // Endereço onde será colocado o conteúdo
            Block* new_block = *curr;
            // Tamanho da aréa antes da alocação
            auto old_lenght = new_block->m_lenght;
            // Atribui o novo tamanho da área
            new_block->m_lenght = blocks_required;
            // Verifica se o cliente não ocupou o tamanho da área livre
            if(blocks_required != old_lenght)
            {
                // Nova área livre criada
                Block* new_block_after = new_block + blocks_required;
                // Tamanho da área livre criada
                new_block_after->m_lenght = old_lenght - blocks_required;
                // O next do novo bloco é o mesmo do bloco antigo
                new_block_after->m_next = new_block->m_next;
                // Reseta endereço do next antigo
                new_block->m_next = nullptr;
                // Remove a área antiga do container ordenado
                m_free_area.erase(curr);
                //  Insere no container ordenado
                auto it = m_free_area.insert(new_block_after).first;
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
                    m_sentinel->m_next = new_block_after;
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
            return new_block->m_raw;
        }
        ++curr;
    }
    throw std::bad_alloc();

}

void SLPool::Free(void * pointer)
{

    // Recupera o bloco com o tamanho
    auto block = reinterpret_cast<Block*>(reinterpret_cast<byte*>(pointer) - sizeof(Block*));

    auto ptPostReserved = m_free_area.upper_bound(block);

    // Caso especial da lista de áreas vazia
    if(m_free_area.empty())
    {
        block->m_next = nullptr;
        m_free_area.insert(block);
        m_sentinel->m_next = block;
        return;
    }
    // Verifica a área precede uma área livre
    if(ptPostReserved != m_free_area.end())
    {
        // Caso 1: Juntar as áreas
        if(*ptPostReserved == block + block->m_lenght)
        {
            // Tamanho: Muda novo
            block->m_lenght += (*ptPostReserved)->m_lenght;
            // Next: Muda do novo
            block->m_next = (*ptPostReserved)->m_next;
            // Mudança no endereço da área livre: remove o antigo e insere o novo
            ptPostReserved = m_free_area.erase(ptPostReserved);
        }
        // Caso 2: Encadear os blocos
        else
        {
            // Tamanho: Permanece
            // Next: Muda
            block->m_next = (*ptPostReserved);
            // Encadeamento insere sempre na lista ordenada
        }
    }
    else
    {
        block->m_next = nullptr;
    }

    if(m_free_area.empty())
    {
        m_sentinel->m_next = block;
        m_free_area.insert(block);
        return;
    }
    auto ptPrevReserved = ptPostReserved;
    --ptPrevReserved;
    // Verifica se o endereço anterior ao upper_bound não é maior que o do bloco
    // Caso isso aconteça, não existe bloco anterior
    if(*ptPrevReserved < block)
    {
        //std::cout << "entrou\n";
        // Caso 1: Juntar os blocos
        if(block == block + block->m_lenght)
        {
            // Tamanho: Muda anterior
            (*ptPrevReserved)->m_lenght += block->m_lenght;
            // Next: Muda o next
            (*ptPrevReserved)->m_next = block;
        }
        // Caso 2: Encadear os blocos
        else
        {
            // Tamanho: Permanece anterior
            // Next: Muda
            block->m_next = nullptr;
            (*ptPrevReserved)->m_next = block;
            // Encadeamento insere sempre na lista ordenada
            m_free_area.insert(block);
        }
    }
    // Se não há àrea anterior, inseri o bloco na lista
    else
    {
        m_sentinel->m_next = block;
        m_free_area.insert(block);
    }
    //std::cout << "Free Finalizado\n";
}
void SLPool::print_memory_pool() const
{
    /* Notação:
     * *    = Bloco reservado
     * -    = Bloco livre;
     * []   = Área
     * N    = Indice da área na pool
     */

    auto current_ptr_block = m_pool;
    auto current_free_area = m_free_area.begin();
    std::cout << "Estado do memory pool: ";

    // Para cada block que compoem o pool, faremos:
    while(false)
    {
        // Quantidades de blocos da área
        auto lenght = current_ptr_block->m_lenght;
        // O bloco atual compoem uma área livre
        if(current_ptr_block == *current_free_area)
        {
            std::cout << '[' << std::setw(lenght) << std::setfill('-') << ']';
            ++current_free_area;
        }
        // O bloco atual compoem uma área reservada
        else
        {
            std::cout << '[' << std::setw(lenght) << std::setfill('-') << ']';
        }
        current_ptr_block += lenght;
    }
    // Imprime as informações do blocos
    std::cout << "\nInformação do sentinela: next = " << m_sentinel->m_next;

    std::cout << "\nInformações das áreas livres: \n";
    current_ptr_block = m_sentinel->m_next;
    while(current_ptr_block != nullptr)
    {
        std::cout   << "{\n  Tamanho: " << (current_ptr_block)->m_lenght         \
                    << "\n  Endereço: " << (current_ptr_block)                   \
                    << "\n  Next:     " << (current_ptr_block)->m_next << "\n}\n";
        current_ptr_block = current_ptr_block->m_next;
    }

    // Imprimi os bytes armazenados nos blocos ocupados
    current_ptr_block = m_pool;
    current_free_area = m_free_area.begin();
    uint block_count = 0;

    std::cout << "\nMapa de bytes: \n" << std::hex << std::setfill('0');
    while(current_ptr_block != m_sentinel)
    {
        // Imprimi área livre
        if(current_ptr_block == *current_free_area)
        {
            auto lenght = current_ptr_block->m_lenght;
            for(uint c = 0; c < lenght; c++, block_count++)
            {
                std::cout << "Bloco " << block_count << ": Não usado.\n";
            }
            ++current_free_area;
            current_ptr_block += lenght;
        }
        // Imprimi informação do bloco
        else
        {
            auto size = Block::BlockSize - sizeof(Header);
            auto ptr = reinterpret_cast<unsigned char*>(current_ptr_block->m_raw);
            std::cout << "Bloco " << block_count << " - tamanho: " << current_ptr_block->m_lenght;
            std::cout << "\nBloco " << block_count << " - bytes: [ ";
            for(uint c = 0; c < size; c++, ptr++)
            {
                std::cout << "0x" << *ptr + 0 << ' ';
            }
            std::cout << "]\n";
            block_count++;
            current_ptr_block++;
        }
    }
    std::cout << std::dec;
}

void SLPool::storageView() const{

    auto curr(m_pool);
    auto curr_free(m_free_area.begin());

    std::cout << "[";
    while(curr != m_sentinel){

        if( curr == *curr_free ){
            std::cout << std::setw(curr->m_lenght) << std::setfill('-') << "";
            curr += curr->m_lenght;
            curr_free++;
        } else{
            std::cout << "#";
            curr++;
        }

    }

    std::cout << "]\n";

}
