#ifndef METAL_FASTVEC_H
#define METAL_FASTVEC_H


#include <algorithm>


namespace metal
{

template< typename T >
class FastVecConstSegment;

template< typename T >
class FastVecSegment;


template< typename T >
class FastVec
{

public:
    using Data = T*;

    FastVec() = default;

    FastVec( unsigned size )
        : data_{ allocate( size ) }
        , size_{ size }
    {
    }

    FastVec( unsigned size, const T& value )
        : FastVec{ size }
    {
        std::fill( data_, data_ + size_, value );
    }

    ~FastVec()
    {
        release( data_ );
        data_ = nullptr;
        size_ = 0;
    }

    FastVec( const FastVec& other )
        : data_{ allocate( other.size_ ) }
        , size_{ other.size_ }
    {
        std::copy( other.data_, other.data_ + other.size_, data_ );
    }

    FastVec( FastVec&& other )
        : data_{ other.data_ }
        , size_{ other.size_ }
    {
        other.data_ = nullptr;
        other.size_ = 0;
    }

    FastVec& operator=( const FastVec& other )
    {
        resize( other.size_ );
        std::copy( other.data_, other.data_ + other.size_, data_ );
        return *this;
    }

    FastVec& operator=( FastVec&& other )
    {
        if ( size_ )
        {
            release( data_ );
        }
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
        return *this;
    }

    void resize( unsigned size )
    {
        if ( size > size_ )
        {
            if ( size_ )
            {
                release( data_ );
            }
            data_ = allocate( size );
        }
        size_ = size;
    }

    Data data() const
    {
        return data_;
    }

    unsigned size() const
    {
        return size_;
    }

    FastVecConstSegment< T > segment( unsigned start, unsigned span ) const
    {
        return FastVecConstSegment< T >{ *this, start, span };
    }

    FastVecSegment< T > segment( unsigned start, unsigned span )
    {
        return FastVecSegment< T >{ *this, start, span };
    }

private:
    static Data allocate( unsigned size )
    {
        return size ? new T[size] : nullptr;
    }
    static void release( Data data )
    {
        delete[] data;
    }

    Data data_ = nullptr;
    unsigned size_ = 0;
};


template< typename T >
class FastVecConstSegment
{

public:
    FastVecConstSegment( const FastVec< T >& vec, unsigned start, unsigned span )
        : vec_{ vec }
        , start_{ start }
        , span_{ span }
    {
    }

    const FastVec< T >& vec() const
    {
        return vec_;
    }

    unsigned start() const
    {
        return start_;
    }

    unsigned span() const
    {
        return span_;
    }

private:
    const FastVec< T >& vec_;
    unsigned start_;
    unsigned span_;
};


template< typename T >
class FastVecSegment
{

public:
    FastVecSegment( FastVec< T >& vec, unsigned start, unsigned span )
        : vec_{ vec }
        , start_{ start }
        , span_{ span }
    {
    }

    FastVecSegment& operator+=( const FastVec< T >& other )
    {
        std::transform( vec_.data() + start_, vec_.data() + start_ + span_, other.data(),
            vec_.data() + start_, binaryAddOp );
        return *this;
    }

    FastVecSegment& operator+=( const FastVecConstSegment< T >& other )
    {
        std::transform( vec_.data() + start_, vec_.data() + start_ + span_, other.vec().data(),
            vec_.data() + start_, binaryAddOp );
        return *this;
    }

private:
    static double binaryAddOp( double left, double right )
    {
        return left + right;
    }

    FastVec< T >& vec_;
    unsigned start_;
    unsigned span_;
};

} // metal

#endif // METAL_FASTVEC_H
