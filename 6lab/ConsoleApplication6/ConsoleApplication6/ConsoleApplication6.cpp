#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <Windows.h>

struct Node {
    int number;
    char symbol;
    Node* left, * right;
};

bool Compare(Node* firstNode, Node* secondNode) {
    return firstNode->number < secondNode->number;
}

void GetFrequencies(std::string& text, std::map<char, int>& frequenciesTable) {
    for (int i = 0; i < text.size(); i++) {
        frequenciesTable[text[i]]++;
    }
}

void GetNodes(const std::map<char, int> frequenciesTable, std::list<Node*>& nodes) {
    for (auto it = frequenciesTable.begin(); it != frequenciesTable.end(); it++) {
        Node* node = new Node;
        node->symbol = it->first;
        node->number = it->second;
        node->left = nullptr;
        node->right = nullptr;
        nodes.push_back(node);
    }
}

Node* HuffmanAlgorithm(std::list<Node*>& nodes) {
    while (nodes.size() != 1) {
        nodes.sort(Compare);

        Node* leftElement = nodes.front();
        nodes.pop_front();
        Node* rightElement = nodes.front();
        nodes.pop_front();

        Node* parent = new Node;
        parent->left = leftElement;
        parent->right = rightElement;
        parent->number = leftElement->number + rightElement->number;

        nodes.push_back(parent);
    }

    return nodes.front();
}

void BuildTable(Node* root, std::vector<bool>& code, std::map<char, std::vector<bool>>& matchingTable) {
    if (root->left != nullptr) {
        code.push_back(0);
        BuildTable(root->left, code, matchingTable);
    }

    if (root->right != nullptr) {
        code.push_back(1);
        BuildTable(root->right, code, matchingTable);
    }

    if (root->left == nullptr && root->right == nullptr) {
        matchingTable[root->symbol] = code;
    }

    if (!code.empty()) {
        code.pop_back();
    }
}

void PrintFrequenciesTable(const std::map<char, int> frequenciesTable, int totalChars) {
    std::cout << "\nТаблица встречаемости символов в тексте:\n\n";
    for (const auto& it : frequenciesTable) {
        double percentage = (static_cast<double>(it.second) / totalChars) * 100;
        std::cout << it.first << " : " << it.second << " ("
            << percentage << "%)" << std::endl;
    }
}

void PrintMatchingTable(const std::map<char, std::vector<bool>> matchingTable) {
    std::cout << "\nТаблица соответсвия символа и кодовой последовательности:\n\n";
    for (const auto& itm : matchingTable) {
        std::cout << itm.first << " : ";
        for (bool bit : itm.second) {
            std::cout << bit;
        }
        std::cout << std::endl;
    }
}

void PrintSequence(const std::string& text, const std::map<char, std::vector<bool>>& matchingTable) {
    std::cout << "\nВыходная последовательность:\n\n";
    for (char ch : text) {
        const std::vector<bool>& temp = matchingTable.at(ch);
        for (bool bit : temp) {
            std::cout << bit;
        }
    }
    std::cout << std::endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::map<char, int> frequenciesTable;
    std::map<char, std::vector<bool>> matchingTable;
    std::list<Node*> nodes;
    std::vector<bool> code;
    std::string text;

    std::cout << "Введите текст: ";
    getline(std::cin, text);

    GetFrequencies(text, frequenciesTable);
    GetNodes(frequenciesTable, nodes);
    Node* root = HuffmanAlgorithm(nodes);
    BuildTable(root, code, matchingTable);

    int totalChars = text.size();
    PrintFrequenciesTable(frequenciesTable, totalChars);
    PrintMatchingTable(matchingTable);
    PrintSequence(text, matchingTable);

    return 0;
}