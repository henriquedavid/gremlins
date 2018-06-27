#include "../include/set.h"
/*
/// Construtor padrão.
template < typename T >
set<T>::set(int size_)
{
	m_area = new T[size_];
	m_size = 0;
	m_capacity = size_;
}

template < typename T >
set<T>::~set(){
	delete [] m_area;
}

/// Insere elementos no set de forma que eles fiquem ordenados por tamanho.
template < typename T >
std::pair<T*, bool> set<T>::insert(  const T & value ){
	if(m_size >= m_capacity){
		// Deve tratar o caso de ser necessário novo espaço?
		T * new_storage = new T[m_capacity * 2];
		m_capacity *= 2;

		auto b_(m_area);
		auto new_b(new_storage);
		auto e_(m_area+m_size);

		while(b_ != e_){
			*new_b = *b_;
			b_++;
			new_b++;
		}

		delete [] m_area;
		m_area = new_storage;
	}

	// Verifica se o elemento já pertence ao conjunto.
	auto begin_f(m_area);
	auto end_f(m_area+m_size);

	while(begin_f != end_f){
		if(value == *begin_f){
			return std::make_pair(begin_f, false );
		}
		begin_f++;
	}

	auto begin_(m_area);
	auto end_(m_area+m_size);

	// Caso de ser o primeiro elemento.
	if( m_size == 0 ){
		*begin_ = value;
		m_size++;
		return std::make_pair(begin_, true);
	}

	// Procura o local que será inserido (ficar ordenado).
	while( begin_ != end_ && value > *begin_ ){
		begin_++;
	}

	// Local onde deve ser adicionado.
	auto aux(begin_);
	
	// Após encontrar o local ele vai mover todos os elementos até aquele ponto para um espaço a frente para abrir espaço.
	while( end_ != aux ){

		// Troca os elementos.
		std::swap(*end_, *(end_-1));

		end_--;

	}

	// Insere o elemento no local correto.
	*aux = value;

	// Aumenta o tamanho
	m_size++;

	// Retorna a posição do valor inserido.
	return std::make_pair(aux,true);
}

/// Retorna o primeiro espaço.
template < typename T >
T * set<T>::begin() const{
	return m_area;
}

/// Retorna o final do set.
template < typename T >
T * set<T>::end() const{
	return m_area + m_size;
}

/// Retorna o final do set.
template < typename T >
const T * set<T>::cend(){
	return m_area + m_size;
}

/// Verificar se está vazio.
template < typename T >
bool set<T>::empty(){
	return m_size == 0;
}

/// Retornar o espaço de armazenamento
template < typename T >
int set<T>::size(){
	return m_size;
}

template < typename T >
void set<T>::print(){
	auto b(m_area);
	auto e(m_area+m_size);

	std::cout << "Set = [ ";

	if( m_size == 0 ){
		std::cout << " vazio ]\n";
		return;
	}

	while(b != e){
		std::cout << *b << " ";
		b++;
	}

	std::cout << "]" << std::endl;
}

template < typename T >
T* set<T>::upper_bound( const T & value ){
	auto b_(m_area);
	auto e_(m_area+m_size);

	while(b_ != e_){

		if(value < *b_)
			return b_;

		b_++;
	}

	return b_;

}

template < typename T >
void set<T>::clear(){

	delete [] this->m_area;
    this->m_area = new T[1];
    this->m_capacity = 1;
    this->m_size = 0;

}

template < typename T >
T * set<T>::erase( T * pos ){

	auto b_(pos);
	auto e_(m_area+m_size);

	while(b_ != e_){
		std::swap(*b_, *(b_+1));
		b_++;
	}

	m_size--;

	return pos;

}

template < typename T >
void set<T>::operator=( const set & value ){
   	m_capacity = value.m_capacity;
   	m_size = value.m_size;

   	m_area = new T[m_capacity];

   	auto beg(m_area);

   	for( auto i(value.begin()) ; i < value.end() ; i++ ){
   		*beg = *i;
   		beg++;
   	}
}
*/
