#ifndef UMA_BSON_TEXT_H
#define UMA_BSON_TEXT_H

#include <uma/bson/Value.h>
#include <algorithm>
#include <string>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::Text
     *
     * \brief A class that holds a string.  BSON string/text values can
     * be large, hence take care when copy constructing or assigning
     * text instances.
     *
     * \date Created 2012/11/30 6:10
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: Text.h 174 2012-12-15 13:13:56Z spt $
     */
    class UMA_BSON_API Text : public Value
    {
    public:
      /**
       * @brief Return the value held in this instance as a constant reference.
       *
       * @return The constant reference to the string.
       */
      const std::string& getValue() const { return value; }

      /**
       * @brief Return the value held in this instance as a reference.
       *
       * @return The reference to the string.
       */
      std::string& getValue() { return value; }

      /**
       * @brief Set the value held in this instance.
       *
       * @param text The new value to hold
       * @return This instance for method chaining
       */
      Text& setValue( const std::string& text )
      {
        value = text;
        return *this;
      }

      /**
       * @brief Append the specified string to the value held in this instance.
       *
       * @param str The string to append.
       * @return This instance for method chaining
       */
      Text& operator += ( const std::string& str )
      {
        value += str;
        return *this;
      }

      /// Cast operator to make this instance behave as a standard string
      operator std::string() const { return value; }

      /**
       * @brief Return the size in bytes for the BSON representation of
       * this instance.
       *
       * @return Returns \c 4 for the length of the string +
       *   size of the string + \c 1 for the null terminator
       */
      int32_t getSize() const
      {
        return static_cast<int32_t>( 4 + value.size() + 1 );
      }

      /**
       * @brief Return the size of the held string.  As with std::string
       * the returned size does not include a null-terminator character.
       *
       * @return The size of the held string.
       */
      size_t size() const { return value.size(); }

    protected:
      /**
       * @brief Default CTOR.  Use to create an empty string value.
       *
       * This is the recommended way to create and populate string values.
       * Fetch the reference to the held string value and update/populate
       * it.
       */
      Text() : Value() {}

      /**
       * @brief Create a new text instance that represents the specified
       *   string value.
       *
       * @warning This form will involve a copy of the passed in string
       * value.  The recommended way to populate a text instance is by
       * default constructing an instance, and then populating the held
       * string value.
       *
       * @param text The string value to hold in this instance.
       */
      explicit Text( const std::string& text ) : Value(), value( text ) {}

      /**
       * @brief Create a text instance from a C-style char array.
       *
       * @param data The string value to hold
       */
      explicit Text( const char* data ) : Value(), value( data ) {}

    private:
      std::string value;
    };

    /**
     * @brief  Compare the two text instances for equality
     *
     * @param lhs The left hand text instance to compare
     * @param rhs The right hand text instance to compare
     * @return Return \c true if the held values are the same
     */
    inline bool operator == ( const Text& lhs, const Text& rhs )
    {
      return lhs.getValue() == rhs.getValue();
    }

    /**
     * @brief  Compare the held value with the specified value
     *
     * @param text The text value to compare with the string.
     * @param str The string value to compare with
     * @return Return \c true if the held value is same as the specified value.
     */
    inline bool operator == ( const Text& text, const std::string& str )
    {
      return text.getValue() == str;
    }

    /**
     * @brief Compare the two text instances. Compares the held values
     * of both instances.
     *
     * @param lhs The left hand text instance to compare
     * @param rhs The right hand text instance to compare
     * @return Return \c true if the value held in the left hand
     *   instance is lexically less than the value held in the right
     *   hand instance.
     */
    inline bool operator < ( const Text& lhs, const Text& rhs )
    {
      return lhs.getValue() < rhs.getValue();
    }

    /**
     * @brief Compares the value held in the specified text with the
     * specified string value
     *
     * @param text The text value to compare with the string.
     * @param str The string value to compare against
     * @return Return \c true if the value encapsulated in this
     *   instance is lexically lower than the value specified.
     */
    inline bool operator < ( const Text& text, const std::string& str )
    {
      return text.getValue() < str;
    }

    /// Just the reverse of operator ==
    inline bool operator != ( const Text& lhs, const Text& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_TEXT_H
