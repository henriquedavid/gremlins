#include "list.h"

using namespace ls;
/// Implementa a infraestrutura para suportar um ponteiro bidirecional.
/// Construtor a partir de um ponteiro. 


// ####################### CONST_ITERATOR #######################


template <typename T>
inline my_const_iterator<T>::my_const_iterator(Node<T> * node): current(node)
{
    /* empty */
}
/// Acessar o conteúdo o qual o ponteiro aponta.
template <typename T>
typename my_const_iterator<T>::const_reference & my_const_iterator<T>::operator*() const
{
    return this->current->data;
}

/// Comparar dois iteradores se são iguais.
template <typename T>
bool my_const_iterator<T>::operator==( const my_const_iterator<T> & rhs ) const
{
    return this->current == rhs.current;
}

/// Comprarar se dois iteradores são diferentes.

template <typename T>
bool my_const_iterator<T>::operator!=( const my_const_iterator<T> & rhs ) const
{
    return this->current != rhs.current;
}
/// Advances iterator to a specific position (walking throught the nodes).
template <typename T>
my_const_iterator<T> my_const_iterator<T>::operator+( int valor )
{
    
    auto i(0);
    while( i != valor){
        this->current = this->current->next;
        ++i;
    }

    return my_const_iterator<T>(this->current);
}

// ####################### ITERATOR #######################

template <typename T>
my_iterator<T>::my_iterator( Node<T> * node ): my_const_iterator<T>(node)
{
}

template <typename T>
typename my_iterator<T>::reference my_iterator<T>::operator*()
{
    return this->current->data;
}

/// Operador de pré-incremento.
template <typename T>
my_iterator<T> & my_iterator<T>::operator++( )
{
    this->current = this->current->next;
    return *this;
}

/// Operador de pós-incremento.
template <typename T>
my_iterator<T> my_iterator<T>::operator++( int )
{
    auto old_current(this->current);
    this->current = this->current->next;
    
    return my_iterator<T>(old_current);
}

template <typename T>
my_iterator<T> & my_iterator<T>::operator--()
{
    this->current = this->current->prev;
    return *this;
}

/// Operador de pós-decremento. 
template <typename T>
my_iterator<T> my_iterator<T>::operator--( int )
{
    auto old_current(this->current);
    this->current = this->current->prev;
    return list<T>::iterador(old_current);
}

template <typename T>
my_iterator<T> my_iterator<T>::operator+( int valor )
{
    auto i(0);
    while( i != valor){
        this->current = this->current->next;
        ++i;
    }

    return my_iterator<T>(this->current);
}

// ####################### LIST #######################


/// [I] SPECIAL MEMBERS

template <typename T>
list<T>::list(){
    m_size = 0;
    Node<T> * h = new Node<T>();
    
    h->next = nullptr;
    this->m_head = h;

}

template <typename T>
list<T>::~list()
{
    clear();
    delete m_head;
}

/// [III] CAPACITY

// returns true if the container contains no elements, and false otherwise.i*/
template < typename T >
bool list<T>::empty(){
    return m_size == 0;
}

/// Common operations to all list implementations
// return the number of elements in the container.
template < typename T >
typename list<T>::size_type list<T>::size() const{
    return m_size;
}

// remove (either logically or physically) all elements from the container.
template < typename T >
void list<T>::clear(){
    auto current(m_head->next);

    m_size = 0;

    while(current != nullptr){

        auto last (current->next);

        delete current;

        current = last;        

    }

    m_head->next = nullptr;


}

template <typename T>
void list<T>::push_back( const T & value ) 
{
    Node<T> * new_node = new Node<T>();
    new_node->data = value;
    new_node->next = nullptr;

    if( m_head->next == nullptr ){
    
        m_head->next = new_node;
    
    } else{

        auto current(m_head->next);
    
        while(current->next != nullptr)
            current = current->next;

        current->next = new_node;

    }
    
    // Incrementa o tamanho.
    m_size++;
}

