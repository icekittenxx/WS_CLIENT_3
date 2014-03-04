#ifndef UMA_BSON_IO_DOCUMENTJSONREADER_H
#define UMA_BSON_IO_DOCUMENTJSONREADER_H

#include <uma/bson/io/JsonReader.h>

namespace uma
{
  namespace bson
  {
    namespace io
    {
      /**
       * \class uma::bson::io::DocumentJsonReader
       *
       * \brief A parser that transforms a JSON stream into a
       * {@link uma::bson::Document}
       *
       * Note that this parser is designed to work with the JSON
       * output format produced through a {@link DocumentJsonWriter}.
       *
       * \date Created 2012/09/27 21:46
       * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
       * \author Rakesh
       * \version $Id: DocumentJsonReader.h 167 2012-12-13 22:11:47Z spt $
       */
      class DocumentJsonReader : private JsonReader
      {
      public:
        /**
         * @brief Parses the contents of the file at the path specified
         * into a document instance.
         *
         * @param filePath The fully qualified path to the JSON file.
         * @return Document The document instance that represents the
         *   JSON data in the file.
         */
        Document parse( const std::string& filePath );

        /**
         * @brief Parses the JSON data bytes from the specified input
         * stream into a document.
         *
         * @param fin The input stream (file or network) from which the
         *   JSON data is to be read.
         * @return Document The document instance that represents the
         *   JSON data from the stream.
         */
        Document parse( std::istream& fin );
      };

    } // namespace io
  } // namespace bson
} // namespace uma

#endif // UMA_BSON_IO_DOCUMENTJSONREADER_H
