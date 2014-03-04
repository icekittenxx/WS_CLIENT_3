#ifndef UMA_BSON_OID_H
#define UMA_BSON_OID_H

#include <uma/bson/Value.h>
#include <uma/bson/Bson.h>
#include <Poco/Timestamp.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::ObjectId
     *
     * \brief A POD that represents a MongoDB OID type.
     *
     * A POD that represents a MongoDB OID type.  OID's encode the
     * creation time of the OID, and hence may be used as an efficient
     * creation date property for the document.
     *
     * \date Created 2012/09/06 19:04
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: ObjectId.h 192 2012-12-23 22:51:30Z spt $
     */
    class UMA_BSON_API ObjectId : public Value
    {
    public:
      /**
       * @brief Default constructor.  Create a new instance with the the
       * current timestamp or specified value.
       *
       * Note that this version stores the microsecond time part in the
       * last 4 bytes of the OID.  This allows a very precise timestamp
       * for the OID value to be retrieved.  The middle 4 bytes are still
       * populated using a random sequence, which hopefully will make
       * the generated OID value close to globally unique.
       *
       * @param ts The timestamp to initialise the OID from.  Defaults to
       *   current time.
       */
      explicit ObjectId( const Poco::Timestamp& ts = Poco::Timestamp() ) : data( ts ) {}

      /**
       * @brief Create a new OID from the byte array specified.
       *
       * @param (value)[] The 12 byte array to initialise from
       */
      explicit ObjectId( const char (&value)[12] ) : data( value ) {}

      /**
       * @brief Create oid from 24 char hex string
       *
       * @param str The string representation from which to initialise the OID
       */
      explicit ObjectId( const std::string& str ) : data( str ) {}

      /**
       * @brief Create a new OID with the three components that the OID
       * bytes represent
       *
       * @param date The time stamp used to initialise the instance.  Note
       *   that only the seconds from UNIX epoch will be used to populate
       *   the first 4 bytes
       * @param random The random value used to populate the second 4 bytes.
       * @param sequence The sequence number used to populate the last 4 bytes.
       */
      ObjectId( const Poco::Timestamp& date, const int random, const int sequence ) :
          data( date, random, sequence ) {}

      /**
       * @brief Return the timestamp value encoded in this OID
       *
       * @return The timestamp value.
       */
      const Poco::Timestamp getTime() const { return data.getTime(); }

      /**
       * @brief Return a 24 char hex representation of the OID
       *
       * @return The hex representation
       */
      const std::string toString() const { return data.toString(); }

      /**
       * @brief Populate the specified char array with the contents of
       * the OID
       *
       * @param bytes The byte array (ideally 12 char in length) that
       *   is to be populated with the contents of the OID value.
       * @param max The optional maximum number of characters to write
       *   into the \c bytes array.  Defaults to \c 12
       */
      void getBytes( char* bytes, const int max = 12 ) const
      {
        data.getBytes( bytes, max );
      }

      /**
       * @brief Replaces the bytes represented in this instance with the
       * specified byte array.
       *
       * @since Version 2.3
       * @param The 12 byte char array to assign to this object id.
       */
      void setBytes( const char (&bytes)[12] ) { data.setBytes( bytes ); }

      /**
       * @brief Return the size in bytes of the BSON representation of this
       * OID value.
       *
       * @return Return \c 12 as per specifications
       */
      int32_t getSize() const { return 12; }

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::OID
       */
      Value::Type getType() const { return Value::OID; }

    private:
      union Data
      {
      public:
        explicit Data( const Poco::Timestamp& ts = Poco::Timestamp() );
        explicit Data( const char (&value)[12] );
        explicit Data( const std::string& str );
        Data( const Poco::Timestamp& date, const int random, const int sequence );

        Data( const Data& );
        Data& operator = ( const Data& rhs );

        const Poco::Timestamp getTime() const;
        const std::string toString() const;

        void getBytes( char* buffer, const int max = 12 ) const;
        void setBytes( const char (&value)[12] );

        bool operator == ( const Data& rhs ) const;

      private:
        void init( const Poco::Timestamp& ts );

      private:
        char bytes[12];
        int32_t ints[3];
      };

      Data data;
    };

    /**
     * @brief Less than operator for comparing ObjectId instances.
     *
     * @return Return \c true if the left hand object id is considered
     *   less (earlier) than the right hand object id.
     */
    inline bool operator < ( const ObjectId& lhs, const ObjectId& rhs )
    {
      return lhs.getTime() < rhs.getTime();
    }

    /**
     * @brief Greater than operator for comparing ObjectId instances.
     *
     * @return Return \c true if the left hand object id is considered
     *   greater (newer) than the right hand object id.
     */
    inline bool operator > ( const ObjectId& lhs, const ObjectId& rhs )
    {
      return lhs.getTime() > rhs.getTime();
    }

    /**
     * @brief Compare two object id values for equality.  Compares the
     * data in each instance.
     *
     * @since 2.0
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true if the two id values are equivalent.
     */
    UMA_BSON_API bool operator == ( const ObjectId& lhs, const ObjectId& rhs );

    /// Just the reverse of operator ==
    inline bool operator != ( const ObjectId& lhs, const ObjectId& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_OID_H
