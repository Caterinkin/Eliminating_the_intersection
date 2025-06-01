#include <iostream>
#include <memory>

class node
{
public:
    int m_value;
    std::weak_ptr<node> parent;  // Используем weak_ptr вместо shared_ptr для разрыва цикла

    node(int value) : m_value{ value } {};
    ~node() { std::cout << "destructor called\n"; }

    void print_parent() const
    {
        if (auto parent_ptr = parent.lock())  // Преобразуем weak_ptr в shared_ptr
        {
            std::cout << "Parent value: " << parent_ptr->m_value << std::endl;
        }
        else
        {
            std::cout << "Parent node is expired or not available\n";
        }
    }
};

int main()
{
    {
        auto node1 = std::make_shared<node>(1);
        auto node2 = std::make_shared<node>(2);

        // Устанавливаем родительские связи
        node1->parent = node2;
        node2->parent = node1;

        // Демонстрация доступа к родителю
        std::cout << "Node1: ";
        node1->print_parent();

        std::cout << "Node2: ";
        node2->print_parent();
    }  // Здесь деструкторы будут вызваны корректно

    return 0;
}