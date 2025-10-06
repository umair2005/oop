#include <iostream>

using namespace std;

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int binarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == x)
            return m;
        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

int interpolationSearch(int arr[], int n, int x) {
    int lo = 0, hi = (n - 1);
    while (lo <= hi && x >= arr[lo] && x <= arr[hi]) {
        if (lo == hi) {
            if (arr[lo] == x) return lo;
            return -1;
        }
        int pos = lo + (((double)(hi - lo) / (arr[hi] - arr[lo])) * (x - arr[lo]));

        if (arr[pos] == x)
            return pos;
        if (arr[pos] < x)
            lo = pos + 1;
        else
            hi = pos - 1;
    }
    return -1;
}

int main() {
    int sampleArr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(sampleArr) / sizeof(sampleArr[0]);

    cout << "--- Sorting Algorithms ---" << endl;

    int arr1[] = {170, 45, 75, 90, 802, 24, 2, 66};
    cout << "\nOriginal array: ";
    printArray(arr1, n);
    selectionSort(arr1, n);
    cout << "Array after Selection Sort: ";
    printArray(arr1, n);

    int arr2[] = {170, 45, 75, 90, 802, 24, 2, 66};
    cout << "\nOriginal array: ";
    printArray(arr2, n);
    insertionSort(arr2, n);
    cout << "Array after Insertion Sort: ";
    printArray(arr2, n);

    int arr3[] = {170, 45, 75, 90, 802, 24, 2, 66};
    cout << "\nOriginal array: ";
    printArray(arr3, n);
    radixSort(arr3, n);
    cout << "Array after Radix Sort: ";
    printArray(arr3, n);

    cout << "\n--- Searching Algorithms ---" << endl;
    cout << "Searching in the sorted array: ";
    printArray(arr3, n);

    int key_to_find = 90;
    int not_found_key = 100;
    
    int b_index = binarySearch(arr3, 0, n - 1, key_to_find);
    cout << "\nBinary Search for " << key_to_find << ": ";
    (b_index == -1) ? cout << "Element not found" << endl : cout << "Element found at index " << b_index << endl;

    b_index = binarySearch(arr3, 0, n - 1, not_found_key);
    cout << "Binary Search for " << not_found_key << ": ";
    (b_index == -1) ? cout << "Element not found" << endl : cout << "Element found at index " << b_index << endl;

    int i_index = interpolationSearch(arr3, n, key_to_find);
    cout << "\nInterpolation Search for " << key_to_find << ": ";
    (i_index == -1) ? cout << "Element not found" << endl : cout << "Element found at index " << i_index << endl;

    i_index = interpolationSearch(arr3, n, not_found_key);
    cout << "Interpolation Search for " << not_found_key << ": ";
    (i_index == -1) ? cout << "Element not found" << endl : cout << "Element found at index " << i_index << endl;

    return 0;
}