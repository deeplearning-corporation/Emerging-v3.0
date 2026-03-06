// emerging.cpp
// Emerging Programming Language Compiler
// Version 3.0
// Fixed for Visual C++

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <direct.h>
#include <sys/stat.h>
#include <windows.h>

class EmergingCompiler {
private:
    std::string version = "3.0";
    std::string compilerName = "emergingcompiler";
    std::vector<std::string> includePaths;
    std::map<std::string, std::string> parsedCode;
    
    // Windows文件系统操作的辅助函数
    bool fileExists(const std::string& filename) {
        struct stat buffer;
        return (stat(filename.c_str(), &buffer) == 0);
    }
    
    bool createDirectory(const std::string& path) {
        return (_mkdir(path.c_str()) == 0) || (errno == EEXIST);
    }
    
    bool removeFile(const std::string& filename) {
        return (remove(filename.c_str()) == 0);
    }
    
public:
    EmergingCompiler() {
        // 初始化包含路径
        includePaths.push_back("./include/");
        includePaths.push_back("./lib/");
    }
    
    void printVersion() {
        std::cout << "Emerging Programming Language version " << version << std::endl;
        std::cout << "Compiler: " << compilerName << std::endl;
        std::cout << "Developed for operating system development" << std::endl;
    }
    
    void printHelp() {
        std::cout << "Emerging Programming Language Compiler v" << version << std::endl;
        std::cout << "Usage: emerging [options] <file.emg>" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  --run <file.emg>              Run the Emerging program directly" << std::endl;
        std::cout << "  --emergingcompiler <file.emg>  Compile using emergingcompiler" << std::endl;
        std::cout << "  -out <file>                    Specify output file" << std::endl;
        std::cout << "  --binary                        Package as binary (.bin)" << std::endl;
        std::cout << "  --dos                          Package as DOS executable (.com)" << std::endl;
        std::cout << "  --version                      Show version information" << std::endl;
        std::cout << "  --help                         Show this help message" << std::endl;
    }
    
    std::string readFile(const std::string& filename) {
        std::ifstream file(filename.c_str());
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << filename << std::endl;
            return "";
        }
        
