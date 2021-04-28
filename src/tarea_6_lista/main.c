
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <pthread.h>
//
//const int MAX_KEY = 100000000;
//int act_keys = 100;
//
//struct list_node_s {
//  int data;
//  struct list_node_s* next;
//  pthread_mutex_t mutex;
//};
//
//struct list_node_s* head = NULL;
//int thread_count;
//int total_ops;
//double insert_p;
//double search_p;
//double delete_p;
//pthread_rwlock_t rwlock;
//pthread_mutex_t count_mutex;
//int Member_count = 0, insert_count = 0, delete_count = 0;
//
///* Setup */
//void Usage(char* prog_name);
//void Get_input(int* inserts_in_main_p);
//
///* Thread function */
//void* Thread_work(void* rank);
//
///* List operations */
//int Insert(int value);
//void Print(void);
//int Member(int value);
//int Delete(int value);
//void Free_list(void);
//int Is_empty(void);
//
//int main(int argc, char* argv[]) {
//  long i;
//  int key, success, attempts;
//  pthread_t* thread_handles;
//  int inserts_in_main;
//  unsigned seed = 1;
//  double start, finish;
//  if (argc != 2) Usage(argv[0]);
//  thread_count = strtol(argv[1],NULL,10);
//  Get_input(&inserts_in_main);
//  i = attempts = 0;
//  while ( i < inserts_in_main && attempts < 2*inserts_in_main ) {
//    key = rand() % MAX_KEY;
//    success = Insert(key);
//    attempts++;
//    if (success) i++;
//  }
//  printf("Inserted %ld keys in empty list\n", i);
//  thread_handles = malloc(thread_count*sizeof(pthread_t));
//  pthread_mutex_init(&count_mutex, NULL);
//  pthread_rwlock_init(&rwlock, NULL);
//
//
//  clock_t t;
//  t = clock();
//
//  for (i = 0; i < thread_count; i++)
//    pthread_create(&thread_handles[i], NULL, Thread_work, (void*) i);
//
//  for (i = 0; i < thread_count; i++)
//    pthread_join(thread_handles[i], NULL);
//
//  t = clock() - t;
//  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
//
//
//  Print();
//  printf("Elapsed time = %e seconds\n", finish - start);
//  printf("Total ops = %d\n", total_ops);
//  printf("Member(FIND) ops = %d\n", Member_count);
//  printf("insert ops = %d\n", insert_count);
//  printf("delete ops = %d\n", delete_count);
//  /* Free List and Threads */
//  Free_list();
//  pthread_rwlock_destroy(&rwlock);
//  pthread_mutex_destroy(&count_mutex);
//  free(thread_handles);
//  return 0;
//}  /* main */
//
//void Usage(char* prog_name) {
//  fprintf(stderr, "usage: %s <thread_count>\n", prog_name);
//  exit(0);
//}  /* Usage */
//
//void Get_input(int* inserts_in_main_p) {
//  printf("Keys: \n");
//  scanf("%d", inserts_in_main_p);
//  printf("Ops Number: \n");
//  scanf("%d", &total_ops);
//  printf("Percent of Ops in searches? (between 0 and 1)\n");
//  scanf("%lf", &search_p);
//  printf("Percent of Ops in inserts? (between 0 and 1)\n");
//  scanf("%lf", &insert_p);
//  delete_p = 1.0 - (search_p + insert_p);
//}  /* Get_input */
//
//int Insert(int value) {
//  struct list_node_s* curr = head;
//  struct list_node_s* pred = NULL;
//  struct list_node_s* temp;
//  int rv = 1;
//  while (curr != NULL && curr->data < value) {
//    pred = curr;
//    curr = curr->next;
//  }
//  if (curr == NULL || curr->data > value) {
//    temp = malloc(sizeof(struct list_node_s));
//    temp->data = value;
//    temp->next = curr;
//    if (pred == NULL)
//      head = temp;
//    else
//      pred->next = temp;
//  } else { /* value in list */
//    rv = 0;
//  }
//
//  return rv;
//}  /* Insert */
//
//void Print(void) {
//  struct list_node_s* temp;
//  printf("lista = ");
//  temp = head;
//  while (temp != (struct list_node_s*) NULL) {
//    printf("%d ", temp->data);
//    temp = temp->next;
//  }
//  printf("\n");
//}  /* Print */
//
//int  Member(int value) {
//  struct list_node_s* temp;
//  temp = head;
//  while (temp != NULL && temp->data < value)
//    temp = temp->next;
//  if (temp == NULL || temp->data > value) {
//    return 0;
//  } else {
//    return 1;
//  }
//}  /* Member */
//
//int Delete(int value) {
//  struct list_node_s* curr = head;
//  struct list_node_s* pred = NULL;
//  int rv = 1;
//  /* Member value */
//  while (curr != NULL && curr->data < value) {
//    pred = curr;
//    curr = curr->next;
//  }
//  if (curr != NULL && curr->data == value) {
//    if (pred == NULL) { /* first element in list */
//      head = curr->next;
//      free(curr);
//    } else {
//      pred->next = curr->next;
//      free(curr);
//    }
//  } else { /* Not in list */
//    rv = 0;
//  }
//
//  return rv;
//}  /* Delete */
//
//void Free_list(void) {
//  struct list_node_s* p;
//  struct list_node_s* temp;
//  if (Is_empty()) return;
//  p = head;
//  temp = p->next;
//  while (temp != NULL) {
//    free(p);
//    p = temp;
//    temp = p->next;
//  }
//  free(p);
//}  /* Free_list */
//
//int  Is_empty(void) {
//  if (head == NULL)
//    return 1;
//  else
//    return 0;
//}  /* Is_empty */
//
//void* Thread_work(void* rank) {
//  long my_rank = (long) rank;
//  int i, val;
//  double which_op;
//  unsigned seed = my_rank + 1;
//  int my_Member_count = 0, my_insert_count=0, my_delete_count=0;
//  int ops_per_thread = total_ops/thread_count;
//  for (i = 0; i < ops_per_thread; i++) {
//    which_op = rand();
//    val = rand() % MAX_KEY;
//    if (which_op < search_p) {
//      pthread_rwlock_rdlock(&rwlock);
//      Member(val);
//      pthread_rwlock_unlock(&rwlock);
//      my_Member_count++;
//    } else if (which_op < search_p + insert_p) {
//      pthread_rwlock_wrlock(&rwlock);
//      Insert(val);
//      pthread_rwlock_unlock(&rwlock);
//      my_insert_count++;
//    } else { /* delete */
//      pthread_rwlock_wrlock(&rwlock);
//      Delete(val);
//      pthread_rwlock_unlock(&rwlock);
//      my_delete_count++;
//    }
//  }  /* for */
//  pthread_mutex_lock(&count_mutex);
//  Member_count += my_Member_count;
//  insert_count += my_insert_count;
//  delete_count += my_delete_count;
//  pthread_mutex_unlock(&count_mutex);
//  return NULL;
//}  /* Thread_work */

