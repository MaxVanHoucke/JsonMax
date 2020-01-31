/**
 * Example that shows using the data structures and exporting to json
 */

#include <iostream>
#include "../single_include/JsonMax.h"

using namespace JsonMax;
using namespace std;

int main() {

    // Using vector as storage (see readme for more info)
    Object stock(VECTOR);
    stock["cookies"] = 40;
    stock["chocolate bars"] = 23;
    stock["sour candies"] = 44;

    cout << "Json of stock:" << endl;
    cout << stock.toString() << endl;

    Object sweets;
    sweets["stock"] = stock;
    sweets["toppings"] = {"Hearts", "Disco", "Nuts"};
    sweets["shop"] = Object();
    sweets["shop"]["name"] = "Max' Sweets";
    sweets["shop"]["street"] = "Sweet Street";

    cout << "\nJson of sweets:" << endl;
    cout << sweets.toString(4) << std::endl;

    return 0;
}
