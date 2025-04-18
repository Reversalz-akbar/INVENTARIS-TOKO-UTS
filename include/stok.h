#ifndef STOK_H
#define STOK_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Stok {
private:
    std::string kode;
    std::string nama;
    int jumlah;
    double harga;

public:
    Stok(const std::string& k, const std::string& n, int j, double h);

    static Stok loadDataDariBaris(const std::string& line);

    std::string kodeStok() const { return kode; }
    std::string namaStok() const { return nama; }
    int TotalStok() const { return jumlah; }
    double HargaStok() const { return harga; }

    void kurangStok(int j);
    void returStok(int j);
    void updateStok(const std::string& n, double h, int j);

    std::string Info() const;

    void simpanDataKeFile(std::ofstream& file) const;
};

#endif
