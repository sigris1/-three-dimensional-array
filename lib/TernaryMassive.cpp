#include "TernaryMassive.h"
#include "cmath"
#include "iostream"

const uint8_t kBlockLength = 8;
const uint8_t kVariableNumbersBlock = 17;
const uint8_t kIncomingBitsCount = 24;
const uint8_t kFirstShiftForDegree = 7;
const uint8_t kSecondShiftForDegree = 15;
const uint8_t kThirdShiftForDegree = 23;
const uint8_t kFirstIncomingBitsCount = 8;
const uint8_t kSecondIncomingBitsCount = 16;
const uint8_t kThirdIncomingBitsCount = 24;
const uint8_t kMaxDegreeValue = 16;
const uint8_t kCheckingPosition = 16;
const uint8_t kPartialShift = 2;
const uint8_t kFirstNumberShift = 1;
const uint8_t kSecondNumberShift = 2;

uint32_t SetNewBinaryValues(bool array[], uint32_t first_significant, uint32_t second_significant, uint32_t third_significant, uint8_t start_value){
    uint8_t first_check = kFirstShiftForDegree;
    uint8_t second_check = kSecondShiftForDegree;
    uint8_t third_check = kThirdShiftForDegree;
    uint32_t real_number = 0;
    uint8_t degree = kMaxDegreeValue;
    while (first_significant > 0) {
        if (first_significant % 2 == 1) {
            array[first_check] = true;
        } else {
            array[first_check] = false;
        }
        first_significant /= 2;
        first_check--;
    }
    while (second_significant > 0) {
        if (second_significant % 2 == 1) {
            array[second_check] = true;
        } else {
            array[second_check] = false;
        }
        second_significant /= 2;
        second_check--;
    }
    while (third_significant > 0) {
        if (third_significant % 2 == 1) {
            array[third_check] = true;
        } else {
            array[third_check] = false;
        }
        third_significant /= 2;
        third_check--;
    }
    for (uint8_t i = start_value; i < start_value + kVariableNumbersBlock; ++i) {
        if (array[i]) {
            real_number += pow(2, degree);
        }
        degree--;
    }
    return real_number;
}

void CreateUnaryBinaryVersion(uint8_t value, bool binary_version[], uint8_t start_index){
    while (value > 0) {
        if (value % 2 == 1) {
            binary_version[start_index] = true;
        } else {
            binary_version[start_index] = false;
        }
        value /= 2;
        start_index--;
    }
}

void CreateBinaryVersion(uint8_t first, uint8_t second, uint8_t third, bool binary_version[]){
    uint8_t first_check = kFirstShiftForDegree;
    uint8_t second_check = kSecondShiftForDegree;
    uint8_t third_check = kThirdShiftForDegree;
    CreateUnaryBinaryVersion(first, binary_version, first_check);
    CreateUnaryBinaryVersion(second, binary_version, second_check);
    CreateUnaryBinaryVersion(third, binary_version, third_check);
}

void CreateRealArray(bool* old_version, bool* value_ib_binary, uint8_t start_value){
    for (uint8_t i = start_value; i < start_value + kVariableNumbersBlock; ++i){
        old_version[i] = value_ib_binary[i - start_value];
    }
}

TernaryArray TernaryArray::create_array(uint64_t length, uint64_t width, uint64_t height) {
    return TernaryArray(length, width, height);
}

TernaryArray::TernaryArray(uint64_t length, uint64_t width, uint64_t height)
        : length_(length)
        , width_(width)
        , height_(height)
{array_ = new uint8_t[(length + 1) * width * height * kVariableNumbersBlock / kBlockLength + 1]{0};}

TernaryArray::~TernaryArray() {
    delete[] array_;
}

TernaryArray TernaryArray::operator+(const TernaryArray& appended) {
    if (appended.length_ == this->length_ && appended.width_ == this->width_ && appended.height_ ==  this->height_) {
        TernaryArray current_array = TernaryArray(this->length_, this->width_, this->height_);
        for (uint64_t i = 0; i < this->length_; ++i){
            for (uint64_t j = 0; j < this->width_; ++j){
                for (uint64_t k = 0; k < this->height_; ++k){
                    current_array[i][j][k] = this->first_index.second_index.third_index.GetValue(i, j, k) + appended.first_index.second_index.third_index.GetValue(i, j, k);
                }
            }
        }
        return current_array;
    } else {
        std::cerr << "Non-calculated array";
        exit(EXIT_SUCCESS);
    }
}

