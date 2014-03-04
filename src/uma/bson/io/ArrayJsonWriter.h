#ifndef UMA_BSON_IO_ARRAYJSONWRITER_H
#define UMA_BSON_IO_ARRAYJSONWRITER_H

#include <uma/bson/io/JsonWriter.h>

namespace uma
{
  namespace bson
  {
    namespace io
    {
      /**
       * \class uma::bson::io::ArrayJsonWriter
       *
       * \brief A streaming writer that transforms a {@link uma::bson::Array}
       * to a JSON representation.
       *
       * \date Created 2012/09/24 13:18
       * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
       * \author Rakesh
       * \version $Id: ArrayJsonWriter.h 167 2012-12-13 22:11:47Z spt $
       */
      class ArrayJsonWriter : private JsonWriter
      {
      public:
        /**
         * @brief Create a new instance of the writer used to serialise
         * the specified array as JSON data to the specified output
         * stream.
         *
         * @param arr The array to serialise as JSON
         * @param os The output stream to serialise to.
         * @param prettyPrint Indicate whether the JSON output should
         *   contain indentation and new lines.  Defaults to \c false
         *   which produces compact (non-pretty) output.
         */
        ArrayJsonWriter( const Array& arr,
            std::ostream& os, bool prettyPrint = false );

        /**
         * @brief Serialise the array to the output stream.
         */
        void write();

      private:
        const Array& array;
      };

    } // namespace io
  } // namespace bson
} // namespace uma

#endif // UMA_BSON_IO_ARRAYJSONWRITER_H