template <typename T>
void list<T>::push_front( const T & value )
{
    Node<T> * new_node = new Node<T>();
    new_node->data = value;
    new_node->next = nullptr;

    // Se ainda não estiver nenhum elemento inserido.
    if( m_head->next == nullptr ){
        // Link do head e do tail com o elemento.
        m_head->next = new_node;
    }
    else{
        // Link do elemento com o head e o primeiro elemento da lista.
        new_node->next = m_head->next;
        m_head->next = new_node;
    }
    // Incrementa o tamanho.
    m_size++;

}

template < typename T >
typename ls::list<T>::iterator ls::list<T>::insert_after(const_iterator position, const value_type &val)
{
    Node<T> * new_node = new Node<T>(val, position.current->next);
    position.current->next = new_node;
    return ls::list<T>::iterator(new_node);
}

template < typename T >
typename ls::list<T>::iterator ls::list<T>::erase_after(const_iterator position)
{
    auto erased = position.current->next;
    if(erased->next != nullptr)
        position.current->next = erased->next;
    else
        position.current->next = nullptr;
    return position.current->next;
}

template < typename T >
const T & list<T>::back() const{
    auto current(m_head->next);

    while(current->next != nullptr )
        current = current->next;

    return current->data;
}

template < typename T >
T & list<T>::back(){
    auto current(m_head->next);

    while(current->next != nullptr )
        current = current->next;

    return current->data;
}

template < typename T >
const T & list<T>::front() const{
    return m_head->next->data;
}

template < typename T > 
T & list<T>::front(){
    return m_head->next->data;
}

template < typename T >
void list<T>::pop_front(){
    // obtem o m_head que é o primeiro elemento.
    auto curr(m_head->next);

    // obtem o segundo elemento da lista.
    auto next(curr->next);

    // Liga o head com o segundo valor.
    m_head->next = next;

    // deleta o antigo primeiro elemento.
    delete curr;

    m_size--;


}

template < typename T >
void list<T>::pop_back(){

    auto current(m_head->next);

    if(m_head->next != nullptr){

        while(current->next->next != nullptr){
            current = current->next;
        }

        delete current->next;

        current->next = nullptr;
        
        m_size--;
    }

}


template <typename T>
T& list<T>::at(list<T>::size_type & index)
{
    Node<T>* curr = this->m_head;

    if(curr == nullptr)
        throw std::out_of_range("Index provided is outside the array range.");

    for(auto i(0u); i < index; ++i)
    {
        if(curr == nullptr)
            throw std::out_of_range("Index provided is outside the array range.");
        curr = curr->next;
    }
    return *curr;
}
/*
/// Getting an iterator
*/

template <typename T>
typename list<T>::iterator list<T>::begin()
{
    return list<T>::iterator(m_head->next);

}

template < typename T >
typename list<T>::const_iterator list<T>::cbegin() const{
    return list<T>::const_iterator(m_head->next);
}

template < typename T >
typename ls::list<T>::iterator ls::list<T>::before_begin(){
    return ls::list<T>::iterator(m_head);
}

template < typename T >
typename ls::list<T>::const_iterator ls::list<T>::cbefore_begin() const{
    return list<T>::const_iterator(m_head);
}

template < typename T >
typename list<T>::iterator list<T>::end(){
    auto current(m_head);

    while(current->next != nullptr)
        current = current->next;

    return list<T>::iterator(current);
}


template < typename T >
typename list<T>::const_iterator list<T>::cend() const{
    auto current(m_head);

    while(current->next != nullptr)
        current = current->next;

    return list<T>::const_iterator(current);
}

template < typename T >
typename list<T>::const_iterator list<T>::find( const T & target ) const{

    auto prev( m_head );
    auto current( m_head->next );

    if( current != nullptr ){
        while( current != nullptr and current->data != target ){
            prev = current;
            current = current->next;
        }
    }

    return list<T>::const_iterator(prev);
}

template < typename T >
std::ostream & ls::operator<<(std::ostream & os_, const list<T>& v_ ){
    auto current( v_.m_head->next );
    std::cout << "[ ";
    
    // verify is the list it's empty.
    if ( current == nullptr ) std::cout << "empty";
    else
    {
        // Walks each element and print one by one.
        while( current != nullptr )
        {
            std::cout << current->data << " ";
            current = current->next;
        }
    }
    std::cout << "]\n";
    return os_;
}