TernaryArray TernaryArray::operator-(const TernaryArray& deducted) {
    if (deducted.length_ == this->length_ && deducted.width_ == this->width_ && deducted.height_ == this->height_) {
        TernaryArray current_array = TernaryArray(this->length_, this->width_, this->height_);
        for (uint64_t i = 0; i < this->length_; ++i){
            for (uint64_t j = 0; j < this->width_; ++j){
                for (uint64_t k = 0; k < this->height_; ++k){
                    current_array[i][j][k] = this->first_index.second_index.third_index.GetValue(i, j, k) - deducted.first_index.second_index.third_index.GetValue(i, j, k);
                }
            }
        }
        return current_array;
    } else {
        std::cerr << "Non-calculated array";
        exit(EXIT_SUCCESS);
    }
}

TernaryArray TernaryArray::operator*(const uint64_t multiplier) {
    TernaryArray current_array = TernaryArray(this->length_, this->width_, this->height_);
    for (uint64_t i = 0; i < this->length_; ++i){
        for (uint64_t j = 0; j < this->width_; ++j){
            for (uint64_t k = 0; k < this->height_; ++k){
                current_array[i][j][k] = this->first_index.second_index.third_index.GetValue(i, j, k) * multiplier;
            }
        }
    }
    return current_array;
}

uint32_t TernaryArray::FirstIndex::SecondIndex::ThirdIndex::GetValue(uint64_t now_length, uint64_t now_width, uint64_t now_height) const {uint64_t full_numbers = (now_length * this->father_->width_ * this->father_->height_ + now_width * this->father_->height_ + now_height) / kBlockLength;
    uint32_t partial_numbers = (now_length * this->father_->width_ * this->father_->height_ + now_width * this->father_->height_ + now_height) % kBlockLength;
    bool binary_number[kIncomingBitsCount];
    uint32_t real_number = 0;
    uint32_t first_significant = 0;
    uint32_t second_significant = 0;
    uint32_t third_significant = 0;
    for (uint8_t i = 0; i < kIncomingBitsCount; ++i) {
        binary_number[i] = false;
    }
    first_significant = this->father_->array_[full_numbers * kVariableNumbersBlock + kPartialShift * partial_numbers];
    second_significant = this->father_->array_[full_numbers * kVariableNumbersBlock + kFirstNumberShift + kPartialShift * partial_numbers];
    third_significant = this->father_->array_[full_numbers * kVariableNumbersBlock + kSecondNumberShift + kPartialShift * partial_numbers];
    real_number = SetNewBinaryValues(binary_number, first_significant, second_significant, third_significant, partial_numbers);
    return real_number;
}

void TernaryArray::FirstIndex::SecondIndex::ThirdIndex::ReplaceValue(uint64_t now_length, uint64_t now_width, uint64_t now_height, uint32_t new_value) {
    uint64_t full_numbers = (now_length * this->father_->width_ * this->father_->height_ + now_width * this->father_->height_ + now_height) / 8;
    uint32_t partial_numbers = (now_length * this->father_->width_ * this->father_->height_ + now_width * this->father_->height_ + now_height) % 8;
    bool new_three_baits_in_binary[kIncomingBitsCount];
    bool new_value_in_binary[kVariableNumbersBlock];
    uint8_t check_position = kCheckingPosition;
    for (uint8_t i = 0; i < kIncomingBitsCount; ++i) {
        new_three_baits_in_binary[i] = 0;
    }
    for (uint8_t i = 0; i < kVariableNumbersBlock; ++i) {
        new_value_in_binary[i] = 0;
    }
    while (new_value > 0) {
        if (new_value % 2 == 1) {
            new_value_in_binary[check_position] = true;
        } else {
            new_value_in_binary[check_position] = false;
        }
        new_value /= 2;
        check_position--;
    }
    uint32_t first_significant = this->father_->array_[full_numbers * kVariableNumbersBlock + kPartialShift * partial_numbers];
    uint32_t second_significant = this->father_->array_[full_numbers * kVariableNumbersBlock + kFirstNumberShift + kPartialShift * partial_numbers];
    uint32_t third_significant = this->father_->array_[full_numbers * kVariableNumbersBlock + kSecondNumberShift + kPartialShift * partial_numbers];
    CreateBinaryVersion(first_significant, second_significant, third_significant, new_three_baits_in_binary);
    CreateRealArray(new_three_baits_in_binary, new_value_in_binary, partial_numbers);
    this->father_->array_[full_numbers * kVariableNumbersBlock + kPartialShift * partial_numbers] = 0;
    for (uint8_t i = 0; i < kFirstIncomingBitsCount; ++i) {
        if (new_three_baits_in_binary[i]) {
            this->father_->array_[full_numbers * kVariableNumbersBlock + kPartialShift * partial_numbers] += pow(2, kFirstShiftForDegree - i);
        }
    }
    this->father_->array_[full_numbers * kVariableNumbersBlock + kFirstNumberShift + kPartialShift * partial_numbers] = 0;
    for (uint8_t i = kFirstIncomingBitsCount; i < kSecondIncomingBitsCount; ++i) {
        if (new_three_baits_in_binary[i]) {
            this->father_->array_[full_numbers * kVariableNumbersBlock + kFirstNumberShift + kPartialShift * partial_numbers] += pow(2, kSecondShiftForDegree - i);
        }
    }
    this->father_->array_[full_numbers * kVariableNumbersBlock + kSecondNumberShift + kPartialShift * partial_numbers] = 0;
    for (uint8_t i = kSecondIncomingBitsCount; i < kThirdIncomingBitsCount; ++i) {
        if (new_three_baits_in_binary[i]) {
            this->father_->array_[full_numbers * kVariableNumbersBlock + kSecondNumberShift + kPartialShift * partial_numbers] += pow(2, kThirdShiftForDegree - i);
        }
    }
}

