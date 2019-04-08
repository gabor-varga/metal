#ifndef METAL_BINARYTRIGONOP_H
#define METAL_BINARYTRIGONOP_H


#include "src/ScalarBinaryOp.h"
#include <cmath>


namespace metal
{

/**
 * @brief Unary operation taken by \ref ScalarBinaryOp object to define the expression for
 * computing the sine of an expression.
 */
class Atan2Op
{

public:
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param left LHS of the operation
     * @param right RHS of the operation
     * @return double Result of operation
     */
    double applyToValue( double left, double right ) const
    {
        return std::atan2( left, right );
    }

    /**
     * @brief Computes the partial derivative of the result w.r.t the LHS.
     *
     * @return double Partial w.r.t. the LHS
     */
    double leftPartial( double left, double right ) const
    {
        return right / cache( left, right );
    }

    /**
     * @brief Computes the partial derivative of the result w.r.t the RHS.
     *
     * @return double Partial w.r.t. the RHS
     */
    double rightPartial( double left, double right ) const
    {
        return -left / cache( left, right );
    }

private:
    struct Cache
    {
        static bool same( double left, double right )
        {
            return std::fabs( left - right ) <= 0.0;
        }

        double left;
        double right;
        double norm;
    };

    double cache( double left, double right ) const
    {
        if ( !Cache::same( left, cache_.left ) || !Cache::same( right, cache_.right ) )
        {
            cache_ = { left, right, left * left + right * right };
        }
        return cache_.norm;
    }

    mutable Cache cache_;
};


/**
 * @brief Binary arc tangent function for two expressions.
 *
 * @tparam Left Type of the LHS expression
 * @tparam Right Type of the RHS expression
 * @param left LHS expression
 * @param right RHS expression
 * @return ScalarBinaryOp< Left, Right, Atan2Op >  Expression that represents the arc tangent
 * function
 */
template< typename Left, typename Right >
ScalarBinaryOp< Left, Right, Atan2Op > atan2(
    const ScalarBase< Left >& left, const ScalarBase< Right >& right )
{
    return ScalarBinaryOp< Left, Right, Atan2Op >(
        static_cast< const Left& >( left ), static_cast< const Right& >( right ), Atan2Op{} );
}

} // metal

#endif // METAL_BINARYTRIGONOP_H