//
//#include <stdio.h>
//#include <stdlib.h>
//#include <pthread.h>
//#include <time.h>
//
//const int MAX_KEY = 100000000;
//int act_keys = 100;
//
//const int IN_LIST = 1;
//const int EMPTY_LIST = -1;
//const int END_OF_LIST = 0;
//
//struct list_node_s {
//  int    data;
//  pthread_mutex_t mutex;
//  struct list_node_s* next;
//};
//
//struct list_node_s* head = NULL;
//pthread_mutex_t head_mutex;
//int thread_count;
//int total_ops;
//double insert_p;
//double search_p;
//double delete_p;
//pthread_mutex_t count_mutex;
//int member_total=0, insert_total=0, delete_total=0;
//
///* Setup */
//void Usage(char* prog_name);
//void Get_input(int* inserts_in_main_p);
//
///* Thread function */
//void* Thread_work(void* rank);
//
///* List operations */
//void Init_ptrs(struct list_node_s** curr_pp, struct list_node_s** pred_pp);
//int Advance_ptrs(struct list_node_s** curr_pp, 	struct list_node_s** pred_pp);
//int Insert(int value);
//void Print(void);
//int Member(int value);
//int Delete(int value);
//void Free_list(void);
//int Is_empty(void);
//
//int main(int argc, char* argv[]) {
//  long i;
//  int key, success, attempts;
//  pthread_t* thread_handles;
//  int inserts_in_main;
//  unsigned seed = 1;
//  double start, finish;
//  if (argc != 2) Usage(argv[0]);
//  thread_count = strtol(argv[1], NULL, 10);
//  Get_input(&inserts_in_main);
//  i = attempts = 0;
//  pthread_mutex_init(&head_mutex, NULL);
//  while ( i < inserts_in_main && attempts < 2*inserts_in_main ) {
//    key = rand() % MAX_KEY;
//    success = Insert(key);
//    attempts++;
//    if (success) i++;
//  }
//  printf("Inserted %ld keys in empty list\n", i);
//  thread_handles = malloc(thread_count*sizeof(pthread_t));
//  pthread_mutex_init(&count_mutex, NULL);
//
//  clock_t t;
//  t = clock();
//
//  for (i = 0; i < thread_count; i++)
//    pthread_create(&thread_handles[i], NULL, Thread_work, (void*) i);
//
//  for (i = 0; i < thread_count; i++)
//    pthread_join(thread_handles[i], NULL);
//
//  t = clock() - t;
//  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
//
//
//  Print();
//  printf("Elapsed time = %e seconds\n", finish - start);
//  printf("Total ops = %d\n", total_ops);
//  printf("member ops = %d\n", member_total);
//  printf("insert ops = %d\n", insert_total);
//  printf("delete ops = %d\n", delete_total);
//  Free_list();
//  pthread_mutex_destroy(&head_mutex);
//  pthread_mutex_destroy(&count_mutex);
//  free(thread_handles);
//  return 0;
//}  /* main */
//
//void Usage(char* prog_name) {
//  fprintf(stderr, "usage: %s <thread_count>\n", prog_name);
//  exit(0);
//}  /* Usage */
//
//void Get_input(int* inserts_in_main_p) {
//  printf("Keys:\n");
//  scanf("%d", inserts_in_main_p);
//  printf("Ops Number:\n");
//  scanf("%d", &total_ops);
//  printf("Percent of Ops in searches? (between 0 and 1)\n");
//  scanf("%lf", &search_p);
//  printf("Percent of Ops in inserts? (between 0 and 1)\n");
//  scanf("%lf", &insert_p);
//  delete_p = 1.0 - (search_p + insert_p);
//}  /* Get_input */
//
//void Init_ptrs(struct list_node_s** curr_pp, struct list_node_s** pred_pp) {
//  *pred_pp = NULL;
//  pthread_mutex_lock(&head_mutex);
//  *curr_pp = head;
//  if (*curr_pp != NULL)
//    pthread_mutex_lock(&((*curr_pp)->mutex));
//}  /* Init_ptrs */
//
//int Advance_ptrs(struct list_node_s** curr_pp, struct list_node_s** pred_pp) {
//  int rv = IN_LIST;
//  struct list_node_s* curr_p = *curr_pp;
//  struct list_node_s* pred_p = *pred_pp;
//  if (curr_p == NULL) {
//    if (pred_p == NULL) {
//      /* At head of list */
//      pthread_mutex_unlock(&head_mutex);
//      return EMPTY_LIST;
//    } else {  /* Not at head of list */
//      return END_OF_LIST;
//    }
//  } else { // *curr_pp != NULL
//    if (curr_p->next != NULL)
//      pthread_mutex_lock(&(curr_p->next->mutex));
//    else
//      rv = END_OF_LIST;
//    if (pred_p != NULL)
//      pthread_mutex_unlock(&(pred_p->mutex));
//    else
//      pthread_mutex_unlock(&head_mutex);
//    *pred_pp = curr_p;
//    *curr_pp = curr_p->next;
//    return rv;
//  }
//}  /* Advance_ptrs */
//
//int Insert(int value) {
//  struct list_node_s* curr;
//  struct list_node_s* pred;
//  struct list_node_s* temp;
//  int rv = 1;
//
//  Init_ptrs(&curr, &pred);
//
//  while (curr != NULL && curr->data < value) {
//    Advance_ptrs(&curr, &pred);
//  }
//
//  if (curr == NULL || curr->data > value) {
//    temp = malloc(sizeof(struct list_node_s));
//    pthread_mutex_init(&(temp->mutex), NULL);
//    temp->data = value;
//    temp->next = curr;
//    if (curr != NULL)
//      pthread_mutex_unlock(&(curr->mutex));
//    if (pred == NULL) {
//      // Inserting in head of list
//      head = temp;
//      pthread_mutex_unlock(&head_mutex);
//    } else {
//      pred->next = temp;
//      pthread_mutex_unlock(&(pred->mutex));
//    }
//  } else { /* value in list */
//    if (curr != NULL)
//      pthread_mutex_unlock(&(curr->mutex));
//    if (pred != NULL)
//      pthread_mutex_unlock(&(pred->mutex));
//    else
//      pthread_mutex_unlock(&head_mutex);
//    rv = 0;
//  }
//
//  return rv;
//}  /* Insert */
//
//
//int  Member(int value) {
//  struct list_node_s *temp, *old_temp;
//  pthread_mutex_lock(&head_mutex);
//  temp = head;
//  if (temp != NULL) pthread_mutex_lock(&(temp->mutex));
//  pthread_mutex_unlock(&head_mutex);
//  while (temp != NULL && temp->data < value) {
//    if (temp->next != NULL)
//      pthread_mutex_lock(&(temp->next->mutex));
//    old_temp = temp;
//    temp = temp->next;
//    pthread_mutex_unlock(&(old_temp->mutex));
//  }
//
//  if (temp == NULL || temp->data > value) {
//    if (temp != NULL)
//      pthread_mutex_unlock(&(temp->mutex));
//    return 0;
//  } else { /* temp != NULL && temp->data <= value */
//    pthread_mutex_unlock(&(temp->mutex));
//    return 1;
//  }
//}  /* Member */
//
//int Delete(int value) {
//  struct list_node_s* curr;
//  struct list_node_s* pred;
//  int rv = 1;
//  Init_ptrs(&curr, &pred);
//  while (curr != NULL && curr->data < value) {
//    Advance_ptrs(&curr, &pred);
//  }
//  if (curr != NULL && curr->data == value) {
//    if (pred == NULL) { /* first element in list */
//      head = curr->next;
//      pthread_mutex_unlock(&head_mutex);
//      pthread_mutex_unlock(&(curr->mutex));
//      pthread_mutex_destroy(&(curr->mutex));
//      free(curr);
//    } else { /* pred != NULL */
//      pred->next = curr->next;
//      pthread_mutex_unlock(&(pred->mutex));
//      pthread_mutex_unlock(&(curr->mutex));
//      pthread_mutex_destroy(&(curr->mutex));
//      free(curr);
//    }
//  } else { /* Not in list */
//    if (pred != NULL)
//      pthread_mutex_unlock(&(pred->mutex));
//    if (curr != NULL)
//      pthread_mutex_unlock(&(curr->mutex));
//    if (curr == head)
//      pthread_mutex_unlock(&head_mutex);
//    rv = 0;
//  }
//
//  return rv;
//}  /* Delete */
//
//
//void* Thread_work(void* rank) {
//  long my_rank = (long) rank;
//  int i, val;
//  double which_op;
//  unsigned seed = my_rank + 1;
//  int my_member=0, my_insert=0, my_delete=0;
//  int ops_per_thread = total_ops/thread_count;
//
//  for (i = 0; i < ops_per_thread; i++) {
//    which_op = rand() % 10;
//    val = rand() % MAX_KEY;
//    if (which_op < search_p) {
//      Member(val);
//      my_member++;
//    } else if (which_op < search_p + insert_p) {
//      Insert(val);
//      my_insert++;
//    } else { /* delete */
//      Delete(val);
//      my_delete++;
//    }
//  }  /* for */
//  pthread_mutex_lock(&count_mutex);
//  member_total += my_member;
//  insert_total += my_insert;
//  delete_total += my_delete;
//  pthread_mutex_unlock(&count_mutex);
//  return NULL;
//}  /* Thread_work */


