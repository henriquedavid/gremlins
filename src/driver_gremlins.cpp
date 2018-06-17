#include <iostream>

#include "../include/slpool.h"
#include "../include/mempool_common.h"

using byte = char;

int main( void )
{
    SLPool sl(128);
//    SLPool sa(44);

    int* b = new(sl) int;
    *b = 4;
/*
    int * a = new(sl) int;
    *a = 1;

    std::cout << "Saída: " << *b << std::endl;

    delete a;*/
    delete b;
	return 0;
}
