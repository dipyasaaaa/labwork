#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate priority score
int calculatePriority(int marks, int understanding) {
    return marks * (2 - understanding);
}

// Merge function for sorting in descending order of priority
void merge(string topics[], int priority[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    string leftTopics[n1], rightTopics[n2];
    int leftPriority[n1], rightPriority[n2];

    for (int i = 0; i < n1; i++) {
        leftTopics[i] = topics[left + i];
        leftPriority[i] = priority[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightTopics[i] = topics[mid + 1 + i];
        rightPriority[i] = priority[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftPriority[i] >= rightPriority[j]) {
            topics[k] = leftTopics[i];
            priority[k] = leftPriority[i];
            i++;
        } else {
            topics[k] = rightTopics[j];
            priority[k] = rightPriority[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        topics[k] = leftTopics[i];
        priority[k] = leftPriority[i];
        i++;
        k++;
    }
    while (j < n2) {
        topics[k] = rightTopics[j];
        priority[k] = rightPriority[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(string topics[], int priority[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(topics, priority, left, mid);
        mergeSort(topics, priority, mid + 1, right);
        merge(topics, priority, left, mid, right);
    }
}

// Function to allocate study time based on priority
void allocateStudyTime(string topics[], int priority[], int n, int totalHours) {
    int totalPriority = 0;
    for (int i = 0; i < n; i++) {
        totalPriority += priority[i];
    }

    cout << "\nStudy Plan:\n";
    for (int i = 0; i < n; i++) {
        double timeAllocated = (double(priority[i]) / totalPriority) * totalHours;
        timeAllocated = round(timeAllocated * 4) / 4; // Round to nearest 0.25 (15 min increments)
        cout << i + 1 << ") " << topics[i] << " : " << timeAllocated << " hours\n";
    }
}

int main() {
    int n;
    cout << "Enter number of Topics: ";
    cin >> n;
    cin.ignore(); // To handle getline correctly

    string topics[n];
    int marks[n], understanding[n], priority[n];

    for (int i = 0; i < n; i++) {
        cout << "\nEnter topic name: ";
        getline(cin, topics[i]);

        cout << "Enter marks weightage (e.g., 15, 5, 2): ";
        cin >> marks[i];

        cout << "Enter understanding level (-1 = No understanding, 0 = Somewhat understood, 1 = Understood but needs revision): ";
        cin >> understanding[i];
        cin.ignore(); // Prevent getline issues in next loop

        priority[i] = calculatePriority(marks[i], understanding[i]);
    }

    // Sorting topics by priority using Merge Sort
    mergeSort(topics, priority, 0, n - 1);

    // Taking user input for total study hours
    int totalHours;
    cout << "\nEnter total available study hours: ";
    cin >> totalHours;

    // Displaying study plan
    allocateStudyTime(topics, priority, n, totalHours);

    return 0;
}
