#include <circbuf.h>
#include <stdio.h>

int main(){
CircBuf * buf;

buf =  new CircBuf(4);

buf->add('1');
buf->add('2');
buf->add('3');
buf->add('4');
buf->imprimirBuf();
printf("head: %c , tail: %c, count: %d\n",buf->getHead(),buf->getTail(),buf->getCount());
printf("\n");

buf->remove();//saco de la cabeza '1'
buf->imprimirBuf();
printf("head: %c , tail: %c, count: %d\n",buf->getHead(),buf->getTail(),buf->getCount());
printf("\n");

buf->add('5'); //agrego '5' a la cola
buf->imprimirBuf();
printf("head: %c , tail: %c, count: %d\n",buf->getHead(),buf->getTail(),buf->getCount());
printf("\n");

/*
buf->remove();buf->remove();buf->remove();buf->imprimirBuf();
printf("head: %c , tail: %c, count: %d\n",buf->getHead(),buf->getTail(),buf->getCount());
printf("\n");
buf->add('w');
buf->imprimirBuf();
printf("head: %c , tail: %c, count: %d\n",buf->getHead(),buf->getTail(),buf->getCount());
printf("\n");
*/

buf->remove(); //saco '2' de la cabeza
buf->imprimirBuf();
printf("head: %c , tail: %c, count: %d\n",buf->getHead(),buf->getTail(),buf->getCount());
printf("\n");

buf->remove(); //saco '3' de la cabeza
buf->imprimirBuf();
printf("head: %c , tail: %c, count: %d\n",buf->getHead(),buf->getTail(),buf->getCount());
printf("\n");

buf->add('6'); //agrego '6' a la cola
buf->imprimirBuf();
printf("head: %c , tail: %c, count: %d\n",buf->getHead(),buf->getTail(),buf->getCount());
printf("\n");




}


