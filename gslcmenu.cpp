#include<stdio.h>
#include<string.h>

char menu[50][50], addMenu[50][50];
int price[15], addPrice[15], id;

void ShowMenu()		//Read menu file
{
	FILE *read;
	read = fopen("menu2.txt", "r");
	id = 0;
	while(!feof(read)){
		fscanf(read, "%[^\#]#%d\n", &menu[id], &price[id]);
		id++;
	}
	fclose(read);
}

void MainMenu()	//Main menu
{
	printf("Pilih salah satu opsi berikut ini:\n");
	printf("1. Show Menu\n");
	printf("2. Add New Menu\n");
	printf("3. Sort by Food Name\n");
	printf("4. Sort by Price\n");
	printf("5. Order Food\n");
	printf("6. Exit\n");
}

void PrintMenu()	//Print menu
{
	printf("\nBerikut menu yang dapat Anda pesan:\n");
	printf("No. Makanan				Harga\n");
	for(int i=0; i<id; i++){
		printf("%d. %s				Rp%d\n", i+1, menu[i], price[i]);
	}
}

void AddMenu()		//Add (append) menu
{
	if(id == 10){
		printf("Menu sudah mencapai batas maksimal.\n\n");
	}
	else{
		int idtemp = 0;
		printf("\nInput nama makanan: ");
		scanf(" %[^\n]", &addMenu[idtemp]);
		for(int i=0; i<id; i++){
			if(strcmp(menu[i], addMenu[idtemp]) == 0){
				printf("\nMakanan sudah ada dalam daftar menu. Silahkan masukkan makanan lain.\n\n");
				AddMenu();
			}
		}
		
		printf("Input harga makanan: ");
		scanf("%d", &addPrice[idtemp]);
		
		FILE *append;
		append = fopen("menu2.txt", "a");
		fprintf(append, "\n%s#%d", addMenu[idtemp], addPrice[idtemp]);
		fclose(append);
	}
	ShowMenu();
}

void SortPriceBubble()		//Sort by price (bubble sort)
{
	int temp;
	char strtemp[50];
	for(int i=0; i<id; i++){
		for(int j=0; j<id-1-i; j++){
			if(price[j] > price[j+1]){
				temp = price[j];
				strcpy(strtemp, menu[j]);
				price[j] = price[j+1];
				strcpy(menu[j], menu[j+1]);
				price[j+1] = temp;
				strcpy(menu[j+1], strtemp);
			}
		}
	}
}

void SortNameBubble()		//Sort by name (bubble sort)
{
	int temp;
	char strtemp[50];
	for(int i=0; i<id-1; i++){
		for(int j=0; j<id-i-1; j++){
			if(strcmp(menu[j], menu[j+1]) > 0){
				strcpy(strtemp, menu[j]);
				int temp = price[j];
				strcpy(menu[j], menu[j+1]);
				price[j] = price [j+1];
				strcpy(menu[j+1], strtemp);
				price[j+1] = temp;
			}
		}
	}
}

void MergeName(int left, int mid, int right)	//Sort by name (merge)
{
	int i = left, j = mid + 1, k = 0;
	char strtemp[1+right-left][50];
	int temp[1+right-left];
	
	while(i <= mid && j <= right){
		if(strcmp(menu[i], menu[j]) < 0){
			strcpy(strtemp[k], menu[i]);
			temp[k] = price[i];
			i++;
		}
		else{
			strcpy(strtemp[k], menu[j]);
			temp[k] = price[j];
			j++;
		}
		k++;
	}
	while(i <= mid){
		strcpy(strtemp[k], menu[i]);
		temp[k] = price[i];
		i++; k++;
	}
	while(j <= right){
		strcpy(strtemp[k], menu[j]);
		temp[k] = price[j];
		j++; k++;
	}
	for(int i=left; i<=right; i++){
		strcpy(menu[i], strtemp[i-left]);
		price[i] = temp[i-left];
	}
}

void SortNameMerge(int left, int right)
{
	if(left < right){
		int mid = (left + right) / 2;
		SortNameMerge(left, mid);
		SortNameMerge(mid+1, right);
		MergeName(left, mid, right);
	}
}

void MergePrice(int left, int mid, int right) //Sort by price (merge)
{
	int i = left, j = mid + 1, k = 0;
	char strtemp[1+right-left][50];
	int temp[1+right-left];
	
	while(i <= mid && j <= right){
		if(price[i] <= price[j]){
			temp[k] = price[i];
			strcpy(strtemp[k], menu[i]);
			i++;
		}
		else{
			temp[k] = price[j];
			strcpy(strtemp[k], menu[j]);
			j++;
		}
		k++;
	}
	while(i <= mid){
		temp[k] = price[i];
		strcpy(strtemp[k], menu[i]);
		i++; k++;
	}
	while(j <= right){
		temp[k] = price[j];
		strcpy(strtemp[k], menu[j]);
		j++; k++;
	}
	for(int i=left; i<=right; i++){
		price[i] = temp[i-left];
		strcpy(menu[i], strtemp[i-left]);
	}
}

