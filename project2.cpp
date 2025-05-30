#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Lagu
{
    string judul;
    string penyanyi;
    int jumlahPendengar;
    string genre;
    float rating;
    string playlist; // nama playlist tempat lagu ini
    Lagu *next;
};

struct Playlist
{
    string nama;
    Playlist *next;
};

Lagu *head = nullptr;
Playlist *headPlaylist = nullptr;

// fungsi menambah lagu biasa (dipakai di load dari file) menyimpan data lagu ke dalam struktur data (linked list)
void tambahLagu(string judul, string penyanyi, int jumlahPendengar, string genre, float rating, string playlist, bool simpanKeFile = true)
{
    Lagu *baru = new Lagu{judul, penyanyi, jumlahPendengar, genre, rating, playlist, nullptr};

    if (!head)
        head = baru;
    else
    {
        Lagu *temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = baru;
    }

    // Simpan ke file hanya jika diminta
    if (simpanKeFile)
    {
        FILE *file = fopen("lagu.txt", "a"); // mode append
        if (file)
        {
            fprintf(file, "%s,%s,%d,%s,%.1f,%s\n",
                    judul.c_str(),
                    penyanyi.c_str(),
                    jumlahPendengar,
                    genre.c_str(),
                    rating,
                    playlist.c_str());
            fclose(file);
        }
        else
        {
            cout << "Gagal menyimpan ke file.\n";
        }
    }
}

// fungsi menambah playlist baru
void tambahPlaylist(string nama)
{
    Playlist *temp = headPlaylist;
    while (temp)
    {
        if (temp->nama == nama)
        {
            cout << "Playlist \"" << nama << "\" sudah ada.\n";
            return;
        }
        temp = temp->next;
    }
    Playlist *baru = new Playlist{nama, nullptr};
    if (!headPlaylist)
    {
        headPlaylist = baru;
    }
    else
    {
        Playlist *last = headPlaylist;
        while (last->next)
            last = last->next;
        last->next = baru;
    }
    cout << "Playlist \"" << nama << "\" berhasil dibuat!\n";
}

// fungsi menampilkan daftar playlist
void tampilkanPlaylist()
{
    if (!headPlaylist) // mengecek apakah pointer headplaylist kosong
    {
        cout << "Belum ada playlist yang terbuat!!!\n"; // jika kosong, tampilkan pesan
        return;
    }
    cout << "\nDaftar Playlist!\n"; // jika ada playlist tampilkan daftar playlist

    Playlist *temp = headPlaylist; // pointer sementara untuk iterasi
    int no = 1;                    // untuk nomor urut playlist

    // looping selama masih ada playlist
    while (temp)
    {
        cout << no++ << ". " << temp->nama << "\n"; // tampilkan no dan nama playlist
        temp = temp->next;                          // memindahkan ke playlist selanjutnya
    }
}

// fungsu untuk mengecek apakah ada playlist yang sudah dibuat atau belum
bool adaPlaylist()
{
    // mengembalikan nilai true jika headPlaylist tidak null (artinya ada playlist)
    // jika null (tidak ada playlist) ->
    return headPlaylist != nullptr;
}

