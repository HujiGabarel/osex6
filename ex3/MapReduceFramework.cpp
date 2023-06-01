#include "MapReduceFramework.h"
#include "Barrier/Barrier.h"
#include <pthread.h>
#include "Job.h"
#include <atomic>
#include <algorithm>
#include <iostream>
#include <unistd.h>

void emit2 (K2 *key, V2 *value, void *context);
void emit3 (K3 *key, V3 *value, void *context);

//struct ThreadContext
//{
//    Barrier *barrier;
//    int threadID;
//    std::atomic<uint64_t> *key_counter;
//    std::atomic<uint64_t> *index_counter;
//    const InputVec &inputVec;
////    IntermediateVec &middleVec;
//    std::vector<IntermediateVec> &middle_vectors;
//    std::vector<IntermediateVec> &shuffled_queue;
//    OutputVec &outputVec;
//    const MapReduceClient &client;
//
//};

struct ReduceContext
{
    unsigned long index;
    OutputVec *outputVec;
};

bool compare (const IntermediatePair &p1, const IntermediatePair &p2)
{
  return (*(p2.first) < *(p1.first)) ;
}

void *thread_func (void *arg)
{

  auto *tc = (ThreadContext *) arg;


  unsigned long old_value;
  IntermediateVec vec;
  tc->thread_vec = &vec;

  //TODO this stage managmaent sucks
  (*tc->index_counter) |= MAP_STAGE;
  (tc->barrier)->barrier ();
  while (((old_value = ((*tc->index_counter) += (1 << 2))) & (0b11)) ==
         MAP_STAGE)
  {
    old_value -= 4;

    if ((old_value >> 2 & (0x7fffffff)) >= (old_value >> 33 &
                                            (0x7fffffff)))
    {
      break;
    }
    else
    {
      auto &element = (*tc->inputVec)[(old_value >> 2 & (0x7fffffff))];
      (*tc->client).map (element.first, element.second, tc);
      (*tc->key_counter)++;
    }
  }

  tc->barrier->barrier();
//  pthread_mutex_lock(tc->stage_counter_mutex);


//  IntermediateVec &thread_mid = (*((*tc).middle_vectors))[tc->threadID];
//  auto a = thread_mid.end()--;
//  for (auto & pair : thread_mid){
//    if(!pair.first){
//      printf ("fsdafsd\n");
//    }
//  }
//  printf ("tid: %d \n", tc->threadID);

  std::sort (vec.begin (), vec.end(), compare);

  (*(tc->middle_vectors))[tc->threadID] = vec;

//  pthread_mutex_unlock(tc->stage_counter_mutex);


//  printf ("Thread %d kc 2222 is %p\n",tc->threadID,tc->key_counter);

  tc->barrier->barrier();
//  printf ("Thread %d kc fdfd is %p\n",tc->threadID,tc->key_counter);

  // Shuffle
  if (tc->threadID == 0)
  {
    unsigned long total_size = 0;
    for (const auto &vec: (*tc->middle_vectors))
    {
      total_size += vec.size ();
    }
    pthread_mutex_lock(tc->stage_counter_mutex);
    (*tc->index_counter)++;
    (*tc->key_counter) = total_size << 32;
    pthread_mutex_unlock(tc->stage_counter_mutex);

    unsigned long empty_vec_counter = 0;
    for (auto &vec: (*tc->middle_vectors))
    {
      if (vec.empty ())
      {
        empty_vec_counter++;
      }
    }
    while (empty_vec_counter < (*tc->middle_vectors).size ())
    {
      K2 *min_key = nullptr;
      for (auto &vec: (*tc->middle_vectors))
      {
        if (!vec.empty ())
        {
          if ((nullptr == min_key) || (*(vec[vec.size () - 1]
              .first) < (*min_key)))
          {
            min_key = (vec[vec.size () - 1]).first;
          }
        }
      }
      IntermediateVec vec_to_add;

      for (auto &vec: (*tc->middle_vectors))
      {
        while (!vec.empty() && !(*min_key < *(vec[vec.size () - 1].first)))
        {
          vec_to_add.push_back (vec[vec.size () - 1]);
          vec.pop_back ();
          (*tc->key_counter)++;
          if (vec.empty ())
          {
            empty_vec_counter++;
          }
        }
      }
      (*tc->shuffled_queue).push_back (vec_to_add);
    }
    pthread_mutex_lock(tc->stage_counter_mutex);
    (*tc->key_counter) = total_size << 32;
    (*tc->index_counter) = REDUCE_STAGE + ((*tc->shuffled_queue).size () << 33);
    pthread_mutex_unlock(tc->stage_counter_mutex);

    for (int i = 0; i < (*tc->shuffled_queue).size(); i++){
      (*tc->outputVec).push_back ({nullptr, nullptr});
    }

  }
  tc->barrier->barrier ();
  while (((old_value = (*tc->index_counter += (1 << 2))) & 0b11) ==
         REDUCE_STAGE)
  {
    old_value -= 4;
    unsigned long curr_index = ((old_value
        >> 2) &(0x7fffffff));
    unsigned long total_size = ((old_value >> 33) & (0x7fffffff));

    if (curr_index >= total_size)
    {
      return nullptr;
    }
    else
    {
      ReduceContext rc = {curr_index, &(*tc->outputVec)};
      unsigned long vec_size = (*tc->shuffled_queue)[curr_index].size ();
      (*tc->client).reduce (&((*tc->shuffled_queue)[curr_index]), &rc);
      unsigned long res = ((*tc->key_counter)+= vec_size);
//      printf ("Thread %d kc is %lu\n", tc->threadID,res & 0xffffffff);
    }
  }
  return nullptr;
}

