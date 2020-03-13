//Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
//Хранимые строки непустые и состоят из строчных латинских букв.
//Начальный размер таблицы должен быть равным 8-ми.
//Перехеширование выполняйте при добавлении элементов в случае,
//Когда коэффициент заполнения таблицы достигает 3/4.
//Хеш-функцию строки реализуйте с помощью вычисления значения многочлена методом Горнера.
//Структура данных должна поддерживать операции
//добавления строки в множество,
//удаления строки из множества
//и проверки принадлежности данной строки множеству.

//1_1. Для разрешения коллизий используйте квадратичное пробирование.
//i-ая проба
//g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

#include <stdio.h>
#include <vector>
#include <string>

const size_t default_size = 8;
const size_t seed = 86969;

using namespace std;

template<class T> int_fast64_t hasher(const T& line, int_fast64_t arr_size){
    int_fast64_t hash = line[0];
    for (int_fast64_t i = 1; i < line.size(); ++i){
        hash = (hash * (seed) + line[i]) % arr_size;
    }
    return hash % arr_size;
}

template <class T>
class HashTable{
private:
    
    vector<T> elements; //Угу
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
    vector<T> external = elements;
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

template<typename type> type custom_in(){
    type input;
    int_fast64_t a;
    a = getchar_unlocked();
    while (a != '\n'){
        input += a;
        a = getchar_unlocked();
    }
    return input;
}

template<typename type> void custom_out(type element){
    for (int_fast64_t i = 0; i < element.size(); ++i){
        putchar_unlocked(element[i]);
    }
}

int main(){
    HashTable<string> table("", "DELETED", &hasher<string>);
    
    string line = "";
    char command = ' ';
    char symbol = ' ';
    bool success = false;
    
    while(true){
        command = getchar_unlocked();
        if (command == EOF){
            break;
        }
        symbol = getchar_unlocked();
        line = custom_in<string>();
        
        success = false;
        
        switch (command) {
            case '+':{
                success = table.insert_element(line);
                break;
            }
            case '?':{
                success = table.check_element(line);
                break;
            }
            case '-':{
                if (!table.check_element(line)){
                    success = false;
                }
                else {
                    success = true;
                    table.delete_element(line);
                }
                break;
            }
            default:{
                break;
            }
        }
        
        if (success){
            custom_out<string>("OK\n");
        }
        else {
            custom_out<string>("FAIL\n");
        }
    }
    
    return 0;
}
