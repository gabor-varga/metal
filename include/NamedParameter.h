#ifndef METAL_NAMEDPARAMETER_H
#define METAL_NAMEDPARAMETER_H


#include "Parameter.h"


namespace metal
{

/**
 * @brief Named parameter which implements the parameter interface in its simplest form.
 *
 */
class NamedParameter : public Parameter
{

public:
    /**
     * @brief Construct a new NamedParameter object.
     *
     * @param dim Dimension of the parameter
     * @param name Name of the parameter
     */
    NamedParameter( int dim, const std::string& name )
        : dim_{ dim }
        , name_{ name }
    {
    }

    int dim() const override
    {
        return dim_;
    }

    const std::string& name() const override
    {
        return name_;
    }

private:
    /** Dimension of the parameter */
    int dim_;

    /** Name of the parameter */
    std::string name_;
};

} // namespace metal

#endif // METAL_NAMEDPARAMETER_H
