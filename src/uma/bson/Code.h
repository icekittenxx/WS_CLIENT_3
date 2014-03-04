#ifndef UMA_BSON_CODE_H
#define UMA_BSON_CODE_H

#include <uma/bson/Text.h>
#include <uma/bson/Value.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Code
     *
     * \brief A POD that represents a code type BSON element value.
     *
     * \date Created 2012/09/05 19:55
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Code.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API Code : public Text
    {
    public:
      /// Default CTOR
      Code() : Text() {}

      /**
       * @brief Create a new instance with the specified code value.
       *
       * @param v The code value to encapsulate
       */
      Code( const std::string& v ) : Text( v ) {}

      /**
       * @brief Create a new instance from a C-style char array.
       *
       * @param data The code value to encapsulate
       */
      Code( const char* data ) : Text( data ) {}

      /**
       * @brief Returns the type for a code instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::Code
       */
      Value::Type getType() const { return Value::Code; }
    };

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_CODE_H
