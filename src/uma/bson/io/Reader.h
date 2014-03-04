#ifndef UMA_BSON_IO_READER_H
#define UMA_BSON_IO_READER_H

#include <uma/bson/Bson.h>
#include <iostream>

namespace uma
{
  namespace bson
  {
    /**
     * \namespace uma::bson::io
     *
     * \brief Classes that provide IO support for BSON data.
     *
     * Namespace with classes that provide IO support for BSON
     * data.  Provides support for reading from BSON data, generating
     * BSON data, as well as JSON IO support.  The {@link
     * uma::bson::Document} and {@link uma::bson::Array} classes provide
     * support for BSON/JSON IO using classes in this namespace.  Clients
     * would normally not need to directly interact with these classes.
     */
    namespace io
    {
      /**
       * \class uma::bson::io::Reader
       *
       * \brief A base streaming parser that parses a stream of
       * BSON bytes from an input stream and transforms into a object model.
       *
       * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
       * \date Created 2012/09/24 11:42
       * \author Rakesh
       * \version $Id: Reader.h 181 2012-12-21 01:08:58Z spt $
       */
      class UMA_BSON_API Reader
      {
      public:
        /// Virtual destructor for sub-classes
        virtual ~Reader() {}

      protected:
        /**
         * @brief Reads the next 4 bytes of data from the input stream
         *   as a \c int32_t value.
         *
         * @param fin The input stream from which the value is to be read.
         * @return int32_t The value from the next 4 bytes in the stream.
         */
        int32_t readInt( std::istream &fin );

        /**
         * @brief Reads the next 8 bytes of data from the input stream
         *   as a \c double value.
         *
         * @param fin The input stream from which the value is to be read.
         * @return double The value from the next 8 bytes in the stream.
         */
        double readDouble( std::istream& fin );

        /**
         * @brief Reads the next 8 bytes of data from the input stream
         *   as a \c int64_t value.
         *
         * @param fin The input stream from which the value is to be read.
         * @return int64_t The value from the next 8 bytes in the stream.
         */
        int64_t readLong( std::istream& fin );

        /**
         * @brief Reads a \c string value from the stream as defined
         * in the BSON specification.
         *
         * As per the BSON specification \c string values are represented
         * by a \c int32_t value that holds the total length of the string
         * (including the null-terminator), followed by the stream of
         * bytes.  \c string instances may contain the null character
         * within in.
         *
         * @param fin The input stream to read from.
         * @param str The string that is to be appended the data from the
         *   input stream
         */
        void readString( std::istream& fin, std::string& str );

        /**
         * @brief Reads a \c cstring value from the stream as defined
         * in the BSON specification.
         *
         * As per the BSON specification \c cstring values are represented
         * by stream of characters terminated by a \c null-terminator
         * (similar to a char array in C).
         *
         * @param fin The input stream to read from.
         * @param str The string that is to be appended the data from the
         *   input stream
         */
        void readCharArray( std::istream& fin, std::string& str );

        /**
         * @brief Reads a binary data object from the stream.
         *
         * @param fin The input stream from which the value is to be read.
         * @return BinaryData The binary data encoded in the stream.
         */
        BinaryData readBinary( std::istream& fin );

        /**
         * @brief Reads the next 12 bytes from the stream into a MongoDB
         * OID value.
         *
         * @param fin The input stream to read from.
         * @return OID The OID instance representing the next 12 bytes
         *   in the stream.
         */
        ObjectId readOID( std::istream& fin );

        /**
         * @brief Reads a regular expression object from the stream
         *
         * @param fin The input stream to read from
         * @return RegularExpression The parsed regular expression instance.
         */
        RegularExpression readRegEx( std::istream& fin );

        /**
         * @brief Reads a MongoDB database reference instance from the
         * stream.
         *
         * @param fin The input stream to read from
         * @return DatabaseReference The parsed database reference instance.
         */
        DatabaseReference readDbRef( std::istream& fin );

        /**
         * @brief Reads a code object with scope document from the stream.
         *
         * @param fin The input stream to read from
         * @return CodeWithScope The parsed code with scope object instance.
         */
        CodeWithScope readCodeWScope( std::istream& fin );

        /**
         * @brief Reads the next 8 bytes from the stream into a MongoDB
         * timestamp object.
         *
         * @param fin The input stream to read from.
         * @return Timestamp The parsed timestamp instance.
         */
        Timestamp readTimestamp( std::istream& fin );

        /**
         * @brief Reads an embedded (or whole) document from the stream.
         *
         * The next 4 bytes of the stream indicate the total bytes that
         * make up the document.  Reads the data into a document instance.
         *
         * @param fin The input stream to read from
         * @return Document The parsed document instance.
         */
        Document readDocument( std::istream& fin );

        /**
         * @brief Reads an embedded array from the stream.
         *
         * @param fin The input stream to read from.
         * @return Array The parsed array instance.
         */
        Array readArray( std::istream& fin );
      };

    } // namespace io
  } // namespace bson
} // namespace uma

#endif // UMA_BSON_IO_READER_H
