#ifndef METAL_UNARYSUBTRACTIONOP_H
#define METAL_UNARYSUBTRACTIONOP_H


#include "ScalarUnaryOp.h"


namespace metal
{

enum class SubtractMode
{
    Normal,
    Reverse
};

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * subtracting an expression from a floating point number and vice-versa.
 */
template< SubtractMode Flag >
class UnarySubtractionOp
{

public:
    /**
     * @brief Construct a new Unary Subtraction Op object with a scalar to subtract from an
     * expression or to subtract the expression from. This depends on the SubtractMode flag.
     *
     * @param scalar Addend
     */
    explicit UnarySubtractionOp( double scalar )
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
        return ( Flag == SubtractMode::Normal ) ? value - scalar_ : scalar_ - value;
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double ) const
    {
        return ( Flag == SubtractMode::Normal ) ? 1.0 : -1.0;
    }

private:
    /** Scalar to be subtracted from the expression or to be the subtrahend */
    double scalar_;
};


/**
 * @brief Binary subtraction operator between an expression and a floating point number.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to subtract from
 * @param subtrahend Floating point value to subtract
 * @return ScalarUnaryOp< Expr, UnarySubtractionOp > Expression that represents the subtraction
 */
template< typename Expr >
ScalarUnaryOp< Expr, UnarySubtractionOp< SubtractMode::Normal > > operator-(
    const ScalarBase< Expr >& expr, double subtrahend )
{
    return ScalarUnaryOp< Expr, UnarySubtractionOp< SubtractMode::Normal > >{
        static_cast< const Expr& >( expr ), UnarySubtractionOp< SubtractMode::Normal >{ subtrahend }
    };
}

/**
 * @brief Binary subtraction operator between a floating point number and an expression.
 *
 * @tparam Expr Type of the expression
 * @param minuend Floating point value to subtract from
 * @param expr Expression to subtract
 * @return ScalarUnaryOp< Expr, UnarySubtractionOp > Expression that represents the subtraction
 */
template< typename Expr >
ScalarUnaryOp< Expr, UnarySubtractionOp< SubtractMode::Reverse > > operator-(
    double minuend, const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, UnarySubtractionOp< SubtractMode::Reverse > >{
        static_cast< const Expr& >( expr ), UnarySubtractionOp< SubtractMode::Reverse >{ minuend }
    };
}

} // metal

#endif // METAL_UNARYSUBTRACTIONOP_H
