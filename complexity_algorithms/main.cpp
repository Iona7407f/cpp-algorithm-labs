#include <cstdint>
#include <iostream>
#include <vector>

struct Result {
    std::int64_t sum = 0;
    std::int64_t steps = 0;
    bool limitExceeded = false;
};

constexpr std::int64_t maxSteps = 10'000'000;

// n is a non-negative integer.
// O(1):
Result func_A(int n) {
    const std::int64_t count = n;

    Result result;
    result.sum = count * (count + 1) / 2;
    result.steps = 1;
    return result;
}

// O(n):
Result func_B(int n) {
    Result result;

    for (std::int64_t i = 1; i <= n; ++i) {
        result.sum += i;
        ++result.steps;
    }

    return result;
}

// O(log n):
Result func_L(int n) {
    Result result;

    for (int j = n; j > 1; j /= 2) {
        ++result.steps;
    }

    return result;
}

// O(n log n):
Result func_D(int n) {
    Result result;

    for (int i = 0; i < n; ++i) {
        for (int j = n; j > 1; j /= 2) {
            ++result.steps;
        }
    }

    return result;
}

// O(n^2):
Result func_C(int n) {
    Result result;

    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            ++result.steps;
        }
    }

    return result;
}

// O(2^n):
Result func_E(int n) {
    Result result;
    std::int64_t limit = 1;

    for (int i = 0; i < n; ++i) {
        if (limit > maxSteps / 2) {
            result.limitExceeded = true;
            return result;
        }
        limit *= 2;
    }

    for (std::int64_t k = 0; k < limit; ++k) {
        ++result.steps;
    }

    return result;
}


// O(n!):
Result func_F(int n) {
    Result result;
    std::int64_t limit = 1;

    for (std::int64_t i = 2; i <= n; ++i) {
        if (limit > maxSteps / i) {
            result.limitExceeded = true;
            return result;
        }
        limit *= i;
    }

    for (std::int64_t k = 0; k < limit; ++k) {
        ++result.steps;
    }

    return result;
}

void printResults(const char* title, Result (*run)(int),
                  const std::vector<int>& inputs, bool showSum = false) {
    std::cout << "\n--- " << title << " ---\n";

    for (int n : inputs) {
        const Result result = run(n);
        std::cout << "n=" << n;

        if (result.limitExceeded) {
            std::cout << "\tStep limit exceeded\n";
            continue;
        }

        if (showSum) {
            std::cout << "\tSum=" << result.sum;
        }

        std::cout << "\tSteps=" << result.steps << '\n';
    }
}

int main() {
    const std::vector<int> inputs = {100, 200, 400, 800, 1600, 3200};
    const std::vector<int> exponentialInputs = {8, 10, 12, 14, 16, 18};
    const std::vector<int> factorialInputs = {4, 5, 6, 7, 8, 9};

    printResults("Function A (O(1))", func_A, inputs, true);
    printResults("Function B (O(n))", func_B, inputs, true);
    printResults("Function L (O(log n))", func_L, inputs);
    printResults("Function C (O(n^2))", func_C, inputs);
    printResults("Function D (O(n log n))", func_D, inputs);
    printResults("Function E (O(2^n))", func_E, exponentialInputs);
    printResults("Function F (O(n!))", func_F, factorialInputs);
}