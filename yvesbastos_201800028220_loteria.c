#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

typedef struct node{
    
    int value;
    char id[129];
}node;

node initNode(char id[129], int value){

    node element;
    element.value = value;

    strcpy(element.id, id);

    return element;
}



void heapifyMin(node *root, uint32_t lenght, uint32_t index){
 
    node aux;
    
    uint32_t father = index;
    uint32_t left = 2*index + 1;
    uint32_t right = 2*index + 2;

    if(left < lenght && root[left].value < root[father].value){
        father = left; 
    }
    if(right < lenght && root[right].value < root[father].value ){
        father = right;
    }
    if(father != index){

        aux = root[index];
        root[index] = root[father];
        root[father] = aux;
        heapifyMin(root, lenght, father);
    }

}

void heapifyMax(node *root, uint32_t lenght, uint32_t index){
 
    node aux;
    
    uint32_t father = index;
    uint32_t left = 2*index + 1;
    uint32_t right = 2*index + 2;

    if(left < lenght && root[left].value > root[father].value){
        father = left; 
    }
    if(right < lenght && root[right].value > root[father].value ){
        father = right;
    }
    if(father != index){

        aux = root[index];
        root[index] = root[father];
        root[father] = aux;
        heapifyMax(root, lenght, father);
    }

}

int main(int argc, char const *argv[])
{

    FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

    int numbBet, cash, bet, actul;
    int result[10];
    char id[129];

    fscanf(input,"%d %d", &cash, &numbBet);

    node* vectorMax = (node*)malloc(numbBet*sizeof(node));
    node* vectorMin = (node*)malloc(numbBet*sizeof(node));

    for(int i = 0; i < 10; i++){

        fscanf(input,"%d", &result[i]);

    }

    for(int i = 0; i < numbBet; i++){
        int value = 0;
        fscanf(input, "%s", id);
        for(int j = 0; j < 15; j++){
            fscanf(input, "%d", &bet);
            for(int k = 0; k < 10 ; k++){

                if(bet == result[k]){
                    value++;
                }
            }
        }

        vectorMax[i] = initNode(id, value);
        vectorMin[i] = initNode(id, value);
    }

    for (int i = numbBet - 1; i >= 0; i--)
    {
        heapifyMax(vectorMax, numbBet, i);
        heapifyMin(vectorMin, numbBet, i);
    }

    int winners = 0, loosers = 0;

    for(int i = 0; i < numbBet; i++){
        if(vectorMax[i].value == vectorMax[0].value){
            winners++;
        }
        if(vectorMin[i].value == vectorMin[0].value){
            loosers++;
        }

    }
    
    fprintf(output, "[%d:%d:%d]\n", winners, vectorMax[0].value, (cash / 2) /winners);
    int max = vectorMax[0].value;
    int aux = numbBet;

    for(int i = 0; i < numbBet; i++){
        if(vectorMax[0].value == max){
            fprintf(output, "%s\n", vectorMax[0].id);
            vectorMax[0] = vectorMax[aux - 1];
            aux--;
            heapifyMax(vectorMax, aux, 0);
        }
    }

    fprintf(output, "[%d:%d:%d]\n", loosers, vectorMin[0].value, (cash / 2) / loosers);
    int min = vectorMin[0].value;
    aux = numbBet;

    for(int i = 0; i < numbBet; i++){
         if(vectorMin[0].value == min){
            fprintf(output, "%s\n", vectorMin[0].id);
            vectorMin[0] = vectorMin[aux - 1];
            aux--;
            heapifyMin(vectorMin, aux, 0);
        }
    }

    fclose(input);
	fclose(output);
    
    return 0;
}
