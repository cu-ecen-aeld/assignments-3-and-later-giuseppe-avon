#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;        	    
    
    thread_func_args->thread_complete_success = false;
    int ret = 0;
    bool ok = false;
    
    int sleepAcquireTime = thread_func_args->wait_to_obtain_ms * 1000;
    DEBUG_LOG("Wait to obtain mutex %d milliseconds", sleepAcquireTime);
    ret = usleep(sleepAcquireTime);
    ok = (ret == 0);
    if(!ok) {
    	ERROR_LOG("Failure sleeping %d ms to obtain mutex", sleepAcquireTime);
    }
    
    if(ok) {
        DEBUG_LOG("Locking the mutex");
        ret = pthread_mutex_lock(thread_func_args->mutex_lock);
        ok = (ret == 0);
        if(!ok) {
            ERROR_LOG("Failure to acquire the mutex lock");
        }
    }
    
    if(ok) {
        int lockReleaseTime = thread_func_args->wait_to_release_ms;
        DEBUG_LOG("Waiting to release mutex %d milliseconds", lockReleaseTime);
        ret = usleep(lockReleaseTime);
        ok = (ret == 0);
        if(!ok) {
            ERROR_LOG("Failure sleeping %d ms before releasing the mutex", lockReleaseTime);
        }    
    }
    
    if(ok) {
        ret = pthread_mutex_unlock(thread_func_args->mutex_lock);
        ok = (ret == 0);
        if(!ok) {
            ERROR_LOG("Failure releasing the mutex lock");
        }    
    }
    
    if(ok) {
        thread_func_args->thread_complete_success = true;
    }
    
    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
    
    struct thread_data *threadData = (struct thread_data*)malloc(sizeof(struct thread_data));
    
    threadData->wait_to_obtain_ms = wait_to_obtain_ms;
    threadData->wait_to_release_ms = wait_to_release_ms;
    threadData->mutex_lock = mutex;
    
    int ret = pthread_create(thread, NULL, &threadfunc, (void*)threadData);
    bool ok = (ret == 0);

    return ok;
}

