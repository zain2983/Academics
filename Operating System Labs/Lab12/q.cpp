#include <iostream>
#include <fstream>
#include <thread>
#include <sys/mman.h>

void changeCase(char* start, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        if (isalpha(start[i])) {
            if (islower(start[i])) {
                start[i] = toupper(start[i]);
            } else {
                start[i] = tolower(start[i]);
            }
        }
    }
}

void processFile(char* map) {
    // Assuming 100 bytes in the file
    size_t halfLength = 50;

    std::thread thread1(changeCase, map, halfLength);
    std::thread thread2(changeCase, map + halfLength, halfLength);

    thread1.join();
    thread2.join();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);


    char* map = static_cast<char*>(mmap(nullptr, 100, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));

    if (map == MAP_FAILED) {
        std::cerr << "Error creating memory map." << std::endl;
        return 1;
    }

    file.read(map, fileSize);
    file.close();

    processFile(map);

    // Output the modified content
    std::cout << "Modified Content: " << std::endl;
    std::cout.write(map, fileSize);

    munmap(map, 100);

    return 0;
}
