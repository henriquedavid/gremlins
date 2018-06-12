#include "slpool.h"

SLPool::SLPool(size_t size)
{
    // Aloca espaco para armazenar a lista de blocos
    m_pool = new Block();
    // O block Pool[0] não terá próximo bloco livre, pois ele é o começo de uma área
    m_pool->m_next = nullptr;
    m_pool->m_lenght = (size_t)(size / Block::BlockSize + 0.5);
    // sentinela aponta para o primeiro bloco
    m_sentinel.m_next = m_pool;
}
SLPool::~SLPool()
{
}

void* SLPool::Allocate(size_t)
{
    return nullptr;
}

void SLPool::Free(void *)
{

}

void SLPool::Release(void *)
{

}
