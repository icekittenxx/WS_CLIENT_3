#ifndef UMA_BSON_IO_JSONREADER_H
#define UMA_BSON_IO_JSONREADER_H

#include <uma/bson/Bson.h>
#include <Poco/Util/JSONObject.h>
#include <Poco/Util/JSONArray.h>
#include <iostream>

namespace uma
{
  namespace bson
  {
    namespace io
    {
      /**
       * \class uma::bson::io::JsonReader
       *
       * \brief A base streaming parser that parses a stream of
       * JSON bytes from an input stream and transforms into a object model.
       *
       * Note that this parser will process only JSON data that was
       * created in the format created by {@link JsonWriter}.
       *
       * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
       * \date Created 2012/09/27 21:54
       * \author Rakesh
       * \version $Id: JsonReader.h 167 2012-12-13 22:11:47Z spt $
       */
      class JsonReader
      {
      public:
        /// Virtual destructor for sub-classes
        virtual ~JsonReader() {}

      protected:
        /**
         * @brief Read a JSON object structure into a document.  Used
         * primarily to read embedded documents.
         *
         * @param object The embedded JSON object to read
         * @param document The document that is to be popuated
         * @return Document The passed in document reference
         */
        Document& read( Poco::Util::JSONObject::Ptr object, Document& document );

        /**
         * @brief Read a JSON array structure into a array.  Used
         * primarily to read embedded arrays.
         *
         * @param object The embedded JSON array to read
         * @return The parsed array instance.
         */
        Array read( Poco::Util::JSONArray::Ptr arrayPtr );

        /**
         * @brief Read a nested binary data object from the
         * current element.
         *
         * @param value The current element being processed
         * @return RegularExpression The encoded binary data
         */
        BinaryData readBinary( Poco::Util::JSONObject::Ptr value );

        /**
         * @brief Read a nested regular expression object from the
         * current element.
         *
         * @param value The current element being processed
         * @return RegularExpression The encoded regular expression
         */
        RegularExpression readRegex( Poco::Util::JSONObject::Ptr value );

        /**
         * @brief Read a nested database reference object from the
         * current element.
         *
         * @param value The current element being processed
         * @return RegularExpression The encoded database reference
         */
        DatabaseReference readDbRef( Poco::Util::JSONObject::Ptr value );

        /**
         * @brief Read a nested code with scope object from the
         * current element.
         *
         * @param value The current element being processed
         * @return RegularExpression The encoded code with scope
         */
        CodeWithScope readCodeWScope( Poco::Util::JSONObject::Ptr value );

        /**
         * @brief Read a nested timestamp object from the
         * current element.
         *
         * @param value The current element being processed
         * @return RegularExpression The encoded timestamp
         */
        Timestamp readTimestamp( Poco::Util::JSONObject::Ptr value );
      };

    } // namespace io
  } // namespace bson
} // namespace uma

#endif // UMA_BSON_IO_JSONREADER_H
