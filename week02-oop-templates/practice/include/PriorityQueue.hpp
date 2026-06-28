#pragma once
#include <queue>

template <typename T>
class PriorityQueue{
    public:
        PriorityQueue(){}
        void push(const T& task){
            storage_.push(task);
        }
        T pop(){
            T top = storage_.top();
            storage_.pop();
            return top;
        }

        const T& top() const{
            return storage_.top();
        }
        bool empty() const
        {
            return storage_.empty();
        }

        size_t size() const{
            return storage_.size();
        }

    private:
        std::priority_queue<T> storage_;
};