TernaryArray::FirstIndex& TernaryArray::operator[](uint64_t position) {
    first_index.second_index.third_index.first_index = position;
    first_index.second_index.third_index.father_ = this;
    return first_index;
}

void TernaryArray::FirstIndex::SecondIndex::ThirdIndex::SetValueAtIndexes() {
    value_at_indexes = this->GetValue(this->first_index, this->second_index, this->third_index);
}

TernaryArray& TernaryArray::operator=(const TernaryArray& other) {
    if (&other == this){
        return *this;
    }
    delete[] array_;
    length_ = other.length_;
    width_ = other.width_;
    height_ = other.height_;
    array_ = new uint8_t[length_ * width_ * height_ * kVariableNumbersBlock / kBlockLength + 1];
    for (uint64_t i = 0; i < length_ * width_ * height_ * kVariableNumbersBlock / kBlockLength + 1; ++i){
        this->array_[i] = other.array_[i];
    }
    return *this;
}

TernaryArray::TernaryArray(const TernaryArray& now_array)
        :length_(now_array.length_)
        , width_(now_array.width_)
        , height_(now_array.height_)
{array_ = new uint8_t[now_array.length_ * now_array.height_ * now_array.height_ * kVariableNumbersBlock / kBlockLength + 1];
    for (uint64_t i = 0; i < now_array.length_ * now_array.height_ * now_array.height_ * kVariableNumbersBlock / kBlockLength + 1; ++i){
        array_[i] = now_array.array_[i];
    }
}

TernaryArray::FirstIndex::SecondIndex& TernaryArray::FirstIndex::operator[](uint64_t position) {
    second_index.third_index.second_index = position;
    father = father;
    return second_index;
}

TernaryArray::FirstIndex::SecondIndex::ThirdIndex& TernaryArray::FirstIndex::SecondIndex::operator[](uint64_t position) {
    third_index.third_index = position;
    third_index.SetValueAtIndexes();
    return third_index;
}

void TernaryArray::FirstIndex::SecondIndex::ThirdIndex::operator=(uint32_t value) {
    value_at_indexes = value;
    ReplaceValue(this->first_index, this->second_index, this->third_index, value);
}

bool TernaryArray::FirstIndex::SecondIndex::ThirdIndex::operator==(uint32_t value) {
    return (this->value_at_indexes == value);
}

std::ostream& operator<<(std::ostream& stream, const TernaryArray::FirstIndex::SecondIndex::ThirdIndex& value) {
    stream << value.GetValue(value.first_index, value.second_index, value.third_index) << " ";
    return stream;
}

std::istream& operator>>(std::istream& stream, TernaryArray::FirstIndex::SecondIndex::ThirdIndex& value) {
    uint32_t current_value;
    stream >> current_value;
    value = current_value;
    return stream;
}
