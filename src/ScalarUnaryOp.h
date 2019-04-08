#ifndef METAL_SCALARUNARYOP_H
#define METAL_SCALARUNARYOP_H


#include "src/ScalarBase.h"


namespace metal
{

template< typename Expr, typename Op >
class ScalarUnaryOp;


/**
 * @brief Type trait for the partial segment type of a scalar unary operator.
 * 
 * @tparam Expr Type of the sub-expression referenced by this unary operation
 * @tparam Op Unary operation type
 */
template< typename Expr, typename Op >
struct PartialSegment< ScalarUnaryOp< Expr, Op > >
{
    /** Alias for internal type */
    using Type = decltype( std::declval< typename PartialSegment< Expr >::Type >() * double{} );
};


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
    /** Alias for Eigen segment ET to represent part of the derivative vector */
    using PartialSegment = typename PartialSegment< ScalarUnaryOp< Expr, Op > >::Type;


    /**
     * @brief Construct a new Scalar Unary Op object using an expression to apply an operation
     * to.
     *
     * @param expr Expression as input for an operator to transform
     * @param op Operation that defines the transformation
     */
    ScalarUnaryOp( const Expr& expr, const Op& op )
        : expr_( expr )
        , op_( op )
        , cache_{ expr_.value() }
        , value_{ op_.applyToValue( cache_ ) }
        , partial_{ op_.partial( cache_ ) }
    {
    }

    /**
     *  @copydoc ScalarBase::value()
     */
    double value() const
    {
        return value_;
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
     *  @copydoc ScalarBase::contains()
     */
    bool contains( const ParameterPtr& p ) const
    {
        return expr_.contains( p );
    }

    /**
     *  @copydoc ScalarBase::at()
     */
    PartialSegment at( const ParameterPtr& p ) const
    {
        if ( !contains( p ) )
        {
            throw std::runtime_error( "Error! Parameter not present in partials: '"
                + ( p ? p->name() : "NULLPTR" ) + "'" );
        }
        // return partial_.segment( expr_.parameterMap().at( p ), p->dim() );
        return expr_.at( p ) * partial_;
    }

    /**
     *  @copydoc ScalarBase::accum()
     */
    void accum( EigenRowVectorSegment& partial, const ParameterPtr& p ) const
    {
        expr_.accum( partial, partial_, p );
    }

    /**
     *  @copydoc ScalarBase::accum()
     */
    void accum( EigenRowVectorSegment& partial, double scalar, const ParameterPtr& p ) const
    {
        expr_.accum( partial, scalar * partial_, p );
    }

private:
    /** Internal expression to apply the unary operator on */
    typename RefTypeSelector< Expr >::Type expr_;

    /** Operation to apply on the expression */
    Op op_;

    /** Cached sub-expression value */
    double cache_;

    /** Computed expression value */
    double value_;

    /** Partial w.r.t. the sub-expression */
    double partial_;
};

} // metal

#endif // METAL_SCALARUNARYOP_H
