#pragma once
#include <iostream>
#include <queue>
#include <pthread.h>

typedef int JobID;

// Abstract Class Job
class Job {
  public:
    Job() = default;
    virtual ~Job() {}

    // This method should be implemented by subclasses.
    virtual int Run() = 0;
};

// Class JobScheduler
class JobScheduler {
  private:
    int num_threads;
    pthread_t* threads;
    std::queue<Job*> jobQueue;
    pthread_mutex_t qlock;
    pthread_cond_t q_not_empty;
    pthread_cond_t q_empty;
    bool shutdown;
    bool dont_accept;

    // Main routine task for threads
    void *work(void* vargs);

    // Calls work function. Compatible with pthread_create.
    friend void* work_(void* This);
  public:
    JobScheduler() = default;
    ~JobScheduler() = default;

    // Initializes the JobScheduler with the number of open threads.
    // Returns true if everything done right false else.
    bool Init(int num_of_threads);

    // Free all resources that the are allocated by JobScheduler
    // Returns true if everything done right false else.
    bool Destroy();

    // Waits Until executed all jobs in the queue.
    void Barrier();

    // Add a job in the queue and returns a JobId
    JobID Schedule(Job* job);

    // Waits until all threads finish their job, and after that close all threads.
    void Stop();
};