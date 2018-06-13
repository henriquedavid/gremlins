#ifndef STORAGE_POOL_H
#define STORAGE_POOL_H
#include "cstdio" // size_t

#include "list/list.h"

/*!
 *	Define um conjunto mínimo de operações que outras classes memory pool
 * devem implementar. Cada nova classe derivada deve adotar uma política
 * distinta de organização e ocupação de memória.
 */
class StoragePool
{
	public:

        using byte = char;

        virtual ~StoragePool(){}
        virtual void* Allocate( size_t ) = 0;
		virtual void Free( void * ) = 0;
        virtual void Release(void *) = 0;

};

#endif
