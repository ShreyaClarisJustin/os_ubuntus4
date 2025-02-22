#include <stdio.h>
#include <unistd.h>
int main() {

 int n, incoming, outgoing, store = 0, bucketsize;
 printf("Enter the bucket size: ");
 scanf("%d", &bucketsize);
 printf("Enter the outgoing rate: ");
 scanf("%d", &outgoing);
 printf("Enter the number of inputs: ");
 scanf("%d", &n);
 while (n > 0) {
	printf("\nEnter the incoming size: ");
	scanf("%d", &incoming);
	printf("\nIncoming size is %d\n", incoming);
	if(incoming <= (bucketsize - store)) {
		store += incoming;
		printf("Bucket buffer size is %d out of %d\n", store, bucketsize);
	} 
 	else{
		printf("packet loss = %d\n", incoming - (bucketsize - store));
		store = bucketsize;
		printf("Buffer is full\n");
	}
	while(store>=outgoing){
		store -= outgoing;
 	}
	printf(" after outgoing %d packets are left out of %d in the buffer\n", store, bucketsize);
 	n--;
 }
 return 0;
}
