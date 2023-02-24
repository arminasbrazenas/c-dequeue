#include "src/dequeue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define CAPACITY        10
#define MAX_STR_LENGTH  32

void dequeue_test_constructor_destructor();
void dequeue_test_get_size();
void dequeue_test_push_back();
void dequeue_test_pop_back();
void dequeue_test_push_front();
void dequeue_test_pop_front();
void dequeue_test_clear();
void dequeue_test_clone();
void dequeue_test_invalid_arguments();

int main() {
    time_t seed = time(NULL);
    srand(time(NULL));
    printf("Test seed: %ld\n\n", seed);

    dequeue_test_constructor_destructor();
    dequeue_test_get_size();
    dequeue_test_push_back();
    dequeue_test_pop_back();
    dequeue_test_push_front();
    dequeue_test_pop_front();
    dequeue_test_clear();
    dequeue_test_clone();
    dequeue_test_invalid_arguments();

    printf("\nAll tests passed successfully.\n");

    return EXIT_SUCCESS;
}

typedef struct s_person {
    int age;
    char name[MAX_STR_LENGTH];
} t_person;

t_person* get_people() {
    t_person* people = malloc(sizeof(t_person) * CAPACITY);

    for (int i = 0; i < CAPACITY; ++i) {
        people[i].age = rand();
        int name_length = rand() % (MAX_STR_LENGTH - 1);
        memset(people[i].name, '\0', MAX_STR_LENGTH);
        for (int j = 0; j < name_length; ++j) {
            people[i].name[j] = rand() % 26 + 'a';
        }
    }

    return people;
}

void dequeue_test_constructor_destructor() {
    printf("Testing constructor and destructor...\n");

    t_dequeue* dequeue = dequeue_create(sizeof(t_person));
    assert(dequeue != NULL);

    dequeue_dispose(&dequeue);
    assert(dequeue == NULL);
}

void dequeue_test_get_size() {
    printf("Testing size getter...\n");

    t_person* people = get_people();
    t_dequeue* dequeue = dequeue_create(sizeof(t_person));

    assert(dequeue_is_empty(dequeue) == true);
    assert(dequeue_get_size(dequeue) == 0);

    for (int i = 0; i < CAPACITY; ++i) {
        dequeue_push_front(dequeue, &people[i]);
    }

    assert(dequeue_is_empty(dequeue) == false);
    assert(dequeue_get_size(dequeue) == CAPACITY);

    free(people);
    dequeue_dispose(&dequeue);
}

void dequeue_test_push_back() {
    printf("Testing push back...\n");

    t_person* people = get_people();
    t_dequeue* dequeue = dequeue_create(sizeof(t_person));

    for (int i = 0; i < CAPACITY; ++i) {
        dequeue_push_back(dequeue, &people[i]);
        t_person* person = dequeue_peek_back(dequeue);
        assert(person->age == people[i].age && strcmp(person->name, people[i].name) == 0);
    }

    free(people);
    dequeue_dispose(&dequeue);
}

void dequeue_test_pop_back() {
    printf("Testing pop back...\n");

    t_person* people = get_people();
    t_dequeue* dequeue = dequeue_create(sizeof(t_person));

    for (int i = 0; i < CAPACITY; ++i) {
        dequeue_push_back(dequeue, &people[i]);
    }

    for (int i = CAPACITY - 1; i >= 0; --i) {
        t_person* person = dequeue_pop_back(dequeue);
        assert(person->age == people[i].age && strcmp(person->name, people[i].name) == 0);
        free(person);
    }

    free(people);
    dequeue_dispose(&dequeue);
}

void dequeue_test_push_front() {
    printf("Testing push front...\n");

    t_person* people = get_people();
    t_dequeue* dequeue = dequeue_create(sizeof(t_person));

    for (int i = 0; i < CAPACITY; ++i) {
        dequeue_push_front(dequeue, &people[i]);
        t_person* person = dequeue_peek_front(dequeue);
        assert(person->age == people[i].age && strcmp(person->name, people[i].name) == 0);
    }

    free(people);
    dequeue_dispose(&dequeue);
}

void dequeue_test_pop_front() {
    printf("Testing pop front...\n");

    t_person* people = get_people();
    t_dequeue* dequeue = dequeue_create(sizeof(t_person));

    for (int i = 0; i < CAPACITY; ++i) {
        dequeue_push_front(dequeue, &people[i]);
    }

    for (int i = CAPACITY - 1; i >= 0; --i) {
        t_person* person = dequeue_pop_front(dequeue);
        assert(person->age == people[i].age && strcmp(person->name, people[i].name) == 0);
        free(person);
    }

    free(people);
    dequeue_dispose(&dequeue);
}

void dequeue_test_clear() {
    printf("Testing clear...\n");

    t_person* people = get_people();
    t_dequeue* dequeue = dequeue_create(sizeof(t_person));

    for (int i = 0; i < CAPACITY; ++i) {
        dequeue_push_front(dequeue, &people[i]);
    }

    dequeue_clear(dequeue);
    assert(dequeue_is_empty(dequeue) == true);

    free(people);
    dequeue_dispose(&dequeue);
}

void dequeue_test_clone() {
    printf("Testing clone...\n");

    t_person* people = get_people();
    t_dequeue* dequeue = dequeue_create(sizeof(t_person));

    for (size_t i = 0; i < CAPACITY; ++i) {
        dequeue_push_back(dequeue, &people[i]);
    }
    t_dequeue* cloned_dequeue = dequeue_clone(dequeue);

    assert(dequeue_get_size(dequeue) == dequeue_get_size(cloned_dequeue));

    for (size_t i = 0; i < CAPACITY; ++i) {
        t_person* person = dequeue_pop_back(dequeue);
        t_person* cloned_person = dequeue_pop_back(cloned_dequeue);
        assert(person->age == cloned_person->age && strcmp(person->name, cloned_person->name) == 0);

        free(person);
        free(cloned_person);
    }

    free(people);
    dequeue_dispose(&dequeue);
    dequeue_dispose(&cloned_dequeue);
}

void dequeue_test_invalid_arguments() {
    printf("Testing invalid arguments...\n");

    assert(dequeue_push_back(NULL, NULL) == EINVAL);
    assert(dequeue_push_front(NULL, NULL) == EINVAL);
    assert(dequeue_pop_back(NULL) == NULL);
    assert(dequeue_pop_front(NULL) == NULL);
    assert(dequeue_peek_back(NULL) == NULL);
    assert(dequeue_peek_front(NULL) == NULL);
    assert(dequeue_clone(NULL) == NULL);
    assert(dequeue_clear(NULL) == EINVAL);
    assert(dequeue_dispose(NULL) == EINVAL);
}

