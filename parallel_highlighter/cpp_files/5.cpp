#include <iostream>
#include <vector>
using namespace std;

class Algorithms {
private:
    vector<int> nums;
public:
    Algorithms(vector<int> nums) { this->nums = nums; }

    int getSize() { return nums.size(); }

    vector<int> SelectionSort() {
        int min;
        int n = nums.size();
        for (int i = 0; i < n - 1; i++) {
            min = i;
            for (int j = i + 1; j < n; j++) {
                if (nums[j] < nums[min])
                    min = j;
            }
            swap(nums[i], nums[min]);
        }
        return nums;
    }

    vector<int> BubbleSort() {
        int n = nums.size();
        bool check_swap;
        for (int i = 0; i < n - 1; i++) {
            check_swap = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (nums[j] > nums[j + 1]) {
                    swap(nums[j], nums[j + 1]);
                    check_swap = true;
                }
            }
            if (!check_swap)
                break;
        }
        return nums;
    }

    void merge(Algorithms &x, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        vector<int> l(n1), r(n2);

        for (int i = 0; i < n1; i++) l[i] = x.nums[left + i];
        for (int j = 0; j < n2; j++) r[j] = x.nums[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (l[i] <= r[j]) x.nums[k++] = l[i++];
            else x.nums[k++] = r[j++];
        }
        while (i < n1) x.nums[k++] = l[i++];
        while (j < n2) x.nums[k++] = r[j++];
    }

    void MergeSort(Algorithms &x, int left, int right) {
        if (left >= right) return;
        int mid = (left + right) / 2;
        MergeSort(x, left, mid);
        MergeSort(x, mid + 1, right);
        merge(x, left, mid, right);
    }

    int LinearSearch(int key) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == key) return i;
        }
        return -1;
    }

    int BinarySearch(int key) {
        int low = 0, high = nums.size() - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (key == nums[mid]) return mid;
            else if (key < nums[mid]) high = mid - 1;
            else low = mid + 1;
        }
        return -1;
    }

    void print() {
        for (int i = 0; i < nums.size(); i++) cout << nums[i] << " ";
        cout << endl;
    }
};


int main() {
    Algorithms testvector1(vector<int>{
        87, 12, 45, 23, 91, 33, 72, 64, 18, 56,
        39, 5, 101, 77, 8, 29, 66, 44, 93, 15,
        2, 84, 70, 99, 36, 11, 52, 68, 27, 49,
        80, 31, 96, 60, 7
    });

    Algorithms testvector2(vector<int>{
        200, 145, 90, 15, 300, 75, 88, 122, 60, 19,
        44, 33, 278, 66, 143, 210, 81, 53, 170, 95,
        11, 250, 140, 199, 72, 6, 160, 42, 121, 134,
        55, 187, 10, 99, 215
    });

    Algorithms testvector3(vector<int>{
        14, 55, 82, 67, 95, 120, 7, 42, 11, 200,
        300, 5, 33, 98, 76, 150, 215, 91, 60, 45,
        134, 88, 270, 12, 180, 63, 50, 28, 19, 44,
        81, 157, 39, 240, 99
    });

    Algorithms testvector4(vector<int>{
        310, 25, 75, 160, 220, 140, 36, 58, 192, 8,
        87, 131, 19, 265, 99, 47, 18, 54, 121, 233,
        11, 270, 200, 66, 41, 90, 102, 75, 305, 12,
        77, 64, 29, 118, 151
    });

    int choice, searchChoice, findnum;
    cout << "Choose a sorting method:\n1. Selection Sort\n2. Bubble Sort\n3. Merge Sort\n";
    cin >> choice;

    
    switch (choice) {
    case 1:
        cout << "\nSelection Sort \n";
        testvector1.SelectionSort();
        testvector2.SelectionSort();
        testvector3.SelectionSort();
        testvector4.SelectionSort();
        break;
    case 2:
        cout << "\nBubble Sort\n";
        testvector1.BubbleSort();
        testvector2.BubbleSort();
        testvector3.BubbleSort();
        testvector4.BubbleSort();
        break;
    case 3:
        cout << "\nMerge Sort \n";
        testvector1.MergeSort(testvector1, 0, testvector1.getSize()-1);
        testvector2.MergeSort(testvector2, 0, testvector2.getSize()-1);
        testvector3.MergeSort(testvector3, 0, testvector3.getSize()-1);
        testvector4.MergeSort(testvector4, 0, testvector4.getSize()-1);
        break;
    default:
        cout << "Invalid option.\n"; return 0;
    }

    
    cout << "Vector 1: "; testvector1.print();
    cout << "Vector 2: "; testvector2.print();
    cout << "Vector 3: "; testvector3.print();
    cout << "Vector 4: "; testvector4.print();

    
    cout << "\nChoose search method:\n1. Linear Search\n2. Binary Search\n";
    cin >> searchChoice;
    cout << "Enter number to search for: ";
    cin >> findnum;

    if (searchChoice == 1) {
        cout << "Vector 1 index: " << testvector1.LinearSearch(findnum) << endl;
        cout << "Vector 2 index: " << testvector2.LinearSearch(findnum) << endl;
        cout << "Vector 3 index: " << testvector3.LinearSearch(findnum) << endl;
        cout << "Vector 4 index: " << testvector4.LinearSearch(findnum) << endl;
    }
    else if (searchChoice == 2) {
        cout << "Vector 1 index: " << testvector1.BinarySearch(findnum) << endl;
        cout << "Vector 2 index: " << testvector2.BinarySearch(findnum) << endl;
        cout << "Vector 3 index: " << testvector3.BinarySearch(findnum) << endl;
        cout << "Vector 4 index: " << testvector4.BinarySearch(findnum) << endl;
    }
    else {
        cout << "Invalid search option.\n";
    }

    return 0;
}
