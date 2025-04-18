#include "transaksi.h"
#include <fstream>
#include <iostream>

Transaksi::Transaksi(Stok& s) : stok(s) {}

void Transaksi::beliBarang(int jumlah) {
    if (stok.TotalStok() >= jumlah) {
        stok.kurangStok(jumlah);
        simpanTransaksi("transaksi.txt", "Pembelian", jumlah);
    } else {
        std::cout << "Stok tidak cukup untuk pembelian!\n";
    }
}

void Transaksi::returBarang(int jumlah) {
    stok.returStok(jumlah);
    simpanTransaksi("transaksi.txt", "Retur", jumlah);
}

void Transaksi::simpanTransaksi(const std::string& filename, const std::string& jenisTransaksi, int jumlah) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << jenisTransaksi << ", Kode: " << stok.kodeStok()
             << ", Nama: " << stok.namaStok() << ", Jumlah: " << jumlah
             << ", Harga: " << stok.HargaStok() << "\n";
        file.close();
        std::cout << "Transaksi disimpan ke file: " << filename << "\n";
    } else {
        std::cout << "Gagal membuka file transaksi!\n";
    }
}
