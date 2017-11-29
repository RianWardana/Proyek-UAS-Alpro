// Ida Bagus Krishna Yoga Utama (1506716983)
// Nurian Satya Wardana (1506717071)

#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#include "../header.h"
//#include "../getKey.h"

int main() {
	int msgCounter = 1;
    printHeader();
    printf("\n");
    int key = getKey();
    populateTable(key);
    printHeader();

	while (1) {
		WSADATA wsa;
    	SOCKET s;
    	struct sockaddr_in server;
    	char *request = malloc(500); 
    	char server_reply[2000];
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
        server.sin_addr.s_addr = inet_addr("103.43.44.105");
        server.sin_family = AF_INET;
        server.sin_port = htons(80);
     
        // Menghubungi server //////////////////////////////////////////////////////////////////
        if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
            printf(" Tidak dapat terhubung dengan server.");
            return 1;
        } //else printf("Koneksi ke server berhasil.\n");

        sprintf(request, "GET /alpro/index.php/app/read/%d HTTP/1.1\r\n"
                        	"Host: 103.43.44.105\r\n"
                        	"Connection: keep-alive\r\n"
                        	"Accept: */*\r\n\r\n", msgCounter);

        send(s, request, strlen(request), 0);

        recv_size = recv(s, server_reply, 2000 , 0);
        server_reply[recv_size] = '\0';

        // int r = 0;
        // while (server_reply[r] != '\0') r++;

        //printf("%c", server_reply[473]);
        // printf("%s", server_reply);

        // int serverLength = strlen(server_reply);
        // printf(" %d ", r);
        
        int a;
        if (server_reply[473] != 'X') { //tadinya pakai [473] // 442
            printf(" ");
        	int n = (server_reply[473] == '\n' ? 473 : 472); //tadinya pakai [473:472] // 442:441
	        for (n; n < strlen(server_reply); n++){
                for (a = 0; a < 95; a++) {
                    if (server_reply[n] - 32 == table[a]) {
                        server_reply[n] = a + 32;
                        break;
                    }
                }
                printf("%c",server_reply[n]);
			}
	        msgCounter++;
            // printf("\n");
        }
       
        closesocket(s);
        WSACleanup();
        sleep(1);
	}
}
