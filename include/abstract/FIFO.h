#ifndef FIFO_H
#define FIFO_H

#define FIFO(size)	struct { uint8_t data[size]; uint8_t read_idx; }
#define FIFO_PUSH(fifo, value)	fifo.data[fifo.read_idx++] = value
#define FIFO_POP(fifo)			fifo.data[fifo.read_idx--]
#define FIFO_IS_EMPTY(fifo)		fifo.read_idx == 0


#endif // FIFO_H
