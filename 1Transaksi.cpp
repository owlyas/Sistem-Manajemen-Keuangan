#include "1Transaksi.h"
#include <iostream>
#include <limits>

using namespace std;

void FiturTransaksi::catatIncome(vector<Transaksi> &daftarTransaksi, double &totalIncome) {
    string tgl, desk;
    double jml;
    char lanjut = 'y';

    cout << "\n=======================================\n";
    cout << "         💸 SUB-MENU: CATAT INCOME      \n";
    cout << "=======================================\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Tanggal Income (YYYY-MM-DD): ";
        getline(cin, tgl);

        cout << "Nominal Income (Rp): ";
        while (!(cin >> jml) || jml <= 0) {
            cout << "Input tidak valid, masukkan angka positif: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Keterangan: ";
        getline(cin, desk);

        daftarTransaksi.emplace_back(tgl, desk, jml, "Pemasukan");
        totalIncome += jml;

        cout << "\n✅ INCOME BERHASIL DICATAT!\n";
        cout << "TOTAL INCOME SAAT INI: Rp " << fixed << setprecision(2) << totalIncome << endl;

        cout << "Catat income lagi? (y/t): ";
        cin >> lanjut;
        lanjut = tolower(lanjut);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (lanjut == 'y');
}

void FiturTransaksi::catatExpense(vector<Transaksi> &daftarTransaksi,
                                  double &totalExpense,
                                  map<string,double> &budgetKategori) {
    string tgl, desk, tipe = "Pengeluaran";
    double jml;
    int kategoriPilihan;
    char lanjut = 'y';

    vector<string> kategoriList = {
        "Makan", "Transportasi", "Self Reward", "Dana Darurat", "Lainnya"
    };

    cout << "\n=======================================\n";
    cout << "      🛒 SUB-MENU: CATAT PENGELUARAN    \n";
    cout << "=======================================\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Pilih Kategori Pengeluaran:\n";
        for (size_t i = 0; i < kategoriList.size(); ++i) {
            cout << i + 1 << ". " << kategoriList[i] << endl;
        }

        cout << "Pilih kategori (1-" << kategoriList.size() << "): ";
        while (!(cin >> kategoriPilihan) || kategoriPilihan < 1 || kategoriPilihan > (int)kategoriList.size()) {
            cout << "Pilihan tidak valid: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        string kategori = kategoriList[kategoriPilihan - 1];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Tanggal Pengeluaran (YYYY-MM-DD): ";
        getline(cin, tgl);

        cout << "Nominal Pengeluaran (Rp): ";
        while (!(cin >> jml) || jml <= 0) {
            cout << "Masukkan angka positif: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Keterangan: ";
        getline(cin, desk);

        string deskripsiLengkap = "[" + kategori + "] " + (desk.empty() ? "Tanpa Keterangan" : desk);

        daftarTransaksi.emplace_back(tgl, deskripsiLengkap, jml, tipe);
        totalExpense += jml;

        cout << "\n✅ PENGELUARAN BERHASIL DICATAT!\n";
        cout << "TOTAL PENGELUARAN SAAT INI: Rp " << fixed << setprecision(2) << totalExpense << endl;

        // Hitung sisa budget kategori
        if (budgetKategori.find(kategori) != budgetKategori.end()) {
            double sisaBudget = budgetKategori[kategori] - jml;
            budgetKategori[kategori] = sisaBudget; // update sisa budget
            cout << "➡ SISA BUDGET KATEGORI '" << kategori << "': Rp " 
                 << fixed << setprecision(2) << (sisaBudget >= 0 ? sisaBudget : 0) << endl;
            if (sisaBudget < 0) {
                cout << "⚠️ Budget kategori ini sudah terlampaui!\n";
            }
        } else {
            cout << "⚠️ Belum ada budget untuk kategori '" << kategori << "'.\n";
        }

        cout << "Catat pengeluaran lagi? (y/t): ";
        cin >> lanjut;
        lanjut = tolower(lanjut);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (lanjut == 'y');
}
