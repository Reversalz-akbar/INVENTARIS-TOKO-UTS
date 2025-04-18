#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include "stok.h"
#include <string>

class Transaksi {
private:
    Stok& stok;  

public:
    Transaksi(Stok& s); 
    void beliBarang(int jumlah);  
    void returBarang(int jumlah);  
    void simpanTransaksi(const std::string& filename, const std::string& jenisTransaksi, int jumlah);  
};

#endif
