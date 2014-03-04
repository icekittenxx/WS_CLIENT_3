#ifndef UMA_BSON_ODMOBJECT_H
#define UMA_BSON_ODMOBJECT_H

#include <uma/bson/Object.h>

#include <Poco/SharedPtr.h>

#include <map>
#include <typeinfo>

namespace uma
{
  namespace bson
  {

    /**
     * @brief Abstract class that presents a more friendly ODM interface
     * than {@link uma::bson::Object}.
     *
     * This class uses a registration system for model objects to register
     * their serialisable fields along with their accessor and mutator
     * methods (see {@link #registerField}.  This removes the
     * requirement to implement {@link #getValue} using an ugly
     * \c if-else statement block.
     *
     * \warning Note: Model classes will need to provide a \c non-const
     * version of the accessor methods for the registration to work.
     *
     * @tparam Model The type of the sub-class (needed for the MetaField
     *   implementation).
     * @since Version 2.5
     * \date Created 2013/02/13 10:30
     * \author Rakesh
     * \version $Id: ODMObject.h 205 2013-02-15 19:38:10Z spt $
     */
    template <typename Model>
    class ODMObject : public Object
    {
    public:
      /// Virtual destructor for sub-classes.
      virtual ~ODMObject() {}

      /**
       * @brief Return the names of the fields registered.  Note that
       * the fields are stored in a \c std::map, hence the order of
       * fields returned may not correspond to the order in which they
       * were registered.
       *
       * @return const FieldNames The \c vector of field names.
       */
      const FieldNames getFieldNames() const
      {
        Object::FieldNames names;

        const Model* model = static_cast<const Model*>( this );
        for ( typename MetaFieldMap::const_iterator iter = getMetaFields( model ).begin();
              iter != getMetaFields( model ).end(); ++iter )
        {
          names.push_back( iter->first );
        }

        return names;
      }

      Value& getValue( const std::string& name )
      {
        Model* model = static_cast<Model*>( this );
        typename MetaFieldMap::iterator iter = getMetaFields( model ).find( name );
        if ( iter == getMetaFields( model ).end() ) throw Poco::NotFoundException( "No field with name: " + name );

        return ( iter->second->getValue( model ) );
      }

      void setValue( const std::string& name, const Value& value )
      {
        Model* model = static_cast<Model*>( this );
        typename MetaFieldMap::iterator iter = getMetaFields( model ).find( name );
        if ( iter == getMetaFields( model ).end() ) throw Poco::NotFoundException( "No field with name: " + name );

        iter->second->setValue( model, value );
      }

    protected:
      /**
       * @brief Abstract base class that encapsulates a field in a model
       * object.  Primarily used to get around requirement that implementation
       * needs exact type of data encapsulated in the field as template
       * type.
       */
      class MetaField
      {
      public:
        /**
         * @brief Create a new instance representing the field with the
         * specified name.
         *
         * @param field The name of the field.
         */
        MetaField( const std::string& field ) : name( field ) {}

        /// Virtual dtor for sub-classing
        virtual ~MetaField() {}

        /**
         * @brief Return the value for the field represented by this
         * instance
         *
         * @param model The model object from which the value is to retrieved.
         * @return Value The value for the field.
         */
        virtual Value& getValue( Model* model ) = 0;

        /**
         * @brief Set the value for the field represented by this
         * instance.
         *
         * @param model The model object in which the value is to be stored.
         * @param value The value for the field to store.
         */
        virtual void setValue( Model* model, const Value& value ) = 0;

        /**
         * @brief Return the name of the field encapsulated in this meta
         * field instance.
         *
         * @return const std::string The field name.
         */
        const std::string& getName() const { return name; }

      private:
        /// The name of the field
        std::string name;
      };

      /// Shared pointer for a meta field instance.
      typedef Poco::SharedPtr<MetaField> MetaFieldPtr;

      /**
       * @brief Encapsulates a field in a model object.  Fields are
       * represented as a triplet of the field in the class, and its
       * accessor and mutator methods.
       *
       * @tparam DataType The data type for the field.  Must be a
       *   sub-class of {@link uma::bson::Value}.
       */
      template <typename DataType>
      class MetaFieldImpl : public MetaField
      {
      public:
        /// Member function pointer to the accessor method
        typedef DataType& (Model::*Accessor)();

        /// Member function pointer to the mutator method
        typedef void (Model::*Mutator)( const DataType& );

        /**
         * @brief Create a new field instance for the specified instance
         * and methods.
         *
         * @param field The name of the field.
         * @param get The accessor method for the field.
         * @param set The mutator method for the field.
         */
        MetaFieldImpl( const std::string& field, Accessor get, Mutator set ) :
          MetaField( field ), accessor( get ), mutator( set ) {}

        Value& getValue( Model* model )
        {
          return ( model->*accessor )();
        }

        void setValue( Model* model, const Value& value )
        {
          const DataType& dt = dynamic_cast<const DataType&>( value );
          ( model->*mutator )( dt );
        }

      private:
        /// Pointer to accessor member function for field
        Accessor accessor;

        /// Pointer to mutator member function for field.  May be \c NULL
        Mutator mutator;
      };

      /**
       * @brief Add (register) a field with the map of fields in the
       * model object.  Best practise is to check whether class has been
       * registered (see {@link #registered}, and if not, register all
       * the fields for the class.
       *
       * @param mo The shared pointer to the meta field instance.
       */
      void registerField( const MetaFieldPtr mo )
      {
        const std::string& name = mo->getName();
        getMetaFields( static_cast<Model*>( this ) ).insert(
              std::pair<std::string,MetaFieldPtr>( name, mo ) );
      }

      /**
       * @brief Return the meta field instance for the field with the
       * specified name.
       *
       * @param name The name of the field whose meta instance is to be retrieved.
       * @return MetaFieldPtr The meta field representing the named field.
       */
      MetaFieldPtr getMetaField( const std::string& name )
      {
        typename MetaFieldMap::iterator iter = getMetaFields( this ).find( name );
        if ( iter == getMetaFields( this ).end() ) throw Poco::NotFoundException( "No field with name: " + name );

        return iter->second;
      }

      /**
       * @brief Check to see if the class for the model object has been
       * registered.  Registration is the process of defining the fields
       * with their accessor and mutator methods.
       *
       * @param model The model object to check to see if registered.
       * @return bool Returns \c true if already registered.
       */
      static bool registered( Model* model )
      {
        std::string cls( typeid( model ).name() );
        typename ClassMetaFields::const_iterator iter = getClassMetaFields().find( cls );
        return ( iter != getClassMetaFields().end() );
      }

    private:
      /// Mapping of field-name to meta field instance.
      typedef std::map<std::string,MetaFieldPtr> MetaFieldMap;

      /// Mapping of class to field-name mapping
      typedef std::map<std::string,MetaFieldMap> ClassMetaFields;

      static ClassMetaFields& getClassMetaFields()
      {
        static ClassMetaFields cmf;
        return cmf;
      }

      static MetaFieldMap& getMetaFields( Model* model )
      {
        std::string cls( typeid( model ).name() );
        ClassMetaFields& cmf = getClassMetaFields();
        MetaFieldMap& mm = cmf[cls];
        return mm;
      }

      static MetaFieldMap& getMetaFields( const Model* model )
      {
        // typeid returns different value without casting away const-ness
        return getMetaFields( const_cast<Model*>( model ) );
      }
    };

  } // namespace bson
} // namespace uma

#endif // UMA_BSON_ODMOBJECT_H
