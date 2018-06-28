#include <iostream>
#include <random>
#include <chrono>
#include <vector>

#include "slpool.h"
#include "mempool_common.h"
#include "storagepooltest_exec.h"

int main( void )
{

    /// --- USO DO GERENCIADOR DE MEMÓRIA PELO CLIENTE --- ////
    ///  ------------------------------------------------  ////
    /// | Aqui será colocado todo o código que usa o     | ////
    /// | gerenciador de mémoria.                        | ////
    ///  ------------------------------------------------  ////
    /// --- USO DO GERENCIADOR DE MEMÓRIA PELO CLIENTE --- ////


    std::cout << "------> Código cliente demonstrando que a classe SLPool funciona corretamente. (Critério 6)\n";

    SLPool sl(200);     // Solicita 200 bytes de espaço ao GM.

    int* b = new(sl) int;

    *b = 54353453;

    std::cout << "Saída: " << *b << std::endl;

    delete b;

    /// --- xxXXxxXXxx TESTE DE DESEMPENHO xxXXxxXXxx ---  ////
    ///  ------------------------------------------------  ////
    /// | Aqui serão colocadore os teste de comparação   | ////
    /// | do uso gerenciador de mémoria e da alocação    | ////
    /// | padrão utilizado pelo sistema operacional.     | ////
    ///  ------------------------------------------------  ////
    /// --- xxXXxxXXxx TESTE DE DESEMPENHO xxXXxxXXxx ---  ////


	return 0;
}
