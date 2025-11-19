<<<<<<< HEAD
=======
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <map> // Diperlukan untuk Analisis Keuangan

using namespace std;

// Kelas Transaksi untuk menyimpan detail setiap catatan pemasukan atau pengeluaran
class Transaksi {
public:
    string tanggal;
    string deskripsi;
    double jumlah;
    string tipe; // "Pemasukan" atau "Pengeluaran"

    Transaksi(string tgl, string desk, double jml, string tp)
        : tanggal(tgl), deskripsi(desk), jumlah(jml), tipe(tp) {}

    // Metode untuk menampilkan detail transaksi dalam format tabel
    void tampilkan() const {
        cout << "| " << setw(10) << left << tanggal
             << "| " << setw(40) << left << deskripsi
             << "| " << setw(12) << right << fixed << setprecision(2) << jumlah
             << "| " << setw(15) << left << tipe << " |" << endl;
    }
};

// Kelas utama untuk mengelola semua fungsionalitas aplikasi
class ManajemenKeuangan {
private:
    vector<Transaksi> daftarTransaksi;
    double totalIncome = 0.0;
    double totalExpense = 0.0; // Variabel baru untuk melacak total pengeluaran

public:
    // Menampilkan menu utama aplikasi
    void tampilkanMenuUtama() const {
        cout << "\n=======================================" << endl;
        cout << "    APLIKASI MANAJEMEN KEUANGAN (CLI)    " << endl;
        cout << "=======================================" << endl;
        cout << "1. Daftar Transaksi (Catat Income/Expense)" << endl;
        cout << "2. Budgeting (Belum Tersedia)" << endl;
        cout << "3. Laporan Keuangan" << endl;
        cout << "4. Analisis Keuangan" << endl;
        cout << "5. Keluar" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Pilih menu (1-5): ";
    }