void emit2 (K2 *key, V2 *value, void *context)
{
  if (key == NULL){
    printf ("fdddd\n");
  }
  auto *tc = (ThreadContext *) context;
  ((*(tc->thread_vec))).push_back ({key, value});
}

void emit3 (K3 *key, V3 *value, void *context)
{
  auto *tc = (ReduceContext *) context;
//  printf("OutputVec size is %lu\n", (*tc->outputVec).size());
  (*tc->outputVec)[tc->index] = {key, value};
}

JobHandle startMapReduceJob (const MapReduceClient &client,
                             const InputVec &inputVec, OutputVec &outputVec,
                             int multiThreadLevel)
{
//  std::vector<pthread_t> *threads = new  std::vector<pthread_t>
//      (multiThreadLevel);
  Job *job = new Job (inputVec.size () ,multiThreadLevel);
//  std::vector<ThreadContext>* contexts = new std::vector<ThreadContext>();
//  auto *barrier = new Barrier(multiThreadLevel);
//
//  std::vector<IntermediateVec>* middle_vectors = new
//      std::vector<IntermediateVec>(multiThreadLevel);
//  std::vector<IntermediateVec>* shuffled = new
//      std::vector<IntermediateVec>(0);
//  pthread_mutex_t *mutex = new pthread_mutex_t;
//  pthread_mutex_init(mutex, NULL);
  for (int i = 0; i < multiThreadLevel; ++i)
  {
    job->contexts.push_back ({&job->barrier, i, &(job->key_counter), &
    (job->atomic_counter),
                         &inputVec,
                              &job->middle_vectors, &job->shuffled, &outputVec,
                         &client, &job->stage_counter_mutex, nullptr});
  }

  for (int i = 0; i < multiThreadLevel; i++)
  {
    if (pthread_create (&(job->threads)[i], nullptr, thread_func, &(job->contexts)
    [i]) != 0)
    {
      std::cerr << "system error: pthread_create" << std::endl;
      exit(1);
    }
  }
  return job;
}

void waitForJob (JobHandle job)
{
  Job *myJob = static_cast<Job *>(job);
  myJob->waitThreads ();
}
void getJobState (JobHandle job, JobState *state)
{
  //TODO pass by value
  *state = static_cast<Job *>(job)->getState ();
}
void closeJobHandle (JobHandle job)
{
  waitForJob (job);
  delete static_cast<Job *>(job);
}

