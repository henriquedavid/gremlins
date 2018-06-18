#ifndef STORAGE_POOL_H
#define STORAGE_POOL_H
#include "cstdio" // size_t

class StoragePool
{
public:

        using byte = unsigned char;

        virtual ~StoragePool(){}
        virtual void* Allocate( size_t ) = 0;
		virtual void Free( void * ) = 0;
};

#endif
