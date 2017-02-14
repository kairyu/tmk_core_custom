#include "console_ring_buffer.h"
#include "rawhid.h"
#include "rawhid_command.h"


static uint8_t rbuf[RBUF_SIZE];
static uint8_t rbuf_head = 0;
static uint8_t rbuf_tail = 0;

void rbuf_enqueue(uint8_t data)
{
    uint8_t sreg = SREG;
    cli();
    char next = (rbuf_head + 1) % RBUF_SIZE;
    if (next != rbuf_tail) {
        rbuf[rbuf_head] = data;
        rbuf_head = next;
    } else {    //if ring buffer is full
        rbuf_clear();
        rbuf_enqueue(data);
    }
    SREG = sreg;
}

uint8_t rbuf_dequeue(void)
{
    char val = 0;

    uint8_t sreg = SREG;
    cli();
    if (rbuf_head != rbuf_tail) {
        val = rbuf[rbuf_tail];
        rbuf_tail = (rbuf_tail + 1) % RBUF_SIZE;
    }
    SREG = sreg;

    return val;
}

bool rbuf_has_data(void)
{
    uint8_t sreg = SREG;
    cli();
    bool has_data = (rbuf_head != rbuf_tail);
    SREG = sreg;
    return has_data;
}

void rbuf_clear(void)
{
    uint8_t sreg = SREG;
    cli();

    uint8_t payload_length = 0;
    uint8_t payload[RBUF_SIZE];
    while(rbuf_has_data()) {
        payload[payload_length] = rbuf_dequeue();
        payload_length++;
    }
    if(payload_length > 0)
        rawhid_send_in_data(RAWHID_COMMAND_DEBUG_PRINT, 0, payload_length, 0, payload, 0, 0);

    rbuf_head = rbuf_tail = 0;
    SREG = sreg;
}
