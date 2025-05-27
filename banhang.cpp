#include <stdio.h>
#include <stdbool.h>

#define MAX_CUSTOMERS 100
#define MAX_TRANSACTIONS 1000

typedef struct {
    int customerID;
    int dayOfWeek; // 0 (T2) đến 6 (CN)
    float amount;
} Transaction;

typedef struct {
    int id;
    int totalTransactions;
    int weekendTransactions;
    float totalSpending;
    bool qualifiesForFridayOffer;
} CustomerStats;

Transaction transactions[MAX_TRANSACTIONS];
int numTransactions = 0;

CustomerStats customers[MAX_CUSTOMERS];
int numCustomers = 0;

// === Tiện ích ===
int findCustomerIndex(int id) {
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == id) return i;
    }
    customers[numCustomers].id = id;
    return numCustomers++;
}

void addTransaction(int customerID, int dayOfWeek, float amount) {
    transactions[numTransactions++] = (Transaction){customerID, dayOfWeek, amount};
}

void analyzeCustomers() {
    for (int i = 0; i < numTransactions; i++) {
        Transaction t = transactions[i];
        int index = findCustomerIndex(t.customerID);
        customers[index].totalTransactions++;
        customers[index].totalSpending += t.amount;

        // Nếu từ Thứ Sáu (5) đến Chủ Nhật (6)
        if (t.dayOfWeek >= 5 || t.dayOfWeek == 4) {
            customers[index].weekendTransactions++;
        }
    }

    for (int i = 0; i < numCustomers; i++) {
        float rate = (float)customers[i].weekendTransactions / customers[i].totalTransactions;
        if (rate >= 0.5) {
            customers[i].qualifiesForFridayOffer = true;
        }
    }
}

void printAnalysis() {
    printf("=== PHAN TICH KHACH HANG ===\n");
    for (int i = 0; i < numCustomers; i++) {
        printf("KHACH #%d | Giao dich: %d | Cuoi tuan: %d | Ty le: %.2f%% | Chi tieu: %.2f | Uu dai Thu Sau: %s\n",
               customers[i].id,
               customers[i].totalTransactions,
               customers[i].weekendTransactions,
               100.0 * customers[i].weekendTransactions / customers[i].totalTransactions,
               customers[i].totalSpending,
               customers[i].qualifiesForFridayOffer ? "CO" : "KHONG");
    }
}

void simulateFridayOffers() {
    printf("\n=== GUI UU DAI THU SAU ===\n");
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].qualifiesForFridayOffer) {
            printf("[SMS] Gui uu dai den KH #%d de kich cau mua sam som cuoi tuan!\n", customers[i].id);
        }
    }
}

// === MAIN ===
int main() {
    // Dữ liệu giao dịch giả lập
    addTransaction(1, 5, 200.0);  // T6
    addTransaction(1, 6, 250.0);  // T7
    addTransaction(1, 4, 150.0);  // T5

    addTransaction(2, 0, 120.0);  // T2
    addTransaction(2, 1, 100.0);  // T3
    addTransaction(2, 5, 90.0);   // T6

    addTransaction(3, 5, 300.0);  // T6
    addTransaction(3, 6, 310.0);  // CN
    addTransaction(3, 4, 350.0);  // T5
    addTransaction(3, 2, 150.0);  // T4

    addTransaction(4, 0, 100.0);  // T2
    addTransaction(4, 3, 150.0);  // T5
    

    analyzeCustomers();
    printAnalysis();
    simulateFridayOffers();

    return 0;
}