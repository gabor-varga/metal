#ifndef METAL_BINARYADDITIONOP_H
#define METAL_BINARYADDITIONOP_H


#include "ScalarBinaryOp.h"


namespace metal
{

/**
 * @brief Binary operation taken by \ref ScalarBinaryOp object to define the expression for adding
 * two expressions.
 *
 */
class BinaryAdditionOp
{

public:
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param left LHS of the addition
     * @param right RHS of the addition
     * @return double Result of addition
     */
    double applyToValue( double left, double right ) const
    {
        return left + right;
    }

    /**
     * @brief Computes the partial derivative of the result w.r.t the LHS.
     *
     * @return double Partial w.r.t. the LHS
     */
    double leftPartial( double, double ) const
    {
        return 1.0;
    }

    /**
     * @brief Computes the partial derivative of the result w.r.t the RHS.
     *
     * @return double Partial w.r.t. the RHS
     */
    double rightPartial( double, double ) const
    {
        return 1.0;
    }
};


/**
 * @brief Binary addition operator between two expressions.
 *
 * @tparam Left Type of the LHS expression
 * @tparam Right Type of the RHS expression
 * @param left LHS expression
 * @param right RHS expression
 * @return ScalarBinaryOp< Left, Right, BinaryAdditionOp > Expression that represents the
 * addition
 */
template< typename Left, typename Right >
ScalarBinaryOp< Left, Right, BinaryAdditionOp > operator+(
    const ScalarBase< Left >& left, const ScalarBase< Right >& right )
{
    return ScalarBinaryOp< Left, Right, BinaryAdditionOp >( static_cast< const Left& >( left ),
        static_cast< const Right& >( right ), BinaryAdditionOp{} );
}

} // metal

#endif // METAL_BINARYADDITIONOP_H
