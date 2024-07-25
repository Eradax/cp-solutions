#include <iostream>
#include <array>

int main() {
    // Define an array of size 5 (for example)
    std::array<int, 5> myArray = {0}; // Initialize all elements to 0

    // Read an integer from the user
    int input;
    std::cout << "Enter an integer: ";
    std::cin >> input;

    // Set the first element of the array to the input value
    myArray[0] = input;

    // Output the array to verify the value is set
    std::cout << "Array contents: ";
    for (int i = 0; i < myArray.size(); ++i) {
        std::cout << myArray[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
