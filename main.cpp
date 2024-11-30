#include <iostream>
#include <stdexcept>
#include <cstdlib> 
#include <ctime>   

template <typename T>
class GenericArray {
private:
    T* data;          //* to dynamic array
    int capacity;     //Current size
    int length;       //Current # elements

    //Reallocate array
    void resize(int new_capacity) {
        T* new_data = new T[new_capacity];
        for (int i = 0; i < length; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    //Constructor
    GenericArray() : data(nullptr), capacity(0), length(0) {}

    //Destructor
    ~GenericArray() {
        delete[] data;
    }

    //Add
    void addElement(const T& value) {
        if (length == capacity) {
            resize((capacity == 0) ? 1 : capacity * 2);
        }
        data[length++] = value;
    }

    //Return specific index
    T at(int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    //Return size
    int size() const {
        return length;
    }

    //Return sum
    T sum() const {
        T total = 0;
        for (int i = 0; i < length; i++) {
            total += data[i];
        }
        return total;
    }

    //Return max
    T max() const {
        if (length == 0) {
            throw std::runtime_error("Array empty");
        }
        T max_val = data[0];
        for (int i = 1; i < length; i++) {
            if (data[i] > max_val) {
                max_val = data[i];
            }
        }
        return max_val;
    }

    //Return min
    T min() const {
        if (length == 0) {
            throw std::runtime_error("Array empty");
        }
        T min_val = data[0];
        for (int i = 1; i < length; i++) {
            if (data[i] < min_val) {
                min_val = data[i];
            }
        }
        return min_val;
    }

    // Return slice 
    T* slice(int begin, int end) const {
        if (begin < 0 || end >= length || begin > end) {
            throw std::out_of_range("Invalid slice bounds");
        }
        int slice_length = end - begin + 1;
        T* slice_data = new T[slice_length];
        for (int i = 0; i < slice_length; i++) {
            slice_data[i] = data[begin + i];
        }
        return slice_data;
    }
};

int main() {
    
    std::srand(std::time(0));

    GenericArray<int> int_array;

    int_array.addElement(10);
    int_array.addElement(20);
    int_array.addElement(30);
    int_array.addElement(40);
    int_array.addElement(50);

    //5 random elements
    for (int i = 0; i < 5; i++) {
        int random_value = std::rand() % 100; 
        int_array.addElement(random_value);
    }

    //Display size
    std::cout << "Size of array: " << int_array.size() << std::endl;

    //Display sum
    std::cout << "Sum of array: " << int_array.sum() << std::endl;

    //Display max and min 
    std::cout << "Max of array: " << int_array.max() << std::endl;
    std::cout << "Min of array: " << int_array.min() << std::endl;

    //Display sliced 
    try {
        int* sliced_array = int_array.slice(2, 7);
        std::cout << "Sliced array (index 2 to 7): ";
        for (int i = 0; i < (7 - 2 + 1); i++) {
            std::cout << sliced_array[i] << " ";
        }
        std::cout << std::endl;

        //Free memory
        delete[] sliced_array;
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
