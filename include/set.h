#ifndef SET_H
#define SET_H

#include <utility>

// Classe baseada na classe set com apenas as funções e os operadores usados para resolver o problemas do projeto gremlins
// Limitações:

template < typename T >
class Iterator
    {
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_reference = const T&;

        Iterator();
        ~Iterator();
        Iterator( pointer pont );
        Iterator & operator++();
        Iterator operator++(int);
        Iterator & operator--();
        Iterator operator--(int);
        Iterator operator+( int value );
        reference operator*() const;
        Iterator<T> * operator->() const;
        Iterator<T> & operator=( const Iterator<T> & rhs );
        bool operator!=(const Iterator<T> & rhs) const;
        bool operator==(const Iterator<T> & rhs) const;
        bool operator<( const Iterator<T> & rhs ) const;
    private:
        pointer m_value;
    };


template < typename T >
class set
{
public:
    // --- ALIAS ---
    using const_iterator = const Iterator<T>;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_reference = const T&;

    // Construtores e destrutor

    set(int size_ = 1);						//!< Construtor.
    ~set();									//!< Destrutor.

    // Funções que modificam o container

    std::pair<Iterator<T>, bool> insert( const_reference value );	//!< Inserir um elemento de forma que fique ordenado.
    Iterator<T> begin() const;                                     //!< Retornar o início do vetor.
    Iterator<T> end() const;                                       //!< Retornar o fim do vetor.
    const_iterator cend();                                      //!< Retornar o fim do vetor cosntante.
    Iterator<T> erase( Iterator<T> pos );                           //!< Remover um determinado elemento em uma posição.
    Iterator<T> upper_bound( const T & value );                    //!< Retornar o menor valor maior que pos
    void clear();                                               //!< Limpar todo o conjunto.

    // Funções de verificação ou depuração
    bool empty();                                               //!< Verificar se o vetor está vazio.
    int size();                                                 //!< Retornar o tamanho do vetor.
    void print();                                               //!< Imprimir os elementos para fins de depuração.
    void operator=( const set & value );                        //!< Operador de atribuição

private:
	T * m_area;
	int m_size;
	int m_capacity;
};
//! \note: não é necessário incluir o .cpp aqui
#include "set.inl"

#endif // SET_H
