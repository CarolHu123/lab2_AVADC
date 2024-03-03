
void user_lock_dekker::lock(int thread_id) {
    // TODO: Implement the lock acquire part of the Dekker algorithm here
    int other = (thread_id + 1) % 2;
    std::atomic_store(&m_flag[thread_id], true);
    while (std::atomic_load(&m_flag[other]) == true) {
        if (std::atomic_load(&m_turn) != other) {
            std::atomic_store(&m_flag[thread_id], false);
            while (std::atomic_load(&m_turn) != other) {
            }
            std::atomic_store(&m_flag[thread_id], true);
        }
    }

    //(void)thread_id; // TODO: Delete this line
}

void user_lock_dekker::unlock(int thread_id) {
    // TODO: Implement the lock release part of the Dekker algorithm here
    int other = (thread_id + 1) % 2;
    std::atomic_store(&m_turn, other);
    std::atomic_store(&m_flag[thread_id], false);
    //(void)thread_id; // TODO: Delete this line
}