// fungsi untuk menambahkan lagu input untuk pengguna
void tambahLaguInteraktif()
{
    // deklarasi variabel untuk menyimpan informasi lagu
    string judul, penyanyi, genre, playlist = "";
    int jumlahPendengar;
    float rating;

    cout << "\nMasukkan Judul Lagu\t\t\t: ";
    getline(cin, judul);
    cout << "Penyanyi\t\t\t\t: ";
    getline(cin, penyanyi);
    cout << "Masukkan Jumlah Pendengar\t\t: ";
    cin >> jumlahPendengar;
    cin.ignore();
    cout << "Masukkan Genre (Pop/Rock/Jazz/Hip-Hop)\t: ";
    getline(cin, genre);
    cout << "Masukkan Rating (1 - 10)\t\t: ";
    cin >> rating;
    cin.ignore();

    // validasi nilai rating
    if (rating < 1 || rating > 10)
    {
        cout << "Rating tidak valid. Harus antara 1 hingga 10.\n";
        return;
    }

    cout << "\nLagu \"" << judul << "\" berhasil ditambahkan!\n";

    // tanya apakah lagu akan dimasukkan ke dalam playlist
    char pilihanPlaylist;
    cout << "\nApakah ingin memasukkan lagu ke playlist? (y/n) : ";
    cin >> pilihanPlaylist;
    cin.ignore();

    if (pilihanPlaylist == 'y' || pilihanPlaylist == 'Y')
    {
        if (!adaPlaylist())
        {
            // jika belum ada playlist, minta buat baru
            cout << "\nBelum ada playlist yang terbuat. Silakan buat playlist dulu!\n";
            string namaPlaylist;
            cout << "\nMasukkan nama playlist baru : ";
            getline(cin, namaPlaylist);
            tambahPlaylist(namaPlaylist);
            playlist = namaPlaylist;
        }
        else
        {
            // tampilkan pilihan playlist
            cout << "\nPilih opsi!\n";
            cout << "1. Buat playlist baru\n";
            cout << "2. Masukkan playlist yang sudah ada\n";
            cout << "Pilih : ";
            int opsi;
            cin >> opsi;
            cin.ignore();

            if (opsi == 1)
            {
                string namaPlaylist;
                cout << "\nMasukkan nama playlist baru : ";
                getline(cin, namaPlaylist);
                tambahPlaylist(namaPlaylist);
                playlist = namaPlaylist;
            }
            else if (opsi == 2)
            {
                // tampilkan playlist dengan nomor
                const int MAKS_PLAYLIST = 100;
                string daftarPlaylist[MAKS_PLAYLIST];
                Playlist *temp = headPlaylist;
                int jumlahPlaylist = 0;

                cout << "\nDaftar Playlist:\n";
                while (temp != NULL && jumlahPlaylist < MAKS_PLAYLIST)
                {
                    cout << (jumlahPlaylist + 1) << ". " << temp->nama << "\n";
                    daftarPlaylist[jumlahPlaylist] = temp->nama;
                    jumlahPlaylist++;
                    temp = temp->next;
                }

                int pilihan;
                cout << "Masukkan nomor playlist dari daftar di atas : ";
                cin >> pilihan;
                cin.ignore();

                if (pilihan >= 1 && pilihan <= jumlahPlaylist)
                {
                    playlist = daftarPlaylist[pilihan - 1];
                }
                else
                {
                    cout << "Pilihan tidak valid, lagu tidak dimasukkan ke playlist.\n";
                    playlist = "";
                }
            }
            else
            {
                cout << "Pilihan tidak valid, lagu tidak dimasukkan ke playlist.\n";
            }
        }
    }

    // tambahkan lagu ke linked list
    tambahLagu(judul, penyanyi, jumlahPendengar, genre, rating, playlist);

    // tampilkan pesan sukses
    cout << "\nLagu \"" << judul << "\" berhasil ditambahkan!\n";
    system("cls");
}

// fungsi menampilkan semua lagu dalam linked list
void tampilkanLagu()
{
    // cek apakah linked list kosong (tidak ada lagu)
    if (!head)
    {
        cout << "Belum ada lagu.\n";
        return; // keluar dari fungsi jika tidak ada lagu
    }
    // petunjuk sementara untuk menelusuri linked list dari awal (head)
    Lagu *temp = head;

    // variabel untuk menghitung urutan lagu
    int i = 1;
    // perulangan untuk menampilkan data setiap node lagu dalam linked list
    while (temp)
    {
        // menampilkan informasi lagu
        cout << "\nJudul\t\t\t: " << temp->judul << endl;
        cout << "Penyanyi\t\t: " << temp->penyanyi << endl;
        cout << "Jumlah Pendengar\t: " << temp->jumlahPendengar << " kali didengar" << endl;
        cout << "Genre\t\t\t: " << temp->genre << endl;
        cout << "Rating\t\t\t: " << fixed << setprecision(1) << temp->rating << endl;
        // Menampilkan nama playlist jika ada, jika tidak maka tampilkan tanda "-"
        cout << "Playlist\t\t: " << (temp->playlist.empty() ? "-" : temp->playlist) << endl;

        // pindah ke node lagu berikutnya
        temp = temp->next;
    }
}

// fungsi mencari lagu berdasarkan keyword yang dicocokkan dengan judul lagu
void cariLagu(string keyword)
{
    // pointer untuk menelusuri seluruh node lagu dalam linked list
    Lagu *temp = head;
    // variabel penanda apakah lagu ditemukan
    bool ketemu = false;
    // perulangan untuk menelusuri seluruh linked list
    while (temp)
    {
        if (temp->judul.find(keyword) != string::npos)
        {
            cout << "\nJudul\t\t\t: " << temp->judul << endl;
            cout << "Penyanyi\t\t: " << temp->penyanyi << endl;
            cout << "Jumlah Pendengar\t: " << temp->jumlahPendengar << endl;
            cout << "Genre\t\t\t: " << temp->genre << endl;
            cout << "Rating\t\t\t: " << fixed << setprecision(1) << temp->rating << endl;
            cout << "Playlist\t\t: " << (temp->playlist.empty() ? "-" : temp->playlist) << endl;
            ketemu = true;
        }
        temp = temp->next;
    }
    if (!ketemu)
        cout << "\nLAGU TIDAK DITEMUKAN!!!\n";

    system("pause");
    system("cls");
}

