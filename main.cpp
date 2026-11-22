#include <iostream>
#include <cstring>
using namespace std;
const int MAX_ITEMS = 10;
struct Item {
    int  code;
    char name[30];
    int  qty;
   };

class BranchA {
    char branchName[30];
    Item items[MAX_ITEMS];
    int count;
public:
    BranchA(const char* n) : count(0) {
        strcpy(branchName,n);
    }
    void addItem(int code,const char* name,int qty) {
        if (count >= MAX_ITEMS) return;
        items[count].code = code;
        strcpy(items[count].name, name);
        items[count].qty = qty;
        count++;
    }
    void display() const {
        cout << "Stock at " << branchName << "\n";
        for (int i = 0; i < count; i++)
            cout << items[i].code << "  " << items[i].name
                 << "  " << items[i].qty << "\n";
                 
    }
};

int main() {
    BranchA jaipur("Jaipur");
    jaipur.addItem(101, "Steel Rods", 500);
    jaipur.addItem(102, "Cement Bags", 300);
    jaipur.display();
    return 0;
}
