#include <iostream>
using namespace std;
#define MAX 100  // Maximum number of points

// Function to check counterclockwise orientation
int orientation(int px, int py, int qx, int qy, int rx, int ry) {
    int val = (qy - py) * (rx - qx) - (qx - px) * (ry - qy);
    return (val > 0) ? 1 : (val < 0 ? -1 : 0);
}

// Convex Hull using Jarvis March Algorithm (without struct and vector)
void convexHull(int x[], int y[], int n) {
    if (n < 3) {
        cout << "Convex hull is not possible";
        return;
    }

    int hullX[MAX], hullY[MAX];  // Arrays to store hull points
    int hullCount = 0;           // Counter for hull points

    int leftmost = 0;

    // Find leftmost point
    for (int i = 1; i < n; i++)
        if (x[i] < x[leftmost])
            leftmost = i;

    int p = leftmost, q;
    do {
        hullX[hullCount] = x[p];
        hullY[hullCount] = y[p];
        hullCount++;

        q = (p + 1) % n;
        
        for (int i = 0; i < n; i++)
            if (orientation(x[p], y[p], x[i], y[i], x[q], y[q]) == -1)
                q = i;

        p = q;
    } while (p != leftmost);

    // Print the Convex Hull
    cout << "Convex Hull: ";
    for (int i = 0; i < hullCount; i++)
        cout << "(" << hullX[i] << ", " << hullY[i] << ") ";
    cout << endl;
}

// Driver function
int main() {
    int n;
    cout << "Enter number of points: ";
    cin >> n;

    int x[MAX], y[MAX];

    cout << "Enter points (x y): ";
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    convexHull(x, y, n);
    return 0;
}
