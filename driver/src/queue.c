/* queue.c --- 
 * 
 * Filename: queue.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Feb  7 19:49:26 2013 (-0500)
 * Version: 
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * URL: 
 * Doc URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 */

/* Code: */
#include "queue.h"

void init_queue(queue_t *buf) {
  buf->head = -1;
  buf->tail = -1;
}

int queue_size(queue_t *buf) {
  if (queue_empty(buf)) {
    return 0;
  }

  if (buf->tail > buf->head) {
    return QUEUE_SIZE - (buf->tail - buf->head + 1);
  } else {
    return QUEUE_SIZE - (buf->head - buf->tail);
  }
}

int enqueue (queue_t *buf, int data) {
  // Check if the queue is full.
  if (queue_size(buf) >= QUEUE_SIZE) {
    return 0;
  }

  // If head is at -1, set both pointers to 0.
  buf->head = buf->head == -1 ? 0 : buf->head;
  buf->tail = buf->tail == -1 ? 0 : buf->tail;

  buf->buffer[buf->tail] = data;

  // Move tail pointer.
  buf->tail++;
  buf->tail %= QUEUE_SIZE;
  return 1;
}

int dequeue (queue_t *buf) {
  // Check if the queue is empty.
  if (queue_empty(buf)) {
    return 0;
  }

  int ret = buf->buffer[buf->head];
  buf->head++;
  buf->head %= QUEUE_SIZE;

  // If the head and tail are at the same position, then the queue is empty so set both to -1.
  if (buf->head == buf->tail) {
    buf->head = -1;
    buf->tail = -1;
  }

  return ret;
}

int queue_empty(queue_t *buf) {
  return buf->head == -1;
}


/* queue.c ends here */
