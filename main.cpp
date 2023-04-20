#include <bits/stdc++.h>
using namespace std;

int M[500][500];
int N;
bool direction = false;

int findTheBetterPlace(int M[500][500], int LENGHT) ;

int calculateCofator(int M[500][500], int I, int J, int LENGTH);

int calculateDeterminant(int M[500][500], int I, int J, int LENGTH);

int resolveDeterminant(int M[500][500], int LENGTH);

int main() {
    
    cin >> N;

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) 
            cin >> M[i][j];

    cout << resolveDeterminant(M, N) << endl;

    return 0;
}

int findTheBetterPlace(int M[500][500], int LENGHT) {
    int zeroAmount = 0;
    int bigger = 0;
    int lineNumber = 0;

    for(int i=0; i<LENGHT; i++) {
        zeroAmount = 0;
        for(int j=0; j<LENGHT; j++) {
            if(!M[i][j]) {
                zeroAmount++;
            }
                
            if(zeroAmount > bigger) {
                direction = false;
                bigger = zeroAmount;
                lineNumber = i;
            }
        }
    }

    for(int i=0; i<LENGHT; i++) {
        zeroAmount = 0;
        for(int j=0; j<LENGHT; j++) {
            if(!M[j][i]) {
                zeroAmount++;
            }

            if(zeroAmount > bigger) {
                bigger = zeroAmount;
                direction = true;
                lineNumber = i;
            }
        }
    }
    return lineNumber;
}

int calculateCofator(int M[500][500], int I, int J, int LENGTH) {
    cout << "calculando cofator de " << M[I][J] << endl;
    return pow(-1, I+J) * calculateDeterminant(M, I, J, LENGTH);
}

int calculateDeterminant(int M[500][500], int I, int J, int LENGTH) {
    int value;
    int acc = 0;
    queue<int> F;
    
    cout << "I: " << I << " J: " << J << endl;

    for(int i=0; i<LENGTH; i++) {
        for(int j=0; j<LENGTH; j++) {
            value = M[i][j];

            if(i!=I and j!=J) {
                cout << "VALUE: " << value << endl;
                F.push(value);
                acc++;
            }
        }
    }

    if(acc > 1) {
        int LENGHT = sqrt(acc);
        int N1[500][500];

        for(int i=0; i<LENGHT; i++)
            for(int j=0; j<LENGHT; j++) {
                N1[i][j] = F.front();
                F.pop();
            }
     
     
        cout << "MATRIZ FORMADA" << endl;
        for(int i=0; i<LENGHT; i++)
            for(int j=0; j<LENGHT; j++)
                cout << N1[i][j] << " ";

        return resolveDeterminant(N1, LENGHT);
    
    }else {
        cout << "VALUE SAINDO: " << F.front() << endl; 
        return F.front();
    }
}

int resolveDeterminant(int M[500][500], int LENGTH) {
    
    cout << "MATRIZ RECEBIDA DE N: " << LENGTH << endl;
    for(int i=0; i<LENGTH; i++) {
        for(int j=0; j<LENGTH; j++)
            cout << M[i][j] << " ";
        cout << endl;
    }
    cout << endl << endl;
    
    int det = 0;

    int lineNumber = findTheBetterPlace(M, LENGTH);
   
    int L[LENGTH];

    if(direction)
        cout << "BEST COLUMN" << endl;
    else cout << "BEST LINE" << endl;

    for(int i=0; i<LENGTH; i++) {
        if(direction) {
            cout << M[i][lineNumber] << endl;
            L[i] = M[i][lineNumber];
        }
        else {
            cout << M[lineNumber][i] << " ";
            L[i] = M[lineNumber][i];
        }
    }

    cout << endl << endl;

    for(int i=0; i<LENGTH; i++) {
        cout << "i: " << i << endl;
        if(direction)
            det += L[i] * calculateCofator(M, i, lineNumber, LENGTH);
        else det += L[i] * calculateCofator(M, lineNumber, i, LENGTH);
    }

    cout << "DETERMINANTE" << endl;
    return det;
}



