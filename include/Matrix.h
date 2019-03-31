#ifndef METAL_MATRIX_H
#define METAL_MATRIX_H


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

/** Type alias for NxM matrix */
template< int Rows, int Cols >
using MatrixT = Eigen::Matrix< metal::Scalar, Rows, Cols >;

/** Type alias for dynamic matrix */
using Matrix = MatrixT< Eigen::Dynamic, Eigen::Dynamic >;

/** Type alias for 3x3 matrix */
using Matrix3 = MatrixT< 3, 3 >;

/** Type alias for 6x6 matrix */
using Matrix6 = MatrixT< 6, 6 >;

/** Type alias for N dimensional vector */
template< int Rows >
using VectorT = MatrixT< Rows, 1 >;

/** Type alias for dynamic vector */
using Vector = VectorT< Eigen::Dynamic >;

/** Type alias for 3 dimensional vector */
using Vector3 = VectorT< 3 >;

/** Type alias for 6 dimensional vector */
using Vector6 = VectorT< 6 >;


/**
 * @brief Creates a metal matrix vaiable from an Eigen matrix variable including the partial
 * derivatives referring to the named parameter created using the provided name.
 *
 * @tparam Rows Number of rows of the input/output matrix
 * @tparam Cols Number of columns of the input/output matrix
 * @param value Value of the matrix
 * @param name Name of the parameter to create
 * @return MatrixT< Rows, Cols > Matrix containing partials
 */
template< int Rows, int Cols >
MatrixT< Rows, Cols > create(
    const Eigen::Matrix< double, Rows, Cols >& value, const std::string& name )
{
    const int dim = static_cast< int >( value.size() );
    MatrixT< Rows, Cols > out{ value.rows(), value.cols() };
    const auto partial = Eigen::Matrix< double, -1, -1 >::Identity( dim, dim );

    const auto p = std::make_shared< NamedParameter >( dim, name );
    for ( int i = 0; i < dim; i++ )
    {
        out[i] = metal::Scalar{ value[i], p, partial.row( i ) };
    }
    return out;
}

} // metal


/**
 * @brief Specialized output operator for Eigen vector expressions which use metal Scalar object.
 * The output is optimized for viewing the value and partial derivatives. It is always using
 * scientific notation, and the precision can be set via the std::setprecision method.
 *
 * @tparam Derived Eigen vector expression type
 * @param os Output stream to output to
 * @param vec Vector expression to print
 * @return std::ostream& Modified output stream
 */
template< typename Derived,
    typename T = typename std::enable_if<
        std::is_same< typename Derived::Scalar, metal::Scalar >::value >::type >
std::ostream& operator<<( std::ostream& os, const Eigen::MatrixBase< Derived >& vec )
{
    metal::ParameterPtrVector params;
    for ( int i = 0; i < vec.size(); i++ )
    {
        const auto& p = vec[i].parameters();
        params.insert( params.end(), p.begin(), p.end() );
    }
    std::sort( params.begin(), params.end() );
    params.erase( std::unique( params.begin(), params.end() ), params.end() );

    const int prec = static_cast< int >( os.precision() );
    metal::detail::printHeader( os, params, prec );

    for ( int i = 0; i < vec.size(); i++ )
    {
        metal::detail::printValue( os, vec[i], prec );
    }

    return os;
}

#endif // METAL_MATRIX_H
