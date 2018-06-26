#ifndef SET_H
#define SET_H

template < typename T >
class set
{
public:
    set(int size_ = 1);						//!< Construtor.
    ~set();									//!< Destrutor.
    std::pair<T*, bool> insert( const T & value );			//!< Inserir um elemento de forma que fique ordenado.
    void clear();							//!< Limpar todo o conjunto.
    T * begin() const;						//!< Retornar o início do vetor.
    T * end() const;						//!< Retornar o fim do vetor.
    const T * cend();						//!< Retornar o fim do vetor cosntante.
    T * erase( T * pos );					//!< Remover um determinado elemento em uma posição.
    T * upper_bound( const T & value );		//!< Retornar o próximo maior valor que value.
    bool empty();							//!< Verificar se o vetor está vazio.
    int size();								//!< Retornar o tamanho do vetor.

    void print();							//!< Imprimir os elementos para fins de depuração.

    void operator=( const set & value );	//!< Operador de atribuição

private:
	T * m_area;
	int m_size;
	int m_capacity;
};

#include "../src/set.cpp"

#endif // SET_H