//#include <stdio.h>
//#include <stdlib.h>
//#include <pthread.h>
//#include <time.h>
//
//const int MAX_KEY = 100000000;
//int act_keys = 100;
//
//struct list_node_s {
//  int data;
//  struct list_node_s* next;
//  pthread_mutex_t mutex;
//};
//
//struct list_node_s* head = NULL;
//int thread_count;
//int total_ops;
//double insert_p;
//double search_p;
//double delete_p;
//pthread_mutex_t mutex;
//pthread_mutex_t count_mutex;
//int member_total=0, insert_total=0, delete_total=0;
//
///* Setup */
//void Usage(char* prog_name);
//void Get_input(int* inserts_in_main_p);
//
///* Thread function */
//void* Thread_work(void* rank);
//
///* List operations */
//int Insert(int value);
//void Print(void);
//int Member(int value);
//int Delete(int value);
//void Free_list(void);
//int Is_empty(void);
//
//int main(int argc, char* argv[]) {
//  long i;
//  int key, success, attempts;
//  pthread_t* thread_handles;
//  int inserts_in_main;
//  unsigned seed = 1;
//  double start, finish;
//  if (argc != 2) Usage(argv[0]);
//  thread_count = strtol(argv[1],NULL,10);
//  Get_input(&inserts_in_main);
//  i = attempts = 0;
//  while ( i < inserts_in_main && attempts < 2*inserts_in_main ) {
//    key = rand() % MAX_KEY;
//    success = Insert(key);
//    attempts++;
//    if (success) i++;
//  }
//  printf("Inserted %ld keys in empty list\n", i);
//  thread_handles = malloc(thread_count*sizeof(pthread_t));
//  pthread_mutex_init(&mutex, NULL);
//  pthread_mutex_init(&count_mutex, NULL);
//
//  clock_t t;
//  t = clock();
//
//  for (i = 0; i < thread_count; i++)
//    pthread_create(&thread_handles[i], NULL, Thread_work, (void*) i);
//
//  for (i = 0; i < thread_count; i++)
//    pthread_join(thread_handles[i], NULL);
//
//  t = clock() - t;
//  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
//
//  Print();
//  printf("Elapsed time = %e seconds\n", time_taken);
//  printf("Total ops = %d\n", total_ops);
//  printf("member ops = %d\n", member_total);
//  printf("insert ops = %d\n", insert_total);
//  printf("delete ops = %d\n", delete_total);
//  /* Free List and Threads */
//  Free_list();
//  pthread_mutex_destroy(&mutex);
//  pthread_mutex_destroy(&count_mutex);
//  free(thread_handles);
//  return 0;
//}  /* main */
//
//void Usage(char* prog_name) {
//  fprintf(stderr, "usage: %s <thread_count>\n", prog_name);
//  exit(0);
//}  /* Usage */
//
//void Get_input(int* inserts_in_main_p) {
//  printf("Keys: \n");
//  scanf("%d", inserts_in_main_p);
//  printf("Ops Number: \n");
//  scanf("%d", &total_ops);
//  printf("Percent of Ops in searches? (between 0 and 1)\n");
//  scanf("%lf", &search_p);
//  printf("Percent of Ops in inserts? (between 0 and 1)\n");
//  scanf("%lf", &insert_p);
//  delete_p = 1.0 - (search_p + insert_p);
//}  /* Get_input */
//
//int Insert(int value) {
//  struct list_node_s* curr = head;
//  struct list_node_s* pred = NULL;
//  struct list_node_s* temp;
//  int rv = 1;
//
//  while (curr != NULL && curr->data < value) {
//    pred = curr;
//    curr = curr->next;
//  }
//
//  if (curr == NULL || curr->data > value) {
//    temp = malloc(sizeof(struct list_node_s));
//    temp->data = value;
//    temp->next = curr;
//    if (pred == NULL)
//      head = temp;
//    else
//      pred->next = temp;
//  } else { /* value in list */
//    rv = 0;
//  }
//
//  return rv;
//}  /* Insert */
//
//void Print(void) {
//  struct list_node_s* temp;
//
//  printf("list = ");
//
//  temp = head;
//  while (temp != (struct list_node_s*) NULL) {
//    printf("%d ", temp->data);
//    temp = temp->next;
//  }
//  printf("\n");
//}  /* Print */
//
//int  Member(int value) {
//  struct list_node_s* temp;
//
//  temp = head;
//  while (temp != NULL && temp->data < value)
//    temp = temp->next;
//
//  if (temp == NULL || temp->data > value) {
//    return 0;
//  } else {
//    return 1;
//  }
//}  /* Member */
//
//int Delete(int value) {
//  struct list_node_s* curr = head;
//  struct list_node_s* pred = NULL;
//  int rv = 1;
//  while (curr != NULL && curr->data < value) {
//    pred = curr;
//    curr = curr->next;
//  }
//  if (curr != NULL && curr->data == value) {
//    if (pred == NULL) { /* first element in list */
//      head = curr->next;
//      free(curr);
//    } else {
//      pred->next = curr->next;
//      free(curr);
//    }
//  } else { /* Not in list */
//    rv = 0;
//  }
//  return rv;
//}  /* Delete */
//
//void Free_list(void) {
//  struct list_node_s* current;
//  struct list_node_s* following;
//
//  if (Is_empty()) return;
//  current = head;
//  following = current->next;
//  while (following != NULL) {
//    free(current);
//    current = following;
//    following = current->next;
//  }
//  free(current);
//}  /* Free_list */
//
//int  Is_empty(void) {
//  if (head == NULL)
//    return 1;
//  else
//    return 0;
//}  /* Is_empty */
//
//void* Thread_work(void* rank) {
//  long my_rank = (long) rank;
//  int i, val;
//  double which_op;
//  unsigned seed = my_rank + 1;
//  int my_member=0, my_insert=0, my_delete=0;
//  int ops_per_thread = total_ops/thread_count;
//
//  for (i = 0; i < ops_per_thread; i++) {
//    which_op = rand();
//    val = rand() % MAX_KEY;
//    if (which_op < search_p) {
//      pthread_mutex_lock(&mutex);
//      Member(val);
//      pthread_mutex_unlock(&mutex);
//      my_member++;
//    } else if (which_op < search_p + insert_p) {
//      pthread_mutex_lock(&mutex);
//      Insert(val);
//      pthread_mutex_unlock(&mutex);
//      my_insert++;
//    } else { /* delete */
//      pthread_mutex_lock(&mutex);
//      Delete(val);
//      pthread_mutex_unlock(&mutex);
//      my_delete++;
//    }
//  }  /* for */
//  pthread_mutex_lock(&count_mutex);
//  member_total += my_member;
//  insert_total += my_insert;
//  delete_total += my_delete;
//  pthread_mutex_unlock(&count_mutex);
//  return NULL;
//}  /* Thread_work */



