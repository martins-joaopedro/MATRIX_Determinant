#include <bits/stdc++.h>
using namespace std;

// Valor alterável de acordo com o tamanho máximo que uma matriz pode assumir
const int MAX = 20;
bool direction = false;
int findBestLine(float M[MAX][MAX], int LENGHT);
float calculateCofactor(float M[MAX][MAX], int I, int J, int LENGTH);
float calculateDeterminant(float M[MAX][MAX], int I, int J, int LENGTH);
float resolveDeterminant(float M[MAX][MAX], int LENGTH);
void printMatrix(bool t, float M[MAX][MAX], int LENGTH);

int main() {
    
    float M[MAX][MAX];
    int N;
    cin >> N;

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) 
            cin >> M[i][j];

    cout << "DETERMINANTE DA MATRIZ: " << resolveDeterminant(M, N) << endl;

    return 0;
}

int findBestLine(float M[MAX][MAX], int LENGHT) {
    int zeros = 0;
    int bigger = 0;
    int lineNumber = 0;

    // Busca pela linha que tem maior quantidade de zeros
    for(int i=0; i<LENGHT; i++) {
        zeros = 0;
        for(int j=0; j<LENGHT; j++) {
            if(!M[i][j]) {
                zeros++;
            }
                
            if(zeros > bigger) {
                direction = false;
                bigger = zeros;
                lineNumber = i;
            }
        }
    }

    // Busca pela coluna que tem maior quantidade de zeros
    for(int i=0; i<LENGHT; i++) {
        zeros = 0;
        for(int j=0; j<LENGHT; j++) {
            if(!M[j][i]) {
                zeros++;
            }

            if(zeros > bigger) {
                bigger = zeros;
                direction = true;
                lineNumber = i;
            }
        }
    }
    return lineNumber;
}

float calculateCofactor(float M[MAX][MAX], int I, int J, int LENGTH) {
    cout << "-> Calculando o cofator de " << M[I][J] << endl;
    return pow(-1, I+J) * calculateDeterminant(M, I, J, LENGTH);
}

float calculateDeterminant(float M[MAX][MAX], int I, int J, int LENGTH) {
    // Gerar outra matriz e resolver o seu determinante
    int acc = 0;
    queue<float> F;
    
    for(int i=0; i<LENGTH; i++) {
        for(int j=0; j<LENGTH; j++) {
            if(i!=I and j!=J) {
                F.push(M[i][j]);
                acc++;
            }
        }
    }

    int LENGHT = sqrt(acc);
    float N1[MAX][MAX];

    for(int i=0; i<LENGHT; i++)
        for(int j=0; j<LENGHT; j++) {
            N1[i][j] = F.front();
            F.pop();
        }
    
    printMatrix(true, N1, LENGHT);

    return resolveDeterminant(N1, LENGHT);
}

float resolveDeterminant(float M[MAX][MAX], int LENGTH) { 
    // Caso a matrix seja uma 2x2 retorna o determinante pelo método trivial -> otimização
    if(LENGTH<=2)
        return M[0][0] * M[1][1] -(M[0][1] * M[1][0]);
    
    // Encontro a melhor linha (ou coluna) para encontrar o determinante através dos cofatores
    int lineNumber = findBestLine(M, LENGTH);
    bool saveDirection = direction;

    // Array auxiliar pra facilitar a manipulação da linha escolhida 
    float L[LENGTH];

    long double det = 0;

    cout << "_______________________________________" << endl;
    saveDirection ? cout << "-> Melhor coluna encontrada: " << endl : cout << "-> Melhor linha encontrada: " << endl;
  
    for(int i=0; i<LENGTH; i++) {
        if(saveDirection) {
            cout << M[i][lineNumber] << endl;
            L[i] = M[i][lineNumber];
        }
        else {
            cout << M[lineNumber][i] << " ";
            L[i] = M[lineNumber][i];
        }
    } cout << endl; 

    for(int i=0; i<LENGTH; i++) {
        // So determina o cofator para elementos que são diferentes de 0
        if(L[i])
            if(saveDirection)
                det += L[i] * calculateCofactor(M, i, lineNumber, LENGTH);
            else det += L[i] * calculateCofactor(M, lineNumber, i, LENGTH);
        else cout << "-> Cofator de 0 => 0" << endl;
    }

    return det;
}

void printMatrix(bool t, float M[MAX][MAX], int LENGTH) {
    if(t)
        cout << endl << "SUB";
    cout << "MATRIZ : " << LENGTH << " x " << LENGTH << endl;
    for(int i=0; i<LENGTH; i++) {
        cout << "[ "; 
        for(int j=0; j<LENGTH; j++)
            cout << M[i][j] << " ";
        cout << "]" << endl;
    }
    cout << endl;
}