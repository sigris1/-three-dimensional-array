#pragma once

#include "cstdint"
#include "sstream"

class TernaryArray {
public:
    class FirstIndex{
    public:
        class SecondIndex {
        public:
            class ThirdIndex {
                friend TernaryArray;
            public:
                bool operator==(uint32_t value);
                uint64_t second_index = -1;
                uint64_t first_index = -1;
                uint64_t third_index = -1;
                uint32_t value_at_indexes = -1;
                void SetValueAtIndexes();
                uint32_t GetValue(uint64_t now_length, uint64_t now_width, uint64_t now_height) const;
                void operator=(uint32_t value);
            private:
                TernaryArray* father_ = nullptr;
                void ReplaceValue(uint64_t now_length, uint64_t now_width, uint64_t now_height, uint32_t new_value);
            };
            ThirdIndex third_index;
            TernaryArray* father = nullptr;
            ThirdIndex& operator[](uint64_t position);
        };
        SecondIndex second_index;
        TernaryArray* father = nullptr;
        SecondIndex& operator[](uint64_t position);
    };
    FirstIndex first_index;
    static TernaryArray create_array(uint64_t length, uint64_t width, uint64_t height);
    TernaryArray(uint64_t length, uint64_t width, uint64_t height);
    TernaryArray(const TernaryArray& array);
    ~TernaryArray();
    TernaryArray operator+(const TernaryArray &appended);
    TernaryArray operator-(const TernaryArray &deducted);
    FirstIndex& operator[](uint64_t position);
    TernaryArray operator*(uint64_t multiplier);
    TernaryArray& operator=(const TernaryArray& array);
private:
    uint64_t length_ = 0;
    uint64_t width_ = 0;
    uint64_t height_ = 0;
    uint8_t* array_;
};

std::ostream& operator<<(std::ostream& stream, const TernaryArray::FirstIndex::SecondIndex::ThirdIndex& value);

std::istream& operator>>(std::istream& stream, TernaryArray::FirstIndex::SecondIndex::ThirdIndex& value);
