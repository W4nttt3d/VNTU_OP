#include <iostream>
#include <cctype>
#include <cstring>

int stringCompareCS(char* str1, char* str2) {
    while (*str1 && *str2) {
        if (*str1 < *str2) return -1;
        if (*str1 > *str2) return 1;
        str1++;
        str2++;
    }
    if (*str1 == *str2) return 0;
    return (*str1) ? 1 : -1;
}

int stringCompareCIS(char* str1, char* str2) {
    while (*str1 && *str2) {
        char c1 = std::tolower(*str1);
        char c2 = std::tolower(*str2);
        if (c1 < c2) return -1;
        if (c1 > c2) return 1;
        str1++;
        str2++;
    }
    if (*str1 == *str2) return 0;
    return (*str1) ? 1 : -1;
}

void inputString(char* str, int maxLength, const std::string& prompt) {
    do {
        std::cout << prompt;
        std::cin.getline(str, maxLength);
        if (std::strlen(str) == 0) {
            std::cout << "Invalid input. Please enter a non-empty string.\n";
        }
    } while (std::strlen(str) == 0);
}

void printResult(int res) {
    if (res == 0) std::cout << "Result: 0 (strings are equal)\n";
    else if (res == -1) std::cout << "Result:-1 (first string is lexicographically less)\n";
    else std::cout << "Result:1 (first string is lexicographically greater)\n";
}

int main() {
    const int MAX_LEN = 100;
    char user1[MAX_LEN];
    char user2[MAX_LEN];

    char test1[] = "Apple";
    char test2[] = "apple";
    char test3[] = "Banana";
    char test4[] = "Apple";
    char test5[] = "Apples";

    std::cout << "=== Case-sensitive comparisons with test strings ===\n";
    printResult(stringCompareCS(test1, test2));
    printResult(stringCompareCS(test1, test4));
    printResult(stringCompareCS(test1, test3));
    printResult(stringCompareCS(test5, test4));

    std::cout << "\n=== Case-insensitive comparisons with test strings ===\n";
    printResult(stringCompareCIS(test1, test2));
    printResult(stringCompareCIS(test1, test4));
    printResult(stringCompareCIS(test1, test3));
    printResult(stringCompareCIS(test5, test4));

    std::cout << "\n=== Now you can test your own strings ===\n";
    inputString(user1, MAX_LEN, "Enter first string: ");
    inputString(user2, MAX_LEN, "Enter second string: ");

    std::cout << "\nCase-sensitive comparison:\n";
    printResult(stringCompareCS(user1, user2));

    std::cout << "Case-insensitive comparison:\n";
    printResult(stringCompareCIS(user1, user2));

    return 0;
}
