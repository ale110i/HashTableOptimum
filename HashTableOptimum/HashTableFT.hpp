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
    
    std::vector<T> elements; //Угу
    T null_element;
    T deleted_element;
    
    int_fast64_t inserted_elements; //Угу
    int_fast64_t size; //Угу
    int_fast64_t (*g_hasher)(const T& element, int_fast64_t arr_size); //Угу
    
    void check_ratio(); //Угу
    bool T_comparator(T &element1, T &element2); //Угу
    void rehash(); //Угу
    
public:
    
    HashTable(T el_null, T el_del, int_fast64_t (*hasher)(const T& element, int_fast64_t arr_size)); //Угу
    ~HashTable(); //Угу
    HashTable& operator=(HashTable const& table) = delete; //Угу
    HashTable(const HashTable &table) = delete; //Угу
    HashTable(HashTable &&table)  = delete; //Угу
    
    bool insert_element(T element); //Угу
    bool check_element(T element); //Угу
    bool delete_element(T element); //Угу
    
};

#endif /* HashTableFT_hpp */
