/**
 * @author Max Van Houcke
 * Converts all the source and header files into a single include header
 */

#include <string>
#include <fstream>
#include <sstream>


/// Converts a file into a single string
std::string fileToString(const std::string& filename) {
    std::string str;
    std::ifstream in(filename);
    if (not in.good()) {
        return "";
    }

    std::string line;
    while (std::getline(in, line)) {
        str += line + "\n";
    }
    return str;
}


/// Returns the actual code in a cpp file
std::string fromCpp(const std::string& filename) {
    std::string content = fileToString(filename);
    std::string usingStatement = "using namespace JsonMax;";
    auto pos = content.find(usingStatement);
    return content.substr(pos + usingStatement.size());
}


/// Returns the actual code/declarations in a header file
std::string fromHeader(const std::string& filename) {
    std::string content = fileToString(filename);
    std::string namespaceStatement = "namespace JsonMax {";
    auto pos = content.find(namespaceStatement);
    content = content.substr(pos + namespaceStatement.size());
    return content.substr(0, content.rfind('}'));
}


/// Removes the JsonMax:: in the given string to prevent compilation errors
void removeNamespace(std::string& str) {
    size_t pos = 0;
    std::string toRemove = "JsonMax::";
    while ((pos = str.find(toRemove, pos)) != std::string::npos) {
        str.replace(pos, toRemove.size(), "");
    }
}


int main() {

    std::string root = "../../../";
    std::string filename = root + "single_include/JsonMax.h";
    std::string license = root + "LICENSE";
    std::ostringstream out;

    // Add license comment
    out << "/*" << std::endl << fileToString(license) << "*/\n" << std::endl;

    // Includes and include guard
    out << "#ifndef JSONMAX_H\n"
           "#define JSONMAX_H\n"
           "\n"
           "#include <string>\n"
           "#include <vector>\n"
           "#include <map>\n"
           "#include <unordered_map>\n"
           "#include <sstream>\n"
           "#include <fstream>\n\n";

    out << "namespace JsonMax {" << std::endl;
    out << fromHeader(root + "src/json_max/Object.h");
    out << fromHeader(root + "src/json_max/Type.h");
    out << fromHeader(root + "src/json_max/Element.h");
    out << fromHeader(root + "src/json_max/Pair.h");
    out << fromHeader(root + "src/json_max/parser/Parser.h");
    out << fromHeader(root + "src/json_max/Tools.h");
    out << fromHeader(root + "src/json_max/Exceptions.h");
    out << fromCpp(root + "src/json_max/Element.cpp");
    out << fromCpp(root + "src/json_max/Pair.cpp");
    out << fromCpp(root + "src/json_max/Object.cpp");
    out << fromCpp(root + "src/json_max/parser/Parser.cpp");
    out << fromCpp(root + "src/json_max/Tools.cpp");
    out << fromCpp(root + "src/json_max/Type.cpp");
    out << "} // namespace JsonMax" << std::endl;
    out << "#endif //JSONMAX_H" << std::endl;

    std::string output = out.str();
    removeNamespace(output);

    std::ofstream file(filename);
    file << output;
    file.close();

    return 0;
}
