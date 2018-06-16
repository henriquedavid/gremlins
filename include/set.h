#ifndef SET_H
#define SET_H

template < typename T >
class set
{
	public:
	    set(int v = 4);
    	
    	void insert( T value );
	    void erase( T * value);
    	
    	void emplace();

	    T * begin();
	    T * end();

	    int size();
	    int capacity();
    
	    T * find();

	private:
		T * m_data;
		int m_size;
		int m_capacity;
};

#include "../src/set.cpp"

#endif // SET_H