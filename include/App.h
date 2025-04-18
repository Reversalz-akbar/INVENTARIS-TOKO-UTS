#ifndef APP_H
#define APP_H

#include "stok.h"
#include <vector>

class App {
private:
    std::vector<Stok>& daftarBarang;
public:
    App(std::vector<Stok>& stok);
    void tampilkanMenu();
    void prosesPilihan();
    void cariProduk();
};

#endif
