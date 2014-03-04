#ifndef UMA_BSON_VALUE_H
#define UMA_BSON_VALUE_H

#include <uma/bson/Bson.h>
#include <iostream>
#include <string>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Value
     *
     * The abstract base class that represents a BSON data type.  Concrete
     * implementations are used to represent the 18 types of data specified
     * in the BSON specifications.
     *
     * \date Created 2012/09/05 19:55
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Value.h 185 2012-12-21 15:39:00Z spt $
     */
    class UMA_BSON_API Value
    {
    public:
      /** BSON element/field types. */
      enum Type
      {
        Eoo = 0, ///< End of document/element
        Double = 1, ///< Floating point
        String = 2, ///< UTF-8 string
        Object = 3, ///< Embedded document
        Array = 4, ///< Embedded array
        BinData = 5, ///< Binary data
        Undefined = 6, ///< Undefined — Deprecated
        OID = 7, ///< MongoDB ObjectId
        Boolean = 8, ///< Boolean false: 0, true: 1
        Date = 9, ///< UTC datetime - milliseconds since UNIX epoch time
        Null = 10, ///< Null value
        RegEx = 11, ///< Regular expression
        DbRef = 12, ///< DBPointer — Deprecated
        Code = 13, ///< JavaScript code
        Symbol = 14, ///< Symbol — Deprecated
        CodeWScope = 15, ///< JavaScript code w/ scope
        Integer = 16, ///< 32-bit Integer
        Timestamp = 17, ///< Timestamp - increment: 4bytes, time: 4bytes
        Long = 18 ///< 64-bit integer
      };

      /// Virtual DTOR for sub-classes
      virtual ~Value() {}

      /**
       * @brief Return the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Implementations will return the appropriate
       *   enum value for its BSON data type.
       */
      virtual Type getType() const = 0;

      /**
       * @brief Return the size of the data as per BSON specifications.
       *
       * @return The size of the BSON data.
       */
      virtual int32_t getSize() const = 0;

      /**
       * @brief Returns a standard textual value for this type.
       *
       * @return A text value representing for the
       *   document type.  Useful for logging/debugging
       */
      const std::string& getTypeName() const { return getTypeName( getType() ); }

      /**
       * @brief Return a descriptive text about the specified type.
       *
       * @param type The type to describe
       * @return The textual description of the type.
       */
      static const std::string& getTypeName( const Type type );

    protected:
      Value() {}
    };

    /**
     * @brief Write integer representation of the value type to the
     * specified output stream.  This is primarily intended for use
     * while debugging/logging.  Note that this cannot be used to
     * write to BSON, since types are written as single byte char values.
     *
     * @param os The output stream to write to
     * @param type The value to write as an integer to the stream
     * @return The output stream for chaining calls.
     */
    inline std::ostream& operator << ( std::ostream& os, const Value::Type& type )
    {
      os << static_cast<int>( type );
      return os;
    }

    /**
     * @brief Compare two values for equality.  Default implementation
     * performs a true comparison of the standard value type implementations
     * provided by this API.
     *
     * @since 2.2
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true if the two instances are the same.
     */
    UMA_BSON_API bool operator == ( const Value& lhs, const Value& rhs );

    /// Just the reverse of operator ==
    inline bool operator != ( const Value& lhs, const Value& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_VALUE_H
