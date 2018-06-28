#include <iostream>
#include <random>
#include <chrono>
#include <vector>

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
*/
void ocupacao_memoria()
{

  SLPool sl(60); // ( 60 + 4 ) / 16 =  4 blocos (+ sentinela)
  using data_type = int*;

  // Esperado:
  // [---- ---- ---- ----]

  std::cout << " --- Caso 1: Free no inicio ---\n";
  std::cout << "- Antes -\n";
  sl.storageView();                     // V
  data_type* a = new(sl) data_type;
  data_type* b = new(sl) data_type;
  data_type* c = new(sl) data_type;
  delete a;
  std::cout << "- Depois -\n";          // A
  sl.storageView();

  // Esperado:
  // [-##-]

  std::cout << " --- Caso 2: Free com área livre anterior adjante e área livre posterior ---\n";
  std::cout << "- Antes -\n";
  sl.storageView();                     // V
  delete b;
  std::cout << "- Depois -\n";          // A
  sl.storageView();

  // Esperado:
  // [--#-]

  std::cout << " --- Caso 3: Free sem área livre anterior e sem área livre posterior ---\n";
  std::cout << "- Antes -\n";
  sl.storageView();                     // V
  a = new(sl) data_type;
  b = new(sl) data_type;
  delete b;
  std::cout << "- Depois -\n";          // A
  sl.storageView();


  // Esperado:
  // [#-#-]

  std::cout << " --- Caso 4: Free com área livre anterior adjante e área livre posterior adjacente ---\n";
  std::cout << "- Antes -\n";
  sl.storageView();                     // V
  delete c;
  std::cout << "- Depois -\n";          // A
  sl.storageView();

  // Esperado:
  // [#---]

  std::cout << " --- Caso 5: Free com área livre posterior e anterior:  ---\n";
  std::cout << "- Antes -\n";
  sl.storageView();                     // V
  b = new(sl) data_type;
  c = new(sl) data_type;
  data_type* d = new(sl) data_type;
  delete a;
  delete c;
  std::cout << "- Depois -\n";          // A
  sl.storageView();

  // Esperado:
  // [-#-#]

  std::cout << " --- Caso 6: Free n primeira posição com mémoria cheia ---\n";
  std::cout << "- Antes -\n";
  sl.storageView();                     // V
  a = new(sl) data_type;
  c = new(sl) data_type;
  delete a;
  std::cout << "- Depois -\n";          // A
  sl.storageView();

  // Esperado:
  // [-###]

  std::cout << " --- Caso 7: Bad Alloc - lista cheia ---\n";
  std::cout << "- Antes -\n";
  sl.storageView();
  a = new(sl) data_type;
  try
  {
      data_type* e = new(sl) data_type;
      std::cout << "- Depois -\n";
      std::cout << "Erro\n";
  }
  catch(std::bad_alloc&)
  {
      std::cout << "- Depois -\n";
      sl.storageView();
  }

  delete a;
  delete b;
  delete c;
  delete d;



  // Template
  std::cout << " --- Caso :  ---\n";
  std::cout << "- Antes -\n";
  sl.storageView();                     // V
  std::cout << "- Depois -\n";          // A
  sl.storageView();

  // Esperado:
  // [----]

}
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
