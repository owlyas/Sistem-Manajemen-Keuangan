#ifndef FITUR_ANALISIS_H
#define FITUR_ANALISIS_H

#include <vector>
#include <map>
#include <string>
#include "Transaksi.h"

class FiturAnalisis {
public:
    void tampilkanTop5Pengeluaran(const std::vector<Transaksi> &daftarTransaksi) const;
    void tampilkanBudgetVsActual(const std::vector<Transaksi> &daftarTransaksi,
                                 const std::map<std::string,double> &budgetKategori) const;
    void analisisKeuangan(const std::vector<Transaksi> &daftarTransaksi,
                          double totalIncome,
                          double totalExpense,
                          const std::map<std::string,double> &budgetKategori) const;
};

#endif
