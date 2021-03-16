#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int valid_digit(char *ip_str);
int valid_ip(char *ip_str);
void class_ip(char *ip_str);

// return 1 jika hanya mengandung digit, else return 0
int valid_digit(char *ip_str){
	//token digunakan untuk menyimpan potongan string
	char* token;
	int i;
	
	//loop untuk mengopi string dari pointer yang ditunjuk fungsi ke string sementara tempStr agar strtok bisa digunakan
	char tempStr[17];
	for(i=0;i<17;i++){
		tempStr[i] = *(ip_str + i);
	}
	
	//strtok untuk memotong string hingga menemukan "."
	token = strtok(tempStr, ".");
	//jika bukan angka maka atoi(token) akan bernilai NULL sehingga tidak hanya mengandung digit dan mereturn 0
	if(!atoi(token))
		return 0;
	
	//strtok untuk memotong string hingga menemukan "."
	token = strtok(NULL, ".");
	//jika bukan angka maka atoi(token) akan bernilai NULL sehingga tidak hanya mengandung digit dan mereturn 0
	if(!atoi(token))
		return 0;
	
	//strtok untuk memotong string hingga menemukan "."
	token = strtok(NULL, ".");
	//jika bukan angka maka atoi(token) akan bernilai NULL sehingga tidak hanya mengandung digit dan mereturn 0
	if(!atoi(token))
		return 0;
	
	//strtok untuk memotong string hingga menemukan "\0"
	token = strtok(NULL, "\0");
	//jika bukan angka maka atoi(token) akan bernilai NULL sehingga tidak hanya mengandung digit dan mereturn 0
	if(!atoi(token))
		return 0;
		
	return 1;
}

// return 1 jika IP string-nya valid, else return 0
int valid_ip(char *ip_str){
	//token digunakan untuk menyimpan potongan string
	char* token;
	//oktet merupakan variabel untuk menentukan apakah jumlah oktet sudah sesuai
	//j merupakan variabel counter dan temp untuk menyimpan sementara integer
	int oktet=0, j, temp;
	//tempStr dan tempStr2 merupakan variabel untuk menyimpan string sementara dibuat dua karena strtok menyebabkan terpotongnya string
	char tempStr[17],tempStr2[17];
	
	//loop untuk mengopi string dari pointer yang ditunjuk fungsi ke string sementara tempStr agar strtok bisa digunakan
	for(j=0;j<17;j++){
		tempStr[j] = *(ip_str + j);
		tempStr2[j] = tempStr[j];
	}
	//memotong tempStr jika menemukan titik dan memasukkan ke token
	token = strtok(tempStr, ".");
	
	//loop untuk menghitung jumlah oktet (berdasarkan jumlah titik)
	while(token != NULL){
		oktet++;

		//akan menghitung jumlah titik untuk menghitung kevalidan oktet
		token = strtok(NULL, ".");
	}
	
	//jika oktet valid (berjumlah 4) maka akan dicek apakah bilangan atau bukan isinya
	if(oktet == 4){
		//jika didalamnya hanya bilangan maka akan masuk ke dicek apakah 0<oktet<256
		if(valid_digit(ip_str)){
			//strtok untuk memotong string hingga menemukan "."
			token = strtok(tempStr2, ".");
			//mengubah token ke integer lalu memasukkannya ke temp
			temp = atoi(token);
			
			//melakukan pengecekan apakah 0<temp<256 dan mereturn 0 jika salah satu tidak valid
			if(temp < 1 || temp > 255)
				return 0;
			
			//strtok untuk memotong string hingga menemukan "."
			token = strtok(NULL, ".");
			//mengubah token ke integer lalu memasukkannya ke temp
			temp = atoi(token);
			
			//melakukan pengecekan apakah 0<temp<256 dan mereturn 0 jika salah satu tidak valid
			if(temp < 1 || temp > 255)
				return 0;
			
			//strtok untuk memotong string hingga menemukan "."
			token = strtok(NULL, ".");
			//mengubah token ke integer lalu memasukkannya ke temp
			temp = atoi(token);
			
			//melakukan pengecekan apakah 0<temp<256 dan mereturn 0 jika salah satu tidak valid
			if(temp < 1 || temp > 255)
				return 0;
			
			//strtok untuk memotong string hingga menemukan "."
			token = strtok(NULL, "\0");
			//mengubah token ke integer lalu memasukkannya ke temp
			temp = atoi(token);
			//melakukan pengecekan apakah 0<temp<256 dan mereturn 0 jika salah satu tidak valid
			if(temp < 1 || temp > 255)
				return 0;
			
			return 1;
		}	
	}
		
	return 0;
}
    
// Prosedur untuk Mencetak Kelas dari IP Address
void class_ip(char *ip_str){
	//token digunakan untuk menyimpan potongan string
	char* token;
	//variabel penyimpan nilai oktet pertama temp dan counter
	int oktet1,i;
	//variabel penyimpan string sementara untuk menggunakan strtok
	char tempStr[17];
	
	//loop untuk mengopi string dari pointer yang ditunjuk fungsi ke string sementara tempStr agar strtok bisa digunakan
	for(i=0;i<16;i++){
		tempStr[i] = *(ip_str + i);
	}
	
	//strtok untuk memotong string hingga menemukan "." sebagai oktet pertama
	token = strtok(tempStr, ".");
	
	//mengubah token ke integer lalu memasukkannya ke oktet1
	oktet1 = atoi(token);
	
	//jika memenuhi kelas maka akan mencetak sesuai dengan spesifikasi
	if(oktet1 < 128)
		printf("Alamat IP Kelas A.\n");
	
	else if(oktet1 < 192)
		printf("Alamat IP Kelas B.\n");
	
	else if(oktet1 < 225)
		printf("Alamat IP Kelas C.\n");
	
	else if(oktet1 < 240)
		printf("Alamat IP Kelas D.\n");
	
	else if(oktet1 < 256)
		printf("Alamat IP Kelas E.\n");
}

int main() {
	//untuk menyimpan string karena maksimal yang valid ddd.ddd.ddd.ddd maka panjangnya 16 dengan \0
    char input[17];
	
	//read input string
	printf("Masukkan alamat IP : ");
	scanf("%17s", &input);
	
	//jika valid akan menentukan kelas dan jika tidak akan mencetak tidak valid
	if (valid_ip(input) == 0)
		printf("Alamat IP Tidak Valid\n");
	
	else{
		printf("Alamat IP Valid\n");
		class_ip(input);
	}
    
    return 0;
}
