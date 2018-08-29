/**
 * @author Max Van Houcke
 */

#include "../include/JsonObject.h"

JsonElement JsonObject::operator[](const std::string &member) {
    for (const auto& elem: elements) {
        if (elem.first == member) {
            return elem.second;
        }
    }
}
