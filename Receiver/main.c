// Ida Bagus Krishna Yoga Utama (1506716983)
// Nurian Satya Wardana (1506717071)

// Melampirkan libary-library yang dibutuhkan.
#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include "../header.h"

// Program utama Receiver, yaitu untuk
// melihat pesan bagi pengguna
int main() {
    // Untuk menghitung sudah berapa pesan
    // yang diterima oleh program dari server.
    int msgCounter = 1;

    // Menampilkan tulisan pada bagian atas program
    printHeader();
    printf("\n");

    // Meminta pengguna untuk menuliskan key agar
    // dapat membaca pesan yang pada server
    // dalam keadaan terenkripsi.
    int key = getKey();
    populateTable(key);
    printHeader();

    // Bagian ini akan diulangi selama program berjalan
    while (1) {
        // Deklarasi variabel-variabel yang dibutuhkan untuk library WinSock
        WSADATA wsa;
        SOCKET s;
        struct sockaddr_in server;

        // Pointer yang merujuk kepada request yang
        // nantinya akan dikirimkan program ini kepada
        // server agar server dapat membalasnya dengan
        // pesan yang ditulis oleh pengguna.
        char *request = malloc(500);

        // Balasan dari server atas request yang
        // dikirimkan oleh program lain. Balasan dari
        // server adalah pesan pengguna.
        char server_reply[2000];

        // Variabel ini akan di-assign oleh library WinSock,
        // yang memberitahukan berapa ukuran dari respon yang
        // diterima oleh program ini dari server.
        int recv_size;

        // Inisialisasi Winsock //////////////////////////////////////////////////////////////////
        if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
            printf(" Winsock failed. Error code: %d",WSAGetLastError());
            return 1;
        } //else printf("Winsock initialised.\n");

        // Membuat socket ///////////////////////////////////////////////////////////////////////
        if((s = socket(AF_INET, SOCK_STREAM, 0 )) == INVALID_SOCKET) {
            printf(" Could not create socket. Error code: %d" , WSAGetLastError());
            return 1;
        } //else printf("Socket created.\n");
        
        // Definisi identitas server ///////////////////////////////////////////////////////////
        // Program ini akan tersambung dengan komputer dengan alamat
        // 103.43.44.105 melalui internet
        server.sin_addr.s_addr = inet_addr("103.43.44.105");
        server.sin_family = AF_INET;

        // Berarti program ini akan tersambung dengan port 8080 pada server.
        // Dapat diperhatikan bahwa port ini berbeda dengan port yang
        // digunakan untuk mengirim pesan (port 8888) karena program yang
        // berjalan pada server terdiri dari dua program dan satu port
        // yang sama tidak dapat di-listen oleh dua entitas program yang
        // berbeda.
        server.sin_port = htons(8080);
     
        // Menghubungi server //////////////////////////////////////////////////////////////////
        if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
            printf(" Tidak dapat terhubung dengan server.");
            return 1;
        } //else printf("Koneksi ke server berhasil.\n");

        // Membuat variabel string 'request' sama dengan jumlah
        // pesan yang sudah diterima oleh program ini.
        sprintf(request, "%d", msgCounter);

        // Program ini akan mengirimkan angka tersebut ke server.
        // Angka tersebut adalah ID pesan. Jika misal program mengirim
        // "1" ke server, maka server akan membalasnya dengan teks
        // pesan yang memiliki ID = 1.
        send(s, request, strlen(request), 0);

        // Meminta respon dari server dan memasukkan respon tersebut
        // ke string 'server_reply' dan membuat nilai variabel 'recv_size'
        // sebagai ukuran dari respon tersebut.
        recv_size = recv(s, server_reply, 2000 , 0);

        // Menambahkan karakter string terminate untuk memudahkan
        // saat mencetak (print) respon dari server.s
        server_reply[recv_size] = '\0';
        
        int a;
        int n = 0;
        if (recv_size > 2) {
            for (n; n < strlen(server_reply); n++) {
                // Proses dekripsi, yaitu mengembalikan representasi
                // ASCII dari pesan pengguna yang representasi ASCII-nya
                // sudah diacak-acak saat proses enkripsi.
                for (a = 0; a < 95; a++) {
                    if (server_reply[n] - 32 == table[a]) {
                        server_reply[n] = a + 32;
                        break;
                    }
                }
                printf("%c",server_reply[n]);
            }
            // Setiap program ini menerima satu pesan dari server,
            // maka variabel ini akan bertambah. Hal ini agar program
            // mengetahui harus mengirim request apa pada periode 
            // selanjutnya.
            msgCounter++;
            printf("\n");  
        }
        
        // Menutup koneksi soket dan menghapus memory
        // yang tadi digunakan untuk WSADATA (WinSock).
        closesocket(s);
        WSACleanup();

        // Program diizinkan untuk istirahat sejenak
        // agar tidak crash.
        sleep(1);
    }
}