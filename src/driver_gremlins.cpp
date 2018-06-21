#include <iostream>
#include <random>
#include <chrono>
#include <vector>

#include "slpool.h"
#include "mempool_common.h"
#include "../src/storagepooltest.cpp"

        /***************************************
         * --- Teste do gerenciador SLPool --- *
         * *************************************/

void ocupacao_memoria(SLPool & sl);

void desempenho_sistemas(){

    std::cout << "#################     COMPARAÇÃO DO SLPOOL COM O DO SO    #################\n\n";
    
    std::vector<double> sl_;
    std::vector<double> sys;
    
    SLPool sl(200);

    for( auto i(0) ; i < 1000 ; i++ ){

        std::cout << "Versão " << i << std::endl;

        std::chrono::steady_clock::time_point first_sl = std::chrono::steady_clock::now();
        int* a = new(sl) int;
        *a = 1000;
        //sl.storageView();
        sl.print_memory_pool();
        int* b = new(sl) int;
        *b = 10;
        //sl.storageView();
        sl.print_memory_pool();
        int* c = new(sl) int;
        *c = 2156;
        //sl.storageView();
        sl.print_memory_pool();
        int* d = new(sl) int;
        *d = 8552;
        //sl.storageView();
        sl.print_memory_pool();
        int* e = new(sl) int;
        *e = 321531;
        //sl.storageView();
        sl.print_memory_pool();
        int* f = new(sl) int;
        *f = 1000;
        //sl.storageView();
        sl.print_memory_pool();
        int* g = new(sl) int;
        *g = 56461123;
        //sl.storageView();
        sl.print_memory_pool();
        int* h = new(sl) int;
        *h = 4162111;
        //sl.storageView();
        sl.print_memory_pool();

        //sl.print_memory_pool();

        delete a;
        delete b;
        delete c;
        delete d;
        delete e;
        delete f;
        delete g;
        delete h;

        //sl.storageView();
        sl.print_memory_pool();

        //ocupacao_memoria(sl);

        std::chrono::steady_clock::time_point end_sl = std::chrono::steady_clock::now();
        double durat_sl = std::chrono::duration_cast<std::chrono::nanoseconds>( end_sl - first_sl ).count();

        sl_.push_back(durat_sl);

    }

    for( auto i(0) ; i < 1000 ; i++ ){


        std::chrono::steady_clock::time_point first_ = std::chrono::steady_clock::now();
        int* a_ = new int;
        *a_ = 1000;
        int* b_ = new int;
        *b_ = 10;
        int* c_ = new int;
        *c_ = 2156;
        int* d_ = new int;
        *d_ = 8552;
        int* e_ = new int;
        *e_ = 321531;
        int* f_ = new int;
        *f_ = 1000;
        int* g_ = new int;
        *g_ = 56461123;
        int* h_ = new int;
        *h_ = 4162111;
        delete a_;
        delete b_;
        delete c_;
        delete d_;
        delete e_;
        delete f_;
        delete g_;
        delete h_;

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

    std::cout << "Média de Tempo de Criação Usando SLPool: " << slpool_time << " nanosegundos." << std::endl;
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
    delete b;
    delete c;
    sl.storageView();

    delete d;
    delete e;
    delete g;
    delete h;

    sl.storageView();

    delete f;

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

    SLPool sl(200);

    int* b = new(sl) int;


    *b = 54353453;
    sl.storageView();

    sl.print_memory_pool();

    delete b;

    sl.print_memory_pool();

    std::cout << "Saída: " << *b << std::endl;




    /// --- xxXXxxXXxx TESTE DE DESEMPENHO xxXXxxXXxx ---  ////
    ///  ------------------------------------------------  ////
    /// | Aqui serão colocadore os teste de comparação   | ////
    /// | do uso gerenciador de mémoria e da alocação    | ////
    /// | padrão utilizado pelo sistema operacional.     | ////
    ///  ------------------------------------------------  ////
    /// --- xxXXxxXXxx TESTE DE DESEMPENHO xxXXxxXXxx ---  ////

    
    desempenho_sistemas();

    std::cout << "#################     OCUPAÇÃO DA MEMÓRIA    #################\n";

    SLPool sl_2(200);

    ocupacao_memoria(sl_2);

	return 0;
}
