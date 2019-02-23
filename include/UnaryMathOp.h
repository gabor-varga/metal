#ifndef METAL_UNARYMATHOP_H
#define METAL_UNARYMATHOP_H


#include "ScalarUnaryOp.h"


namespace metal
{

    template< typename Expr >
    struct SineOp
    {
        using Input = typename Expr::Partial;
        using Output = decltype( std::declval< Input >().operator*( double() ) );

        double applyToValue( double value ) const
        {
            return sin( value );
        }

        Output applyToPartial( double value, const Input& partial ) const
        {
            return partial * cos( value );
        }
    };

    template< typename Expr >
    ScalarUnaryOp< Expr, SineOp< Expr > > sin( const ScalarBase< Expr >& scalar )
    {
        return ScalarUnaryOp< Expr, SineOp< Expr > >(
            static_cast< const Expr& >( scalar ), SineOp< Expr >() );
    }

} // metal

#endif // METAL_UNARYMATHOP_H
