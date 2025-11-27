#include "4Analisis.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void FiturAnalisis::tampilkanTop5Pengeluaran(const vector<Transaksi> &daftarTransaksi) const {
    vector<Transaksi> pengeluaranList;

    for (size_t i = 0; i < daftarTransaksi.size(); ++i) {
        const Transaksi &t = daftarTransaksi[i];
        if (t.tipe == "Pengeluaran") {
            pengeluaranList.push_back(t);
        }
    }

    if (pengeluaranList.empty()) {
        cout << "Belum ada data pengeluaran.\n";
        return;
    }

    int n = static_cast<int>(pengeluaranList.size());

    // SELECTION SORT DESC 
    for (int i = 0; i < n - 1 && i < 5; ++i) {
        int idxMax = i;
        for (int j = i + 1; j < n; ++j) {
            if (pengeluaranList[j].jumlah > pengeluaranList[idxMax].jumlah) {
                idxMax = j;
            }
        }
        if (idxMax != i) {
            swap(pengeluaranList[i], pengeluaranList[idxMax]);
        }
    }

    int batas = min(5, n);

    cout << "+------------+------------------------------------------+--------------+------------------+\n";
    cout << "| Tanggal    | Deskripsi                                | Jumlah (Rp)  | Tipe Transaksi   |\n";
    cout << "+------------+------------------------------------------+--------------+------------------+\n";

    for (int i = 0; i < batas; ++i) {
        pengeluaranList[i].tampilkan();
    }

    cout << "+------------+------------------------------------------+--------------+------------------+\n";
}

void FiturAnalisis::tampilkanBudgetVsActual(const vector<Transaksi> &daftarTransaksi,
                                            const map<string,double> &budgetKategori) const {
    if (budgetKategori.empty()) {
        cout << "Belum ada data budget.\n";
        return;
    }

    // Hitung total pengeluaran per kategori
    map<string,double> totalPengeluaranPerKategori;

    for (size_t i = 0; i < daftarTransaksi.size(); ++i) {
        const Transaksi &t = daftarTransaksi[i];

        if (t.tipe == "Pengeluaran") {
            string kategori = "Lainnya";
            size_t p1 = t.deskripsi.find('[');
            size_t p2 = t.deskripsi.find(']');

            if (p1 != string::npos && p2 != string::npos && p2 > p1 + 1) {
                kategori = t.deskripsi.substr(p1 + 1, p2 - p1 - 1);
            }

            totalPengeluaranPerKategori[kategori] += t.jumlah;
        }
    }

    cout << "+----------------+--------------+--------------+--------------+--------------+-------------------+\n";
    cout << "| Kategori       | Budget Awal  | Pengeluaran  | Sisa Budget  | % Realisasi  | Status            |\n";
    cout << "+----------------+--------------+--------------+--------------+--------------+-------------------+\n";

    // Iterasi map budgetKategori tanpa auto
    for (map<string,double>::const_iterator it = budgetKategori.begin();
         it != budgetKategori.end(); ++it) {

        string kategori = it->first;
        double sisaSekarang = it->second;

        double totalPengeluaran = 0.0;
        if (totalPengeluaranPerKategori.count(kategori)) {
            totalPengeluaran = totalPengeluaranPerKategori.at(kategori);
        }

        double budgetAwal = sisaSekarang + totalPengeluaran;

        // hitung persen pakai if-else
        double persen;
        if (budgetAwal > 0) {
            persen = (totalPengeluaran / budgetAwal) * 100.0;
        } else {
            persen = 0.0;
        }

        // analisis status pakai if-else
        string status;
        if (persen > 100.0) {
            status = "Melebihi budget";
        } else if (persen >= 80.0) {
            status = "Hampir habis";
        } else if (persen >= 50.0) {
            status = "Cukup tinggi";
        } else if (persen > 0.0) {
            status = "Masih aman";
        } else {
            status = "Belum terpakai";
        }

        cout << "| " << setw(14) << left << kategori
             << "| " << setw(12) << right << fixed << setprecision(2) << budgetAwal
             << "| " << setw(12) << right << fixed << setprecision(2) << totalPengeluaran
             << "| " << setw(12) << right << fixed << setprecision(2) << sisaSekarang
             << "| " << setw(12) << right << fixed << setprecision(2) << persen
             << "| " << setw(19) << left  << status << "|\n";
    }

    cout << "+----------------+--------------+--------------+--------------+--------------+-------------------+\n";
}

void FiturAnalisis::analisisKeuangan(const vector<Transaksi> &daftarTransaksi,
                                     double totalIncome,
                                     double totalExpense,
                                     const map<string,double> &budgetKategori) const {
                                        
    cout << "\n=======================================\n";
    cout << "        ANALISIS KEUANGAN           \n";
    cout << "=======================================\n";

    if (daftarTransaksi.empty()) {
        cout << "Belum ada data dianalisis.\n";
        return;
    }

    double saldoAkhir = totalIncome - totalExpense;

    cout << "\n--- RINGKASAN KEUANGAN ---\n";
    cout << "Total Income     : Rp " << totalIncome << endl;
    cout << "Total Pengeluaran: Rp " << totalExpense << endl;
    cout << "Saldo Akhir      : Rp " << saldoAkhir << endl;

    cout << "\n--- TOP 5 PENGELUARAN TERBESAR ---\n";
    tampilkanTop5Pengeluaran(daftarTransaksi);

    cout << "\n--- BUDGET vs ACTUAL per Kategori ---\n";
    tampilkanBudgetVsActual(daftarTransaksi, budgetKategori);
}
