#ifndef INCLUDE_CPPBINARYTREE_HPP
#define INCLUDE_CPPBINARYTREE_HPP

/*----------------------------------------------------------------------
                                Include
*----------------------------------------------------------------------*/
#include <iostream>
#include <memory>

/**
 * @brief Binary Tree. Holds pointers to left and right Item of Binary tree and T data.
 * Therefore some operations have constant complexity.
 * @tparam T Type of items.
 */
template<typename T>
class CBinaryTree
{
    /**
     * @brief Tree item. Each tree value is hold in this class.
     * It wraps value by adding pointer to left and right element.
     * @tparam TItem Type of items stored in a tree.
     */
    template<typename TItem>
    class CBinaryTreeItem
    {
    public:
        
        /*----------------------------------------------------------------------
                         Constructors & Destructors
        *----------------------------------------------------------------------*/
        CBinaryTreeItem(const TItem& aValue)
            : mLeft(nullptr)
            , mRight(nullptr)
            , mValue(aValue)
        {}

        CBinaryTreeItem(CBinaryTreeItem& aObj)
            : mLeft(std::make_shared<CBinaryTreeItem<T>>(aObj.mLeft))
            , mRight(std::make_shared<CBinaryTreeItem<T>>(aObj.mRight))
            , mValue(aObj.mValue)
        {}

        /*----------------------------------------------------------------------
                                Overload operators
        *----------------------------------------------------------------------*/
        /**
         * @brief Operator ->
         */
        T* operator->()
        {
            return &(this);
        }

        /**
         * @brief Pointer to right Item.
         */
        std::shared_ptr<CBinaryTreeItem<T>> mRight;

        /**
         * @brief Pointer to left item.
         */
        std::shared_ptr<CBinaryTreeItem<T>> mLeft;

        /**
         * @brief Value.
         */
        TItem mValue;
    };
    // /////////////////////////////////////////////////////////////////////
    // /////////////////////////////////////////////////////////////////////
    // /////////////////////////////////////////////////////////////////////
public:

    /*----------------------------------------------------------------------
                           Constructors & Destructors
    *----------------------------------------------------------------------*/
    CBinaryTree()
        : mRoot(nullptr)
        , n(nullptr)
        , mSize(NULL)
    {}

    CBinaryTree(const CBinaryTree<T>& aObj)
    {
        if (!aObj.empty())
        {
            mRoot = copyBinaryTree(aObj.mRoot);
        }
        else
        {
            iniBinaryTree();
        }
    }

    ~CBinaryTree()
    {
        mRoot.reset();
        n.reset();
    }

    /*----------------------------------------------------------------------
                                Overload operators
    *----------------------------------------------------------------------*/

    /**
     * @brief Assignment operator
     */
    CBinaryTree<T>& operator=(const CBinaryTree<T>& aObj)
    {
        if (!empty())
        {
            mRoot.reset();
            iniBinaryTree();
        }

        if (!aObj.empty())
        {
            mRoot = copyBinaryTree(aObj.mRoot);
        }

        return *this;
    }

    /**
     * @brief Compares tree
     */
    bool operator==(const CBinaryTree<T>& aObj)
    {
        if (mRoot == aObj.mRoot)
        {
            return true;
        }

        if (mSize != aObj.mSize)
        {
            return false;
        }
        return (identicalBinaryTrees(mRoot, aObj.mRoot));
    }

    /**
     * @brief Compares tree
     */
    bool operator!=(const CBinaryTree<T>& aObj)
    {
        return !(*this == aObj);
    }

    /*----------------------------------------------------------------------
                                   Methods
    *----------------------------------------------------------------------*/

    /**
     * @brief Indicates if the tree empty.
     * Complexity: O(1)
     * @return true if list is empty, otherwise false.
     */
    bool empty() const
    {
        return(mSize == 0);
    }

    /**
     * @brief Insert value in tree
     * @param aValue is value which you want to insert
     * @return NULL
     */
    void insert(const T& aValue)
    {
        if (empty())
        {
            n = std::make_shared<CBinaryTreeItem<T>>(aValue);
            mRoot = std::make_shared<CBinaryTreeItem<T>>(n);
            mSize++;
        }
        else
        {
            writeValueInTree(mRoot, aValue);
        }
    }

    /**
     * @brief Delete Item from tree
     * @param aValue is value which you want to delete from tree
     * @return true if value delete.True otherway.
     */

