#ifndef UMA_BSON_IO_OBJECTWRITER_H
#define UMA_BSON_IO_OBJECTWRITER_H

#include <uma/bson/io/Writer.h>
#include <uma/bson/Object.h>

namespace uma
{
  namespace bson
  {
    namespace io
    {
      /**
       * \class uma::bson::io::ObjectWriter
       *
       * A base streaming writer class that transforms the data in a bson
       * object into a BSON representation and writes it to an output stream.
       *
       * @since Version 2.2
       * \date Created 2012/12/18 07:25
       * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
       * \author Rakesh
       * \version $Id: ObjectWriter.h 181 2012-12-21 01:08:58Z spt $
       */
      class UMA_BSON_API ObjectWriter : public Writer
      {
      public:
        /**
         * @brief Create a new instance of the writer to serialise the
         * specified object to the output stream.
         *
         * @param obj The object to serialise
         * @param os The output stream to write to.
         */
        ObjectWriter( const uma::bson::Object& obj, std::ostream& os );

        /// Virtual destructor for sub-classes
        virtual ~ObjectWriter() {}

        /**
         * @brief Serialise the object instance to the output stream.
         * Sub-classes may re-implement to customise serialisation of
         * custom model objects.
         */
        virtual void write();

      protected:
        using Writer::write;

        /**
         * @brief Return the object that is being serialised using this
         * instance.
         *
         * @return The object that is being serialised using this writer.
         */
        const uma::bson::Object& getObject() const { return object; }

        /**
         * @brief Serialises a BSON object implementation to the output
         * stream.  This method is used primarily for serialising
         * sub-classes of {@link uma::bson::Object} which implement simple object
         * models.  Default {@link uma::bson::Document} instances are serialised
         * using the more specialised {@link #write( const uma::bson::Document& )}
         * method.
         *
         * @param obj The object to serialise to BSON.
         */
        virtual void write( const Object& obj );

        void write( const Array& arr );

      private:
        const uma::bson::Object& object;
      };

    } // namespace io
  } // namespace bson
} // namespace uma

#endif // UMA_BSON_IO_OBJECTWRITER_H
