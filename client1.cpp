#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

void kode(int &cif, std::string &str) {
    int cif_array[3];
    cif_array[0] = cif / 100 % 10;
    cif_array[1] = cif / 10 % 10;
    cif_array[2] = cif % 10;

    int index = 0;
    // Шифрование
    for (std::size_t i = 0; i < str.length(); i++) {
        str[i] += cif_array[index];
        index = (index + 1) % 3; 
    }
}
void dekode(int &cif, std::string &str) {
    int cif_array[3];
    cif_array[0] = cif / 100 % 10;
    cif_array[1] = cif / 10 % 10;
    cif_array[2] = cif % 10;

    int index = 0;
    // декод
    for (std::size_t i = 0; i < str.length(); i++) {
        str[i] -= cif_array[index];
        index = (index + 1) % 3; 
    }
}


int main() {
    std::cout << "Приветствую, товарищ! Этот чат работает по принципу радио. Для работы с ним необходимо знать 2 команды: \n" <<
"1) приём - передать возможность писать своему собеседнику \n" <<
"2) конец связи - окончить разговор \n";
    std::string message;
    int key;
    std::ifstream infile("key.txt");
    if (infile.is_open()) {
        infile >> key;
        infile.close();
    }
    if(key == 0) {
        key = 1;
        std::ofstream outfile("key.txt");
        if (outfile.is_open()) {
            outfile << key;
            outfile.close();
        }
    }
    //ввод ключа 
    std::cout << "\nВведите ключ шифра(3 цифры): ";
    int sif = 0;
    std::cin >> sif; 
    if (sif >= 1000 || sif <= 99) {std::cout << "\nНеверный ключ, пока";return 0;}


    while (true) {
        while(key == 2){
            bool notEmpty = false;
            std::ifstream infile("chat1.txt");
            if (infile.is_open()) {
                while (std::getline(infile, message)) {
                    if(!message.empty()){
                        dekode(sif, message);
                        std::cout << message << std::endl;

                        if(message == "Клиент 2: приём"){key = 1;}
                        if(message == "Клиент 2: конец связи"){key = 0;}

                        std::ofstream outfile("key.txt");
                        if (outfile.is_open()) {
                            outfile << key;
                            outfile.close();
                        }
                        notEmpty = true;
                    }
                }
                infile.close();
    
                if (notEmpty) {
                    std::ofstream outfile("chat1.txt", std::ios::trunc);
                    outfile.close();
                }
            }
        }
        while(key == 1) {
            std::cout << "Клиент 1: ";
            std::getline(std::cin, message);
                        
            // Запись в .txt
            std::ofstream outfile("chat1.txt", std::ios_base::app); 
            if (outfile.is_open()) {
                

                if(message == "приём"){ key = 2; }
                if(message == "конец связи"){ key = 0; }

                message = "Клиент 1: " + message;
                kode(sif, message);

                outfile << message << std::endl;

                std::ofstream outfile("key.txt");
                if (outfile.is_open()) {
                    outfile << key;
                    outfile.close();
                }
                outfile.close();
            }
        }

        if(key == 0) { break; }
    }
}
