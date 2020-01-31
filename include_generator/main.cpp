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

    std::string filename = "../../single_include/JsonMax.h";
    std::ostringstream out;

    // Add license comment
    out << "/*" << std::endl << fileToString("../../LICENSE") << "*/\n" << std::endl;

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
    out << fromHeader("../../src/Object.h");
    out << fromHeader("../../src/Type.h");
    out << fromHeader("../../src/Element.h");
    out << fromHeader("../../src/Pair.h");
    out << fromHeader("../../src/Parser.h");
    out << fromHeader("../../src/Tools.h");
    out << fromHeader("../../src/Exceptions.h");
    out << fromCpp("../../src/Element.cpp");
    out << fromCpp("../../src/Pair.cpp");
    out << fromCpp("../../src/Object.cpp");
    out << fromCpp("../../src/Parser.cpp");
    out << fromCpp("../../src/Tools.cpp");
    out << fromCpp("../../src/Type.cpp");
    out << "} // namespace JsonMax" << std::endl;
    out << "#endif //JSONMAX_H" << std::endl;

    std::string output = out.str();
    removeNamespace(output);

    std::ofstream file(filename);
    file << output;
    file.close();

    return 0;
}
