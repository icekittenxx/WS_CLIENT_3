#ifndef UMA_BSON_EOO_H
#define UMA_BSON_EOO_H

#include <uma/bson/Value.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::EOO
     *
     * \brief A POD that represents a EOO value.
     *
     * \date Created 2012/09/05 20:30
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: EOO.h 181 2012-12-21 01:08:58Z spt $
     */
    class UMA_BSON_API EOO : public Value
    {
    public:
      /// Default CTOR
      EOO() {}

      /**
       * @brief Returns the size of the bson representation of this value
       * as per the BSON specifications.
       *
       * @return Returns \c 0
       */
      int32_t getSize() const { return 0; }

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::Eoo
       */
      Value::Type getType() const { return Value::Eoo; }
    };

    /**
     * @brief Compare two EOO values for equality.  Always returns \c true.
     *
     * @since 2.0
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true
     */
    inline bool operator == ( const EOO& /* lhs */, const EOO& /* rhs */ )
    {
      return true;
    }

    /// Just the reverse of operator ==
    inline bool operator != ( const EOO& lhs, const EOO& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_EOO_H
