/*
* @file pthread_doc.c
* @brief Program to demonstrate various pthread functions
*
* This source file contains code for demonstrating the Pthread API
* functions, through various configurations 
*
* Tools used: GCC Compiler, make
* How to compile from source: make <demo name>
*
* @author Rishi Soni
* @date October 5 2017
* @version 1.0
*
*/

#define _GNU_SOURCE     /* To get pthread_getattr_np() declaration */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#define NUM_THREADS (2)
#define COUNTER     (10)
int counter = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

//Start functions for different threads
static void *print_message_np(void *ptr)
{
    char *msg;
    msg = (char*)ptr;
}

static void *print_message(void *ptr)
{
    char *msg;
    msg = (char*)ptr;
    printf("%s. Thread Number: %ld\n", msg, pthread_self());
}

static void *print_message1(void *ptr)
{
    char *msg;
    msg = (char*)ptr;
    pthread_exit(NULL);
    printf("%s. Thread Number: %ld\n", msg, pthread_self());
}

static void *print_message_m(void *ptr)
{
    char *msg;
    msg = (char*)ptr;
    printf("%s. Thread Number: %ld\n", msg, pthread_self());
    pthread_mutex_lock(&mutex);
    counter++;
    pthread_mutex_unlock(&mutex);
}

static void *print_message_mm(void *ptr)
{
    char *msg;
    msg = (char*)ptr;
    printf("%s. Thread Number: %ld\n", msg, pthread_self());
    pthread_mutex_trylock(&mutex);
    counter++;
    pthread_mutex_unlock(&mutex);
}

