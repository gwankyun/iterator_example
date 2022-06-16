#pragma once
#include "common.hpp"
#include "LegacyForwardIterator.hpp"

template<typename Iter>
struct LegacyBidirectionalIterator
    : public Indirection<LegacyBidirectionalIterator<Iter>, Iter>
    , public Increment<LegacyBidirectionalIterator<Iter>, Iter>
    , public Decrement<LegacyBidirectionalIterator<Iter>, Iter>
    , public MemberAccess<LegacyForwardIterator<Iter>, Iter>
    , public Assignment<LegacyForwardIterator<Iter>, Iter>
    , public Equality<LegacyForwardIterator<Iter>, Iter>
{
#ifdef __cpp_lib_concepts
    using iterator_concept = std::bidirectional_iterator_tag;
#endif

    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;

    typedef std::bidirectional_iterator_tag iterator_category;

    LegacyBidirectionalIterator() {}

    LegacyBidirectionalIterator(const LegacyBidirectionalIterator& other)
    : m_iter(other.m_iter)
    {}

    ~LegacyBidirectionalIterator() {}

    LegacyBidirectionalIterator(pointer ptr) : m_iter(ptr) {}

    LegacyBidirectionalIterator& operator=(const pointer ptr)
    {
        m_iter = ptr;
        return *this;
    }

    pointer& get()
    {
        return m_iter;
    }

    const pointer& get() const
    {
        return m_iter;
    }

private:
    pointer m_iter;
};

template<typename T>
inline bool operator==(
    const LegacyBidirectionalIterator<T>& lhs,
    const LegacyBidirectionalIterator<T>& rhs)
{
    return lhs == rhs;
}

template<typename T>
inline bool operator!=(
    const LegacyBidirectionalIterator<T>& lhs,
    const LegacyBidirectionalIterator<T>& rhs)
{
    return !(lhs == rhs);
}
