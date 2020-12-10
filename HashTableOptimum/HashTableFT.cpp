//
//  HashTableFT.cpp
//  HashTableOptimum
//
//  Created by Alexey Ischenko on 12/02/2019.
//  Copyright © 2019 Enthropy. All rights reserved.
//

#include "HashTableFT.hpp"

const size_t default_size = 8;
const size_t seed = 86969;

template<class T> int_fast64_t hasher(const T& line, int_fast64_t arr_size){
    int_fast64_t hash = line[0];
    for (int_fast64_t i = 1; i < line.size(); ++i){
        hash = (hash * (seed) + line[i]) % arr_size;
    }
    return hash % arr_size;
}

template<class T> HashTable<T>::HashTable(T el_null, T el_del, int_fast64_t (*hasher)(const T& element, int_fast64_t arr_size)){
    inserted_elements = 0;
    null_element = el_null;
    deleted_element = el_del;
    g_hasher = hasher;
    size = default_size;
    elements.resize(size);
    for (int_fast64_t i = 0; i < size; ++i){
        elements[i] = null_element;
    }
}

template<class T> HashTable<T>::~HashTable(){
    elements.clear();
}

template<class T> void HashTable<T>::check_ratio(){
    if (static_cast<double>(inserted_elements) / size >= 0.75){
        rehash();
    }
}

template<class T> void HashTable<T>::rehash(){
    std::vector<T> external = elements;
    size = size * 2;
    elements.clear();
    elements.resize(size);
    for (int_fast64_t i = 0; i < size; ++i){
        elements[i] = null_element;
    }
    inserted_elements = 0;
    for (int_fast64_t i = 0; i < external.size(); ++i){
        if (external[i] != null_element && external[i] != deleted_element){
            insert_element(external[i]);
        }
    }
}

template<class T> bool HashTable<T>::insert_element(T element){
    int_fast64_t i = 0;
    int_fast64_t element_hash = g_hasher(element, size);
    while (elements[(element_hash + i*i) % size] != null_element && elements[(element_hash + i*i) % size] != element){
        element_hash += i*i;
        ++i;
    }
    if (elements[(element_hash + i*i) % size] != null_element){
        return false;
    }
    elements[(element_hash + i*i) % size] = element;
    ++inserted_elements;
    check_ratio();
    return true;
}

template<class T> bool HashTable<T>::T_comparator(T &element1, T &element2){
    if (element1 == null_element || element2 == null_element){
        return false;
    }
    if (element1.size() != element2.size()){
        return false;
    }
    bool p = true;
    for (int_fast64_t i = 0; i < element2.size(); ++i){
        if (element1[i] != element2[i]){
            p = false;
            break;
        }
    }
    return p;
}

template<class T> bool HashTable<T>::check_element(T element){
    bool p = false;
    int_fast64_t i = 0;
    int_fast64_t element_hash = g_hasher(element, size);
    while (elements[(element_hash + i*i) % size] != null_element){
        if (T_comparator(elements[(element_hash + i*i) % size], element)){
            p = true;
            break;
        }
        element_hash += i*i;
        ++i;
    }
    return p;
}

template<class T> bool HashTable<T>::delete_element(T element){
    int_fast64_t i = 0;
    int_fast64_t element_hash = g_hasher(element, size);
    while (elements[(element_hash + i*i) % size] != null_element && elements[(element_hash + i*i) % size] != element){
        element_hash += i*i;
        ++i;
    }
    if (elements[(element_hash + i*i) % size] == null_element){
        return false;
    }
    elements[(element_hash + i*i) % size] = deleted_element;
    check_ratio();
    return true;
}


