#ifndef UMA_BSON_REGULAREXPRESSION_H
#define UMA_BSON_REGULAREXPRESSION_H

#include <uma/bson/Value.h>

#include <sstream>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::RegularExpression
     *
     * \brief A POD that represents a regular expression type BSON element value.
     *
     * \date Created 2012/09/09 21:41
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: RegularExpression.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API RegularExpression : public Value
    {
    public:
      /// Default CTOR
      RegularExpression() {}

      /**
       * @brief Create a new instance that encapsulates the specified
       * regular expression and flags values.
       *
       * @param re The regular expression to encapsulate
       * @param f The flags to encapsulate.  Defaults to empty.
       */
      RegularExpression( const std::string& re, const std::string& f = std::string() ) :
        regex( re ), flags( f ) {}

      /**
       * @brief Return the regular expression value encapsulated in this
       * instance as a constant reference.
       *
       * @return The regular expression value.
       */
      const std::string& getRegex() const { return regex; }

      /**
       * @brief Return the regular expression value encapsulated in this
       * instance as a non-constant reference.
       *
       * @return The regular expression value.
       */
      std::string& getRegex() { return regex; }

      /**
       * @brief Set the regular expression encapsulated in this instance.
       *
       * @param value The regular expression value
       * @return This instance for method chaining
       */
      RegularExpression& setRegex( const std::string& value )
      {
        regex = value;
        return *this;
      }

      /**
       * @brief Return the flags value encapsulated in this instance as
       * a constant reference.
       *
       * @return The regex flags.
       */
      const std::string& getFlags() const { return flags; }

      /**
       * @brief Return the flags value encapsulated in this instance as
       * a non-constant reference.
       *
       * @return The regex flags.
       */
      std::string& getFlags() { return flags; }

      /**
       * @brief Set the regular expression flags value encapsulated in
       * this instance
       *
       * @param value The regex flags value
       * @return This instance for method chaining.
       */
      RegularExpression& setFlags( const std::string& value )
      {
        flags = value;
        return *this;
      }

      /**
       * @brief Return a string representation of this instance.
       *
       * The returned value is primarily intended for logging/debugging
       * purposes.
       *
       * @return The string representation
       */
      std::string toString() const
      {
        std::stringstream ss;
        ss << "{ \"$regex\" : \"" << regex <<
              "\", \"$options\" : \"" << flags << "\" }";
        return ss.str();
      }

      /**
       * @brief Return the total size in bytes the BSON representation
       * of the data in this instance occupies.
       *
       * @return Returns length in bytes
       */
      int32_t getSize() const { return static_cast<int32_t>( regex.size() + flags.size() + 2 ); }

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::RegEx
       */
      Value::Type getType() const { return Value::RegEx; }

    private:
      std::string regex;
      std::string flags;
    };

    /**
     * @brief Compare two regular expressions for equality.  Compares
     * the \c regex and \c flags values for equality.
     *
     * @since 2.0
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true if the two instances are equivalent.
     */
    inline bool operator == (
        const RegularExpression& lhs, const RegularExpression& rhs )
    {
      return ( ( lhs.getRegex() == rhs.getRegex() ) &&
          ( lhs.getFlags() == rhs.getFlags() ) );
    }

    /// Just the reverse of operator ==
    inline bool operator != (
        const RegularExpression& lhs, const RegularExpression& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_REGULAREXPRESSION_H
