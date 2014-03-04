#ifndef UMA_BSON_ARRAY_H
#define UMA_BSON_ARRAY_H

#include <uma/bson/Value.h>
#include <uma/bson/Element.h>

#include <Poco/SharedPtr.h>
#include <sstream>
#include <vector>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Array
     * \brief A class that represents a BSON array type document.
     *
     * An array stores its elements using sequential numbers as
     * the element/field names.  All data is stored as a shared pointer
     * to a PIMPL class to allow efficient pass by value semantics.
     * To properly clone/copy an array use the {@link #clone} method.
     *
     * \date Created 2012/09/06 18:41
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Array.h 203 2013-02-15 12:23:15Z spt $
     */
    class UMA_BSON_API Array : public Value
    {
    public:
      /// Default constructor.  Unlike {@link Document} no object id is assigned
      Array() : pimpl( new ArrayImpl ) {}

      /**
       * @brief Create a new array instance with the contents of the
       * BSON file at specified path.
       *
       * @param filePath The fully qualified name of the file to read.
       * @return The array object representing the BSON data.
       */
      static Array fromFile( const std::string& filePath );

      /**
       * @brief Create a new array instance with the contents of the
       * \c char array.  Can be used to create array instances from
       * MongoDB C/C++ driver functions.
       *
       * @param bytes The char array containing the BSON data
       * @param length  The total length of the char array
       * @return The array object representing the BSON data.
       */
      static Array fromBytes( const char* bytes, const int32_t length );

      /**
       * @brief  Create a new array instance with the contents read
       * from the specified stream.  Usually used to read the BSON
       * data over a network.
       *
       * @param is The input stream to read the BSON data from
       * @return The array object representing the BSON data.
       */
      static Array fromStream( std::istream& is );

      /**
       * @brief  Create a new array instance with the JSON data
       * from the specified stream.
       *
       * @param is The input stream to read the JSON data from
       * @return The array object representing the BSON data.
       */
      static Array fromJson( std::istream& is );

      /**
       * @brief Check to see if the array is empty (has no elements)
       *
       * @return Return \c true if there are no child elements.
       */
      bool isEmpty() const { return pimpl->isEmpty(); }

      /**
       * @brief Return the total number of fields->(top-level) in this
       * array.
       *
       * @return The total number of fields->
       */
      size_t size() const { return pimpl->size(); }

      /// A constant iterator for the elements in the array.
      typedef std::vector<Element>::const_iterator ConstantIterator;

      /**
       * @brief Return a constant iterator to the first element in the
       * array.
       *
       * @since 2.0
       * @return The iterator to the first element.
       */
      ConstantIterator begin() const { return pimpl->begin(); }

      /**
       * @brief Return a constant iterator to the last element in the
       * array.
       *
       * @since 2.0
       * @return The iterator to the last element.
       */
      ConstantIterator end() const { return pimpl->end(); }

      /**
       * @brief Return the element at the specified index in the array
       * as a constant reference.
       *
       * @param index The array index from which to retrieve the element.
       * @return The element at the specified index.
       * @throw std::out_of_range If the specified index is invalid.
       */
      const Element& at( const size_t index ) const { return pimpl->at( index ); }

      /**
       * @brief Return the element at the specified index in the array
       * as a reference.
       *
       * @param index The array index from which to retrieve the element.
       * @return The element at the specified index
       * @throw std::out_of_range If the specified index is invalid.
       */
      Element& at( const size_t index ) { return pimpl->at( index ); }

      /**
       * @brief Return a reference to the element at the specified index
       * in the array.
       *
       * If no element exists at the specified index, an empty element with
       * value {@link uma::bson::Undefined} is created and stored at the
       * specified index.  A total of \c index - {@link #size()} elements
       * will be added to the array.
       *
       * @param index The index of the element within the array
       * @return The reference to the existing element or newly created one.
       */
      Element& operator [] ( const size_t index );

      /// Alias for {@link #at( const int ) const}
      const Element& operator [] ( const size_t index ) const { return at( index ); }

      /**
       * @brief Adds the specified element to the array.
       *
       * Note that any name specified to the element is ignored.  Moreover,
       * the name of the element is modified to indciate its index in
       * the array.
       *
       * @param element The element to add to the array
       * @param index The index at which to add the element.  This
       *   enables user defined ordering of the array contents.
       * @return The current array instance to enable method chaining.
       */
      Array& add( const Element& element, const int index = -1 )
      {
        pimpl->add( element, index );
        return *this;
      }

      /**
       * @brief Add a new element with the specified value to the array.
       *
       * @tparam DataType The type of value to be added to the array.
       * @param value The new value to add to the array
       * @return The current array instance to enable method chaining.
       */
      template <typename DataType>
      Array& add( const DataType& value )
      {
        std::stringstream ss;
        ss << size();
        Element e( ss.str(), value );
        return add( e );
      }

      /// Alias for {@link #add} method.
      template <typename DataType>
      Array& operator << ( const DataType& value ) { return add( value ); }

      /**
       * @brief Remove the element at the specified index
       *
       * @param index The index of the element to remove from the array.
       * @return A copy of the element that was removed.
       * @throw Poco::NotFoundException If no element exists at the
       *   specified index.
       */
      Element remove( const int index ) { return pimpl->remove( index ); }

      /**
       * @brief Write a BSON representation of the data in this array
       * to the output stream.
       *
       * @param os The output stream to serialise the BSON data to.
       */
      void toBson( std::ostream& os ) const;

      /**
       * @brief Generate a JSON representation of the data in the
       * array.
       *
       * Note that the JSON generated is based closely upon the BSON
       * specification and is not in a "natural" JSON format.  The
       * format was chosen to make it easy to re-parse the JSON back
       * into a array.
       *
       * @param os The output stream to serialise the JSON data to.
       * @param prettyPrint Indicate whether the output should contain
       *   indentation and line breaks for readability.
       */
      void toJson( std::ostream& os, bool prettyPrint = false ) const;

      /**
       * @brief Clone the contents of this array.
       *
       * This is the recommended way to copy an array.  The default
       * copy constructor and assignment operator return array instances
       * that share the internal data.  This method returns an array
       * instance with the equivalent but different instances of the
       * internal data.
       *
       * @warning This method has not been optimised.  The current
       * implementation serialises the array to a BSON stream, and
       * then de-serialises the BSON stream into a new array instance.
       *
       * @since 1.3
       * @return An array instance with all the internal data duplicated.
       */
      Array clone() const;

      /**
       * @brief Return the size of the bson data held in the array.
       *
       * @return The size of the bson data array
       */
      int32_t getSize() const { return pimpl->getSize(); }

      /**
       * @brief Returns the datatype for an array as specified in the
       * BSON specification.
       *
       * @return The type for an array.
       */
      Value::Type getType() const { return Value::Array; }

    private:
      class ArrayImpl
      {
      public:
        bool isEmpty() const { return fields.empty(); }
        size_t size() const { return fields.size(); }

        Array::ConstantIterator begin() const { return fields.begin(); }
        Array::ConstantIterator end() const { return fields.end(); }

        Element& at( const size_t index ) { return fields.at( index ); }
        const Element& at( const size_t index ) const { return fields.at( index ); }

        void add( const Element& element, const int index = -1 );

        Element remove( const int index );

        int32_t getSize() const;

      private:
        typedef std::vector<Element> Container;
        Container fields;
      };

      typedef Poco::SharedPtr<ArrayImpl> PimplPtr;
      PimplPtr pimpl;
    };

    /**
     * @brief Compare two arrays for equality.  Arrays are considered
     * equal if they have the same size and the same elements at the
     * same indices in the array.
     *
     * @warning This method performs a true deep comparison and will not
     * be efficient.
     *
     * @since 2.0
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true if the two instances have equivalent elements.
     */
    UMA_BSON_API bool operator == ( const Array& lhs, const Array& rhs );

    /// Just the reverse of operator ==
    inline bool operator != ( const Array& lhs, const Array& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_ARRAY_H
