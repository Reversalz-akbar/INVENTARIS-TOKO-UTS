#include "stok.h"
#include "transaksi.h"
#include "Elektronik.h"
#include "Pakaian.h"
#include "Makanan.h"
#include "App.h"
#include <vector>
#include <fstream>
#include <limits>
#include <iostream>
#include <ctime>

void muatDataStok(const std::string& filename, std::vector<Stok>& daftar) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Gagal membuka file " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            daftar.emplace_back(Stok::loadDataDariBaris(line));
        }
    }
}

void simpanStok(const std::string& filename, const std::vector<Stok>& daftar) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Gagal menyimpan ke file!\n";
        return;
    }
    for (const auto& s : daftar) {
        file << s.kodeStok() << ","
             << s.namaStok() << ","
             << s.TotalStok() << ","
             << s.HargaStok() << "\n";
    }
}

void catatTransaksi(const std::string& filename, const std::string& kode, const std::string& aksi, int jumlah) {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cout << "Gagal mencatat transaksi!\n";
        return;
    }

    time_t now = time(0);
    tm* localTime = localtime(&now);

    file << kode << "," << aksi << "," << jumlah << ","
         << (localTime->tm_year + 1900) << "-"
         << (localTime->tm_mon + 1) << "-"
         << localTime->tm_mday << " "
         << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec
         << "\n";
}

int main() {
    // ✅ Banner ASCII Art tanpa warning
    std::cout << " _                      _             _       _        _         \n";
    std::cout << "(_) _ ____   _____ _ __| |_ __ _ _ __(_)___  | |_ ___ | | _____  \n";
    std::cout << "| || '_ \\ \\ / / _ \\ '__| __/ _` | '__| / __| | __/ _ \\| |/ / _ \\ \n";
    std::cout << "| || | | \\ V /  __/ |  | || (_| | |  | \\__ \\ | || (_) |   < (_) |\n";
    std::cout << "|_||_| |_|\\_/ \\___|_|   \\__\\__,_|_|  |_|___/  \\__\\___/|_|\\_\\___/ \n";
    std::cout << "                                                                 \n";
    std::cout << "     SISTEM INVENTARIS & TRANSAKSI TOKO  CLI EDITION            \n";
    std::cout << "=================================================================\n";

    std::vector<Stok> inventarisToko;
    muatDataStok("stok_terkini.txt", inventarisToko);
    App app(inventarisToko);

    int pilihan;
    std::string kode, nama;
    int jumlah;
    double harga;

    while (true) {
        std::cout << "\n1. Lihat Stok\n2. Tambah Stok\n3. Kurangi Stok\n4. Retur Stok\n5. Update Stok\n6. Keluar\n7. Pembelian\n8. Laporan & Filter Produk\nPilihan: ";
        std::cin >> pilihan;

        if (pilihan == 1) {
            for (const auto& s : inventarisToko)
                std::cout << s.Info() << '\n';

        } else if (pilihan == 2) {
            std::cout << "Kode: ";
            std::cin >> kode;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nama: ";
            std::getline(std::cin, nama);
            std::cout << "Jumlah: ";
            std::cin >> jumlah;
            std::cout << "Harga: ";
            std::cin >> harga;

            inventarisToko.emplace_back(kode, nama, jumlah, harga);
            simpanStok("stok_terkini.txt", inventarisToko);

        } else if (pilihan == 3) {
            std::cout << "Kode barang: ";
            std::cin >> kode;
            std::cout << "Jumlah dikurangi: ";
            std::cin >> jumlah;

            bool ditemukan = false;
            for (auto& s : inventarisToko) {
                if (s.kodeStok() == kode) {
                    s.kurangStok(jumlah);
                    ditemukan = true;
                    break;
                }
            }

            if (ditemukan)
                simpanStok("stok_terkini.txt", inventarisToko);
            else
                std::cout << "Kode tidak ditemukan.\n";

        } else if (pilihan == 4) {
            std::cout << "Kode barang: ";
            std::cin >> kode;
            std::cout << "Jumlah retur: ";
            std::cin >> jumlah;

            bool ditemukan = false;
            for (auto& s : inventarisToko) {
                if (s.kodeStok() == kode) {
                    s.returStok(jumlah);
                    catatTransaksi("transaksi.txt", kode, "retur", jumlah);
                    simpanStok("stok_terkini.txt", inventarisToko);
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan)
                std::cout << "Kode tidak ditemukan.\n";

        } else if (pilihan == 5) {
            std::cout << "Kode: ";
            std::cin >> kode;
            std::cin.ignore();
            std::cout << "Nama baru: ";
            std::getline(std::cin, nama);
            std::cout << "Harga baru: ";
            std::cin >> harga;
            std::cout << "Jumlah baru: ";
            std::cin >> jumlah;

            bool ditemukan = false;
            for (auto& s : inventarisToko) {
                if (s.kodeStok() == kode) {
                    s.updateStok(nama, harga, jumlah);
                    simpanStok("stok_terkini.txt", inventarisToko);
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan)
                std::cout << "Kode tidak ditemukan.\n";

        } else if (pilihan == 6) {
            std::cout << "Menyimpan data dan keluar...\n";
            simpanStok("stok_terkini.txt", inventarisToko);
            break;

        } else if (pilihan == 7) {
            std::cout << "Kode barang: ";
            std::cin >> kode;
            std::cout << "Jumlah beli: ";
            std::cin >> jumlah;

            bool ditemukan = false;
            for (auto& s : inventarisToko) {
                if (s.kodeStok() == kode) {
                    Transaksi trx(s);
                    trx.beliBarang(jumlah);
                    simpanStok("stok_terkini.txt", inventarisToko);
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan)
                std::cout << "Kode tidak ditemukan.\n";

        } else if (pilihan == 8) {
            app.prosesPilihan();  // fitur mahasiswa 3
        } else {
            std::cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}
