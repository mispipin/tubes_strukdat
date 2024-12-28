#include <iostream>
#include <stack>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <set>
#include <locale>
#include <sstream>
using namespace std;

struct Item {
    string kodeInventaris;
    string nama;
    string kategori;
    string warna;
    int jumlah;
    double harga;

    string spesifikasi;

    string ram;    // Laptop
    string cpu;    // Laptop, Desktop
    string gpu;    // Laptop, Desktop
    string storage; // Desktop
    string resolusi; // Monitor
    string ukuran;  // Monitor
    string panel;   // Monitor
    string tipeSwitch; // Keyboard
    string konektivitas; // Mouse
    string sensor;  // Mouse
    int dpi;        // Mouse
};


// Fungsi untuk menghapus titik dari input harga dan validasi
bool validasiHarga(string input, double& hasil) {
    input.erase(remove(input.begin(), input.end(), '.'), input.end()); // Hapus titik
    try {
        for (char c : input) {
            if (!isdigit(c) && c != '.') return false;
        }
        hasil = stod(input); // Konversi ke double
        return true;
    } catch (...) {
        return false;
    }
}

// Fungsi untuk memformat angka dengan titik sebagai pemisah ribuan
string formatHarga(double angka) {
    stringstream ss;
    ss << fixed << setprecision(2) << angka;
    string hasil = ss.str();

    // Ganti titik ribuan dengan koma jika ingin
    int n = hasil.find('.');
    if (n != string::npos) {
        for (int i = n - 3; i > 0; i -= 3) {
            hasil.insert(i, ",");
        }
    }
    return hasil;
}

// Fungsi untuk login
bool login() {
    string username, password;
    const string USERNAME = "admin";
    const string PASSWORD = "1234";

    while (true) {
        cout << "\n========== Login Sistem ==========" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if (username == USERNAME && password == PASSWORD) {
            cout << "\nLogin berhasil! Selamat datang, " << username << "!\n";
            return true;
        } else {
            cout << "\nLogin gagal! Username atau password salah. Silakan coba lagi.\n";
        }
    }
}

// Fungsi untuk menampilkan semua item dengan informasi umum
void tampilkanItem(const stack<Item>& inventory) {
    if (inventory.empty()) {
        cout << "\nInventory kosong!\n";
        return;
    }

    cout << "\n================= Daftar Inventory =================\n";
    cout << left << setw(15) << "Kode"
         << left << setw(25) << "Nama"
         << left << setw(15) << "Kategori"
         << right << setw(10) << "Jumlah"
         << right << setw(20) << "Harga" << endl;
    cout << string(80, '-') << endl;

    stack<Item> temp = inventory;
    while (!temp.empty()) {
        Item item = temp.top();
        temp.pop();
        cout << left << setw(15) << item.kodeInventaris
             << left << setw(25) << item.nama
             << left << setw(15) << item.kategori
             << right << setw(10) << item.jumlah
             << right << setw(20) << formatHarga(item.harga) << endl;
    }
    cout << string(80, '-') << endl;
}

// Fungsi untuk menampilkan item berdasarkan kategori dengan informasi lebih spesifik
void tampilkanBerdasarkanKategori(const stack<Item>& inventory) {
    if (inventory.empty()) {
        cout << "\nInventory kosong!\n";
        return;
    }

    int pilihanKategori;
    cout << "\nPilih Kategori yang ingin ditampilkan: " << endl;
    cout << "1. Laptop" << endl;
    cout << "2. Desktop" << endl;
    cout << "3. Monitor" << endl;
    cout << "4. Keyboard" << endl;
    cout << "5. Mouse" << endl;
    cout << "Pilih (1-5): ";
    cin >> pilihanKategori;

    bool adaItem = false;
    stack<Item> temp = inventory;
    
    // Menampilkan header sesuai format
    cout << "\n================= Daftar Item Kategori Terpilih =================\n";
    cout << left << setw(15) << "Kode"
         << left << setw(25) << "Nama"
         << left << setw(15) << "Kategori"
         << left << setw(20) << "Warna"
         << right << setw(10) << "Jumlah"
         << right << setw(20) << "Harga"
         << right << setw(20) << "Spesifikasi" << endl; // Lebar kolom Spesifikasi lebih besar
    cout << string(140, '-') << endl;

    while (!temp.empty()) {
        Item item = temp.top();
        temp.pop();
        if ((pilihanKategori == 1 && item.kategori == "Laptop") ||
            (pilihanKategori == 2 && item.kategori == "Desktop") ||
            (pilihanKategori == 3 && item.kategori == "Monitor") ||
            (pilihanKategori == 4 && item.kategori == "Keyboard") ||
            (pilihanKategori == 5 && item.kategori == "Mouse")) {
            adaItem = true;

            // Menampilkan setiap item sesuai format
            cout << left << setw(15) << item.kodeInventaris
                 << left << setw(25) << item.nama
                 << left << setw(15) << item.kategori
                 << left << setw(20) << item.warna
                 << right << setw(10) << item.jumlah
                 << right << setw(20) << formatHarga(item.harga)
                 << right << setw(20);  

            // Menampilkan spesifikasi berdasarkan kategori
            if (item.kategori == "Laptop") {
                cout << "RAM: " << item.ram << ", CPU: " << item.cpu << ", GPU: " << item.gpu;
            } else if (item.kategori == "Desktop") {
                cout << "CPU: " << item.cpu << ", GPU: " << item.gpu << ", RAM: " << item.ram << ", Storage: " << item.storage;
            } else if (item.kategori == "Monitor") {
                cout << "Resolusi: " << item.resolusi << ", Ukuran: " << item.ukuran << ", Panel: " << item.panel;
            } else if (item.kategori == "Keyboard") {
                cout << "Tipe Switch: " << item.tipeSwitch;
            } else if (item.kategori == "Mouse") {
                cout << "Konektivitas: " << item.konektivitas << ", Sensor: " << item.sensor << ", DPI: " << item.dpi;
            }

            cout << endl;
        }
    }

    if (!adaItem) {
        cout << "Tidak ada item dalam kategori ini.\n";
    }
}



