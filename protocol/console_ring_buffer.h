#ifndef RING_BUFFER_H
#define RING_BUFFER_H

/*--------------------------------------------------------------------
 * Ring buffer to store chars from keyboard
 *------------------------------------------------------------------*/

#include "lufa.h"
#define RBUF_SIZE 28

void rbuf_enqueue(uint8_t data);
uint8_t rbuf_dequeue(void);
bool rbuf_has_data(void);
void rbuf_clear(void);

#endif  /* RING_BUFFER_H */
