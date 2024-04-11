#include "gtest/gtest.h"
#include "../lib/TernaryMassive.h"


TEST(TernaryTests, CreatingTest) {
    TernaryArray array = TernaryArray::create_array(2,3,4);
}

TEST(TernaryTests, SetValue_1){
    TernaryArray array(2, 3, 4);
    array[1][2][0] = 3422;
    ASSERT_EQ(array[1][2][0].GetValue(1, 2, 0), 3422);
}

TEST(TernaryTests, SetValue_2){
    TernaryArray array = TernaryArray::create_array(54,23,75);
    array[23][11][69] = 239;
    ASSERT_EQ(array[23][11][69].GetValue(23, 11, 69), 239);
}

TEST(TernaryTests, SetValue_3){
    TernaryArray array = TernaryArray::create_array(54,23,75);
    array[23][11][69] = 239;
    ASSERT_EQ(array[23][11][69].value_at_indexes, 239);
}

TEST(TernaryTests, SetValue_4){
    TernaryArray array = TernaryArray::create_array(54,23,75);
    array[23][11][69] = 239;
    TernaryArray cloned_array = array;
    ASSERT_EQ(cloned_array[23][11][69].value_at_indexes, 239);
}

TEST(TernaryTests,AddingWithValues_1){
    TernaryArray first_array(2, 3, 4);
    first_array[1][1][1] = 3422;
    TernaryArray second_array(2, 3, 4);
    second_array[1][1][1] = 3422;
    TernaryArray third_array = first_array + second_array;
    ASSERT_EQ(third_array[1][1][1].GetValue(1, 1, 1), 6844);
}

TEST(TernaryTests,AddingWithValues_2){
    TernaryArray first_array(6, 9, 4);
    first_array[1][1][1] = 239;
    TernaryArray second_array(6, 9, 4);
    second_array[1][1][1] = 234;
    TernaryArray third_array = first_array + second_array;
    ASSERT_EQ(third_array[1][1][1].GetValue(1, 1, 1), 239 + 234);
}

TEST(TernaryTests,AddingWithValues_3){
    TernaryArray first_array(10, 10, 10);
    first_array[1][2][3] = 239;
    first_array[6][6][6] = 1745;
    TernaryArray second_array(10, 10, 10);
    second_array[1][2][3] = 234;
    second_array[6][6][6] = 1846;
    TernaryArray third_array = first_array + second_array;
    ASSERT_EQ(third_array[6][6][6].GetValue(6, 6, 6), 1745 + 1846);
}


TEST(TernaryTests, DeductingWithValues_1){
    TernaryArray first_array(2, 3, 4);
    first_array[1][2][3] = 8;
    TernaryArray second_array(2, 3, 4);
    second_array[1][2][3] = 5;
    TernaryArray third_array = first_array - second_array;
    ASSERT_EQ(third_array[1][2][3].GetValue(1, 2, 3), 3);
}

TEST(TernaryTests, DeductingWithValues_2){
    TernaryArray first_array(4, 3, 8);
    first_array[1][2][2] = 459;
    TernaryArray second_array(4, 3, 8);
    second_array[1][2][2] = 59;
    TernaryArray third_array = first_array - second_array;
    ASSERT_EQ(third_array[1][2][2].GetValue(1, 2, 2), 400);
}

TEST(TernaryTests, DeductingWithValues_3){
    TernaryArray first_array(8, 1, 9);
    first_array[1][0][3] = 8643;
    TernaryArray second_array(8, 1, 9);
    second_array[1][0][3] = 0;
    TernaryArray third_array = first_array - second_array;
    ASSERT_EQ(third_array[1][0][3].GetValue(1, 0, 3), 8643);
}

TEST(TernaryTests, MultiplicatingWithValue_1){
    TernaryArray array(2, 3, 4);
    array[1][2][3] = 5;
    TernaryArray second_array = array * 10;
    ASSERT_EQ(second_array[1][2][3].GetValue(1, 2, 3), 50);
}

TEST(TernaryTests, MultiplicatingWithValue_2){
    TernaryArray array(5, 6, 9);
    array[4][2][8] = 1;
    TernaryArray second_array = array * 239;
    ASSERT_EQ(second_array[4][2][8].GetValue(4, 2, 8), 239);
}

TEST(TernaryTests, MultiplicatingWithValue_3){
    TernaryArray array(2, 3, 4);
    array[1][2][3] = 5;
    TernaryArray second_array = array * 10;
    ASSERT_EQ(second_array[1][2][3].GetValue(1, 2, 3), 50);
}

TEST(TernaryTests, CopyTest){
    TernaryArray first_array(7, 8, 3);
    first_array[1][2][0] = 8;
    TernaryArray second_array = first_array;
    first_array[1][2][0] = 6;
    ASSERT_EQ(second_array[1][2][0].GetValue(1, 2, 0), 8);
}

TEST(TernaryTests, ReadingTest){
    std::stringstream string;
    TernaryArray array(8, 5, 2);
    array[5][2][1] = 42;
    string << array[5][2][1];
    uint32_t value;
    string >> value;
    ASSERT_EQ(value, array[5][2][1].GetValue(5, 2, 1));
}

TEST(TernaryTests, WritingTest){
    std::stringstream string;
    TernaryArray array(12, 6, 10);
    string << 143;
    string >> array[3][2][8];
    ASSERT_EQ(143, array[3][2][8].GetValue(3, 2, 8));
}