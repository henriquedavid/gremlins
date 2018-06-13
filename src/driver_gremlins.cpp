#include <iostream>

#include "../include/slpool.h"
#include "../include/mempool_common.h"


using byte = char;

int main( void )
{
    SLPool sl(128);

	
    int* b = new(sl) int;
    *b = 4;

    std::cout << "Saída: " << *b << std::endl;
	return 0;
}
