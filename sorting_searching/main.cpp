#include <cstddef>
#include <iostream>
#include <vector>

void printArray(const char* title, const std::vector<int>& values) {
    std::cout << title;
    for (int value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

std::size_t insertionSort(std::vector<int>& values) {
    std::size_t comparisons = 0;

    for (std::size_t i = 1; i < values.size(); ++i) {
        const int key = values[i];
        std::size_t j = i;

        while (j > 0) {
            ++comparisons;
            if (values[j - 1] <= key) {
                break;
            }
            values[j] = values[j - 1];
            --j;
        }
        values[j] = key;
    }

    return comparisons;
}

// Sorts the range [left, right).
void mergeSortRange(std::vector<int>& values, std::vector<int>& buffer,
                    std::size_t left, std::size_t right) {
    if (right - left < 2) {
        return;
    }

    const std::size_t mid = left + (right - left) / 2;
    mergeSortRange(values, buffer, left, mid);
    mergeSortRange(values, buffer, mid, right);

    std::size_t i = left;
    std::size_t j = mid;
    std::size_t k = left;

    while (i < mid && j < right) {
        if (values[i] <= values[j]) {
            buffer[k++] = values[i++];
        } else {
            buffer[k++] = values[j++];
        }
    }
    while (i < mid) {
        buffer[k++] = values[i++];
    }
    while (j < right) {
        buffer[k++] = values[j++];
    }

    for (k = left; k < right; ++k) {
        values[k] = buffer[k];
    }
}

void mergeSort(std::vector<int>& values) {
    std::vector<int> buffer(values.size());
    mergeSortRange(values, buffer, 0, values.size());
}

std::ptrdiff_t linearSearch(const std::vector<int>& values, int key) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (values[i] == key) {
            return static_cast<std::ptrdiff_t>(i);
        }
    }
    return -1;
}

// Expects values sorted in ascending order.
std::ptrdiff_t binarySearch(const std::vector<int>& values, int key) {
    std::size_t left = 0;
    std::size_t right = values.size();

    while (left < right) {
        const std::size_t mid = left + (right - left) / 2;

        if (values[mid] == key) {
            return static_cast<std::ptrdiff_t>(mid);
        }
        if (values[mid] < key) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return -1;
}

// Expects both vectors sorted in ascending order.
std::vector<int> mergeArrays(const std::vector<int>& first,
                             const std::vector<int>& second) {
    std::vector<int> merged;
    merged.reserve(first.size() + second.size());

    std::size_t i = 0;
    std::size_t j = 0;
    while (i < first.size() && j < second.size()) {
        if (first[i] <= second[j]) {
            merged.push_back(first[i++]);
        } else {
            merged.push_back(second[j++]);
        }
    }
    while (i < first.size()) {
        merged.push_back(first[i++]);
    }
    while (j < second.size()) {
        merged.push_back(second[j++]);
    }

    return merged;
}

int main() {
    const std::vector<int> input = {4, 7, 1, 9, 3, 6};
    const int key = 9;
    const int missing = 99;

    printArray("Input: ", input);

    std::vector<int> insertionResult = input;
    const auto comparisons = insertionSort(insertionResult);
    printArray("Insertion sort: ", insertionResult);
    std::cout << "Comparisons (insertion): " << comparisons << '\n';

    std::vector<int> mergeResult = input;
    mergeSort(mergeResult);
    printArray("Merge sort: ", mergeResult);

    std::cout << "Linear search " << key << ": index "
              << linearSearch(input, key) << " (original vector)\n";
    std::cout << "Binary search " << key << ": index "
              << binarySearch(mergeResult, key) << " (sorted vector)\n";
    std::cout << "Binary search " << missing << ": "
              << binarySearch(mergeResult, missing) << '\n';

    const std::vector<int> first = {1, 5, 8};
    const std::vector<int> second = {2, 3, 7, 10};
    printArray("Merge: ", mergeArrays(first, second));
}