/**********************************************************************
 *
 * Filename:    serial.cpp
 * 
 * Description: Implementation of the SerialPort class.
 *
 * Notes:       
 *
 * 
 * Copyright (c) 1998 by Michael Barr.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#include <scc.h>
#include <serial.h>

static SCC  scc;

/**********************************************************************
 * 
 * Method:      SerialPort()
 *
 * Description: Default constructor for the serial port class.
 *
 * Notes:    
 *
 * Returns:     None defined.
 *
 **********************************************************************/
SerialPort::SerialPort(int            port,
                       unsigned long  baudRate,
                       unsigned int   txQueueSize,
                       unsigned int   rxQueueSize)
{
    //
    // Initialize the logical device.
    //
    switch (port)
    {
      case UART0:
        channel = 0;
        break;

      default:
        channel = -1;
        break;
    }

    //
    // Create input and output FIFO's.
    //
    pTxQueue = new CircBuf(txQueueSize);
    pRxQueue = new CircBuf(rxQueueSize);

    // 
    // Initialize the hardware device.
    // 
    scc.reset(channel);
    scc.init(channel, baudRate, pTxQueue, pRxQueue);

}   /* SerialPort() */


/**********************************************************************
 *
 * Function:    ~SerialPort()
 * 
 * Description: Destroy a serial port.
 *
 * Notes:       
 *
 * Returns:     None defined.
 *
 **********************************************************************/
SerialPort::~SerialPort(void)
{
    //
    // Reset the hardware.
    //
//    scc.reset(channel);

    //
    // Free the input and output FIFO's.
    //
    delete pTxQueue;
    delete pRxQueue;

}   /* ~SerialPort() */


/**********************************************************************
 * 
 * Method:      putchar()
 *
 * Description: Write one character to the serial port.
 *
 * Notes:
 *
 * Returns:     The transmitted character is returned on success.  
 *              -1 is returned in the case of an error.
 *
 **********************************************************************/
int
SerialPort::putchar(int c)
{
    if (pTxQueue->isFull())
    {
        return (-1);
    }

    //
    // Add the character to the transmit FIFO.
    //
    pTxQueue->add((char) c);
	if (c == '\n')
    	pTxQueue->add('\r');

    //
    // Start the transmit engine (if it's stalled).
    //
    scc.txStart(channel);

    return (c);

}   /* putchar() */


/**********************************************************************
 * 
 * Method:      puts()
 *
 * Description: Copies the null-terminated string s to the serial
 *              port and appends a newline character.
 *
 * Notes:       In rare cases, this function may return success though
 *              the newline was not actually sent.
 *
 * Returns:     The number of characters transmitted successfully.
 *              Otherwise, -1 is returned to indicate error.
 *
 **********************************************************************/
int
SerialPort::puts(const char * s)
{
    const char *  p;

	//
	// Send each character of the string.
	//
    for (p = s; *p != '\0'; p++)
    {
        if (putchar(*p) < 0) break;
    }

    //
    // Add a newline character.
    //
	//putchar('\r');//antes estaba /n

    return ((p - s) + 1);

}   /* puts() */


/**********************************************************************
 * 
 * Method:      getchar()
 *
 * Description: Read one character from the serial port.
 *
 * Notes:
 *
 * Returns:     The next character found on this input stream.
 *              -1 is returned in the case of an error.
 *
 **********************************************************************/
int
SerialPort::getcharr(void) //rr
{
    int  c;



    //
    // If the receive engine is stalled, restart it.
    //
    if (! pRxQueue->isFull())
    {
        scc.rxStart(channel);
    }

   else if (pRxQueue->isEmpty())
    {
        return (-1);               // There is no input data available.
    }

    //
    // Read the next byte out of the receive FIFO.
    //
    c = pRxQueue->remove();

    return (c);

}   /* getchar() */


/**********************************************************************
 * 
 * Method:      gets()
 *
 * Description: Collects a string of characters terminated by a new-
 *              line character from the serial port and places it in s.  
 *              The new-line character is replaced by a null character.
 *
 * Notes:       The caller is responsible for allocating space for the
 *              string.
 *
 * Warnings:    This function does not block waiting for a newline.  
 *              It will return whatever it finds in the receive queue.
 *
 * Returns:     A pointer to the string.
 *              Otherwise, NULL is returned to indicate an error.
 *
 **********************************************************************/
char *
SerialPort::gets(char * s)
{
    char *  p;
    int     c;

	//
	// Read characters until a newline is found or no more data.
	//
    for (p = s; (c = getcharr()) != '\n' && c >= 0; p++) //rr
    {
        *p = c;  
    }

	//
	// Terminating the string.
	//
    *p = '\0';

    return (s);

}   /* gets() */

//**********************************************************************
void
SerialPort::desactivarSerial(void){
	scc.desactivarUART();
}

void
SerialPort::activarSerial(void){
	scc.activarUART();
}