        std::string content;
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        file.close();
        return content;
    }
    
    bool writeFile(const std::string& filename, const std::string& content) {
        std::ofstream file(filename.c_str());
        if (!file.is_open()) {
            std::cerr << "Error: Cannot write to file " << filename << std::endl;
            return false;
        }
        
        file << content;
        file.close();
        return true;
    }
    
    std::string processUsingDirectives(const std::string& code) {
        std::string result = code;
        size_t pos = 0;
        
        while ((pos = result.find("using ", pos)) != std::string::npos) {
            size_t start = pos;
            size_t end = result.find("\n", start);
            std::string line = result.substr(start, end - start);
            
            // 解析 using "filename.h"
            size_t quote1 = line.find("\"");
            size_t quote2 = line.find("\"", quote1 + 1);
            
            if (quote1 != std::string::npos && quote2 != std::string::npos) {
                std::string headerFile = line.substr(quote1 + 1, quote2 - quote1 - 1);
                
                // 查找头文件
                bool found = false;
                for (const auto& path : includePaths) {
                    std::string fullPath = path + headerFile;
                    if (fileExists(fullPath)) {
                        std::string headerContent = readFile(fullPath);
                        result.replace(start, end - start, "// Included: " + headerFile + "\n" + headerContent);
                        found = true;
                        break;
                    }
                }
                
                if (!found) {
                    std::cerr << "Warning: Header file not found: " << headerFile << std::endl;
                }
            }
            pos = end;
        }
        
        return result;
    }
    
    std::string transformSyntax(const std::string& code) {
        std::string result = code;
        
        // 将 out("text") 转换为 emerging::out("text")
        size_t pos = 0;
        while ((pos = result.find("out(", pos)) != std::string::npos) {
            size_t end = result.find(")", pos);
            if (end != std::string::npos) {
                std::string content = result.substr(pos + 4, end - pos - 4);
                result.replace(pos, end - pos + 1, "emerging::out(" + content + ")");
            }
            pos += 10;
        }
        
        // 将 inb(port) 转换为 emerging::inb(port)
        pos = 0;
        while ((pos = result.find("inb(", pos)) != std::string::npos) {
            size_t end = result.find(")", pos);
            if (end != std::string::npos) {
                std::string content = result.substr(pos + 4, end - pos - 4);
                result.replace(pos, end - pos + 1, "emerging::inb(" + content + ")");
            }
            pos += 10;
        }
        
        // 将 outb(port, value) 转换为 emerging::outb(port, value)
        pos = 0;
        while ((pos = result.find("outb(", pos)) != std::string::npos) {
            size_t end = result.find(")", pos);
            if (end != std::string::npos) {
                std::string content = result.substr(pos + 5, end - pos - 5);
                result.replace(pos, end - pos + 1, "emerging::outb(" + content + ")");
            }
            pos += 11;
        }
        
        return result;
    }
    
    bool compileToExecutable(const std::string& inputFile, const std::string& outputFile, bool isBinary = false, bool isDOS = false) {
        std::string code = readFile(inputFile);
        if (code.empty()) return false;
        
        // 处理 using 指令
        code = processUsingDirectives(code);
        
        // 转换语法
        code = transformSyntax(code);
        
        // 添加底层操作系统开发支持
        std::string fullCode = "// Emerging Language v" + version + " Compiled Code\n";
        fullCode += "// Generated by emergingcompiler\n\n";
        fullCode += "#include <iostream>\n";
        fullCode += "#include <cstdint>\n";
        fullCode += "#include <cstring>\n\n";
        
        // 添加底层内存访问函数
        fullCode += "namespace emerging {\n";
        fullCode += "    inline void out(const char* str) { std::cout << str; }\n";
        fullCode += "    inline void out(int num) { std::cout << num; }\n";
        fullCode += "    inline void out(unsigned int num) { std::cout << num; }\n";
        
        // 内联汇编版本 - 仅用于x86
        fullCode += "    inline uint8_t inb(uint16_t port) {\n";
        fullCode += "        uint8_t value;\n";
        fullCode += "        __asm {\n";
        fullCode += "            mov dx, port\n";
        fullCode += "            in al, dx\n";
        fullCode += "            mov value, al\n";
        fullCode += "        }\n";
        fullCode += "        return value;\n";
        fullCode += "    }\n";
        
        fullCode += "    inline void outb(uint16_t port, uint8_t value) {\n";
        fullCode += "        __asm {\n";
        fullCode += "            mov dx, port\n";
        fullCode += "            mov al, value\n";
        fullCode += "            out dx, al\n";
        fullCode += "        }\n";
        fullCode += "    }\n";
        fullCode += "}\n\n";
        
        fullCode += "using namespace emerging;\n\n";
        fullCode += "int main() {\n";
        fullCode += code;
        fullCode += "\n    return 0;\n}\n";
        
        // 生成临时C++文件
        std::string tempFile = "temp_emerging.cpp";
        if (!writeFile(tempFile, fullCode)) return false;
        
        // 编译C++代码
        std::string compileCmd;
        if (isDOS) {
            compileCmd = "cl /c /Ox /arch:IA32 " + tempFile + " /Fotemp.obj && link temp.obj /OUT:" + outputFile + ".com /SUBSYSTEM:CONSOLE";
        } else if (isBinary) {
            compileCmd = "cl /c /Ox /arch:IA32 /FA " + tempFile + " && link temp.obj /OUT:" + outputFile + ".bin /SUBSYSTEM:CONSOLE /ENTRY:main /NODEFAULTLIB";
        } else {
            compileCmd = "cl /EHsc " + tempFile + " /Fe" + outputFile + ".exe";
        }
        
        std::cout << "Compiling with emergingcompiler..." << std::endl;
        int result = system(compileCmd.c_str());
        
        // 清理临时文件
        removeFile(tempFile);
        removeFile("temp.obj");
        
        return result == 0;
    }
    
    bool runDirectly(const std::string& inputFile) {
        std::string exeFile = "temp_run.exe";
        if (compileToExecutable(inputFile, exeFile)) {
            std::cout << "Running " << inputFile << "..." << std::endl;
            std::string runCmd = exeFile;
            system(runCmd.c_str());
            removeFile(exeFile);
            return true;
        }
        return false;
    }
    
    void createDirectories() {
        createDirectory("lib");
        createDirectory("doc");
        createDirectory("include");
        createDirectory("emergingcompiler");
    }
};

int main(int argc, char* argv[]) {
    EmergingCompiler compiler;
    
    if (argc < 2) {
        compiler.printHelp();
        return 1;
    }
    
    // 创建必要的目录
    compiler.createDirectories();
    
    std::string command = argv[1];
    
    if (command == "--version") {
        compiler.printVersion();
        return 0;
    }
    
    if (command == "--help") {
        compiler.printHelp();
        return 0;
    }
    
    if (command == "--run" && argc >= 3) {
        std::string file = argv[2];
        if (compiler.runDirectly(file)) {
            std::cout << "Program executed successfully." << std::endl;
        } else {
            std::cerr << "Failed to run program." << std::endl;
            return 1;
        }
        return 0;
    }
    
    if (command == "--emergingcompiler" && argc >= 3) {
        std::string inputFile = argv[2];
        std::string outputFile = "output";
        bool isBinary = false;
        bool isDOS = false;
        
        // 解析选项
        for (int i = 3; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-out" && i + 1 < argc) {
                outputFile = argv[++i];
            } else if (arg == "--binary") {
                isBinary = true;
            } else if (arg == "--dos") {
                isDOS = true;
            }
        }
        
        std::string extension;
        if (isDOS) extension = ".com";
        else if (isBinary) extension = ".bin";
        else extension = ".exe";
        
        if (compiler.compileToExecutable(inputFile, outputFile, isBinary, isDOS)) {
            std::cout << "Successfully compiled to " << outputFile << extension << std::endl;
        } else {
            std::cerr << "Compilation failed." << std::endl;
            return 1;
        }
        return 0;
    }
    
    compiler.printHelp();
    return 1;
}
