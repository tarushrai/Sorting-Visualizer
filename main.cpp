#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

// Function to visualize the array
void visualize(const std::vector<int>& arr, int highlight = -1) {
    for (int i = 0; i < arr.size(); i++) {
        if (i == highlight) {
            std::cout << "[" << arr[i] << "] ";
        } else {
            std::cout << arr[i] << " ";
        }
    }
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Slow down for visualization
}

// Bubble Sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
            visualize(arr, j);
        }
    }
}

// Selection Sort
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
            visualize(arr, j);
        }
        std::swap(arr[min_idx], arr[i]);
        visualize(arr, i);
    }
}

// Merge Sort Helper Functions
void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i++];
        } else {
            arr[k] = R[j++];
        }
        visualize(arr, k);
        k++;
    }

    while (i < n1) {
        arr[k++] = L[i++];
        visualize(arr, k);
    }

    while (j < n2) {
        arr[k++] = R[j++];
        visualize(arr, k);
    }
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Quick Sort Helper Functions
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
        visualize(arr, j);
    }
    std::swap(arr[i + 1], arr[high]);
    visualize(arr, i + 1);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Heap Sort Helper Functions
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        visualize(arr, i);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        visualize(arr, i);
        heapify(arr, i, 0);
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    std::cout << "Original Array: ";
    visualize(arr);

    std::cout << "\nBubble Sort:\n";
    bubbleSort(arr);

    arr = {12, 11, 13, 5, 6, 7};
    std::cout << "\nSelection Sort:\n";
    selectionSort(arr);

    arr = {12, 11, 13, 5, 6, 7};
    std::cout << "\nMerge Sort:\n";
    mergeSort(arr, 0, arr.size() - 1);

    arr = {12, 11, 13, 5, 6, 7};
    std::cout << "\nQuick Sort:\n";
    quickSort(arr, 0, arr.size() - 1);

    arr = {12, 11, 13, 5, 6, 7};
    std::cout << "\nHeap Sort:\n";
    heapSort(arr);

    return 0;
}
