#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <cstring>
#include <type_traits>
#include <iterator>
#include <cstddef> // std::size_t
#include <vector>
#include <algorithm>
#include <string>
#include <concepts>
#include "LegacyIterator.hpp"
#include "LegacyInputIterator.hpp"
#include "LegacyOutputIterator.hpp"
#include "LegacyForwardIterator.hpp"
#include "LegacyBidirectionalIterator.hpp"
#include "LegacyRandomAccessIterator.hpp"

int main(int argc, char* argv[])
{
    doctest::Context context;

    context.applyCommandLine(argc, argv);
    context.setOption("no-breaks", true);

    int res = context.run();
    if (context.shouldExit())
    {
        return res;
    }

    context.clearFilters();

    return res;
}

template<typename T>
struct basic_string_view_const_iterator
{
    typedef std::size_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_category;

    basic_string_view_const_iterator() : m_ptr(NULLPTR) {}

    basic_string_view_const_iterator(const T* ptr) : m_ptr(ptr) {}

    ~basic_string_view_const_iterator() {}

    basic_string_view_const_iterator& operator+=(int n)
    {
        m_ptr += n;
        return *this;
    }

    basic_string_view_const_iterator& operator-=(int n)
    {
        m_ptr -= n;
        return *this;
    }

    reference operator[](std::size_t index)
    {
        return *(m_ptr + index);
    }

    reference operator*()
    {
        return *m_ptr;
    }

    basic_string_view_const_iterator& operator++()
    {
        m_ptr++;
        return *this;
    }

private:
    const T* m_ptr;
};

template<typename T>
inline basic_string_view_const_iterator<T> operator+(
    const basic_string_view_const_iterator<T>& lhs,
    int n)
{
    lhs += n;
    return lhs;
}

template<typename T>
inline basic_string_view_const_iterator<T> operator+(
    int n,
    const basic_string_view_const_iterator<T>& rhs)
{
    rhs += n;
    return rhs;
}

template<typename T>
inline basic_string_view_const_iterator<T> operator-(
    const basic_string_view_const_iterator<T>& lhs,
    int n)
{
    lhs -= n;
    return lhs;
}

template<typename T>
inline basic_string_view_const_iterator<T>::difference_type operator-(
    const basic_string_view_const_iterator<T>& lhs,
    const basic_string_view_const_iterator<T>& rhs)
{
    return lhs.m_ptr - rhs.m_ptr;
}

template<typename T>
inline bool operator<(
    const basic_string_view_const_iterator<T>& lhs,
    const basic_string_view_const_iterator<T>& rhs)
{
    return rhs - lhs > 0;
}

template<typename T>
inline bool operator>(
    const basic_string_view_const_iterator<T>& lhs,
    const basic_string_view_const_iterator<T>& rhs)
{
    return rhs < lhs;
}

template<typename T>
inline bool operator>=(
    const basic_string_view_const_iterator<T>& lhs,
    const basic_string_view_const_iterator<T>& rhs)
{
    return !(lhs < lhs);
}

template<typename T>
inline bool operator<=(
    const basic_string_view_const_iterator<T>& lhs,
    const basic_string_view_const_iterator<T>& rhs)
{
    return !(lhs > lhs);
}

TEST_CASE("const char*")
{
    std::string str("12345");
    const char* p = str.c_str();
    p++;
    CHECK(*p == '2');
}

TEST_CASE("char const*")
{
    std::string str("12345");
    char const* p = str.c_str();
    p++;
    CHECK(*p == '2');
}

template<typename T>
struct Iterator
{
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;

    static reference indirection(pointer ptr)
    {
        return *ptr;
    }

    static void prefix_increment(pointer& ptr)
    {
        ++ptr;
    }
};

template<typename T>
struct InputIterator
{
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;

    static reference indirection(pointer ptr)
    {
        return *ptr;
    }

    static void prefix_increment(pointer& ptr)
    {
        ++ptr;
    }

    static pointer member_access(pointer ptr)
    {
        return ptr;
    }
};

template<typename T>
struct OutputIterator
{
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;

