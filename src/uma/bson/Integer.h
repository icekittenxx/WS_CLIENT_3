#ifndef UMA_BSON_INTEGER_H
#define UMA_BSON_INTEGER_H

#include <uma/bson/PrimitiveValue.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Integer
     *
     * \brief A POD that represents an integer type BSON element value.
     *
     * \date Created 2012/09/13 18:02
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Integer.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API Integer : public PrimitiveValue<int32_t>
    {
    public:
      /// Default CTOR
      Integer() : PrimitiveValue( 0 ) {}

      /**
       * @brief Create a new instance that encapsulates the specified
       * value.
       *
       * @param v The integer to encapsulate
       */
      explicit Integer( const int32_t v ) : PrimitiveValue( v ) {}

      /**
       * @brief Return the size in bytes that the encapsulated value
       * represents as per the BSON specifications.
       *
       * @return Returns \c 4 as per specifications.
       */
      int32_t getSize() const { return 4; }

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::Integer
       */
      Value::Type getType() const { return Value::Integer; }
    };

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_INTEGER_H