// Fungsi untuk menambahkan item
void tambahItem(stack<Item>& inventory, set<string>& kodeSet) {
    Item itemBaru;
    string inputHarga;

    // Validasi kode inventaris
    do {
        cout << "\nMasukkan Kode Inventaris: ";
        cin.ignore();
        getline(cin, itemBaru.kodeInventaris);
        if (kodeSet.count(itemBaru.kodeInventaris)) {
            cout << "Kode inventaris sudah ada. Silakan masukkan kode yang berbeda.\n";
        }
    } while (kodeSet.count(itemBaru.kodeInventaris));
    kodeSet.insert(itemBaru.kodeInventaris);

    cout << "Masukkan Nama Produk: ";
    getline(cin, itemBaru.nama);

    int pilihanKategori;
    cout << "\nPilih Kategori: " << endl;
    cout << "1. Laptop" << endl;
    cout << "2. Desktop" << endl;
    cout << "3. Monitor" << endl;
    cout << "4. Keyboard" << endl;
    cout << "5. Mouse" << endl;
    cout << "Pilih (1-5): ";
    cin >> pilihanKategori;
    cin.ignore();

    switch (pilihanKategori) {
        case 1: 
            itemBaru.kategori = "Laptop"; 
            cout << "Masukkan RAM (contoh: 16GB): ";
            getline(cin, itemBaru.ram);
            cout << "Masukkan CPU (contoh: Intel i7): ";
            getline(cin, itemBaru.cpu);
            cout << "Masukkan GPU (contoh: NVIDIA GTX 1050): ";
            getline(cin, itemBaru.gpu);
            break;
        case 2: 
            itemBaru.kategori = "Desktop"; 
            cout << "Masukkan CPU (contoh: Intel i5): ";
            getline(cin, itemBaru.cpu);
            cout << "Masukkan GPU (contoh: NVIDIA GTX 1660): ";
            getline(cin, itemBaru.gpu);
            cout << "Masukkan RAM (contoh: 16GB): ";
            getline(cin, itemBaru.ram);
            cout << "Masukkan Storage (contoh: 1TB SSD): ";
            getline(cin, itemBaru.storage);
            break;
        case 3: 
            itemBaru.kategori = "Monitor"; 
            cout << "Masukkan Resolusi (contoh: 1920x1080): ";
            getline(cin, itemBaru.resolusi);
            cout << "Masukkan Ukuran (contoh: 24 inch): ";
            getline(cin, itemBaru.ukuran);
            cout << "Masukkan Panel (contoh: IPS): ";
            getline(cin, itemBaru.panel);
            break;
        case 4: 
            itemBaru.kategori = "Keyboard"; 
            cout << "Masukkan Tipe Switch (contoh: Mekanikal): ";
            getline(cin, itemBaru.tipeSwitch);
            break;
        case 5: 
            itemBaru.kategori = "Mouse"; 
            cout << "Masukkan Konektivitas (contoh: Wireless, Bluetooth): ";
            getline(cin, itemBaru.konektivitas);
            cout << "Masukkan Sensor (contoh: Optical, Laser): ";
            getline(cin, itemBaru.sensor);
            cout << "Masukkan DPI (contoh: 1600): ";
            cin >> itemBaru.dpi;
            cin.ignore();
            break;
        default: 
            cout << "Kategori tidak valid!" << endl;
            return;
    }

    cout << "Masukkan Warna yang Tersedia (pisahkan dengan koma jika lebih dari satu): ";
    getline(cin, itemBaru.warna);

    cout << "Masukkan Jumlah: ";
    cin >> itemBaru.jumlah;

    // Validasi input harga
    do {
        cout << "Masukkan Harga (gunakan titik untuk pemisah ribuan): ";
        cin >> inputHarga;
        if (!validasiHarga(inputHarga, itemBaru.harga)) {
            cout << "Harga harus berupa angka. Silakan coba lagi.\n";
        }
    } while (!validasiHarga(inputHarga, itemBaru.harga));

    inventory.push(itemBaru);
    cout << "\nItem berhasil ditambahkan!\n";
}


