//header file for a thread-safe queue
#include <mutex>
#include <thread>
#include <queue>
#include <iostream>
#include <condition_variable>

//for the empty condition
struct empty_queue: std::exception{
    const char* what() const throw();
};

template <class T, class Container = std::deque<T>>
class ThreadSafeQueue{
private:
    mutable std::mutex mut;
    std::queue<T> q;
    std::condition_variable cV;
public:
    ThreadSafeQueue(){
        //blank, just make the members
    }
    
    ThreadSafeQueue(const ThreadSafeQueue& tsq){
        // I don't have to lock my lock because this is a constructor,
        //so no one else will try to access my data while I'm doing this
        std::lock_guard<std::mutex> lk(mut);
        for (T t : tsq.q){
            this->q.push(t);
        }
    }
    //no copy assignment allowed
    ThreadSafeQueue& operator=(const ThreadSafeQueue& tsq) = delete;

    //move assignment is allowed
    ThreadSafeQueue& operator=(ThreadSafeQueue&& tsq){
        //mutex doesn't have any copy/move operator, so we just use a new one
        tsq.mut.lock();
        this->q = std::move(tsq.q);
        this->cV = std::move(tsq.cV);
        //everything else is taken care of by the queue managing itself
        tsq.mut.unlock();
    }
    //push onto the q and signal
    void push(T t){
        std::lock_guard<std::mutex> lk(mut);
        q.push(t);
        cV.notify_one();
    }
    //returns immediately, stores the value in the reference variable,
    //can use return value for status
    bool try_pop(T& t){
        if (mut.try_lock()){
        if (q.empty()) return false;
        t = q.front();
        q.pop();
        mut.unlock();
        return true;
        }

        return false;
    }

    //can't store in return value, but can return nullptr to indicate empty
    std::shared_ptr<T> try_pop(){
        if (mut.try_lock()){
        if (q.empty()) return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(q.front()));
        q.pop();
        mut.unlock();
        return res;
        }
        return nullptr;
    }

    void wait_and_pop(T& t){
        std::unique_lock<std::mutex> lk(mut);
        cV.wait(lk, [this]{
            return !q.empty();
        });
        t = q.front();
        q.pop();
    }

    std::shared_ptr<T> wait_and_pop(){
        std::lock_guard<std::mutex> lk(mut);
        cV.wait(lk, [this]{
            return !q.empty();
        });
        std::shared_ptr<T> ptr = &(q.front());
        q.pop();
        return ptr;
    }
    

    bool empty() const{
        std::lock_guard<std::mutex> lk(mut);
        return q.empty();
    }

    size_t size() const{
        std::lock_guard<std::mutex> lk(mut);
        return q.size();
    }
   
};