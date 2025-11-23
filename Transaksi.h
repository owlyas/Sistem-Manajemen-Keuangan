#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include <iostream>
#include <iomanip>
#include <string>

class Transaksi {
public:
    std::string tanggal;
    std::string deskripsi;
    double jumlah;
    std::string tipe;

    Transaksi(std::string tgl, std::string desk, double jml, std::string tp)
        : tanggal(tgl), deskripsi(desk), jumlah(jml), tipe(tp) {}

    void tampilkan() const {
        std::cout << "| " << std::setw(10) << std::left << tanggal
                  << "| " << std::setw(40) << std::left << deskripsi
                  << "| " << std::setw(12) << std::right << std::fixed << std::setprecision(2) << jumlah
                  << "| " << std::setw(15) << std::left << tipe << " |" << std::endl;
    }
};

#endif
