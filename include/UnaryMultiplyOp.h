#ifndef METAL_UNARYMULTIPLYOP_H
#define METAL_UNARYMULTIPLYOP_H


#include "ScalarUnaryOp.h"


namespace metal
{

    template< typename Expr >
    class UnaryMultiplyOp
    {

    public:
        using Input = typename Expr::Partial;
        using Output = decltype( std::declval< Input >().operator*( double() ) );

        explicit UnaryMultiplyOp( double scalar )
            : scalar_{ scalar }
        {
        }

        double applyToValue( double value ) const
        {
            return value * scalar_;
        }

        Output applyToPartial( double, const Input& partial ) const
        {
            return partial * scalar_;
        }

    private:
        double scalar_;
    };


    template< typename Expr >
    ScalarUnaryOp< Expr, UnaryMultiplyOp< Expr > > operator*(
        const ScalarBase< Expr >& scalar, double multiplier )
    {
        return ScalarUnaryOp< Expr, UnaryMultiplyOp< Expr > >(
            static_cast< const Expr& >( scalar ), UnaryMultiplyOp< Expr >( multiplier ) );
    }

    template< typename Expr >
    ScalarUnaryOp< Expr, UnaryMultiplyOp< Expr > > operator*(
        double multiplier, const ScalarBase< Expr >& scalar )
    {
        return scalar * multiplier;
    }

} // metal

#endif // METAL_UNARYMULTIPLYOP_H
