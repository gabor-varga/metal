#ifndef METAL_UNARYDIVISIONOP_H
#define METAL_UNARYDIVISIONOP_H


#include "ScalarUnaryOp.h"


namespace metal
{

enum class DivisionMode
{
    Normal,
    Reverse
};

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for dividing
 * an expression and to a floating point number.
 */
template< DivisionMode Flag >
class UnaryDivisionOp
{

public:
    /**
     * @brief Construct a new Unary Division Op object with a scalar to divide the expression with,
     * or to divide this scalar with an expression. This depends on the DivisionMode flag.
     *
     * @param scalar Addend
     */
    explicit UnaryDivisionOp( double scalar )
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
        return ( Flag == DivisionMode::Normal ) ? value / scalar_ : scalar_ / value;
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @param value Value of the expression
     * @return double Partial
     */
    double partial( double value ) const
    {
        return ( Flag == DivisionMode::Normal ) ? 1.0 / scalar_ : 1.0 / value;
    }

private:
    /** Scalar to be added to the expression */
    double scalar_;
};


/**
 * @brief Binary division operator between an expression and a floating point number.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to divide
 * @param divisor Floating point value to divide with
 * @return ScalarUnaryOp< Expr, UnaryDivisionOp > Expression that represents the division
 */
template< typename Expr >
ScalarUnaryOp< Expr, UnaryDivisionOp< DivisionMode::Normal > > operator/(
    const ScalarBase< Expr >& expr, double divisor )
{
    return ScalarUnaryOp< Expr, UnaryDivisionOp< DivisionMode::Normal > >{
        static_cast< const Expr& >( expr ), UnaryDivisionOp< DivisionMode::Normal >{ divisor }
    };
}

/**
 * @brief Binary division operator between a floating point number and an expression.
 *
 * @tparam Expr Type of the expression
 * @param dividend Floating point value to divide
 * @param expr Expression to divide with
 * @return ScalarUnaryOp< Expr, UnaryDivisionOp > Expression that represents the division
 */
template< typename Expr >
ScalarUnaryOp< Expr, UnaryDivisionOp< DivisionMode::Reverse > > operator/(
    double dividend, const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, UnaryDivisionOp< DivisionMode::Reverse > >{
        static_cast< const Expr& >( expr ), UnaryDivisionOp< DivisionMode::Reverse >{ dividend }
    };
}

} // metal

#endif // METAL_UNARYDIVISIONOP_H
