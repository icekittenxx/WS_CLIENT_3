#ifndef UMA_BSON_CODEWITHSCOPE_H
#define UMA_BSON_CODEWITHSCOPE_H

#include <string>
#include <uma/bson/Document.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::CodeWithScope
     *
     * \brief A POD that represents a code with document scope BSON element value.
     *
     * \date Created 2012/09/09 21:52
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: CodeWithScope.h 172 2012-12-14 17:21:21Z spt $
     */
    class UMA_BSON_API CodeWithScope : public Value
    {
    public:
      /// Default CTOR
      CodeWithScope() {}

      /**
       * @brief Create a new instance with the specified code and scope.
       *
       * @param c The code to be encapsulated in this instance.
       * @param doc The scope to be encapsulated in this instance.
       */
      CodeWithScope( const std::string& c, const Document& doc ) :
        code( c ), scope( doc ) {}

      /**
       * @brief Return the code value stored in this instance as a
       * constant reference.
       *
       * @return The code value
       */
      const std::string& getCode() const { return code; }

      /**
       * @brief Return the code value stored in this instance as a
       * non-constant reference.
       *
       * @return The code value
       */
      std::string& getCode() { return code; }

      /**
       * @brief Return the code stored in this instance.
       *
       * @return The code value
       */
      const std::string& getValue() const { return code; }

      /**
       * @brief Sets the code encapsulated in this instance.
       *
       * @param v The new code value to encapsulate
       * @return The current instance for method chaining
       */
      CodeWithScope& setCode( const std::string& v )
      {
        code = v;
        return *this;
      }

      /**
       * @brief Returns the scope stored in this instance as a
       * constant reference.
       *
       * @return The scope value
       */
      const Document& getScope() const { return scope; }

      /**
       * @brief Returns the scope stored in this instance as a
       * non-constant reference.
       *
       * @return The scope value
       */
      Document& getScope() { return scope; }

      /**
       * @brief Sets the scope encapsulated in this instance.
       *
       * @param doc The new scope value to encapsulate
       * @return This instance for method chaining
       */
      CodeWithScope& setScope( const Document& doc )
      {
        scope = doc;
        return *this;
      }

      /**
       * @brief Returns the total size of the BSON representation of this
       * instance.
       *
       * @return The total size if bytes for this instance
       */
      int32_t getSize() const
      {
        return static_cast<int32_t>( 4 + code.size() + 1 + scope.getSize() );
      }

      /**
       * @brief Returns the type for this instance as listed in the
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::CodeWScope
       */
      Value::Type getType() const { return Value::CodeWScope; }

    private:
      std::string code;
      Document scope;
    };

    /**
     * @brief Compare two code with scope instances for equality.
     * Compares the code and scope values of each instance.
     *
     * @since 2.0
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true if the two instances are equivalent
     */
    inline bool operator == (
        const CodeWithScope& lhs, const CodeWithScope& rhs )
    {
      return ( ( lhs.getCode() == rhs.getCode() ) &&
          ( lhs.getScope() == rhs.getScope() ) );
    }

    /// Just the reverse of operator ==
    inline bool operator != ( const CodeWithScope& lhs, const CodeWithScope& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_CODEWITHSCOPE_H
