#ifndef UMA_BSON_SYMBOL_H
#define UMA_BSON_SYMBOL_H

#include <uma/bson/Text.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Symbol
     *
     * \brief A POD that represents a programming language symbol type BSON
     * element value.
     *
     * \date Created 2012/09/09 21:49
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Symbol.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API Symbol : public Text
    {
    public:
      /// Default CTOR
      Symbol() {}

      /**
       * @brief Create a new instance that encapsulates the specified value.
       *
       * @param v The string value to encapsulate
       */
      Symbol( const std::string& v ) : Text( v ) {}

      /**
       * @brief Create a new instance from a C-style char array.
       *
       * @param data The string value to encapsulate
       */
      Symbol( const char* data ) : Text( data ) {}

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::Symbol
       */
      Value::Type getType() const { return Value::Symbol; }
    };

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_SYMBOL_H