void SortPriceMerge(int left, int right)
{
	if(left < right){
		int mid = left + (right - left) / 2;
		SortPriceMerge(left, mid);
		SortPriceMerge(mid+1, right);
		MergePrice(left, mid, right);
	}
}

//Pesan makanan

char pesanan[25][25];
int quantity[10];
long long int harga_total[10];

void ScanPesanan(int jenis)
{
	printf("Input nama makanan dan jumlah makanan yang ingin Anda pesan (Input pesanan harus sesuai dengan nama di menu)\n");
	for(int i=0; i<jenis; i++){
		harga_total[i] = 0;
		printf("Nama makanan yang dipesan: ");
		scanf(" %[^\n]", &pesanan[i]);
		for(int j=0; j<id; j++){
			if(strcmp(pesanan[i], menu[j]) == 0){
				printf("Jumlah pesanan: ");
				scanf("%d", &quantity[i]);
				harga_total[i] = price[j] * quantity[i];
			}
		}
		if(harga_total[i] == 0){
			printf("Maaf, makanan yang Anda pesan tidak ada dalam daftar menu.\n"); //validate input
			printf("Apakah Anda ingin mengganti pesanan? (Input 0 = Tidak, 1 = Ya)\n");
			int y;
			scanf("%d", &y);
			if(y == 1){
				i--;
			}
		}
	}
}

long long int GrandTotal(int jenis)
{
	int sum = 0;
	for(int i=0; i<jenis; i++){
		sum += harga_total[i];
	}
	return sum;
}

void PrintSummary(int jenis)
{
	for(int i=0; i<jenis; i++){
		printf("%d. %s\n", i+1, pesanan[i]);
		printf("Qty: %d\n", quantity[i]);
		printf("Harga Satuan: ");
		for(int j=0; j<id; j++){
			if(strcmp(pesanan[i], menu[j]) == 0){
				printf("Rp%d\n", price[j]);
			}
		}
		printf("Harga Total: Rp%lld\n", harga_total[i]);
	}
	printf("\nGrand Total: Rp%lld\n", GrandTotal(jenis));
}

int main()
{
	ShowMenu();
	printf("Selamat datang. ");
	int action, sort = 0;
	
	main_menu:
	MainMenu();
	printf("Opsi yang dipilih: "); scanf("%d", &action);
	if(action == 1){
		ShowMenu();
		PrintMenu(); printf("\n\n");
		goto main_menu;		
	}
	else if(action == 2){
		AddMenu();
		PrintMenu(); printf("\n\n");
		goto main_menu;
	}
	else if(action == 3){
		sortname:
		printf("\nMetode apakah yang Anda ingin guanakan?\n1. Bubble Sort.\n2. Merge Sort.\n");
		printf("Metode yang dipilih: "); scanf("%d", &sort);
		if(sort == 1){
			SortNameBubble();
		}
		else if(sort == 2){
			SortNameMerge(0, id-1);
		}
		else{
			printf("Input valid adalah 1 atau 2.\n\n");
			goto sortname;
		}
		PrintMenu(); printf("\n\n");
		goto main_menu;
	}
	else if(action == 4){
		sortprice:
		printf("\nMetode apakah yang Anda ingin guanakan?\n1. Bubble Sort.\n2. Merge Sort.\n");
		printf("Metode yang dipilih: "); scanf("%d", &sort);
		if(sort == 1){
			SortPriceBubble();
		}
		else if(sort == 2){
			SortPriceMerge(0, id-1);
		}
		else{
			printf("Input valid adalah 1 atau 2.\n\n");
			goto sortprice;
		}
		PrintMenu(); printf("\n\n");
		goto main_menu;
	}
	else if(action == 5){
		int jenis;
		printf("\nBerapa jenis makanan yang akan Anda pesan?\n");
		scanf("%d", &jenis);
		ScanPesanan(jenis); printf("\n\n");

		if(GrandTotal(jenis) > 0){
			PrintSummary(jenis);
			printf("Terimakasih karena telah melakukan pemesanan. Silahkan tunggu pesanan Anda.\n");
			goto main_menu;
		}
		else{
			printf("Terimakasih.\n");
			goto main_menu;
		}
	}
	else if(action == 6){
		printf("\nTerima kasih!\n");
		return 0;
	}
	else{
		printf("Input valid hanya untuk angka 1-6\n\n");
		goto main_menu;
	}
}
