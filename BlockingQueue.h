#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

//-----------------------------------------------------------------------------
#include <queue>
#include <mutex>
#include <condition_variable>

#include "Exception.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

template <class T> class BlockingQueue {
    private:
        std::mutex m;
        std::queue<T> queue;
        std::condition_variable cv;
        bool permanentlyClosed;

    public:
        BlockingQueue() : permanentlyClosed(false) {}
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
                if (permanentlyClosed) {
                    throw(Exception(QUEUE_CLOSED, "Cola vacía y cerrada."));
                }
            
                cv.wait(l);
            }

            T t = queue.front();
            queue.pop();
            return t;
        }

        void close() {
            std::unique_lock<std::mutex> l(m);
            permanentlyClosed = true;
            cv.notify_all();
        }

        ~BlockingQueue() {}
};

//-----------------------------------------------------------------------------
#endif // __BLOCKING_QUEUE_H__
