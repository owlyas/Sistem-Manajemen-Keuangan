#include "3Laporan.h"
#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

void FiturLaporan::tampilkanRingkasan(double totalIncome, double totalExpense) const {
    double saldoAkhir = totalIncome - totalExpense;

    cout << "\n--- RINGKASAN KEUANGAN ---\n";
    cout << "Total Income     : Rp " << totalIncome << endl;
    cout << "Total Pengeluaran: Rp " << totalExpense << endl;
    cout << "Saldo Akhir      : Rp " << saldoAkhir << endl;
}

void FiturLaporan::tampilkanLaporan(const vector<Transaksi> &daftarTransaksi,
                                    double totalIncome,
                                    double totalExpense) const {
    cout << "\n=======================================\n";
    cout << "          LAPORAN KEUANGAN          \n";
    cout << "=======================================\n";

    if (daftarTransaksi.empty()) {
        cout << "Belum ada transaksi.\n";
        return;
    }

    cout << "+------------+------------------------------------------+--------------+------------------+\n";
    cout << "| Tanggal    | Deskripsi                                | Jumlah (Rp)  | Tipe Transaksi   |\n";
    cout << "+------------+------------------------------------------+--------------+------------------+\n";

    for (size_t i = 0; i < daftarTransaksi.size(); ++i) {
        daftarTransaksi[i].tampilkan();
    }

    cout << "+------------+------------------------------------------+--------------+------------------+\n";

    tampilkanRingkasan(totalIncome, totalExpense);
}

void FiturLaporan::cariTransaksi(const vector<Transaksi> &daftarTransaksi) {
    if (daftarTransaksi.empty()) {
        cout << "\nBelum ada transaksi untuk dicari.\n";
        return;
    }

    int metode;
    cout << "\n=======================================\n";
    cout << "              CARI TRANSAKSI           \n";
    cout << "=======================================\n";
    cout << "Cari berdasarkan:\n";
    cout << "1. Tanggal\n";
    cout << "2. Kata Kunci Deskripsi\n";
    cout << "3. Tipe (Pemasukan/Pengeluaran)\n";
    cout << "Pilih (1-3): ";

    if (!(cin >> metode)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Transaksi> ketemu;

    if (metode == 1) {
        string tgl;
        cout << "Masukkan tanggal (YYYY-MM-DD): ";
        getline(cin, tgl);

        for (size_t i = 0; i < daftarTransaksi.size(); ++i) {
            if (daftarTransaksi[i].tanggal == tgl) {
                ketemu.push_back(daftarTransaksi[i]);
            }
        }

    } else if (metode == 2) {
        string key;
        cout << "Masukkan kata kunci deskripsi: ";
        getline(cin, key);

        for (size_t i = 0; i < daftarTransaksi.size(); ++i) {
            if (daftarTransaksi[i].deskripsi.find(key) != string::npos) {
                ketemu.push_back(daftarTransaksi[i]);
            }
        }

    } else if (metode == 3) {
        string tp;
        cout << "Masukkan tipe (Pemasukan/Pengeluaran): ";
        getline(cin, tp);

        for (size_t i = 0; i < daftarTransaksi.size(); ++i) {
            if (daftarTransaksi[i].tipe == tp) {
                ketemu.push_back(daftarTransaksi[i]);
            }
        }

    } else {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    cout << "\n--- HASIL PENCARIAN ---\n";

    if (ketemu.empty()) {
        cout << "Tidak ada transaksi yang ditemukan.\n";
        return;
    }

    cout << "+------------+------------------------------------------+--------------+------------------+\n";
    cout << "| Tanggal    | Deskripsi                                | Jumlah (Rp)  | Tipe Transaksi   |\n";
    cout << "+------------+------------------------------------------+--------------+------------------+\n";

    for (size_t i = 0; i < ketemu.size(); ++i) {
        ketemu[i].tampilkan();
    }

    cout << "+------------+------------------------------------------+--------------+------------------+\n";
}

void FiturLaporan::menuLaporanKeuangan(const vector<Transaksi> &daftarTransaksi,
                                       double totalIncome,
                                       double totalExpense) {
    int pilih;

    do {
        cout << "\n=======================================\n";
        cout << "            LAPORAN KEUANGAN        \n";
        cout << "=======================================\n";
        cout << "1. Daftar Semua Transaksi\n";
        cout << "2. Cari Transaksi (Searching)\n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "Pilih (1-3): ";

        if (!(cin >> pilih)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilih = 0;
        }

        switch (pilih) {
            case 1: tampilkanLaporan(daftarTransaksi, totalIncome, totalExpense); break;
            case 2: cariTransaksi(daftarTransaksi); break;
            case 3: cout << "Kembali...\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }

    } while (pilih != 3);
}
