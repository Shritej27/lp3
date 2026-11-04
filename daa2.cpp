
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};

struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

void printCodes(Node *root, string code)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
    {
        cout << root->ch << " : "
             << (code.empty() ? "0" : code) << endl;
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

void huffmanEncoding(vector<char> &chars, vector<int> &freq, int n)
{
    priority_queue<Node *, vector<Node *>, Compare> pq;

    for (int i = 0; i < n; i++)
        pq.push(new Node(chars[i], freq[i]));

    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();

        Node *right = pq.top();
        pq.pop();

        Node *parent = new Node('$',
                                left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    printCodes(pq.top(), "");
}

int main()
{
    int n;

    cout << "Enter number of characters: ";
    if (!(cin >> n) || n <= 0 || n > 256)
    {
        cout << "Invalid number of characters!" << endl;
        return 0;
    }

    vector<char> chars(n);
    vector<int> freq(n);

    cout << "Enter characters and their frequencies:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> chars[i] >> freq[i];

        if (freq[i] <= 0)
        {
            cout << "Frequency must be positive!" << endl;
            return 0;
        }

        for (int j = 0; j < i; j++)
        {
            if (chars[i] == chars[j])
            {
                cout << "Duplicate characters are not allowed!"
                     << endl;
                return 0;
            }
        }
    }

    cout << "\nHuffman Codes:\n";
    huffmanEncoding(chars, freq, n);

    return 0;
}
