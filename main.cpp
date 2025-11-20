#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <map> 

using namespace std;

// Kelas Transaksi untuk menyimpan detail setiap catatan
class Transaksi {
public:
    string tanggal;
    string deskripsi;
    double jumlah;
    string tipe;

    Transaksi(string tgl, string desk, double jml, string tp)
        : tanggal(tgl), deskripsi(desk), jumlah(jml), tipe(tp) {}

    void tampilkan() const {
        cout << "| " << setw(10) << left << tanggal
             << "| " << setw(40) << left << deskripsi
             << "| " << setw(12) << right << fixed << setprecision(2) << jumlah
             << "| " << setw(15) << left << tipe << " |" << endl;
    }
};

class ManajemenKeuangan {
private:
    vector<Transaksi> daftarTransaksi;
    double totalIncome = 0.0;
    double totalExpense = 0.0;

    // 🔥 MAP untuk menyimpan budget kategori
    map<string, double> budgetKategori;

public:
    void tampilkanMenuUtama() const {
        cout << "\n=======================================" << endl;
        cout << "    APLIKASI MANAJEMEN KEUANGAN (CLI)    " << endl;
        cout << "=======================================" << endl;
        cout << "1. Daftar Transaksi (Catat Income/Expense)" << endl;
        cout << "2. Budgeting" << endl;
        cout << "3. Laporan Keuangan" << endl;
        cout << "4. Analisis Keuangan" << endl;
        cout << "5. Keluar" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Pilih menu (1-5): ";
    }

