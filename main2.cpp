#include <iostream>
#include <vector>
#include <thread>     // Required for std::this_thread::sleep_for
#include <chrono>     // Required for std::chrono::milliseconds

void visualize(const std::vector<int>& arr, int highlight = -1) {
    for (int i = 0; i < arr.size(); i++) {
        if (i == highlight) {
            std::cout << "[" << arr[i] << "] ";
        } else {
            std::cout << arr[i] << " ";
        }
    }
    std::cout << std::endl;

    // Pause the program for 100 milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  
}

// Bubble Sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                visualize(arr, j);  // Visualize after every swap
            }
        }
    }
}

// Selection Sort
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
        visualize(arr, i);  // Visualize after every selection
    }
}

// Merge Sort Helper
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        visualize(arr, k);  // Visualize after merging
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        visualize(arr, k);
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        visualize(arr, k);
        j++;
        k++;
    }
}

// Merge Sort
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort Helper (Partition function)
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
            visualize(arr, i);  // Visualize after swap
        }
    }
    std::swap(arr[i + 1], arr[high]);
    visualize(arr, i + 1);  // Visualize after placing pivot
    return i + 1;
}

// Quick Sort
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Heap Sort Helper
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        visualize(arr, i);  // Visualize after heapify swap
        heapify(arr, n, largest);
    }
}

// Heap Sort
void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        visualize(arr, i);  // Visualize after each extraction
        heapify(arr, i, 0);
    }
}

// Main Function to Run Sorting Visualizations
int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    
    std::cout << "Original Array: ";
    visualize(arr);
    
    // Uncomment the sort you want to visualize:
    
    // bubbleSort(arr);
    // selectionSort(arr);
    // mergeSort(arr, 0, arr.size() - 1);
    // quickSort(arr, 0, arr.size() - 1);
    // heapSort(arr);
    
    std::cout << "Sorted Array: ";
    visualize(arr);
    return 0;
}
