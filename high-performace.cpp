// high-performace.cpp : This file contains the 'main' function. Program execution begins and ends there.
// testing some cpp stuff to see whats good lol

#include <iostream>
#include <set>
#include <string>
#include <vector>

template<typename ...T>
void print(const T &...args) {
    auto printArg{
    [](const auto& arg) {std::cout << arg; }
    };
    (printArg(args), ...);
}

template<typename ...T>
void print(std::ostream &out, const T &...args) {
    auto printArg{
    [&out](const auto& arg) {out << arg; }
    };
    (printArg(args), ...);
}

// trying to make a container so i can see when the values have been copied from it
// and how many times its coppied
// currently making changes so that it prints when the values have been moved etc

class Set {
public:
    Set(std::string arg) {
        value.push_back(arg);
    }
    void insert(std::string arg) {
        value.push_back(arg);
    }

    size_t getSize() const {
        return value.size();
    }

    std::string operator[](int i) {
        return value[i];
    }
    
    friend std::ostream& operator<<(std::ostream &out, const Set& set);

    Set() = default;
    Set(const Set&) { print("Set Has been coppied\n"); }
    Set(Set&&) { print("Move Constructor has been called\n"); }
    Set& operator=(const Set&) = default;
    Set& operator=(Set&&) = default;

private:
    std::vector<std::string> value;
};

std::ostream& operator<<(std::ostream& out, const Set& set){
    for (int i{ 0 }; i < set.getSize(); i++) {
        out << set.value[i] << ' ';
    }
    return out;
}


class Bagel {
public:
    // Bagel class takes ownership of passed toppings value
    Bagel(Set ts)  : toppings_(std::move(ts)) {}
   // {
   //     toppings_.insert(std::move(ts));
   // }
    Bagel(const Bagel&) { print("Bagel has been coppied\n"); }
    Set getToppings()const {
        return toppings_; // could call std::move which would prevent a copy being made here for performace
    }
    void printToppings(){ // not working LOL
        // print(toppings_);
        toppings_.insert("sam");
        for (int i{ 0 }; i < toppings_.getSize(); i++) {
            print(toppings_[i]);
        }
    }
private:
    Set toppings_;
};

int main()
{
    Set toppings;
    toppings.insert("salt");
    Bagel bagel_a{ toppings }; // bagel_a has salt as a topping

    toppings.insert("pepper");
    Bagel bagel_b{ toppings }; // bagel b now has salt & pepper
    print("\nBAGEL A TOPPINGS: ");
    bagel_a.printToppings(); // trying to print the toppings but error :( shame
    print('\n');
    print("\nBAGEL B TOPPINGS: ");
    bagel_b.printToppings();
    print('\n');
    print("TOPPINGS ADDING: ", toppings, '\n');
    // for (int i{ 0 }; i < toppings.getSize(); i++) {
    //     print(toppings[i], '\n');
    // }
    // for (int i{ 0 }; i < bagel_a.getToppings().getSize(); i++) {
    //     print("\nBAGEL A TOPPINGS: ", bagel_a.getToppings()[i]);
    // }
   // for (int i{ 0 }; i < bagel_b.getToppings().getSize(); i++) {
   //     print("\nBAGEL B TOPPINGS: ", bagel_a.getToppings()[i]);
   // }
   //for (const auto& value : toppings) {
   //    print(value, '\n');
   //}
    return 0;
}
