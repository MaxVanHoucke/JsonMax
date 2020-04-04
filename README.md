# JsonMax &nbsp; [![Build Status](https://travis-ci.com/MaxVanHoucke/JsonMax.svg?token=h6oBgPcMpoopU8fjW1uH&branch=master)](https://travis-ci.com/MaxVanHoucke/JsonMax)

### A lightweight Single Include Json library for modern C++11

- [How to use](#how-to-use)
- [Element](#element)
- [Object](#object)
- [Parsing/toJson](#deserializationserialization-parsingtojson)
- [Error handling](#error-handling)
- [Efficiency](#efficiency)
- [Build Source](#build-source)

## How to use

JsonMax is written in C++11 and only uses the standard library. Just [download](single_include/JsonMax.h) the single include file, and include it wherever you need. It's that easy!  

```cpp
#include "JsonMax.h"

// Optional, saves you some typing but is not always recommended
using namespace JsonMax;
```

## Element
Every possible Json value can be stored as an Element

```cpp
Element str = "JsonMax";
Element integer = 10;
Element floating = 3.14;
Element object = Object();
Element array = {"all possible json values", 3.14, 10, Object()};
Element boolean = true;
Element jsonNull = nullptr;

// Assignment operators available, changes the underlying type
integer = "now it's a string";
```

### Getters

When using a getter on an Element that stores a different type, e.g. stores a string but getInt() is called, a TypeException is thrown.

```cpp
element.getBool();
element.getInt();
element.getDouble();
element.getString();
element.getObject();
element.getArray();
```

### Type checkers

```cpp
// The type defaults to UNINITIALIZED
Element element;

// Returns a value from the Type enum (either INTEGER, BOOLEAN, FRACTION, OBJECT, STRING, ARRAY, JSON_NULL or UNINITIALIZED)
element.getType();

// Or conveniently use one of the following methods
element.isNull();
element.isBool();
element.isInt();
element.isDouble();
element.isString();
element.isObject();
element.isArray();
```

## Object

```cpp
// Creates a Json Object, uses a hashmap to store your key/value pairs
Object object;

// Pick your preferred data structure
Object hashmap(HASHMAP);
Object map(MAP);
Object vec(VECTOR);
```

### Specifics of each data structure

| | Retrieve | Insert  | Remove | Memory used | Order of pairs |
|---|:---:|:---:|:---:|:---:|:---:|
| Hashmap | O(1) | O(1) | O(1) | Most | Random      
| Map | O(log n) | O(log n) | O(log n) | Significant | Alphabetical on keys 
| Vector | O(n) | O(1) | O(n) | Minimal | Original

### Usage

The operator[] returns a reference to the Element with the given key (and creates one if the key didn't exist yet).  
Now the element can be used as previously described, which makes for some elegant code

```cpp
Object object;

object["library"] = "JsonMax";
object["number"] = 10;
object["pi"] = 3.14;

object["array"] = {"can be all possible json values", 10, 2.1, Object()};

// Array is a type alias for vector<Element>
Array array;
array.push_back("can be all possible json values");
array.push_back(10);
object["different array"] = array;

object["owner"] = Object();

// Chaining the operator[] works fine, if the elements are of type Object
object["owner"]["name"] = "Max";
```

### Iterate

Use the Object::pairs method to get a vector of the key/value pairs

```cpp
for (const Pair& pair: object.pairs()) {
    std::string key = pair.getKey();
    Element& value = pair.getValue();
}
```

### Handy methods

```cpp
// Removes a pair with given key, does nothing if the key doesn't exist
object.remove("key");

// Removes all pairs
object.clear();

// Returns the amount of items
object.size();

// Returns true if the pair with the given key exists
object.exists("key");

// Returns true if the object doesn't contain any pairs
object.empty();
```

## Deserialization/Serialization (parsing/toJson)

Parsing returns an Element, you can get the desired type with a getter.  
Both Element and object have a toString method, which returns the Json string representation.

```cpp
// Parsing returns an Element
Element obj = parse(" {\"name\": \"JsonMax\"} ");
Object actualObject = obj.getObject();

// Raw strings make it nicer
Element obj2 = parse(R"( {"name": "JsonMax"} )");

// Parse file
Element objFromFile = parseFile("filename.json");

// Get Json string
objFromFile.toString();

// Default indentation is 0, pick one yourself
objFromFile.toString(4);
```

## Error handling

The library includes 2 exceptions: TypeException and ParseException.  
Both inherit from std::exception and are self explanatory.
Some examples:

```cpp
Object object;
object["key"] = "string";

try {
    int integer = object["key"].getInt();
} catch (TypeException& e) {
    std::cout << e.what() << std::endl;
    
    // Output: Casting an element of type STRING to INTEGER is not possible.
}


try {
    // I forgot a '}' at the end of my string
    Element element = parse(R"( {"test": "a" )");
} catch (ParseException& e) {
    std::cout << e.what() << std::endl;
    
    // Output: Invalid Json: object does not end with '}'
}
```


## Efficiency

### Memory

Elements and Objects contain only one pointer to the actual data and one enum value.  
The pointer is situated in a union, while the enum indicates which type of pointer is currently in use. 

## Build Source

To build the source code simply use *CMake* and *Make*

```
mkdir build
cd build
cmake ..
make
```

You can now generate a new single include

```
cd src/include_generator
./JsonMaxIncludeGenerator
```

Or run all tests

```
cd test
./JsonMaxTests
```

Or run one of the examples (e.g. sweets demo)

```
cd examples/sweets
./JsonMaxDemoSweets
```
