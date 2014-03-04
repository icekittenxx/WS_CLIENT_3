#ifndef UMA_BSON_OBJECT_H
#define UMA_BSON_OBJECT_H

#include <uma/bson/Value.h>

#include <Poco/Exception.h>

#include <vector>

namespace uma
{
  namespace bson
  {
    /**
     * @brief Abstract base class that represents a BSON Object type.
     *
     * The primary purpose of this indirection is to allow client API to
     * model BSON object instances as regular POD types.  By implementing
     * the methods in this abstract interface these classes automatically
     * get support for serialisation to and from BSON.
     *
     * @since Version 2.2
     * \date Created 2012/12/17 19:30
     * \author Rakesh
     * \version $Id: Object.h 192 2012-12-23 22:51:30Z spt $
     */
    class UMA_BSON_API Object : public Value
    {
    public:
      /// Virtual destructor for sub-classes.
      virtual ~Object() {}

      /// A container for the top-level fields in an object.
      typedef std::vector<std::string> FieldNames;

      /// Iterator for iterating over the top-level field names in an object.
      typedef FieldNames::const_iterator FieldsIterator;

      /**
       * @brief Return a vector of all the element names (top-level only)
       * in this object.
       *
       * @return The vector of element names.
       */
      virtual const FieldNames getFieldNames() const = 0;

      /**
       * @brief Return the value for the element with the specified name.
       *
       * This method is primarily intended to provide rudimentary ODM
       * (object-document mapping) capabilities in the API.  Model objects
       * that extend this class and store fields as {@link Value} types
       * may be serialised to BSON seamlessly.  See unit test suite for
       * a simple custom model object that is serialised to BSON.
       *
       * @since Version 2.2
       * @param name The name of the BSON element
       * @return The value for the element.
       * @throw Poco::NotFoundException If no element with specified name exists.
       */
      virtual Value& getValue( const std::string& name ) = 0;

      /// Constant version of getValue method.
      virtual const Value& getValue( const std::string& name ) const
      {
        return const_cast<Object*>( this )->getValue( name );
      }

      /**
       * @brief Return an empty instance of an object implementation that
       * represents the type of data stored in an array type field.
       *
       * Array type fields are used to represent data stored in container
       * classes in the class.  This method is used primarily when
       * de-serialising an object instance from its BSON representation.
       * If the object being de-serialised contains array type data,
       * this method will be used to determine the type of values stored
       * in the array.
       *
       * Note that container fields that store simple types (literally
       * all types of values except Value::Type::Object) will in general
       * not need any special support or this method to be implemented.
       *
       * Note that the default implementation just throws an exception.
       * This is done to avoid having to make this method a pure-virtual
       * method.  Not all model objects will need to store collections
       * of values, and hence only objects that need to support collections
       * need implement this method.
       *
       * The calling method implemented in this API will populate
       * the instance returned with the BSON data and save in an
       * {@link uma::bson::Element}.  The element instance takes ownership
       * of the memory allocated for the instance returned.  Implementations
       * must not \c delete the instance returned.
       *
       * @param name The name of the array type field.
       * @return A new empty object instance that will be populated
       *   and stored in an {@link uma::bson::Array}.
       */
      virtual Object* getObjectForArray( const std::string& /* name */ )
      {
        throw Poco::NotImplementedException();
      }

      /**
       * @brief Set the value for the element with the specified name.
       *
       * This method is also used to provide rudimentary ODM capabilities
       * in the API.  Model objects that extend this class and store fields
       * as {@link Value} types may be deserialised from BSON through
       * this method.  See unit test suite for a simple custom model
       * object that is de-serialised from BSON.
       *
       * Note that from Version 2.3 onwards a default implementation is
       * provided.  The default implementation handles setting the value
       * for all the simple types.  In particular \c Value::Type::Object,
       * \c Value::Type::Array and consequently \c Value::Type::CodeWScope
       * are not handled and may throw an exception.  Despite this clients
       * may still not need to provide an implementation of this method
       * even if they store other object and array fields.  The BSON
       * deserialiser implemented in this API retrieves a reference to the
       * current object/array from the destination instance and populates
       * those.  Hence if the only code using this method is from the
       * internal BSON deserialiser, there will be no need to provide
       * additional implementation for setting object/array fields.
       *
       * @since Version 2.2
       * @param name
       * @param value
       * @throw Poco::InvalidArgumentException Will be thrown if the
       *   specified value type does not match the existing value type.
       *   May also be throw since this method invokes {@link #getValue( const std::string& )}
       *   at the beginning to fetch the current instance that is to be
       *   modified.
       * @throw Poco::NotImplementedException If the value specified is a
       *   complex type such as \c Value::Type::Object or \c Value::Type::Array.
       */
      virtual void setValue( const std::string& name, const Value& value );

      /**
       * @brief Serialise the data in this object in BSON format to
       * the specified output stream.
       *
       * The default implementation uses {@link uma::bson::io::ObjectWriter}
       * to serialise the fields returned by {@link #getFieldNames} to
       * the stream.
       *
       * @param os The output stream to serialise the BSON data to.
       */
      virtual void toBson( std::ostream& os ) const;

      /**
       * @brief Populate the fields in this object from the BSON data
       * stream.  Complementary method to {@link #toBson}.
       *
       * @param is The BSON data stream from which this object instance
       *   is to be populated.
       * @throw Poco::InvalidArgumentException If the bson data contains
       *   elements that do not match the fields in this class.
       */
      virtual void populate( std::istream& is );

      int32_t getSize() const;

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value::Type}::Object
       */
      Value::Type getType() const { return Value::Object; }
    };

    /**
     * @brief Compare two objects for equality.
     *
     * Ensures that both objects have same number of elements, and
     * compares each element for equality.  Objects are considered
     * equal only if they have equivalent elements at the same positions
     * (index) within the object, or which have the same ordering of
     * elements.
     *
     * @warning This method performs a true deep comparison and may be
     * quite heavy weight depending upon the data in the documents being
     * compared.
     *
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true if the two instances are equal.
     */
    UMA_BSON_API bool operator == ( const Object& lhs, const Object& rhs );

    /// Just the reverse of operator ==
    inline bool operator != ( const Object& lhs, const Object& rhs )
    {
      return ! ( lhs == rhs );
    }
  }
}

#endif // UMA_BSON_OBJECT_H
