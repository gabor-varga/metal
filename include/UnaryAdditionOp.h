#ifndef METAL_UNARYADDITIONOP_H
#define METAL_UNARYADDITIONOP_H


#include "ScalarUnaryOp.h"
#include "UnaryNegateOp.h"


namespace metal
{

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for adding
 * an expression and to a floating point number.
 */
class UnaryAdditionOp
{

public:
    /**
     * @brief Construct a new Unary Addition Op object with a scalar to add to an expression.
     *
     * @param scalar Addend
     */
    explicit UnaryAdditionOp( double scalar )
        : scalar_{ scalar }
    {
    }

    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return value + scalar_;
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double ) const
    {
        return 1.0;
    }

private:
    /** Scalar to be added to the expression */
    double scalar_;
};


/**
 * @brief Binary addition operator between an expression and a floating point number.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to add to
 * @param addend Floating point value to add
 * @return ScalarUnaryOp< Expr, UnaryAdditionOp > Expression that represents the
 * addition
 */
template< typename Expr >
ScalarUnaryOp< Expr, UnaryAdditionOp > operator+( const ScalarBase< Expr >& expr, double addend )
{
    return ScalarUnaryOp< Expr, UnaryAdditionOp >{ static_cast< const Expr& >( expr ),
        UnaryAdditionOp{ addend } };
}

/**
 * @brief Binary addition operator between a floating point number and an expression.
 *
 * @tparam Expr Type of the expression
 * @param augend Floating point value to add to
 * @param expr Expression to add
 * @return ScalarUnaryOp< Expr, UnaryAdditionOp > Expression that represents the
 * addition
 */
template< typename Expr >
ScalarUnaryOp< Expr, UnaryAdditionOp > operator+( double augend, const ScalarBase< Expr >& expr )
{
    // Since addition is commutative, just delegate
    return expr + augend;
}

// /**
//  * @brief Binary subtraction operator between an expression and a floating point number.
//  *
//  * @tparam Expr Type of the expression
//  * @param expr Expression to subtract from
//  * @param subtrahend Floating point value to subtract
//  * @return ScalarUnaryOp< Expr, UnaryAdditionOp > Expression that represents the
//  * inverse addition with negative subtrahend
//  */
// template< typename Expr >
// ScalarUnaryOp< Expr, UnaryAdditionOp > operator-(
//     const ScalarBase< Expr >& expr, double subtrahend )
// {
//     // Since subtraction is just addition with negated subtrahend
//     return expr + (-subtrahend);
// }

// /**
//  * @brief Binary subtraction operator between a floating point number and an expression.
//  *
//  * @tparam Expr Type of the expression
//  * @param minuend Floating point value to subtract from
//  * @param expr Expression to subtract
//  * @return ScalarUnaryOp< ScalarUnaryOp< Expr, UnaryNegateOp >, UnaryAdditionOp > Expression that
//  * represents the inverse addition with negated expression
//  */
// template< typename Expr >
// ScalarUnaryOp< ScalarUnaryOp< Expr, UnaryNegateOp >, UnaryAdditionOp > operator-(
//     double minuend, const ScalarBase< Expr >& expr )
// {
//     // Since subtraction is just addition with negated subtrahend
//     return minuend + (-expr);
// }

} // metal

#endif // METAL_UNARYADDITIONOP_H