//
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <pthread.h>
//
//struct list_node_s {
//  int data;
//  struct list_node_s* next;
////  pthread_mutex_t mutex;
//};
//
//struct list_node_s** head_p = NULL;
//struct pthread_mutex_t** head_p_mutex;
//
//int Member(int value) {
//  struct list_node_s* curr_p = *head_p;
//  while (curr_p != NULL && curr_p->data < value)
//    curr_p = curr_p->next;
//  if (curr_p == NULL || curr_p->data > value) {
//    return 0;
//  } else {
//    return 1;
//  }
//}
///* Member */
//
////void MemberThreads(int value) {
////  struct list_node_s* temp_p;
////  pthread_mutex_lock((pthread_mutex_t *) &head_p_mutex);
////  temp_p = (struct list_node_s *) head_p;
////  while (temp_p != NULL && temp_p->data < value) {
////    if (temp_p->next != NULL)
////      pthread_mutex_lock(&temp_p->next->mutex);
////    if (temp_p == *head_p)
////      pthread_mutex_unlock((pthread_mutex_t *) &head_p_mutex);
////    pthread_mutex_unlock(&temp_p->mutex);
////    temp_p = temp_p->next;
////  }
////}
/////* MemberPthreads */
//
//int Insert(int value) {
//  struct list_node_s* curr_p = *head_p;
//  struct list_node_s* pred_p = NULL;
//  struct list_node_s* temp_p;
//  while (curr_p != NULL && curr_p ->data < value) {
//    pred_p = curr_p;
//    curr_p = curr_p ->next;
//  }
//  if (curr_p == NULL || curr_p->data > value) {
//    temp_p = malloc(sizeof(struct list_node_s));
//    temp_p ->data = value;
//    temp_p ->next = curr_p;
//    if (pred_p == NULL) /* New first node */
//      *head_p = temp_p;
//    else
//      pred_p->next = temp_p;
//    return 1;
//  } else { /* Value already in list */
//    return 0;
//  }
//}
///* Insert */
//
//int Delete(int value) {
//  struct list_node_s* curr_p = *head_p;
//  struct list_node_s* pred_p = NULL;
//  while (curr_p != NULL && curr_p->data < value) {
//    pred_p = curr_p;
//    curr_p = curr_p->next;
//  }
//  if (curr_p != NULL && curr_p->data == value) {
//    if (pred_p == NULL) { /* Deleting first node in list */
//      *head_p = curr_p->next;
//      free(curr_p);
//    } else {
//      pred_p->next = curr_p->next;
//      free(curr_p);
//    }
//    return 1;
//  } else { /* Value isn’t in list */
//    return 0;
//  }
//}
///* Delete */
//
//void operarThreads() {
//  for (int i = 0; i < 99900; ++i) {
//    pthread_mutex_lock((pthread_mutex_t *) &head_p);
//    Member(i);
//    pthread_mutex_unlock((pthread_mutex_t *) &head_p);
//  }
//
//  for (int i = 0; i < 50; ++i) {
//    pthread_mutex_lock((pthread_mutex_t *) &head_p);
//    Insert(-i);
//    pthread_mutex_unlock((pthread_mutex_t *) &head_p);
//  }
//
//  for (int i = 0; i < 50; ++i) {
//    pthread_mutex_lock((pthread_mutex_t *) &head_p);
//    Delete(-i);
//    pthread_mutex_unlock((pthread_mutex_t *) &head_p);
//  }
//}
//
//int main() {
//  for (int i = 0; i < 1000; ++i) {
//    Insert(i);
//  }
//  // numero threads
//  int numThreads = 1;
//
//  pthread_t* thread_handles = malloc(numThreads*sizeof(pthread_t));
//
//  clock_t t;
//  t = clock();
//
//  for (int i = 0; i < numThreads; i++)
//    pthread_create(&thread_handles[i], NULL, (void *(*)(void *)) operarThreads, (void*) i);
//
//  for (int i = 0; i < numThreads; i++)
//    pthread_join(thread_handles[i], NULL);
//
//  t = clock() - t;
//  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
//
//  printf("fun() took %f seconds to execute \n", time_taken);
//  return 0;
//}
//
////int Member22(int value) {
////  struct list_node_s* temp_p;
////  pthread_mutex_t
////  pthread_mutex_lock(&head_p_mutex);
////  temp_p = head_p;
////  while (temp_p != NULL && temp_p->data < value) {
////    if (temp_p->next != NULL)
////    pthread_mutex_lock(&(temp_p->next->mutex));
////    if (temp_p == head_p)
////    pthread_mutex_unlock(&head_p_mutex);
////    pthread_mutex_unlock(&(temp_p->mutex));
////    temp_p = temp_p->next;
////  }
////}
////if (temp_p == NULL | | temp_p->data > value) {
////if (temp_p == head_p)
////pthread_mutex_unlock(&head_p_mutex);
////if (temp_p != NULL)
////pthread_mutex_unlock(&(temp_p->mutex));
////return 0;
////} else {
////if (temp_p == head_p)
////pthread_mutex_unlock(&head_p_mutex);
////pthread_mutex_unlock(&(temp_p->mutex));
////return 1;
////}
///* Member22 */
//
//
//
//
////void *Pth_mat_vect(void* rank) {
////long my_rank = (long) rank;
////int i, j;
////int local_m = m/thread_count;
////int my_first_row = my_rank*local_m;
////int my last row = (my_rank+1)*local_m − 1;
////}
////for (i = my_first_row; i <= my last row; i++) {
////y[i] = 0.0;
////for (j = 0; j < n; j++)
////y[i] += A[i][j]*x[j];
////}
////return NULL;
/////* Pth mat vect */
