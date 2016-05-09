#include <circbuf.h>
#include <stdio.h>

int main(){
CircBuf * buf;


char entrada=0;
char str[10]={};
printf("Ingrese la longitud del buffer\n");
while(str[0]==0)
	scanf("%s",str);
entrada=10*(str[0]-0x30)+(str[1]-0x30);	

buf =  new CircBuf(entrada);
entrada=0;
while(1)
{
	while(entrada==0)
		scanf("%c",&entrada);
	if(entrada!='\n')
	{
		if(entrada=='=')
		{
			buf->remove();
			buf->imprimirBuf();
			printf("head: %c , tail: %c, count: %d\n",buf->getHead(),buf->getTail(),buf->getCount());
			printf("\n");
			entrada=0;
		}
		else
		{
			buf->add(entrada);
			buf->imprimirBuf();
			printf("head: %c , tail: %c, count: %d\n",buf->getHead(),buf->getTail(),buf->getCount());
			printf("\n");
			entrada=0;
		}
	}
	else
	{
		entrada=0;
	}
}

}