    bool deleteVal(const T& aValue)
    {
        if ((!empty()) && (contains(aValue)))
        {
            if (mSize == 1)
            {
                mRoot.reset();
            }
            else
            {
                deleteItemBinaryTree(mRoot, aValue);
            }
            mSize--;

            if (!contains(aValue))
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Checks the tree contains object.
     * Complexity: O(n) - because it has to check all items. In the worst case entire tree will be checked.
     * The worst case takes place if there isn't the value in the tree or it is on the last position.
     * @param aValue Value to check.
     * @return true if list contains value, otherwise false.
     */
    bool contains(const T& aValue) const
    {
        bool res = false;
        if (!empty())
        {
            res = (findItemBinaryTree(mRoot, aValue));
        }
        return res;
    }

    /**
     * @brief Show max value which is in tree
     * @param NULL
     * @return Max value of tree
     */
    T getMaxValueTree()
    {
        T res = NULL;
        if (!empty())
        {
            res = getMaxValue(mRoot);
        }
        return res;
    }

    /**
     * @brief Show min value which is in tree
     * @param NULL
     * @return Min value in tree
     */
    T getMinValueTree()
    {
        T res = NULL;
        if (!empty())
        {
            res = getMinValue(mRoot);
        }
        return res;
    }

    /**
     * @brief Print all value from tree
     * @param NULL
     * @return NULL
     */
    void printBinaryTree()
    {
        if (!empty())
        {
            printTree(mRoot);
        }
        else
        {
            std::cout << "Tree is empty" << std::endl;
        }
    }

    /**
     * @brief Show how many item in tree
     * @param NULL
     * @return Size of tree
     */

    uintmax_t size()const
    {
        return mSize;
    }

private:

    /**
     * @brief Write value in tree.
     * @param Smart pointer which you check
     * @param Value which you want insert
     * @return NULL
     */
    void writeValueInTree(std::shared_ptr<CBinaryTreeItem<T>>& aObj, const T& aValue)
    {
        if (aObj == nullptr)
        {
            n = std::make_shared<CBinaryTreeItem<T>>(aValue);
            aObj = n;
            mSize++;
        }

        if (aValue < (aObj->mValue)) // go to left
        {
            if ((aObj->mLeft) == nullptr)
            {
                n = std::make_shared<CBinaryTreeItem<T>>(aValue);
                aObj->mLeft = n;
                mSize++;
            }
            else
            {
                writeValueInTree(aObj->mLeft, aValue);
            }
        }
        else // go to right
        {
            if ((aObj->mValue) == aValue)
            {
                return;
            }

            if ((aObj->mRight) == nullptr)
            {
                n = std::make_shared<CBinaryTreeItem<T>>(aValue);
                aObj->mRight = n;
                mSize++;
            }
            else
            {
                writeValueInTree(aObj->mRight, aValue);
            }
        }
    }

    /**
     * @brief Copy binary tree
     * @param Pointer at present root
     * @param Pointer at source root
     * @return NULL
     */
    std::shared_ptr<CBinaryTreeItem<T>> copyBinaryTree(const std::shared_ptr<CBinaryTreeItem<T>>& aObj)
    {
        if (aObj == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<CBinaryTreeItem<T>> tmp = std::make_shared<CBinaryTreeItem<T>>(aObj->mValue);
        tmp->mLeft = copyBinaryTree(aObj->mLeft);
        tmp->mRight = copyBinaryTree(aObj->mRight);
        mSize++;
        return tmp;
    }


    /**
     * @brief Compares tree
     * @param Pointer at item from present treemRoot
     * @param Pointer at item from object tree
     * @return true if trees similar.Otherway false
     */
    bool identicalBinaryTrees(  const std::shared_ptr<CBinaryTreeItem<T>>& thisRoot,
                                const std::shared_ptr<CBinaryTreeItem<T>>& objRoot) const
    {

        if ((thisRoot == nullptr) && (objRoot == nullptr))
        {
            return true;
        }
        if ((thisRoot != nullptr) && (objRoot != nullptr))
        {
            bool arg1 = (thisRoot->mValue == objRoot->mValue);
            bool arg2 = (identicalBinaryTrees(thisRoot->mLeft, objRoot->mLeft));
            bool arg3 = (identicalBinaryTrees(thisRoot->mRight, objRoot->mRight));

            return (arg1 && arg2 && arg3);
        }
        return false;
    }

    /**
     * @brief Find nessesery item in tree
     * @param Pointer at item
     * @param Value
     * @return Pointer at item which contain aValue
     */
    bool findItemBinaryTree(const std::shared_ptr<CBinaryTreeItem<T>>& aObj, const T& aValue) const
    {
        if (aObj == nullptr)
        {
            return false;
        }
        if (aObj->mValue == aValue)
        {
            return true;
        }
        if ((aObj->mLeft) != nullptr)
        {
            if (findItemBinaryTree(aObj->mLeft, aValue))
            {
                return true;
            }
        }
        if ((aObj->mRight) != nullptr)
        {
            if (findItemBinaryTree(aObj->mRight, aValue))
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Delete nessesery item from tree
     * @param Pointer at item
     * @param Value
     * @return Pointer at item which contain aValue
     */
    std::shared_ptr<CBinaryTreeItem<T>> deleteItemBinaryTree(std::shared_ptr<CBinaryTreeItem<T>>& aObj, const T& aValue)
    {
        if (aObj == nullptr)
        {
            return nullptr;
        }

        if (aValue < aObj->mValue)// go to left
        {
            aObj->mLeft = deleteItemBinaryTree(aObj->mLeft, aValue);
        }
        else if (aValue > aObj->mValue) // go to right
        {
            aObj->mRight = deleteItemBinaryTree(aObj->mRight, aValue);
        }
        else
        {
            if (((aObj->mLeft) == nullptr) && ((aObj->mRight) == nullptr))
            {
                aObj = nullptr;
            }
            else if ((aObj->mLeft) == nullptr)
            {
                std::shared_ptr<CBinaryTreeItem<T>> tmp = aObj;
                aObj = aObj->mRight;
                tmp = nullptr;
            }
            else if ((aObj->mRight) == nullptr)
            {
                std::shared_ptr<CBinaryTreeItem<T>> tmp = aObj;
                aObj = aObj->mLeft;
                tmp = nullptr;
            }
            else
            {
                std::shared_ptr<CBinaryTreeItem<T>> tmp = findMin(aObj->mRight);
                aObj->mValue = tmp->mValue;
                aObj->mRight = deleteItemBinaryTree(aObj->mRight, tmp->mValue);
            }
        }
        return aObj;
    }


    /**
     * @brief This function looking for min element
     * @param Pointer at item
     * @return Min aValue in tree
     */
    std::shared_ptr<CBinaryTreeItem<T>> findMin(std::shared_ptr<CBinaryTreeItem<T>>& aObj)
    {
        if (aObj == nullptr)
        {
            return nullptr;
        }
        if (aObj->mLeft != nullptr)
        {
            return findMin(aObj->mLeft);
        }
        return aObj;
    }

    /**
     * @brief Print all value from tree
     * @param Pointer at root
     * @return NULL
     */
    void printTree(const std::shared_ptr<CBinaryTreeItem<T>>& aObj)
    {
        if (aObj != nullptr)
        {
            std::cout << aObj->mValue << std::endl;
            printTree(aObj->mRight);
            printTree(aObj->mLeft);
        }
        else
        {
            return;
        }
    }

    /**
     * @brief Show max value which is in tree
     * @param Pointer at item
     * @return Max value of tree
     */
    T getMaxValue(const std::shared_ptr<CBinaryTreeItem<T>>& aObj)
    {
        if ((aObj->mRight) == nullptr)
        {
            return aObj->mValue;
        }
        else
        {
            return getMaxValue(aObj->mRight);
        }
    }

    /**
     * @brief Show min value which is in tree
     * @param Pointer at item
     * @return Min value of tree
     */
    T getMinValue(const std::shared_ptr<CBinaryTreeItem<T>>& aObj)
    {
        if ((aObj->mLeft) == nullptr)
        {
            return aObj->mValue;
        }
        else
        {
            return getMinValue(aObj->mLeft);
        }
    }

    /**
     * @brief Free allocate memory which have tree
     * @param NULL
     * @return NULL
     */
    void iniBinaryTree()
    {
        mRoot = nullptr;
        n = nullptr;
        mSize = 0;
    }

    /**
     * @brief Pointer to the first item of the tree.
     */
    std::shared_ptr<CBinaryTreeItem<T>> mRoot;
    /**
     * @brief Pointer to the intermediary item of the tree.
     */
    std::shared_ptr<CBinaryTreeItem<T>> n;
    /**
    * @brief Show how many items present in tree.
    */
    uintmax_t mSize;
};


#endif
