//
// Created by T9058090 on 23/05/2023.
//
#include <pthread.h>
#include "MapReduceFramework.h"
#include "Barrier/Barrier.h"
#include <iostream>
#include <atomic>
#include "Job.h"
#include <algorithm>

Job::Job (unsigned long
    input_vec_size,
          unsigned long thread_num) :
    threads (thread_num), shuffled(0),contexts(0), middle_vectors
    (thread_num), atomic_counter
    (input_vec_size << 33), key_counter (input_vec_size << 32) , barrier
    (thread_num),
    wait_called
    (false), state
    ({UNDEFINED_STAGE,0}), stage_counter_mutex ()
{
  pthread_mutex_init(&stage_counter_mutex, NULL);



}

void Job::waitThreads ()
{
  if (!wait_called)
  {
    for (std::size_t i = 0; i < (threads).size (); ++i)
    {
      auto thread = (threads)[i];
      if (pthread_join (thread, nullptr) != 0)
      {
        std::cerr << "system error: pthread_join" << std::endl;
        exit (1);
      }
    }
    wait_called = true;
    std::cout << "wait was called" << std::endl;
  }
}

JobState Job::getState () const
{
  pthread_mutex_lock((contexts[0].stage_counter_mutex));
  uint64_t old_atom = atomic_counter.load ();
  uint64_t old = key_counter.load ();
  pthread_mutex_unlock((contexts[0].stage_counter_mutex));
  return {(stage_t) (old_atom & 0b11), std::min(100 * ((float) (old &
  0xffffffff)/
  (float) (old >> 32)), (float) 100.0)};

}


