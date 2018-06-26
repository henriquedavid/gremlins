#ifndef SET_H
#define SET_H

#include <utility>

// Classe baseada na classe set com apenas as funções e os operadores usados para resolver o problemas do projeto gremlins
// Limitações:

template < typename T >
class set
{
private:
    class iterator
    {
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_reference = const T&;

        iterator operator++();
        iterator operator--();
        const_reference operator*();
        const_reference operator->();
    private:
        pointer m_value;
    };
public:
    // --- ALIAS ---
    using const_iterator = const iterator;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_reference = const T&;

    // Construtores e destrutor

    set(int size_ = 1);						//!< Construtor.
    ~set();									//!< Destrutor.

    // Funções que modificam o container

    std::pair<iterator, bool> insert( const_reference value );	//!< Inserir um elemento de forma que fique ordenado.
    iterator begin() const;                                     //!< Retornar o início do vetor.
    iterator end() const;                                       //!< Retornar o fim do vetor.
    const_iterator cend();                                      //!< Retornar o fim do vetor cosntante.
    iterator erase( iterator * pos );                           //!< Remover um determinado elemento em uma posição.
    T * upper_bound( const T & value );                         //!< Retornar o menor valor maior que pos
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

#endif // SET_H
