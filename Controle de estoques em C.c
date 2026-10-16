#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
char nome[100];
int quantidade;
} Item;

void limparBuffer() {
int c;
while ((c = getchar()) != '\n' && c != EOF);
}

void adicionarItem() {
char nome[100];
int quantidade;
printf("Digite o nome do item: ");
fgets(nome, sizeof(nome), stdin);
nome[strcspn(nome, "\n")] = '\0';

printf("Digite a quantidade: ");
scanf("%d", &quantidade);
limparBuffer();

FILE *file = fopen("inventory.txt", "a");
if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
}

fprintf(file, "%s\n%d\n", nome, quantidade);
fclose(file);

printf("Item adicionado com sucesso!\n");
}

void removerItem() {
char nomeBusca[100];
int qtdRemover;

printf("Digite o nome do item: ");
fgets(nomeBusca, sizeof(nomeBusca), stdin);
nomeBusca [strcspn(nomeBusca, "\n")] = '\0';

printf("Digite a quantidade a ser removida: ");
scanf("%d", &qtdRemover);
limparBuffer();

FILE *file = fopen("inventory.txt", "r");
if (file == NULL) {
    printf("Item não encontrado.\n");
    return;
}

Item itens[100];
int totalItens = 0;
char linhaNome[100];
char linhaQtd[20];

while (fgets(linhaNome, sizeof(linhaNome), file) != NULL && fgets(linhaQtd, sizeof(linhaQtd), file) != NULL) {
    linhaNome[strcspn(linhaNome, "\n")] = '\0';
    strcpy(itens[totalItens].nome, linhaNome);
    itens[totalItens].quantidade = atoi(linhaQtd);
    totalItens++;
}
fclose(file);

int encontrado = 0;
int indiceEncontrado = -1;

for (int i = 0; i < totalItens; i++) {
    if (strcmp(itens[i].nome, nomeBusca) == 0) {
        encontrado = 1;
        indiceEncontrado = i;
        break;
    }
}

if (!encontrado) {
    printf("Item não encontrado.\n");
    return;
}

if (itens[indiceEncontrado].quantidade < qtdRemover) {
    printf("Estoque insuficiente. Quantidade disponível: %d\n", itens[indiceEncontrado].quantidade);
    return;
}

itens[indiceEncontrado].quantidade -= qtdRemover;

file = fopen("inventory.txt", "w");
if (file == NULL) {
    printf("Erro ao atualizar o arquivo.\n");
    return;
}

for (int i = 0; i < totalItens; i++) {
    if(itens[i].quantidade == 0) {
        continue;
    }
    fprintf(file, "%s\n%d\n", itens[i].nome, itens[i].quantidade);
}
fclose(file);

if (itens[indiceEncontrado].quantidade == 0) {
    printf("Item removido do estoque!\n");
   } else {
    printf("Quantidade atualizada com sucesso!\n");
   }
}

void listarEstoque() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("O estoque está vazio.\n");
        return;
    }
    
char linhaNome[100];
char linhaQtd[20];
int temItens = 0;

long pos = ftell(file);
fseek(file, 0, SEEK_END);
if (ftell(file) == 0) {
    fclose(file);
    printf("O estoque está vazio.\n");
    return;
}
fseek(file, pos, SEEK_SET);

printf("==================================\n");
printf("         Estoque Atual            \n");
printf("==================================\n");

while (fgets(linhaNome, sizeof(linhaNome), file) != NULL && fgets(linhaQtd, sizeof(linhaQtd), file) != NULL) {
    linhaNome[strcspn(linhaNome, "\n")] = '\0';
    int qtd = atoi(linhaQtd);
    
    if (strlen(linhaNome) > 0) {
        printf("Nome: %s\n", linhaNome);
        printf("Quantidade: %d\n", qtd);
        temItens = 1;
    }
}
fclose(file);

if (!temItens) {
    printf("O estoque está vazio.\n");
    }
}

int main() {
    int opcao;
    do {
        printf("==================================\n");
        printf("        Controle de Estoque       \n");
        printf("==================================\n");
        printf("O que deseja fazer?\n\n");
        printf("1. Adicionar item.\n");
        printf("2. Remover item.\n");
        printf("3. Listar estoque.\n");
        printf("4. Sair.\n");
         printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            limparBuffer ();
            printf("Opção inválida! Tente novamente.\n");
            continue;
        }
        limparBuffer ();
        
    switch (opcao) {
        case 1:
            adicionarItem();
            break;
        case 2:
            removerItem();
            break;
        case 3:
            listarEstoque();
            break;
        case 4:
            printf("Obrigada por usar o controle de estoques! Até a próxima.\n");
            break;
            default:
            printf("Opção inválida! Tente novamente.\n");
            break;
    }
} while (opcao != 4);
    
return 0;
}