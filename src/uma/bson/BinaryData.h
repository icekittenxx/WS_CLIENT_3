#ifndef UMA_BSON_BINDATA_H
#define UMA_BSON_BINDATA_H

#include <uma/bson/Value.h>

#include <Poco/SharedPtr.h>

#include <iostream>
#include <vector>

namespace uma
{
  namespace bson
  {
    /**
     * \class uma::bson::BinaryData
     *
     * \brief A POD that represents a BSON element of type binary data.
     *
     * This is just an array of bytes (char) stored in a std::vector.
     * The recommended way to fill/populate the {@link BinaryData::Buffer}
     * is to create an empty instance of this class, get a non-constant
     * reference to the buffer and populate it.  The usual caveat about
     * reserving space in the vector before filling applies.
     *
     * \date Created 2012/09/06 18:50
     * \copyright Copyright &copy; 2012, Sans Pareil Technologies, Inc.
     * \author Rakesh
     * \version $Id: BinaryData.h 174 2012-12-15 13:13:56Z spt $
     */
    class UMA_BSON_API BinaryData : public Value
    {
    public:
      /// The container used to store the binary data
      typedef std::vector<char> Buffer;

      /// Enumeration of the types used to identify the type of binary content
      enum DataType
      {
        General = 0, ///< Binary / Generic data to be used by all clients/tools
        Function = 1,
        ByteArrayDeprecated = 2, ///< use General instead
        UUIDDeprecated = 3, ///< deprecated
        UUID = 4, ///< language-independent UUID format across all drivers
        MD5 = 5,
        Custom = 128 ///< User defined type
      };

      /**
       * @brief Default constructor.
       *
       * @param dt The binary data type to assign to this instance.
       *   Defaults to \c DataType::General
       */
      BinaryData( const DataType dt = BinaryData::General ) :
        pimpl( new BinaryDataImpl( dt ) ) {}

      /**
       * @brief Create a new instance with the data specified.
       *
       * @param length The total length in bytes of the binary content
       * @param data The binary data
       * @param dataType The data type for the binary content
       */
      BinaryData( const char*& bytes, const int length,
          const DataType dt = BinaryData::General ) :
        pimpl( new BinaryDataImpl( bytes, length, dt ) ) {}

      /**
       * @brief Create a new instance from the contents of the specified
       * stream.
       *
       * @param is The input stream from which the binary data is to be
       *   read.
       * @param dataType The data type for the binary content
       */
      BinaryData( std::istream& is, const DataType dt = BinaryData::General ) :
        pimpl( new BinaryDataImpl( is, dt ) ) {}

      /**
       * @brief Create a new instance with the contents of the file
       * at specified path.
       *
       * @param filePath The fully qualified path to the file.
       * @throw Poco::Exception If errors are encountered while reading
       *   the file.
       */
      BinaryData( const std::string& filePath, const DataType dt = BinaryData::General ) :
        pimpl( new BinaryDataImpl( filePath, dt ) ) {}

      /**
       * @brief Return the data stored in this instance as a constant
       * reference.
       *
       * @return The binary data.
       */
      const Buffer& getData() const { return pimpl->getData(); }

      /**
       * @brief Return the data stored in this instance as a non-constant
       * reference.
       *
       * @return The binary data.
       */
      Buffer& getData() { return pimpl->getData(); }

      /**
       * @brief Set the binary data for this instance.
       *
       * @warning Note that this method involves copying the specified
       * data.  This can be a very expensive method and should be
       * used with care.  Recommended method is to retrieve the
       * non-constant reference to the data and clear/fill it.  If
       * populating a fresh instance, default construct an instance,
       * fetch reference to the data and fill it.
       *
       * @param buffer The data that will replace the current data.
       * @param dataType The data type for the new binary data.
       * @return The current instance for method chaining.
       */
      BinaryData& setData( const Buffer& buffer,
          const DataType dataType = BinaryData::General )
      {
        pimpl->setData( buffer, dataType );
        return *this;
      }

      /**
       * @brief Return the data type for the binary data.
       *
       * @return The binary data type
       */
      DataType getDataType() const { return pimpl->getDataType(); }

      /**
       * @brief Return the size of the bson representation of the binary data.
       *
       * The size of the bson representation is \c 4 bytes for the
       * length of the data, plus \c 1 byte for the binary data type,
       * plus the size of the buffer itself.
       *
       * @return The size of the bson representation of the vector holding
       *   the binary data.
       */
      int32_t getSize() const { return pimpl->getSize(); }

      /**
       * @brief Return the type that represents binary data as per
       * BSON specifications.
       *
       * @return Returns {@link uma::bson::Value}::Type::BinData
       */
      Value::Type getType() const { return Value::BinData; }

    private:
      class UMA_BSON_API BinaryDataImpl
      {
      public:
        BinaryDataImpl( const DataType dt = BinaryData::General ) : dataType( dt ) {}

        BinaryDataImpl( const char*& bytes, const int length, const DataType dt ) :
          dataType( dt ), data( bytes, bytes + length ) {}

        BinaryDataImpl( std::istream& is, const DataType dt );

        BinaryDataImpl( const std::string& filePath, const DataType dt );

        const Buffer& getData() const { return data; }
        Buffer& getData() { return data; }

        void setData( const Buffer& buffer, const DataType dataType );

        DataType getDataType() const { return dataType; }

        int32_t getSize() const;

      private:
        DataType dataType;
        Buffer data;
      };

      typedef Poco::SharedPtr<BinaryDataImpl> PimplPtr;
      PimplPtr pimpl;
    };

    /**
     * @brief Writes the contents of the binary data to the specified
     * file output stream.
     *
     * @param os The file output stream to write the binary data to.
     * @param element The binary data instance to serialise to file.
     * @return The output stream for method chaining.
     */
    UMA_BSON_API std::ofstream& operator << (
        std::ofstream& os, const BinaryData& element );

    /**
     * @brief Writes the contents of the binary data to the specified
     * output stream.
     *
     * @param os The output stream to write the binary data to.
     * @param element The binary data instance to serialise to the stream.
     * @return The output stream for method chaining.
     */
    inline std::ostream& operator << (
        std::ostream& os, const BinaryData::DataType& type )
    {
      os << static_cast<int>( type );
      return os;
    }

    /**
     * @brief Compare two binary data instances for equality.  Compares
     * the data stored in each instance and their types for equality.
     *
     * @warning Performance of this method will depend upon the size of
     * the binary data held in the instances.
     *
     * @since 2.0
     * @param lhs The left hand value to compare
     * @param rhs The right hand value to compare
     * @return Return \c true if the two instances are equivalent.
     */
    inline bool operator == ( const BinaryData& lhs, const BinaryData& rhs )
    {
      return ( ( lhs.getDataType() == rhs.getDataType() ) &&
          ( lhs.getData() == rhs.getData() ) );
    }

    /// Just the reverse of operator ==
    inline bool operator != ( const BinaryData& lhs, const BinaryData& rhs )
    {
      return ! ( lhs == rhs );
    }

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_BINDATA_H
