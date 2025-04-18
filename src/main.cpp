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

void muatDataStok(const std::string& filename, std::vector<Stok>& daftarBarang) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Gagal membuka file " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            daftarBarang.push_back(Stok::loadDataDariBaris(line));
        }
    }
    file.close();
}

void simpanStokKeFile(const std::string& filename, const std::vector<Stok>& daftarBarang) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Gagal membuka file untuk menyimpan!" << std::endl;
        return;
    }
    for (const auto& s : daftarBarang) {
        file << s.kodeStok() << ","
             << s.namaStok() << ","
             << s.TotalStok() << ","
             << s.HargaStok() << "\n";
    }
    file.close();
}

void catatTransaksi(const std::string& filename, const std::string& kode, const std::string& aksi, int jumlah) {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cout << "Gagal membuka file transaksi!" << std::endl;
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

    file.close();
}

int main() {
    std::vector<Stok> daftarBarang;
    muatDataStok("stok_terkini.txt", daftarBarang);
    App app(daftarBarang); // Inisialisasi App

    int pilihan;
    std::string kode, nama;
    int jumlah;
    double harga;

    while (true) {
        std::cout << "\n1. Lihat Stok\n2. Tambah Stok\n3. Kurangi Stok\n4. Retur Stok\n5. Update Stok\n6. Keluar\n7. Pembelian\n8. Laporan & Filter Produk\nPilihan: ";
        std::cin >> pilihan;

        if (pilihan == 1) {
            if (daftarBarang.empty()) {
                std::cout << "Daftar barang kosong!" << std::endl;
            } else {
                for (const auto& s : daftarBarang) {
                    std::cout << s.Info() << std::endl;
                }
            }
        } else if (pilihan == 2) {
            std::cout << "\nKode: ";
            std::cin >> kode;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nama: ";
            std::getline(std::cin, nama);

            std::cout << "Jumlah: "; std::cin >> jumlah;
            std::cout << "Harga: "; std::cin >> harga;
            daftarBarang.emplace_back(kode, nama, jumlah, harga);
            simpanStokKeFile("stok_terkini.txt", daftarBarang);
        } else if (pilihan == 3) {
            std::cout << "Masukkan kode barang: ";
            std::cin >> kode;
            std::cout << "Masukkan jumlah barang untuk dikurangi: ";
            std::cin >> jumlah;

            bool ditemukan = false;
            for (auto& s : daftarBarang) {
                if (s.kodeStok() == kode) {
                    s.kurangStok(jumlah);
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan) {
                std::cout << "Barang dengan kode " << kode << " tidak ditemukan!\n";
            } else {
                simpanStokKeFile("stok_terkini.txt", daftarBarang);
            }
        } else if (pilihan == 4) {
            std::cout << "Masukkan kode barang: ";
            std::cin >> kode;
            std::cout << "Masukkan jumlah barang untuk retur: ";
            std::cin >> jumlah;

            bool ditemukan = false;
            for (auto& s : daftarBarang) {
                if (s.kodeStok() == kode) {
                    s.returStok(jumlah);
                    catatTransaksi("transaksi.txt", kode, "retur", jumlah);
                    simpanStokKeFile("stok_terkini.txt", daftarBarang);
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan) {
                std::cout << "Kode barang tidak ditemukan dalam daftar stok!" << std::endl;
            }
        } else if (pilihan == 5) {
            std::cout << "Kode: "; std::cin >> kode;
            std::cin.ignore();

            std::cout << "Nama baru: "; std::getline(std::cin, nama);
            std::cout << "Harga baru: "; std::cin >> harga;
            std::cout << "Jumlah baru: "; std::cin >> jumlah;

            bool ditemukan = false;
            for (auto& s : daftarBarang) {
                if (s.kodeStok() == kode) {
                    s.updateStok(nama, harga, jumlah);
                    simpanStokKeFile("stok_terkini.txt", daftarBarang);
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan) {
                std::cout << "Kode barang tidak ditemukan untuk diupdate!" << std::endl;
            }
        } else if (pilihan == 6) {
            break;
        } else if (pilihan == 7) {
            std::cout << "Masukkan kode barang yang ingin dibeli: ";
            std::cin >> kode;
            std::cout << "Masukkan jumlah yang ingin dibeli: ";
            std::cin >> jumlah;

            bool ditemukan = false;
            for (auto& s : daftarBarang) {
                if (s.kodeStok() == kode) {
                    Transaksi transaksi(s);
                    transaksi.beliBarang(jumlah);
                    simpanStokKeFile("stok_terkini.txt", daftarBarang);
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan) {
                std::cout << "Barang dengan kode tersebut tidak ditemukan.\n";
            }
        } else if (pilihan == 8) {
            app.prosesPilihan(); // 🔥 Fitur Mahasiswa 3
        } else {
            std::cout << "Pilihan tidak valid!" << std::endl;
        }
    }

    return 0;
}
