#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

// Node structure for Huffman Tree
struct Node {
    char data;
    int freq;
    Node *left, *right;
    
    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

// Comparison class for priority queue
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Recursive Approach
class HuffmanRecursive {
private:
    void encode(Node* root, string str, unordered_map<char, string>& huffmanCode) {
        if (root == nullptr) return;
        
        // Found a leaf node
        if (!root->left && !root->right) {
            huffmanCode[root->data] = str;
        }
        
        encode(root->left, str + "0", huffmanCode);
        encode(root->right, str + "1", huffmanCode);
    }
    
public:
    unordered_map<char, string> buildHuffmanTree(string text) {
        // Count frequency of characters
        unordered_map<char, int> freq;
        for (char ch : text) {
            freq[ch]++;
        }
        
        // Create priority queue
        priority_queue<Node*, vector<Node*>, Compare> pq;
        
        // Create leaf nodes and add to priority queue
        for (auto pair : freq) {
            pq.push(new Node(pair.first, pair.second));
        }
        
        // Build Huffman Tree
        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();
            
            Node* parent = new Node('$', left->freq + right->freq);
            parent->left = left;
            parent->right = right;
            
            pq.push(parent);
        }
        
        // Generate Huffman codes
        unordered_map<char, string> huffmanCode;
        encode(pq.top(), "", huffmanCode);
        
        return huffmanCode;
    }
};

// Greedy Approach
class HuffmanGreedy {
public:
    unordered_map<char, string> buildHuffmanTree(string text) {
        // Count frequency of characters
        unordered_map<char, int> freq;
        for (char ch : text) {
            freq[ch]++;
        }
        
        // Create min heap using priority queue
        priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> minHeap;
        
        // Add all characters to min heap
        for (auto pair : freq) {
            minHeap.push({pair.second, pair.first});
        }
        
        unordered_map<char, string> huffmanCode;
        
        // Build codes greedily
        while (minHeap.size() > 1) {
            auto first = minHeap.top(); minHeap.pop();
            auto second = minHeap.top(); minHeap.pop();
            
            // Add '0' to all codes of first
            for (auto& code : huffmanCode) {
                if (code.first == first.second) {
                    code.second = "0" + code.second;
                }
            }
            if (huffmanCode.find(first.second) == huffmanCode.end()) {
                huffmanCode[first.second] = "0";
            }
            
            // Add '1' to all codes of second
            for (auto& code : huffmanCode) {
                if (code.first == second.second) {
                    code.second = "1" + code.second;
                }
            }
            if (huffmanCode.find(second.second) == huffmanCode.end()) {
                huffmanCode[second.second] = "1";
            }
            
            // Add combined frequency back to heap
            minHeap.push({first.first + second.first, min(first.second, second.second)});
        }
        
        return huffmanCode;
    }
};

// Example usage
int main() {
    string text = "hello world";
    
    // Recursive approach
    HuffmanRecursive huffmanRecursive;
    auto recursiveCode = huffmanRecursive.buildHuffmanTree(text);
    
    cout << "Recursive Approach Huffman Codes:\n";
    for (auto pair : recursiveCode) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // Greedy approach
    HuffmanGreedy huffmanGreedy;
    auto greedyCode = huffmanGreedy.buildHuffmanTree(text);
    
    cout << "\nGreedy Approach Huffman Codes:\n";
    for (auto pair : greedyCode) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    return 0;
}