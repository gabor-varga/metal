#ifndef METAL_SCALARUNARYOP_H
#define METAL_SCALARUNARYOP_H


#include "ScalarBase.h"


namespace metal
{

    /**
     * @brief Proxy ET type to represent a unary operation in which exactly one other expression
     * (scalar) take part in.
     *
     * The operation type is taken as a parameter when constructing the object. The partial
     * derivative vector expression is cached at construction, as the dimension has to be the same
     * as the incoming expression (since there is no source of additional parameters).
     *
     * @tparam Expr Type of expression the unary operation acts on
     * @tparam Op Type of operation to be applied on the expression
     */
    template< typename Expr, typename Op >
    class ScalarUnaryOp : public ScalarBase< ScalarUnaryOp< Expr, Op > >
    {

    public:
        /** Alias for type of partial derivative vector. Using Eigen row vector */
        using Partial = typename Op::Output;

        /** Alias for Eigen segment ET to represent part of the derivative vector */
        using PartialSegment = decltype( std::declval< Partial >().segment( int(), int() ) );

        /** Alias for the iterator */
        using IteratorType = Iterator< ScalarUnaryOp< Expr, Op > >;


        /**
         * @brief Construct a new Scalar Unary Op object using an expression to apply an operation
         * to.
         *
         * @param expr Expression as input for an operator to transform
         * @param op Operation that defines the transformation
         */
        ScalarUnaryOp( const Expr& expr, const Op& op )
            : expr_{ expr }
            , op_{ op }
            , partial_{ op_.applyToPartial( expr_.value(), expr_.partial() ) }
        {
        }

        /**
         *  @copydoc ScalarBase::value()
         */
        double value() const
        {
            return op_.applyToValue( expr_.value() );
        }

        /**
         *  @copydoc ScalarBase::partial()
         */
        Partial partial() const
        {
            return partial_;
        }

        /**
         *  @copydoc ScalarBase::parameterMap()
         */
        auto parameterMap() const
        {
            return expr_.parameterMap();
        }

        /**
         *  @copydoc ScalarBase::dim()
         */
        size_t dim() const
        {
            return expr_.dim();
        }

        /**
         *  @copydoc ScalarBase::size()
         */
        size_t size() const
        {
            return expr_.size();
        }

        /**
         *  @copydoc ScalarBase::parameters()
         */
        ParameterPtrVector parameters() const
        {
            return expr_.parameters();
        }

        /**
         *  @copydoc ScalarBase::begin()
         */
        IteratorType begin() const
        {
            return IteratorType( *this, expr_.parameterMap().begin() );
        }

        /**
         *  @copydoc ScalarBase::end()
         */
        IteratorType end() const
        {
            return IteratorType( *this, expr_.parameterMap().end() );
        }

    private:
        /** Internal expression to apply the unary operator on */
        const Expr& expr_;

        /** Operation to apply on the expression */
        Op op_;

        /** Internal cached expression for the partial derivative vector after applying the
         * operation */
        Partial partial_;
    };

} // metal

#endif // METAL_SCALARUNARYOP_H
