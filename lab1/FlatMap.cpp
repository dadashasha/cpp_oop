#include "FlatMap.h"


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

