#ifndef MEMPOOL_COMMON_H
#define MEMPOOL_COMMON_H

struct Tag
{
 StoragePool * pool ;
};


void * operator new( size_t bytes, StoragePool & p )
{
	Tag * const tag = reinterpret_cast<Tag *> (p.Allocate(bytes + sizeof(Tag)) );
	tag->pool = &p;
	return ( reinterpret_cast<void *> ( tag+1U ) );
}


void operator delete( void * ptr) noexcept
{
	Tag * const tag = reinterpret_cast<Tag *>( ptr ) - 1U;
	if( nullptr != tag->pool )
		tag->pool->Release( tag );
	else
		std::free( tag );
}

#endif
