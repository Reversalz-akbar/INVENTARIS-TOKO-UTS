#include "Produk.h"

Produk::Produk(const std::string& kode,
               const std::string& nama,
               double             harga,
               int                stok)
    : kodeProduk(kode), nama(nama), harga(harga), stok(stok) {}
