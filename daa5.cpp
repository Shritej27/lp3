#include <bits/stdc++.h>
using namespace std;

// Partition: First element as pivot (Two-pointer method)
int partitionArray(vector<int>& arr, int low, int high) {

    int pivot = arr[low];

    int i = low;
    int j = high;

    while (i < j) {

        // Move i towards right
        while (i < high && arr[i] <= pivot) {
            i++;
        }

        // Move j towards left
        while (j > low && arr[j] > pivot) {
            j--;
        }

        // Swap misplaced elements
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }

    // Place pivot at correct position
    swap(arr[low], arr[j]);
    for(int k=0;k<arr.size();k++){
        cout<<arr[k]<<" ";
    }
    cout<<endl;
    return j;
}

// Deterministic Quick Sort
void quickSort(vector<int>& arr, int low, int high) {

    if (low < high) {

        int pIndex = partitionArray(arr, low, high);
        
        quickSort(arr, low, pIndex - 1);
     
        quickSort(arr, pIndex + 1, high);
    }
}

// Randomized Partition
int randomizedPartition(vector<int>& arr, int low, int high) {

    // Generate random index
    int randomIndex = low + rand() % (high - low + 1);

    // Swap random element with first element
    swap(arr[low], arr[randomIndex]);

    // Apply the same two-pointer partition
    return partitionArray(arr, low, high);
}

// Randomized Quick Sort
void randomizedQuickSort(vector<int>& arr, int low, int high) {

    if (low < high) {

        int pIndex = randomizedPartition(arr, low, high);

        randomizedQuickSort(arr, low, pIndex - 1);
        randomizedQuickSort(arr, pIndex + 1, high);
    }
}

// Display array
void display(vector<int>& arr) {

    for (int x : arr) {
        cout << x << " ";
    }

    cout << endl;
}

int main() {

   

    int n, choice;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid array size\n";
        return 0;
    }

    vector<int> arr(n);

    cout << "Enter array elements:\n";

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    do {

        cout << "\n===== QUICK SORT MENU =====";
        cout << "\n1. Deterministic Quick Sort";
        cout << "\n2. Randomized Quick Sort";
        cout << "\n3. Compare Both";
        cout << "\n4. Exit";

        cout << "\nEnter choice: ";
        cin >> choice;

        vector<int> a = arr;
        vector<int> b = arr;

        switch (choice) {

            case 1:

                quickSort(a, 0, n - 1);

                cout << "Deterministic Sorted Array: ";
                display(a);

                break;

            case 2:

                randomizedQuickSort(b, 0, n - 1);

                cout << "Randomized Sorted Array: ";
                display(b);

                break;

            case 3:

                quickSort(a, 0, n - 1);
                randomizedQuickSort(b, 0, n - 1);

                cout << "\nDeterministic Sorted Array: ";
                display(a);

                cout << "Randomized Sorted Array: ";
                display(b);

                cout << "\nTime Complexity:";
                cout << "\nBest Case: O(n log n)";
                cout << "\nAverage Case: O(n log n)";
                cout << "\nWorst Case: O(n^2)";

                cout << "\n\nSpace Complexity:";
                cout << "\nAverage Case: O(log n)";
                cout << "\nWorst Case: O(n)\n";

                break;

            case 4:

                cout << "Exiting...\n";

                break;

            default:

                cout << "Invalid choice\n";
        }

    } while (choice != 4);

    return 0;
}