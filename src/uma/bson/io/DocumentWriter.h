#ifndef UMA_BSON_DOCUMENTWRITER_H
#define UMA_BSON_DOCUMENTWRITER_H

#include <uma/bson/io/Writer.h>

namespace uma
{
  namespace bson
  {
    namespace io
    {
      /**
       * \class uma::bson::io::DocumentWriter
       *
       * \brief A serialiser that writes the BSON representation of a
       * document to an output stream.
       *
       * \date Created 2012/09/22 18:30
       * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
       * \author Rakesh
       * \version $Id: DocumentWriter.h 167 2012-12-13 22:11:47Z spt $
       */
      class DocumentWriter : private Writer
      {
      public:
        /**
         * @brief Create a new document writer instance for serialising
         * the specified document instance to the specified output stream.
         *
         * @param doc The document to serialise as BSON
         * @param os The stream to serialise the BSON data to
         */
        DocumentWriter( const Document& doc, std::ostream& os );

        /**
         * @brief Serialise the document to the output stream.
         */
        void write();

      private:
        const Document& document;
      };
    }
  }
}

#endif // UMA_BSON_DOCUMENTWRITER_H
