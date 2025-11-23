#ifndef APP_CLI_H
#define APP_CLI_H

#include <vector>
#include <map>
#include <string>
#include "Transaksi.h"
#include "1Transaksi.h"
#include "2Budgeting.h"
#include "3Laporan.h"
#include "4Analisis.h"

class AppCLI {
private:
    std::vector<Transaksi> daftarTransaksi;
    double totalIncome;
    double totalExpense;
    std::map<std::string,double> budgetKategori;

    FiturTransaksi fiturTransaksi;
    FiturBudget fiturBudget;
    FiturLaporan fiturLaporan;
    FiturAnalisis fiturAnalisis;

    void tampilkanMenuUtama() const;

public:
    AppCLI();
    void run();
};

#endif
