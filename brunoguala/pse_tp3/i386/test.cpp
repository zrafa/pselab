#include <stdio.h>
#include "circbuf.cpp"
#include "circbuf.h"
#include <unistd.h>
//debemos incluir serial.cpp ya que es quien interactua con scc
#include "serial.cpp"

void menu ();

int main (){
	
	int fin=1;
	int opcion=0;
	item i=' ';
	item l=' ';
	CircBuf *buffer_circular=NULL;
	 int k=0;
	
	while(fin){

		menu();
		printf("\nIngrese una opcion \n");
		scanf("%d", &opcion);

		switch (opcion){
			//en c++ el case necesita hacer referencia a un bloque
			case 0 :{ 
					 int longitud=0;
					 printf("\nIngrese la longitud de buffer circular\n");
					 scanf("%u", &longitud); //con %u guardamos en una variable un numero entero sin signo
					 buffer_circular=new CircBuf(longitud);
					 break;
					}

			case 1 :{ 
					 printf("\nIngrese un caracter \n");
					 //while(i == ' ')
					 scanf("%s", &i);
					 //gets(&i); deprecada
					 printf("Caracter Ingresado : %c", i);
					 (buffer_circular)->add(i);
					 break;
					}

			case 2 :{
					 l=(*buffer_circular).remove();
					 (l != ' ') ? printf("\nSe elimino el item : %u ", l) : printf("\nNo existen items para eliminar en el buffer circular : ");

					 if(l == ' ')
						(*buffer_circular).display_sin_htc();

					 break;
					}

			case 3 :{
					 if((*buffer_circular).isEmpty()){
						printf("\nLa estructura buffer circular se encuentra vacia : ");
						(*buffer_circular).display_sin_htc();
					 }else{
						printf("\nLa estructura buffer circular no esta vacia, posee los siguientes items : ");
						(*buffer_circular).display_sin_htc();
					 }

					 break;
					}

			case 4 :{
					 if((*buffer_circular).isFull()){
						printf("\nLa estructura buffer circular se encuentra completa : ");
						(*buffer_circular).display_sin_htc();
					 }else{
						printf("\nLa estructura buffer circular no esta completa, posee los siguientes items : ");
						(*buffer_circular).display_sin_htc();
					 }

					 break;
					}

			case 5 :{
					 (*buffer_circular).display_buffer();
					 break;
					}

			case 6 :{
					 printf("\nIniciando proceso de limpieza de memoria ....\n");
					 sleep(2);
					 printf("Liberando espacio ocupado por la estructura array ....\n");
					 sleep(2);
					 printf("Ok ....\n\n");
					 sleep(1);

					 delete buffer_circular;
					 fin=0;
					 break;
					}

			case 7 :{
					 printf("\nIngrese la longitud de ambos buffers circulares\n");
					// printf("k : %u ", *k); 
					 scanf("%d",&k);
					 //n=getchar();
					 //m=getchar();
					 //printf("%u", k);
					 //scanf("%u", &n);
					 
					 //SerialPort *serial=new SerialPort(0, 9600L, k, k);
					 printf("Pasamos la definicion del serial");
					 item c=' ';
					 while(1){
						printf("LLegamos hasta getchar");
						//c=(*serial).getchar(); //usamos flecha con puntero
						printf("%s", c);
							//(*serial).putchar(c); //llama a 
						
												
					 }//sex code, max va cua-ro. Psicologia.El camino del guerrero pacifico. Ligar es facil si sabes como.
					 
					}

			default : printf("\n  Opcion Incorrecta ");
					  break;

		}

	}

	return 0;
}

void menu (){
	printf("\n\n");
	printf("*********************\n");
	printf("*        MENU       *\n");
	printf("*********************\n");
	printf("*    0) CREATE      *\n");
	printf("*    1) ADD         *\n");
	printf("*    2) REMOVE      *\n");
	printf("*    3) IS_EMPTY    *\n");
	printf("*    4) IS_FULL     *\n");
	printf("*    5) DISPLAY     *\n");
	printf("*    6) GET OUT     *\n");
	printf("*    7) DRIVER      *\n");
	printf("*********************\n");
}


