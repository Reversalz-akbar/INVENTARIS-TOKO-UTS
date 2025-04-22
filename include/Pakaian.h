#ifndef PAKAIAN_H
#define PAKAIAN_H

#include "Produk.h"

class Pakaian : public Produk {
public:
    Pakaian(const std::string& kode,
            const std::string& nama,
            double             harga,
            int                stok);

    void        tampilkanInfo() const override;
    std::string kategori()      const override { return "Pakaian"; }
    double      diskon()        const override { return harga * 0.15; }   // 15 %
};

#endif
