#ifndef UMA_BSON_IO_JSONWRITER_H
#define UMA_BSON_IO_JSONWRITER_H

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
       * \class uma::bson::io::JsonWriter
       *
       * \brief A streaming writer that transforms an object model into a
       * JSON representation.
       *
       * The JSON representation is modelled upon the BSON specification
       * and does not follow a "natural" JSON representation.  This
       * is done to make it easy to parse a JSON representation back into
       * a {@link uma::bson::Document} or {@link uma::bson::Array}
       * representation by the API easy.
       *
       * \date Created 2012/09/24 13:15
       * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
       * \author Rakesh
       * \version $Id: JsonWriter.h 167 2012-12-13 22:11:47Z spt $
       */
      class JsonWriter
      {
      public:
        /// Virtual destructor for sub-classes
        virtual ~JsonWriter() {}

      protected:
        /**
         * @brief Create a new instance of the writer that will write to
         * the specified output stream.
         *
         * The \c prettyPrint parameter is used to indicate whether the
         * output should contain indentation and line-breaks (primarily
         * for human consumption) or not.
         *
         * @param os The output stream to write the JSON representation to
         * @param pretty Whether the output should contain line breaks and
         *   indentation (\c true).
         */
        JsonWriter( std::ostream& os, bool pretty ) :
          stream( os ), indent( 0 ), prettyPrint( pretty ),
          outputElementName( true ) {}

        /**
         * @brief Return the output stream for use from sub-classes.
         *
         * @return std::ostream The output stream to which the JSON
         *   output is being written.
         */
        std::ostream& getStream() { return stream; }

        /**
         * @brief Writes a string value to the JSON stream after escaping
         * special characters.  At present only escapes double quotes.
         *
         * @param value The string value to be written
         */
        void write( const std::string& value );

        /**
         * @brief Serialises an empty element JSON representation.
         *
         * Empty elements are elements with any of the following
         * value types:
         * \li {@link uma::bson::Value}::Type::Eoo
         * \li {@link uma::bson::Value}::Type::Undefined
         * \li {@link uma::bson::Value}::Type::Null
         *
         * @param element The element that is to be serialised as JSON
         * @param index The index of the element in the document/array.
         */
        void writeEmpty( const Element& element, const int32_t index );

        /**
         * @brief Serialises an element that holds a \c double value as JSON.
         *
         * @param element The element of type {@link uma::bson::Value}::Type::Double
         * @param index The index of the element in the document/array.
         */
        void writeDouble( const Element& element, const int32_t index );

        /**
         * @brief Serialises an element that holds a \c std::string value
         * as JSON.
         *
         * @param element The element of type {@link uma::bson::Value}::Type::String
         * @param index The index of the element in the document/array.
         */
        void writeString( const Element& element, const int32_t index );

        /**
         * @brief Writes an element that holds an embedded document as
         * JSON
         *
         * Writes meta data about the element, bson size and data type
         * and delegates to {@link #write( Document )} to serialise the
         * embedded document.
         *
         * @param element The element of type {@link uma::bson::Value}::Type::Object
         * @param index The index of the element in the document/array.
         */
        void writeDocument( const Element& element, const int32_t index );

        /**
         * @brief Serialises an element that holds an embedded array as JSON
         *
         * Writes meta data about the element, bson size and data type
         * and delegates to {@link #write( Array )} to serialise the
         * embedded array.
         *
         * @param element The element of type {@link uma::bson::Value}::Type::Array
         * @param index The index of the element in the document/array.
         */
        void writeArray( const Element& element, const int32_t index );

        /**
         * @brief Serialises an element that holds embedded binary data.
         *
         * The binary data is serialised as a \c base64 encoded stream
         * of characters.
         *
         * @param element The element of type {@link uma::bson::Value}::Type::BinData
         * @param index The index of the element in the document/array.
         */
        void writeBinary( const Element& element, const int32_t index );

        /**
         * @brief Serialises a MongoDB OID element as JSON.
         *
         * Serialises a 24 character string representation of the object Id.
         *
         * @param element The element of type {@link uma::bson::Value}::Type::OID
         * @param index The index of the element in the document/array.
         */
        void writeOid( const Element& element, const int32_t index );

        /**
         * @brief Serialises a \c bool element as JSON
         *
         * @param element The element of type {@link uma::bson::Value}::Type::Boolean
         * @param index The index of the element in the document/array.
         */
        void writeBoolean( const Element& element, const int32_t index );

        /**
         * @brief Serialises a date-time type element as JSON
         *
         * Date-time values are serialised as an \c int64_t value that
         * represents the milliseconds since UNIX epoch time -
         * January 1, 1970
         *
         * @param element The element of type {@link uma::bson::Value}::Type::Date
         * @param index The index of the element in the document/array.
         */
        void writeDate( const Element& element, const int32_t index );

        /**
         * @brief Serialises a regular expression data type as JSON
         *
         * @param element The element of type {@link uma::bson::Value}::Type::RegEx
         * @param index The index of the element in the document/array.
         */
        void writeRegex( const Element& element, const int32_t index );

        /**
         * @brief Serialises a MongoDB database reference type element as JSON
         *
         * @param element The element of type {@link uma::bson::Value}::Type::DbRef
         * @param index The index of the element in the document/array.
         */
        void writeDbRef( const Element& element, const int32_t index );

        /**
         * @brief Serialises a code type element as JSON
         *
         * @param element The element of type {@link uma::bson::Value}::Type::Code
         * @param index The index of the element in the document/array.
         */
        void writeCode( const Element& element, const int32_t index );

        /**
         * @brief Serialises a programming language symbol type element as JSON
         *
         * @param element The element of type {@link uma::bson::Value}::Type::Symbol
         * @param index The index of the element in the document/array.
         */
        void writeSymbol( const Element& element, const int32_t index );

        /**
         * @brief Serialises a code segment with a BSON object scope as JSON
         *
         * @param element The element of type {@link uma::bson::Value}::Type::CodeWScope
         * @param index The index of the element in the document/array.
         */
        void writeCodeWScope( const Element& element, const int32_t index );

        /**
         * @brief Serialises a \c int32_t element as JSON
         *
         * @param element The element of type {@link uma::bson::Value}::Type::Integer
         * @param index The index of the element in the document/array.
         */
        void writeInt( const Element& element, const int32_t index );

        /**
         * @brief Serialises a MongoDB timestamp element as JSON
         *
         * Timestamp elements are represented by a \c int32_t increment
         * value and a \c std::time_t type date value.
         *
         * @param element The element of type {@link uma::bson::Value}::Type::Timestamp
         * @param index The index of the element in the document/array.
         */
        void writeTimestamp( const Element& element, const int32_t index );

        /**
         * @brief Serialises a \c int64_t element as JSON
         *
         * @param element The element of type {@link uma::bson::Value}::Type::Long
         * @param index The index of the element in the document/array.
         */
        void writeLong( const Element& element, const int32_t index );

        /**
         * @brief Serialises a element as JSON
         *
         * Determines the data type of the element and delegates to the
         * appropriate \c writeXxx method to serialise into JSON.
         *
         * @param element The element to be serialised
         * @param index The index of the element in the document/array.
         */
        void write( const Element& element, const int32_t index );

        /**
         * @brief Serialises a document instance as JSON
         *
         * @param element The document to be serialised.
         */
        void write( const Document& doc );

        /**
         * @brief Serialises an array element as JSON
         *
         * @param element The array to be serialised
         */
        void write( const Array& arr );

        /**
         * @brief If pretty print is enabled, writes appropriate number
         * of spaces to the output stream.
         */
        void writeIndent();

        /**
         * @brief If pretty print is enabled, writes an end of line
         * character to the output stream.
         */
        void writeEndLine();

      private:
        std::ostream& stream;
        int indent;
        bool prettyPrint;
        bool outputElementName;
      };

    } // namespace io
  } // namespace bson
} // namespace uma

#endif // UMA_BSON_IO_JSONWRITER_H
