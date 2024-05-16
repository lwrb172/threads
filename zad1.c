#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *doubling(void * arg) {
    int *num = (int *)arg;
    int *result = malloc(sizeof(int));
    *result = (*num) * 2;
    return result;
}

int main(void) {
    pthread_t thread1, thread2;
    int num1 = 2, num2 = 4;
    int *result1, *result2;

    if (pthread_create(&thread1, NULL, doubling, &num1) != 0) {
        perror("thread1 - create");
        abort();
    }

    if (pthread_create(&thread2, NULL, doubling, &num2) != 0) {
        perror("thread2 - create");
        abort();
    }

    if (pthread_join(thread1, (void **)&result1) != 0) {
        perror("thread1 - join");
        abort();
    }
    printf("podwojona wartość: %d\n", *result1);
    free(result1);

    if (pthread_join(thread2, (void **)&result2) != 0) {
        perror("thread2 - join");
        abort();
    }
    printf("podwojona wartość: %d\n", *result2);
    free(result2);

    return 0;
}
