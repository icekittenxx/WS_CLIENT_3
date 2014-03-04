#ifndef UMA_BSON_IO_OBJECTREADER_H
#define UMA_BSON_IO_OBJECTREADER_H

#include <uma/bson/io/Reader.h>
#include <uma/bson/Object.h>

namespace uma
{
  namespace bson
  {
    namespace io
    {

      class UMA_BSON_API ObjectReader : public Reader
      {
      public:
        /**
         * @brief Parses the contents of the file at the path specified
         * into the specified object instance.
         *
         * @param object The object instance whose fields are to be
         *   populated with the BSON data from the specified file.
         * @param filePath The fully qualified path to the BSON file.
         */
        virtual void parse( uma::bson::Object& object, const std::string& filePath );

        /**
         * @brief Parses the BSON data bytes from the specified input
         * stream into the specified object instance.
         *
         * @param object The object instance whose fields are to be
         *   populated with the BSON data from the specified file.
         * @param fin The input stream (file or network) from which the
         *   BSON data is to be read.
         */
        virtual void parse( uma::bson::Object& object, std::istream& fin );

      protected:
        void readObject( uma::bson::Object& object, std::istream& is );

        void readArray( uma::bson::Object& object, const std::string& name,
            uma::bson::Array& array, std::istream& fin );
      };

    } // namespace io
  } // namespace bson
} // namespace uma

#endif // UMA_BSON_IO_OBJECTREADER_H
