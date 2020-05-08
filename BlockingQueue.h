#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

//-----------------------------------------------------------------------------
#include <queue>
#include <mutex>
#include <condition_variable>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#define QUEUE_CLOSED 0;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

template <class T> class BlockingQueue {
    private:
        std::mutex m;
        std::queue<T> queue;
        std::condition_variable cv;
        bool permanently_closed;

    public:
        BlockingQueue() : permanently_closed(false) {}
        BlockingQueue(const BlockingQueue&) = delete;
        BlockingQueue& operator=(const BlockingQueue&) = delete;

        void push(T t) {
            std::unique_lock<std::mutex> l(m);
            queue.push(t);
            cv.notify_all();
        }

        T pop() {
            std::unique_lock<std::mutex> l(m);
            while (queue.empty()) {
                if (permanently_closed) {
                    return QUEUE_CLOSED;
                }

                cv.wait(l);
            }

            T t = queue.front();
            queue.pop();
            return t;
        }

        void close() {
            std::unique_lock<std::mutex> l(m);
            permanently_closed = true;
            cv.notify_all();
        }

        ~BlockingQueue() {}
};

//-----------------------------------------------------------------------------
#endif // __BLOCKING_QUEUE_H__
