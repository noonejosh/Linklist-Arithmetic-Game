//Hanz Joshua V. Ancuna
//BSCS-2B
//DSA Quiz

#include <iostream>
#include <fstream>


using namespace std;

// Structure for binary tree node
struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node(char c, int f) : character(c), frequency(f), left(NULL), right(NULL) {}
};

// Structure for priority queue using linked list
struct Q {
    Node* node;
    Q* next;

    Q(Node* bn) : node(bn), next(NULL) {}
};

class priorityQueue {
private:
    Q* head;
    string treeCode[256]; // Store Huffman codes

    // Function to generate Huffman codes recursively
    void huffmanCode(Node* r, string code) {
        if(r){
            if (r->character != '\0') {
                treeCode[static_cast<int>(r->character)] = code;
            }

            // Traverse left with '0' appended to the code
            huffmanCode(r->left, code + "0");
            // Traverse right with '1' appended to the code
            huffmanCode(r->right, code + "1");
        }
    }

public:
    priorityQueue() : head(NULL) {}

    void enqueue(char c, int f) {
        Node* node = new Node(c, f);
        Q* newNode = new Q(node);

        // If the head is empty or newNode has a lower frequency than the head, insert at the beginning
        if (!head || newNode->node->frequency < head->node->frequency) {
            newNode->next = head;
            head = newNode;
        } else {
            // Else find the correct position to insert the new node
            Q* current = head;
            while (current->next && newNode->node->frequency >= current->next->node->frequency) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void* huffmanTree() {
        Q* temp;

        while (head && head->next) {
            Q* leftNode = head;
            Q* rightNode = head->next;

            // Create a new combined node with left and right children
            Node* combined = new Node('\0', leftNode->node->frequency + rightNode->node->frequency);
            combined->left = leftNode->node;
            combined->right = rightNode->node;

            // Remove the two nodes from the queue
            head = head->next->next;

            // Create a new queue node for the combined node
            Q* combinedNode = new Q(combined);

            // Insert the combined node back into the priority queue while maintaining order
            if (!head || combinedNode->node->frequency < head->node->frequency) {
                combinedNode->next = head;
                head = combinedNode;
            } else {
                Q* current = head;
                while (current->next && combinedNode->node->frequency >= current->next->node->frequency) {
                    current = current->next;
                }
                combinedNode->next = current->next;
                current->next = combinedNode;
            }
        }
        huffmanCode(head->node,"");
    }


    void textFileReader(string inputFile) {
        ifstream fp(inputFile);
        if (!fp.is_open()) {
            cout << "Unable to open file.";
            return;
        }

        char ch;
        int chars[256] = {0}; // Initialize the array to zero

        while (fp.get(ch)) {
            chars[ch]++;
        }

        for (int i = 0; i < 256; i++) {
            if (chars[i] != 0) {
                enqueue(char(i), chars[i]);
            }
        }

        fp.close();
    }

   void compressFile(string inputFile) {
        textFileReader(inputFile);
        huffmanTree();

        ifstream inputedFile(inputFile); // Open the file in binary mode
        ofstream compressedFile("compressed.huff");

        if (!inputedFile.is_open() || !compressedFile.is_open()) {
            cout << "Error: Unable to open file for compression." << endl;
            return;
        }


        string bits; // Use a string to accumulate bits for each character
        string line;
        while (getline(inputedFile,line)) {
            for(char ch: line){
                bits += treeCode[ch];
                while (bits.length() >= 8) {
                    // Convert the first 8 bits to a byte and write to the compressed file
                    compressedFile.put(static_cast<char>(stoi(bits.substr(0, 8), NULL, 2)));
                    bits = bits.substr(8);
                }
            }
            bits += treeCode['\n'];
            while (bits.length() >= 8) {
                compressedFile.put(static_cast<char>(stoi(bits.substr(0, 8), NULL, 2)));
                bits = bits.substr(8);
            }
        }

        cout << "Successful: File has been compressed." << endl;
        inputedFile.close();
        compressedFile.close();
    }

    void decompressFile(string compressedFile) {
        ifstream compressedFileStream(compressedFile, ios::binary); // Open the file in binary mode
        ofstream decompressedFile("decompressed.txt");

        if (!compressedFileStream.is_open() || !decompressedFile.is_open()) {
            cout << "Error: Unable to open file for decompression." << endl;
            return;
        }

        huffmanTree();

        Node* root = head->node; // Save the root of the Huffman tree
        Node* current = root;    // Initialize the current node

        char byte; // Read bytes for decompression
        while (compressedFileStream.get(byte)) {
            for (int i = 7; i >= 0; --i) {
                // Traverse the tree based on each bit in the byte
                char bit = (byte & (1 << i)) ? '1' : '0';

                if (bit == '0') {
                    current = current->left;
                } else if (bit == '1') {
                    current = current->right;
                }

                if (current->left == NULL && current->right == NULL) {
                    decompressedFile << current->character;
                    current = root; // Reset current to the root for the next character
                }
            }
        }

        cout << "Successful: File has been decompressed." << endl;
        compressedFileStream.close();
        decompressedFile.close();
    }


};

int main() {
    priorityQueue l;
    string s;
    int choice;
    do{
        cout << "1. Compress Text File" << endl;
        cout << "2. Decompress Text File" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
        case 1:
            cout << "Enter a text file: ";
            cin >> s;
            l.compressFile(s);
            break;
        case 2:
            cout << "Enter a text file: ";
            cin >> s;
            l.decompressFile(s);
        }
    }while(choice!=2);

    return 0;
}
