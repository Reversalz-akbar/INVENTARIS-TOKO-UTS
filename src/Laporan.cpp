#include "Laporan.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void Laporan::tampilkanStokRendah(const std::vector<Stok>& daftar, int ambangStok) {
    std::cout << "\n=== Produk dengan Stok di bawah " << ambangStok << " ===\n";
    bool ada = false;
    for (const auto& s : daftar) {
        if (s.TotalStok() < ambangStok) {
            std::cout << s.Info() << "\n";
            ada = true;
        }
    }
    if (!ada) {
        std::cout << "Tidak ada produk dengan stok di bawah " << ambangStok << ".\n";
    }
}

void Laporan::tampilkanProdukTermahal(const std::vector<Stok>& daftar) {
    if (daftar.empty()) {
        std::cout << "Daftar barang kosong.\n";
        return;
    }

    auto maxIt = std::max_element(daftar.begin(), daftar.end(),
        [](const Stok& a, const Stok& b) {
            return a.HargaStok() < b.HargaStok();
        });

    std::cout << "\n=== Produk Termahal ===\n" << maxIt->Info() << "\n";
}

void Laporan::tampilkanProdukByKategori(const std::vector<Stok>& daftar, const std::string& kategori) {
    std::cout << "\n=== Produk dengan Kata Kunci \"" << kategori << "\" ===\n";
    bool ditemukan = false;
    for (const auto& s : daftar) {
        if (s.namaStok().find(kategori) != std::string::npos) {
            std::cout << s.Info() << "\n";
            ditemukan = true;
        }
    }
    if (!ditemukan) {
        std::cout << "Tidak ditemukan produk dengan kategori tersebut.\n";
    }
}

void Laporan::buatLaporanPenjualan(const std::string& transaksiFile, const std::string& outputFile) {
    std::ifstream in(transaksiFile);
    std::ofstream out(outputFile);

    if (!in.is_open()) {
        std::cout << "❌ Gagal membuka file transaksi: " << transaksiFile << "\n";
        return;
    }

    if (!out.is_open()) {
        std::cout << "❌ Gagal membuat file laporan: " << outputFile << "\n";
        return;
    }

    std::string line;
    out << "=== LAPORAN PENJUALAN ===\n\n";
    while (std::getline(in, line)) {
        out << line << "\n";
    }

    std::cout << "✅ Laporan berhasil disimpan di: " << outputFile << "\n";

    in.close();
    out.close();
}
