#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char *reverseWords(char *str){
	char **str2;
	str2 = (char**)malloc(50*sizeof(char*));
	int i;
	for(i=0;i<50;i++) *(str2+i) = (char*)malloc(50*sizeof(char));
	
	int row = 0,col=0, count = 0;
	
	while(str[count]!='\0'){
		if(str[count]==' '){
			str2[row][col] = '\0';
			count++;
			row++;
			col=0;
		}
		str2[row][col]=str[count];
		col++;
		count++;
	}
	str2[row][col] = '\0';
	str2[row + 1] = NULL;
	
	count=0;
	
	char *conv_str = (char*)malloc(50 * sizeof(char));
    conv_str[0] = '\0'; 
	for(i=row;i>=0;i--){
		col=0;
		while(str2[i][col]!='\0'){
			conv_str[count]=str2[i][col];
			col++;
			count++;
		}
		conv_str[count]=' ';
		count++;
	}
	
	conv_str[count-1]='\0';
	return conv_str;
}

int main(){
	char str[] = "The quick brown fox jumps over the lazy dog!";
	printf("%s\n",str);
	char *rever_words = reverseWords(str);
	printf("%s\n",rever_words);
}
