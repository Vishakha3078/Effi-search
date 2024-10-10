#include<stdio.h>
#include<stdlib.h>

typedef unsigned char byte;
//arr[0] contains an element to search
//arr[1] contains counter
//arr[2] contains segment size 'k'
//arr[3] to arr[2050] contains m1
//arr[2051] to arr[1050626] contains m2

int compare(const void* a , const void* b){
	return (*(int*)a - *(int*)b);
}

int lsearch(int *arr,int start,int size,int e){
	int i;
	for (i = start; i < (start+size); i++){
		if (arr[i] == e)
			return i;
		else if (arr[i] > e && i == start)
			return -1;
		else if (arr[i] > e)
			return i-1;
	}
	return i-1;
}

int bisearch(int *arr,int low,int high,int e){
	while(low <= high){
		int mid = (low + high)/2;
		if (arr[mid] == e)
			return mid;
		else if (arr[mid] < e)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
} 

// 3 * t = start of minimums 
// (3 * t) + (k * t) = start of segment
// temp - m2 = end of m1 
// temp - m2 = start of m2 and temp -> end of m2
int main(){
        int temp;
        int m1,k,t,m2;// m1 -> primary memory , k -> number of parts of segment , t -> size taken by each value , m2 -> seondary memory
        printf("memory size : ");//in bytes
        scanf("%d\n",m2);
        printf("value size : ");//bytes required for one value
        scanf("%d\n",t);

        // m1 - kt = (m2 / k)
        //(k*k)t - (m1*k) + m2 = 0
        temp = (4 * m2) * t;
        m1 = pow(temp,0.5);

        k = m1 / (2 * t);
        temp = t+t+t+m1+m2;//size need to be malloced


	int *arr = (int*)malloc(1050627*sizeof(int));
	arr[2] = 1024;
	arr[0] = 456684546; 
	//inserting data into 'm2'
	FILE *fptr = fopen("data.txt","r");
	int n;
	arr[1] = 2051;
        while(fread(&arr[arr[1]],sizeof(int),1,fptr)){
                arr[1]++;
        }
        fclose(fptr);

	//sorting 'm2'
	qsort(arr + 2051,,t,compare);

	// inserting segment minimums in 'm1'
	n = 2051;
	for (arr[1] = 3; arr[1] < ( arr[2]+ 3); arr[1]++){
		arr[arr[1]] = arr[n];
		n += arr[2];
		
	}
	printf("e = %d\n", arr[1050626]);	
	//finding in minimums 	
	arr[1] = lsearch(arr,3,arr[2],arr[0]);
//	printf(" min = %d\n",arr[1]);
	if (arr[arr[1]] == arr[0])
		printf("element found at %d pos \n",arr[1]);
	else if (arr[1] == -1)
		printf("element not found\n");
	else{
		arr[1] = 2051 + ((arr[1] - 3)* arr[2]);
		//placing segment in 'm1'
		for( n = arr[2] + 3; n < 2051; n++)
			arr[n] = arr[arr[1]++];
		//finding in segment
		arr[1] = bisearch(arr,arr[2] + 3,2050,arr[0]);
		if (arr[1] != -1)
			printf("element found : %d\n",arr[arr[1]]);
		else
			printf("element not found\n");
	}		
}
