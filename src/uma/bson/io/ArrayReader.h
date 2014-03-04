#ifndef UMA_BSON_IO_ARRAYREADER_H
#define UMA_BSON_IO_ARRAYREADER_H

#include <uma/bson/io/Reader.h>

namespace uma
{
  namespace bson
  {
    namespace io
    {
      /**
       * \class uma::bson::io::ArrayReader
       *
       * \brief A streaming parser that parses a stream of BSON bytes from an
       * input stream and transforms into a {@link uma::bson::Array} model.
       *
       * \date Created 2012/10/02 19:46
       * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
       * \author Rakesh
       * \version $Id: ArrayReader.h 167 2012-12-13 22:11:47Z spt $
       */
      class ArrayReader : private Reader
      {
      public:
        /**
         * @brief Parses the contents of the file at the path specified
         * into a array instance.
         *
         * @param filePath The fully qualified path to the BSON file.
         * @return Array The array instance that represents the
         *   BSON data in the file.
         */
        Array parse( const std::string& filePath );

        /**
         * @brief Parses the BSON data bytes from the specified input
         * stream into a array.
         *
         * @param fin The input stream (file or network) from which the
         *   BSON data is to be read.
         * @return Array The array instance that represents the
         *   BSON data from the stream.
         */
        Array parse( std::istream& fin );
      };
    } // namespace io
  } // namespace bson
} // namespace uma

#endif // UMA_BSON_IO_ARRAYREADER_H
