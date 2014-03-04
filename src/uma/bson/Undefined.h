#ifndef UMA_BSON_UNDEFINED_H
#define UMA_BSON_UNDEFINED_H

#include <uma/bson/Value.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Undefined
     *
     * A POD that represents a BSON element of type undefined.
     *
     * \date Created 2012/09/06 18:55
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Undefined.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API Undefined : public Value
    {
    public:
      /// Default CTOR
      Undefined() {}

      /**
       * @brief Return the size in bytes for the BSON representation of
       * this value.
       *
       * @return Returns \c 0 as per specifications.
       */
      int32_t getSize() const { return 0; }

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::Undefined
       */
      Value::Type getType() const { return Value::Undefined; }
    };

    /**
     * @brief Compare two undefined values for equality.  Always returns true.
     *
     * @since 2.0
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true
     */
    inline bool operator == ( const Undefined& /* lhs */, const Undefined& /* rhs */ )
    {
      return true;
    }

    /// Just the reverse of operator ==
    inline bool operator != ( const Undefined& lhs, const Undefined& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_UNDEFINED_H
