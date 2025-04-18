#include "stok.h"

Stok::Stok(const std::string& k, const std::string& n, int j, double h)
    : kode(k), nama(n), jumlah(j), harga(h) {}

Stok Stok::loadDataDariBaris(const std::string& line) {
    std::istringstream stream(line);
    std::string kode, nama;
    int jumlah;
    double harga;

    std::getline(stream, kode, ',');
    std::getline(stream, nama, ',');
    stream >> jumlah;
    stream.ignore(); 
    stream >> harga;

    return Stok(kode, nama, jumlah, harga);
}

void Stok::kurangStok(int j) {
    jumlah -= j;
}

void Stok::returStok(int j) {
    jumlah += j;
}

void Stok::updateStok(const std::string& n, double h, int j) {
    nama = n;
    harga = h;
    jumlah = j;
}

std::string Stok::Info() const {
    return "Kode: " + kode + ", Nama: " + nama + ", Jumlah: " + std::to_string(jumlah) + ", Harga: " + std::to_string(harga);
}

void Stok::simpanDataKeFile(std::ofstream& file) const {
    file << kode << "," << nama << "," << jumlah << "," << harga << "\n";
}
