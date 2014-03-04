#ifndef UMA_BSON_TIMESTAMP_H
#define UMA_BSON_TIMESTAMP_H

#include <uma/bson/Value.h>
#include <Poco/Timestamp.h>

#include <sstream>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Timestamp
     *
     * \brief A POD that represents a database timestamp BSON element value.
     *
     * Timestamp values are represented by an 8 byte long number.  The
     * first four bytes are used to represent the increment value, and
     * the next four bytes represent the seconds since UNIX epoch time.
     *
     * \date Created 2012/09/09 21:55
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Timestamp.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API Timestamp : public Value
    {
    public:
      /// Default CTOR
      Timestamp() : time( Poco::Timestamp() ), increment( 0 ) {}

      /**
       * @brief Create a new instance with the specified increment
       * and time values.
       *
       * @param seconds The time since UNIX epoch to encapsulate
       * @param inc The increment value to encapsulate
       */
      Timestamp( const std::time_t seconds, const int32_t inc ) :
        time( Poco::Timestamp::fromEpochTime( seconds ) ),
        increment( inc ) {}

      /**
       * @brief Return the time value in this instance as a
       * constant reference.
       *
       * @return The time value.
       */
      const Poco::Timestamp& getTime() const { return time; }

      /**
       * @brief Return the time value in this instance as a
       * non-constant reference.
       *
       * @return The time value.
       */
      Poco::Timestamp& getTime() { return time; }

      /**
       * @brief Set the time value encapsulated in this instance
       *
       * @param ts The new value to set
       * @return This instance for method chaining
       */
      Timestamp& setTime( const Poco::Timestamp& ts )
      {
        time = ts;
        return *this;
      }

      /**
       * @brief Set the time value encapsulated in this instance
       *
       * @param seconds The seconds since UNIX epoch value to set.
       * @return This instance for method chaining
       */
      Timestamp& setTime( const std::time_t seconds )
      {
        time = Poco::Timestamp::fromEpochTime( seconds );
        return *this;
      }

      /**
       * @brief Returns the increment value encapsulated in this instance.
       *
       * @return The increment value
       */
      int32_t getIncrement() const { return increment; }

      /**
       * @brief Set the increment value encapsulated in this instance
       *
       * @param inc The new increment value
       * @return This instance for method chaining
       */
      Timestamp& setIncrement( const int32_t inc )
      {
        increment = inc;
        return *this;
      }

      /**
       * @brief Return a string representation of the data encapsulated
       * in this instance primarily intended for logging/debugging
       * purposes.
       *
       * @return Textual representation of the data.
       */
      std::string toString() const
      {
        std::stringstream ss;
        ss << "{ \"t\" : " << time.epochTime() <<
              ", \"i\" : " << increment << " }";
        return ss.str();
      }

      /**
       * @brief Return the size in bytes of the BSON representation of
       * this instance.
       *
       * @return Returns \c 8 as per BSON specifications
       */
      int32_t getSize() const { return 8; }

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::Timestamp
       */
      Value::Type getType() const { return Value::Timestamp; }

    private:
      Poco::Timestamp time;
      int32_t increment;
    };


    /**
     * @brief Compare two timestamps for equality.  Compares the
     * timestamp and increment values of both instances for equality.
     *
     * @since 2.0
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true if the two instances have the same values.
     */
    inline bool operator == ( const Timestamp& lhs, const Timestamp& rhs )
    {
      return ( ( lhs.getTime() == rhs.getTime() ) &&
          ( lhs.getIncrement() == rhs.getIncrement() ) );
    }

    /// Just the reverse of operator ==
    inline bool operator != ( const Timestamp& lhs, const Timestamp& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_TIMESTAMP_H
