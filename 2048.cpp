#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int m[4][4];

// Shift left
void addLeft(int m[4][4]){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(m[j][i] == 0) continue;
			int k = j+1;
			while(k < 4){
				if(m[j][i] == m[k][i]){
					m[j][i] += m[k][i];
					m[k][i] = 0;
					break;
				}
				else if(m[k][i] == 0) k++;
				else break;
			}
		}
	}
}

void moveLeft(int m[4][4]){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(m[j][i] == 0){
				int k = j+1;
				while(k < 4){
					if(m[k][i] != 0){
						m[j][i] = m[k][i];
						m[k][i] = 0;
						break;
					}
					k++;
				}
			}
		}
	}
}

// Shift up
void addUp(int m[4][4]){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(m[j][i] == 0) continue;
			int k = i+1;
			while(k < 4){
				if(m[j][i] == m[j][k]){
					m[j][i] += m[j][k];
					m[j][k] = 0;
					break;
				}
				else if(m[j][k] == 0) k++;
				else break;
			}
		}
	}
}

void moveUp(int m[4][4]){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(m[j][i] == 0){
				int k = i+1;
				while(k < 4){
					if(m[j][k] != 0){
						m[j][i] = m[j][k];
						m[j][k] = 0;
						break;
					}
					k++;
				}
			}
		}
	}
}

// Shift right
void addRight(int m[4][4]){
	for(int i=3; i>=0; i--){
		for(int j=3; j>=0; j--){
			if(m[j][i] == 0) continue;
			int k = j-1;
			while(k >= 0){
				if(m[j][i] == m[k][i]){
					m[j][i] += m[k][i];
					m[k][i] = 0;
					break;
				}
				else if(m[k][i] == 0) k--;
				else break;
			}
		}
	}
}

void moveRight(int m[4][4]){
	for(int i=3; i>=0; i--){
		for(int j=3; j>=0; j--){
			if(m[j][i] == 0){
				int k = j-1;
				while(k >= 0){
					if(m[k][i] != 0){
						m[j][i] = m[k][i];
						m[k][i] = 0;
						break;
					}
					k--;
				}
			}
		}
	}
}

// Shift down
void addDown(int m[4][4]){
	for(int i=3; i>=0; i--){
		for(int j=3; j>=0; j--){
			if(m[j][i] == 0) continue;
			int k = i-1;
			while(k >= 0){
				if(m[j][i] == m[j][k]){
					m[j][i] += m[j][k];
					m[j][k] = 0;
					break;
				}
				else if(m[j][k] == 0) k--;
				else break;
			}
		}
	}
}

void moveDown(int m[4][4]){
	for(int i=3; i>=0; i--){
		for(int j=3; j>=0; j--){
			if(m[j][i] == 0){
				int k = i-1;
				while(k >= 0){
					if(m[j][k] != 0){
						m[j][i] = m[j][k];
						m[j][k] = 0;
						break;
					}
					k--;
				}
			}
		}
	}
}

int main(){	
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			scanf("%d", &m[j][i]);
		}
	}
	
	int t;
	scanf("%d", &t);
	
	switch(t){
		case 0:
			addLeft(m);
			moveLeft(m);
			break;
		case 1:
			addUp(m);
			moveUp(m);
			break;
		case 2:
			addRight(m);
			moveRight(m);
			break;
		case 3:	
			addDown(m);
			moveDown(m);
			break;
	}
	
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			printf("%d ", m[j][i]);
		}
		printf("\n");
	}
	
	return 0;
}
