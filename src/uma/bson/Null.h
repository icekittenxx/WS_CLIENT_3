#ifndef UMA_BSON_NULL_H
#define UMA_BSON_NULL_H

#include <uma/bson/Value.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Null
     *
     * \brief A POD that represents a null BSON element value.
     *
     * \date Created 2012/09/09 20:16
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Null.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API Null : public Value
    {
    public:
      /// Default CTOR
      Null() {}

      /**
       * @brief Returns the size of the object as per BSON specifications
       *
       * @return Returns \c 0
       */
      int32_t getSize() const { return 0; }

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::Null
       */
      Value::Type getType() const { return Value::Null; }
    };

    /**
     * @brief Compare two null values for equality.  Always returns \c true.
     *
     * @since 2.0
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true
     */
    inline bool operator == ( const Null& /* lhs */, const Null& /* rhs */ )
    {
      return true;
    }

    /// Just the reverse of operator ==
    inline bool operator != ( const Null& lhs, const Null& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_NULL_H
