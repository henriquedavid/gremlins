#include <iostream>

#include "slpool.h"
#include "mempool_common.h"

using byte = char;

int main( void )
{
    SLPool sl(128);

<<<<<<< HEAD
	
=======
    int* b = new(sl) int;
    *b = 4;
>>>>>>> 5a2dc0e187a87eb40c521ea98b4ace15241825d7

    std::cout << "Saída: " << *b << std::endl;
	return 0;
}
