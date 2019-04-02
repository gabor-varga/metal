#ifndef UTIL_EXCEPTION_H
#define UTIL_EXCEPTION_H


#include <exception>
#include <string>


namespace util
{

    class Thrower : public std::exception
    {

    public:
        Thrower( const std::string& msg, const std::string& func, const std::string& file, int line )
        : msg_( msg )
        , func_( func )
        , file_( file )
        , line_( line )
        {
            output_ += "Exception occured:";
            output_ += "\nMessage:  " + msg_;
            output_ += "\nFunction: " + func_;
            output_ += "\nFile:     " + file_;
            output_ += "\nLine:     " + std::to_string( line_ );
        }

        const char* what() const noexcept override
        {
            return output_.c_str();
        }

    private:
        const std::string msg_;
        const std::string func_;
        const std::string file_;
        const int line_;
        std::string output_;

    };
}

#define ASSERT( condition, message ) if ( ! ( condition ) ) throw Thrower( message, "", __FILE__, __LINE__ )

#endif // UTIL_EXCEPTION_H
