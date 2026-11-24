#include <iostream>
#include <cstring>
using namespace std;
const int MAX_ITEMS = 10;
struct Item {
    int  code;
    char name[30];
    int  qty;
   };
   class StockException {
public:
    char message[100];
    StockException(const char* msg) {
        strcpy(message,msg);
    }
};
class BranchB;  
class BranchA {
    char branchName[30];
    Item items[MAX_ITEMS];
    int itemcount;
public:
    BranchA(const char* n) : itemcount(0) {
        strcpy(branchName,n);
    }
    void addItem(int code,const char* name,int qty) {
        if (itemcount >= MAX_ITEMS) return;
        items[itemcount].code = code;
        strcpy(items[itemcount].name, name);
        items[itemcount].qty = qty;
        itemcount++;
    }
    void display() const {
        cout << "Stock at " << branchName << "\n";
        for (int i = 0; i < itemcount; i++)
            cout << items[i].code << "  " << items[i].name
                 << "  " << items[i].qty << "\n";
                 
    }
    friend void transferstock(BranchA& from,BranchB& to,int code,int qty);
    friend void transferstock(BranchB& from, BranchA& to,int code,int qty);
};
class BranchB {
    char branchName[30];
    Item items[MAX_ITEMS];
    int itemcount;
    public:
    BranchB(const char* name)  {
        strcpy(branchName,name);
        itemcount = 0;
    }
    void addItem(int code,const char* name,int qty){
        if (itemcount>=MAX_ITEMS) return;
        items[itemcount].code=code;
        strcpy(items[itemcount].name,name);
        items[itemcount].qty=qty;
        itemcount++;
    }
    void display() const {
        cout << "Stock at " << branchName << "\n";
        for (int i = 0; i < itemcount; i++)
            cout << items[i].code << "  " << items[i].name
                 << "  " << items[i].qty << "\n";
    }
    friend void transferstock(BranchA& from,BranchB& to,int code,int qty);
    friend void transferstock(BranchB& from, BranchA& to,int code, int qty);
};

void transferstock(BranchA& from,BranchB& to,int code,int qty) {
    int s=-1;
    for(int i=0;i<from.itemcount;i++){
        if(from.items[i].code==code){
            s=i;
            break;
        }
    }
    if(s==-1) {
        throw StockException("Item code not found in source branch");
    }
    if(from.items[s].qty<qty) {
        throw StockException("Not enough stock in source branch");
    }
    int d=-1;
    for(int i=0;i<to.itemcount;i++){
        if(to.items[i].code==code){
            d=i;
            break;
        }
    } 
    if(d==-1) {
     if(to.itemcount>=MAX_ITEMS) {
        throw StockException("Destination branch is full");
     }
     to.items[to.itemcount].code=code;
     strcpy(to.items[to.itemcount].name,from.items[s].name);
     to.items[to.itemcount].qty=qty;
        to.itemcount++;
    }
    from.items[s].qty-=qty;
    to.items[d].qty+=qty;
    cout<<"Stock transferred successfully\n";
}
void transferstock(BranchB& from, BranchA& to,int code, int qty) {
    int s=-1;
    for(int i=0;i<from.itemcount;i++){
        if(from.items[i].code==code){
            s=i;
            break;
        }
    }
    if(s==-1) {        throw StockException("Item code not found in source branch");
    }
    if(from.items[s].qty<qty) {
        throw StockException("Not enough stock in source branch");
    }
    int d=-1;
    for(int i=0;i<to.itemcount;i++){
        if(to.items[i].code==code){
            d=i;
            break;
        }
    } 
    if(d==-1) {
     if(to.itemcount>=MAX_ITEMS) {
        throw StockException("Destination branch is full");
     }
     to.items[to.itemcount].code=code;
     strcpy(to.items[to.itemcount].name,from.items[s].name);
     to.items[to.itemcount].qty=qty;
        to.itemcount++;
    }
    from.items[s].qty-=qty;
    to.items[d].qty+=qty;
    cout<<"Stock transferred successfully\n";
}

int main() {
    BranchA jaipur("Jaipur");
    BranchB Jodhpur("Jodhpur");
    jaipur.addItem(101, "Steel Rods", 500);
    jaipur.addItem(102, "Cement Bags", 300);
    Jodhpur.addItem(101, "Steel Rods", 1000);

    transferstock(jaipur, Jodhpur, 101, 50);
    transferstock(jaipur, Jodhpur, 102, 40);
    transferstock(jaipur, Jodhpur, 103, 10); 
    try {
        transferstock(jaipur, Jodhpur, 101, 600); 
    } catch (const StockException& e) {
        cout << "Error: " << e.message << endl;
    }
    try{
        transferstock(Jodhpur, jaipur, 101, 2000); 
    } catch (const StockException& e) {
        cout << "Error: " << e.message << endl;
    }
    try{
        transferstock(Jodhpur, jaipur, 104, 10); 
    } catch (const StockException& e) {
        cout << "Error: " << e.message << endl;
    }
    jaipur.display();
    Jodhpur.display();
    return 0;
}
