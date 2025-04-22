#ifndef PRODUK_H
#define PRODUK_H

#include <string>

class Produk {
protected:
    std::string kodeProduk;
    std::string nama;
    double      harga;
    int         stok;

public:
    Produk(const std::string& kode,
           const std::string& nama,
           double            harga,
           int               stok);
    virtual ~Produk() = default;

    // ——— virtual / polymorphic ———
    virtual void        tampilkanInfo()  const = 0;   // tampil info lengkap
    virtual std::string kategori()       const = 0;   // “Elektronik” dll
    virtual double      diskon()         const = 0;   // nominal diskon

    // ——— utilitas umum ———
    double getHargaSetelahDiskon() const { return harga - diskon(); }

    // ——— getter & setter ringan ———
    const std::string& getKodeProduk() const { return kodeProduk; }
    const std::string& getNama()       const { return nama; }
    double             getHarga()      const { return harga; }
    int                getStok()       const { return stok; }
    void               setStok(int s)        { stok = s; }
};

#endif
