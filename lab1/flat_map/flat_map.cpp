#include "flat_map.h"

FlatMap::FlatMap() : nodes_(new Node*[DEFAULT_CAPACITY]), size_(DEFAULT_SIZE), capacity_(DEFAULT_CAPACITY) {}

FlatMap::~FlatMap() {
    clear_nodes();
}

FlatMap::FlatMap(const FlatMap& other_map)
: nodes_(new Node*[other_map.capacity_]), size_(other_map.size_), capacity_(other_map.capacity_) {
    for (auto i = 0; i < other_map.size_; i++) {
        nodes_[i] = new Node(other_map.nodes_[i]->key, other_map.nodes_[i]->value);
    }
}

FlatMap::FlatMap(FlatMap &&other_map) noexcept : nodes_(new Node*[DEFAULT_CAPACITY]), size_(other_map.size_), capacity_(other_map.capacity_) {
    std::swap(nodes_, other_map.nodes_);
    other_map.size_ = DEFAULT_SIZE;
    other_map.capacity_ = DEFAULT_CAPACITY;
}

FlatMap& FlatMap::operator=(const FlatMap& other_map) {
    if (this == &other_map) {
        return *this;
    }

    clear_nodes();
    nodes_ = new Node*[other_map.capacity_];
    size_ = other_map.size_;
    capacity_ = other_map.capacity_;

    for (auto i = 0; i < other_map.size_; i++) {
        nodes_[i] = new Node(other_map.nodes_[i]->key, other_map.nodes_[i]->value);
    }

    return *this;
}

FlatMap &FlatMap::operator=(FlatMap &&x) noexcept {
    nodes_ = x.nodes_;
    size_ = x.size_;
    capacity_ = x.capacity_;
    x.nodes_ = new Node*[DEFAULT_CAPACITY];
    size_ = DEFAULT_SIZE;
    capacity_ = DEFAULT_CAPACITY;

    return *this;
}

std::size_t FlatMap::size() const {
    return size_;
}

std::string& FlatMap::operator[](const std::string& key) {
//  если в последнем элементе массива не nullptr, мы расширяем массив в 2 раза
    if (size_ >= capacity_ - 1)
        resize();

    auto index = find_index(key);

//  если index указывает на несуществующий элемент в конце массива, мы создаем на этом месте новую Node
    if (index >= size_) {
        nodes_[index] = new Node(key, "");
        size_++;
        return nodes_[index]->value;
    }

//  возвращаем найденный элемент
    if (nodes_[index]->key == key)
        return nodes_[index]->value;

//  перемещаем nullptr из конца массива в нужную ячейку с конца
    for (std::size_t i = size_; i > index; i--) {
        std::swap(nodes_[i], nodes_[i - 1]);
    }

    nodes_[index] = new Node(key, "");
    size_++;

    return nodes_[index]->value;
}

bool FlatMap::contains(const std::string& key) {
    auto index = find_index(key);
    return index < size_ && nodes_[index]->key == key;
}

bool FlatMap::erase(const std::string& key) {
    auto index = find_index(key);
    if (index >= size_ || nodes_[index]->key != key)
        return false;

//  сдвигаем удаляемый элемент в конец массива
    for (; index < size_ - 1; index++) {
        std::swap(nodes_[index], nodes_[index + 1]);
    }

    delete nodes_[index];
    nodes_[index] = nullptr;
    size_--;

    return true;
}

void FlatMap::clear() {
    clear_nodes();
    nodes_ = new Node*[DEFAULT_CAPACITY];
    size_ = DEFAULT_SIZE;
    capacity_ = DEFAULT_CAPACITY;
}

FlatMap::Iterator FlatMap::begin() {
    return {this, 0};
}

FlatMap::Iterator FlatMap::end() {
    return {this, size_};
}

FlatMap::Iterator FlatMap::find(const std::string &key) {
    auto index = find_index(key);

    if (index >= size_ || nodes_[index]->key == key)
        return {this, index};

    return {this, size_};
}

FlatMap::Iterator FlatMap::Iterator::operator++() {
    if (master->size_ == position) {
        return {master, position};
    }

    return {master, ++position};
}

bool FlatMap::Iterator::operator==(FlatMap::Iterator &other) {
    return master == other.master && position == other.position;
}

bool FlatMap::Iterator::operator!=(FlatMap::Iterator &other) {
    return !(*this == other);
}

void FlatMap::clear_nodes() {
    for (auto i = 0; i < size_; i++) {
        delete nodes_[i];
    }

    delete[] nodes_;
}

std::size_t FlatMap::find_index(const std::string& key) {
    if (size_ == 0)
        return 0;

    std::size_t left = 0;
    std::size_t right = size_ - 1;

    while (left <= right) {
        std::size_t mid = left + (right - left) / 2;
        int comparison = key.compare(nodes_[mid]->key);

        if (comparison == 0)
            return mid;

        if (comparison < 0) {
            if (right < mid - 1) {
                return size_;
            }
            right = mid - 1;
        }
        else
            left = mid + 1;
    }

    return left;
}

void FlatMap::resize() {
    capacity_ *= 2;
    auto new_nodes = new Node*[capacity_];

    for (auto i = 0; i < size_; i++) {
        new_nodes[i] = new Node(nodes_[i]->key, nodes_[i]->value);
    }

    delete[] nodes_;
    nodes_ = new_nodes;
}
