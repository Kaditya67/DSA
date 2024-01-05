#include <iostream>

class MyArray {
private:
    struct ArrayData {
        int total_size;
        int used_size;
        int *ptr;
    };

    ArrayData *data;

public:
    MyArray(int tsize, int usize) {
        if (usize > tsize) {
            std::cout << "\nError: Used Size should be less than Total Size\n";
            exit(0);
        }

        data = new ArrayData;
        data->total_size = tsize;
        data->used_size = usize;
        data->ptr = new int[tsize]; // Dynamic allocation on the heap
    }

    ~MyArray() {
        delete[] data->ptr; // Freeing memory for the array
        delete data;        // Freeing memory for the structure
    }

    void setVal() {
        std::cout << "\nSetting Values:\n";
        for (int i = 0; i < data->used_size; i++) {
            std::cout << "Enter the value for Element " << i + 1 << " : ";
            std::cin >> data->ptr[i];
        }
    }

    void show() {
        std::cout << "Displaying Elements:\n";
        for (int i = 0; i < data->used_size; i++) {
            std::cout << data->ptr[i] << std::endl;
        }
    }
};

int main() {
    int tsize, usize;

    std::cout << "Enter the size of array to be created: ";
    std::cin >> tsize;
    std::cout << "Enter the size of array to be used: ";
    std::cin >> usize;

    MyArray m(tsize, usize); // Automatic memory management using constructors and destructors
    m.setVal();              // Setting values
    m.show();                // Display the elements

    return 0;
}
