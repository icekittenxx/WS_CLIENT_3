#ifndef UMA_BSON_DOUBLE_H
#define UMA_BSON_DOUBLE_H

#include <uma/bson/PrimitiveValue.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Double
     *
     * \brief A POD that represents a double value in a BSON element.
     *
     * \date Created 2012/09/13 17:39
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Double.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API Double : public PrimitiveValue<double>
    {
    public:
      /// Default CTOR
      Double() : PrimitiveValue( 0.0 ) {}

      /**
       * @brief Create a new instance that encapsulates the specified
       * double value.
       *
       * @param v The value to encapsulate in this instance.
       */
      explicit Double( const double v ) : PrimitiveValue( v ) {}

      /**
       * @brief Returns the number of bytes the BSON representation of
       * this instance.
       *
       * @return Returns the value from the BSON specification (\c 8).
       */
      int32_t getSize() const { return 8; }

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::Double
       */
      Value::Type getType() const { return Value::Double; }
    };

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_DOUBLE_H
