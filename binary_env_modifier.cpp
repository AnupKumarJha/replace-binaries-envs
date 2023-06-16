A tool to replace local environment info in binaries

#include <iostream>
#include <fstream>
#include <regex>

// Function to replace path-like strings with shortened versions
std::string replacePathStrings(const std::string& originalString, const std::string& basePath) {
    // Replace the path with a shortened version relative to the base directory
    std::string shortenedPath = originalString;
    if (shortenedPath.find(basePath) == 0) {
        shortenedPath.replace(0, basePath.length(), ".");
    }
    return shortenedPath;
}

// Function to modify the binary by replacing path-like strings
void modifyBinary(const std::string& binaryPath, const std::string& basePath) {
    std::ifstream inputFile(binaryPath, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Failed to open binary file: " << binaryPath << std::endl;
        return;
    }

    // Read the entire binary into a string
    std::string binaryData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    // Define a regular expression to match path-like strings
    std::regex pathRegex(R"((\/\w+)*\/\w+\.\w+)");

    // Replace path-like strings in the binary data
    std::string modifiedBinaryData = binaryData;
    std::sregex_iterator it(binaryData.begin(), binaryData.end(), pathRegex);
    std::sregex_iterator end;
    while (it != end) {
        std::smatch match = *it;
        modifiedBinaryData.replace(match.position(), match.length(), replacePathStrings(match.str(), basePath));
        ++it;
    }

    // Write the modified binary back to the file
    std::ofstream outputFile(binaryPath, std::ios::binary | std::ios::trunc);
    if (!outputFile) {
        std::cerr << "Failed to write modified binary: " << binaryPath << std::endl;
        return;
    }
    outputFile.write(modifiedBinaryData.c_str(), modifiedBinaryData.length());

    std::cout << "Binary modification complete." << std::endl;
}

int main(int argc, char* argv[]) {
    // Check command-line arguments
    if (argc < 3) {
        std::cerr << "Usage: binary_modifier <binary_path> <base_directory>" << std::endl;
        return 1;
    }

    // Extract command-line arguments
    std::string binaryPath = argv[1];
    std::string basePath = argv[2];

    // Modify the binary
    modifyBinary(binaryPath, basePath);

    return 0;
}
