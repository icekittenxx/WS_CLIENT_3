#ifndef UMA_BSON_STRING_H
#define UMA_BSON_STRING_H

#include <uma/bson/Text.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::String
     *
     * \brief A POD that represents a string value in a BSON element.
     *
     * \date Created 2012/09/05 19:55
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: String.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API String : public Text
    {
    public:
      /// Default CTOR
      String() {}

      /**
       * @brief Create a new instance that stores the specified value.
       *
       * @param v The string value to store
       */
      String( const std::string& v ) : Text( v ) {}

      /**
       * @brief Create a new instance from a C-style char array.
       *
       * @param data The string value to store
       */
      String( const char* data ) : Text( data ) {}

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::String
       */
      Value::Type getType() const { return Value::String; }
    };

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_STRING_H
