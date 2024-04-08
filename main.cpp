#include <iostream>
#include <vector>

using namespace std;

class Time {
private:
    int seconds;

public:
    Time(int secs = 0) : seconds(secs) {}

    operator int() const { return seconds; }

    friend std::istream& operator>>(std::istream& is, Time& t) {
        int h = 0, m = 0, s = 0;
        char sep;
        is >> h >> sep >> m >> sep >> s;
        t.seconds = h * 3600 + m * 60 + s;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        os << t.hours() << "h:" << t.minutes() % 60 << "m:" << t.seconds % 60 << "s";
        return os;
    }

    Time operator+(const Time& other) const {
        return Time(seconds + other.seconds);
    }

    Time operator-(const Time& other) const {
        return Time(seconds - other.seconds);
    }

    Time operator*(int scalar) const {
        return Time(seconds * scalar);
    }

private:
    int hours() const { return seconds / 3600; }
    int minutes() const { return seconds / 60; }
};

class Item {
public:
    std::string name;
    double unit_net_price;
    char VAT_type;
    int quantity;

    Item(std::string n, double price, char VAT, int qty)
        : name(n), unit_net_price(price), VAT_type(VAT), quantity(qty) {}

    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        double total = item.unit_net_price * item.quantity * (1 + item.VAT_rate());
        os << item.name << " | " << item.unit_net_price << " " << item.VAT_type << " | " << item.quantity << " | " << item.unit_net_price * item.quantity << " | " << total;
        return os;
    }

    double VAT_rate() const {
        switch (VAT_type) {
        case 'A': return 0.23;
        case 'B': return 0.08;
        case 'C': return 0.00;
        default: return 0.0;
        }
    }
};

class Invoice {
public:
    long seller_NIP, buyer_NIP;
    std::vector<Item> items;

    Invoice(long seller, long buyer) : seller_NIP(seller), buyer_NIP(buyer) {}

    void add_item(const Item& item) {
        items.push_back(item);
    }

    friend std::ostream& operator<<(std::ostream& os, const Invoice& inv) {
        os << "------------------VAT invoice------------------\n";
        os << "Seller: " << inv.seller_NIP << "      Buyer: " << inv.buyer_NIP << "\n\n";
        double net_total = 0, gross_total = 0;
        for (const auto& item : inv.items) {
            net_total += item.unit_net_price * item.quantity;
            gross_total += item.unit_net_price * item.quantity * (1 + item.VAT_rate());
            os << item << "\n";
        }
        os << "------------------------------------ TOTAL ----\n";
        os << "                                " << net_total << " | " << gross_total << "\n";
        return os;
    }
};

int main (){

    Time t1(200);
    cout << t1 << endl; // displays 03m:20s
    Time t2;
    cin >> t2; // user enters 10h:12m:01s

    Time t3 = t2 - t1; // 10h:8m:41s
    int t3s = t3; //    36521
    cout << t3s << endl;
    cout << " " << endl;


    Invoice inv(7770003699, 0123456);
    inv.add_item(Item("M3 screw", 0.37, 'A', 100));
    inv.add_item(Item("2 mm drill", 2.54, 'B', 2));
    std::cout << inv << std::endl;
    return 0;
}
