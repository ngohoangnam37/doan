#include <stdio.h>
#include <stdbool.h>

#define MAX_CUSTOMERS 10
#define MAX_TRANSACTIONS 100

// Danh sách mô tả
const char* paymentMethods[] = {"Tien mat", "The", "Vi dien tu"};
const char* membershipTypes[] = {"Thuong", "Bac", "Vang"};
const char* timesOfDay[] = {"Sang", "Chieu", "Tooi"};
const char* days[] = {"Thu Hai", "Thu Ba", "Thu Tu", "Thu Nam", "Thu Sau", "Thu Bay", "Chu Nhat"};
const char* quarters[] = {"Q1", "Q2", "Q3", "Q4"};

// Cấu trúc giao dịch
typedef struct {
    int customerID;
    int dayOfWeek;
    int timeOfDay;
    int favoriteProduct;
    int paymentMethod;
    int membershipType;
    float amount;
    int month; 
} Transaction;

// Mô phỏng nhãn cụm K-means (cụm 0: bình thường, 1: chi tiêu trung bình, 2: khách VIP)
int clusterLabels[MAX_CUSTOMERS + 1] = {0, 2, 1, 0, 1, 2, 2, 0, 1, 1, 0};

void printTransactionDetails(const Transaction* transaction) {
    printf("   Ngay giao dich: %s\n", days[transaction->dayOfWeek]);
    printf("   Thoi gian: %s\n", timesOfDay[transaction->timeOfDay]);
    printf("   San pham ua thich: #%d\n", transaction->favoriteProduct);
    printf("   Thanh toan: %s\n", paymentMethods[transaction->paymentMethod]);
    printf("   Loai the thanh vien: %s\n", membershipTypes[transaction->membershipType]);
    printf("   So tien: %.2f\n", transaction->amount);
}

void simulateSendSMS(int customerID) {
    printf(" [SMS] Gui uu dai den khach hang #%d vao thu Sau!\n", customerID);
}

int main() {
    Transaction transactions[MAX_TRANSACTIONS] = {
        {1, 5, 1, 101, 1, 2, 250.0, 2},
        {1, 6, 0, 101, 1, 2, 300.0, 3},
        {1, 5, 2, 103, 1, 2, 150.0, 2},
        {2, 0, 1, 201, 0, 1, 200.0, 0},
        {2, 6, 1, 202, 2, 1, 220.0, 2},
        {2, 5, 1, 202, 2, 1, 180.0, 1},
        {3, 2, 1, 301, 1, 0, 100.0, 2},
        {3, 5, 2, 301, 0, 0, 80.0, 2},
        {4, 6, 0, 401, 2, 2, 500.0, 4},
        {5, 6, 1, 501, 1, 1, 600.0, 4},
        {6, 6, 2, 601, 1, 1, 700.0, 4},
        {7, 1, 1, 701, 0, 0, 150.0, 5}
    };

    int numTransactions = 12;
    float spending[MAX_CUSTOMERS + 1] = {0};
    int weekendCount[MAX_CUSTOMERS + 1] = {0};
    bool offer[MAX_CUSTOMERS + 1] = {false};
    float quarterlyRevenue[4] = {0};

    // Phân tích dữ liệu
    for (int i = 0; i < numTransactions; i++) {
        int id = transactions[i].customerID;
        spending[id] += transactions[i].amount;

        if (transactions[i].dayOfWeek == 5 || transactions[i].dayOfWeek == 6)
            weekendCount[id]++;

        int month = transactions[i].month;
        int quarter = month / 3;
        quarterlyRevenue[quarter] += transactions[i].amount;
    }

    // Gán ưu đãi nếu ≥ 2 giao dịch cuối tuần
    for (int i = 1; i <= MAX_CUSTOMERS; i++) {
        if (weekendCount[i] >= 2) {
            offer[i] = true;
        }
    }

    // In chi tiết giao dịch + ưu đãi
    printf("=== Danh sach khach hang co uu dai ===\n\n");
    for (int i = 0; i < numTransactions; i++) {
        int id = transactions[i].customerID;

        if (offer[id]) {
            printf("Khach hang #%d [Cum %d] - Tong chi tieu: %.2f\n", id, clusterLabels[id], spending[id]);
            printTransactionDetails(&transactions[i]);
            printf("UU DAI THU SAU: Co\n");
            printf("---------------------------------\n");
        }
    }

    // Báo cáo doanh thu theo quý
    printf("\n=== Bao cao doanh thu theo quy ===\n");
    for (int q = 0; q < 4; q++) {
        printf("%s: %.2f VND\n", quarters[q], quarterlyRevenue[q]);
    }

    // Mô phỏng gửi SMS nếu hôm nay là Thứ Sáu (dayOfWeek == 4)
    int simulatedToday = 4; // Thứ Sáu
    if (simulatedToday == 4) {
        printf("\n=== Gui uu dai vao Thu Sau ===\n");
        for (int i = 1; i <= MAX_CUSTOMERS; i++) {
            if (offer[i]) {
                simulateSendSMS(i);
            }
        }
    }

    return 0;
} 