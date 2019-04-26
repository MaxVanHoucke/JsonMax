## JsonMax &nbsp; [![Build Status](https://travis-ci.com/MaxVanHoucke/JsonMax.svg?token=h6oBgPcMpoopU8fjW1uH&branch=master)](https://travis-ci.com/MaxVanHoucke/JsonMax)

### A lightweight Json serializer/deserializer and data type for C++

- [Examples](#Examples)
  - [Basic deserializing/parsing](#Basic example, deserializing/parsing)
- [Efficiency](#Upcomingfeatures)


### Upcomin gfeatures
- Derive from class to make object json deserializable
- Single include
- speed test
- make any class serializable and deserializable


## Examples

### Deserializing/parsing

```cpp
// Single include
#include "JsonMax.h"

// Everything is wrapped in this namespace
using namespace JsonMax;

int main() {
    // Parse file
    Object jsonFile = parseFile("file.json");
    
    // Parse string
    Object jsonString = parse(" {\"name\": \"max\"} ");
    
    // Using raw strings makes it easier
    Object jsonString2 = parse(R"( { "name": "max" } )");
    
    return 0;
}


```

