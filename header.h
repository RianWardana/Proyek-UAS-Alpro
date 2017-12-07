// Ida Bagus Krishna Yoga Utama (1506716983)
// Nurian Satya Wardana (1506717071)

// Melampirkan libary-library yang dibutuhkan.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

// Melampirkan header ini untuk mencari key
// dari teks yang dimasukkan pengguna
#include "getKey.h"


// Deklarasi prototype dari fungsi yang
// nanti akan digunakan
int sender();
void printHeader();
int helpMenu();
void populateTable();

// Mendeklarasikan array yang nanti
// akan digunakan untuk proses enkripsi.
int table[95];


// Fungsi ini adalah untuk mengirimkan pesan
// ke server.
int sender(){
	char nama[20];								// nama pengguna
    char msgRaw[99];							// pesan yang ditulis pengguna
    char *msgWithName = (char*)malloc(120); 	// pesan yang sudah disertai dengan nama pengirim
	
	// Digunakan untuk mengakhiri program
	// jika pengguna menulis "selesai".
	char selesai[10];							
	strcpy(selesai,"selesai");					

	// Menampilkan tulisan pada atas program
    printHeader();
    printf("\n");

    // Meminta pengguna menulis 'password'
    // sebagai key pada proses enkripsi.
    int key = getKey();
    
    // Digunakan untuk proses enkripsi
    populateTable(key);

    // Meminta pengguna untuk menulis nama
    printf(" Nama Anda: ");
    scanf(" %[^\n]%*c", &nama);

    // Hal ini akan diulang selamanya (selama program berjalan)
 	while (1) {
        printHeader();

        // Meminta pengguna menuliskan pesannya
        printf("\n Pesan Anda: ");
        scanf(" %[^\n]%*c", msgRaw);
        
        // Menghentikan program saat pengguna menulis "selesai"
        if(strcmp(msgRaw, selesai) == 0){
        	exit(1);
		}
        
        // Menggabungkan [NAMA] dan [PESAN] menjadi [NAMA]: [PESAN]
        sprintf(msgWithName, "%s: %s", nama, msgRaw);
        
        int i = 0, length = 0;
		
		// Untuk mengetahui panjang [PESAN]
		while(msgWithName[length] != '\0'){
			length++;
		} 

		// Mendeklarasi msgEncrypted yang panjangnya
		// sesuai dengan panjang [PESAN].
		char *msgEncrypted = (char*)malloc(length);

		// Melakukan enkripsi pada pesan pengguna yaitu dengan
		// memetakan representasi ASCII dari masing-masing huruf
		// pada pesan.
		for (i = 0; i < length; i++) {
			if ((msgWithName[i] > 126) || (msgWithName[i] < 32)) msgWithName[i] == '?';
			msgEncrypted[i] = table[msgWithName[i]-32] + 32;
		}

		// Deklarasi variabel-variabel yang dibutuhkan untuk library WinSock
        WSADATA wsa;
        SOCKET s;
        struct sockaddr_in server;
        char *header = (char*)malloc(500);             // header untuk HTTP POST request
        char *msgUrlFormatted = (char*)malloc(130);    // pesan yang sudah sesuai format HTTP POST x-www-form-urlencoded
     
        // Inisialisasi Winsock //////////////////////////////////////////////////////////////////
        if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
            printf(" Winsock failed. Error code: %d", WSAGetLastError());
            return 1;
        } //else printf("Winsock initialised.\n");
         
        // Membuat socket ///////////////////////////////////////////////////////////////////////
        if((s = socket(AF_INET, SOCK_STREAM, 0 )) == INVALID_SOCKET) {
            printf(" Could not create socket. Error code: %d", WSAGetLastError());
            return 1;
        } //else printf("Socket created.\n");
        
        // Definisi identitas server ///////////////////////////////////////////////////////////
        // Mendefinisikan IP dari server
        server.sin_addr.s_addr = inet_addr("103.43.44.105");
        server.sin_family = AF_INET;

        // Mendefinisikan pada port berapa program server
        // listening kepada request.
        server.sin_port = htons(8888);
     
        // Menghubungi server //////////////////////////////////////////////////////////////////
        if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
            printf(" Tidak dapat terhubung dengan server.");
            return 1;
        } //else printf("Koneksi ke server berhasil.\n");
		
        // Kirim pesan ////////////// ///////////////////////////////////////////////////////////
        send(s, msgEncrypted, strlen(msgEncrypted), 0);
        printf(" Pesan terkirim.");
        
        // Menutup koneksi soket dan menghapus memory
        // yang tadi digunakan untuk WSADATA (WinSock).
        closesocket(s);
        WSACleanup();
    }
}


