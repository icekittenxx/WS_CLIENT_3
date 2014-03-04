#ifndef UMA_BSON_DATABASEREFERENCE_H
#define UMA_BSON_DATABASEREFERENCE_H

#include <uma/bson/Value.h>
#include <uma/bson/ObjectId.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::DatabaseReference
     *
     * \brief A POD that represents a database reference type BSON element value. *
     * \date Created 2012/09/09 21:44
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: DatabaseReference.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API DatabaseReference : public Value
    {
    public:
      /// Default CTOR
      DatabaseReference() {}

      /**
       * @brief Create a new instance with the specified collection
       * name and OID value.
       *
       * @param col The collection (full namespace for the database
       *   and collection) name that the document being referenced
       *   resides in.
       * @param id The object id of the referenced document.
       */
      DatabaseReference( const std::string& col, const ObjectId& id ) :
        collection( col ), oid( id ) {}

      /**
       * @brief Returns the name of the collection stored in this
       * instance as a constant reference.
       *
       * @return The collection name.
       */
      const std::string& getCollection() const { return collection; }

      /**
       * @brief Returns the name of the collection stored in this
       * instance as a non-constant reference.
       *
       * @return The collection name.
       */
      std::string& getCollection() { return collection; }

      /**
       * @brief Sets the value of the collection name encapsulated in
       * this instance.
       *
       * @param col The new collection name value
       * @return This instance for method chaining.
       */
      DatabaseReference& setCollection( const std::string& col )
      {
        collection = col;
        return *this;
      }

      /**
       * @brief Return the object id of the referenced document as a
       * constant reference
       *
       * @return The OID value
       */
      const ObjectId& getOID() const { return oid; }

      /**
       * @brief Return the object id of the referenced document as a
       * non-constant reference
       *
       * @return The OID value
       */
      ObjectId& getOID() { return oid; }

      /**
       * @brief Sets the object id of the referenced document
       *
       * @param id The new object id to encapsulate
       * @return This instance for method chaining.
       */
      DatabaseReference& setOID( const ObjectId& id )
      {
        oid = id;
        return *this;
      }

      /**
       * @brief Returns a string representation of a database reference
       * for logging/debugging purposes.
       *
       * @return The textual representation
       */
      const std::string toString() const
      {
        std::stringstream ss;
        ss << "{ \"$ref\" : \"" << collection <<
              "\", \"$id\" : \"" << oid.toString() << "\" }";
        return ss.str();
      }

      /**
       * @brief Returns the size in bytes the BSON representation of
       * this instance occupies.
       *
       * @return The size in bytes of the BSON data
       */
      int32_t getSize() const { return static_cast<int32_t>( collection.size() + 1 + 12 ); }

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::DbRef
       */
      Value::Type getType() const { return Value::DbRef; }

    private:
      std::string collection;
      ObjectId oid;
    };

    /**
     * @brief Compare two database references for equality.  Compares
     * the names of the collections and the object id values.
     *
     * @since 2.0
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true if the two instances are equivalent.
     */
    inline bool operator == (
        const DatabaseReference& lhs, const DatabaseReference& rhs )
    {
      return ( ( lhs.getCollection() == rhs.getCollection() ) &&
          ( lhs.getOID() == rhs.getOID() ) );
    }

    /// Just the reverse of operator ==
    inline bool operator != (
        const DatabaseReference& lhs, const DatabaseReference& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_DATABASEREFERENCE_H
