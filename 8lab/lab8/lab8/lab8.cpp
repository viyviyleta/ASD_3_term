#include <iostream>
#include <vector>
#include <string>

struct Item {
    std::string name;
    int weight;
    int value;
};

void knapsack(int capacity, const std::vector<Item>& items) {
    int num_items = items.size();
    std::vector<std::vector<int>> dp(num_items + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= num_items; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int max_value = dp[num_items][capacity];
    std::cout << "Максимальная стоимость: " << max_value << std::endl;

    std::cout << "Предметы в рюкзаке:" << std::endl;
    int w = capacity;
    for (int i = num_items; i > 0 && max_value > 0; --i) {
        if (max_value != dp[i - 1][w]) {
            std::cout << "- " << items[i - 1].name << " (вес: " << items[i - 1].weight << ", стоимость: " << items[i - 1].value << ")" << std::endl;
            max_value -= items[i - 1].value;
            w -= items[i - 1].weight;
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int capacity;
    std::cout << "Введите вместимость рюкзака: ";
    std::cin >> capacity;

    int num_items;
    std::cout << "Введите количество предметов: ";
    std::cin >> num_items;

    std::vector<Item> items;
    for (int i = 0; i < num_items; ++i) {
        Item item;
        std::cout << "Введите название предмета, его вес и стоимость: ";
        std::cin >> item.name >> item.weight >> item.value;
        items.push_back(item);
    }

    knapsack(capacity, items);

    return 0;
}