// fungsi untuk mengurutkan lagu berdasarkan jumlah pendengar secara menurun (descending)
void urutkanLagu()
{
    // jika tidak ada lagu, langsung keluar dari fungsi
    if (!head)
        return;

    bool swapped;
    // bubble sort untuk mengurutkan linked list
    do
    {
        swapped = false;   // apakah ada pertukaran data
        Lagu *curr = head; // mulai dari node pertama
        while (curr->next)
        {
            // jika node saat ini memiliki jumlah pendengar lebih kecil dari node berikutnya
            if (curr->jumlahPendengar < curr->next->jumlahPendengar)
            {
                swap(curr->judul, curr->next->judul);
                swap(curr->penyanyi, curr->next->penyanyi);
                swap(curr->jumlahPendengar, curr->next->jumlahPendengar);
                swap(curr->genre, curr->next->genre);
                swap(curr->rating, curr->next->rating);
                swap(curr->playlist, curr->next->playlist);
                swapped = true; // tandai bahwa telah terjadi pertukaran
            }
            // pindah ke node berikutnya
            curr = curr->next;
        }
    } while (swapped); // ulangi selama ada pertukaran
    cout << "Lagu berhasil diurutkan berdasarkan jumlah pendengar.\n";
    tampilkanLagu();
}

// Filter berdasarkan penyanyi atau genre
void filterLagu(string kriteria, string value)
{
    Lagu *temp = head;
    bool ketemu = false;
    while (temp)
    {
        if ((kriteria == "penyanyi" && temp->penyanyi == value) ||
            (kriteria == "genre" && temp->genre == value))
        {
            cout << "\nJudul\t\t\t: " << temp->judul << endl;
            cout << "Penyanyi\t\t: " << temp->penyanyi << endl;
            cout << "Jumlah Pendengar\t: " << temp->jumlahPendengar << endl;
            cout << "Genre\t\t\t: " << temp->genre << endl;
            cout << "Rating\t\t\t: " << fixed << setprecision(1) << temp->rating << endl;
            cout << "Playlist\t\t: " << (temp->playlist.empty() ? "-" : temp->playlist) << endl;
            ketemu = true;
        }
        temp = temp->next;
    }
    if (!ketemu)
        cout << "\nTidak ada lagu dengan " << kriteria << " tersebut.\n";
}

