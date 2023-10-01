#include "FlatMap.h"

std::size_t FlatMap::binarySearch(const std::string& key) {
    if (size == 0)
        return 0;
    object* lower_bound =
        std::lower_bound(array, array + size, key, [](const object& , const std::string& k) { return kv.key < k; });
    return lower_bound - array;
}

//Расширение массива
void FlatMap::extension(std::size_t newСapacity) {
    if (newСapacity <= capacity) {
        return ;
    }

    FlatMap temp;
    temp.array = new object[newСapacity];
    temp.capacity = newСapacity;
    temp.size = size;
    
    std::copy(array, array + size, temp.array);
    std::swap(array, temp.array);
    std::swap(size, temp.size);
    std::swap(capacity, temp.capacity);
}

//Стандартный коснтруктор
FlatMap::FlatMap() : array(nullptr), size(0), capacity_(0) {}

//Деструктор
FlatMap::~FlatMap() {
    delete[] array;
    size = 0;
    capacity = 0;
}

//Очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
void FlatMap::clear() {
    delete[] array;
    array = nullptr;
    size = 0;
    capacity = 0;
}

//Получить количество элементов в таблице
std::size_t FlatMap::size() const {
    return size;
}

//Конструктор копирования
FlatMap::FlatMap(const FlatMap& other_map) : array(nullptr), size(0), capacity(0) {
    FlatMap temp;
    temp.extension(other_map.capacity);
    temp.size = other_map.size;
    
    std::copy(other_map.data, other_map.data + other_map.size, temp.data);
    std::swap(data, temp.data);
    std::swap(size, temp.size);
    std::swap(capacity, temp.capacity);
}

