#include <stdio.h>

#define MAX 100
#define FEE_STANDARD 150000
#define FEE_HI 30000

int main() {
    int maSo[MAX];
    int tuoi[MAX];
    int bhyt[MAX];
    int chiPhi[MAX];
    int n = 0;
    int i, k;

    printf('=== HE THONG QUAN LY HANG CHO KIOSK MEDICARE ===\n');
    printf('Nhap so luong benh nhan ban đầu (0 < n <= 100): ');
    if (scanf('%d', &n) != 1 || n <= 0 || n > MAX) {
        printf('Loi: So lượng benh nhan khong hop le!\n');
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf('\n--- Nhập thông tin bệnh nhân thứ %d ---\n', i + 1);
        maSo[i] = i + 1;
        
        do {
            printf('Nhap tuoi (1-120): ');
            scanf('%d', &tuoi[i]);
            if (tuoi[i] < 1 || tuoi[i] > 120) {
                printf('Loi: Tuoi phai tu 1 den 120. Vui long nhap lai!\n');
            }
        } while (tuoi[i] < 1 || tuoi[i] > 120);

        do {
            printf('Nhap trang thai BHYT (1: Co, 0: Khong): ');
            scanf('%d', &bhyt[i]);
            if (bhyt[i] != 0 && bhyt[i] != 1) {
                printf('Loi: Trang thai BHYT chi nhan gia tri 0 hoac 1. Nhap lai!\n');
            }
        } while (bhyt[i] != 0 && bhyt[i] != 1);

        if (bhyt[i] == 1) {
            chiPhi[i] = FEE_HI;
        } else {
            chiPhi[i] = FEE_STANDARD;
        }
    }

    int tongDoanhThu = 0;
    int soLuongUuTien = 0;

    printf('\n================ DANH SACH HANG CHO BAN DAU ================\n');
    printf('%-10s | %-10s | %-15s | %-15s | %-15s\n', 'STT', 'Ma So', 'Tuoi', 'BHYT', 'Chi Phi (VND)');
    printf('-------------------------------------------------------------------\n');
    for (i = 0; i < n; i++) {
        tongDoanhThu += chiPhi[i];
        if (tuoi[i] >= 70) {
            soLuongUuTien++;
        }
        printf('%-10d | %-10d | %-15d | %-15s | %-15d\n', 
            i + 1, maSo[i], tuoi[i], (bhyt[i] == 1 ? 'Co' : 'Khong'), chiPhi[i]);
    }
    printf('-------------------------------------------------------------------\n');
    printf('Tong doanh thu dự kiến: %d VND\n', tongDoanhThu);
    printf('Tong so benh nhan uu tien (>= 70 tuoi): %d\n', soLuongUuTien);

    printf('\nNhap vi tri chi so K can huy luot khám (0 den %d): ', n - 1);
    if (scanf('%d', &k) != 1 || k < 0 || k >= n) {
        printf('Loi: Vi tri K khong hop le hoac vuot qua pham vi hàng cho!\n');
        return 1;
    }

    for (i = k; i < n - 1; i++) {
        maSo[i] = maSo[i + 1];
        tuoi[i] = tuoi[i + 1];
        bhyt[i] = bhyt[i + 1];
        chiPhi[i] = chiPhi[i + 1];
    }
    n--;

    tongDoanhThu = 0;
    soLuongUuTien = 0;

    printf('\n================ DANH SACH SAU KHI HUY LUOT KHAM ================\n');
    printf('%-10s | %-10s | %-15s | %-15s | %-15s\n', 'STT', 'Ma So', 'Tuoi', 'BHYT', 'Chi Phi (VND)');
    printf('-------------------------------------------------------------------\n');
    for (i = 0; i < n; i++) {
        tongDoanhThu += chiPhi[i];
        if (tuoi[i] >= 70) {
            soLuongUuTien++;
        }
        printf('%-10d | %-10d | %-15d | %-15s | %-15d\n', 
            i + 1, maSo[i], tuoi[i], (bhyt[i] == 1 ? 'Co' : 'Khong'), chiPhi[i]);
    }
    printf('-------------------------------------------------------------------\n');
    printf('Tong doanh thu cap nhat: %d VND\n', tongDoanhThu);
    printf('So luong benh nhan uu tien hien tai: %d\n', soLuongUuTien);

    return 0;
}
