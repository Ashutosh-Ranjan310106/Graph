#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int **matrix;
    int rows;
    int columns;
} AdjaciantMatrix;
typedef struct
{
   int row_index;
   int col_index;
   int Value;
}element;

typedef struct
{
    int rows;
    int cols;
    int num_element;
    element* sparseM;
}sparseMatrix;
typedef struct
{
    int v1;
    int v2;
}Edge;

void createAdjaciantMatrix(AdjaciantMatrix *adm,int num_node){
    adm->matrix=(int**)malloc(sizeof(int*));
    adm->rows=num_node;
    for (int i=0;i<adm->rows;i++){
        adm->matrix[i]=(int*)calloc(num_node,sizeof(int));
    }
    adm->columns=num_node;
}
void updateEdgeFrequency(AdjaciantMatrix * adm, int term_index, int document_index, int frequency){
    adm->matrix[document_index][term_index]=frequency;
}
int getEdgeFrequency(AdjaciantMatrix *tdm,int term_index, int document_index){
    return tdm->matrix[document_index][term_index];
}

void createSparseArray(sparseMatrix* sm,int rows, int cols, int num){
    sm->sparseM=(element*) malloc(num*sizeof(element));
    sm->rows=rows;
    sm->cols=cols;
    sm->num_element=num;
    
}


sparseMatrix* toSparseMatrix(AdjaciantMatrix *adm){
    sparseMatrix *sm;
    int c=0;
    sm=(sparseMatrix*)malloc(sizeof(sparseMatrix));
    for (int i=0;i<adm->rows;i++){
        for (int j=0;j<adm->columns;j++){
            if (adm->matrix[i][j]!=0){
                c+=1;
            }
        }
    }
    createSparseArray(sm,adm->rows,adm->columns,c);
    int index=0; 
    for (int i=0;i<adm->rows;i++){
        for (int j=0;j<adm->columns;j++){
            if (adm->matrix[i][j]!=0){
                sm->sparseM[index].row_index=i;
                sm->sparseM[index].col_index=j;
                sm->sparseM[index].Value=adm->matrix[i][j];
                index+=1;
            }
        }
    }
    return sm;
}

void addedge(AdjaciantMatrix *adm, Edge* edge, int l){
    for (int i = 0;i < l ; i++){
        updateEdgeFrequency(adm, edge[i].v1, edge[i].v2, 1);
    }
}




void printAdjaciantMatrix(AdjaciantMatrix *adm){
    for (int i=0;i<adm->rows;i++){
        for (int j=0;j<adm->columns;j++){
            printf("%d , ",adm->matrix[i][j]);
        }
        printf("\n");
    }
}
void printSparseMatrix(sparseMatrix *sm){
    for (int i=0;i<sm->num_element;i++){
        printf("col: %d, row: %d, value: %d\n",sm->sparseM[i].col_index,sm->sparseM[i].row_index,sm->sparseM[i].Value);
    }
        printf("\n");

}

int main(){
    AdjaciantMatrix* adm1;
    adm1 =(AdjaciantMatrix*)malloc(sizeof(AdjaciantMatrix));
    
    createAdjaciantMatrix(adm1,4);
    updateEdgeFrequency(adm1,3,3,-1);
    updateEdgeFrequency(adm1,2,2,-1);
    updateEdgeFrequency(adm1,1,1,-1);
    updateEdgeFrequency(adm1,0,0,-1);
    Edge edge[4]={{0,1}, {1,2}, {2,3}, {3,1}};
    addedge(adm1,edge,4);
    printAdjaciantMatrix(adm1);

    sparseMatrix *sm;
    sm=(sparseMatrix*)malloc(sizeof(sparseMatrix));
    sm=toSparseMatrix(adm1);
    printSparseMatrix(sm);
    for (int i=0;i<adm1->rows;i++){
        free(adm1->matrix[i]);
    }
    free(adm1->matrix);
    return 0;
}