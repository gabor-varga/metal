#ifndef DIFF_PARAMETER_H
#define DIFF_PARAMETER_H


#include <memory>
#include <string>
#include <vector>


namespace diff
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

} // namespace diff

#endif // DIFF_PARAMETER_H
