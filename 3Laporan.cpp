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
    cout << "          📜 LAPORAN KEUANGAN          \n";
    cout << "=======================================\n";

    if (daftarTransaksi.empty()) {
        cout << "Belum ada transaksi.\n";
        return;
    }

    cout << "+------------+------------------------------------------+--------------+------------------+\n";
    cout << "| Tanggal    | Deskripsi                                | Jumlah (Rp)  | Tipe Transaksi   |\n";
    cout << "+------------+------------------------------------------+--------------+------------------+\n";

    for (const auto &t : daftarTransaksi)
        t.tampilkan();

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
    cout << "            🔍 CARI TRANSAKSI           \n";
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
    vector<Transaksi> hasil;

    if (metode == 1) {
        string tgl;
        cout << "Masukkan tanggal (YYYY-MM-DD): ";
        getline(cin, tgl);

        for (auto &t : daftarTransaksi)
            if (t.tanggal == tgl) hasil.push_back(t);

    } else if (metode == 2) {
        string key;
        cout << "Masukkan kata kunci deskripsi: ";
        getline(cin, key);

        for (auto &t : daftarTransaksi)
            if (t.deskripsi.find(key) != string::npos) hasil.push_back(t);

    } else if (metode == 3) {
        string tp;
        cout << "Masukkan tipe (Pemasukan/Pengeluaran): ";
        getline(cin, tp);

        for (auto &t : daftarTransaksi)
            if (t.tipe == tp) hasil.push_back(t);

    } else {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    cout << "\n--- HASIL PENCARIAN ---\n";

    if (hasil.empty()) {
        cout << "Tidak ada transaksi yang ditemukan.\n";
        return;
    }

    cout << "+------------+------------------------------------------+--------------+------------------+\n";
    cout << "| Tanggal    | Deskripsi                                | Jumlah (Rp)  | Tipe Transaksi   |\n";
    cout << "+------------+------------------------------------------+--------------+------------------+\n";

    for (auto &t : hasil) t.tampilkan();

    cout << "+------------+------------------------------------------+--------------+------------------+\n";
}

void FiturLaporan::menuLaporanKeuangan(const vector<Transaksi> &daftarTransaksi,
                                       double totalIncome,
                                       double totalExpense) {
    int pilih;

    do {
        cout << "\n=======================================\n";
        cout << "            📘 LAPORAN KEUANGAN        \n";
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
