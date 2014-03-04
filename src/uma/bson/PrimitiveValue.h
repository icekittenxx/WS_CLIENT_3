#ifndef UMA_BSON_PRIMITIVEVALUE_H
#define UMA_BSON_PRIMITIVEVALUE_H

#include <uma/bson/Value.h>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::PrimitiveValue
     *
     * \brief A base value class used to represent primitive type values.
     *
     * \tparam T The primitive type encapsulated by this class.
     * \since Version 2.0
     * \date Created 2012/12/02 18:02
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: PrimitiveValue.h 203 2013-02-15 12:23:15Z spt $
     */
    template <typename T>
    class UMA_BSON_API PrimitiveValue : public Value
    {
    public:
      /// Default CTOR
      PrimitiveValue() {}

      /**
       * @brief Create a new instance that encapsulates the specified
       * value.
       *
       * @param v The primitive value to encapsulate
       */
      explicit PrimitiveValue( const T v ) : value( v ) {}

      /**
       * @brief Return the primitive value encapsulated in this instance.
       *
       * @return The primitive value
       */
      T getValue() const { return value; }

      /**
       * @brief Set the value encapsulated in this instance.
       *
       * @param v The new value to set.
       * @return This instance for method chaining
       */
      PrimitiveValue<T>& setValue( const T v ) { value = v; return *this; }

      /**
       * @brief Adds the specified value to the encapsulated value.
       *
       * @param v The value to add
       * @return This instance for method chaining
       */
      PrimitiveValue<T>& operator += ( const T v )
      {
        value += v;
        return *this;
      }

      /**
       * @brief Subtract the specified value from the encapsulated value
       *
       * @param v The value to subtract
       * @return This instance for method chaining
       */
      PrimitiveValue<T>& operator -= ( const T v )
      {
        value -= v;
        return *this;
      }

      /**
       * @brief Multiple the encapsulated value by the specified value
       *
       * @param v The value to multiple by
       * @return This instance for method chaining
       */
      PrimitiveValue<T>& operator *= ( const T v )
      {
        value *= v;
        return *this;
      }

      /**
       * @brief Divide the encapsulated value by the specified value.
       *
       * @param v The value to divide by
       * @return This instance for method chaining
       */
      PrimitiveValue<T>& operator /= ( const T v )
      {
        value /= v;
        return *this;
      }

      /// Cast operator to convert to the encapsulated value
      operator T () const { return value; }

    private:
      T value;
    };

    /**
     * @brief Compare the encapsulated values in the specified instances
     * for equality;
     *
     * @tparam T The primitive type encapsulated by this class.
     * @param lhs The left hand instance to compare.
     * @param rhs The right hand instance to compare.
     * @return Return \c true if the values are equal
     */
    template <typename T>
    inline bool operator == ( const PrimitiveValue<T>& lhs, const PrimitiveValue<T>& rhs )
    {
      return lhs.getValue() == rhs.getValue();
    }

    /**
     * @brief Compare the encapsulated value in the specified instance
     * for equality with the specified primitive value.
     *
     * @tparam T The primitive type encapsulated by this class.
     * @param lhs The primitive instance to compare.
     * @param rhs The primitive value to compare against
     * @return Return \c true if the values are equal
     */
    template <typename T>
    inline bool operator == ( const PrimitiveValue<T>& lhs, const T rhs )
    {
      return lhs.getValue() == rhs;
    }

    /// Just the reverse of operator ==
    template <typename T>
    inline bool operator != ( const PrimitiveValue<T>& lhs, const PrimitiveValue<T>& rhs )
    {
      return ! ( lhs == rhs );
    }

    /// Just the reverse of operator ==
    template <typename T>
    inline bool operator != ( const PrimitiveValue<T>& lhs, const T rhs )
    {
      return ! ( lhs == rhs );
    }

    /**
     * @brief Check to see if the value encapsulated in the left hand
     * instance is less than the value in the right hand instance.
     *
     * @tparam T The primitive type encapsulated by this class.
     * @param lhs The left hand instance to compare.
     * @param rhs The right hand instance to compare.
     * @return Return \c true if the value in the left hand instance
     *   is less than the value in the right hand instance.
     */
    template <typename T>
    inline bool operator < ( const PrimitiveValue<T>& lhs, const PrimitiveValue<T>& rhs )
    {
      return lhs.getValue() < rhs.getValue();
    }

    /**
     * @brief Compare the encapsulated value in the left hand instance
     * with the primitive value specified.
     *
     * @tparam T The primitive type encapsulated by this class.
     * @param lhs The left hand instance to compare.
     * @param rhs The primitive alue to compare
     * @return Return \c true if the value in the left hand instance
     *   is less than the right hand value.
     */
    template <typename T>
    inline bool operator < ( const PrimitiveValue<T>& lhs, const T rhs )
    {
      return lhs.getValue() < rhs;
    }

    /**
     * @brief Compare the encapsulated values of the two instances.
     *
     * @tparam T The primitive type encapsulated by this class.
     * @param lhs The left hand instance to compare against
     * @param rhs The right hand instance to compare against
     * @return Return \c true if the left hand instance is greater
     *   than the right hand instance.
     */
    template <typename T>
    inline bool operator > ( const PrimitiveValue<T>& lhs, const PrimitiveValue<T>& rhs )
    {
      return lhs.getValue() > rhs.getValue();
    }

    /**
     * @brief Compare the encapsulated value in the left hand instance
     * with the primitive value in the right hand instance.
     *
     * @tparam T The primitive type encapsulated by this class.
     * @param lhs The left instance to compare
     * @param rhs The primitivate value to compare
     * @return Return \c true if the encapsulated value is greater
     *   than the primitive value.
     */
    template <typename T>
    inline bool operator > ( const PrimitiveValue<T>& lhs, const T rhs )
    {
      return lhs.getValue() > rhs;
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_PRIMITIVEVALUE_H
