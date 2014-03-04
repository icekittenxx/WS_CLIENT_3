#include <uma/bson/Object.h>
#include <uma/bson/ODMObject.h>
#include <uma/bson/Document.h>
#include <uma/bson/Array.h>
#include <uma/bson/String.h>
#include <uma/bson/Integer.h>

#include <Poco/FileStream.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using uma::bson::Object;
using uma::bson::ODMObject;
using uma::bson::Document;
using uma::bson::Array;
using uma::bson::String;
using uma::bson::Integer;


namespace test
{
	// Simple class that illustrates encapsulation of BSON document/array instances
	class Person
	{
	public:
		Person() : doc( uma::bson::Document::emptyDocument() )
		{
			using std::string;

			doc["name"] = "Some Developer";
			doc["city"]  = "Some City";
			doc["state"] = "Some State";
			doc["country"] = "Some Country";
			doc["hello"] = "world";

			phones[0] = "+1 111 222 3333";
			phones << string( "+44 222 333 4444" );
			phones << string( "+91 333 444 5555" );
		}

		const std::string& getName() const { return doc.get( "name" ).getValue<String>().getValue(); }
		void setName( const std::string& name ) { doc.set( "name", name ); }

		const std::string& getCity() const { return doc.get( "city" ).getValue<String>().getValue(); }
		void setCity( const std::string& city ) { doc.set( "city", city ); }

		const std::string& getState() const { return doc.get( "state" ).getValue<String>().getValue(); }
		void setState( const std::string& state ) { doc.set( "state", state ); }

		const std::string& getCountry() const { return doc.get( "country" ).getValue<String>().getValue(); }
		void setCountry( const std::string& country ) { doc.set( "country", country ); }

		const std::vector<std::string> getPhones() const
		{
			std::vector<std::string> v;

			for ( Array::ConstantIterator iter = phones.begin(); iter != phones.end(); ++iter )
			{
				v.push_back( iter->getValue<String>().getValue() );
			}

			return v;
		}

		void print() const
		{
			using std::cout;
			using std::endl;
			using std::string;
			using std::vector;

			cout << "Person bson contents" << endl;
			cout << "Name: " << getName() << endl;
			cout << "City: " << getCity() << endl;
			cout << "State: " << getState() << endl;
			cout << "Country: " << getCountry() << endl;

			cout << "Phone numbers: ";
			const vector<string>& phones = getPhones();
			for ( vector<string>::const_iterator iter = phones.begin(); iter != phones.end(); ++iter )
			{
				cout << *iter << ", ";
			}
			cout << endl;

			cout << endl << "JSON representation:" << endl;
			doc.toJson( cout );
			
			//----------------------------);
			//--------------------

			using std::ostream;
			using std::filebuf;
			using std::string;
			using std::ostringstream;
			using std::stringstream;
			using std::iostream;

			//filebuf fb;
			//fb.open ("d:\\test.txt", std::ios::out);
			//std::ostream os(&fb);
			//os << "Test sentence\n";
			//fb.close();
			//string buf;
			//iostream ok();

			//string out( "D:/test.txt" );
			//Poco::FileOutputStream fos( out, std::ios::out | std::ios::binary | std::ios::trunc );
			//doc.toBson( fos );
			//fos.close();


			ostringstream buf(std::ios::out | std::ios::binary |std::ios::trunc);
			doc.toBson(buf);

			string oo;
			oo = buf.str();
			cout << endl;
			cout << oo;
			cout << endl;
			for(int i = 0; i < oo.size(); i ++){
				cout << oo[i];
			}
			//char xx[100];
			//memset(xx, 0x00, sizeof xx);
			//memcpy(xx, oo.c_str(), sizeof xx);
			
			//--------------------
			//--------------------------------
			cout << endl;
		}

	private:
		uma::bson::Document doc;
		uma::bson::Array phones;
	};

	// Simple class that illustrates ODM
	class Group : public uma::bson::Object
	{
	public:
		Group() {}

		const int getGid() const { return gid.getValue(); }
		void setGid( const int value ) { gid.setValue( value ); }

		const std::string& getName() const { return name.getValue(); }
		void setName( const std::string& n ) { name.setValue( n ); }

		Group clone() const
		{
			std::stringstream ss;
			toBson( ss );

			Group g;
			g.populate( ss );
			return g;
		}

		void print() const
		{
			std::cout << "Group gid: " << getGid() << ", name: " << getName() << std::endl;
		}

	private:
		const FieldNames getFieldNames() const
		{
			FieldNames names;
			names.push_back( "gid" );
			names.push_back( "name" );

			return names;
		}

		uma::bson::Value& getValue( const std::string& element )
		{
			if ( element == "gid" ) return gid;
			if ( element == "name" ) return name;
		}

	private:
		uma::bson::Integer gid;
		uma::bson::String name;
	};

	// Simple class that illustrates better ODM
	class Role : public ODMObject<Role>
	{
	public:
		Role() : rid( 0 ), name() { registerFields(); }
		Role( const int32_t id, const std::string& rn ) : rid( id ), name( rn ) { registerFields(); }

		uma::bson::Integer& getRid() { return rid; }
		const uma::bson::Integer& getRid() const { return rid; }
		void setRid( const uma::bson::Integer& id ) { rid = id; }

		uma::bson::String& getName() { return name; }
		const uma::bson::String& getName() const { return name; }
		void setName( const uma::bson::String& rn ) { name = rn; }

	private:
		void registerFields()
		{
			if ( ! registered( this ) )
			{
				registerField( new MetaFieldImpl<uma::bson::Integer>( "rid", &Role::getRid, &Role::setRid ) );
				registerField( new MetaFieldImpl<uma::bson::String>( "name", &Role::getName, &Role::setName ) );
			}
		}

	private:
		uma::bson::Integer rid;
		uma::bson::String name;
	};
}

void main()
{
	using std::cout;
	using std::endl;

	test::Person person;
	person.print();

	test::Group og;
	og.setGid( 100 );
	og.setName( "Some Group" );
	cout << endl << "Simple ODM demo" << endl << "Original ";
	og.print();

	const test::Group& cg = og.clone();
	cout << "Cloned ";
	cg.print();

	test::Role role;
	role.setRid( Integer( 1234 ) );
	cout << "ODM demo: role.getValue( \"rid\" ) == role.getRid(): " <<
		( role.getValue( "rid" ) == role.getRid() ) << endl;
	role.setValue( "name", String( "Test Role" ) );
	cout << "ODM demo: role.getValue( \"name\" ) == role.getName(): " <<
		( role.getValue( "name" ) == role.getName() ) << endl;

	cout << endl << "Close window to exit" << endl;
	std::string s;
	std::cin >> s;

	return;
}
