// Ida Bagus Krishna Yoga Utama (1506716983)
// Nurian Satya Wardana (1506717071)

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include "header.h"


int main(){	
	char pilih;
	char rpt1;

	do{
		
		printHeader();
		
		printf("\n 1. Kirim Pesan\n"
			   " 2. Petunjuk Penggunaan Program \n"
			   " 3. Exit \n"
			   "\n"
			   " Masukkan pilihan Anda (1/2/3): ");
		scanf(" %c", &pilih);
		
		switch(pilih){
			case '1':
				sender();
				break;
			case '2' :
				helpMenu();
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
		scanf(" %c", &rpt1);
	
	}while(rpt1 == 'y');
	
	return 0;
}
