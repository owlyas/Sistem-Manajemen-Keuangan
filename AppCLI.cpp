#include "AppCLI.h"
#include <iostream>
#include <limits>

using namespace std;

AppCLI::AppCLI() : totalIncome(0.0), totalExpense(0.0) {}

void AppCLI::tampilkanMenuUtama() const {
    cout << "\n=======================================\n";
    cout << "    APLIKASI MANAJEMEN KEUANGAN (CLI)    \n";
    cout << "=======================================\n";
    cout << "1. Catat Transaksi (Catat Income/Expense)\n";
    cout << "2. Budgeting\n";
    cout << "3. Laporan Keuangan\n";
    cout << "4. Analisis Keuangan\n";
    cout << "5. Keluar\n";
    cout << "---------------------------------------\n";
    cout << "Pilih menu (1-5): ";
}

void AppCLI::run() {
    int pilihan;
    do {
        tampilkanMenuUtama();
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = 0;
        }

        switch (pilihan) {
            case 1:
                // sub menu transaksi
                {
                    int sub;
                    do {
                        cout << "\n--- 1. Catat TRANSAKSI ---\n";
                        cout << "1. Catat Income (Pemasukan)\n";
                        cout << "2. Catat Expense (Pengeluaran)\n";
                        cout << "3. Kembali ke Menu Utama\n";
                        cout << "Pilih opsi (1-3): ";

                        if (!(cin >> sub)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            sub = 0;
                        }

                        switch (sub) {
                            case 1: fiturTransaksi.catatIncome(daftarTransaksi, totalIncome); break;
                            case 2: fiturTransaksi.catatExpense(daftarTransaksi, totalExpense, budgetKategori); break;
                            case 3: cout << "Kembali...\n"; break;
                            default: cout << "Pilihan tidak valid.\n";
                        }
                    } while (sub != 3);
                }
                break;
            case 2:
                fiturBudget.menuBudgeting(budgetKategori);
                break;
            case 3:
                fiturLaporan.menuLaporanKeuangan(daftarTransaksi, totalIncome, totalExpense);
                break;
            case 4:
                fiturAnalisis.analisisKeuangan(daftarTransaksi, totalIncome, totalExpense, budgetKategori);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan aplikasi ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);
}
