"""
Example of:
    multiple threads to produce resource,
    single thread to process resource

Useful:
    Write to the same file in web requests

BEAR
03/02/16
"""

from threading import Thread, Condition
from Queue import Queue
from time import sleep
import string
import random

q = Queue()
condition = Condition()

def random_string(size=6, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))

def producer(c, n):
    i = 0
    while True:
        condition.acquire()
        i += 1
        s = '%s_%03d' % (c, i)
        print('Put %s' % s)
        q.put(s)
        condition.notify()
        condition.release()
        sleep(1)

def consumer():
    while True:
        condition.acquire()
        while True:
            if not q.empty() and q.qsize() >= 5:
                break
            condition.wait(3)

        print 'Start to process ...'
        while not q.empty():
            s = q.get()
            print('--> Get %s' % s)
            q.task_done()
        condition.release()

if __name__ == '__main__':
    i = 0
    for c in string.lowercase:
        i += 1
        t1 = Thread(target=producer, args=(c, i))
        t1.daemon = True
        t1.start()

    t2 = Thread(target=consumer)
    t2.daemon = True
    t2.start()

    sleep(5)
    q.join()
