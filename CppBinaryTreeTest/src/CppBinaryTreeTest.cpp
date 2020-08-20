/*
 * CppBinaryTreeTest.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: algorithm
 */
#include <include/CppBinaryTree.hpp>
#include <gtest/gtest.h>
#include <time.h>

using namespace ::testing;

/**
 * @brief Typedef for test type. The same test can be used to all similar containers.
 */
template<typename T>
using DContainer = CBinaryTree<T>;

class CContainerTest : public Test
{
public:

};


/**
 * Test for empty container.
 */
TEST_F(CContainerTest, empty)
{
    DContainer<int> container;
    // check size of empty container
    const unsigned int sizeEmptyActual = container.size();
    ASSERT_EQ(sizeEmptyActual, 0u);
    // check empty method
    const bool emptyActual = container.empty();
    ASSERT_TRUE(emptyActual);
    // check if empty container contains item
    const bool containsActual = container.contains(1);
    ASSERT_FALSE(containsActual);
    // check if empty container contains max value
    const unsigned int maxEmptyActual = container.getMaxValueTree();
    ASSERT_EQ(maxEmptyActual, NULL);
    // check if empty container contains min value
    const unsigned int minEmptyActual = container.getMinValueTree();
    ASSERT_EQ(minEmptyActual, NULL);
}


/**
 * Test insert one element.
 */
TEST_F(CContainerTest, oneElement_insert)
{
    DContainer<int> container;

    // insert new item
    const int value = 50;
    container.insert(value);

    //check contains item
    const bool valueContainsExpected = container.contains(value);
    ASSERT_TRUE(valueContainsExpected);
    const bool valueContainsExpectedWrong = container.contains(value+1);
    ASSERT_FALSE(valueContainsExpectedWrong);

    // check max value
    const int maxValueExpected = container.getMaxValueTree();
    ASSERT_EQ(maxValueExpected, value);

    //check min value
    const int minValueExpected = container.getMinValueTree();
    ASSERT_EQ(minValueExpected, value);

    //check empty
    const bool valueEmpty = container.empty();
    ASSERT_FALSE(valueEmpty);

    //check container size
    const unsigned int valueSizeExpected = container.size();
    ASSERT_EQ(valueSizeExpected, 1);

}


/**
 * Test for delete one element.
 */
TEST_F(CContainerTest, oneElement_delete)
{
    DContainer<int> container;

    // insert new item
    const int value = 50;
    container.insert(value);

    //check delete item
    const bool valueDeleteExpectedWrong = container.deleteVal(value+1);
    ASSERT_FALSE(valueDeleteExpectedWrong);

    const bool valueDeleteExpecte = container.deleteVal(value);
    ASSERT_TRUE(valueDeleteExpecte);

    //check item in container which was delete
    const bool valueContainsExpected = container.contains(value);
    ASSERT_FALSE(valueContainsExpected);

    //check empty
    const bool valueEmpty = container.empty();
    ASSERT_TRUE(valueEmpty);

    //check container size
    const unsigned int valueSizeExpected = container.size();
    ASSERT_EQ(valueSizeExpected, 0);

    //check delete item in empty container
    const bool valueDeleteEmptyExpecte = container.deleteVal(value);
    ASSERT_FALSE(valueDeleteEmptyExpecte);
}


/**
 * Test for check one max Value.
 */
TEST_F(CContainerTest, check_oneMax_item)
{
    DContainer<int> container;
    int arr[20]{32,16,67,12,98,
                85,31,83,1,20,
                2,13,27,37,47,
                57,50,66,77,88};
    int maxVal = 98;
    const unsigned int mSize = sizeof(arr)/sizeof(arr[0]);

    // loop for adding items
    for (unsigned int j = 0; j < mSize; ++j)
    {
        // insert new item
        container.insert(arr[j]);
    }

    //check max value in container
    const int maxValueExpected = container.getMaxValueTree();
    ASSERT_EQ(maxValueExpected, maxVal);
}


/**
 * Test for check one min Value.
 */
