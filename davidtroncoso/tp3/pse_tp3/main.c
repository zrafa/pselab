#include <stdio.h>
#include "circbuf.h"

main()
{
	CircBuf ma(5);
	ma.add('1');
	ma.add('2');
	ma.add('3');
	ma.add('4');
	ma.add('5');
	ma.add('7');
ma.remove();
ma.remove();
ma.remove();
ma.remove();
ma.remove();
ma.add('6');
printf("%c\n",ma.remove());
}