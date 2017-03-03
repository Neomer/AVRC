#ifndef QUEUE_H
#define QUEUE_H

#include <inttypes.h>

#define QUEUE(size) \
	struct { \
		uint8_t data[size]; \
		uint8_t read_idx; \
		uint8_t write_idx; \
	}

#define QUEUE_SIZE(queue)				(sizeof(queue.data) / sizeof(queue.data[0]))
#define QUEUE_COUNT(queue)				(queue.write_idx > queue.read_idx)?(queue.write_idx - queue.read_idx):(QUEUE_SIZE(queue) - queue.read_idx + queue.write_idx)
#define QUEUE_ISFULL(queue)				(QUEUE_SIZE(queue) == queue.head_idx)
#define QUEUE_ADD(queue, value)			queue.data[queue.write_idx++] = value; if (QUEUE_SIZE(queue) == queue.write_idx) queue.write_idx = 0;
#define QUEUE_GET(queue)				queue.data[queue.read_idx++]; if (QUEUE_SIZE(queue) == queue.read_idx) queue.read_idx = 0
//#define QUEUE_EQUALS(queue, value)	bool fl=true; int idx=0; while ((*(value+idx)&&(fl)){fl=*(b+idx)==queue.data[idx];idx++}
	

#endif // QUEUE_H