// Fungsi untuk mencari item berdasarkan kode inventaris
void cariItem(stack<Item>& inventory) {
    string kode;
    bool ditemukan = false;

    cout << "Masukkan kode item yang ingin dicari: ";
    cin.ignore();
    getline(cin, kode);

    stack<Item> temp = inventory;
    while (!temp.empty()) {
        Item item = temp.top();
        temp.pop();
        if (item.kodeInventaris == kode) {
            cout << "\nItem ditemukan!" << endl;
            cout << left << setw(15) << "Kode"
                 << left << setw(25) << "Nama"
                 << left << setw(15) << "Kategori"
                 << left << setw(20) << "Warna"
                 << right << setw(10) << "Jumlah"
                 << right << setw(20) << "Harga" << endl;
            cout << string(110, '-') << endl;
            cout << left << setw(15) << item.kodeInventaris
                 << left << setw(25) << item.nama
                 << left << setw(15) << item.kategori
                 << left << setw(20) << item.warna
                 << right << setw(10) << item.jumlah
                 << right << setw(20) << formatHarga(item.harga) << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Item dengan kode " << kode << " tidak ditemukan.\n";
    }
}

// Fungsi untuk mengupdate item berdasarkan kode inventaris
void updateItem(stack<Item>& inventory, const string& kode) {
    bool ditemukan = false;
    stack<Item> temp;
    while (!inventory.empty()) {
        Item item = inventory.top();
        inventory.pop();
        if (item.kodeInventaris == kode) {
            ditemukan = true;
            cout << "\nItem yang akan diupdate ditemukan!" << endl;
            int jumlahBaru;
            cout << "Masukkan Jumlah baru (biarkan kosong jika tidak ingin mengubah): ";
            string inputJumlah;
            cin.ignore();
            getline(cin, inputJumlah);
            if (!inputJumlah.empty()) {
                item.jumlah = stoi(inputJumlah);
            }
            
            double hargaBaru;
            cout << "Masukkan Harga baru (biarkan kosong jika tidak ingin mengubah): ";
            string inputHarga;
            getline(cin, inputHarga);
            if (!inputHarga.empty() && validasiHarga(inputHarga, hargaBaru)) {
                item.harga = hargaBaru;
            }
            
            temp.push(item); // Simpan item yang sudah diupdate
            break;
        } else {
            temp.push(item); // Simpan item yang tidak diupdate
        }
    }

    if (!ditemukan) {
        cout << "Item dengan kode " << kode << " tidak ditemukan untuk diupdate.\n";
    }

    // Kembalikan sisa item ke inventory
    while (!temp.empty()) {
        inventory.push(temp.top());
        temp.pop();
    }
}

// Fungsi untuk menghitung total nilai inventory
void hitungTotalNilai(const stack<Item>& inventory) {
    double totalNilai = 0;

    stack<Item> temp = inventory;
    while (!temp.empty()) {
        Item item = temp.top();
        temp.pop();
        totalNilai += item.harga * item.jumlah;
    }

    cout << "\nTotal nilai inventory: " << formatHarga(totalNilai) << endl;
}

int main() {
    stack<Item> inventory;
    set<string> kodeSet;  // Untuk menyimpan kode inventaris yang sudah ada
    int pilihan;

    // Proses login
    login();

    do {
        cout << "\n========== Sistem Manajemen Inventory ==========" << endl;
        cout << "1. Tambah Item" << endl;
        cout << "2. Cari Item" << endl;
        cout << "3. Tampilkan Semua Item" << endl;
        cout << "4. Tampilkan Berdasarkan Kategori" << endl;
        cout << "5. Update Item" << endl;
        cout << "6. Hitung Total Nilai Inventory" << endl;
        cout << "7. Keluar" << endl;
        cout << "===============================================\n";
        cout << "Pilih menu (1-7): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahItem(inventory, kodeSet);
                break;
            case 2:
                cariItem(inventory);
                break;
            case 3:
                tampilkanItem(inventory);
                break;
            case 4:
                tampilkanBerdasarkanKategori(inventory);
                break;
            case 5: {
                string kode;
                cout << "Masukkan kode item yang ingin diupdate: ";
                cin.ignore();
                getline(cin, kode);
                updateItem(inventory, kode);
                break;
            }
            case 6:
                hitungTotalNilai(inventory);
                break;
            case 7:
                cout << "\nTerima kasih telah menggunakan sistem ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 7);

    return 0;
}
