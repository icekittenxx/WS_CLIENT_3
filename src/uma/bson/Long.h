#ifndef UMA_BSON_LONG_H
#define UMA_BSON_LONG_H

#include <uma/bson/PrimitiveValue.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Long
     *
     * \brief A POD that represents a long (64 bit integer) type BSON element value.
     *
     * \date Created 2012/09/13 18:17
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Long.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API Long : public PrimitiveValue<int64_t>
    {
    public:
      /// Default CTOR
      Long() : PrimitiveValue( 0 ) {}

      /**
       * @brief Create a new instance that encapsulates the specified
       * value.
       *
       * @param v The value to encapsulate
       */
      Long( const int64_t v ) : PrimitiveValue( v ) {}

      /**
       * @brief Return the size in bytes of the BSON representation of
       * this value.
       *
       * @return Returns \c 8 as per specifications
       */
      int32_t getSize() const { return 8; }

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::Long
       */
      Value::Type getType() const { return Value::Long; }

    private:
      int64_t value;
    };

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_LONG_H
