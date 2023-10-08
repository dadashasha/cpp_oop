#include <gtest/gtest.h>

#include "flat_map.h"

// Тесты для конструктора и метода size()
TEST(FlatMapTest, ConstructorAndSize) {
FlatMap map;
EXPECT_EQ(map.size(), 0);

map["key1"] = "value1";
map["key2"] = "value2";

EXPECT_EQ(map.size(), 2);
}

// Тесты для конструктора копирования
TEST(FlatMapTest, CopyConstructor) {
    FlatMap map;
    EXPECT_EQ(map.size(), 0);

    map["key1"] = "value1";
    map["key2"] = "value2";

    FlatMap copy_map(map);

    EXPECT_EQ(map.size(), 2);
    EXPECT_EQ(map["key1"], "value1");
    EXPECT_EQ(map["key2"], "value2");

    EXPECT_EQ(copy_map.size(), 2);
    EXPECT_EQ(copy_map["key1"], "value1");
    EXPECT_EQ(copy_map["key2"], "value2");
}

// Тесты для оператора присваивания
TEST(FlatMapTest, OperationEquels) {
    FlatMap map;
    EXPECT_EQ(map.size(), 0);

    map["key1"] = "value1";
    map["key2"] = "value2";

    FlatMap copy_map;
    copy_map = map;

    EXPECT_EQ(map.size(), 2);
    EXPECT_EQ(map["key1"], "value1");
    EXPECT_EQ(map["key2"], "value2");

    EXPECT_EQ(copy_map.size(), 2);
    EXPECT_EQ(copy_map["key1"], "value1");
    EXPECT_EQ(copy_map["key2"], "value2");
}

// Тесты для метода operator[]
TEST(FlatMapTest, OperatorSquareBrackets) {
FlatMap map;
map["key1"] = "value1";
map["key2"] = "value2";

EXPECT_EQ(map["key1"], "value1");
EXPECT_EQ(map["key2"], "value2");

// Попытка доступа к несуществующему ключу должна создать новую запись
EXPECT_EQ(map.size(), 2);
map["key3"] = "value3";
EXPECT_EQ(map.size(), 3);
EXPECT_EQ(map["key3"], "value3");
}

// Тесты для метода contains()
TEST(FlatMapTest, Contains) {
FlatMap map;
map["key1"] = "value1";

EXPECT_TRUE(map.contains("key1"));
EXPECT_FALSE(map.contains("key2"));
}

// Тесты для метода erase()
TEST(FlatMapTest, Erase) {
FlatMap map;
map["key1"] = "value1";
map["key2"] = "value2";

EXPECT_EQ(map.erase("key1"), 1); // Должен удалиться 1 элемент
EXPECT_EQ(map.erase("key1"), 0); // Уже удаленный элемент
EXPECT_EQ(map.size(), 1);

EXPECT_EQ(map.erase("key2"), 1);
EXPECT_EQ(map.size(), 0);
EXPECT_FALSE(map.contains("key2"));
}

// Тесты для метода clear()
TEST(FlatMapTest, Clear) {
    FlatMap map;
    map["key1"] = "value1";

    map.clear();

    EXPECT_FALSE(map.contains("key1"));
    EXPECT_EQ(map.size(), 0);
}

// Тесты для метода для итераторов
TEST(FlatMapTest, Iterator) {
    FlatMap map;

    std::array<Node, 4> array_node {
        Node{"key1", "value1"},
        Node{"key2", "value2"},
        Node{"key3", "value3"},
        Node{"key4", "value4"}
    };

    for (int i = 0; i < 4; i++) {
        map[array_node[i].key] = array_node[i].value;
    }

    int index = 0;

    EXPECT_EQ(map.size(), 4);

//    for (auto it = map.begin(); it != map.end(); ++it)
    for (auto it : map) {
        EXPECT_EQ(it->key, array_node[index].key);
        EXPECT_EQ(it->value, array_node[index].value);
        index++;
    }

    EXPECT_EQ((*map.find("key2"))->key, "key2");
    EXPECT_EQ((*map.find("key2"))->value, "value2");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}