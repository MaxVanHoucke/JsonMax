## JsonMax &nbsp; [![Build Status](https://travis-ci.com/MaxVanHoucke/JsonMax.svg?token=h6oBgPcMpoopU8fjW1uH&branch=master)](https://travis-ci.com/MaxVanHoucke/JsonMax)

### A lightweight Single Include Json Library for C++11

- [Guide](#guide)
  - [How to use](#how-to-use)
  - [Parsing/toJson](#deserializationserialization-parsingtojson)
  - [Error handling](#error-handling)
- [Efficiency and design](#efficiency-and-design)

## Guide

### How to use

JsonMax is written in C++11 and only uses the standard library. Just download the single include file, and include it wherever you need. It's that easy!  

```cpp
#include "JsonMax.h"

// Optional, saves you some typing
using namespace JsonMax;
```


### Object

This class represents a Json Object.  
You can pick the underlying data structure used.

```cpp
// Creates a Json Object, uses a hashmap to store your key/value pairs
Object object;

// Pick your preferred data structure
Object hashmap(HASHMAP);
Object map(MAP);
Object vec(VECTOR);
```

#### Specifics of each data structure

| | Retrieve | Insert  | Remove | Memory used | Order of pairs |
|---|:---:|:---:|:---:|:---:|:---:|
| Hashmap | O(1) | O(1) | O(1) | Most | Random      
| Map | O(log n) | O(log n) | O(log n) | Medium | Alphabetical on keys 
| Vector | O(n) | O(1) | O(1) | Minimal | Original

#### Usage

An object stores instances of the Element class.  
These elements can be retrieved with the operator[], it returns a reference to the Element with the given key, and creates one if not present.  Because Element has constructors and assigment operators for all possible json values (objects, strings, ints, floats, arrays), the following code 
can be written

```cpp
Object object;

// Strings, ints and doubles
object["library"] = "JsonMax";
object["number"] = 10;
object["pi"] = 3.14;

// Array with initializer list
object["array"] = {"can be all possible json values", 10, 2.1, Object()};

// Array with JsonMax::Array (which is a type alias for vector<Element>)
Array array;
array.push_back("can be all possible json values");
array.push_back(10);
object["different array"] = array;
 
// Object
object["owner"] = Object();

// Easily access/change object by chaining the operator[]
object["owner"]["name"] = "Max";
```

### Deserialization/Serialization (parsing/toJson)

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

### Error handling

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


## Efficiency and design
