#include <iostream>
#include <stack>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;

struct Item {
    string kodeInventaris;
    string nama;
    int jumlah;
    double harga;
    string kategori;
    string spesifikasi;
    string satuan;
};

// Fungsi untuk menghapus karakter titik dari string
string hapusTitik(const string &input) {
    string hasil = input;
    hasil.erase(remove(hasil.begin(), hasil.end(), '.'), hasil.end());
    return hasil;
}

// Fungsi untuk menghitung total nilai inventory
double hitungTotalNilaiInventory(const stack<Item>& inventory) {
    double total = 0;
    stack<Item> temp = inventory;  // Salin stack untuk iterasi
    while (!temp.empty()) {
        const Item& item = temp.top();
        total += item.harga * item.jumlah;
        temp.pop();
    }
    return total;
}

// Fungsi untuk menampilkan item (tampil hanya kode, nama produk, kategori, harga, jumlah)
void tampilkanItem(const stack<Item>& inventory) {
    if (inventory.empty()) {
        cout << "Inventory kosong!" << endl;
    } else {
        cout << "\n------ Daftar Semua Item ------" << endl;
        cout << left << setw(15) << "Kode Inventaris"
             << left << setw(20) << "Nama Produk"
             << left << setw(20) << "Kategori"
             << right << setw(15) << "Harga"
             << right << setw(10) << "Jumlah" << endl;
        cout << string(80, '-') << endl;

        stack<Item> temp = inventory;  // Salin stack untuk iterasi
        while (!temp.empty()) {
            const Item& item = temp.top();
            cout << left << setw(15) << item.kodeInventaris
                 << left << setw(20) << item.nama
                 << left << setw(20) << item.kategori
                 << right << setw(15) << "Rp. " << fixed << setprecision(2) << item.harga
                 << right << setw(10) << item.jumlah << endl;
            temp.pop();
        }
        cout << string(80, '-') << endl;
    }
}

bool validasiKodeInventaris(const stack<Item>& inventory, const string &kode) {
    stack<Item> temp = inventory;  // Salin stack untuk pencarian
    while (!temp.empty()) {
        if (temp.top().kodeInventaris == kode) {
            return true;
        }
        temp.pop();
    }
    return false;
}

