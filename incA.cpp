#include<stdio.h>

int max(int a, int b, int c){
	if(a >= b && a >= c) return a;
	else if(b >= a && b >= c) return b;
	else if(c >= a && c >= b) return c;
}

int min(int a, int b, int c){
	if(a <= b && a <= c) return a;
	else if(b <= a && b <= c) return b;
	else if(c <= a && c <= b) return c;
}

int main(){
	int n, tres;
	scanf("%d %d", &n, &tres);
	
	int rating[n];
	for(int i=0; i<n; i++){
		scanf("%d", &rating[i]);
	}
	
	int balRating = 0, bal = 0;;
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			for(int k=j+1; k<n; k++){
				if(max(rating[i], rating[j], rating[k]) - min(rating[i], rating[j], rating[k]) <= tres){
					if(balRating < rating[i] + rating[j] + rating[k])
						balRating = rating[i] + rating[j] + rating[k];
					bal++;
				}
			}
		}
	}
	
	if(bal == 0) printf("-1\n");
	else printf("%d %d", bal, balRating);
	
	return 0;
}
