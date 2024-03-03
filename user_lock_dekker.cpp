#include "user_locks.hpp"
using namespace std;

user_lock_dekker::user_lock_dekker()
    : user_lock() {
    m_flag[0] = m_flag[1] = false;
    m_turn = false; // 0 1
}

void user_lock_dekker::lock(int thread_id) {
    // TODO: Implement the lock acquire part of the Dekker algorithm here
    int other = (thread_id + 1) % 2;
    std::atomic_store(&m_flag[thread_id], true);

    while (std::atomic_load(&m_flag[other]) == true) {
        if (std::atomic_load(&m_turn) != thread_id) {
            std::atomic_store(&m_flag[thread_id], false);
            while (std::atomic_load(&m_turn) != thread_id) {
            }
            std::atomic_store(&m_flag[thread_id], true);
        }
    }
    std::atomic_store(&m_turn, thread_id);

    //(void)thread_id; // TODO: Delete this line
}

void user_lock_dekker::unlock(int thread_id) {
    // TODO: Implement the lock release part of the Dekker algorithm here
    int other = (thread_id + 1) % 2;
    std::atomic_store(&m_turn, other);
    std::atomic_store(&m_flag[thread_id], false);
    //(void)thread_id; // TODO: Delete this line
}
