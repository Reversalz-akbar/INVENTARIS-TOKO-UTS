#include "Makanan.h"
#include <iostream>

using namespace std;

Makanan::Makanan(const std::string& kode,
                 const std::string& nama,
                 double             harga,
                 int                stok)
    : Produk(kode, nama, harga, stok) {}

void Makanan::tampilkanInfo() const {
    cout << "[Makanan] " << nama
         << " | Harga: " << harga
         << " | Stok: "  << stok
         << " | Diskon: " << diskon()
         << endl;
}
