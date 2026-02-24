#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Please input numbers to find average." << std::endl;
        return 0;
    }

    double sum = 0;
    int count = 0;

    for (int i = 1; i < argc; ++i) {
        try {
            sum += std::stod(argv[i]);
            count++;
        } catch (...) {
            continue;
        }
    }

    if (count > 0) {
        double average = sum / count;
        std::cout << "---------------------------------" << std::endl;
        std::cout << "Average of " << count << " numbers = " << average << std::endl;
        std::cout << "---------------------------------" << std::endl;
    }
    return 0;
}
