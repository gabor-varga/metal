#ifndef METAL_SCALAR_H
#define METAL_SCALAR_H


#include "NamedParameter.h"
#include "ScalarBase.h"
#include <numeric>


namespace metal
{

/**
 * @brief Concrete final type of the ET design architecture involving derivatives computation.
 *
 * Represents a scalar quantity including partial derivatives with respect to arbitrary number
 * of external parameters.
 *
 */
class Scalar : public ScalarBase< Scalar >
{

public:
    /** Alias for type of partial derivative vector. Using Eigen row vector */
    using Partial = EigenRowVector;

    /** Alias for Eigen segment ET to represent part of the derivative vector */
    using PartialSegment = Eigen::VectorBlock< const Partial, -1 >;

    /** Alias for the iterator */
    using IteratorType = Iterator< Scalar >;


    /**
     * @brief Construct a new Scalar object without holding partial deriatives.
     *
     * Default for the value is zero.
     *
     * @param value Value of the scalar object
     */
    explicit Scalar( double value = 0.0 )
        : value_{ value }
        , partial_{}
        , parameterMap_{}
    {
    }

    /**
     * @brief Construct a new Scalar object and creates a parameter with the specified name.
     *
     * The partial derivative w.r.t. this parameter is initialized to unity.
     *
     * @param value Value of the scalar object
     * @param name Name of the internal parameter
     */
    template< typename T = NamedParameter >
    Scalar( double value, const std::string& name )
        : value_{ value }
        , partial_{ Eigen::Matrix< double, 1, 1 >::Ones() }
        , parameterMap_{ { { std::make_shared< T >( 1, name ), 0 } } }
    {
    }

    /**
     * @brief Construct a new Scalar object from an existing expression by forcing the
     * evaluation of the value and partial derivatives.
     *
     * @tparam Expr Type of expression to evaluate
     * @param expr Expression to evaluate
     */
    template< typename Expr >
    Scalar( const ScalarBase< Expr >& expr )
        : value_{ expr.value() }
        , partial_{}
        , parameterMap_{}
    {
        const int totalDim = static_cast< int >( expr.dim() );
        partial_.setZero( totalDim );

        int id = 0;
        const auto& params = expr.parameters();
        for ( const auto& p : params )
        {
            const int dim = p->dim();
            auto segment = partial_.segment( id, dim );
            expr.accum( segment, 1.0, p );
            parameterMap_[p] = id;
            id += dim;
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
     *  @copydoc ScalarBase::partial()
     */
    const Partial& partial() const
    {
        return partial_;
    }

    /**
     *  @copydoc ScalarBase::dim()
     */
    const ParameterMap& parameterMap() const
    {
        return parameterMap_;
    }

    /**
     *  @copydoc ScalarBase::dim()
     */
    size_t dim() const
    {
        return static_cast< size_t >( partial_.size() );
    }

    /**
     *  @copydoc ScalarBase::size()
     */
    size_t size() const
    {
        return parameterMap_.size();
    }

    /**
     *  @copydoc ScalarBase::parameters()
     */
    ParameterPtrVector parameters() const
    {
        ParameterPtrVector out;
        for ( const auto& entry : parameterMap_ )
        {
            out.push_back( entry.first );
        }
        return out;
    }

    /**
     *  @copydoc ScalarBase::begin()
     */
    IteratorType begin() const
    {
        return IteratorType{ *this, parameterMap_.begin() };
    }

    /**
     *  @copydoc ScalarBase::end()
     */
    IteratorType end() const
    {
        return IteratorType{ *this, parameterMap_.end() };
    }

    /**
     *  @copydoc ScalarBase::count()
     */
    bool count( const ParameterPtr& p ) const
    {
        return parameterMap_.count( p );
    }

    /**
     *  @copydoc ScalarBase::at()
     */
    PartialSegment at( const ParameterPtr& p ) const
    {
        if ( !count( p ) )
        {
            throw std::runtime_error( "Error! Parameter not present in partials: '"
                + ( p ? p->name() : "NULLPTR" ) + "'" );
        }
        return partial_.segment( parameterMap_.at( p ), p->dim() );
    }

    /**
     *  @copydoc ScalarBase::accum()
     */
    void accum( EigenRowVectorSegment& partial, double scalar, const ParameterPtr& p ) const
    {
        partial += scalar * at( p );
    }

    /**
     * @brief In-place addition operator with a number.
     *
     * @param other Floating point value to add
     * @return Scalar& Reference to modified object
     */
    Scalar& operator+=( double other )
    {
        value_ += other;
        return *this;
    }

    /**
     * @brief In-place subtraction operator with a number.
     *
     * @param other Floating point value to subtract
     * @return Scalar& Reference to modified object
     */
    Scalar& operator-=( double other )
    {
        value_ -= other;
        return *this;
    }

    /**
     * @brief In-place multiplication operator with a number.
     *
     * @param other Floating point value to multiply with
     * @return Scalar& Reference to modified object
     */
    Scalar& operator*=( double other )
    {
        value_ *= other;
        partial_ *= other;
        return *this;
    }

    /**
     * @brief In-place division operator with a number.
     *
     * @param other Floating point value to divide with
     * @return Scalar& Reference to modified object
     */
    Scalar& operator/=( double other )
    {
        value_ /= other;
        partial_ /= other;
        return *this;
    }

private:
    /** Physical value of the scalar */
    double value_;

    /** Storage for partial derivative vector */
    Partial partial_;

    /** Associative map of parameters to their position and dimensino in the partial vector */
    ParameterMap parameterMap_;
};

} // metal

#endif // METAL_SCALAR_H
