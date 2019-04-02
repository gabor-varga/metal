#ifndef METAL_FASTVEC_H
#define METAL_FASTVEC_H


#include <algorithm>
#include <iostream>


namespace metal
{

template< typename T >
class FastVecConstSegment;

template< typename T >
class FastVecScaledConstSegment;

template< typename T >
class FastVecSegment;


template< typename T >
class FastVec
{

public:
    using Data = T*;

    FastVec() = default;

    FastVec( int size )
        : data_{ allocate( size ) }
        , size_{ size }
    {
    }

    FastVec( int size, const T& value )
        : FastVec{ size }
    {
        std::fill( data_, data_ + size_, value );
    }

    FastVec( const FastVecConstSegment< T >& other )
        : data_{ allocate( other.size() ) }
        , size_{ other.size() }
    {
        std::copy( other.vec().data() + other.start(),
            other.vec().data() + other.start() + other.size(), data_ );
    }

    FastVec( const FastVecScaledConstSegment< T >& other )
        : data_{ allocate( other.size() ) }
        , size_{ other.size() }
    {
        std::copy( other.vec().data() + other.start(),
            other.vec().data() + other.start() + other.size(), data_ );
        *this *= other.scale();
    }

    // FastVec( const FastVecSegment< T >& other )
    //     : data_{ allocate( other.size() ) }
    //     , size_{ other.size() }
    // {
    //     std::copy( other.vec().data() );
    // }

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

    template< typename U >
    FastVec& operator*=( const U& scalar )
    {
        for ( int i = 0; i < size_; i++ )
        {
            data_[i] *= scalar;
        }
        return *this;
    }

    template< typename U >
    FastVec& operator/=( const U& scalar )
    {
        const double tmp = 1.0 / scalar;
        *this *= tmp;
        return *this;
    }

    void resize( int size )
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

    double operator[]( int index ) const
    {
        return data_[index];
    }

    double& operator[]( int index )
    {
        return data_[index];
    }

    int size() const
    {
        return size_;
    }

    FastVecConstSegment< T > segment( int start, int span ) const
    {
        return FastVecConstSegment< T >{ *this, start, span };
    }

    FastVecSegment< T > segment( int start, int span )
    {
        return FastVecSegment< T >{ *this, start, span };
    }

private:
    static Data allocate( int size )
    {
        return size ? new T[size] : nullptr;
    }
    static void release( Data data )
    {
        delete[] data;
    }

    Data data_ = nullptr;
    int size_ = 0;
};

template< typename T >
std::ostream& operator<<( std::ostream& os, const FastVec< T >& vec )
{
    for ( int i = 0; i < vec.size(); i++ )
    {
        os << vec[i] << std::endl;
    }
    return os;
}


template< typename T >
class FastVecConstSegment
{

public:
    FastVecConstSegment( const FastVec< T >& vec, int start, int span )
        : vec_{ vec }
        , start_{ start }
        , span_{ span }
    {
    }

    double operator[]( int index ) const
    {
        return vec_[start_ + index];
    }

    const FastVec< T >& vec() const
    {
        return vec_;
    }

    int start() const
    {
        return start_;
    }

    int size() const
    {
        return span_;
    }

private:
    const FastVec< T >& vec_;
    int start_;
    int span_;
};

template< typename T >
std::ostream& operator<<( std::ostream& os, const FastVecConstSegment< T >& segment )
{
    for ( int i = 0; i < segment.size(); i++ )
    {
        os << segment.vec()[segment.start() + i] << std::endl;
    }
    return os;
}

template< typename T >
class FastVecScaledConstSegment
{

public:
    FastVecScaledConstSegment( const FastVecConstSegment< T >& segment, double scale )
        : segment_{ segment }
        , scale_{ scale }
    {
    }

    double operator[]( int index ) const
    {
        return scale_ * segment_[index];
    }

    const FastVec< T >& vec() const
    {
        return segment_.vec();
    }

    int start() const
    {
        return segment_.start();
    }

    int size() const
    {
        return segment_.size();
    }

    double scale() const
    {
        return scale_;
    }

private:
    const FastVecConstSegment< T > segment_;
    double scale_;
};

template< typename T >
FastVecScaledConstSegment< T > operator*( const FastVecConstSegment< T >& segment, double scalar )
{
    return FastVecScaledConstSegment< T >{ segment, scalar };
}


template< typename T >
class FastVecSegment
{

public:
    FastVecSegment( FastVec< T >& vec, int start, int span )
        : vec_{ vec }
        , start_{ start }
        , span_{ span }
    {
    }

    double& operator[]( int index )
    {
        return vec_.data()[start_ + index];
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

    FastVecSegment& operator+=( const FastVecScaledConstSegment< T >& other )
    {
        std::transform( vec_.data() + start_, vec_.data() + start_ + span_, other.vec().data(),
            vec_.data() + start_, MultAndAddOp{ other.scale() } );
        return *this;
    }

private:
    static double binaryAddOp( double left, double right )
    {
        return left + right;
    }

    class MultAndAddOp
    {
    public:
        MultAndAddOp( double scale )
            : scale_{ scale }
        {
        }
        double operator()( double left, double right )
        {
            return left + scale_ * right;
        }

    private:
        double scale_;
    };

    FastVec< T >& vec_;
    int start_;
    int span_;
};

} // metal

#endif // METAL_FASTVEC_H
