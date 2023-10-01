#ifndef FLAT_MAP_H
#define FLAT_MAP_H

#include <iostream>
#include <string>

class FlatMap {
   private:
    struct object {
        std::string key;
        std::string value;
    };
    object* array;
    std::size_t size;
    std::size_t capacity;

    std::size_t binSearch(const std::string& key);

    public:
     FlatMap();
     FlatMap(const FlatMap& other_map);
     FlatMap(FlatMap&& x) noexcept;
     ~FlatMap();
     FlatMap& operator=(const FlatMap& other_map);
     FlatMap& operator=(FlatMap&& x) noexcept;
     std::size_t size() const;
     std::string& operator[](const std::string& key);
     bool contains(const std::string& key);
     std::size_t erase(const std::string& key);
     void clear();
};

#endif  // FLAT_MAP_H