// Mengisi tabel yang melakukan pemetaan dari satu
// angka ke angka lain, yang mana angka tersebut
// adalah representasi ASCII dari setiap huruf 
// pada pesan yang ditulis pengguna.
// Dasar melakukannya pemetaan didasarkan atas
// password (key) yang ditulis oleh pengguna.
void populateTable(int key) {
	int i;
	for (i = 0; i < 95; i++) table[i] = -1;

	int a = 0;
	for (i = 0; i < 95; i++) {
		a = a + key;
		if (a > 94) a = a - 95;
		while (table[a] != -1) {
			a++;
			if (a > 94) a = a - 95;
		}
		table[a] = i;
	}
}


// Menampilkan pesan bantuan
int helpMenu(){ 
	char rpt,pilih;
	
	do{
		system("mode 80");
		system("color F0");
		system("cls");
		
		printf("########################################################################\n"
			   "#                ENIGCHAT - Messenger with ASCII Based                 #\n"
			   "#                        Encryption-Decryption                         #\n"
			   "#                                Oleh :                                #\n"
			   "#              1. Ida Bagus Krishna Yoga Utama - 1506716983            #\n"
	           "#                 2. Nurian Satya Wardana - 1506717071                 #\n"
		       "########################################################################\n"
			   "# HELP MENU - PETUNJUK PENGOPERASIAN                                   #\n"
			   "# 1. Masuk ke Menu Kirim Pesan                                         #\n"
			   "# 2. Tulis key (password) untuk enkripsi anda                          #\n"
			   "# 3. Tulis nama anda (nama anda sebagai pengirim pesan)                #\n"
			   "# 4. Tulis isi pesan anda                                              #\n"
			   "# 5. Jika ingin berhenti mengirim pesan, ketik selesai                 #\n"
			   "# 6. Untuk informasi lebih lanjut hubungi: Krishna (ibkyu@live.com),   #\n"
			   "#    Rian (rianwardana@live.com) \n\n"
			   "# Anda ingin kemana?                                                   #\n"
			   "# 1. Menu Kirim Pesan                                                  #\n"
			   "# 2. Exit                                                              #\n"
			   "Masukkan pilihan anda(1/2/3): ");
		scanf(" %c", &pilih);
		
		switch(pilih){
			case '1' :
				sender();
				break;
			case '2' :
				return 0;
				break;
			default :
				printf(" ERROR - Masukkan input yang sesuai!\n");
				break;
		}
		
		printf("\n Apakah ingin memasukkan kata lagi? "
			   "\n Pilih (y) untuk kembali ke awal"
			   "\n Pilih (n) untuk keluar dari program"
			   "\n Pilihan anda (y/n) : ");
		scanf(" %c", &rpt);
	} while(rpt == 'y');
	
	return 0;
}

// Menampilkan header
void printHeader(){
	system("mode 80");
	system("color F0");
	system("cls");
		
	printf("########################################################################\n"
		   "#                ENIGCHAT - Messenger with ASCII Based                 #\n"
		   "#                        Encryption-Decryption                         #\n"	
		   "#                                Oleh :                                #\n"
		   "#              1. Ida Bagus Krishna Yoga Utama - 1506716983            #\n"
           "#                 2. Nurian Satya Wardana - 1506717071                 #\n"
	       "########################################################################\n");	   
}