#include <iostream>

#include "slpool.h"
#include "mempool_common.h"

        /***************************************
         * --- Teste do gerenciador SLPool --- *
         * *************************************/

int main( void )
{

    /// --- USO DO GERENCIADOR DE MEMÓRIA PELO CLIENTE --- ////
    ///  ------------------------------------------------  ////
    /// | Aqui será colocado todo o código que usa o     | ////
    /// | gerenciador de mémoria.                        | ////
    ///  ------------------------------------------------  ////
    /// --- USO DO GERENCIADOR DE MEMÓRIA PELO CLIENTE --- ////

    SLPool sl(128);
//    sl.print_memory_pool();
    int* b = new(sl) int;
//    sl.print_memory_pool();
    *b = 4;
//    sl.print_memory_pool();
    delete b;
    sl.print_memory_pool();
//    std::cout << "Saída: " << *b << std::endl;


    /// --- xxXXxxXXxx TESTE DE DESEMPENHO xxXXxxXXxx ---  ////
    ///  ------------------------------------------------  ////
    /// | Aqui serão colocadore os teste de comparação   | ////
    /// | do uso gerenciador de mémoria e da alocação    | ////
    /// | padrão utilizado pelo sistema operacional.     | ////
    ///  ------------------------------------------------  ////
    /// --- xxXXxxXXxx TESTE DE DESEMPENHO xxXXxxXXxx ---  ////

	return 0;
}
