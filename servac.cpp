#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

int main() {
    std::string message;
    int key;
    while (true) {
        std::ifstream infile("key.txt");
        if (infile.is_open()) {
            infile >> key;
            infile.close();
        }
        if(key == 1){
            std::ifstream infile("chat1.txt");
            if (infile.is_open()) {
                bool notEmpty = false; // это флаг
                while (std::getline(infile, message)) {
                    std::cout << message << std::endl;
                    notEmpty = true;
                    std::ofstream outfile("chat2.txt", std::ios_base::app); // Открываем файл для добавления
                    if (outfile.is_open()) {
                        outfile << message << std::endl;
                        outfile.close();
                    }
                }
                infile.close();
                
                if (notEmpty) {
                    std::ofstream outfile("chat1.txt", std::ios::trunc); // Открываем файл для очистки
                    outfile.close(); // Закрываем файл
                }
            }
        }
        
        else{
            std::ifstream infile("chat2.txt");
            if (infile.is_open()) {
                bool notEmpty = false; // это флаг
                while (std::getline(infile, message)) {
                    std::cout << message << std::endl;
                    notEmpty = true;
                    
                    std::ofstream outfile("chat1.txt", std::ios_base::app); // Открываем файл для добавления
                    if (outfile.is_open()) {
                        outfile << message << std::endl;
                        outfile.close();
                    }
                }
                infile.close();
                
                if (notEmpty) {
                    std::ofstream outfile("chat2.txt", std::ios::trunc); // Открываем файл для очистки
                    outfile.close(); // Закрываем файл
                }
            }
        }
    }
    return 0;
}