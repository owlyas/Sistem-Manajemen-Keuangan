MYMO – Aplikasi Manajemen Keuangan Pribadi
Kelompok 7 – Proyek Akhir Algoritma dan Pemrograman
Anggota:

Salsabila Putri (240505300 02)
Nbasya Aulia (240505300 09)
Zaun Nawa (240505300 10)

Deskripsi Singkat
MYMO adalah aplikasi berbasis Command Line Interface (CLI) untuk membantu pengguna mengelola keuangan pribadi.
Aplikasi ini memungkinkan pengguna untuk mencatat transaksi pemasukan (income) dan pengeluaran (expense) dengan kategori, menghitung saldo otomatis, mengatur budget, menampilkan laporan, serta menganalisis pola keuangan bulanan.

=============================================================================================================

Fitur Utama
Catat Transaksi -- > Mencatat income dan expense dengan kategori dan deskripsi, Menghitung total income, total expense, dan saldo secara otomatis, Menampilkan daftar transaksi dan pencarian berdasarkan tanggal, kategori, atau deskripsi.

Budgeting -- > Menetapkan budget per kategori, Memantau sisa budget dan memberikan peringatan jika terlampaui.

Laporan Keuangan --> Menampilkan ringkasan total income, total expense, dan saldo akhir, Menampilkan daftar transaksi berdasarkan kategori, tanggal, atau deskripsi.

Analisis Keuangan --> Mengurutkan pengeluaran terbesar, Membandingkan realisasi pengeluaran dengan budget yang ditentukan, Membantu pengguna merencanakan keuangan bulanan secara lebih bijak.

=============================================================================================================

Struktur Program

AppCLI.h / AppCLI.cpp → Menu utama, jalankan aplikasi, integrasi modul.

1Transaksi.h / Transaksi.cpp → Modul untuk input, pencatatan, dan pengelolaan transaksi.

2Budgeting.h / Budgeting.cpp → Modul untuk pengaturan dan monitoring budget per kategori.

3Laporan.h / Laporan.cpp → Modul untuk menampilkan laporan keuangan.

4Analisis.h / Analisis.cpp → Modul untuk analisis pengeluaran dan perbandingan dengan budget.

=============================================================================================================

Struktur Data:

vector<Transaksi> digunakan sebagai array dinamis untuk menyimpan daftar transaksi.

map<string, double> digunakan untuk menyimpan budget per kategori.

=============================================================================================================

Cara Menjalankan Aplikasi

Compile semua file .cpp menggunakan compiler C++ (misal g++).

g++ AppCLI.cpp Transaksi.cpp Budgeting.cpp Laporan.cpp Analisis.cpp -o MYMO


Jalankan aplikasi:

./MYMO


Ikuti menu CLI untuk:

Mencatat transaksi

Mengatur budget

Melihat laporan keuangan

Melakukan analisis

=============================================================================================================

Teknologi yang Digunakan

Bahasa Pemrograman: C++

Struktur Data: vector, map

Platform: Command Line Interface (CLI)

Catatan Tambahan

Input harus sesuai format, misal nominal uang berupa angka positif dan tanggal dalam format YYYY-MM-DD.

MYMO masih berbasis CLI, sehingga cocok untuk desktop/terminal.
