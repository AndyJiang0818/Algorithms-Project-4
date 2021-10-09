// Xihao Jiang
// CSCI 335
// Homework 4
// 4/12/21
// Implement linear probing.

#ifndef LINEAR_PROBLING
#define LINEAR_PROBLING

#include <vector>
#include <algorithm>
#include <functional>

// Linear probing implementation.
template <typename HashedObj>
class HashTableLinear
{
public:
    HashTableLinear(size_t size = 101)
    {
        capacity = size;
        MakeEmpty();
    }

    void MakeEmpty()
    {
        array_ = std::vector<std::vector<HashEntry>>();
        probe = 0;
        current_size_ = 0;
        collisions = 0;
        for (int i = 0; i < capacity; i++)
        {
            array_.push_back(std::vector<HashEntry>());
        }
    }

    bool Insert(HashedObj &x)
    {
        size_t current_pos = InternalHash(x);
        for (size_t i = 0; i < array_[current_pos].size(); i++)
        {
            if (array_[current_pos][i].element_ == x)
            {
                return false;
            }
            collisions++;
        }
        array_[current_pos].push_back(x);
        current_size_++;
        return true;
    }

    bool Remove(const HashedObj &x)
    {
        size_t current_pos = InternalHash(x);
        for (size_t i = 0; i < array_[current_pos].size(); i++)
        {
            if (array_[current_pos][i].element_ == x)
            {
                array_[current_pos].remove(i);
                return true;
            }
            collisions++;
        }
        return false;
    }

    bool Contains(const HashedObj &x)
    {
        probe = 1;
        size_t current_pos = InternalHash(x);
        for (size_t i = 0; i < array_[current_pos].size(); i++)
        {
            if (array_[current_pos][i].element_ == x)
            {
                return true;
            }
            collisions++;
            probe++;
        }
        return false;
    }

    int getNumberOfElement()
    {
        return current_size_;
    }

    int getSizeOfTable()
    {
        return current_size_;
    }

    int getNumberOfCollisions()
    {
        return collisions;
    }

    int getProbe()
    {
        return probe;
    }

private:
    struct HashEntry
    {
        HashedObj element_;

        HashEntry(const HashedObj &e = HashedObj{})
            : element_{e} {}

        HashEntry(HashedObj &&e)
            : element_{std::move(e)} {}
    };

    std::vector<std::vector<HashEntry>> array_;
    size_t current_size_;
    int collisions;
    int probe;
    int capacity;

    size_t InternalHash(const HashedObj &x) const
    {
        static std::hash<HashedObj> hf;
        return hf(x) % array_.size();
    }
};

#endif