#include <filesystem>
#include <fstream>
#include "json2hpp.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4)
    {
        printf("Usage: json2cpp <name> <input.json> <output.hpp>\n");
        return -1;
    }

    std::string name = argv[1];
    std::filesystem::path input = argv[2];
    std::filesystem::path output = argv[3];

    if (!std::filesystem::exists(input))
    {
        printf("Error: Input file does not exist\n");
        printf("%s\n", input.filename().c_str());
    }

    input = std::filesystem::absolute(input);
    output = std::filesystem::absolute(output);

    std::ifstream in{ input };

    std::string json{ std::istreambuf_iterator<char>{ in }, std::istreambuf_iterator<char>{} };

    auto res = kaixo::json::parse(json);
    if (!res)
    {
        printf("Error: No output generated\n");
        return -1;
    }

    std::ofstream out{ output };
    out << kaixo::json2hpp::generate(name, res.value());
    return 0;
}
