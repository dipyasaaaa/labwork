#include <iostream>
#include <queue>
using namespace std;

const int MAX_NODES = 100;
int freq[MAX_NODES];
char items[MAX_NODES];
int tree[MAX_NODES][3]; // [freq, left, right]
string codes[26];
int nodeCount;

void buildHuffmanTree(int n) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < n; i++) {
        tree[i][0] = freq[i];
        tree[i][1] = tree[i][2] = -1;
        pq.push({freq[i], i});
    }

    nodeCount = n;
    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        tree[nodeCount][0] = left.first + right.first;
        tree[nodeCount][1] = left.second;
        tree[nodeCount][2] = right.second;
        pq.push({tree[nodeCount][0], nodeCount});
        nodeCount++;
    }
}

void generateHuffmanCodes(int node, string code) {
    if (node < nodeCount && tree[node][1] == -1 && tree[node][2] == -1) {
        codes[items[node] - 'A'] = code;
        return;
    }
    if (tree[node][1] != -1) generateHuffmanCodes(tree[node][1], code + "0");
    if (tree[node][2] != -1) generateHuffmanCodes(tree[node][2], code + "1");
}

void printHuffmanCodes(int n) {
    cout << "Char | Huffman Code" << endl;
    cout << "-------------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << items[i] << "   | " << codes[items[i] - 'A'] << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    cout << "Enter characters: ";
    for (int i = 0; i < n; i++) {
        cin >> items[i];
    }

    cout << "Enter corresponding frequencies: ";
    for (int i = 0; i < n; i++) {
        cin >> freq[i];
    }
    
    buildHuffmanTree(n);
    generateHuffmanCodes(nodeCount - 1, "");
    printHuffmanCodes(n);
    return 0;
}
