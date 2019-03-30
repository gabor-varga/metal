#ifndef METAL_VECTOR_H
#define METAL_VECTOR_H


#include "Core.h"
#include <iomanip>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <Eigen/Geometry>
#pragma clang diagnostic pop
#elif defined __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <Eigen/Geometry>
#pragma GCC diagnostic pop
#else
#include <Eigen/Geometry>
#endif


namespace Eigen
{

/**
 * @brief This template specialization of the Eigen num traits object is allowing the Scalar object
 * to be used as the scalar template parameter for Eigen vectors and matrices.
 */
template<>
struct NumTraits< metal::Scalar > : NumTraits< double >
{
    /** Alias for real type */
    using Real = metal::Scalar;

    /** Alias for non-integer type */
    using NonInteger = metal::Scalar;

    /** Alias for nested type */
    using Nested = metal::Scalar;

    /** Alias for literal type */
    using Literal = double;

    /**
     * @brief Enum fo further settings
     *
     */
    enum
    {
        IsComplex = 0, /** It is not complex */
        IsInteger = 0, /** It is not an integer */
        IsSigned = 1, /** It is signed*/
        RequireInitialization = 1, /** It does require initialization (construction)*/
        ReadCost = 1, /** It has normal read cost */
        AddCost = 3, /** It has higher addition cost */
        MulCost = 3 /** It has higher multiplication cost */
    };
};

/**
 * @brief Template specialization for determining the result type of a binary operation between
 * Scalar object and a floating point number. It is defined for any kind of binary operation.
 *
 * @tparam BinaryOp Type of the binary operation
 */
template< typename BinaryOp >
struct ScalarBinaryOpTraits< metal::Scalar, double, BinaryOp >
{
    /** Alias for return type */
    using ReturnType = metal::Scalar;
};

/**
 * @brief Template specialization for determining the result type of a binary operation between
 * floating point number and a Scalar object. It is defined for any kind of binary operation.
 *
 * @tparam BinaryOp Type of the binary operation
 */
template< typename BinaryOp >
struct ScalarBinaryOpTraits< double, metal::Scalar, BinaryOp >
{
    /** Alias for return type */
    using ReturnType = metal::Scalar;
};

} // Eigen


namespace metal
{

template< int Rows, int Cols >
using MatrixT = Eigen::Matrix< metal::Scalar, Rows, Cols >;

using Vector = MatrixT< -1, 1 >;
using Vector3 = MatrixT< 3, 1 >;


inline Vector create( const Eigen::Matrix< double, -1, 1 >& value, const std::string& name )
{
    const auto dim = value.size();
    Vector out{ dim };
    const auto partial = Eigen::Matrix< double, -1, -1 >::Identity( dim, dim );

    const auto p = std::make_shared< NamedParameter >( dim, name );
    for ( int i = 0; i < dim; i++ )
    {
        out[i] = metal::Scalar{ value[i], p, partial.row( i ) };
    }
    return out;
}


// inline std::ostream& operator<<( std::ostream& os, const Vector& vec )
inline void print( std::ostream& os, const Vector& vec )
{
    ParameterPtrVector params;
    for ( int i = 0; i < vec.size(); i++ )
    {
        const auto& p = vec[i].parameters();
        params.insert( params.end(), p.begin(), p.end() );
    }
    std::sort( params.begin(), params.end() );
    params.erase( std::unique( params.begin(), params.end() ), params.end() );

    const int maxParamNameWidth = 9;
    const int pad = 3;
    const int width = maxParamNameWidth + pad;

    os << std::setw( width ) << "";
    for ( const auto& p : params )
    {
        const auto& name = p->name();
        if ( p->dim() == 1 )
        {
            os << std::setw( width ) << name;
        }
        else
        {
            for ( int k = 0; k < p->dim(); k++ )
            {
                const std::string nameWithIndex = name + std::to_string( k );
                os << std::setw( width ) << nameWithIndex;
            }
        }
    }
    os << std::endl;

    for ( int i = 0; i < vec.size(); i++ )
    {
        os << std::setw( width ) << vec[i].value();
        for ( const auto& p : params )
        {
            if ( vec[i].contains( p ) )
            {
                const auto partial = vec[i].at( p );
                for ( int j = 0; j < partial.size(); j++ )
                    os << std::setw( width ) << partial[j];
            }
            else
            {
                os << std::setw( width * p->dim() ) << "";
            }
        }
        os << std::endl;
    }

    // return os;
}

} // metal

#endif // METAL_VECTOR_H
