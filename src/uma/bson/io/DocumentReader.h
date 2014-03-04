#ifndef UMA_BSON_DOCUMENTPARSER_H
#define UMA_BSON_DOCUMENTPARSER_H

#include <uma/bson/io/Reader.h>

namespace uma
{
  namespace bson
  {
    namespace io
    {
      /**
       * \class uma::bson::io::DocumentReader
       *
       * \brief A streaming parser that parses a stream of BSON bytes from an
       * input stream and transforms into a {@link uma::bson::Document} model.
       *
       * \date Created 2012/09/21 19:49
       * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
       * \author Rakesh
       * \version $Id: DocumentReader.h 167 2012-12-13 22:11:47Z spt $
       */
      class DocumentReader : private Reader
      {
      public:
        /**
         * @brief Parses the contents of the file at the path specified
         * into a document instance.
         *
         * @param filePath The fully qualified path to the BSON file.
         * @return Document The document instance that represents the
         *   BSON data in the file.
         */
        Document parse( const std::string& filePath );

        /**
         * @brief Parses the BSON data bytes from the specified input
         * stream into a document.
         *
         * @param fin The input stream (file or network) from which the
         *   BSON data is to be read.
         * @return Document The document instance that represents the
         *   BSON data from the stream.
         */
        Document parse( std::istream& fin );
      };
    }
  }
}

#endif // UMA_BSON_DOCUMENTPARSER_H
