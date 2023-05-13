#include <iostream>
#include <vector>
#include <string>
#include <memory>


class Detail
{
protected:
    Detail() = default;
    virtual ~Detail() = default;

   
};

class Assembly : public Detail
{
protected:
    friend void FillVector(std::vector<Assembly>* vec); // Добавляет объявление дружественности
    explicit Assembly(const std::string& detail_info) : detail(detail_info) {
        std::cout << "Assembly constructor is called." << std::endl;
    }

    const std::string& getDetail() const { // геттер для поля detail
        return detail;
    }

private:
    std::string detail;
};

void FillVector(std::vector<Assembly>* vec) { // Изменяем тип параметра
    for (int i = 0; i < 5; ++i)
    {
        auto a = std::unique_ptr<Assembly>(new Assembly("Detail #" + std::to_string(i)));
        vec->push_back(std::move(*a));
    }
}

std::vector<Assembly> vec;

int main() {
    FillVector(&vec);
    for (auto i = vec.begin(); i != vec.end(); i++)
    {
        std::cout << i->getDetail() << std::endl; // используется геттер для вывода значения поля detail
    }
    return 0;
}