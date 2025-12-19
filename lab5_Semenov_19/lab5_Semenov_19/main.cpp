#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>


int inputPositiveInt(const std::string& prompt) 
{
    int value;
    do 
    {
        std::cout << prompt;
        std::cin >> value;
        if (value <= 0) 
        {
            std::cout << "Invalid input. Please enter a positive integer.\n";
        }
    } while (value <= 0);
    return value;
}

void generateMatrix(std::vector<std::vector<int>>& a, int n, int m) 
{
    a.resize(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            a[i][j] = std::rand() % 21 - 10;
        }
    }
}

void printMatrix(const std::vector<std::vector<int>>& a) 
{
    for (const auto& row : a) 
    {
        for (int x : row) 
        {
            std::cout << x << "\t";
        }
        std::cout << std::endl;
    }
}

long long columnProduct(const std::vector<std::vector<int>>& a, int col) 
{
    long long product = 1;
    for (const auto& row : a) 
    {
        product *= row[col];
    }
    return product;
}

int findMinProductColumn(const std::vector<std::vector<int>>& a) 
{
    int m = static_cast<int>(a[0].size());
    int minCol = 0;
    long long minProduct = columnProduct(a, 0);

    for (int j = 1; j < m; j++) 
    {
        long long currentProduct = columnProduct(a, j);
        if (currentProduct < minProduct) 
        {
            minProduct = currentProduct;
            minCol = j;
        }
    }
    return minCol;
}

int main() 
{
    int n = inputPositiveInt("Enter number of rows (positive integer): ");
    int m = inputPositiveInt("Enter number of columns (positive integer): ");

    std::vector<std::vector<int>> matrix;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    generateMatrix(matrix, n, m);

    std::cout << "\nGenerated matrix:\n";
    printMatrix(matrix);

    int minCol = findMinProductColumn(matrix);

    std::cout << "\nColumn with minimum product: " << minCol + 1 << std::endl;
    std::cout << "Minimum product value: " << columnProduct(matrix, minCol) << std::endl;

    return 0;
}
