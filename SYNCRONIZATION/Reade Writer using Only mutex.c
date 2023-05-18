/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t wr,mutex;
int a=10,readcount=0;

void * reader(void *arg){
    long int num;
    num=(long int)arg;
    pthread_mutex_lock(&mutex);
        readcount++;
    pthread_mutex_unlock(&mutex);
    
    if(readcount==1){
        pthread_mutex_lock(&wr);
        
    }
    printf("\n Reader %ld is in critical section ",num);
    printf("\n Reader %ld is reading data %d ",num,a);
    sleep(1);
    pthread_mutex_lock(&mutex);
    readcount--;
    pthread_mutex_unlock(&mutex);
    
    if(readcount==0){
        pthread_mutex_unlock(&wr);
    }
    printf("\n Reader %ld left critical section",num);
    
    
}
void* writer (void *arg){
    long int num;
    num=(long int) arg;
    
    //lock wr variable tu enter case
    pthread_mutex_lock(&wr);
    printf("\n Writer %ld is in critical section ",num);
    printf("\n Writer %ld have written data as  %d ",num,++a);
    sleep(1);
    pthread_mutex_unlock(&wr);
    printf("\n Writer %ld left critical section",num);
    
}

int main()
{
    pthread_t r[10],w[10];
    int i,j,nor,now;
    
    //initialize mutex variables
    pthread_mutex_init(&wr,NULL);
    pthread_mutex_init(&mutex,NULL);
    
    //read input data
    printf("Enter number of reader and writers :");
    scanf("%d %d",&nor,&now);
    
    //Creating reader and writer threads
    for(int i=1;i<=nor;i++){
        pthread_create(&r[i],NULL,reader,(void *)i);
        
    }
    for(int j=1;j<=nor;j++){
        pthread_create(&w[j],NULL,writer,(void *)j);
        
    }
    //join the threads 
    for(i=0;i<nor;i++){
        pthread_join(r[i],NULL);
        
    }for(j=0;j<now;j++){
        pthread_join(w[j],NULL);
        
    }
    return 0;
}

