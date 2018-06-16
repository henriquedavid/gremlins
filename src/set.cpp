#include "../include/set.h"

template < typename T >
set<T>::set( int size_ )
{

	this->m_data = new T[size_];
	this->m_size = 0;
	this->m_capacity = size_;

}

template < typename T >
void set<T>::insert( T value ){

}

template < typename T >
void set<T>::erase( T * value ){

}

template < typename T >
void set<T>::emplace(){

}

template < typename T >
T * set<T>::begin(){
	return m_data;
}

template < typename T >
T * set<T>::end(){
	return m_data+m_size;
}

template < typename T >
int set<T>::size(){
	return m_size;
}

template < typename T >
int set<T>::capacity(){
	return m_capacity;
}

T * find(){
	return ;
}