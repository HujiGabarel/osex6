//
// Created by T9058090 on 23/05/2023.
//

#ifndef _JOB_H_
#define _JOB_H_

#include <cstdint>
#include <atomic>
#include "Barrier/Barrier.h"
#include "MapReduceFramework.h"
struct ThreadContext
{
    Barrier *barrier;
    int threadID;
    std::atomic<uint64_t> *key_counter;
    std::atomic<uint64_t> *index_counter;
    const InputVec *inputVec;
    std::vector<IntermediateVec> *middle_vectors;
    std::vector<IntermediateVec> *shuffled_queue;
    OutputVec *outputVec;
    const MapReduceClient *client;
    pthread_mutex_t *stage_counter_mutex;
    IntermediateVec *thread_vec;

};

class Job
{

 public:
  std::vector<pthread_t> threads;
  std::vector<IntermediateVec> shuffled;
  std::vector<ThreadContext> contexts;
  std::vector<IntermediateVec> middle_vectors;
  std::atomic<uint64_t> atomic_counter;
  std::atomic<uint64_t> key_counter;
  Barrier barrier;
  pthread_mutex_t stage_counter_mutex;



  bool wait_called;
  JobState state;




  Job(unsigned long input_vec_size,
      unsigned long thread_num);
  JobState getState() const;
  void waitThreads();

};

#endif //_JOB_H_
