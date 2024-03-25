#include <iostream>
#include <time.h>
using namespace std;

void MulM1M2(double **M1, double **M2, double **MR, int l1, int c2)
{
    for (int i = 0; i < l1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            MR[i][j] = 0;
            for (int k = 0; k < c2; k++)
            {
                MR[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
}

void transpostaM2(double **M2, double **M2T, int l2, int c2)
{
    for (int i = 0; i < l2; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            M2T[i][j] = M2[j][i];
        }
    }
}

void MulM1M2T(double **M1, double **M2T, double **MR, int l1, int c2)
{
    for (int i = 0; i < l1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            MR[i][j] = 0;
            for (int k = 0; k < c2; k++)
            {
                MR[i][j] += M1[i][k] * M2T[k][j];
            }
        }
    }
}

void genMat(double **M, int linhas, int colunas)
{
    srand(time(NULL));
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            M[i][j] = rand() % 100;
        }
    }
}

void exibeMat(int linhas, int colunas,double **M){
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}


int main(int argc, char *argv[])
{
    float tempo1 = 0.0;
    float tempo2 = 0.0;
    clock_t inicio, fim;

    if (argc != 6)
    {
        cout << "Uso: ./mulmatriz.x l1 c1 l2 c2 o|t" << endl;
        return 1;
    }

    int l1, c1, l2, c2;
    char metodo;
    double **M1, **M2, **M2T, **MR;

    l1 = atoi(argv[1]);
    c1 = atoi(argv[2]);
    l2 = atoi(argv[3]);
    c2 = atoi(argv[4]);
    metodo = argv[5][0];

    M1 = new double *[l1];
    M2 = new double *[l2];
    M2T = new double *[l2];
    MR = new double *[l1];

    for (int i = 0; i < l1; i++)
    {
        M1[i] = new double[c1];
    }
    for (int i = 0; i < l2; i++)
    {
        M2[i] = new double[c2];
        M2T[i] = new double[c2];
        MR[i] = new double[c2];
    }
    genMat(M1, l1, c1);
    genMat(M2, l2, c2);

    
    if (metodo == 't')
    {
        inicio = clock();
        transpostaM2(M2, M2T, l2, c2);
        MulM1M2T(M1, M2T, MR, l1, c2);
        fim = clock();
        tempo1 = (float)(((fim - inicio) + 0.0)/ CLOCKS_PER_SEC);
        cout << "Tempo de execução Transposta: " << tempo1 << "s" << endl;

    } else if (metodo == 'o')
    {
        inicio = clock();
        MulM1M2(M1, M2, MR, l1, c2);
        fim = clock();
        tempo2 = (float)(((fim - inicio) + 0.0)/ CLOCKS_PER_SEC);
        cout << "Tempo de execução normal: " << tempo2 << "s" << endl;

    }


    for (int i = 0; i < l1; i++)
    {
        delete[] M1[i];
        delete[] MR[i];
    }
    for (int i = 0; i < l2; i++)
    {
        delete[] M2[i];
        delete[] M2T[i];
    }
    delete[] M1;
    delete[] M2;
    delete[] M2T;
    delete[] MR;

    return 0;
}