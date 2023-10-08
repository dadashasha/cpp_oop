#ifndef FLAT_MAP_FLAT_MAP_H
#define FLAT_MAP_FLAT_MAP_H

#include <iostream>
#include <algorithm>
#include <utility>

struct Node {
    Node() = default;
    Node(std::string key, std::string value) : key(std::move(key)), value(std::move(value)) {}
    std::string key;
    std::string value;
};

class FlatMap {
public:
    friend  class Iterator;

    class Iterator {
        FlatMap *master;
        std::size_t position;
    public:

        Iterator(FlatMap *a_master, std::size_t a_position) : master(a_master), position(a_position) {}

        Node* operator*() { return master->nodes_[position]; }

        Iterator operator++();

        bool operator==(Iterator &other);

        bool operator!=(Iterator &other);
    };

    /// стандартный конструктор
    FlatMap();

    // конструктор копирования
    FlatMap(const FlatMap& other_map);

    // конструктор перемещения
    FlatMap(FlatMap&& other_map) noexcept;

    // деструктор
    ~FlatMap();

    // оператор присваивания
    FlatMap& operator=(const FlatMap& other_map);

    // оператор перемещения
    FlatMap& operator=(FlatMap&& other_map) noexcept;

    // получить количество элементов в таблице
    [[nodiscard]] std::size_t size() const;

    // доступ / вставка элемента по ключу
    std::string& operator[](const std::string& key);

    // возвращает true, если запись с таким ключом присутствует в таблице
    bool contains(const std::string& key);

    // удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
    bool erase(const std::string& key);

    // очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
    void clear();

    // Получить итератор на первый элемент
    Iterator begin();

    // Получить итератор на элемент, следующий за последним
    Iterator end();

    // Получить итератор на элемент по данному ключу, или на end(), если такого ключа нет.
    // В отличие от operator[] не создает записи для этого ключа, если её ещё нет
    Iterator find(const std::string& key);

private:

    const std::size_t DEFAULT_CAPACITY = 8;
    const std::size_t DEFAULT_SIZE = 0;

    Node** nodes_;
    std::size_t size_;
    std::size_t capacity_;

    std::size_t find_index(const std::string& key);
    void resize();
    void clear_nodes();
};

#endif
