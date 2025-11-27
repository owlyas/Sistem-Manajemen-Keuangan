#include "2Budgeting.h"
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

void FiturBudget::menuBudgeting(map<string,double> &budgetKategori) {
    int pilih;
    char lanjut = 'y';

    vector<string> kategoriList = {
        "Makan", "Transportasi", "Self Reward", "Dana Darurat", "Lainnya"
    };

    do {
        cout << "\n=======================================\n";
        cout << "              MENU BUDGETING         \n";
        cout << "=======================================\n";

        cout << "Pilih kategori untuk di-budget:\n";
        for (size_t i = 0; i < kategoriList.size(); ++i) {
            cout << i + 1 << ". " << kategoriList[i] << endl;
        }

        cout << "Pilih kategori (1-" << kategoriList.size() << "): ";
        while (!(cin >> pilih) || pilih < 1 || pilih > (int)kategoriList.size()) {
            cout << "Input tidak valid. Pilih kategori (1-"
                 << kategoriList.size() << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        string kategori = kategoriList[pilih - 1];

        double nominal;
        cout << "Masukkan nominal budget untuk kategori '" << kategori << "' (Rp): ";
        while (!(cin >> nominal) || nominal <= 0) {
            cout << "Nominal tidak valid. Masukkan angka positif: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        budgetKategori[kategori] = nominal;

        cout << "\n✅ Budget berhasil dicatat!\n";
        cout << "Kategori : " << kategori << endl;
        cout << "Budget   : Rp " << fixed << setprecision(2) << nominal << endl;

        cout << "\nIsi budget kategori lain? (y/t): ";
        cin >> lanjut;
        lanjut = tolower(lanjut);

    } while (lanjut == 'y');

    if (!budgetKategori.empty()) {
        cout << "\n=======================================\n";
        cout << "        RANGKUMAN BUDGET SAAT INI   \n";
        cout << "=======================================\n";

        cout << left << setw(20) << "Kategori"
             << right << setw(15) << "Budget (Rp)" << endl;
        cout << string(35, '-') << endl;

        for (const auto &pair : budgetKategori) {
            cout << left << setw(20) << pair.first
                 << right << "Rp " << fixed << setprecision(2) << pair.second << endl;
        }
    } else {
        cout << "\nBelum ada budget yang diinput.\n";
    }

    cout << "\nKembali ke Menu Utama...\n";
}
