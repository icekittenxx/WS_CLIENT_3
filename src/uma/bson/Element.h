#ifndef UMA_BSON_ELEMENT_H
#define UMA_BSON_ELEMENT_H

#include <uma/bson/Value.h>

#include <Poco/Exception.h>
#include <Poco/SharedPtr.h>

#include <string>

namespace uma
{
  namespace bson
  {
    class ElementImpl;

    /**
     * \class uma::bson::Element
     *
     * \brief A class that represents a BSON element.  Stores the name-value
     * mapping for a BSON element in a PIMPL.  This enables efficient
     * copy-by-value semantics at the cost of shared data across the
     * various copies of the element.
     *
     * \date Created 2012/09/05 19:49
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Element.h 203 2013-02-15 12:23:15Z spt $
     */
    class UMA_BSON_API Element
    {
    public:
      /// Default CTOR
      Element() : pimpl( new ElementImpl ) {}

      /**
       * @brief Create a new element with the specified name and value.
       *
       * @tparam DataType The type of value to store in the element.
       * @param fieldName The field name for this element.
       * @param v The value for the element
       */
      template<typename DataType>
      Element( const std::string& fieldName, const DataType& v ) :
        pimpl( new ElementImpl( fieldName, new DataType( v ) ) ) {}

      /**
       * @brief Create a new element with the specified name and value.
       *
       * @warning Note that this element takes ownership of the specified
       * value instance.  Callers must not \c delete the passed in
       * value.
       *
       * @since Version 2.2
       * @param name The field name of the this element
       * @param value The value of this element.
       */
      static Element createElement( const std::string& name, Value* value );

      /**
       * @brief Return the name of the element.
       *
       * @return The field name.
       */
      const std::string& getName() const { return pimpl->getName(); }

      /**
       * @brief Rename this element.
       *
       * @warning Note that this is an internal use only
       * method.  If you invoke this method from client code, the element
       * may become invisible to the containing document.  Client's should
       * always use the methods in the document/array classes to manage
       * elements, which in turn will invoke this method to update the
       * instance as appropriate.
       *
       * @param name The new name for this element.
       */
      Element& setName( const std::string& name )
      {
        pimpl->setName( name );
        return *this;
      }

      /**
       * @brief Return a reference to the value held in this element for
       * editing.
       *
       * If the template type specified does not match the current data
       * type, or if the value is \c null an exception is thrown.
       *
       * @tparam DataType The type of value stored in the element.
       * @return The current value held in this element.
       * @throw Poco::NullValueException If no value is currently held
       *   in this element.
       * @throw Poco::BadCastException If the template type specified does
       *   not match the type held in this element.
       */
      template <typename DataType>
      DataType& getValue()
      {
        if ( ! pimpl->getValue() )
        {
          throw Poco::NullValueException( "Element does not contain a valid value" );
        }

        DataType* dt = dynamic_cast<DataType*>( pimpl->getValue() );
        if ( dt ) return *dt;

        throw Poco::BadCastException(
              "Value type: {" + pimpl->getValue()->getTypeName() + "} mismatch" );
      }

      /**
       * @brief Return a constant reference to the value held in this element.
       *
       * If the template type specified does not match the current data
       * type, or if the value is \c null an exception is thrown.
       *
       * @tparam DataType The type of value stored in the element.
       * @return The current value held in this element.
       * @throw Poco::NullValueException If no value is currently held
       *   in this element.
       * @throw Poco::BadCastException If the template type specified does
       *   not match the type held in this element.
       */
      template <typename DataType>
      const DataType& getValue() const
      {
        return const_cast<Element*>( this )->getValue<DataType>();
      }

      /**
       * @brief Set the value held in this element to the specified
       * value.
       *
       * @tparam DataType The type of value stored in the element.
       * @param dt The value to set for this element.
       * @return This instance for method chaining.
       */
      template <typename DataType>
      Element& setValue( const DataType& dt )
      {
        return set( new DataType( dt ) );
      }

      /**
       * @brief Set the value held in this element to the specified
       * value.
       *
       * @warning Note that the element takes ownership of the specified
       * value instance.  Callers must not \c delete the passed in
       * value.
       *
       * @param val The value to set for this element.
       * @return This instance for method chaining.
       */
      Element& set( Value* val )
      {
        pimpl->setValue( val );
        return *this;
      }

      /**
       * @brief Copy assignment operator used to assign a new value to
       * this element.
       *
       * @warning This element takes ownership of the passed in value
       * instance.  Callers must not \c delete the passed in value instance.
       *
       * @since Version 2.2
       * @tparam DataType The type of value stored in the element.
       * @param value The new value to associate with this element.
       * @return This instance for method chaining.
       */
      template <typename DataType>
      Element& operator = ( DataType value ) { return set( value ); }

      /**
       * @brief A convenience method to retrieve the value of a simple
       * type.  This cannot be implemented as a template specialisation
       * of the {@link #getValue()} method since those methods return
       * references to the value.
       *
       * Template specialisations are provided for the common simple
       * types (\c double, \c string, \c bool, \c integer, \c long) which will
       * work as expected.  This method makes it easier to retrieve
       * simple values than the full syntax.  For example:
       *
       * <pre>const double dval = elem->getValue<Double>().getValue();</pre>
       * becomes
       * <pre>const double dval = elem->getSimple<double>();</pre>
       *
       * @tparam SimpleType The primitive represented by the element value.
       * @return The simple value.
       */
      template <typename SimpleType>
      SimpleType getSimple() const
      {
        throw Poco::NotImplementedException( "No template specialisation available" );
      }

