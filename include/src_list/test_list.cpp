#include <iostream>
#include <memory>
#include <cassert>
#include "../list/list.h"
#include <list>

using namespace std;

template < typename T >
bool cmp(ls::list<T> & va, std::list<T> & vb){
    auto f(va.cbegin());
    auto size = va.size();
    if(size != vb.size())

        return false;


    for( auto & a : vb ){
        if(*(f) != a)
            return false;

        f++;
    }
    return true;
}

int main(){


    /// =====================================    TESTS   ================================================  
    
    ls::list<int> l1;

    l1.push_front(4);
    l1.push_back(6);
    l1.push_front(2);
    l1.push_back(8);

    std::cout << l1 << std::endl;

    std::cout << "Há " << l1.size() << " elementos.\n";
    if(l1.empty())
        std::cout << "Está vazio!\n";
    else
        std::cout << "Não está vazio.\n";

    l1.clear();    

    std::cout << "Há " << l1.size() << " elementos.\n";
    if(l1.empty())
        std::cout << "Está vazio!\n";
    else
        std::cout << "Não está vazio.\n";

    l1.push_front(4);
    l1.push_back(6);
    l1.push_front(2);
    l1.push_back(8);

    std::cout << l1 << std::endl;

    std::cout << "Há " << l1.size() << " elementos.\n";
    if(l1.empty())
        std::cout << "Está vazio!\n";
    else
        std::cout << "Não está vazio.\n";

    std::cout << l1.front() << std::endl;
    std::cout << l1.back() << std::endl;

    l1.pop_front();
    l1.pop_back();

    std::cout << l1 << std::endl;
    
    return 0;
}
