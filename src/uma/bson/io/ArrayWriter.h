#ifndef UMA_BSON_IO_ARRAYWRITER_H
#define UMA_BSON_IO_ARRAYWRITER_H

#include <uma/bson/io/Writer.h>

namespace uma
{
  namespace bson
  {
    namespace io
    {
      /**
       * \class uma::bson::io::ArrayWriter
       *
       * \brief A serialiser that writes the BSON representation of an
       * array to a output stream.
       *
       * \date Created 2012/10/02 19:12
       * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
       * \author Rakesh
       * \version $Id: ArrayWriter.h 167 2012-12-13 22:11:47Z spt $
       */
      class ArrayWriter : private Writer
      {
      public:
        /**
         * @brief Create a new array writer instance for serialising
         * the specified array instance to the specified output stream.
         *
         * @param arr The array to serialise as BSON
         * @param os The stream to serialise the BSON data to
         */
        ArrayWriter( const Array& arr, std::ostream& os );

        /**
         * @brief Serialise the document to the output stream.
         */
        void write();

      private:
        const Array& array;
      };

    } // namespace io
  } // namespace bson
} // namespace uma

#endif // UMA_BSON_IO_ARRAYWRITER_H
