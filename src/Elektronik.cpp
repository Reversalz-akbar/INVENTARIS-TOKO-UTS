#include "Elektronik.h"
#include <iostream>

using namespace std;

Elektronik::Elektronik(const std::string& kode,
                       const std::string& nama,
                       double             harga,
                       int                stok)
    : Produk(kode, nama, harga, stok) {}

void Elektronik::tampilkanInfo() const {
    cout << "[Elektronik] " << nama
         << " | Harga: "   << harga
         << " | Stok: "    << stok
         << " | Diskon: "  << diskon()
         << endl;
}
