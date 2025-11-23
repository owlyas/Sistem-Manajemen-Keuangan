#ifndef FITUR_LAPORAN_H
#define FITUR_LAPORAN_H

#include <vector>
#include "Transaksi.h"

class FiturLaporan {
public:
    void tampilkanRingkasan(double totalIncome, double totalExpense) const;
    void tampilkanLaporan(const std::vector<Transaksi> &daftarTransaksi,
                          double totalIncome,
                          double totalExpense) const;

    void menuLaporanKeuangan(const std::vector<Transaksi> &daftarTransaksi,
                             double totalIncome,
                             double totalExpense);

    void cariTransaksi(const std::vector<Transaksi> &daftarTransaksi);
};

#endif