/* pthread_create, join, self 
*  This code creates two threads, and passes two messages, 
*  corresponding to the thread. Joins main() thread after 
*  worker thread finishes execution. Displays thread ID
*  Does not call pthread_exit()
*  Compile and run command: make Demo1
*/
#ifdef Demo_1
int main(int argc, char const *argv[])
{
    pthread_t thread[NUM_THREADS];
    const char *message1 = "Entered Thread 1";
    const char *message2 = "Entered Thread 2";

    printf("Demo1 code for pthread_create, join, self\n");

    if (pthread_create(&thread[0], NULL, print_message, (void*)message1))
    {
        perror("Thread1 creation failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread[1], NULL, print_message, (void*)message2))
    {
        perror("Thread2 creation failed");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    exit(EXIT_SUCCESS);
}
#endif

/* pthread_create, join , exit, self
*  This code creates two threads, and passes two messages, 
*  corresponding to the thread. Joins main() thread after 
*  worker thread finishes execution. Displays thread ID
*  Thread 2 calls pthread_exit() to exit execution
*  Compile and run command: make Demo2
*/
#ifdef Demo_2
int main(int argc, char const *argv[])
{
    pthread_t thread[NUM_THREADS];
    const char *message1 = "Entered Thread 1";
    const char *message2 = "Entered Thread 2";

    printf("Demo2 code for pthread_create, join, exit, self\n");
    if (pthread_create(&thread[0], NULL, print_message, (void*)message1))
    {
        perror("Thread1 creation failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread[1], NULL, print_message1, (void*)message2))
    {
        perror("Thread2 creation failed");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    exit(EXIT_SUCCESS);
}
#endif

/* pthread_getattr_np
*  This code creates two threads, and passes two messages, 
*  corresponding to the thread. Sets different stack and guard sizes for
*  different threads. Verifies the set stack and guard sizes using 
*  pthread_getattr_np, and displays them on the terminal
*  Compile and run command: make Demo3
*/
#ifdef Demo_3
int main(int argc, char const *argv[])
{
    pthread_t thread[NUM_THREADS];
    long stack_size_1, stack_size_2, guard_size_1, guard_size_2, stack_size = -1, guard_size = -1;
    long stack_size_t = -1, guard_size_t = -1;
    pthread_attr_t attr1, attr2;
    pthread_attr_t attrp;

    int i;
    const char *message1 = "Entered Thread 1";
    const char *message2 = "Entered Thread 2";
    
    printf("Demo3 code for pthread_getattr_np\n");
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attrp);

    //Setting thread attributes manually
    stack_size_1 = 0x201000; // 2101248 bytes;
    guard_size_1 = 4096;  //in bytes
    
    stack_size_2 = 0x201000; // 2101248 bytes;
    guard_size_2 = 8192;  //in bytes

    i = pthread_attr_setstacksize(&attr1, stack_size_1);
    if(i != 0)
    {
        perror("pthread_attr_setstacksize");
        exit(1);
    }

    i = pthread_attr_setguardsize(&attr1, guard_size_1);
    if(i != 0)
    {
        perror("pthread_attr_setguardsize");
        exit(1);
    }

    i = pthread_attr_setstacksize(&attr2, stack_size_2);
    if(i != 0)
    {
        perror("pthread_attr_setstacksize");
        exit(1);
    }

    i = pthread_attr_setguardsize(&attr2, guard_size_2);
    if(i != 0)
    {
        perror("pthread_attr_setguardsize");
        exit(1);
    }

    //Thread creation
    if (pthread_create(&thread[0], &attr1, print_message_np, (void*)message1))
    {
        perror("Thread1 creation failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread[1], &attr2, print_message_np, (void*)message2))
    {
        perror("Thread2 creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&attrp, 0, sizeof(attrp));

    //display thread attributes
    i = pthread_getattr_np(thread[0], &attrp);
    if(i != 0)
    {
        perror("pthread_getattr_np");
        exit(1);
    }

    i = pthread_attr_getguardsize(&attrp, &guard_size);
    if (i != 0)
    {
        perror("pthread_attr_getguardsize");
        exit(1);   
    }
    printf("Thread 1: Guard size = %ld bytes\n", guard_size);

    i = pthread_attr_getstacksize(&attrp, &stack_size);
    if (i != 0)
    {
        perror("pthread_attr_getstacksize");
        exit(1);   
    }
    printf("Thread 1: Stack size = %ld bytes\n", stack_size);

    memset(&attrp, 0, sizeof(attrp));
    i = pthread_getattr_np(thread[1], &attrp);
    if(i != 0)
    {
        perror("pthread_getattr_np");
        exit(1);
    }

    i = pthread_attr_getguardsize(&attrp, &guard_size_t);
    if (i != 0)
    {
        perror("pthread_attr_getguardsize");
        exit(1);   
    }
    printf("Thread 2: Guard size = %ld bytes\n", guard_size_t);

    i = pthread_attr_getstacksize(&attrp, &stack_size_t);
    if (i != 0)
    {
        perror("pthread_attr_getstacksize");
        exit(1);   
    }
    printf("Thread 2: Stack size = %ld bytes\n", stack_size_t);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    exit(EXIT_SUCCESS);
}
#endif


/* pthread_getattr_default_np
*  This code creates two threads, and passes two messages, 
*  corresponding to the thread. Displays the default stack and guard 
*  sizes and displays the results on the terminal.
*  Compile and run command: make Demo4
*/
#ifdef Demo_4
int main(int argc, char const *argv[])
{
    pthread_t thread[NUM_THREADS];
    long stack_size = -1, guard_size = -1;
    long stack_size_t = -1, guard_size_t = -1;
    pthread_attr_t attrp;

    int i;
    const char *message1 = "Entered Thread 1";
    const char *message2 = "Entered Thread 2";
    
    printf("Demo4 code for pthread_getattr_default_np\n");
    pthread_attr_init(&attrp);

    if (pthread_create(&thread[0], NULL, print_message_np, (void*)message1))
    {
        perror("Thread1 creation failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread[1], NULL, print_message_np, (void*)message2))
    {
        perror("Thread2 creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&attrp, 0, sizeof(attrp));
    //display thread attributes
    i = pthread_getattr_default_np(&attrp);
    if(i != 0)
    {
        perror("pthread_getattr_np");
        exit(1);
    }

    i = pthread_attr_getguardsize(&attrp, &guard_size);
    if (i != 0)
    {
        perror("pthread_attr_getguardsize");
        exit(1);   
    }
    printf("Default Guard size = %ld bytes\n", guard_size);

    i = pthread_attr_getstacksize(&attrp, &stack_size);
    if (i != 0)
    {
        perror("pthread_attr_getstacksize");
        exit(1);   
    }
    printf("Default Stack size = %ld bytes\n", stack_size);

    memset(&attrp, 0, sizeof(attrp));
    
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    exit(EXIT_SUCCESS);
}
#endif


/* pthread_setattr_default_np
*  This code creates two threads, and passes two messages, 
*  corresponding to the thread. Sets the default stack and guard 
*  sizes 
*  Compile and run command: make Demo5
*/
#ifdef Demo_5
int main(int argc, char const *argv[])
{
    pthread_t thread[NUM_THREADS];
    long stack_size = -1, guard_size = -1;
    long stack_size_t = -1, guard_size_t = -1;
    pthread_attr_t attrp, attr;

    int i;
    const char *message1 = "Entered Thread 1";
    const char *message2 = "Entered Thread 2";
    
    printf("Demo4 code for pthread_setattr_default_np\n");
    pthread_attr_init(&attrp);
    pthread_setattr_default_np(&attrp);

    if (pthread_create(&thread[0], &attrp, print_message_np, (void*)message1))
    {
        perror("Thread1 creation failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread[1], &attrp, print_message_np, (void*)message2))
    {
        perror("Thread2 creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&attrp, 0, sizeof(attrp));
    //display thread attributes
    i = pthread_getattr_np(thread[0], &attr);
    if(i != 0)
    {
        perror("pthread_getattr_np");
        exit(1);
    }

    i = pthread_attr_getguardsize(&attr, &guard_size);
    if (i != 0)
    {
        perror("pthread_attr_getguardsize");
        exit(1);   
    }
    printf("Guard size = %ld bytes\n", guard_size);

    i = pthread_attr_getstacksize(&attr, &stack_size);
    if (i != 0)
    {
        perror("pthread_attr_getstacksize");
        exit(1);   
    }
    printf("Stack size = %ld bytes\n", stack_size);

    memset(&attrp, 0, sizeof(attr));
    
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    exit(EXIT_SUCCESS);
}
#endif



/* Mutex testing (init, lock, unlock, destroy)
*  This code creates two threads, and passes two messages, 
*  corresponding to the thread. Applies mutex lock on a variable.
*  Thread 1 gets access to resource before thread 2
*  Compile and run command: make Demo5
*/
#ifdef Demo_6
int main(int argc, char const *argv[])
{
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attribute[NUM_THREADS];
    const char *message1 = "Entered Thread 1";
    const char *message2 = "Entered Thread 2";

    printf("Demo5 code for mutex init, lock, unlock, destroy\n");

    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&thread[0], NULL, print_message_m, (void*)message1))
    {
        perror("Thread1 creation failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread[1], NULL, print_message_m, (void*)message2))
    {
        perror("Thread2 creation failed");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    printf("Value of counter is %d\n", counter);

    pthread_mutex_destroy(&mutex);
    exit(EXIT_SUCCESS);
}
#endif

/* Mutex testing (init, trylock, unlock, destroy)
*  This code creates two threads, and passes two messages, 
*  corresponding to the thread. Applies mutex lock on a variable. Tries
*  to lock mutex. If cannot do so, fails and exits
*  Thread 1 gets access to resource before Thread 2
*  Compile and run command: make Demo6
*/
#ifdef Demo_7
int main(int argc, char const *argv[])
{
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attribute[NUM_THREADS];
    const char *message1 = "Entered Thread 1";
    const char *message2 = "Entered Thread 2";

    printf("Demo6 code for mutex init, trylock, unlock, destroy\n");

    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&thread[0], NULL, print_message_mm, (void*)message1))
    {
        perror("Thread1 creation failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread[1], NULL, print_message_mm, (void*)message2))
    {
        perror("Thread2 creation failed");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    printf("Value of counter is %d\n", counter);

    pthread_mutex_destroy(&mutex);

    exit(EXIT_SUCCESS);
}
#endif

/* Condition Variables
*  This code creates two threads, and passes two messages, 
*  corresponding to the thread. Thread 2 waits for Thread 1 to signal it. 
*  Compile and run command: make Demo7
*/
#ifdef Demo_8
static void *print_message_c1(void *ptr)
{
    char *msg;
    msg = (char*)ptr;
    printf("%s. Thread Number: %ld\n", msg, pthread_self());
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    counter++;
    pthread_mutex_unlock(&mutex);
}

static void *print_message_c2(void *ptr)
{
    char *msg;
    msg = (char*)ptr;
    printf("%s. Thread Number: %ld\n", msg, pthread_self());
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&cond);
    counter++;
    pthread_mutex_unlock(&mutex);
}


int main(int argc, char const *argv[])
{
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attribute[NUM_THREADS];
    const char *message1 = "Entered Thread 1";
    const char *message2 = "Entered Thread 2";

    printf("Demo7 code for cond init, wait, destroy\n");

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    if (pthread_create(&thread[0], NULL, print_message_c1, (void*)message1))
    {
        perror("Thread1 creation failed");
        exit(EXIT_FAILURE);
    }

    sleep(1);

    if (pthread_create(&thread[1], NULL, print_message_c2, (void*)message2))
    {
        perror("Thread2 creation failed");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    printf("Value of counter is %d\n", counter);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);


    exit(EXIT_SUCCESS);
}
#endif
