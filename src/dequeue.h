#ifndef DEQUEUE_H
#define DEQUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct s_dequeue_node {
    void* element;
    struct s_dequeue_node* prev;
    struct s_dequeue_node* next;
} t_dequeue_node;

typedef struct s_dequeue {
    size_t size;
    int element_size_in_bytes;
    struct s_dequeue_node* front;
    struct s_dequeue_node* back;
} t_dequeue;

/**
 * Creates a new generic dequeue.
 * All dequeue elements are of the same size.
 * When you no longer need the dequeue, dequeue_destroy should be called to deallocate the memory.
 * @param element_size_in_bytes Size of the dequeue element in bytes.
 * @return A pointer to the created dequeue on success; otherwise, NULL.
 */
t_dequeue* dequeue_create(int element_size_in_bytes);

/**
 * Adds an element at the back of the given dequeue.
 * @param dequeue A pointer to the dequeue to push the element to.
 * @param element A pointer to the element to push to the dequeue.
 * @retval 0 if successful;
 * @retval EINVAL if one of the given pointers is NULL;
 * @retval ENOMEM if the function fails to allocate memory for the new element.
 */
int dequeue_push_back(t_dequeue* dequeue, void* element);

/**
 * Adds an element at the front of the given dequeue.
 * @param dequeue A pointer to the dequeue to push the element to.
 * @param element A pointer to the element to push to the dequeue.
 * @retval 0 on success;
 * @retval EINVAL if one of the given pointers is NULL;
 * @retval ENOMEM if the function fails to allocate memory for the new element.
 */
int dequeue_push_front(t_dequeue* dequeue, void* element);

/**
 * Removes an element at the back of the given dequeue.
 * @param dequeue A pointer to the dequeue to pop the element from.
 * @return A pointer to the popped element on success; otherwise, NULL.
 * @note The caller is responsible for freeing the returned pointer after it is no longer needed.
 */
void* dequeue_pop_back(t_dequeue* dequeue);

/**
 * Removes an element at the front of the given dequeue.
 * @param dequeue A pointer to the dequeue to pop the element from.
 * @return A pointer to the popped element on success; otherwise, NULL.
 * @note The caller is responsible for freeing the returned pointer after it is no longer needed.
 */
void* dequeue_pop_front(t_dequeue* dequeue);

/**
 * Returns a pointer to the element at the back of the given dequeue without removing it.
 * @param dequeue A pointer to the dequeue to peek from.
 * @return A pointer to the element on success; otherwise, NULL;
 */
void* dequeue_peek_back(t_dequeue* dequeue);

/**
 * Returns a pointer to the element at the front of the given dequeue without removing it.
 * @param dequeue A pointer to the dequeue to peek from.
 * @return A pointer to the element on success; otherwise, NULL;
 */
void* dequeue_peek_front(t_dequeue* dequeue);

/**
 * Gets the number of elements in the dequeue.
 * @param dequeue A pointer to the dequeue to get the size of. Must be not NULL.
 * @return The number of elements in the dequeue.
 */
size_t dequeue_get_size(t_dequeue* dequeue);

/**
 * Checks whether the given dequeue is empty.
 * @param dequeue A pointer to the dequeue to check. Must be not NULL.
 * @return True if the dequeue is empty; otherwise, false.
 */
bool dequeue_is_empty(t_dequeue* dequeue);

/**
 * Creates a new dequeue with the same elements as the given dequeue.
 * @param dequeue A pointer to the dequeue to clone.
 * @return A pointer to the cloned dequeue on success; otherwise, NULL.
 */
t_dequeue* dequeue_clone(t_dequeue* dequeue);

/**
 * Removes all elements from the dequeue and frees the allocated memory.
 * @param dequeue A pointer to the dequeue to be cleared.
 * @retval 0 on success;
 * @retval EINVAL if a NULL dequeue pointer is given.
 */
int dequeue_clear(t_dequeue* dequeue);

/**
 * Frees the memory of the given dequeue and sets its pointer to NULL.
 * @param dequeue Pointer to the dequeue to be destroyed.
 * @retval 0 on success;
 * @retval EINVAL if a NULL dequeue pointer is given.
 */
int dequeue_destroy(t_dequeue** dequeue);

#endif
