#include "slpool.h"
#include <iostream>

/// Construtor da SLPool (Gerenciador de Memória).
SLPool::SLPool(size_t size)
{
    // Determina a quantidade de blocos necessários a partir de size
    unsigned int blocks_required = std::ceil((size + sizeof(Header)) / (float) Block::BlockSize);
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
}

/// Realiza a alocação de memória.
void* SLPool::Allocate(size_t size)
{

    // FIRST-FIT

    #ifndef FIRSTFIT

    // Quantidade de blocos necessários.
    unsigned int blocks_required = std::ceil((size+sizeof(Header)) / (float) Block::BlockSize);

    // O próximo bloco.
    auto curr(m_sentinel->m_next);
    // O bloco atual.
    auto last(m_sentinel);

    // Enquanto haver espaço procure.
    while( curr != nullptr ){

        // Caso em que o tamanho do bloco é exatamente igual ao necessário.
        if( curr->m_lenght == blocks_required ){

            // Desconecta o bloco da região.
            auto next_curr(curr->m_next);
            last->m_next = next_curr;

            // Retorna o bloco liberado da lista.
            return curr->m_raw;
        }

        else if( curr->m_lenght > blocks_required ){

            auto curr_2(curr+blocks_required);

            Block* new_block = curr_2;
            new_block->m_lenght = curr->m_lenght - blocks_required;
            new_block->m_next = curr->m_next;

            curr->m_lenght = blocks_required;

            // Desconecta o bloco anterior e conecta com o novo.
            last->m_next = new_block;

            // Desconecta o bloco anterior e conecta com o novo.

            return curr->m_raw;

        } else{
                last = curr;
                curr = curr->m_next;
        }
    }
    throw std::bad_alloc();

    #endif

    #ifdef BESTFIT

    // Quantidade de blocos necessários.
    unsigned int blocks_required = std::ceil((size+sizeof(Header)) / Block::BlockSize);

    // O próximo bloco.
    auto curr(m_sentinel->m_next);
    // O bloco atual.
    auto last(m_sentinel);

    // Enquanto haver espaço procure.
    while( curr != nullptr ){

        // Caso em que o bloco é exatamente igual ao necessário.
        if( curr->m_lenght == blocks_required ){

            // Desconecta o bloco da região.
            auto next_curr(curr->m_next);
            last->m_next = next_curr;

            // Retorna o bloco liberado da lista.
            return curr;
        }

        else if( curr->m_lenght > blocks_required ){

            auto proc_menor(curr->next);
            auto proc_atual(curr);


            while(proc_atual != nullptr){

                if(curr->m_lenght < proc_atual->m_lenght && proc_menor->m_lenght < proc_atual->m_lenght)
                    proc_menor = proc_atual;

                proc_atual = proc_atual->m_next;
            }

            curr = proc_menor;

            auto curr_2(curr+blocks_required);    // 1U significa para não haver a perda de 1 byte.
            curr_2->m_next = curr->m_next;

            Block* new_block = curr_2;
            new_block->m_lenght = curr->m_lenght - blocks_required;

            curr->m_lenght = blocks_required;

            // Desconecta o bloco anterior e conecta com o novo.
            last->m_next = new_block;

            curr->m_next = nullptr;

            return curr;

        } else{
                last = curr;
                curr = curr->m_next;
        }
    }
    throw std::bad_alloc();

    #endif
    throw std::bad_alloc(); 
}

void SLPool::Free( void * pointer ) 
{
    auto pt = reinterpret_cast<Block*>(reinterpret_cast<byte*>(pointer) - sizeof(Block*));
    // Iteradores
    auto ptPrev = m_sentinel;
    auto ptPost = m_sentinel->m_next;
    // Objetivo procurar a área antes do bloco

    // Enquanto o atual for menor prossiga
    while(ptPost < pt)
    {
        ptPrev = ptPost;
        ptPost = ptPost->m_next;
    }
    // Caso 1: Área livre predessessora
    // Imediatamente antes
    if(ptPrev + ptPrev->m_lenght == pt)
    {
            ptPrev->m_lenght += pt->m_lenght;
            // O next que fica é do de prev
            pt = ptPrev;
    }
    // Encadeia com prev
    else
    {
        pt->m_next = ptPost;
        ptPrev->m_next = pt;
    }
    // Caso 2: Área livre sucessora
    // Imediatamente depois
    if(pt + pt->m_lenght == ptPost)
    {
        // next quer permance eh o do pt
        pt->m_next = ptPost->m_next;
    }
    // Encadeado
    else
    {
        pt->m_next = ptPost;
    }

}
/*
void SLPool::Free( void * pointer ){

    auto ptReserved = reinterpret_cast<Block*>(pointer);

    auto ptPrevReserved(m_sentinel);
    auto ptPosReserved(m_sentinel->m_next);

    while(ptPosReserved != nullptr || ptPosReserved != nullptr ){
        ptPrevReserved = ptPosReserved;
        ptPosReserved = ptPosReserved->m_next;
    }

    std::cout << "TESTETESTETESTETESTETESTETESTETESTETESTETESTETESTETESTETESTETESTETESTE\n";

    ptPrevReserved->m_next = ptReserved;
    ptReserved->m_next = ptPosReserved;

    // Anterior e Posterior são livres.
    if(ptReserved-(ptPrevReserved->m_lenght) == ptPrevReserved && ptReserved+(ptReserved->m_lenght) == ptPosReserved){

        ptPrevReserved->m_lenght += ptReserved->m_lenght + ptPosReserved->m_lenght;
        ptReserved = nullptr;
        ptPosReserved = nullptr;

    }
    // Anterior e Posterior são reservadas.
    else if(ptReserved-(ptPrevReserved->m_lenght) != ptPrevReserved && ptReserved+(ptReserved->m_lenght) != ptPosReserved){
        // Não faz nada pois já está adicionada.
    }
    // Anterior é reservada e posterior é livre.
    else if(ptReserved-(ptPrevReserved->m_lenght) != ptPrevReserved && ptReserved+(ptReserved->m_lenght) == ptPosReserved){
        ptReserved->m_lenght += ptPosReserved->m_lenght;
        ptPosReserved = nullptr;
    }
    // Anterior é livre e posterior é reservada.
    else{
        ptPrevReserved->m_lenght += ptReserved->m_lenght;
        ptReserved = nullptr;
    }

}
*/
void SLPool::storageView(){

    auto current(m_sentinel->m_next);

    std::cout << "\n\nDados das áreas livres: " << std::endl;

    while( current != nullptr ){
        std::cout << "Tamanho: " << current->m_lenght << " | Endereço: "<< current << " | Next: " << (current->m_next) << std::endl;
        current = current->m_next;
    }

    std::cout << "Visualização gráfica:\n";

    current = m_pool;

    std::cout << "[";

    while(current != m_sentinel){

        if(verificaLivre(current)){
            std::cout << std::setw(current->m_lenght) << std::setfill('-') << "";
            current += current->m_lenght;
        } else{
            std::cout << "#";
            current++;
        }


    }
    std::cout << "]\n" << std::endl;

}

bool SLPool::verificaLivre( Block * block_ ){

    auto curr(m_sentinel->m_next);

    while(curr != nullptr){
        if(curr == block_)
            return true;
        curr = curr->m_next;
    }

    return false;
}
