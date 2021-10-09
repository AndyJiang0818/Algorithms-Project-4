// Xihao Jiang
// CSCI 335
// Homework 4
// 4/12/21
// Implement double hashing, and rehashing.

#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include "quadratic_probing.h"

// Double hashing implementation.
template <typename HashedObj>
class HashTableDouble
{
public:
  enum EntryType
  {
    ACTIVE,
    EMPTY,
    DELETED
  };

  explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
  {
    MakeEmpty();
  }

  bool Contains(const HashedObj &x)
  {
    probe = 1;
    return IsActive(FindPos(x));
  }

  void MakeEmpty()
  {
    current_size_ = 0;
    collisions = 0;
    probe = 0;
    R = 7;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj &x)
  {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;

    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;

    // Rehashing
    if (++current_size_ > array_.size() / 2)
      Rehash();
    return true;
  }

  bool Insert(HashedObj &&x)
  {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;

    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehashing
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj &x)
  {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  void SetR(int R)
  {
    this->R = R;
  }

  int getNumberOfElement()
  {
    return current_size_;
  }

  int getSizeOfTable()
  {
    return array_.size();
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
    EntryType info_;

    HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY)
        : element_{e}, info_{i} {}

    HashEntry(HashedObj &&e, EntryType i = EMPTY)
        : element_{std::move(e)}, info_{i} {}
  };

  std::vector<HashEntry> array_;
  size_t current_size_;
  int collisions;
  int probe;
  int R;

  bool IsActive(size_t current_pos)
  {
    return array_[current_pos].info_ == ACTIVE;
  }

  size_t FindPos(const HashedObj &x)
  {
    size_t offset = 1;
    size_t current_pos = InternalHash(x);
    size_t index1 = InternalHash(x);
    size_t index2 = InternalHash2(x);
    while (array_[current_pos].info_ != EMPTY &&
           array_[current_pos].element_ != x)
    {
      collisions++;
      probe++;
      current_pos = (index1 + offset * index2) % array_.size();
      offset++;
      if (current_pos >= array_.size())
        current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash()
  {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto &entry : array_)
      entry.info_ = EMPTY;

    // Copy table over.
    current_size_ = 0;
    for (auto &entry : old_array)
      if (entry.info_ == ACTIVE)
        Insert(std::move(entry.element_));
  }

  size_t InternalHash(const HashedObj &x) const
  {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size();
  }

  size_t InternalHash2(const HashedObj &x) const
  {
    static std::hash<HashedObj> hf;
    return R - (hf(x) % R);
  }
};

#endif // DOUBLE_PROBING_H
