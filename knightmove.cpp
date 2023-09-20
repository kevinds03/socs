#include <stdio.h>

int moves = 20, count_moves = 0;
char chessboard[10][10];

void Chessboard(char chessboard[][10])
{
	for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            chessboard[i][j] = ' ';
        }
    }
}

void CountMoves(char chessboard[][10], int x, int y){
    if(chessboard[x][y] == 'R' || x < 0 || y < 0 || y >= 8 || x >= 8){
        return;
    }
    else if(chessboard[x][y] == 'Q'){
        if(moves > count_moves){
            moves = count_moves;
        }
        return;
    }
    else if(count_moves >= moves){
        return;
    }
    
    count_moves++;
    chessboard[x][y] = 'R';
    
    CountMoves(chessboard, x+2, y+1);
    CountMoves(chessboard, x+2, y-1);
    CountMoves(chessboard, x-2, y+1);
    CountMoves(chessboard, x-2, y-1);
    CountMoves(chessboard, x+1, y+2);
    CountMoves(chessboard, x+1, y-2);
    CountMoves(chessboard, x-1, y+2);
    CountMoves(chessboard, x-1, y-2);
    
    chessboard[x][y] = ' ';
    count_moves--;
    return;
}

int main(){
    int testcase;
    scanf("%d", &testcase);
    
    char initial_pos[2], end_pos[2];
	for(int i=0; i<testcase; i++){
        moves = 20;
        count_moves = 0;
        
        Chessboard(chessboard);
        
        scanf("%s %s", &initial_pos, &end_pos);
        
		chessboard[7-(initial_pos[1]-'1')][initial_pos[0]-'A'] = 'P';
        chessboard[7-(end_pos[1]-'1')][end_pos[0]-'A'] = 'Q';
    	
		int x = 7 - (initial_pos[1]-'1');
        int y = initial_pos[0] - 'A';
        CountMoves(chessboard, x, y);
        
		printf("Case #%d: %d\n", i+1, moves);
    }
    
    return 0;
}
