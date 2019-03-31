#ifndef METAL_UNARYINVERSETRIGONOP_H
#define METAL_UNARYINVERSETRIGONOP_H


#include "ScalarUnaryOp.h"
#include <cmath>


namespace metal
{

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the inverse sine of an expression.
 */
struct InverseSineOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return std::asin( value );
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        return 1.0 / std::sqrt( 1.0 - value * value );
    }
};


/**
 * @brief Sine function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply inverse sine to
 * @return ScalarUnaryOp< Expr, InverseSineOp > Expression that represents the inverse
 * sine operation
 */
template< typename Expr >
ScalarUnaryOp< Expr, InverseSineOp > asin( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, InverseSineOp >(
        static_cast< const Expr& >( expr ), InverseSineOp{} );
}


/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the inverse cosine of an expression.
 */
struct InverseCosineOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return std::acos( value );
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        return -1.0 / std::sqrt( 1.0 - value * value );
    }
};


/**
 * @brief Cosine function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply inverse cosine to
 * @return ScalarUnaryOp< Expr, InverseCosineOp > Expression that represents the inverse
 * cosine operation
 */
template< typename Expr >
ScalarUnaryOp< Expr, InverseCosineOp > acos( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, InverseCosineOp >(
        static_cast< const Expr& >( expr ), InverseCosineOp{} );
}


/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the inverse tangent of an expression.
 */
struct InverseTangentOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return std::atan( value );
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        return 1.0 / ( 1.0 + value * value );
    }
};


/**
 * @brief Tangent function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply inverse tangent to
 * @return ScalarUnaryOp< Expr, InverseTangentOp > Expression that represents the inverse
 * tangent operation
 */
template< typename Expr >
ScalarUnaryOp< Expr, InverseTangentOp > atan( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, InverseTangentOp >(
        static_cast< const Expr& >( expr ), InverseTangentOp{} );
}

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the inverse sine hyperbolic of an expression.
 */
struct InverseSineHyperOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return std::asinh( value );
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        return 1.0 / std::sqrt( value * value + 1.0 );
    }
};


/**
 * @brief Sine function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply inverse sine hyperbolic to
 * @return ScalarUnaryOp< Expr, InverseSineHyperOp > Expression that represents the inverse
 * sine operation
 */
template< typename Expr >
ScalarUnaryOp< Expr, InverseSineHyperOp > asinh( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, InverseSineHyperOp >(
        static_cast< const Expr& >( expr ), InverseSineHyperOp{} );
}


/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the inverse cosine hyperbolic of an expression.
 */
struct InverseCosineHyperOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return std::acosh( value );
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        return 1.0 / std::sqrt( value * value - 1.0 );
    }
};


/**
 * @brief Cosine function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply  inverse cosine hyperbolic to
 * @return ScalarUnaryOp< Expr, InverseCosineHyperOp > Expression that represents the inverse
 * cosine operation
 */
template< typename Expr >
ScalarUnaryOp< Expr, InverseCosineHyperOp > acosh( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, InverseCosineHyperOp >(
        static_cast< const Expr& >( expr ), InverseCosineHyperOp{} );
}


/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the inverse tangent hyperbolic of an expression.
 */
struct InverseTangentHyperOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return std::atanh( value );
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        return 1.0 / ( 1.0 - value * value );
    }
};


/**
 * @brief Tangent function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply inverse tangent hyperbolic to
 * @return ScalarUnaryOp< Expr, InverseTangentHyperOp > Expression that represents the inverse
 * tangent operation
 */
template< typename Expr >
ScalarUnaryOp< Expr, InverseTangentHyperOp > atanh( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, InverseTangentHyperOp >(
        static_cast< const Expr& >( expr ), InverseTangentHyperOp{} );
}

} // metal

#endif // METAL_UNARYINVERSETRIGONOP_H
