#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Struct untuk menyimpan informasi peminjam
struct Peminjaman {
    string nama;
    string nik;
    double uangPinjam;
    double bunga;
    Peminjaman* next;
};

// Fungsi untuk menambahkan data peminjaman ke linked list
void tambahPeminjaman(Peminjaman*& head, string nama, string nik, double uangPinjam) {
    Peminjaman* baru = new Peminjaman;
    baru->nama = nama;
    baru->nik = nik;
    baru->uangPinjam = uangPinjam;
    baru->bunga = uangPinjam * 0.02; // Bunga 2%
    baru->next = head;
    head = baru;
}

// Fungsi untuk mencari data peminjaman berdasarkan NIK
Peminjaman* cariPeminjaman(Peminjaman* head, string nik) {
    Peminjaman* temp = head;
    while (temp != nullptr) {
        if (temp->nik == nik) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr; // Jika tidak ditemukan
}

// Fungsi untuk menghitung total yang harus dikembalikan (uang + bunga)
double hitungTotalKembali(double uangPinjam, double bunga) {
    return uangPinjam + bunga;
}

int main() {
    Peminjaman* dataPeminjaman = nullptr;

    int menu;
    do {
        cout << "Selamat datang di Peminjaman Uang WSA\n";
        cout << "Menu:\n";
        cout << "1. Pinjam Uang\n";
        cout << "2. Pengembalian Uang\n";
        cout << "3. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> menu;

        switch (menu) {
            case 1: {
                string nama, nik;
                double uangPinjam;
                cout << "Nama: ";
                cin.ignore();
                getline(cin, nama);
                cout << "NIK: ";
                cin >> nik;
                cout << "Uang yang ingin dipinjam: ";
                cin >> uangPinjam;
                tambahPeminjaman(dataPeminjaman, nama, nik, uangPinjam);
                cout << "Data peminjaman berhasil disimpan!\n";
                break;
            }
            case 2: {
                string nama, nik;
                cout << "Nama: ";
                cin.ignore();
                getline(cin, nama);
                cout << "NIK: ";
                cin >> nik;
                Peminjaman* peminjaman = cariPeminjaman(dataPeminjaman, nik);
                if (peminjaman != nullptr) {
                    cout << "Nama: " << peminjaman->nama << endl;
                    cout << "NIK: " << peminjaman->nik << endl;
                    cout << "Total yang harus dikembalikan (uang + bunga 2%): ";
                    cout << fixed << setprecision(2) << peminjaman->uangPinjam + peminjaman->bunga << endl;

                    double jumlahKembali;
                    cout << "Jumlah uang yang ingin dikembalikan: ";
                    cin >> jumlahKembali;

                    if (jumlahKembali == peminjaman->uangPinjam + peminjaman->bunga) {
                        cout << "Selamat, Anda sudah tidak memiliki pinjaman lagi!\n";
                        // Hapus data peminjaman dari linked list
                        Peminjaman* temp = dataPeminjaman;
                        Peminjaman* prev = nullptr;
                        while (temp != nullptr) {
                            if (temp == peminjaman) {
                                if (prev != nullptr) {
                                    prev->next = temp->next;
                                } else {
                                    dataPeminjaman = temp->next;
                                }
                                delete temp;
                                break;
                            }
                            prev = temp;
                            temp = temp->next;
                        }
                    } else if (jumlahKembali < peminjaman->uangPinjam + peminjaman->bunga) {
                        double sisaTagihan = peminjaman->uangPinjam + peminjaman->bunga - jumlahKembali;
                        cout << "Sisa tagihan Anda: " << fixed << setprecision(2) << sisaTagihan << endl;
                        peminjaman->uangPinjam += peminjaman->bunga - jumlahKembali; // Kurangi tagihan
                    } else {
                        cout << "Jumlah yang Anda kembalikan melebihi tagihan!\n";
                    }
                } else {
                    cout << "Data peminjaman tidak ditemukan.\n";
                }
                break;
            }
            case 3: {
                cout << "Terima kasih sudah menggunakan layanan kami.\n";
                break;
            }
            default:
                cout << "Pilihan tidak valid. Silakan pilih kembali.\n";
        }

    } while (menu != 3);

    return 0;
}
