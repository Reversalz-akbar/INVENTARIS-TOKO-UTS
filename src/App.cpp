#include "App.h"
#include "Laporan.h"
#include <iostream>
#include <string>

App::App(std::vector<Stok>& stok) : daftarBarang(stok) {}

void App::tampilkanMenu() {
    std::cout << "\n=== MENU LAPORAN ===\n"
              << "1. Cari Produk\n"
              << "2. Filter Stok Rendah\n"
              << "3. Produk Termahal\n"
              << "4. Filter Berdasarkan Kategori\n"
              << "5. Buat Laporan Penjualan\n"
              << "0. Kembali ke Menu Utama\n";
}

void App::prosesPilihan() {
    int pilihan;
    do {
        tampilkanMenu();
        std::cout << "Pilih: ";
        std::cin >> pilihan;
        std::cin.ignore();

        switch (pilihan) {
            case 1: cariProduk(); break;
            case 2: {
                int ambang;
                std::cout << "Masukkan batas stok: ";
                std::cin >> ambang;
                Laporan::tampilkanStokRendah(daftarBarang, ambang);
                break;
            }
            case 3:
                Laporan::tampilkanProdukTermahal(daftarBarang);
                break;
            case 4: {
                std::string kat;
                std::cout << "Masukkan kata kunci kategori: ";
                std::getline(std::cin, kat);
                Laporan::tampilkanProdukByKategori(daftarBarang, kat);
                break;
            }
            case 5:
                Laporan::buatLaporanPenjualan("transaksi.txt", "laporan_penjualan.txt");
                break;
            case 0:
                std::cout << "Kembali ke menu utama...\n"; break;
            default:
                std::cout << "Pilihan tidak valid\n";
        }
    } while (pilihan != 0);
}

void App::cariProduk() {
    std::string keyword;
    std::cout << "Masukkan nama produk yang dicari: ";
    std::getline(std::cin, keyword);

    std::cout << "=== Hasil Pencarian ===\n";
    for (const auto& s : daftarBarang) {
        if (s.namaStok().find(keyword) != std::string::npos) {
            std::cout << s.Info() << "\n";
        }
    }
}