    // Loop utama untuk menjalankan aplikasi
    void jalankan() {
        int pilihan;
        do {
            tampilkanMenuUtama();
            // Cek apakah input valid
            if (!(cin >> pilihan)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pilihan = 0; // Set ke 0 agar masuk ke default case
            }

            switch (pilihan) {
                case 1:
                    menuDaftarTransaksi();
                    break;
                case 2:
                    cout << "\n[MENU 2: Budgeting] - Belum diimplementasikan" << endl;
                    break;
                case 3:
                    tampilkanLaporan(); // Implementasi Laporan
                    break;
                case 4:
                    analisisKeuangan(); // Implementasi Analisis Keuangan
                    break;
                case 5:
                    cout << "Terima kasih telah menggunakan aplikasi ini. Sampai jumpa!" << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
        } while (pilihan != 5);
    }

private:
    // Sub-menu untuk pencatatan transaksi
    void menuDaftarTransaksi() {
        int pilihanTransaksi;
        do {
            cout << "\n--- 1. DAFTAR TRANSAKSI ---" << endl;
            cout << "1. Catat Income (Pemasukan)" << endl;
            cout << "2. Catat Expense (Pengeluaran)" << endl;
            cout << "3. Kembali ke Menu Utama" << endl;
            cout << "Pilih opsi (1-3): ";

            if (!(cin >> pilihanTransaksi)) {
                cout << "Input tidak valid. Harap masukkan angka." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pilihanTransaksi = 0;
                continue;
            }

            switch (pilihanTransaksi) {
                case 1:
                    catatIncome();
                    break;
                case 2:
                    catatExpense(); // Panggil fungsi Catat Expense
                    break;
                case 3:
                    cout << "\nKembali ke Menu Utama..." << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
            }

        } while (pilihanTransaksi != 3);
    }

    // Fungsi untuk mencatat Pemasukan (Income)
    void catatIncome() {
        string tgl, desk;
        double jml;
        char lanjut = 'y';

        cout << "\n=======================================" << endl;
        cout << "         💸 SUB-MENU: CATAT INCOME      " << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Pastikan buffer input kosong

        do {
            cout << "---------------------------------------" << endl;
            cout << "Tanggal Income (YYYY-MM-DD): ";
            getline(cin, tgl);

            cout << "Nominal Income (Rp): ";
            while (!(cin >> jml) || jml <= 0) {
                cout << "Input nominal tidak valid. Masukkan angka positif: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // buang newline sisa

            cout << "Keterangan: ";
            getline(cin, desk);

            daftarTransaksi.emplace_back(tgl, desk, jml, "Pemasukan");
            totalIncome += jml;

            cout << "\n✅ INCOME BERHASIL DICATAT!" << endl;
            cout << "➡️ TOTAL INCOME SAAT INI: Rp " << fixed << setprecision(2) << totalIncome << endl;

            cout << "Catat income lagi? (y/t): ";
            if (!(cin >> lanjut)) {
                lanjut = 't';
            }
            lanjut = tolower(lanjut);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (lanjut == 'y');

        cout << "Kembali ke Menu Daftar Transaksi." << endl;
    }

    // Fungsi baru untuk mencatat Pengeluaran (Expense)
    void catatExpense() {
        string tgl, desk, tipe = "Pengeluaran";
        double jml;
        int kategoriPilihan;
        char lanjut = 'y';

        // Definisi kategori pengeluaran sesuai permintaan
        vector<string> kategoriList = {"Makan", "Transportasi", "Self Reward", "Dana Darurat", "Lainnya"};

        cout << "\n=======================================" << endl;
        cout << "      🛒 SUB-MENU: CATAT PENGELUARAN    " << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Pastikan buffer input kosong

        do {
            cout << "---------------------------------------" << endl;

            // 1. Tampilkan dan Pilih Kategori
            cout << "Pilih Kategori Pengeluaran:" << endl;
            for (size_t i = 0; i < kategoriList.size(); ++i) {
                cout << i + 1 << ". " << kategoriList[i] << endl;
            }
            cout << "Pilih kategori (1-" << kategoriList.size() << "): ";

            while (!(cin >> kategoriPilihan) || kategoriPilihan < 1 || kategoriPilihan > kategoriList.size()) {
                cout << "Pilihan tidak valid. Masukkan angka 1 sampai " << kategoriList.size() << ": ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            string kategori = kategoriList[kategoriPilihan - 1];
            
            // Buang newline sisa setelah input angka kategori
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

            // 2. Set Tanggal
            cout << "Tanggal Pengeluaran (YYYY-MM-DD): ";
            getline(cin, tgl);

            // 3. Nominal
            cout << "Nominal Pengeluaran (Rp): ";
            while (!(cin >> jml) || jml <= 0) {
                cout << "Input nominal tidak valid. Masukkan angka positif: ";
                cout << "Nominal Pengeluaran (Rp): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Buang newline sisa

            // 4. Keterangan (Deskripsi)
            cout << "Keterangan (Opsional): ";
            getline(cin, desk);

            // Gabungkan kategori ke deskripsi
            string deskripsiLengkap = "[" + kategori + "] " + (desk.empty() ? "Tanpa Keterangan" : desk);

            // Catat Transaksi
            daftarTransaksi.emplace_back(tgl, deskripsiLengkap, jml, tipe);
            totalExpense += jml;

            cout << "\n✅ PENGELUARAN BERHASIL DICATAT!" << endl;
            cout << "Kategori: " << kategori << endl;
            cout << "➡️ TOTAL PENGELUARAN SAAT INI: Rp " << fixed << setprecision(2) << totalExpense << endl;

            // 5. Looping
            cout << "Catat pengeluaran lagi? (y/t): ";
            if (!(cin >> lanjut)) {
                lanjut = 't';
            }
            lanjut = tolower(lanjut);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (lanjut == 'y');

        cout << "Kembali ke Menu Daftar Transaksi." << endl;
    }

    // Menampilkan ringkasan keuangan
    void tampilkanRingkasan() const {
        double saldoAkhir = totalIncome - totalExpense;

        cout << "\n--- RINGKASAN KEUANGAN ---" << endl;
        cout << "Total Pemasukan (Income): " << setw(10) << right << fixed << setprecision(2) << totalIncome << " Rp" << endl;
        cout << "Total Pengeluaran (Expense): " << setw(9) << right << fixed << setprecision(2) << totalExpense << " Rp" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Saldo Akhir: " << setw(23) << right << fixed << setprecision(2) << saldoAkhir << " Rp" << endl;
        cout << "---------------------------------------" << endl;
        
        if (saldoAkhir < 0) {
            cout << "⚠️ PERINGATAN: Pengeluaran melebihi pemasukan! Anda defisit." << endl;
        } else if (saldoAkhir == 0) {
            cout << "⚖️ Saldo Anda seimbang." << endl;
        } else {
            cout << "👍 Saldo Anda positif. Kelola uang Anda dengan bijak!" << endl;
        }
    }

    // Fungsi untuk menampilkan Laporan Keuangan (Menu 3)
    void tampilkanLaporan() const {
        cout << "\n=======================================" << endl;
        cout << "          📜 LAPORAN KEUANGAN          " << endl;
        cout << "=======================================" << endl;

        if (daftarTransaksi.empty()) {
            cout << "Belum ada transaksi yang dicatat." << endl;
            return;
        }

        // Header Tabel
        cout << "+------------+------------------------------------------+--------------+------------------+" << endl;
        cout << "| Tanggal    | Deskripsi                                | Jumlah (Rp)  | Tipe Transaksi   |" << endl;
        cout << "+------------+------------------------------------------+--------------+------------------+" << endl;

        // Isi Tabel (Tampilkan semua transaksi)
        for (const auto& t : daftarTransaksi) {
            t.tampilkan();
        }

        // Footer Tabel
        cout << "+------------+------------------------------------------+--------------+------------------+" << endl;
        
        // Ringkasan
        tampilkanRingkasan();
    }

    // Fungsi untuk menampilkan Analisis Keuangan sederhana (Menu 4)
    void analisisKeuangan() const {
        cout << "\n=======================================" << endl;
        cout << "        📈 ANALISIS KEUANGAN           " << endl;
        cout << "=======================================" << endl;

        if (daftarTransaksi.empty()) {
            cout << "Belum ada data untuk dianalisis." << endl;
            return;
        }

        tampilkanRingkasan();

        // Analisis Sederhana: Pengeluaran per Kategori (Hanya untuk pengeluaran)
        map<string, double> expenseByCategory;
        
        if (totalExpense > 0) {
            for (const auto& t : daftarTransaksi) {
                if (t.tipe == "Pengeluaran") {
                    // Ekstrak kategori dari deskripsi "[Kategori] Keterangan"
                    size_t start = t.deskripsi.find('[');
                    size_t end = t.deskripsi.find(']');
                    if (start != string::npos && end != string::npos && start < end) {
                        string kategoriKey = t.deskripsi.substr(start + 1, end - start - 1);
                        expenseByCategory[kategoriKey] += t.jumlah;
                    }
                }
            }

            cout << "\n--- PERSENTASE PENGELUARAN BERDASARKAN KATEGORI ---" << endl;
            cout << "+------------------+--------------+------------+" << endl;
            cout << "| Kategori         | Jumlah (Rp)  | Persentase |" << endl;
            cout << "+------------------+--------------+------------+" << endl;
            
            for (const auto& pair : expenseByCategory) {
                double persentase = (pair.second / totalExpense) * 100.0;
                cout << "| " << setw(16) << left << pair.first
                     << " | " << setw(12) << right << fixed << setprecision(2) << pair.second 
                     << " | " << setw(8) << right << fixed << setprecision(2) << persentase << "% |" << endl;
            }
            cout << "+------------------+--------------+------------+" << endl;
        } else {
            cout << "\nTidak ada pengeluaran yang dicatat untuk analisis kategori." << endl;
        }
    }
};

int main() {
    // Set format default untuk output double
    cout << fixed << setprecision(2);
    
    // Inisialisasi dan jalankan aplikasi
    ManajemenKeuangan app;
    app.jalankan();
    return 0;
}