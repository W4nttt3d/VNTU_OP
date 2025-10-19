#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    void* array;
    size_t size;
    size_t capacity;
    size_t elemSize;
} DynamicArray;

void initDynamicArray(DynamicArray* array, size_t elemSize)
{
    array->array = NULL;
    array->size = 0;
    array->capacity = 0;
    array->elemSize = elemSize;
}

void initDynamicArrayWithSize(DynamicArray* array, size_t elemSize, size_t size)
{
    array->array = calloc(size, elemSize);
    array->size = size;
    array->capacity = size;
    array->elemSize = elemSize;
}

void DelDynamicArray(DynamicArray* array)
{
    free(array->array);
    array->array = NULL;
    array->size = 0;
    array->capacity = 0;
}

void assign(const DynamicArray* src, DynamicArray* dest)
{
    if(src == dest) return;

    DelDynamicArray(dest);
    dest->size = src->size;
    dest->capacity = src->capacity;
    dest->elemSize = src->elemSize;
    dest->array = malloc(src->capacity * src->elemSize);
    memcpy(dest->array, src->array, src->size * src->elemSize);
}

void* at(DynamicArray* array, size_t index)
{
    if(index >= array->size)
    {
        fprintf(stderr, "Index out of range\n");
        exit(EXIT_FAILURE);
    }
    return (char*)array->array + index * array->elemSize;
}

void reserve(DynamicArray* array, size_t newCapacity)
{
    if(newCapacity <= array->capacity) return;

    void* newArray = calloc(newCapacity, array->elemSize);
    if(array->array)
    {
        memcpy(newArray, array->array, array->size * array->elemSize);
        free(array->array);
    }
    array->array = newArray;
    array->capacity = newCapacity;
}

void setSize(DynamicArray* array, size_t newSize)
{
    if (newSize > array->capacity)
    {
        reserve(array, newSize);
    }

    if(newSize < array->size)
    {
        memset((char*)array->array + newSize * array->elemSize, 0, (array->size - newSize) * array->elemSize);
    }

    array->size = newSize;
}

size_t getSize(const DynamicArray* array)
{
    return array->size;
}

size_t getCapacity(const DynamicArray* array)
{
    return array->capacity;
}

void clear(DynamicArray* array)
{
    if(array->array)
    {
        memset(array->array, 0, array->size * array->elemSize);
    }
    array->size = 0;
}

void push_back(DynamicArray* array, const void* element)
{
    if(array->size >= array->capacity)
    {
        reserve(array, array->capacity == 0 ? 1 : array->capacity*2);
    }

    memcpy((char *)array->array + array->size * array->elemSize, element, array->elemSize);
    array->size++;
}

void pop_back(DynamicArray* array)
{
    if (array->size == 0)
    {
        fprintf(stderr, "Array is empty\n");
        exit(EXIT_FAILURE);
    }
    array->size--;
    memset((char*)array->array + array->size * array->elemSize, 0, array->elemSize);
}

void* back(DynamicArray* array)
{
    if(array->size == 0)
    {
        fprintf(stderr, "Array is empty\n");
        exit(EXIT_FAILURE);
    }
    return at(array, array->size - 1);
}

void shringToFit(DynamicArray* array)
{
    if(array->size < array->capacity)
    {
        void* newArray = malloc(array->size * array->elemSize);
        memcpy(newArray, array->array, array->size * array->elemSize);
        free(array->array);
        array->array = newArray;
        array->capacity = array->size;
    }
}

void inputArray(DynamicArray* array)
{
    size_t n;
    printf("Enter number of elements: ");
    scanf("%zu", &n);

    for(size_t i = 0; i < n; i++)
    {
        double num;
        printf("array[%zu] = ", i);
        scanf("%lf", &num);
        push_back(array, &num);
    }
}

double findClosestToInteger(const DynamicArray* array, double* outMinDiff)
{
    double closest = *(double*)at((DynamicArray*)array, 0);
    double minDiff = fabs(closest - round(closest));

    for(size_t i = 1; i < getSize(array); i++)
    {
        double current = *(double*)at((DynamicArray*)array, i);
        double diff = fabs(current - round(current));
        if(diff < minDiff)
        {
            minDiff = diff;
            closest = current;
        }
    }

    if(outMinDiff)
    {
        *outMinDiff = minDiff;
    }


    return closest;
}

int main(void) {
    DynamicArray arr;
    initDynamicArray(&arr, sizeof(int));

    printf("Initial size: %zu, capacity: %zu\n", getSize(&arr), getCapacity(&arr));

    // push_back
    for(int i = 1; i <= 5; i++) {
        push_back(&arr, &i);
        printf("After push_back %d: size = %zu, capacity = %zu\n", i, getSize(&arr), getCapacity(&arr));
    }

    // access elements with at
    printf("Elements using at(): ");
    for(size_t i = 0; i < getSize(&arr); i++) {
        printf("%d ", *(int*)at(&arr, i));
    }
    printf("\n");

    // back
    printf("Last element (back): %d\n", *(int*)back(&arr));

    // pop_back
    pop_back(&arr);
    printf("After pop_back: size = %zu, last element = %d\n", getSize(&arr), *(int*)back(&arr));

    // setSize larger
    setSize(&arr, 8);
    printf("After setSize(8): size = %zu, capacity = %zu\n", getSize(&arr), getCapacity(&arr));

    // setSize smaller
    setSize(&arr, 3);
    printf("After setSize(3): size = %zu, capacity = %zu\n", getSize(&arr), getCapacity(&arr));

    // clear
    clear(&arr);
    printf("After clear: size = %zu, capacity = %zu\n", getSize(&arr), getCapacity(&arr));

    // reserve
    reserve(&arr, 10);
    printf("After reserve(10): size = %zu, capacity = %zu\n", getSize(&arr), getCapacity(&arr));

    // push_back again
    int val = 42;
    push_back(&arr, &val);
    printf("After push_back 42: size = %zu, last element = %d\n", getSize(&arr), *(int*)back(&arr));

    // shrinkToFit
    shringToFit(&arr);
    printf("After shrinkToFit: size = %zu, capacity = %zu\n", getSize(&arr), getCapacity(&arr));

    // assign
    DynamicArray arr2;
    initDynamicArray(&arr2, sizeof(int));
    assign(&arr, &arr2);
    printf("After assign: arr2 size = %zu, last element = %d\n", getSize(&arr2), *(int*)back(&arr2));

    // cleanup
    DelDynamicArray(&arr);
    DelDynamicArray(&arr2);

    //Laboratory tasks
    printf("\n\n--- Laboratory task ---\n");

    DynamicArray array;
    initDynamicArray(&array, sizeof(double));

    inputArray(&array);

    double minDiff;
    double closest = findClosestToInteger(&array, &minDiff);

    printf("\nElement closest to an integer: %.4f\n", closest);
    printf("Distance to nearest integer: %.4f\n", minDiff);

    DelDynamicArray(&array);

    return 0;
}