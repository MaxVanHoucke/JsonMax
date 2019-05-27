/**
 * @author Max Van Houcke
 */

#include <string>
#include <fstream>


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


std::string fromCpp(const std::string& filename) {
    std::string content = fileToString(filename);
    std::string usingStatement = "using namespace JsonMax;";
    auto pos = content.find(usingStatement);
    return content.substr(pos + usingStatement.size());
}

std::string fromHeader(const std::string& filename) {
    std::string content = fileToString(filename);
    std::string namespaceStatement = "namespace JsonMax {";
    auto pos = content.find(namespaceStatement);
    content = content.substr(pos + namespaceStatement.size());
    return content.substr(0, content.rfind('}'));
}


int main() {

    std::string filename = "../../single_include/JsonMax.h";
    std::ofstream out(filename);

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
    out << "}" << std::endl;
    out << "using namespace JsonMax;" << std::endl;
    out << fromCpp("../../src/Element.cpp");
    out << fromCpp("../../src/Pair.cpp");
    out << fromCpp("../../src/Object.cpp");
    out << fromCpp("../../src/Parser.cpp");
    out << fromCpp("../../src/Tools.cpp");
    out << fromCpp("../../src/Type.cpp");
    out << "#endif //JSONMAX_H" << std::endl;

    return 0;
}
