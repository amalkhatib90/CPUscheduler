/** @file libscheduler.h
 */

#ifndef LIBSCHEDULER_H_
#define LIBSCHEDULER_H_

struct _job_t;
typedef struct _job_t
{
	int id;
	int priority;
	int arrival_time;
	int start_time; //time starts for one of them(start -arr)
	int running_time; // how much time run already curr - start
	int remaining_time; // how much time left
	int end_time; // the time it finished
} *job_t;

static job_t new_job(int job_id, int arr_time, int run_time, int priority){
  job_t new_job = (job_t) malloc(sizeof(job_t));

  new_job->id = job_id;
  new_job->priority = priority;
  new_job->arrival_time = arr_time;
  new_job->start_time = -1;
  new_job->running_time = run_time;
  new_job->remaining_time = run_time;
  new_job->end_time= 0;

  return new_job;
}

/**
  Constants which represent the different scheduling algorithms
*/
typedef enum {FCFS = 0, SJF, PSJF, PRI, PPRI, RR} scheme_t;

void  scheduler_start_up               (int cores, scheme_t scheme);
int   scheduler_new_job                (int job_number, int time, int running_time, int priority);
int   scheduler_job_finished           (int core_id, int job_number, int time);
int   scheduler_quantum_expired        (int core_id, int time);
float scheduler_average_turnaround_time();
float scheduler_average_waiting_time   ();
float scheduler_average_response_time  ();
void  scheduler_clean_up               ();
void  scheduler_show_queue             ();

int idle_core                          ();
void set_time                           (int time);
int least_prio_job                    (void* job);

#endif /* LIBSCHEDULER_H_ */
