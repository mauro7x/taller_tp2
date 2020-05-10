#ifndef __RESOURCE_QUEUE_H__
#define __RESOURCE_QUEUE_H__

//-----------------------------------------------------------------------------
#include <queue>
#include <mutex>
#include <condition_variable>

#include "Resources.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#define QUEUE_CLOSED INVALID;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class ResourceQueue {
    private:
        std::mutex m;
        std::queue<Resource> queue;
        std::condition_variable cv;
        bool permanently_closed;

    public:
        ResourceQueue();
        ResourceQueue(const ResourceQueue&) = delete;
        ResourceQueue& operator=(const ResourceQueue&) = delete;
        
        void push(Resource resource);
        Resource pop();
        void close();

        ~ResourceQueue();
};

//-----------------------------------------------------------------------------
#endif // __RESOURCE_QUEUE_H__
