

#include <fstream>
#include <cctype>
#include <cstdio>
#include <string>
#include <memory>
#include <iostream>

class Billing
{
public:
    float price;
    unsigned long int id;
    std::string name;
    Billing()
    {
        id = 0;
        price = 0;
        name = "NOT FOUND";
    }
    void input()
    {
        std::cout << "\n\t\t Input ";
        std::cout << "\n\t\t=========\n";
        std::cout << "ID: ";
        std::cin >> id;
        std::cout << "Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Price: ";
        std::cin >> price;
    }
    void output()
    {
        std::cout << "\n\t\t Output ";
        std::cout << "\n\t\t=========\n";
        std::cout << "ID: " << id << "\n";
        std::cout << "\nName: ";
        std::cout << name;
        std::cout << "\nPrice: Rs " << price;
    }
};

void Borders()
{
    std::cout << "\n";
}

void DataIN()
{
    std::ofstream item("DataBase.dat", std::ios::binary | std::ios::app);
    Billing obj;
    obj.input();
    item.write((char*)&obj, sizeof(obj));
    item.close();
}

Billing DataCHECK(unsigned long int id)
{
    unsigned long int temp_id;
    std::ifstream item("DataBase.dat", std::ios::binary);
    Billing obj, obj1;
    item.seekg(0, std::ios::beg);
    while (item.read((char*)&obj, sizeof(obj)))
    {
        temp_id = obj.id;
        if (temp_id == id)
        {
            std::cout << "\nMatched ID: " << temp_id;
            item.close();
            return obj;
        }
    }
    item.close();
    return obj1;
}

void bill()
{
    float sum = 0, price[20];
    std::string name[20];
    Billing obj;
    unsigned long int temp_id;
    int i = 0;
    char ch = 'y';
    while (ch == 'y')
    {
        Borders();
        std::cout << "\n\t\t Billing";
        std::cout << "\n\t\t=========";
        std::cout << "\nEnter ID: ";
        std::cin >> temp_id;
        obj = DataCHECK(temp_id);
        sum += obj.price;
        price[i] = obj.price;
        name[i] = obj.name;
        std::cout << "\n\n More Products ? (Y/N):";
        std::cin >> ch;
        std::tolower(ch);
        i++;
    }
    std::cout << "\n\t\t Summary";
    std::cout << "\n\t\t=========\n";
    for (int j = 0; j < i; j++)
    {
        Borders();
        std::cout << "\t" << name[j] << "\t\tRs." << price[j] << std::endl;
    }
    std::cout << "\n\n\nTotal Bill: Rs." << sum;
    std::cout << "\n\nPress Any key to exit....";
    std::cin.get();
}

int main()
{
    int choice;
    unsigned long int a;
    Billing obj;
    while (true)
    {
        std::cout << "\n\t\t\t SuperMarket Database Management ";
        std::cout << "\n\t\t\t===================================\n";
        std::cout << "\t1.Enter Data into database (*)" << std::endl;
        std::cout << "\t2.Verify with Database (*)" << std::endl;
        std::cout << "\t3.Billing" << std::endl;
        std::cout << "\t4.Exit (*)" << std::endl << "\n\n\tEnter Any Choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            DataIN();
            break;
        case 2:
            std::cout << "\n\tEnter Item Id to be verified:";
            std::cin >> a;
            obj = DataCHECK(a);
            obj.output();
            break;
        case 3:
            bill();
            break;
        case 4:
            return 0;
        default:
            std::cout << "\tInvalid Input....";
            std::cin.get();
        }
        std::cin.get();
    }
}
