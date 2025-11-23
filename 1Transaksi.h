#ifndef FITUR_TRANSAKSI_H
#define FITUR_TRANSAKSI_H

#include <vector>
#include <map>
#include <string>
#include "Transaksi.h"

class FiturTransaksi {
public:
    void catatIncome(std::vector<Transaksi> &daftarTransaksi, double &totalIncome);
    void catatExpense(std::vector<Transaksi> &daftarTransaksi,
                      double &totalExpense,
                      std::map<std::string,double> &budgetKategori);
};

#endif
