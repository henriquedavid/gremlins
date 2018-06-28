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
    // Coloca o primeiro bloco na lista de áreas livres
    m_free_area.insert(m_pool);
}

/// Destrutor da SLPool (Gerenciador de Memória).
SLPool::~SLPool()
{
    delete [] m_pool;
    m_free_area.clear();
}

/// Realiza a alocação de memória.
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
            m_free_area.erase(curr);   
            m_sentinel->m_next = *m_free_area.begin();
            return new_block->m_raw;
        }
        else if((*curr)->m_lenght > blocks_required)
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

/// Realiza a liberação da memória.
void SLPool::Free(void * pointer)
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

/// Imprime uma visualização do mapa de memória.
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
            std::cout << "Bloco " << block_count << " - bytes: [ ";
            for(uint c = 0; c < size; c++, ptr++)
            {
                std::cout << "0x" << std::setw(2) << std::setfill('0') << *ptr + 0 << ' ';
            }
            std::cout << "]\n";
            block_count++;
            current_ptr_block++;
        }
    }
    std::cout << std::dec;

}

/// Imprime visualização de memória de forma a mostrar os blocos ocupados.
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
