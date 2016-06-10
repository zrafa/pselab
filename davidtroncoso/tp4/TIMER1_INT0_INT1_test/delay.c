/**********************************************************************
 *
 * Function:    delay()
 *
 * Description: Busy-wait for the requested number of milliseconds.
 *
 * Notes:       The number of decrement-and-test cycles per millisecond
 *              was determined through trial and error.  This value is
 *              dependent upon the processor type and speed.
 *
 * Returns:     None defined.
 *
 **********************************************************************/
void 
delay(unsigned int nMilliseconds)
{
    volatile unsigned int nCycles1;
    volatile unsigned int nCycles2;

	nCycles1 = nMilliseconds;
    while (nCycles1--)
	{
		nCycles2 = 1200;
		while (nCycles2--);
	}


}   /* delay() */

