//
//  HashTableFT.hpp
//  HashTableOptimum
//
//  Created by Alexey Ischenko on 12/02/2019.
//  Copyright © 2019 Enthropy. All rights reserved.
//

#ifndef HashTableFT_hpp
#define HashTableFT_hpp

#include <stdio.h>
#include <vector>
#include <string>


template <class T>
class HashTable{
private:
    
    std::vector<T> elements;
    T null_element;
    T deleted_element;
    
    int_fast64_t inserted_elements;
    int_fast64_t size;
    int_fast64_t (*g_hasher)(const T& element, int_fast64_t arr_size);
    
    void check_ratio();
    bool T_comparator(T &element1, T &element2);
    void rehash();
    
public:
    
    HashTable(T el_null, T el_del, int_fast64_t (*hasher)(const T& element, int_fast64_t arr_size));
    ~HashTable();
    HashTable& operator=(HashTable const& table) = delete;
    HashTable(const HashTable &table) = delete;
    HashTable(HashTable &&table)  = delete;
    
    bool insert_element(T element);
    bool check_element(T element);
    bool delete_element(T element);
    
};

#endif /* HashTableFT_hpp */
