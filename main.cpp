/* 
 * File:   main.cpp
 * Author: Benet
 *
 * Created on 11 de febrero de 2016, 18:25
 */

#include <iostream>

using namespace std;

//Taulell
const int N_FILES = 9;
const int N_COLUM = 9;
const int N_LLIURES = N_FILES * N_COLUM;
//Menu
const int ADD_NUM = 1;
const int DEL_NUM = 2;
const int EXIT = 3;

/*
 Estructura Casella que conte la info de les variables que te cada casella del sudoku
 */
    typedef struct {
        int numero;
        bool lliure;
        bool original;//dyrtyrtegjhkhjkghj
    } Casella;
/*
 Estructura Sudoku conte una variable casella i el numero de caselles lliures que queden al sudoku.
 */
    typedef struct {
        Casella tauler[N_FILES][N_COLUM];
        int nLliures;
    }Sudoku;

/*
Mostrar el menœ dÕopcions del joc (afegir nœmero, treure nœmero, sortir del joc)
*/
void getMenu()
{
        cout <<"1. Afegir numero."<<endl;
        cout <<"2. Treure numero."<<endl;
        cout <<"3. Sortir joc."<<endl;
        cout <<"Op => ";
}

void generarTaula(Casella tauler[][N_COLUM]){

    for(int i=0; i<N_FILES; i++){
        for (int j=0; j<N_COLUM; j++){
            tauler[i][j].numero=0;
            tauler[i][j].lliure=true;
            tauler[i][j].original=true;
        }
    }

}
void pintarTaula(Casella tauler[][N_COLUM]){
                   cout << "             SUDOKU            " <<endl;
    for(int i=0; i<N_FILES; i++){
        if(i%3==0) cout << "-------------------------------" <<endl;
        cout << "|";
        for(int j=1; j<=N_COLUM; j++){
            if(j!=1 && j%3==0)cout << "{" << tauler[i][j-1].numero << "}|";
            else cout << "{" << tauler[i][j-1].numero << "}";
        }
        cout << endl;
    }
    cout << "-------------------------------" <<endl;
}

void getCoordenades(int &x, int &y){

    cout << "Fila => ";
    cin >> y;
    y--;
    while(y<0 || y>N_FILES-1){
        cout << "Error. Files fora del rang [1-9]" <<endl;
        cout << "Fila => ";
        cin >> y;
        y--;
    }
    cout << "Columna => ";
    cin >> x;
    x--;
    while(x<0 || x>N_COLUM-1){
        cout << "Error. Columna fora del rang [1-9]" <<endl;
        cout << "Columna => ";
        cin >> x;
        x--;
    }
}

int getNewNumber(){
    int r;
    cout << "Valor => ";
    cin >>r;
    return r;
}

bool isValidFila(Casella tauler[][N_COLUM], int y, int numero){
    
    bool valid=true;
    int i=0;
    
    while(valid && i<N_COLUM){
        
        if(tauler[y][i].numero==numero){
            valid=false;
        }else{
            i++;
        }
    }
    
    return valid;
    
}
bool isValidColum(Casella tauler[][N_COLUM], int x, int numero){
    
    bool valid=true;
    int i=0;
    
    while(valid && i<N_FILES){
        
        if(tauler[i][x].numero==numero){
            valid=false;
        }else{
            i++;
        }
    }
    
    return valid;
    
}
bool isValidSubMatriu(Casella tauler[][N_COLUM], int x, int y, int num){

    //saber a quina submatriu esta la coordenada
    
    //1. Saber a quina coordenada x comença la submatriu
   
    int iX;//inici coordenada x submatriu
    
    if(x>2 && x<6){
        iX=3;
    }else if(x>5){
        iX=6;
    }else{
        iX=0;
    }
    
    //2. Saber a quina coordenada y comença la submatriu.
    
    int iY;
     if(y>2 && y<6){
        iY=3;
    }else if(y>5){
        iY=6;
    }else{
        iY=0;
    }   
    
    //Mirar dins de la submatriud si el valor que es vol introduir ja existeix:
    
    bool valid=true;
    int i=iY;
    
    while(valid && i<(iY+3)){
        int j=iX;
        while(valid && j<(iX+3)){
            if(tauler[i][j].numero==num){
                valid=false;
            }else{
                j++;
            }
        }
        i++;
    }
    /*
    for(int i=iY; i<(iY+3); i++){
        for(int j=iX; j<(iX+3); j++){
            if(tauler[i][j].numero==num){
                valid=false;
            }
        }
    }*/
    
    return valid;
    
}
/*
Inici programa.
*/
int main()
{
    Sudoku sudoku;
    generarTaula(sudoku.tauler);
    sudoku.nLliures=N_LLIURES;
    int op;
    
    do{
        //int tauler [N_FILES][N_COLUM];
        
        pintarTaula(sudoku.tauler);
        getMenu();
        cin >> op;

        while( op < 1 || op > 3){
            cout << "Error. Valor no vˆlid." <<endl;
            getMenu();
            cin >> op;
        }

        cout << "Opci— escollida => " << op << endl;

        switch(op){
            case ADD_NUM:
                int cX, cY;
                getCoordenades(cX,cY);
                
                if(sudoku.tauler[cY][cX].lliure){
                    
                    int num;
                    num=getNewNumber();
                    while(num<1 || num>9){
                        cout << "Error. Valor fora del rang [1-9]." <<endl;
                        num=getNewNumber();
                    }
                    
                    if(isValidFila(sudoku.tauler, cY,num)){
                        if(isValidColum(sudoku.tauler,cX, num)){
                            if(isValidSubMatriu(sudoku.tauler,cX,cY,num)){
                                sudoku.tauler[cY][cX].numero=num;
                                sudoku.tauler[cY][cX].lliure=false;
                                sudoku.nLliures--;
                            }else{
                                cout << "Error. El numero "<< num << " ja existeix a la submatriu." <<endl;
                            }
                        }else{
                            cout << "Error. El numero "<< num << " ja existeix a la columna "<< cX+1 << " ." <<endl;
                        }
                    }else{
                        cout << "Error. El numero "<< num << " ja existeix a la fila "<< cY+1 << " ." <<endl;
                    }
                    
                }else{
                    cout << "Aquesta posició ja està ocupada." <<endl;
                }
                
                break;
            case DEL_NUM:
                
                getCoordenades(cX,cY);
                
                if(!sudoku.tauler[cY][cX].lliure){

                    sudoku.tauler[cY][cX].numero=0;
                    sudoku.tauler[cY][cX].lliure=true;
                    sudoku.nLliures++;
                    
                }else{
                    cout << "Aquesta posició no està ocupada." <<endl;
                }               
                break;
            case EXIT:
                cout << "Bye." <<endl;
                break;
            default:
                break;
        }


    }while(op != 3);

    return 0;
}