    static reference indirection(pointer ptr)
    {
        return *ptr;
    }

    static void prefix_increment(pointer& ptr)
    {
        ++ptr;
    }

    static pointer member_access(pointer ptr)
    {
        return ptr;
    }
};

template<typename T>
struct ForwardIterator
{
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;

    static reference indirection(pointer ptr)
    {
        return *ptr;
    }

    static void prefix_increment(pointer& ptr)
    {
        ++ptr;
    }

    static pointer member_access(pointer ptr)
    {
        return ptr;
    }

    static bool equality(pointer a, pointer b)
    {
        return a == b;
    }
};

template<typename T>
struct BidirectionalIterator
{
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;

    static reference indirection(pointer ptr)
    {
        return *ptr;
    }

    static void prefix_increment(pointer& ptr)
    {
        ++ptr;
    }

    static void prefix_decrement(pointer& ptr)
    {
        --ptr;
    }

    static pointer member_access(pointer ptr)
    {
        return ptr;
    }
};

template<typename T>
struct RandomAccessIterator
{
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;

    static reference indirection(pointer ptr)
    {
        return *ptr;
    }

    static void prefix_increment(pointer& ptr)
    {
        ++ptr;
    }

    static pointer member_access(pointer ptr)
    {
        return ptr;
    }

    static reference subscript(pointer ptr, difference_type n)
    {
        return *(ptr + n);
    }

    static void addition_assignment(pointer& ptr, difference_type n)
    {
        ptr += n;
        return *this;
    }

    static void assignment(pointer& a, pointer b)
    {
        a = b;
    }

    static void subtraction_assignment(pointer& ptr, difference_type n)
    {
        ptr -= n;
        return *this;
    }

    static difference_type subtraction(pointer& a, pointer& b)
    {
        return a - b;
    }
};

TEST_CASE("LegacyIterator")
{
    using Iter_t = LegacyIterator<Iterator<int>>;

    std::vector<int> vec { 1, 2, 3, 4, 5 };
    Iter_t iter = vec.data();
    CHECK(std::indirectly_readable<Iter_t>);
    CHECK(std::weakly_incrementable<Iter_t>);
    CHECK((*iter == 1));
    ++iter;
    CHECK((*iter == 2));
    ++iter;
    CHECK((*iter == 3));
}

TEST_CASE("LegacyInputIterator")
{
    using Iter_t = LegacyInputIterator<InputIterator<int>>;

    CHECK(std::input_iterator<Iter_t>);

    std::vector<int> vec { 1, 2, 3, 4, 5 };
    Iter_t iter = vec.data();
    CHECK((*iter == 1));
    ++iter;
    CHECK((*iter == 2));
    ++iter;
    CHECK((*iter == 3));
    CHECK((*iter++ == 3));
}

TEST_CASE("LegacyOutputIterator")
{
    using Iter_t = LegacyOutputIterator<OutputIterator<int>>;

    CHECK(std::output_iterator<Iter_t, int>);

    std::vector<int> vec { 1, 2, 3, 4, 5 };
    Iter_t iter = vec.data();
    *iter++ = 6;
    CHECK(vec[0] == 6);
    CHECK(vec[1] == 2);
}

TEST_CASE("LegacyForwardIterator")
{
    using Iter_t = LegacyForwardIterator<ForwardIterator<int>>;

    CHECK(std::forward_iterator<Iter_t>);

    std::vector<int> vec { 1, 2, 3, 4, 5 };
    Iter_t iter = vec.data();
    *iter++ = 6;
    CHECK(vec[0] == 6);
    CHECK(vec[1] == 2);
}

TEST_CASE("LegacyBidirectionalIterator")
{
    using Iter_t = LegacyBidirectionalIterator<BidirectionalIterator<int>>;

    CHECK(std::bidirectional_iterator<Iter_t>);
}

TEST_CASE("LegacyRandomAccessIterator")
{    
    using Iter_t = LegacyRandomAccessIterator<RandomAccessIterator<int>>;

    CHECK(std::random_access_iterator<Iter_t>);
}
