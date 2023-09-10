#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_LINE_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    double nota1;
    double nota2;
} Aluno;

void calcularSituacao(Aluno aluno, FILE *outputFile) {
    double media = (aluno.nota1 + aluno.nota2) / 2.0;
    const char *situacao = (media >= 7.0) ? "APROVADO" : "REPROVADO";
    fprintf(outputFile, "%s, %.2lf, %s\n", aluno.name, media, situacao);
}

int main() {
    FILE *inputFile = fopen("DadosEntrada.csv", "r");
    FILE *outputFile = fopen("SituacaoFinal.csv", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        Aluno aluno;
        char *token = strtok(line, ",");
        strncpy(aluno.name, token, MAX_NAME_LENGTH);

        
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");

        
        token = strtok(NULL, ",");
        aluno.nota1 = atof(token);
        token = strtok(NULL, ",");
        aluno.nota2 = atof(token);

        calcularSituacao(aluno, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Processamento concluído. Resultados gravados em SituacaoFinal.csv\n");

    return 0;
}