// Hapus lagu berdasarkan judul
void hapusLagu(string judul)
{
    Lagu *temp = head;
    Lagu *prev = nullptr;

    while (temp)
    {
        if (temp->judul == judul)
        {
            if (prev)
                prev->next = temp->next;
            else
                head = temp->next;

            delete temp;
            cout << "\nLagu \"" << judul << "\" berhasil dihapus.\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "LAGU TIDAK DITEMUKAN!!!\n";
}

void hapusSemua()
{
    while (head)
    {
        Lagu *temp = head;
        head = head->next;
        delete temp;
    }

    while (headPlaylist)
    {
        Playlist *temp = headPlaylist;
        headPlaylist = headPlaylist->next;
        delete temp;
    }
}

// Fungsi untuk membaca data lagu dari file teks tanpa fungsi lanjutan
void loadDariFile(const string &filename)
{
    char namaFile[100];
    int i;
    for (i = 0; i < filename.length() && i < 99; i++)
        namaFile[i] = filename[i];
    namaFile[i] = '\0';

    FILE *file = fopen("lagu.txt", "r");
    if (!file)
    {
        cout << "Gagal membuka file" << endl;
        return;
    }

    hapusSemua(); // Hapus semua data lama

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        // Hapus newline
        int j = 0;
        while (line[j] != '\0')
        {
            if (line[j] == '\n' || line[j] == '\r')
            {
                line[j] = '\0';
                break;
            }
            j++;
        }

        // Pisahkan berdasarkan koma (maks. 6 field)
        string data[6];
        int index = 0, start = 0;
        for (int k = 0; line[k] != '\0'; k++)
        {
            if (line[k] == ',' && index < 5)
            {
                data[index] = "";
                for (int m = start; m < k; m++)
                    data[index] += line[m];
                index++;
                start = k + 1;
            }
        }
        // Field terakhir
        data[5] = "";
        for (int m = start; line[m] != '\0'; m++)
            data[5] += line[m];

        // Konversi jumlah pendengar (int)
        int jumlahPendengar = 0;
        for (int x = 0; x < data[2].size(); x++)
            jumlahPendengar = jumlahPendengar * 10 + (data[2][x] - '0');

        // Konversi rating (float)
        float rating = 0;
        bool titik = false;
        float pembagi = 10;
        for (int x = 0; x < data[4].size(); x++)
        {
            if (data[4][x] == '.')
            {
                titik = true;
            }
            else if (!titik)
            {
                rating = rating * 10 + (data[4][x] - '0');
            }
            else
            {
                rating += float(data[4][x] - '0') / pembagi;
                pembagi *= 10;
            }
        }

        // Tambahkan lagu ke linked list
        tambahLagu(data[0], data[5], jumlahPendengar, data[3], rating, data[5], 0);
    }

    fclose(file);
    cout << "Data berhasil dimuat dari " << filename << endl;
}

int main()
{
    int pilih;
    do
    {
        cout << "\n===== Menu The Music Library Project =====\n";
        cout << "1. Tambah Lagu\n";
        cout << "2. Tampilkan Lagu\n";
        cout << "3. Cari Lagu Berdasarkan Judul\n";
        cout << "4. Urutkan Lagu berdasarkan Jumlah Pendengar (Descending)\n";
        cout << "5. Filter Lagu (Penyanyi/Genre)\n";
        cout << "6. Hapus Lagu\n";
        cout << "7. Tampilkan Playlist\n";
        cout << "8. Load dari File\n";
        cout << "0. Keluar\n";
        cout << "Pilih : ";
        cin >> pilih;
        cin.ignore();
        system("cls");

        switch (pilih)
        {
        case 1:
            tambahLaguInteraktif();
            break;
        case 2:
            tampilkanLagu();
            system("pause");
            system("cls");
            break;
        case 3:
        {
            string keyword;
            cout << "Masukkan Judul Lagu : ";
            getline(cin, keyword);
            cariLagu(keyword);
            break;
        }
        case 4:
            urutkanLagu();
            system("pause");
            system("cls");
            break;
        case 5:
        {
            int pilihKriteria;
            cout << "Filter berdasarkan:\n";
            cout << "1. Penyanyi\n";
            cout << "2. Genre\n";
            cout << "Pilih : ";
            cin >> pilihKriteria;
            cin.ignore();

            system("cls");

            string kriteria, value;
            const int MAKS_UNIK = 100;
            string daftarUnik[MAKS_UNIK];
            int jumlahUnik = 0;
            Lagu *temp = head;

            // Ambil daftar unik berdasarkan kriteria
            if (pilihKriteria == 1)
            {
                kriteria = "penyanyi";
                while (temp)
                {
                    bool sudahAda = false;
                    for (int i = 0; i < jumlahUnik; i++)
                    {
                        if (daftarUnik[i] == temp->penyanyi)
                        {
                            sudahAda = true;
                            break;
                        }
                    }
                    if (!sudahAda && jumlahUnik < MAKS_UNIK)
                    {
                        daftarUnik[jumlahUnik] = temp->penyanyi;
                        jumlahUnik++;
                    }
                    temp = temp->next;
                }
            }
            else if (pilihKriteria == 2)
            {
                kriteria = "genre";
                while (temp)
                {
                    bool sudahAda = false;
                    for (int i = 0; i < jumlahUnik; i++)
                    {
                        if (daftarUnik[i] == temp->genre)
                        {
                            sudahAda = true;
                            break;
                        }
                    }
                    if (!sudahAda && jumlahUnik < MAKS_UNIK)
                    {
                        daftarUnik[jumlahUnik] = temp->genre;
                        jumlahUnik++;
                    }
                    temp = temp->next;
                }
            }
            else
            {
                cout << "Pilihan tidak valid.\n";
                break;
            }

            // Tampilkan daftar yang ditemukan
            cout << "\nDaftar " << kriteria << ":\n";
            for (int i = 0; i < jumlahUnik; i++)
            {
                cout << i + 1 << ". " << daftarUnik[i] << endl;
            }

            // Minta pengguna pilih angka
            int pilihan;
            cout << "Pilih nomor " << kriteria << " : ";
            cin >> pilihan;
            cin.ignore();

            // Validasi
            if (pilihan < 1 || pilihan > jumlahUnik)
            {
                cout << "Pilihan tidak valid.\n";
                break;
            }

            value = daftarUnik[pilihan - 1];

            system("cls");

            // Panggil fungsi filter
            filterLagu(kriteria, value);
            break;
        }

        case 6:
        {
            string judul;
            cout << "Masukkan judul lagu yang ingin dihapus : ";
            getline(cin, judul);
            hapusLagu(judul);
            break;
        }
        case 7:
            tampilkanPlaylist();
            system("pause");
            system("cls");
            break;
        case 8:
        {
            string filename;
            cout << "Masukkan Nama File : ";
            getline(cin, filename);
            loadDariFile(filename);
            break;
        }
        case 0:
            hapusSemua();
            cout << "Terima Kasih Program Akan Di tutup!\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilih != 0);

    return 0;
}