      /**
       * @brief Set the value for this element.  This is supported only
       * for the specialisations provided (primarily for setting simple
       * primitive type values).
       *
       * @tparam DataType The primitive value type.
       * @param v The value to set
       * @return This instance for method chaining.
       */
      template <typename DataType>
      Element& setSimple( const DataType /* v */ )
      {
        throw Poco::NotImplementedException( "No template specialisation available" );
      }

      /**
       * @brief Returns the total size in bytes the BSON representation
       * of this element.
       *
       * @return The size in bytes
       */
      int32_t getSize() const { return ( pimpl.get() ) ? pimpl->getSize() : 0; }

      /**
       * @brief Returns the type for data stored in this element.
       *
       * @return The current data type
       */
      Value::Type getType() const
      {
        return ( pimpl.get() ) ? pimpl->getType() : Value::Undefined;
      }

    private:
      class UMA_BSON_API ElementImpl
      {
      public:
        ElementImpl() : name(), value( 0 ) {}

        ElementImpl( const std::string& fieldName, Value* val ) :
          name( fieldName ), value( val ) {}

        ~ElementImpl();

        const std::string& getName() const { return name; }

        void setName( const std::string& newName ) { name = newName; }

        const Value* getValue() const { return value; }
        Value* getValue() { return value; }

        void setValue( Value* val );

        int32_t getSize() const;

        Value::Type getType() const
        {
          return ( value ) ? value->getType() : Value::Undefined;
        }

      private:
        ElementImpl( const ElementImpl& impl );
        ElementImpl& operator = ( const ElementImpl& rhs );

        std::string name;
        Value* value;
      };

      typedef Poco::SharedPtr<ElementImpl> PimplPtr;
      PimplPtr pimpl;
    };

    /// Specialised CTOR for an element holding a {@link uma::bson::Double}
    template<>
    UMA_BSON_API Element::Element( const std::string& name, const double& value );

    /// Specialised CTOR for an element holding a {@link uma::bson::String}
    template<>
    UMA_BSON_API Element::Element( const std::string& name, const std::string& value );

    /// Specialised CTOR for an element holding a {@link uma::bson::Boolean}
    template<>
    UMA_BSON_API Element::Element( const std::string& name, const bool& value );

    /// Specialised CTOR for an element holding a {@link uma::bson::Integer}
    template<>
    UMA_BSON_API Element::Element( const std::string& name, const int& value );

    /// Specialised CTOR for an element holding a {@link uma::bson::Long}
    template<>
    UMA_BSON_API Element::Element( const std::string& name, const int64_t& value );

    /// Specialised method for getting the value of {@link uma::bson::Double}
    template<>
    UMA_BSON_API double Element::getSimple<double>() const;

    /// Specialised method for getting the value of {@link uma::bson::String}
    template<>
    UMA_BSON_API std::string Element::getSimple<std::string>() const;

    /// Specialised method for getting the value of {@link uma::bson::Boolean}
    template<>
    UMA_BSON_API bool Element::getSimple<bool>() const;

    /// Specialised method for getting the value of {@link uma::bson::Integer}
    template<>
    UMA_BSON_API int32_t Element::getSimple<int32_t>() const;

    /// Specialised method for getting the value of {@link uma::bson::Long}
    template<>
    UMA_BSON_API int64_t Element::getSimple<int64_t>() const;

    /// Specialised method for setting the value to {@link uma::bson::Double}
    template<>
    UMA_BSON_API Element& Element::setValue<double>( const double& v );

    /// Specialised method for setting the value to {@link uma::bson::String}
    template<>
    UMA_BSON_API Element& Element::setValue<std::string>( const std::string& v );

    /// Specialised method for setting the value to {@link uma::bson::Boolean}
    template<>
    UMA_BSON_API Element& Element::setValue<bool>( const bool& v );

    /// Specialised method for setting the value to {@link uma::bson::Integer}
    template<>
    UMA_BSON_API Element& Element::setValue<int32_t>( const int32_t& v );

    /// Specialised method for setting the value to {@link uma::bson::Long}
    template<>
    UMA_BSON_API Element& Element::setValue<int64_t>( const int64_t& v );

    /// Specialised method for setting the value to {@link uma::bson::Double}
    template <>
    UMA_BSON_API Element& Element::operator = ( const double value );

    /// Specialised method for setting the value to {@link uma::bson::String}
    template <>
    UMA_BSON_API Element& Element::operator = ( const std::string& value );

    /// Specialised method for setting the value to {@link uma::bson::String}
    template <>
    UMA_BSON_API Element& Element::operator = ( const char* value );

    /// Specialised method for setting the value to {@link uma::bson::Boolean}
    template <>
    UMA_BSON_API Element& Element::operator = ( const bool value );

    /// Specialised method for setting the value to {@link uma::bson::Integer}
    template <>
    UMA_BSON_API Element& Element::operator = ( const int32_t value );

    /// Specialised method for setting the value to {@link uma::bson::Long}
    template <>
    UMA_BSON_API Element& Element::operator = ( const int64_t value );

    /**
     * @brief Comparison operator for ordering element instances.
     *
     * Compares the names of the two elements.  May be used by hash
     * containers to order the elements by name.
     *
     * @param lhs The left hand element to compare
     * @param rhs The right hand element to compare
     * @return Returns \c true if the name of the left hand element
     *   is lexically less than the name of the right hand element.
     */
    inline bool operator < ( const Element& lhs, const Element& rhs )
    {
      return lhs.getName() < rhs.getName();
    }

    /**
     * @brief Compare two elements for equality.  Compares the names
     * and held values of the elements.
     *
     * @since 2.0
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true if the two elements have the same
     *   name and value.
     */
    UMA_BSON_API bool operator == ( const Element& lhs, const Element& rhs );

    /// Just the reverse of operator ==
    inline bool operator != ( const Element& lhs, const Element& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_ELEMENT_H
