#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
void pr(int **matrix, size_t *rows, size_t row){ //печать матрицы, сюда нужно передавать ещеи  количество строк
	for(size_t i=0;i<row;i++){
		for(size_t j=0;j<rows[i];j++)
			printf("%d ",matrix[i][j]);  
		puts("");      
	}
}
char *mygets(char **str, size_t *L, FILE *in){
	size_t begin=0;
	if (*str==NULL){
		*str=(char *)malloc(*L);
	}
	while(fgets(*str+begin,*L-begin,in)){
		begin=*L-1;  
		if(strchr(*str,'\n'))
			break;
		(*L)*=2;
		*str=(char*)realloc(*str,*L);
	}
	if(begin==0){
		free(*str);
		return NULL;
	}
	return *str;
}			

int main(void){ 
      //чтение из файла криволинейного массива, здесь нужно найти и исправить две опечатки
     FILE *in=fopen("1.txt","r");
     char *buf=NULL;//нужно заменить динамическим массивом 
     int **matrix,*data=NULL; size_t *rows=NULL,Ldata=1,Lrows=1,s=0,j=0,L=1;
//data -- одномерный массив всех чисел файла,s -- их количество, rows -- массив длин матрицы, 
//j -- количество строк, Ldata, Lrows -- размеры отведенной под data и rows памяти
     while(mygets(&buf,&L,in)){ //fgets нужно заменить на mygets   
         char *tmp=buf; int pos,k; //переменные для sscanf, которая извлечет числа из buf
         if(j+1>=Lrows){ //количество строк матрицы должно увеличиться на 1, проверяем, достаточно ди отведенной ранее памяти
             Lrows*=2; rows=realloc(rows,Lrows*sizeof(*rows)); //если нет, запрашиваем новую и переносим туда старые данные для массива rows
         }
         rows[j]=0; //теперь памяти достаточно, rows[j] должно стать количеством чисес в buf
         for(;sscanf(tmp,"%d%n",&k,&pos)==1;tmp+=pos){ //пока возможно, извлекаем из buf число, чтобы записать его в массив data
	     if(s+1>=Ldata){  // проверяем, достаточно ли отведенной для data памяти для записи числа k
        	     Ldata*=2;data=realloc(data,Ldata*sizeof(*data));
	     }
             data[s]=k;rows[j]++;s++;
	}    
	     if(sscanf(tmp,"%s",tmp)==1){//проверяем мусор в файле
		puts("err");;goto end;
	      } 
             j++; //переходим к следующей строке
     } 
     data=realloc(data, s*sizeof(*data)+j*sizeof(*matrix));//последний realloc для сокращения отведенной под data памяти + добавляем посде data место для j указателей на строки
//это и будет матрица, под которую память отведена единым куском
     for(size_t i=s-1;i+1>=1;i--)//нужно сместить элементы массива data в конец отведенной памяти
	       data[i+j*sizeof(*matrix)/sizeof(int)]=data[i];

      matrix=(int**)data;
      matrix[0]=(int *)(matrix+j); 
      for(size_t i=1;i<j;i++)
		matrix[i]=matrix[i-1]+rows[i-1];
      pr(matrix,rows,j);	
	end:  free(matrix); free(rows);fclose(in);
     puts("_________");
    
	return 0;
} 
