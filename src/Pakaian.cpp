#include "Pakaian.h"
#include <iostream>

using namespace std;

Pakaian::Pakaian(const std::string& kode,
                 const std::string& nama,
                 double             harga,
                 int                stok)
    : Produk(kode, nama, harga, stok) {}

void Pakaian::tampilkanInfo() const {
    cout << "[Pakaian] " << nama
         << " | Harga: " << harga
         << " | Stok: "  << stok
         << " | Diskon: " << diskon()
         << endl;
}
