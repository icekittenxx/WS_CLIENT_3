#ifndef UMA_BSON_BOOLEAN_H
#define UMA_BSON_BOOLEAN_H

#include <uma/bson/PrimitiveValue.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Boolean
     *
     * \brief A POD that represents a boolean type BSON element value.
     *
     * \date Created 2012/09/13 18:15
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Boolean.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API Boolean : public PrimitiveValue<bool>
    {
    public:
      /// Default CTOR
      Boolean() : PrimitiveValue( false ) {}

      /**
       * @brief Create a new instance that encapsulates the specified
       * value.
       *
       * @param v The boolean to encapsulate
       */
      explicit Boolean( const bool v ) : PrimitiveValue( v ) {}

      /**
       * @brief Return the size in bytes occupied by this instance.
       *
       * This is used to compute the total size of a bson
       * {@link uma::bson::Document} or {@link uma::bson::Array}
       *
       * @return The size in bytes (\c 1)
       */
      int32_t getSize() const { return 1; }

      /**
       * @brief Return the type for a boolean value as listed in the
       * BSON specifications
       *
       * @return Returns {@link uma::bson::Value}::Type::Boolean
       */
      Value::Type getType() const { return Value::Boolean; }
    };

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_BOOLEAN_H
