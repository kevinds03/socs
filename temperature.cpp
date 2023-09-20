#include<stdio.h>
#include<string.h>

struct City{
		char name[1001];
		double temperature;
		char degree;
	};
	
City info[101];
int id;

void ReadFile()
{
	FILE *read;
	read = fopen("testdata.in", "r");
	id = 0;
	while(!feof(read)){
		fscanf(read, "%[^#]#%lf#%c\n", &info[id].name, &info[id].temperature, &info[id].degree);
		id++;
	}
	fclose(read);
}

int main()
{
	ReadFile();
	
	City tempinfo[101];
	
	for(int i=0; i<id; i++){
		for(int j=0; j<id-i-1; j++){
			if(strcmp(info[j].name, info[j+1].name) > 0){
				City temp = info[j];
				info[j] = info[j+1];
				info[j+1] = temp;
			}
		}
	}
	
	for(int i=0; i<id; i++){
		tempinfo[i] = info[i];
	}
	
	
	for(int i=0; i<id; i++){
		if(info[i].degree == 'F'){
			tempinfo[i].temperature = (tempinfo[i].temperature - 32) * 5 / 9;
		}
	}
	
	for(int i=0; i<id; i++){
		for(int j=0; j<id-i-1; j++){
			if(tempinfo[j].temperature > tempinfo[j+1].temperature){
				City temp = info[j];
				info[j] = info[j+1];
				info[j+1] = temp;
				
				temp = tempinfo[j];
				tempinfo[j] = tempinfo[j+1];
				tempinfo[j+1] = temp;
			}
		}
	}
	
	for(int i=0; i<id; i++){
		printf("%s is %.2lf%c\n", info[i].name, info[i].temperature, info[i].degree);
	}
	
	return 0;
}
