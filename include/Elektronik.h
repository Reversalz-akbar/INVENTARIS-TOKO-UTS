#ifndef ELEKTRONIK_H
#define ELEKTRONIK_H

#include "Produk.h"

class Elektronik : public Produk {
public:
    Elektronik(const std::string& kode,
               const std::string& nama,
               double             harga,
               int                stok);

    void        tampilkanInfo() const override;
    std::string kategori()      const override { return "Elektronik"; }
    double      diskon()        const override { return harga * 0.10; }   // 10 %
};

#endif
