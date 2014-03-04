#ifndef UMA_BSON_IO_ARRAYJSONREADER_H
#define UMA_BSON_IO_ARRAYJSONREADER_H

#include <uma/bson/io/JsonReader.h>

namespace uma
{
  namespace bson
  {
    namespace io
    {
      /**
       * @class uma::bson::io::ArrayJsonReader
       *
       * @brief A parser for transforming a JSON serialised BSON array
       * into an {@link uma::bson::Array} object representation
       *
       * Note that this parser will process only JSON data that was
       * created in the format created by {@link JsonWriter}.
       *
       * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
       * \date Created 2012/09/30 06:45
       * \author Rakesh
       * \version $Id: ArrayJsonReader.h 167 2012-12-13 22:11:47Z spt $
       */
      class ArrayJsonReader : private JsonReader
      {
      public:
        /**
         * @brief Parses the contents of the file at the path specified
         * into an array instance.
         *
         * @param filePath The fully qualified path to the JSON file.
         * @return Document The array instance that represents the
         *   JSON data in the file.
         */
        Array parse( const std::string& filePath );

        /**
         * @brief Reads a JSON representation of a BSON array from the
         * stream.
         *
         * @param fin The input stream to read from.
         * @return Array The parsed array instance.
         */
        Array parse( std::istream& fin );
      };

    } // namespace io
  } // namespace bson
} // namespace uma

#endif // UMA_BSON_IO_ARRAYJSONREADER_H
