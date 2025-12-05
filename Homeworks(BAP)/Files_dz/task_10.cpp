#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
void createConfig() {
    std::ofstream file("config.json");
    file << "{\n";
    file << " \"app_name\": \"My Application\",\n";
    file << " \"version\": \"1.0.0\",\n";
    file << " \"settings\": {\n";
    file << " \"max_connections\": 100,\n";
    file << " \"timeout\": 30,\n";
    file << " \"debug_mode\": true\n";
    file << " },\n";
    file << " \"database\": {\n";
    file << " \"host\": \"localhost\",\n";
    file << " \"port\": 5432,\n";
    file << " \"username\": \"admin\"\n";
    file << " }\n";
    file << "}";
    file.close();
    std::cout << "Конфигурационный файл создан\n";
}

int main()
{
    createConfig();
    std::ifstream inFile("config.json");
    std::string line;
    int newTimeout;
    std::vector<std::string> lines;
    if (inFile.is_open()){
        while (std::getline(inFile, line)){
            cout << line << "\n";
            size_t pos = line.find("\"timeout\":");
        if (pos != std::string::npos) {
            size_t colonPos = line.find(':', pos);
            size_t commaPos = line.find(',', colonPos);
            
            if (commaPos == std::string::npos) {
                commaPos = line.length();
            }
            
            line = line.substr(0, colonPos + 1) + " " + std::to_string(newTimeout) + 
                   (commaPos < line.length() ? "," : "");
        }
        lines.push_back(line);
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    inFile.close();
    std::ofstream outFile("config.json");
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!\n";
    }
    
    for (size_t i = 0; i < lines.size(); ++i) {
        outFile << lines[i];
        if (i != lines.size() - 1) {
            outFile << "\n";
        }
    }
    
    outFile.close();
}