int main() {
    stack<Item> inventory;
    int pilihan;

    do {
        cout << "\n=================================" << endl;
        cout << "          ITProcure"                << endl;
        cout << "=================================" << endl;
        cout << "1. Tambah Item" << endl;
        cout << "2. Hapus Item" << endl;
        cout << "3. Tampilkan Item" << endl;
        cout << "4. Update Item" << endl;
        cout << "5. Cari Item" << endl;
        cout << "6. Hitung Total Nilai Inventory" << endl;
        cout << "8. Keluar" << endl;
        cout << "=================================" << endl;
        cout << "Pilih Menu (1-8): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int kategori;
                cout << "\nPilih Kategori Barang:" << endl;
                cout << "1. Laptop" << endl;
                cout << "2. Handphone" << endl;
                cout << "3. Desktop" << endl;
                cout << "4. Keyboard" << endl;
                cout << "5. Mouse" << endl;
                cout << "Pilih kategori (1-5): ";
                cin >> kategori;

                Item itemBaru;

                // Set kode dan spesifikasi berdasarkan kategori yang dipilih
                switch (kategori) {
                    case 1: {  // Laptop
                        cout << "Masukkan Kode Inventaris: ";
                        cin.ignore(); // Membersihkan input buffer
                        getline(cin, itemBaru.kodeInventaris);
                        cout << "Masukkan Nama Produk: ";
                        getline(cin, itemBaru.nama);
                        cout << "Masukkan Harga: ";
                        cin >> itemBaru.harga;
                        cout << "Masukkan Jumlah: ";
                        cin >> itemBaru.jumlah;
                        cin.ignore(); // Membersihkan input buffer
                        cout << "Masukkan Spesifikasi RAM: ";
                        getline(cin, itemBaru.spesifikasi); // RAM
                        cout << "Masukkan Spesifikasi CPU: ";
                        getline(cin, itemBaru.spesifikasi); // CPU
                        cout << "Masukkan Spesifikasi GPU: ";
                        getline(cin, itemBaru.spesifikasi); // GPU
                        itemBaru.kategori = "Laptop";
                        break;
                    }
                    case 2: {  // Handphone
                        cout << "Masukkan Kode Inventaris: ";
                        cin.ignore(); // Membersihkan input buffer
                        getline(cin, itemBaru.kodeInventaris);
                        cout << "Masukkan Merk Produk: ";
                        getline(cin, itemBaru.nama);
                        cout << "Masukkan Harga: ";
                        cin >> itemBaru.harga;
                        cout << "Masukkan Jumlah: ";
                        cin >> itemBaru.jumlah;
                        cin.ignore(); // Membersihkan input buffer
                        cout << "Masukkan Spesifikasi RAM: ";
                        getline(cin, itemBaru.spesifikasi); // RAM
                        cout << "Masukkan Spesifikasi Konektivitas: ";
                        getline(cin, itemBaru.spesifikasi); // Konektivitas
                        cout << "Masukkan Sistem Operasi: ";
                        getline(cin, itemBaru.spesifikasi); // Sistem Operasi
                        itemBaru.kategori = "Handphone";
                        break;
                    }
                    case 3: {  // Desktop
                        cout << "Masukkan Kode Inventaris: ";
                        cin.ignore(); // Membersihkan input buffer
                        getline(cin, itemBaru.kodeInventaris);
                        cout << "Masukkan Nama Produk: ";
                        getline(cin, itemBaru.nama);
                        cout << "Masukkan Harga: ";
                        cin >> itemBaru.harga;
                        cout << "Masukkan Jumlah: ";
                        cin >> itemBaru.jumlah;
                        cin.ignore(); // Membersihkan input buffer
                        cout << "Masukkan Spesifikasi RAM: ";
                        getline(cin, itemBaru.spesifikasi); // RAM
                        cout << "Masukkan Spesifikasi CPU: ";
                        getline(cin, itemBaru.spesifikasi); // CPU
                        cout << "Masukkan Spesifikasi GPU: ";
                        getline(cin, itemBaru.spesifikasi); // GPU
                        itemBaru.kategori = "Desktop";
                        break;
                    }
                    case 4: {  // Keyboard
                        cout << "Masukkan Kode Inventaris: ";
                        cin.ignore(); // Membersihkan input buffer
                        getline(cin, itemBaru.kodeInventaris);
                        cout << "Masukkan Nama Produk: ";
                        getline(cin, itemBaru.nama);
                        cout << "Masukkan Harga: ";
                        cin >> itemBaru.harga;
                        cout << "Masukkan Jumlah: ";
                        cin >> itemBaru.jumlah;
                        cin.ignore(); // Membersihkan input buffer
                        cout << "Masukkan Spesifikasi Konektivitas: ";
                        getline(cin, itemBaru.spesifikasi); // Konektivitas
                        cout << "Masukkan Ukuran: ";
                        getline(cin, itemBaru.spesifikasi); // Ukuran
                        itemBaru.kategori = "Keyboard";
                        break;
                    }
                    case 5: {  // Mouse
                        cout << "Masukkan Kode Inventaris: ";
                        cin.ignore(); // Membersihkan input buffer
                        getline(cin, itemBaru.kodeInventaris);
                        cout << "Masukkan Nama Produk: ";
                        getline(cin, itemBaru.nama);
                        cout << "Masukkan Harga: ";
                        cin >> itemBaru.harga;
                        cout << "Masukkan Jumlah: ";
                        cin >> itemBaru.jumlah;
                        cin.ignore(); // Membersihkan input buffer
                        cout << "Masukkan Spesifikasi Konektivitas: ";
                        getline(cin, itemBaru.spesifikasi); // Konektivitas
                        itemBaru.kategori = "Mouse";
                        break;
                    }
                    default:
                        cout << "Pilihan kategori tidak valid!" << endl;
                        continue;
                }

                inventory.push(itemBaru);
                cout << "Item berhasil ditambahkan!" << endl;
                break;
            }
            case 2: {  // Hapus Item berdasarkan kode inventaris
                string kode;
                cout << "Masukkan Kode Inventaris Item yang ingin dihapus: ";
                cin.ignore(); // Membersihkan input buffer
                getline(cin, kode);

                if (!validasiKodeInventaris(inventory, kode)) {
                    cout << "Error: Item dengan kode inventaris " << kode << " tidak ditemukan." << endl;
                } else {
                    stack<Item> temp;
                    bool found = false;
                    while (!inventory.empty()) {
                        Item item = inventory.top();
                        inventory.pop();
                        if (item.kodeInventaris == kode && !found) {
                            found = true;
                            cout << "Item dengan kode inventaris " << kode << " berhasil dihapus." << endl;
                        } else {
                            temp.push(item);  // Salin item ke stack sementara
                        }
                    }
                    // Kembalikan item-item yang tidak dihapus ke stack utama
                    while (!temp.empty()) {
                        inventory.push(temp.top());
                        temp.pop();
                    }
                }
                break;
            }
            case 3: {  // Tampilkan Semua Item
                tampilkanItem(inventory);
                break;
            }
            case 4: {  // Update Item berdasarkan kode inventaris
                string kode;
                cout << "Masukkan Kode Inventaris Item yang ingin diupdate: ";
                cin.ignore(); // Membersihkan input buffer
                getline(cin, kode);

                if (!validasiKodeInventaris(inventory, kode)) {
                    cout << "Error: Item dengan kode inventaris " << kode << " tidak ditemukan." << endl;
                } else {
                    stack<Item> temp;
                    bool found = false;
                    while (!inventory.empty()) {
                        Item item = inventory.top();
                        inventory.pop();
                        if (item.kodeInventaris == kode && !found) {
                            found = true;
                            cout << "Item ditemukan! Update data berikut:" << endl;
                            cout << "Masukkan Nama Produk: ";
                            getline(cin, item.nama);
                            cout << "Masukkan Harga: ";
                            cin >> item.harga;
                            cout << "Masukkan Jumlah: ";
                            cin >> item.jumlah;
                            cin.ignore(); // Membersihkan input buffer
                            cout << "Masukkan Spesifikasi: ";
                            getline(cin, item.spesifikasi);
                            cout << "Data berhasil diperbarui!" << endl;
                        }
                        temp.push(item);  // Salin item ke stack sementara
                    }
                    // Kembalikan item-item yang sudah diperbarui ke stack utama
                    while (!temp.empty()) {
                        inventory.push(temp.top());
                        temp.pop();
                    }
                }
                break;
            }
            case 5: {  // Cari Item berdasarkan kode inventaris
                string kode;
                cout << "Masukkan Kode Inventaris Item yang ingin dicari: ";
                cin.ignore(); // Membersihkan input buffer
                getline(cin, kode);

                if (!validasiKodeInventaris(inventory, kode)) {
                    cout << "Error: Item dengan kode inventaris " << kode << " tidak ditemukan." << endl;
                } else {
                    stack<Item> temp = inventory;  // Salin stack untuk pencarian
                    while (!temp.empty()) {
                        const Item& item = temp.top();
                        if (item.kodeInventaris == kode) {
                            cout << "\nItem ditemukan!" << endl;
                            cout << left << setw(15) << "Kode Inventaris"
                                 << left << setw(20) << "Nama Produk"
                                 << left << setw(20) << "Kategori"
                                 << right << setw(15) << "Harga"
                                 << right << setw(10) << "Jumlah" << endl;
                            cout << string(80, '-') << endl;
                            cout << left << setw(15) << item.kodeInventaris
                                 << left << setw(20) << item.nama
                                 << left << setw(20) << item.kategori
                                 << right << setw(15) << "Rp. " << fixed << setprecision(2) << item.harga
                                 << right << setw(10) << item.jumlah << endl;
                            cout << string(80, '-') << endl;
                            break;
                        }
                        temp.pop();
                    }
                }
                break;
            }
            case 6: {  // Hitung Total Nilai Inventory
                double totalNilai = hitungTotalNilaiInventory(inventory);
                cout << "Total Nilai Inventory: Rp. " << fixed << setprecision(2) << totalNilai << endl;
                break;
            }
            case 8:
                cout << "Keluar dari program. Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih antara 1 hingga 8." << endl;
        }
    } while (pilihan != 8);

    return 0;
}
