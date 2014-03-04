#ifndef UMA_BSON_DATE_H
#define UMA_BSON_DATE_H

#include <uma/bson/Value.h>
#include <Poco/Timestamp.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Date
     *
     * \brief A POD that represents a BSON element value of type date.
     *
     * Dates contain millisecond level precise date-time values.  Note
     * that the \c Poco::Timestamp used to represent the date-time is
     * capable of storing date-time with microsecond precision.
     *
     * \date Created 2012/09/06 20:13
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Date.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API Date : public Value
    {
    public:
      /// Default CTOR
      Date() : timestamp( Poco::Timestamp() ) {}

      /**
       * @brief Create a new instance from a UNIX time value.
       *
       * @param time The seconds since UNIX epoch time.
       */
      explicit Date( const int32_t time ) :
        timestamp( Poco::Timestamp::fromEpochTime( time ) ) {}

      /**
       * @brief Initialise with millisecond precision time since epoch time
       *
       * @param time The milliseconds elapsed since UNIX epoch time.
       */
      explicit Date( const int64_t time ) :
        timestamp( Poco::Timestamp::fromEpochTime( time / 1000 ) )
      {
        int64_t secs = timestamp.epochTime();
        int64_t millis = time - ( secs * 1000 );
        timestamp += millis * 1000;
      }

      /**
       * @brief Create a new date instance with the specified timestamp
       *
       * @param ts The timestamp to initialise this date with.
       */
      explicit Date( const Poco::Timestamp& ts ) : timestamp( ts ) {}

      /**
       * @brief Return the time encapsulated in this instance
       *
       * @return The time value
       */
      const Poco::Timestamp& getValue() const { return timestamp; }

      /**
       * @brief Set the time to be encapsulated in this instance.
       *
       * @param ts The new time value
       * @return This instance for method chaining.
       */
      Date& setValue( const Poco::Timestamp& ts )
      {
        timestamp = ts;
        return *this;
      }

      /**
       * @brief Returns a string representation of the time for
       * logging/debugging purposes.
       *
       * @return Returns the date-time in ISO 8601 format.
       */
      const std::string toString() const
      {
        return Poco::DateTimeFormatter::format(
            timestamp, Poco::DateTimeFormat::ISO8601_FORMAT );
      }

      /**
       * @brief Returns the size in bytes of the BSON representation of
       * this instance.
       *
       * @return Returns 8 - the length of a int64_t value
       */
      int32_t getSize() const { return 8; }

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::Date
       */
      Value::Type getType() const { return Value::Date; }

    private:
      Poco::Timestamp timestamp;
    };

    /**
     * @brief Compare the two data values for \c less-than operator
     *
     * @param lhs The left hand date to compare against
     * @param rhs The right hand date to compare against
     * @return Return \c true if the datetime in the left hand
     *   instance is lower than the datetime in the right hand instance.
     */
    inline bool operator < ( const Date& lhs, const Date& rhs )
    {
      return lhs.getValue() < rhs.getValue();
    }

    /**
     * @brief Compare the two data values for \c greater-than operator
     *
     * @param lhs The left hand date to compare against
     * @param rhs The right hand date to compare against
     * @return Return \c true if the left hand datetime instance
     *   is greater than the datetime in the right hand instance.
     */
    inline bool operator > ( const Date& lhs, const Date& rhs )
    {
      return lhs.getValue() > rhs.getValue();
    }

    /**
     * @brief Compare two date values for equality.
     *
     * @param lhs The left hand date to compare against
     * @param rhs The right hand date to compare against
     * @return Return \c true if the datetime values represented
     *   are equal.
     */
    inline bool operator == ( const Date& lhs, const Date& rhs )
    {
      return lhs.getValue() == rhs.getValue();
    }

    /// Just the reverse of operator ==
    inline bool operator != ( const Date& lhs, const Date& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_DATE_H
