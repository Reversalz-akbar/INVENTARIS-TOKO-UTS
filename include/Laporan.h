#ifndef LAPORAN_H
#define LAPORAN_H

#include "stok.h"
#include <vector>
#include <string>

namespace Laporan {
    void tampilkanStokRendah(const std::vector<Stok>& daftar, int ambangStok);
    void tampilkanProdukTermahal(const std::vector<Stok>& daftar);
    void tampilkanProdukByKategori(const std::vector<Stok>& daftar, const std::string& kategori);
    void buatLaporanPenjualan(const std::string& transaksiFile, const std::string& outputFile);
}

#endif
