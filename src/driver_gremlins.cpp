#include <iostream>
#include <random>
#include <chrono>
#include <vector>

#include "slpool.h"
#include "mempool_common.h"
#include "storagepooltest.h"

class Conta
{
    int id;
    int agencia;
    unsigned int saldo;
};


        /***************************************
         * --- Teste do gerenciador SLPool --- *
         * *************************************/

void ocupacao_memoria(SLPool & sl);

void desempenho_sistemas(){

    std::cout << "#################     COMPARAÇÃO DO SLPOOL COM O DO SO    #################\n\n";
    
    std::vector<double> sl_;
    std::vector<double> sys;
    
    SLPool sl(16000);

    for( auto i(0) ; i < 1000 ; i++ ){


        Conta** contas = new Conta*[10000];

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

    for( auto i(0) ; i < 1000 ; i++ ){


        Conta** contas = new Conta*[1000];


          std::chrono::steady_clock::time_point first_ = std::chrono::steady_clock::now();
        for(auto j(0) ; j < 1000 ; j++ )
        {
            contas[j] = new Conta();
        }

        for(auto j(0) ; j < 1000 ; j++ )
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

    std::cout << "------------------------------------------\n";

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
    sl.print_memory_pool();
    sl.storageView(); // <-----------------------------------
    delete b;
    delete c;


    delete d;
    delete e;
    delete g;
    delete h;

    sl.storageView();

//    delete f;

    int* i = new(sl) int;
    *i = 2111;
    sl.print_memory_pool();


    sl.storageView();   
}

int main( void )
{

    /// --- USO DO GERENCIADOR DE MEMÓRIA PELO CLIENTE --- ////
    ///  ------------------------------------------------  ////
    /// | Aqui será colocado todo o código que usa o     | ////
    /// | gerenciador de mémoria.                        | ////
    ///  ------------------------------------------------  ////
    /// --- USO DO GERENCIADOR DE MEMÓRIA PELO CLIENTE --- ////

//    SLPool sl(200);

//    int* b = new(sl) int;


//    *b = 54353453;
//    sl.storageView();

//    sl.print_memory_pool();

//    delete b;

//    sl.print_memory_pool();

//    std::cout << "Saída: " << *b << std::endl;




    /// --- xxXXxxXXxx TESTE DE DESEMPENHO xxXXxxXXxx ---  ////
    ///  ------------------------------------------------  ////
    /// | Aqui serão colocadore os teste de comparação   | ////
    /// | do uso gerenciador de mémoria e da alocação    | ////
    /// | padrão utilizado pelo sistema operacional.     | ////
    ///  ------------------------------------------------  ////
    /// --- xxXXxxXXxx TESTE DE DESEMPENHO xxXXxxXXxx ---  ////

    
    desempenho_sistemas();

    std::cout << "#################     OCUPAÇÃO DA MEMÓRIA    #################\n";

//    SLPool sl_2(200);

//    ocupacao_memoria(sl_2);

	return 0;
}
