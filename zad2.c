#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *array;
int array_size;

pthread_mutex_t lock;

void *arr_first_half(void *arg) {
    for (int i = 0; i < array_size / 2; ++i) {
        pthread_mutex_lock(&lock);
        array[i] = 1;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *arr_sec_half(void *arg) {
    for (int i = array_size / 2; i < array_size; ++i) {
        pthread_mutex_lock(&lock);
        array[i] = 2;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock, NULL);

    printf("Array size: ");
    scanf("%d", &array_size);
    array = (int*)malloc(array_size * sizeof(int));

    if (pthread_create(&thread1, NULL, arr_first_half, NULL) != 0) {
        perror("thread1 - create");
        abort();
    }

    if (pthread_create(&thread2, NULL, arr_sec_half, NULL) != 0) {
        perror("thread2 - create");
        abort();
    }

    if (pthread_join(thread1, NULL) != 0) {
        perror("thread1 - join");
        abort();
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("thread1 - join");
        abort();
    }

    pthread_mutex_destroy(&lock);

    for (int i = 0; i < array_size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
    free(array);

    return 0;
}

