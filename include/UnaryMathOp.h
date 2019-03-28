#ifndef METAL_UNARYMATHOP_H
#define METAL_UNARYMATHOP_H


#include "ScalarUnaryOp.h"
#include <cmath>


namespace metal
{

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the sine of an expression.
 */
struct SineOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return std::sin( value );
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        return std::cos( value );
    }
};


/**
 * @brief Sine function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply sine to
 * @return ScalarUnaryOp< Expr, SineOp > Expression that represents the
 * sine operation
 */
template< typename Expr >
ScalarUnaryOp< Expr, SineOp > sin( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, SineOp >( static_cast< const Expr& >( expr ), SineOp{} );
}


/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the cosine of an expression.
 */
struct CosineOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return std::cos( value );
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        return -std::sin( value );
    }
};


/**
 * @brief Cosine function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply cosine to
 * @return ScalarUnaryOp< Expr, CosineOp > Expression that represents the
 * cosine operation
 */
template< typename Expr >
ScalarUnaryOp< Expr, CosineOp > cos( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, CosineOp >( static_cast< const Expr& >( expr ), CosineOp{} );
}


/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the tangent of an expression.
 */
struct TangentOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return std::tan( value );
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        const double tmp = std::cos( value );
        return 1.0 / ( tmp * tmp );
    }
};


/**
 * @brief Tangent function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply tangent to
 * @return ScalarUnaryOp< Expr, TangentOp > Expression that represents the
 * tangent operation
 */
template< typename Expr >
ScalarUnaryOp< Expr, TangentOp > tan( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, TangentOp >( static_cast< const Expr& >( expr ), TangentOp{} );
}

} // metal

#endif // METAL_UNARYMATHOP_H
