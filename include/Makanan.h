#ifndef MAKANAN_H
#define MAKANAN_H

#include "Produk.h"

class Makanan : public Produk {
public:
    Makanan(const std::string& kode,
            const std::string& nama,
            double             harga,
            int                stok);

    void        tampilkanInfo() const override;
    std::string kategori()      const override { return "Makanan"; }
    double      diskon()        const override { return harga * 0.05; }   // 5 %
};

#endif
