#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#include "header.h"
#include "getKey.h"

int main() {
    char nama[20];                      	// nama pengirim pesan sebagai pengenal
    char msgRaw[99];                    	// pesan yang ditulis pengguna dengan panjang maksimal 100 karakter

    printHeader();
    int key = getKey();
    
    printHeader();
    printf(" Nama Anda: ");
    scanf(" %[^\n]%*c", &nama);

    while (1) {
        printHeader();
        printf(" Pesan Anda: ");
        scanf(" %[^\n]%*c", &msgRaw);

        WSADATA wsa;
        SOCKET s;
        struct sockaddr_in server;
        char *header = malloc(500);             // header untuk HTTP POST request
        char *msgWithName = malloc(120);        // pesan yang sudah disertai dengan nama pengirim
        char *msgEncrypted = malloc(120);       // pesan yang sudah terenkripsi
        char *msgUrlFormatted = malloc(130);    // pesan yang sudah sesuai format HTTP POST x-www-form-urlencoded
     
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
        sprintf(msgWithName, "%s: %s", nama, msgRaw);

        // sementara, msgEncrypted = msgWithName, tapi nanti diganti ya
        sprintf(msgEncrypted, "%s", msgWithName);

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
        sleep(1);
    }
}
