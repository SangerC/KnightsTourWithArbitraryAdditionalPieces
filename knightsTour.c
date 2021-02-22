#include <stdio.h>
#include <stdlib.h>

enum ASCII {ASCII0 = 48,
            ASCIIB = 66,
            ASCIIK = 75,
            ASCIIN = 78,
            ASCIIP = 80,
            ASCIIQ = 81,
            ASCIIR = 82,
            ASCIIa = 97,
            ASCIIp = 112
};

const int NADJX[8] = {1,2, 2, 1,-1,-2,-2,-1};
const int NADJY[8] = {2,1,-1,-2,-2,-1, 1,2};
const int NADJSIZE = 8;

int boardSize;
int pieceSize = 0;







int withinBoard(int x, int y){
    if(x>=0 && x<boardSize && y>=0 && y<boardSize) return 1;
    return 0;
}

void printTwoDArray(int board[boardSize][boardSize]){
    for(int i=boardSize-1; i>=0;i--){
        for(int j=0; j<boardSize; j++){
            if(board[i][j]<10&&board[i][j]>=0)printf(" ");
            printf("  %d",board[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void printPieces(int piecesArrays[boardSize][boardSize][boardSize*boardSize]){

    printf("\n");
    
    for(int pieceIndex=0; pieceIndex<pieceSize; pieceIndex++){
        for(int i=boardSize-1;i>=0;i--){
            for(int j=0;j<boardSize;j++){
                if(piecesArrays[i][j][pieceIndex]<10 && piecesArrays[i][j][pieceIndex]>=0) printf(" ");
                printf("  %d",piecesArrays[i][j][pieceIndex]);
            }
            printf("\n\n");
        }
        printf("\n\n");
    }
}

int knightsTour(int board[boardSize][boardSize], int piecesArrays[boardSize][boardSize][boardSize*boardSize], int piecesState[], int row, int column){

    int step = board[row][column];
    int newRow = row;
    int newColumn = column;

    for(int i=0;i<NADJSIZE;i++){
        newRow = row + NADJX[i];
        newColumn = column + NADJY[i];

        if(withinBoard(newRow, newColumn) && board[newRow][newColumn]==-1){
            if(step==(boardSize*boardSize)-2){ 
                board[newRow][newColumn]=step+1;
                return 1;
            }

            int pieceIndex = 0;
            int capturable = 0;
            int pieceToCapture = -1;
            
            for(int pieceIndex=0;pieceIndex<pieceSize;pieceIndex++){
               if(piecesArrays[newRow][newColumn][pieceIndex]==-1 && piecesState[pieceIndex]){
                  capturable = 1; 
               } 
               else if(piecesArrays[newRow][newColumn][pieceIndex]==1){
                  pieceToCapture = pieceIndex;
               }
            }
            
            if(!capturable){
                board[newRow][newColumn] = step+1;
                
                if(pieceToCapture!=-1) piecesState[pieceToCapture] = 0;

                if(knightsTour(board,piecesArrays,piecesState,newRow,newColumn))return 1;
                
                if(pieceToCapture!=-1) piecesState[pieceToCapture] = 1;
                
                board[newRow][newColumn] = -1;

            }

        }

    }
    
    return 0;
}


int main( int argc, char *argv[]){
    
    if(argc==1){
        
        printf("\nBoard Size: \n");
        
        scanf("%d", &boardSize);

        int board[boardSize][boardSize];

        for(int i=0; i<boardSize;i++){
            for(int j=0; j<boardSize; j++){
                board[i][j]=-1;
            }
        }
        
        char array[boardSize*boardSize*4];
        scanf("%[^q]s",array);
       
        board[array[3]-ASCII0-1][array[2]-ASCIIa] = 0;

        printTwoDArray(board);

        int index = 5;       

        int piecesArrays[boardSize][boardSize][boardSize * boardSize];

        int pieceIndex;

        while(array[index]!='\0'){
            
            pieceIndex = (index-5)/4;

            int pieceRow = array[index+2]-ASCII0-1;

            int pieceColumn = array[index+1]-ASCIIa;

            for(int i=0;i<pieceIndex;i++){
                if(piecesArrays[pieceRow][pieceColumn][i]==1){
                    printf("Pieces placed on same spot");
                    return 1;
                }
            }

            switch(array[index]){
                
                case ASCIIR:
                    for(int i=0; i<boardSize;i++){
                        for(int j=0; j<boardSize;j++){
                            if(i == pieceRow || j == pieceColumn)piecesArrays[i][j][pieceIndex] = -1;  
                            else piecesArrays[i][j][pieceIndex] = 0;  
                        }
                    }
                    break;

                case ASCIIN:
                    for(int i=0; i<boardSize;i++){
                        for(int j=0; j<boardSize;j++){
                            piecesArrays[i][j][pieceIndex] = 0;  
                        }
                    }
                    for(int i=0;i<NADJSIZE;i++){
                        if(withinBoard(NADJX[i]+pieceRow,NADJY[i]+pieceColumn)) piecesArrays[NADJX[i]+pieceRow][NADJY[i]+pieceColumn][pieceIndex] = -1;    
                    }
                    break;

                case ASCIIB:
                    for(int i=0; i<boardSize;i++){
                        for(int j=0; j<boardSize;j++){
                            piecesArrays[i][j][pieceIndex] = 0;  
                        }
                    }
                    for(int i=-pieceColumn;i<=boardSize-pieceColumn;i++){
                        if(withinBoard(pieceRow+i,pieceColumn+i)){
                            piecesArrays[pieceRow+i][pieceColumn+i][pieceIndex]=-1;
                        }
                        if(withinBoard(pieceRow-i,pieceColumn+i)){
                            piecesArrays[pieceRow-i][pieceColumn+i][pieceIndex]=-1;
                        }
                    }
                    break;

                case ASCIIQ:
                     for(int i=0; i<boardSize;i++){
                        for(int j=0; j<boardSize;j++){
                            if(i == pieceRow || j == pieceColumn)piecesArrays[i][j][pieceIndex] = -1;  
                            else piecesArrays[i][j][pieceIndex] = 0;  
                        }
                    }
                    for(int i=-pieceColumn;i<=boardSize-pieceColumn;i++){
                        if(withinBoard(pieceRow+i,pieceColumn+i)){
                            piecesArrays[pieceRow+i][pieceColumn+i][pieceIndex]=-1;
                        }
                        if(withinBoard(pieceRow-i,pieceColumn+i)){
                            piecesArrays[pieceRow-i][pieceColumn+i][pieceIndex]=-1;
                        }
                    }
                    break;

                case ASCIIK:
                    for(int i=0; i<boardSize;i++){
                        for(int j=0; j<boardSize;j++){
                            piecesArrays[i][j][pieceIndex] = 0;  
                        }
                    }
                    for(int i=-1;i<2;i++){
                        for(int j=-1;j<2;j++){
                            if(withinBoard(i+pieceRow,i+pieceColumn)) piecesArrays[i+pieceRow][j+pieceColumn][pieceIndex] = -1;                              
                        }
                    }
                    break;

                case ASCIIP:
                    for(int i=0; i<boardSize;i++){
                        for(int j=0; j<boardSize;j++){
                            piecesArrays[i][j][pieceIndex] = 0;  
                        }
                    }
                    
                    if(pieceRow<boardSize-1){
                        if(pieceColumn>0) piecesArrays[pieceRow+1][pieceColumn-1][pieceIndex] = -1;
                        if(pieceColumn<boardSize-1)piecesArrays[pieceRow+1][pieceColumn+1][pieceIndex] = -1;
                    }

                    break;

                case ASCIIp:
                    for(int i=0; i<boardSize;i++){
                        for(int j=0; j<boardSize;j++){
                            piecesArrays[i][j][pieceIndex] = 0;  
                        }
                    }
                    
                    if(pieceRow>0){
                        if(pieceColumn>0) piecesArrays[pieceRow-1][pieceColumn-1][pieceIndex] = -1;
                        if(pieceColumn<boardSize-1)piecesArrays[pieceRow-1][pieceColumn+1][pieceIndex] = -1;
                    }

                    break;
            }
            piecesArrays[pieceRow][pieceColumn][pieceIndex] = 1;  
            
            pieceSize++;
            index+=4;
        }
 
       
        int piecesState[pieceSize];

        for(int i=0;i<pieceSize;i++){
            piecesState[i] = 1;
        }

        printPieces(piecesArrays);
       
        int output = knightsTour(board,piecesArrays, piecesState, array[3]-ASCII0-1,array[2]-ASCIIa);
       
        if(output){
           printf("\n\nPath Found: \n");
           printTwoDArray(board);
        }
        else printf("\n\nNo Path Found :(");

    }


}
