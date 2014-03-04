#ifndef UMA_BSON_IO_WRITER_H
#define UMA_BSON_IO_WRITER_H

#include <uma/bson/Bson.h>

#include <iostream>
#include <string>

namespace uma
{
  namespace bson
  {
    namespace io
    {
      /**
       * \class uma::bson::io::Writer
       *
       * A base streaming writer class that transforms the data in a object
       * model into a BSON representation and writes it to an output stream.
       *
       * \date Created 2012/09/21 19:49
       * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
       * \author Rakesh
       * \version $Id: Writer.h 181 2012-12-21 01:08:58Z spt $
       */
      class UMA_BSON_API Writer
      {
      public:
        /// Virtual destructor for sub-classes
        virtual ~Writer() {}

      protected:
        /**
         * @brief Create a new instance of the writer that will write to
         * the specified output stream.
         *
         * @param os The output stream to write the BSON representation to
         */
        Writer( std::ostream& os ) : stream( os ) {}

        /**
         * @brief Return the output stream for use from sub-classes.
         *
         * @return std::ostream The output stream to which the BSON
         *   output is being written.
         */
        std::ostream& getStream() { return stream; }

        /**
         * @brief Writes a 32 bit integer value to the output stream
         *
         * @param value The value to serialise as BSON
         */
        void write( const int32_t value );

        /**
         * @brief Writes a 64 bit integer value to the output stream.
         *
         * @param value The value to serialise to BSON
         */
        void write( const int64_t value );

        /**
         * @brief Writes a \c double value to the output stream.
         *
         * @param value The value to serialise to BSON
         */
        void write( const double value );

        /**
         * @brief Writes a \c boolean value to the output stream.
         *
         * @param value The value to serialise to BSON
         */
        void write( const bool value );

        /**
         * @brief Writes a \c std::string value to the output stream.
         *
         * Used to serialise a std::string as BSON to the output stream.
         * This method is used to output both \c string and \c cstring
         * values as referred to in the BSON specifications.
         *
         * @param value The value to serialise to BSON
         * @param withLength Flag that indicates whether a \c string (\c true)
         *   or a \c cstring (\c false) is to be written.
         */
        void write( const std::string& value, const bool withLength = false );

        /**
         * @brief Writes binary data type value to the output stream.
         *
         * @param data The value to serialise to BSON
         */
        void write( const BinaryData& data );

        /**
         * @brief Writes a MongoDB OID value to the output stream.
         *
         * @param oid The value to serialise to BSON
         */
        void write( const ObjectId& oid );

        /**
         * @brief Writes a date-time value to the output stream.
         *
         * Date-time values are serialised as an \c int64_t value
         * that represents the milliseconds since UNIX epoch time -
         * January 1, 1970.
         *
         * @param date The value to serialise to BSON
         */
        void write( const Date& date );

        /**
         * @brief Writes a regular expression value to the output stream.
         *
         * @param regex The value to serialise to BSON
         */
        void write( const RegularExpression& regex );

        /**
         * @brief Writes a MongoDB database reference value to the output stream.
         *
         * @param dbref The value to serialise to BSON
         */
        void write( const DatabaseReference& dbref );

        /**
         * @brief Writes a code with scope value to the output stream.
         *
         * @param code The value to serialise to BSON
         */
        void write( const CodeWithScope& code );

        /**
         * @brief Writes a timestamp value to the output stream.
         *
         * Timestamps are written as a \c int64_t value, with the
         * first 4 bytes representing an increment value, and the
         * last 4 bytes representing a std::time_t value.
         *
         * @param ts The value to serialise to BSON
         */
        void write( const Timestamp& ts );

        /**
         * @brief Serialises a bson element to the output stream.
         *
         * Determines the {@link uma::bson::Element::getType()} value
         * for the element and delegates to the appropriate \c write
         * method for serialising the value.
         *
         * @param element The element to serialise to BSON
         */
        void write( const Element& element );

        /**
         * @brief Serialises a document to the output stream.
         *
         * This method is also used to serialise embedded document values.
         * Embedded document values are also included in values of type
         * {@link uma::bson::CodeWithScope} and
         * {@link uma::bson::BinaryData}.
         *
         * @param value The value to serialise to BSON
         */
        void write( const Document& doc );

        /**
         * @brief Serialises an array to the output stream.
         *
         * @param value The value to serialise to BSON
         */
        virtual void write( const Array& arr );

      private:
        std::ostream& stream;
      };

    } // namespace io
  } // namespace bson
} // namespace uma

#endif // UMA_BSON_IO_WRITER_H
