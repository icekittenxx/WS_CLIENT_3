#ifndef UMA_BSON_DOCUMENT_H
#define UMA_BSON_DOCUMENT_H

#include <uma/bson/Object.h>
#include <uma/bson/Element.h>
#include <uma/bson/ObjectId.h>

#include <Poco/Exception.h>
#include <Poco/HashMap.h>
#include <Poco/SharedPtr.h>

#include <iostream>
#include <map>


namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Document
     *
     * \brief A class that represents a BSON Object.
     *
     * Documents may be top level objects, or sub-objects of a document.
     * All the data in this class is contained in a shared pointer, hence
     * this class may be passed by value without significant overhead.
     * This also makes it easier to work with embedded documents that are
     * retrieved as element values. To properly clone/copy an array use
     * the {@link #clone} method.
     *
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \date Created 2012/09/06 18:59
     * \author Rakesh
     * \version $Id: Document.h 203 2013-02-15 12:23:15Z spt $
     */
    class UMA_BSON_API Document : public Object
    {
    public:
      /// The special ObjectId element/field name as used by MongoDB
      const static std::string OBJECT_ID;

      /**
       * @brief Default constructor for creating new documents.
       *
       * Use to create an new document that will be populated by subsequent
       * invocations of the * {@link #set} method.  The constructor adds
       * a new {@link ObjectId} field with the special element name {@link #OBJECT_ID}.
       *
       * @param oid The object id to use for the new document, or a default
       *   constructed object id.
       */
      Document( const ObjectId& oid = ObjectId() ) :
        pimpl( new DocumentImpl( oid ) ) {}

      /**
       * @brief Create an empty document without a default assigned
       * {@link #OBJECT_ID} field.
       *
       * @return The new empty document.
       */
      static Document emptyDocument() { return Document( 0 ); }

      /**
       * @brief Create a new document instance with the contents of the
       * BSON file at specified path.
       *
       * @param filePath The fully qualified name of the file to read.
       * @return The document object representing the BSON data.
       */
      static Document fromFile( const std::string& filePath );

      /**
       * @brief Create a new document instance with the contents of the
       * \c char array.  Can be used to create document instances from
       * MongoDB C/C++ driver functions.
       *
       * @param bytes The char array containing the BSON data
       * @param length  The total length of the char array
       * @return The document object representing the BSON data.
       */
      static Document fromBytes( const char* bytes, const int32_t length );

      /**
       * @brief  Create a new document instance with the contents read
       * from the specified stream.  Usually used to read the BSON
       * data over a network.
       *
       * @param is The input stream to read the BSON data from
       * @return The document object representing the BSON data.
       */
      static Document fromStream( std::istream& is );

      /**
       * @brief  Create a new document instance with the JSON data
       * from the specified stream.
       *
       * @param is The input stream to read the JSON data from
       * @return The document object representing the BSON data.
       */
      static Document fromJson( std::istream& is );

      /**
       * @brief Check to see if the document has any elements.
       *
       * @return Return \c true is there are no elements.
       */
      bool isEmpty() const { return pimpl->isEmpty(); }

      /// Constant iterator for iterating over the elements in document
      typedef std::vector<Element>::const_iterator ConstantIterator;

      /**
       * @brief Return a constant iterator to the first element in the container
       * that stores the elements in this document.
       *
       * @since 2.0
       * @return The iterator to the first entry in container.
       */
      ConstantIterator begin() const { return pimpl->begin(); }

      /**
       * @brief Returns a constant iterator to the end of the container
       * that stores the elements in this document.
       *
       * @since 2.0
       * @return The iterator to the end of the container.
       */
      ConstantIterator end() const { return pimpl->end(); }

      const FieldNames getFieldNames() const { return pimpl->getFieldNames(); }

      /**
       * @brief Check to see if a element/field with specified name
       * exists.  Note that the check is non-recursive, and hence the
       * name specified must be simple and not dot separated.
       *
       * @param name The name of the element/field to check for existence
       * @return Returns \c true if an element exists.
       */
      bool hasElement( const std::string& name ) const
      {
        return pimpl->hasElement( name );
      }

      /**
       * @brief Create an empty element of specified type and return a
       * reference to the newly created element.
       *
       * Use this method to create an element of a specific data type and
       * then populate the value for the newly created element.  This
       * will avoid a copy-construction of the value instance when setting
       * an element value.
       *
       * @warning Note that if an element exists with the specified name,
       * a reference to the existing element is returned, regardless of
       * the data type held in that element.
       *
       * @tparam DataType The type of value to be stored in the element.
       * @since Version 2.4
       * @param name The name of the element to retrieve.
       * @return The element with the specified name
       * @throw Poco::NotFoundException If no element with specified name
       *   exists.
       */
      template <typename DataType>
      Element& create( const std::string& name )
      {
        if ( ! hasElement( name ) )
        {
          set( Element::createElement( name, new DataType() ) );
        }

        return get( name );
      }

      /**
       * @brief Return the element with the specified name as a constant
       * reference.
       *
       * @param name The name of the element to retrieve.
       * @return The element with the specified name
       * @throw Poco::NotFoundException If no element with specified name
       *   exists.
       */
      const Element& get( const std::string& name ) const
      {
        return pimpl->get( name );
      }

      /**
       * @brief Return the element with the specified name as a reference.
       *
       * @param name The name of the element to retrieve.
       * @return The element with the specified name
       * @throw Poco::NotFoundException If no element with specified name
       *   exists.
       */
      Element& get( const std::string& name ) { return pimpl->get( name ); }

      /** @brief Retrieve the element with specified name.
       *
       * Similar to a \c std::map if no element with the specified name
       * exists, a new element with the specified name is added to the
       * document.  The element will be assigned a value type \c undefined.
       *
       * @since Version 2.2
       * @param name The name of the element to retrieve.
       * @return The element with the specified name
       */
      Element& operator [] ( const std::string& name );

      /// Alias for {@link #get( const std::string& )}
      const Element& operator [] ( const std::string& name ) const { return get( name ); }

      Value& getValue( const std::string& name )
      {
        return get( name ).getValue<Value>();
      }

      /**
       * @brief Check to see if a element/field with specified name
       * exists in embedded objects/arrays in the document.  The nested
       * field name specified must use the dot notation supported by
       * MongoDB.
       *
       * @param name The name of the element/field to check for existence
       * @return Returns \c true if an element exists.
       * @throw Poco::Exception Exceptions may be thrown if the name specified
       *   does not properly follow the document structure.  For instance
       *   if a nested element is an array, and the subsequent element
       *   name specified is not of type numeric, and exception will be
       *   thrown.
       */
      bool hasNestedElement( const std::string& name ) const
      {
        return pimpl->hasNestedElement( name );
      }

      /**
       * @brief Return the nested element from the BSON document.
       *
       * The element
       * name should be specified using the dot notation supported by
       * MongoDB.  Note that array type sub-objects will be traversed
       * by the index number element name.
       *
       * \param name The fully qualified (eg. field1.field2.3.field3)
       *   name of the embedded element
       * \return The requested embedded element.
       * @throw Poco::NotFoundException If the specified nested element
       *   is not found.
       * @throw Poco::Exception Other Exceptions may be thrown if the name
       *   does not properly follow the document structure.  For instance
       *   if a nested element is an array, and the subsequent element
       *   name specified is not of type numeric, and exception will be
       *   thrown.
       */
      const Element& getNestedElement( const std::string& name ) const
      {
        return pimpl->getNestedElement( name );
      }

      /**
       * @brief Add the specified element to this document.
       *
       * Replaces any existing element which has the same name as the
       * specified element.
       *
       * @warning If the name of the element is \c _id, it will be
       * inserted at index \c 0 regardless of the value of \c index
       * specified.
       *
       * @param value The new element to add to this document.
       * @param index The optional index at which the new element is to
       *   be inserted.  This may be used to provide clients control over
       *   the order of the elements in this document.
       * @return This instance for method chaining.
       */
      Document& set( const Element& value, const int32_t index = -1 )
      {
        pimpl->set( value, index );
        return *this;
      }

      /// Alias for {@link #set( uma::bson::Element&, int32_t )}
      Document& operator << ( const Element& value ) { return set( value ); }

      /**
       * @brief Adds a new element with the specified name and value to
       * this document.
       *
       * If an element already exists with the specified name, it is
       * replaced.  The optional \c index parameter may be used to
       * control the ordering of the elements in this document.
       *
       * @tparam DataType The type of value to be stored in the element.
       * @param name The name of the element to be added.
       * @param value The value for the new element.
       * @param index The optional index at which to insert the element.
       * @return This instance for method chaining
       */
      template <typename DataType>
      Document& set( const std::string& name, const DataType& value,
          const int32_t index = -1 )
      {
        return set( Element( name, value ), index );
      }

      void setValue( const std::string& name, const Value& value );

      /**
       * @brief Return the object identity field for this document.
       *
       * @warning A new object identity will be generated and assigned
       * to this document if one does not yet exist.
       *
       * @return The object id for this document.
       */
      const ObjectId& getObjectId() { return pimpl->getObjectId(); }

      /**
       * @brief Set the \c _id field that holds the object identity for
       * the document.
       *
       * @param oid The object id for the document.
       * @return This instance for method chaining
       */
      Document& setObjectId( const ObjectId& oid = ObjectId() )
      {
        pimpl->setObjectId( oid );
        return *this;
      }

      /**
       * @brief Remove the element with the specified name from this
       * document.
       *
       * @warning Note that only top-level elements may be removed using this
       * method.  Nested elements are not processed.
       *
       * @param name The name of the element to remove.
       * @return A copy of the element that was removed.
       * @throw Poco::NotFoundException If an element with specified name
       *   does not exist in this document.
       */
      Element remove( const std::string& name ) { return pimpl->remove( name ); }

      /**
       * @brief Return the total number of top-level elements in the document.
       *
       * @return The number of top-level elements.
       */
      size_t size() const { return pimpl->size(); }

      void toBson( std::ostream& os ) const;

      /**
       * @brief Generate a JSON representation of the data in the
       * document.
       *
       * Note that the JSON generated is based closely upon the BSON
       * specification and is not in a "natural" JSON format.  The
       * format was chosen to make it easy to re-parse the JSON back
       * into a document.
       *
       * @param os The output stream to serialise the JSON data to.
       * @param prettyPrint Indicate whether the output should contain
       *   indentation and line breaks for readability.
       */
      void toJson( std::ostream& os, bool prettyPrint = false ) const;

      /**
       * @brief Clone the contents of this document.
       *
       * This is the recommended way to copy a document.  The default
       * copy constructor and assignment operator return document instances
       * that share the internal data.  This method returns a document
       * instance with the equivalent but different instances of the
       * internal data.
       *
       * @warning This method has not been optimised.  The current
       * implementation serialises the document to a BSON stream, and
       * then de-serialises the BSON stream into a new document instance.
       *
       * @since 1.3
       * @return A document instance with all the internal data duplicated.
       */
      Document clone() const;

      /**
       * @brief Compare two documents for equivalence.
       *
       * Documents are considered equivalent if they
       * have the same elements even though the ordering of elements is
       * different.  The \c == operator performs the true equality check,
       * which this method performs equivalence check.
       *
       * @warning This method performs a true deep comparison and may be
       * quite heavy weight depending upon the data in the documents being
       * compared.
       *
       * @since 2.1
       * @param doc The document to compare for equivalence.
       * @return Return \c true if the specified document is equivalent
       *   to this instance.
       */
      bool isEquivalentTo( const Document& doc ) const;

      /**
       * @brief The size is bytes of the BSON representation of the document.
       *
       * @return The size of the bson data array
       */
      int32_t getSize() const { return pimpl->getSize(); }

    private:
      Document( const int /* size */ ) : pimpl( new DocumentImpl ) {}

      void populate( std::istream& /* is */ )
      {
        throw Poco::NotImplementedException();
      }

    private:
      class DocumentImpl
      {
      public:
        DocumentImpl() {}

        DocumentImpl( const ObjectId& oid )
        {
          setObjectId( oid );
        }

        bool isEmpty() const { return fields.empty(); }

        Document::ConstantIterator begin() const { return fields.begin(); }
        Document::ConstantIterator end() const { return fields.end(); }

        const Document::FieldNames getFieldNames() const;

        bool hasElement( const std::string& name ) const
        {
          return ( names.find( name ) != names.end() );
        }

        const ObjectId& getObjectId();

        void setObjectId( const ObjectId& oid = ObjectId() )
        {
          set( Element( OBJECT_ID, oid ), 0 );
        }

        Element& get( const std::string& name );
        const Element& get( const std::string& name ) const;

        bool hasNestedElement( const std::string& name ) const;
        const Element& getNestedElement( const std::string& name ) const;

        void set( const Element& value, const int32_t index = -1 );

        Element remove( const std::string& name );

        size_t size() const { return fields.size(); }

        int32_t getSize() const;

      private:
        void insert( const Element& value, const int32_t index );
        void update( const Element& value, const int32_t index );
        void updateIndices();

      private:
        typedef std::vector<Element> Vector;
        Vector fields;

        typedef Poco::HashMap<std::string,std::size_t> NameMap;
        NameMap names;
      };

      typedef Poco::SharedPtr<DocumentImpl> PimplPtr;
      PimplPtr pimpl;
    };

    /**
     * @brief Specialisation of the \c set method for double value.
     *
     * @param name The name of the element
     * @param value The double value for the element
     * @param index The optional index to insert the element at.
     * @return This instance for method chaining.
     */
    template <>
    inline Document& Document::set( const std::string& name,
        const double& value, const int32_t index )
    {
      Element e( name, value );
      return set( e, index );
    }

    /**
     * @brief Specialisation of the \c set method for a string value.
     *
     * @param name The name of the element
     * @param value The string value for the element
     * @param index The optional index to insert the element at.
     * @return This instance for method chaining.
     */
    template <>
    inline Document& Document::set( const std::string& name,
        const std::string& value, const int32_t index )
    {
      Element e( name, value );
      return set( e, index );
    }

    /**
     * @brief Specialisation of the \c set method for a boolean value.
     *
     * @param name The name of the element
     * @param value The boolean value for the element
     * @param index The optional index to insert the element at.
     * @return This instance for method chaining.
     */
    template <>
    inline Document& Document::set( const std::string& name,
        const bool& value, const int32_t index )
    {
      Element e( name, value );
      return set( e, index );
    }

    /**
     * @brief Specialisation of the \c set method for an integer value.
     *
     * @param name The name of the element
     * @param value The integer value for the element
     * @param index The optional index to insert the element at.
     * @return This instance for method chaining.
     */
    template <>
    inline Document& Document::set( const std::string& name,
        const int32_t& value, const int32_t index )
    {
      Element e( name, value );
      return set( e, index );
    }

    /**
     * @brief Specialisation of the \c set method for a long value.
     *
     * @param name The name of the element
     * @param value The long value for the element
     * @param index The optional index to insert the element at.
     * @return This instance for method chaining.
     */
    template <>
    inline Document& Document::set( const std::string& name,
        const int64_t& value, const int32_t index )
    {
      Element e( name, value );
      return set( e, index );
    }

    /**
     * @brief Compare two documents for equality.
     *
     * Ensures that both documents have same number of elements, and
     * compares each element for equality.  Documents are considered
     * equal only if they have equivalent elements at the same positions
     * (index) within the document, or which have the same ordering of
     * elements.
     *
     * @warning This method performs a true deep comparison and may be
     * quite heavy weight depending upon the data in the documents being
     * compared.
     *
     * @since 2.0
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true if the two instances are equal.
     */
    UMA_BSON_API bool operator == ( const Document& lhs, const Document& rhs );

    /// Just the reverse of operator ==
    inline bool operator != ( const Document& lhs, const Document& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_DOCUMENT_H
