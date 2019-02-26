#ifndef METAL_PARAMETER_H
#define METAL_PARAMETER_H


#include <memory>
#include <string>
#include <vector>
#include <map>


namespace metal
{

    /**
     * @brief Parameter for which partial derivative is computed.
     *
     */
    class Parameter
    {

    public:
        /**
         * @brief Construct a new Parameter object.
         *
         * @param dim Dimension of the parameter
         * @param name Name of the parameter
         */
        Parameter( int dim, const std::string& name )
            : dim_{ dim }
            , name_{ name }
        {
        }

        /**
         * @brief Returns the dimension of the parameter.
         *
         * @return int Dimension of the parameter
         */
        int dim() const
        {
            return dim_;
        }

        /**
         * @brief Returns the name of the parameter.
         *
         * @return const std::string& Name of the parameter
         */
        const std::string& name() const
        {
            return name_;
        }

    private:
        /** Dimension of the parameter */
        int dim_;

        /** Name of the parameter */
        std::string name_;
    };

    /** Alias for shared pointer of a parmeter */
    using ParameterPtr = std::shared_ptr< Parameter >;

    /** Alias for vector the parameter pointers */
    using ParameterPtrVector = std::vector< ParameterPtr >;

    /** Alias for type of representing the range of the derivative vector that holds information
     * w.r.t to a specific parameter */
    using Span = std::pair< int, int >;

    /** Alias for type mapping the parameter space to derivative vector space */
    using ParameterMap = std::map< ParameterPtr, Span >;

} // namespace metal

#endif // METAL_PARAMETER_H
