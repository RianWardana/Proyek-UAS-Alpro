// Ida Bagus Krishna Yoga Utama (1506716983)
// Nurian Satya Wardana (1506717071)

#include <stdio.h>

int getKey() {
	int i, j, temp;
	int keysLength = 0;
	
	// Jumlah maksimal karakter yang bisa ditulis ialah 32,
	// namun user dapat menuliskan key dengan panjang kurang dari itu
	char keys[32];
	
	// Meminta user untuk menulis key
	printf(" Tulis key: ");
	scanf(" %[^\n]%*c", &keys);
	
	// Mencari berapa panjang key yang ditulis user.
	// Ini berguna saat user menuliskan key dengan panjang kurang dari 32 karakter,
	// program tidak perlu melakukan pengulangan sebanyak 32 kali.
	while(keys[keysLength] != '\0') keysLength++;
	int lastIndex = keysLength - 1;
	
	// Melakukan bubble sort terhadap key, mengurutkan kode ASCII dari kecil ke besar
	for (i=0; i<lastIndex; i++) {
		for(j=lastIndex; j>i; j--) {
			if(keys[j] < keys[j-1]) {
				temp = keys[j];
				keys[j] = keys[j-1];
				keys[j-1] = temp;
			}
		}
	}
	
	// Ouput fungsi ini ialah kode ASCII dari median key.
	// Bilangan bulat inilah yang selanjutnya digunakan pada algoritma enkripsi dan dekripsi.
	return keys[keysLength/2];
}
