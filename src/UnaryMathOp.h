#ifndef METAL_UNARYMATHOP_H
#define METAL_UNARYMATHOP_H


#include "src/ScalarUnaryOp.h"
#include <cmath>


namespace metal
{

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the square of an expression.
 */
struct SquareOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return value * value;
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        return 2 * value;
    }
};


/**
 * @brief Sine function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply square to
 * @return ScalarUnaryOp< Expr, SquareOp > Expression that represents the square
 */
template< typename Expr >
ScalarUnaryOp< Expr, SquareOp > sqr( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, SquareOp >(
        static_cast< const Expr& >( expr ), SquareOp{} );
}

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the cube of an expression.
 */
struct CubeOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return value * value * value;
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        return 3 * value * value;
    }
};


/**
 * @brief Sine function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply square to
 * @return ScalarUnaryOp< Expr, CubeOp > Expression that represents the cube
 */
template< typename Expr >
ScalarUnaryOp< Expr, CubeOp > cube( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, CubeOp >(
        static_cast< const Expr& >( expr ), CubeOp{} );
}

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the square root of an expression.
 */
struct SquareRootOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return std::sqrt( value );
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        return 0.5 / std::sqrt( value );
    }
};


/**
 * @brief Sine function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply square root to
 * @return ScalarUnaryOp< Expr, SquareRootOp > Expression that represents the square root
 */
template< typename Expr >
ScalarUnaryOp< Expr, SquareRootOp > sqrt( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, SquareRootOp >(
        static_cast< const Expr& >( expr ), SquareRootOp{} );
}

} // metal

#endif // METAL_UNARYMATHOP_H