TEST_F(CContainerTest, check_oneMin_item)
{
    DContainer<int> container;
        int arr[20]{32,16,67,12,98,
                    85,31,83,1,20,
                    2,13,27,37,47,
                    57,50,66,77,88};
        int minVal = 1;
        unsigned int mSize = sizeof(arr)/sizeof(arr[0]);

        // loop for adding items
        for (unsigned int j = 0; j < mSize; ++j)
        {
            // insert new item
            container.insert(arr[j]);
        }

        //check max value in container
        const int minValueExpected = container.getMinValueTree();
        ASSERT_EQ(minValueExpected, minVal);
}


/**
 * Test for check insert method
 */
TEST_F(CContainerTest, insert_item)
{
    DContainer<int> container;
        int arr[20]{32,16,67,12,98,
                    85,31,83,1,20,
                    2,13,27,37,47,
                    57,50,66,77,88};
        unsigned int mSize = sizeof(arr)/sizeof(arr[0]);

        // loop for adding items
        for (unsigned int j = 0; j < mSize; ++j)
        {
            // insert new item
            container.insert(arr[j]);

            // check value of inserted item
            const bool insertedValueActual = container.contains(arr[j]);
            ASSERT_TRUE(insertedValueActual);

            //check size of container
            const unsigned int realSize = j+1;
            const unsigned int sizeValueExpect = container.size();
            ASSERT_EQ(sizeValueExpect, realSize);
        }
}


/**
 * Test for check delete method
 */
TEST_F(CContainerTest, delete_item)
{
    DContainer<int> container;
        int arr[20]{32,16,67,12,98,
                    85,31,83,1,20,
                    2,13,27,37,47,
                    57,50,66,77,88};

        unsigned int mSize = sizeof(arr)/sizeof(arr[0]);

        // loop for adding items
        for (unsigned int j = 0; j < mSize; ++j)
        {
            // insert new items
            container.insert(arr[j]);
        }

        // loop for delete items
        unsigned int realSize = 19;
        for (unsigned int j = 0; j < mSize; ++j)
        {
            // delete item
            const bool deleteValueActual = container.deleteVal(arr[j]);
            ASSERT_TRUE(deleteValueActual);

            // check value of contains item
            const bool containsValueActual = container.contains(arr[j]);
            ASSERT_FALSE(containsValueActual);

            //check size of container
            const unsigned int sizeValueExpect = container.size();
            ASSERT_EQ(sizeValueExpect, realSize);
            --realSize;
        }
}


/**
 * Test for insert method
 */
TEST_F(CContainerTest, similar_tree)
{

    DContainer<int> containerA1;
    DContainer<int> containerA2;
    DContainer<int> containerB1;

    int arr[20]{50,20,30,40,51,
                5,15,25,35,45,
                70,65,75,85,95,
                2,67,77,87,97};

    int arr1[20]{51,21,31,41,52,
                6,16,26,36,46,
                71,66,76,86,96,
                3,68,78,88,99};

    for (unsigned int j = 0; j < 20; ++j)
    {
        containerA1.insert(arr[j]);
        containerA2.insert(arr[j]);
        containerB1.insert(arr1[j]);
    }

    ASSERT_TRUE(containerA1 == containerA2);
    ASSERT_TRUE(containerA1 != containerB1);
    ASSERT_FALSE(containerA1 == containerB1);

    DContainer<int> containerC1(containerA1);

    ASSERT_TRUE(containerA1 == containerC1);


    DContainer<int> containerD1;
    containerD1 = containerA1;
    ASSERT_TRUE(containerA1 == containerD1);

}


/**
 * @brief Base class for GoogleTest parametrized tests.
 */
class CContainerParamTest : public TestWithParam<unsigned int>
{
};


/**
 * @brief Function to display name of tests.
 * @param aInfo Param info.
 * @return Label
 */
std::string customMessage(testing::TestParamInfo<unsigned int> aInfo)
{
    std::stringstream ss;
    ss<<"Size_"<<aInfo.param;
    return ss.str();
};

const unsigned int minSize = 1u;
const unsigned int maxSize = 20u;
const unsigned int stepSize = 1u;

INSTANTIATE_TEST_CASE_P(ParamTest_Values,
                        CContainerParamTest,
                        Range(minSize, maxSize, stepSize),
                        customMessage);



