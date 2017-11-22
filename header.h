#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include "getKey.h"
void printHeader();
int sender();
int helpMenu();

int sender(){
	char nama[20];                      	// nama pengirim pesan sebagai pengenal
    char msgRaw[99];                    	// pesan yang ditulis pengguna dengan panjang maksimal 100 karakter
    char pmsh[5];

    printHeader();
    
    int key = getKey();

    printf(" Nama Anda: ");
    scanf(" %[^\n]%*c", &nama);
    
    strcpy(pmsh," : ");

 	while (1) {
        
        printf("\n Pesan Anda: ");
        scanf(" %[^\n]%*c", msgRaw);
        
        strcat(nama, pmsh);
        strcat(nama,msgRaw);
        
        int i = 0, length = 0, j;
		
		while(nama[length] != '\0'){
			length++;
		} 
		
		int encrypted[length];

		for(i=0;i<length;i++){
			encrypted[i]=nama[i]; 
		}

		for(j=0;j<i;j++){
			encrypted[j] -= (100-(key+j));
		}

		printf("\n Data yang telah terenkripsi adalah: \n ");
		for(i = 0; i < length; i++){
			printf("%c", encrypted[i]);
		}
		
		char msgEn[length];
		for(i = 0; i < length; i++){
			msgEn[i] = encrypted[i];
		}

	/* ==================== Start of WinSock Class ===================================================== */
        WSADATA wsa;
        SOCKET s;
        struct sockaddr_in server;
        char *header = (char*)malloc(500);             // header untuk HTTP POST request
        char *msgWithName = (char*)malloc(120);        // pesan yang sudah disertai dengan nama pengirim
        char *msgEncrypted = (char*)malloc(120);       // pesan yang sudah terenkripsi
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
        server.sin_addr.s_addr = inet_addr("103.43.44.105");	// lokasi server
        server.sin_family = AF_INET;
        server.sin_port = htons(80);							// port pada server
     
        // Menghubungi server //////////////////////////////////////////////////////////////////
        if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
            printf(" Tidak dapat terhubung dengan server.");
            return 1;
        } //else printf("Koneksi ke server berhasil.\n");
        
        // Pesan yang dikirim adalah "[NAMA]: [PESAN]"
        //sprintf(msgWithName, "%s: %s", nama, msgEn);

        // sementara, msgEncrypted = msgWithName, tapi nanti diganti ya
        sprintf(msgEncrypted, "%s", msgEn);

        // Formatting header //////////////////////////////////////////////////////////////////
        sprintf(header, "POST /alpro/index.php/app/send HTTP/1.1\r\n"
                        "Host: 103.43.44.105\r\n"
                        "Connection: keep-alive\r\n"
                        "Content-Type: text/plain\r\n"
                        "Accept: */*\r\n"
                        "Content-Length: %d\r\n\r\n", strlen(msgEncrypted) + 4);
        
        // Formatting pesan //////////////////////////////////////////////////////////////////
        sprintf(msgUrlFormatted, "%s\r\n", msgEncrypted);

        // Kirim HTTP POST request ///////////////////////////////////////////////////////////
        send(s, header, strlen(header), 0);
        send(s, msgUrlFormatted, strlen(msgUrlFormatted), 0);
        printf(" Pesan terkirim.");
        
        closesocket(s);
        WSACleanup();
    }
}

int helpMenu(){ 
	char rpt,pilih;
	
	do{
	
		system("mode 80");
		system("color F0");
		system("cls");
		
		printf("########################################################################\n"
			   "#                ENIGMOO - Word Encryption-Decryption                  #\n"	
			   "#                                Oleh :                                #\n"
			   "#              1. Ida Bagus Krishna Yoga Utama - 1506716983            #\n"
	           "#                 2. Nurian Satya Wardana - 1506717071                 #\n"
		       "########################################################################\n"
			   "# HELP MENU - PETUNJUK PENGOPERASIAN                                   #\n"
			   "# 1. Masuk ke Menu Encrypt-Decrypt                                     #\n"
			   "# 2. Tulis pilihan Anda, masukkan 1 untuk enkripsi,                    #\n"
			   "#    masukkan 2 untuk dekripsi                                         #\n"
			   "# 3. Tulis nama file yang akan dienkripsi atau didekripsi              #\n"
			   "# 4. Tulis key pilihan Anda                                            #\n"
			   "# 5. Hasil enkripsi akan disimpan ke dalam file encrypted.txt,         #\n"
			   "#    Hasil dekripsi akan disimpan ke dalam file decrypted.txt          #\n"
			   "# 5. Untuk informasi lebih lanjut hubungi: Krishna (ibkyu@live.com),   #\n"
			   "#    Rian (rianwardana@live.com) \n\n"
			   "# Anda ingin kemana?                                                   #\n"
			   "# 1. Main Menu                                                         #\n"
			   "# 2. Menu Encrypt-Decrypt                                              #\n"
			   "# 3. Exit                                                              #\n"
			   "Masukkan pilihan anda(1/2/3): ");
		scanf(" %c", &pilih);
		
		switch(pilih){
			case '1' :
				//main();
				break;
			case '2' :
				sender();
				break;
			case '3' :
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
	}while(rpt == 'y');
	
	return 0;
}

void printHeader(){
	system("mode 80");
	system("color F0");
	system("cls");
		
	printf("########################################################################\n"
		   "#                ENIGMOO - Word Encryption-Decryption                  #\n"	
		   "#                                Oleh :                                #\n"
		   "#              1. Ida Bagus Krishna Yoga Utama - 1506716983            #\n"
           "#                 2. Nurian Satya Wardana - 1506717071                 #\n"
	       "########################################################################\n");	   
}
