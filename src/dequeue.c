#include "dequeue.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#pragma region Private function declarations

static t_dequeue_node* _dequeue_node_create(t_dequeue* dequeue);

#pragma endregion

#pragma region Public function implementations

t_dequeue* dequeue_create(int element_size_in_bytes) {
    t_dequeue* dequeue;
    dequeue = malloc(sizeof(t_dequeue));
    if (dequeue == NULL) {
        return NULL;
    }

    dequeue->front = NULL;
    dequeue->back = NULL;
    dequeue->size = 0;
    dequeue->element_size_in_bytes = element_size_in_bytes;

    return dequeue;
}

int dequeue_push_back(t_dequeue* dequeue, void* element) {
    if (dequeue == NULL || element == NULL) {
        return EINVAL;
    }

    t_dequeue_node* node = _dequeue_node_create(dequeue);
    if (node == NULL) {
        return ENOMEM;
    }

    memcpy(node->element, element, dequeue->element_size_in_bytes);
    node->prev = dequeue->back;
    node->next = NULL;

    if (dequeue_is_empty(dequeue)) {
        dequeue->front = node;
    } else {
        dequeue->back->next = node;
    }
    dequeue->back = node;
    dequeue->size++;

    return 0;
}

int dequeue_push_front(t_dequeue* dequeue, void* element) {
    if (dequeue == NULL || element == NULL) {
        return EINVAL;
    }

    t_dequeue_node* node = _dequeue_node_create(dequeue);
    if (node == NULL) {
        return ENOMEM;
    }

    memcpy(node->element, element, dequeue->element_size_in_bytes);
    node->prev = NULL;
    node->next = dequeue->front;

    if (dequeue_is_empty(dequeue)) {
        dequeue->back = node;
    } else {
        dequeue->front->prev = node;
    }
    dequeue->front = node;
    dequeue->size++;

    return 0;
}

void* dequeue_pop_back(t_dequeue* dequeue) {
    if (dequeue == NULL || dequeue_is_empty(dequeue)) {
        return NULL;
    }

    t_dequeue_node* node = dequeue->back;

    dequeue->back = node->prev;
    if (dequeue->back == NULL) {
        dequeue->front = NULL;
    } else {
        dequeue->back->next = NULL;
    }
    dequeue->size--;

    void* element = node->element;
    free(node);

    return element;
}

void* dequeue_pop_front(t_dequeue* dequeue) {
    if (dequeue == NULL || dequeue_is_empty(dequeue)) {
        return NULL;
    }

    t_dequeue_node* node = dequeue->front;

    dequeue->front = node->next;
    if (dequeue->front == NULL) {
        dequeue->back = NULL;
    } else {
        dequeue->front->prev = NULL;
    }
    dequeue->size--;

    void* element = node->element;
    free(node);

    return element;
}

void* dequeue_peek_back(t_dequeue* dequeue) {
    if (dequeue == NULL || dequeue_is_empty(dequeue)) {
        return NULL;
    }

    return dequeue->back->element;
}

void* dequeue_peek_front(t_dequeue* dequeue) {
    if (dequeue == NULL || dequeue_is_empty(dequeue)) {
        return NULL;
    }

    return dequeue->front->element;
}

size_t dequeue_get_size(t_dequeue* dequeue) {
    return dequeue->size;
}

bool dequeue_is_empty(t_dequeue* dequeue) {
    return dequeue_get_size(dequeue) == 0 ? true : false;
}

t_dequeue* dequeue_clone(t_dequeue* dequeue) {
    if (dequeue == NULL) {
        return NULL;
    }

    t_dequeue* cloned_dequeue = dequeue_create(dequeue->element_size_in_bytes);
    if (cloned_dequeue == NULL) {
        return NULL;
    }

    t_dequeue_node* node = dequeue->front;
    while (node != NULL) {
        dequeue_push_back(cloned_dequeue, node->element);
        node = node->next;
    }

    return cloned_dequeue;
}

int dequeue_clear(t_dequeue* dequeue) {
    if (dequeue == NULL) {
        return EINVAL;
    }

    void* element = dequeue_pop_back(dequeue);
    while (element != NULL) {
        free(element);
        element = dequeue_pop_back(dequeue);
    }

    return 0;
}

int dequeue_destroy(t_dequeue** dequeue) {
    if (dequeue == NULL || *dequeue == NULL) {
        return EINVAL;
    }

    int error_code = dequeue_clear(*dequeue);
    if (error_code != 0) {
        return error_code;
    }

    free(*dequeue);
    *dequeue = NULL;

    return 0;
}

#pragma endregion

#pragma region Private function implementations

/**
 * Creates and initializes a new node for the given dequeue.
 * @param dequeue The dequeue structure that the node belongs to.
 * @return A pointer to the new dequeue node on success; otherwise, NULL.
 */
static t_dequeue_node* _dequeue_node_create(t_dequeue* dequeue) {
    if (dequeue == NULL) {
        return NULL;
    }

    t_dequeue_node* node;
    node = malloc(sizeof(t_dequeue_node));
    if (node == NULL) {
        return NULL;
    }

    node->prev = NULL;
    node->next = NULL;
    node->element = malloc(dequeue->element_size_in_bytes);
    if (node->element == NULL) {
        free(node);
        return NULL;
    }

    return node;
}

#pragma endregion