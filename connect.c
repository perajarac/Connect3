#include <stdio.h>
#include <stdlib.h>
#define SAFE_MALLOC(p, n, tip)\
p=malloc(n*sizeof(tip));\
if (p==NULL){\
    printf("MEM_GRESKA");\
    exit(-1);\
}

int** ucitavanje(int m, int n){
    int** matrica;
    SAFE_MALLOC(matrica, m, int*);
    for (int i=0; i<m; i++ ){
        SAFE_MALLOC(matrica[i], n, int)
        for (int j=0; j<n; j++){
            scanf("%d",&matrica[i][j]);
        }
    }
    return matrica;
}

int provera(int** matrica, int m, int n, int* p){
    for (int i=m-1; i>0; i--){
        for (int j=0; j<n; j++){
            if (matrica[i][j]==0 && matrica[i-1][j]!=0){
                return 1;
            }
        }
    }
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            int flag=0;
            for (int k=0; k<3; k++){
                if (matrica[i][j]==p[k]){
                    flag=1;
                }
            }
            if (flag==0) return 1;
        }
    }
    return 0;
}

char* pobednik(int** matrica, int m, int n){
    int red=0, kolona=0, dijagonala=0;
    for (int i=m-1; i>2; i--){
        for (int j=0; j<n-3; j++){
            for (int k=1; k<4;k++){
                if (matrica[i][j+k-1]==matrica[i][j+k]){
                    red++;
                }    
                if (red==3){
                    switch(matrica[i][j]){
                        case 1:
                            return "POBEDIO ZUTI";
                        case 2:
                            return "POBEDIO CRVENI";
                    }
                }
                if (k==3) red=0;
            }
        }    
    }            
               
    for (int i=m-1; i>2; i--){
        for (int j=0; j<n-3; j++){
            for (int k=1; k<4;k++){
                if (matrica[i-k+1][j]==matrica[i-k][j]){
                    kolona++;
                }    
                if (kolona==3){
                    switch(matrica[i][j]){
                        case 1:
                            return "POBEDIO ZUTI";
                        case 2:
                            return "POBEDIO CRVENI";
                    }
                    
                }
                if (k==3) kolona=0;
            }
        }    
    }          
    
    for (int i=m-1; i>2; i--){
        for (int j=0; j<n-3; j++){
            for (int k=1; k<4;k++){
                if (matrica[i-k+1][j+k-1]==matrica[i-k][j+k]){
                    dijagonala++;
                }    
                if (dijagonala==3){
                    switch(matrica[i][j]){
                        case 1:
                            return "POBEDIO ZUTI";
                        case 2:
                            return "POBEDIO CRVENI";
                    }
                }
                if (k==3) dijagonala=0;
            }
        }    
    }
    return "NEMA POBEDNIKA";
}    

void ispis(int** matrica, int m, int n){
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            if (j!=n-1){
                printf("%d ", matrica[i][j]);
            }
            else {
                printf("%d", matrica[i][j]);
            }
        }
        putchar('\n');
    }
}

void oslobadjanje(int** matrica, int m, int n, int* p){
    for (int i=0; i<m; i++) free(matrica[i]); 
    free(matrica); 
    free(p);
}


int main(){
    int** matrica;
    int* p;
    int m, n, i=0;
    scanf("%d%d",&m, &n);
    if (m<=0 || n<=0){
        return 0;
    }
    SAFE_MALLOC(p, 3, int);
    for (int* t=p; t<p+3; *t++){
        *t=i++;
    }
    matrica=ucitavanje(m, n);
    if (provera(matrica, m, n, p)==1){
        oslobadjanje(matrica, m, n, p);
        return 0;
    }
    ispis(matrica, m, n);
    printf("%s", pobednik(matrica, m, n));
    oslobadjanje(matrica, m, n, p);
    return 0;
}