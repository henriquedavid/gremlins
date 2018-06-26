#include <iostream>

#include "../../include/set.h"

int main(){

	set<int> test(4);

	// Inserir - Correto.
	test.print();
	test.insert(3);
	test.print();
	test.insert(2);
	test.print();
	test.insert(6);
	test.print();
	test.insert(5);
	test.print();

	// Empty - Correto.
	auto vaz = test.empty();

	if(vaz)
		std::cout << "Vazio!\n";
	else
		std::cout << "Não vazio!\n";

	// Clear

	test.clear();

	vaz = test.empty();

	if(vaz)
		std::cout << "Vazio!\n";
	else
		std::cout << "Não vazio!\n";

	test.print();

	// Inserir (realocação e aumento de tamanho) - Correto.
	test.print();
	test.insert(3);
	test.print();
	test.insert(2);
	test.print();
	test.insert(6);
	test.print();
	test.insert(5);
	test.insert(1);
	test.insert(4);
	test.insert(7);
	test.print();

	std::cout << "TESTE DO BEGIN E DO END E DO CEND\n";
	for( auto i(test.begin()) ; i < test.cend(); i++ ){
		std::cout << *i << " ";
	}

	std::cout << std::endl;

	std::cout << "O upper_bound de 5 é " << *(test.upper_bound(5)) << std::endl;

	test.erase(test.begin() + 3); // Remove o elemento 4

	test.print();

	std::cout << "Tamanho = " << test.size() << std::endl;

	return 0;
}