#ifndef UMA_BSON_BSON_H
#define UMA_BSON_BSON_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(_WIN32_CE) || defined(_WIN64) && !defined(__CYGWIN__)
#include <cstdint>
#endif

#if (defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64))
  #if defined(UMA_BSON_EXPORTS)
    #define UMA_BSON_API __declspec(dllexport)
  #else
    #define UMA_BSON_API __declspec(dllimport)
  #endif
#endif

#if !defined(UMA_BSON_API)
  #define UMA_BSON_API
#endif


namespace uma
{
  /**
   * \namespace uma::bson
   *
   * \brief Classes that present a DOM style view of a BSON document.
   *
   * Namespace with classes that present a DOM style view of a BSON
   * document.  Unlike the MongoDB C++ API, a {@link uma::bson::Document}
   * and {@link uma::bson::Array} are not related.  A Document presents
   * a \c std::map style interface while an array presents a
   * \c std::vector type interface.
   *
   * All the value objects used to encapsulate BSON data types use shared
   * pointers to store its data where appropriate, making them easy to
   * pass by value.  This also makes them harder to clone.  Callers must
   * keep this in mind and treat shared memory with the usual care.
   */
  namespace bson
  {
    class Value;
    class EOO;
    class Double;
    class String;
    class BinaryData;
    class Undefined;
    class ObjectId;
    class Boolean;
    class Date;
    class Null;
    class RegularExpression;
    class DatabaseReference;
    class Code;
    class Symbol;
    class CodeWithScope;
    class Integer;
    class Timestamp;
    class Long;

    class Array;
    class Object;
    class Document;
    class Element;
  }
}

#endif // UMA_BSON_BSON_H
