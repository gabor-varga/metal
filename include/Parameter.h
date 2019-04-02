#ifndef METAL_PARAMETER_H
#define METAL_PARAMETER_H


#include <map>
#include <memory>
#include <string>
#include <vector>


namespace metal
{

/**
 * @brief Parameter pure abstract interface for which partial derivative is computed.
 *
 */
class Parameter
{

public:
    /**
     * @brief Destroy the Parameter object
     * 
     */
    virtual ~Parameter() = default;

    /**
     * @brief Returns the dimension of the parameter.
     *
     * @return int Dimension of the parameter
     */
    virtual int dim() const = 0;

    /**
     * @brief Returns the name of the parameter.
     *
     * @return const std::string& Name of the parameter
     */
    virtual const std::string& name() const = 0;
};


// Defined outside to avoid weak-vtables clang warning
// Parameter::~Parameter() {}

/** Alias for shared pointer of a parmeter */
using ParameterPtr = std::shared_ptr< Parameter >;

/** Alias for vector the parameter pointers */
using ParameterPtrVector = std::vector< ParameterPtr >;

/** Alias for type mapping the parameter space to derivative vector space */
using ParameterMap = std::map< ParameterPtr, int >;

} // namespace metal

#endif // METAL_PARAMETER_H
