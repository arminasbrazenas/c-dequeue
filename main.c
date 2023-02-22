#include "src/dequeue.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

typedef struct s_person {
    int age;
    char name[32];
} t_person;

int main() {
    t_person* person = NULL;
    t_person people[] = {
    { 21, "Alice Johnson" },
    { 35, "Bob Smith" },
    { 18, "Charlie Brown" },
    { 27, "David Wilson" },
    { 42, "Eve Hernandez" }
    };
    const size_t PEOPLE_CAPACITY = sizeof(people) / sizeof(people[0]);

    // Test constructor
    t_dequeue* dequeue = dequeue_create(sizeof(t_person));
    assert(dequeue != NULL);
    assert(dequeue_is_empty(dequeue));

    // Test push back with peek
    for (int i = 0; i < PEOPLE_CAPACITY; ++i) {
        dequeue_push_back(dequeue, &people[i]);
        person = dequeue_peek_back(dequeue);
        assert(person->age == people[i].age && strcmp(person->name, people[i].name) == 0);
    }

    // Test pop back
    person = dequeue_pop_back(dequeue);
    free(person);

    // Test size
    size_t size = dequeue_get_size(dequeue);
    assert(size == PEOPLE_CAPACITY - 1);

    // Test clone
    t_dequeue* cloned_dequeue = dequeue_clone(dequeue);
    for (size_t i = 0; i < size; ++i) {
        person = dequeue_pop_back(dequeue);
        t_person* cloned_person = dequeue_pop_back(cloned_dequeue);
        assert(person->age == cloned_person->age && strcmp(person->name, cloned_person->name) == 0);

        free(person);
        free(cloned_person);
    }

    assert(dequeue_is_empty(dequeue) && dequeue_get_size(dequeue) == dequeue_get_size(cloned_dequeue));
    assert(dequeue_destroy(&cloned_dequeue) == 0 && cloned_dequeue == NULL);

    // Test push front with peek
    for (int i = PEOPLE_CAPACITY - 1; i >= 0; --i) {
        dequeue_push_front(dequeue, &people[i]);
        person = dequeue_peek_front(dequeue);
        assert(person->age == people[i].age && strcmp(person->name, people[i].name) == 0);
    }

    // Test pop front
    person = dequeue_pop_front(dequeue);
    free(person);

    person = dequeue_peek_front(dequeue);
    assert(person->age == people[1].age && strcmp(person->name, people[1].name) == 0);

    // Test clear
    dequeue_clear(dequeue);
    assert(dequeue != NULL && dequeue_get_size(dequeue) == 0);

    // Test destructor
    assert(dequeue_destroy(&dequeue) == 0 && dequeue == NULL);

    // Test null pointers
    assert(dequeue_push_back(NULL, NULL) == EINVAL);
    assert(dequeue_push_front(NULL, NULL) == EINVAL);
    assert(dequeue_pop_back(NULL) == NULL);
    assert(dequeue_pop_front(NULL) == NULL);
    assert(dequeue_peek_back(NULL) == NULL);
    assert(dequeue_peek_front(NULL) == NULL);
    assert(dequeue_clone(NULL) == NULL);
    assert(dequeue_clear(NULL) == EINVAL);
    assert(dequeue_destroy(NULL) == EINVAL);

    return EXIT_SUCCESS;
}