    void jalankan() {
        int pilihan;
        do {
            tampilkanMenuUtama();
            if (!(cin >> pilihan)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pilihan = 0;
            }

            switch (pilihan) {
                case 1: menuDaftarTransaksi(); break;
                case 2: menuBudgeting(); break;  
                case 3: tampilkanLaporan(); break;
                case 4: analisisKeuangan(); break;
                case 5: cout << "Terima kasih telah menggunakan aplikasi ini.\n"; break;
                default: cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != 5);
    }

private:


void menuBudgeting() {
    int pilih;
    char lanjut = 'y';

    vector<string> kategoriList = {
        "Makan", "Transportasi", "Self Reward", "Dana Darurat", "Lainnya"
    };

    do {
        cout << "\n=======================================" << endl;
        cout << "              🧾 MENU BUDGETING         " << endl;
        cout << "=======================================" << endl;

        cout << "Pilih kategori untuk di-budgets:\n";
        for (size_t i = 0; i < kategoriList.size(); ++i) {
            cout << i + 1 << ". " << kategoriList[i] << endl;
        }

        cout << "Pilih kategori (1-" << kategoriList.size() << "): ";
        while (!(cin >> pilih) || pilih < 1 || pilih > kategoriList.size()) {
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

        cout << "\n✅ Budget berhasil dicatat!" << endl;
        cout << "Kategori : " << kategori << endl;
        cout << "Budget   : Rp " << fixed << setprecision(2) << nominal << endl;

        cout << "\nIsi budget kategori lain? (y/t): ";
        cin >> lanjut;
        lanjut = tolower(lanjut);

    } while (lanjut == 'y');

    cout << "\nKembali ke Menu Utama...\n";
}

// =========================================================
// MENU TRANSAKSI, INCOME, EXPENSE (tidak diubah) 
// =========================================================
void menuDaftarTransaksi() {
    int pilihanTransaksi;
    do {
        cout << "\n--- 1. DAFTAR TRANSAKSI ---" << endl;
        cout << "1. Catat Income (Pemasukan)" << endl;
        cout << "2. Catat Expense (Pengeluaran)" << endl;
        cout << "3. Kembali ke Menu Utama" << endl;
        cout << "Pilih opsi (1-3): ";

        if (!(cin >> pilihanTransaksi)) {
            cout << "Input tidak valid.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihanTransaksi = 0;
            continue;
        }

        switch (pilihanTransaksi) {
            case 1: catatIncome(); break;
            case 2: catatExpense(); break;
            case 3: cout << "\nKembali ke Menu Utama...\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }

    } while (pilihanTransaksi != 3);
}

void catatIncome() {
    string tgl, desk;
    double jml;
    char lanjut = 'y';

    cout << "\n=======================================" << endl;
    cout << "         💸 SUB-MENU: CATAT INCOME      " << endl;
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

        cout << "\n✅ INCOME BERHASIL DICATAT!" << endl;
        cout << "➡ TOTAL INCOME SAAT INI: Rp " << fixed << setprecision(2) << totalIncome << endl;


        cout << "Catat income lagi? (y/t): ";
        cin >> lanjut;
        lanjut = tolower(lanjut);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (lanjut == 'y');
}

void catatExpense() {
    string tgl, desk, tipe = "Pengeluaran";
    double jml;
    int kategoriPilihan;
    char lanjut = 'y';

    vector<string> kategoriList = {
        "Makan", "Transportasi", "Self Reward", "Dana Darurat", "Lainnya"
    };

    cout << "\n=======================================" << endl;
    cout << "      🛒 SUB-MENU: CATAT PENGELUARAN    " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Pilih Kategori Pengeluaran:\n";
        for (size_t i = 0; i < kategoriList.size(); ++i) {
            cout << i + 1 << ". " << kategoriList[i] << endl;
        }

        cout << "Pilih kategori (1-" << kategoriList.size() << "): ";
        while (!(cin >> kategoriPilihan) || kategoriPilihan < 1 || kategoriPilihan > kategoriList.size()) {
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

        cout << "\n✅ PENGELUARAN BERHASIL DICATAT!" << endl;
        cout << "➡ TOTAL PENGELUARAN SAAT INI: Rp " << fixed << setprecision(2) << totalExpense << endl;

        // 🔥 Hitung sisa budget kategori
        if (budgetKategori.find(kategori) != budgetKategori.end()) {
            double sisaBudget = budgetKategori[kategori] - jml;
            budgetKategori[kategori] = sisaBudget; // update sisa budget
            cout << "➡ SISA BUDGET KATEGORI '" << kategori << "': Rp " 
                 << fixed << setprecision(2) << (sisaBudget >= 0 ? sisaBudget : 0) << endl;
            if (sisaBudget < 0) {
                cout << "⚠️ Budget kategori ini sudah terlampaui!" << endl;
            }
        } else {
            cout << "⚠️ Belum ada budget untuk kategori '" << kategori << "'." << endl;
        }

        cout << "Catat pengeluaran lagi? (y/t): ";
        cin >> lanjut;
        lanjut = tolower(lanjut);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (lanjut == 'y');
}




void tampilkanRingkasan() const {
    double saldoAkhir = totalIncome - totalExpense;

    cout << "\n--- RINGKASAN KEUANGAN ---" << endl;
    cout << "Total Income     : Rp " << totalIncome << endl;
    cout << "Total Pengeluaran: Rp " << totalExpense << endl;
    cout << "Saldo Akhir      : Rp " << saldoAkhir << endl;
}

void tampilkanLaporan() const {
    cout << "\n=======================================" << endl;
    cout << "          📜 LAPORAN KEUANGAN          " << endl;
    cout << "=======================================\n";

    if (daftarTransaksi.empty()) {
        cout << "Belum ada transaksi.\n";
        return;
    }

    cout << "+------------+------------------------------------------+--------------+------------------+" << endl;
    cout << "| Tanggal    | Deskripsi                                | Jumlah (Rp)  | Tipe Transaksi   |" << endl;
    cout << "+------------+------------------------------------------+--------------+------------------+" << endl;

    for (const auto& t : daftarTransaksi) t.tampilkan();

    cout << "+------------+------------------------------------------+--------------+------------------+" << endl;

    tampilkanRingkasan();
}

void analisisKeuangan() const {
    cout << "\n=======================================" << endl;
    cout << "        📈 ANALISIS KEUANGAN           " << endl;
    cout << "=======================================\n";

    if (daftarTransaksi.empty()) {
        cout << "Belum ada data dianalisis.\n";
        return;
    }

    tampilkanRingkasan();
}
};

int main() {
    cout << fixed << setprecision(2);

    ManajemenKeuangan app;
    app.jalankan();
    return 0;
}