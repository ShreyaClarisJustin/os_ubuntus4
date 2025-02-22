#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUCKET_SIZE 10 // Maximum bucket size
#define OUT_RATE 1 // Rate at which tokens leave the bucket
int main(){
	int incoming,bucket=0;
	while(1){
		printf("\nEnter the number of packets coming at second %d: ", bucket + 1);
		scanf("%d", &incoming);
		if(incoming>BUCKET_SIZE) {
			printf("Bucket overflow\n");
		}
		else{
			if(incoming + bucket > BUCKET_SIZE) {
				printf("Packet loss: %d packets discarded\n", incoming + bucket - BUCKET_SIZE);
				bucket = BUCKET_SIZE;
			}
			else {
				bucket += incoming;
			}
			printf("Bucket size: %d\n", bucket);
			if (bucket > OUT_RATE) {
				printf("%d packets sent out at second %d\n", OUT_RATE, bucket);
				bucket -= OUT_RATE;
			}
			else{
				printf("Bucket is empty\n");
			}
		}
		sleep(1); // Simulate one second delay
	}
return 0;
}
