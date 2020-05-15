#include "ResourceQueue.h"

//-----------------------------------------------------------------------------
#include <queue>
#include <mutex>
#include <condition_variable>

#include "Resources.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// API Pública

ResourceQueue::ResourceQueue() : permanently_closed(false) {}


void ResourceQueue::push(Resource resource) {
    std::unique_lock<std::mutex> l(m);
    queue.push(resource);
    cv.notify_all();
}


Resource ResourceQueue::pop() {
    std::unique_lock<std::mutex> l(m);
    while (queue.empty()) {
        if (permanently_closed) {
            return QUEUE_CLOSED;
        }

        cv.wait(l);
    }

    Resource resource = queue.front();
    queue.pop();
    return resource;
}


void ResourceQueue::close() {
    std::unique_lock<std::mutex> l(m);
    permanently_closed = true;
    cv.notify_all();
}


ResourceQueue::~ResourceQueue() {}

//-----------------------------------------------------------------------------
