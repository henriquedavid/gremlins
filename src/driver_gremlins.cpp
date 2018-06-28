#include <iostream>
#include <random>
#include <chrono>
#include <vector>

//#include "../include/set.h"
#include "slpool.h"
#include "mempool_common.h"
#include "storagepooltest_exec.h"

/*
class Conta
{
    int id;
    int agencia;
    unsigned int saldo;
};*/


        /***************************************
         * --- Teste do gerenciador SLPool --- *
         * *************************************/

/*
/// Teste básico para realizar o teste de forma a verificar como está sendo a ocupação de memória.
void ocupacao_memoria(SLPool & sl);


/// Testar o desempenh de forma a comparar o SLPool com o do Sistema Operacional criando contas de banco.
void desempenho_sistemas(void){

    std::cout << "#################     COMPARAÇÃO DO SLPOOL COM O DO SO    #################\n\n";
    
    std::vector<double> sl_;
    std::vector<double> sys;


    SLPool sl(160000);

    for( auto i(0) ; i < 10000 ; i++ ){


        Conta** contas = new Conta*[100000];

        std::chrono::steady_clock::time_point first_sl = std::chrono::steady_clock::now();

        for(auto j(0) ; j < 100 ; j++ )
        {
            contas[j] = new(sl) Conta;
        }

        for(auto j(0); j < 100; j++ )
        {
            delete contas[j];
        }
        std::chrono::steady_clock::time_point end_sl = std::chrono::steady_clock::now();


        delete contas;

        double durat_sl = std::chrono::duration_cast<std::chrono::nanoseconds>( end_sl - first_sl ).count();

        sl_.push_back(durat_sl);

    }

    for( auto i(0) ; i < 10000 ; i++ ){


        Conta** contas = new Conta*[100000];


          std::chrono::steady_clock::time_point first_ = std::chrono::steady_clock::now();
        for(auto j(0) ; j < 100 ; j++ )
        {
            contas[j] = new Conta();
        }

        for(auto j(0) ; j < 100 ; j++ )
        {
            delete contas[j];
        }

        std::chrono::steady_clock::time_point end_ = std::chrono::steady_clock::now();

        double durat_ = std::chrono::duration_cast<std::chrono::nanoseconds>( end_ - first_ ).count();

        sys.push_back(durat_);
    }

    double slpool_time = 0;
    double slpool_system = 0;

    for(auto & i : sl_ )
        slpool_time += i;
    
    for(auto & i : sys )
        slpool_system += i;

    slpool_time /= sl_.size();
    slpool_system /= sys.size();

    std::cout << "Média de Tempo de Criação Usando SLPool:   " << slpool_time << " nanosegundos." << std::endl;
    std::cout << "Média de Tempo de Criação Usando SO:       " << slpool_system << " nanosegundos.\n\n" << std::endl;

}

void ocupacao_memoria(SLPool & sl){


    int* a = new(sl) int;
    *a = 1000;
    sl.storageView();

    int* b = new(sl) int;
    *b = 10;
    sl.storageView();

    int* c = new(sl) int;
    *c = 2156;
    sl.storageView();

    int* d = new(sl) int;
    *d = 8552;
    sl.storageView();

    int* e = new(sl) int;
    *e = 321531;
    sl.storageView();

    int* f = new(sl) int;
    *f = 1000;
    sl.storageView();

    int* g = new(sl) int;
    *g = 56461123;
    sl.storageView();

    int* h = new(sl) int;
    *h = 4162111;
    sl.storageView();

    delete a;
    delete b;
    delete c;
    sl.print_memory_pool();
    sl.storageView(); 

    delete d;
    delete e;
    delete g;
    delete h;

    sl.storageView();


    int* i = new(sl) int;
    *i = 2111;
    sl.print_memory_pool();

    sl.storageView();

    delete f;
    sl.storageView();   
}
*/int main( void )
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
/*
    
    std::cout << "------> Código para testar o desempenho de SLPool, de maneira a comparar com o SO. (Critério 7)\n";

    //desempenho_sistemas();

    std::cout << "#################     OCUPAÇÃO DA MEMÓRIA    #################\n";
    
    std::cout << "------> Código de visualização do mapa de memória do SLPool para fins de depuração. (Critério 8)\n";*/
    /*
        Os métodos da SLPool:
                storageView(); e
                print_memory_pool() servem para visualizar a memória.
    */

    //SLPool sl_2(200);
    //ocupacao_memoria(sl_2);

    //StoragePoolTest( sl_2, 1);

	return 0;
}
