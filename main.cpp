#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ================================
// KONSTANTA
// ================================
const string CATEGORIES[] = {
    "Makan", "Skincare", "Transport", 
    "Hiburan", "Tagihan", "Lain-lain"
};
const int CAT_COUNT = 6;

// ================================
// STRUCT
// ================================
struct Transaction {
    string tanggal;
    char tipe;          // 'I' atau 'E'
    int catIdx;
    double nominal;
    string detail;
};

int main() {
    vector<Transaction> transactions;
    double budgets[CAT_COUNT];
    double totalCat[CAT_COUNT];
    int idxSort[CAT_COUNT];

    int n, pilihan;
    double income = 0, expense = 0, saldo = 0, savingRate = 0;
    bool found;

    // ================================
    // 1. INPUT BUDGET
    // ================================
    cout << "=== INPUT BUDGET PER KATEGORI ===\n";
    for (int i = 0; i < CAT_COUNT; i++) {
        do {
            cout << CATEGORIES[i] << " : ";
            cin >> budgets[i];
        } while (budgets[i] < 0);
    }

    // ================================
    // 2. INPUT JUMLAH TRANSAKSI
    // ================================
    cout << "\nJumlah Transaksi: ";
    cin >> n;
    cin.ignore(); // clear buffer

    // ================================
    // 3. INPUT DETAIL TRANSAKSI
    // ================================
    for (int i = 0; i < n; i++) {
        Transaction t;

        // 3.1 Tanggal
        do {
            cout << "\nTanggal (dd/mm/yyyy): ";
            getline(cin, t.tanggal);
        } while (t.tanggal == "");

        // 3.2 Tipe
        do {
            cout << "Tipe (I/E): ";
            cin >> t.tipe;
            t.tipe = toupper(t.tipe);
        } while (t.tipe != 'I' && t.tipe != 'E');

        // 3.3 Pilih kategori
        cout << "Pilih Kategori:\n";
        for (int j = 0; j < CAT_COUNT; j++) {
            cout << j + 1 << ". " << CATEGORIES[j] << endl;
        }

        do {
            cout << "Masukkan pilihan (1-6): ";
            cin >> pilihan;
        } while (pilihan < 1 || pilihan > CAT_COUNT);
        t.catIdx = pilihan - 1;

        // 3.4 Nominal
        do {
            cout << "Nominal: ";
            cin >> t.nominal;
        } while (t.nominal <= 0);
        cin.ignore();

        // 3.5 Detail
        cout << "Detail: ";
        getline(cin, t.detail);

        // 3.6 Simpan
        transactions.push_back(t);
    }

    // ================================
    // 4 & 5. HITUNG INCOME & EXPENSE
    // ================================
    for (auto &tr : transactions) {
        if (tr.tipe == 'I') income += tr.nominal;
        else expense += tr.nominal;
    }

    // ================================
    // 6. SALDO & SAVING RATE
    // ================================
    saldo = income - expense;
    savingRate = (income > 0) ? (saldo / income) * 100 : 0;

    // ================================
    // 7. RINGKASAN
    // ================================
    cout << "\n=== RINGKASAN ===\n";
    cout << "Total Income : " << income << endl;
    cout << "Total Expense: " << expense << endl;
    cout << "Saldo        : " << saldo << endl;
    cout << "Saving Rate  : " << savingRate << "%\n";

    // ================================
    // 8–10. TOP 5 EXPENSE
    // ================================
    vector<Transaction> temp = transactions;

    // Selection Sort DESC (nominal)
    for (int i = 0; i < temp.size() - 1; i++) {
        int idxMax = i;
        for (int j = i + 1; j < temp.size(); j++) {
            if (temp[j].nominal > temp[idxMax].nominal)
                idxMax = j;
        }
        swap(temp[i], temp[idxMax]);
    }

    cout << "\n=== TOP 5 PENGELUARAN ===\n";
    int count = 0;
    for (auto &tr : temp) {
        if (tr.tipe == 'E') {
            cout << CATEGORIES[tr.catIdx] << " - Rp " << tr.nominal
                 << " (" << tr.detail << ")\n";
            count++;
            if (count == 5) break;
        }
    }
    if (count == 0) cout << "(Tidak ada pengeluaran)\n";

    // ================================
    // 11–12. TOTAL EXPENSE PER KATEGORI
    // ================================
    for (int i = 0; i < CAT_COUNT; i++) totalCat[i] = 0;

    for (auto &tr : transactions) {
        if (tr.tipe == 'E')
            totalCat[tr.catIdx] += tr.nominal;
    }

    // ================================
    // 13–14. SORTING RANK KATEGORI
    // ================================
    for (int i = 0; i < CAT_COUNT; i++) idxSort[i] = i;

    for (int i = 0; i < CAT_COUNT - 1; i++) {
        int kMax = i;
        for (int j = i + 1; j < CAT_COUNT; j++) {
            if (totalCat[idxSort[j]] > totalCat[idxSort[kMax]])
                kMax = j;
        }
        swap(idxSort[i], idxSort[kMax]);
    }

    cout << "\n=== RANKING PENGELUARAN PER KATEGORI ===\n";
    for (int i = 0; i < CAT_COUNT; i++) {
        if (totalCat[idxSort[i]] > 0) {
            cout << CATEGORIES[idxSort[i]] << " : Rp " 
                 << totalCat[idxSort[i]] << endl;
        }
    }

    // ================================
    // 16–17. SEARCH BERDASARKAN KATEGORI
    // ================================
    cout << "\nCari Transaksi Berdasarkan Kategori (1-6): ";
    int k;
    do {
        cin >> k;
    } while (k < 1 || k > CAT_COUNT);
    int idx = k - 1;

    cout << "\n=== TRANSAKSI DI KATEGORI: " << CATEGORIES[idx] << " ===\n";
    found = false;

    for (auto &tr : transactions) {
        if (tr.catIdx == idx) {
            cout << tr.tanggal << " | "
                 << tr.tipe << " | Rp " << tr.nominal
                 << " | " << tr.detail << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "(Tidak ada transaksi pada kategori ini)\n";
    }

    return 0;
}
