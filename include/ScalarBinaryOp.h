#ifndef METAL_SCALARBINARYOP_H
#define METAL_SCALARBINARYOP_H


#include "ScalarBase.h"


namespace metal
{

template< typename Left, typename Right, typename Op >
class ScalarBinaryOp;


/**
 * @brief Type trait for the partial segment type of a scalar binary operator.
 *
 * @tparam Left Left hand side expression type in the binary operation
 * @tparam Right Right hand side expression type in the binary operation
 * @tparam Op Binary operation type
 */
template< typename Left, typename Right, typename Op >
struct PartialSegment< ScalarBinaryOp< Left, Right, Op > >
{
    /** Alias for internal type */
    using Type = EigenRowVector;
};


/**
 * @brief Proxy ET type to represent a binary operation which uses two other sub-expressions as
 * left-hand-side (LHS) and right-hand-side (RHS).
 *
 * @tparam Left Left hand side expression type in the binary operation
 * @tparam Right Right hand side expression type in the binary operation
 * @tparam Op Binary operation type
 */
template< typename Left, typename Right, typename Op >
class ScalarBinaryOp : public ScalarBase< ScalarBinaryOp< Left, Right, Op > >
{

public:
    /** Alias for type of partial derivative vector. */
    using Partial = EigenRowVector;

    /** Alias for Eigen segment ET to represent part of the derivative vector */
    using PartialSegment = typename PartialSegment< ScalarBinaryOp< Left, Right, Op > >::Type;


    /**
     * @brief Construct a new Scalar Binary Op object using two expression as LHS and RHS of the
     * operation as well as the operator to be applied.
     *
     * @param left Left-hand-side expression
     * @param right Right-hand-side expression
     * @param op Operation to apply on LHS and RHS
     */
    ScalarBinaryOp( const Left& left, const Right& right, const Op& op )
        : left_{ left }
        , right_{ right }
        , op_{ op }
        , cache_{ left_.value(), right_.value() }
        , value_{ op_.applyToValue( cache_.first, cache_.second ) }
        , parameters_{ left_.parameters() }
    {
        // Cache some checks to help optimally construct the vector of all parameters that the
        // expression references
        const bool condition1 = parameters_.size() == 0;
        const bool condition2 = right_.size() && left_.parameters() != right_.parameters();

        // @TODO: This part could probably be optimised better
        if ( condition1 || condition2 )
        {
            const auto& params = right_.parameters();
            parameters_.insert( parameters_.end(), params.begin(), params.end() );
        }
        if ( condition2 )
        {
            std::sort( parameters_.begin(), parameters_.end() );
            parameters_.erase(
                std::unique( parameters_.begin(), parameters_.end() ), parameters_.end() );
        }
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
        // @TODO: This could be cached, but is only ever called once in Scalar constructor, and I
        // don't see other application from the user point of view
        const auto func = []( int tmp, const ParameterPtr& p ) { return tmp + p->dim(); };
        return std::accumulate( parameters_.begin(), parameters_.end(), size_t{ 0 }, func );
    }

    /**
     *  @copydoc ScalarBase::size()
     */
    size_t size() const
    {
        return parameters_.size();
    }

    /**
     *  @copydoc ScalarBase::parameters()
     */
    const ParameterPtrVector& parameters() const
    {
        return parameters_;
    }

    /**
     *  @copydoc ScalarBase::contains()
     */
    bool contains( const ParameterPtr& p ) const
    {
        // @TODO: Since the parameter vector is sorted, this should be O(N). Maybe it should be
        // replaced by std::set to have O(1) complexity
        return std::find( parameters_.begin(), parameters_.end(), p ) != parameters_.end();
    }

    /**
     *  @copydoc ScalarBase::at()
     */
    PartialSegment at( const ParameterPtr& p ) const
    {
        // @TODO: This is quite expensive, and should not be used in performant code. Generally the
        // expression will be optimally evaluated when constructing a Scalar from it, and that is
        // the main use-case.

        PartialSegment out = PartialSegment::Zero( p->dim() );

        if ( left_.contains( p ) )
        {
            out += op_.leftPartial( cache_.first, cache_.second ) * left_.at( p );
        }
        if ( right_.contains( p ) )
        {
            out += op_.rightPartial( cache_.first, cache_.second ) * right_.at( p );
        }

        return out;
    }

    /**
     *  @copydoc ScalarBase::accum()
     */
    void accum( EigenRowVectorSegment& partial, double scalar, const ParameterPtr& p ) const
    {
        if ( left_.contains( p ) )
        {
            left_.accum( partial, scalar * op_.leftPartial( cache_.first, cache_.second ), p );
        }
        if ( right_.contains( p ) )
        {
            right_.accum( partial, scalar * op_.rightPartial( cache_.first, cache_.second ), p );
        }
    }

private:
    /** Alias for cache of the operator partials */
    using Cache = std::pair< double, double >;

    /** LHS expression */
    const Left& left_;

    /** RHS expression */
    const Right& right_;

    /** Binary operator */
    Op op_;

    /** Cached operator partials */
    Cache cache_;

    /** Cached value */
    double value_;

    /** Cached parameters from expression */
    ParameterPtrVector parameters_;
};

} // metal

#endif // METAL_SCALARBINARYOP_H
