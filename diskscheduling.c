#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

#define INT_SIZE 4
#define INT_COUNT 20
#define MEMORY_SIZE INT_COUNT * INT_SIZE

int intArray[INT_COUNT];
signed char *mmapfptr;
int get_bin(){
        //gets an array of numbers we can work with instead of bytes in a binary file
        int mmapfile_fd = open("request.bin", O_RDONLY);
        mmapfptr = mmap(0,MEMORY_SIZE,PROT_READ,MAP_PRIVATE,mmapfile_fd,0);
        for (int i = 0; i < INT_COUNT; i++){
                memcpy(intArray+i,mmapfptr+ i * 4,INT_SIZE);
        }
        return 0;
}


int fcfs(int intArray[], int head){
        
        int sum = 0;
        
        printf("FCFS DISK SCHEDULING ALGORITHM:\n\n");

        for (int i = 0; i < INT_COUNT; i++){
                if (i == 19) {
                        printf("%d\n", intArray[i]);
                }
                else {
                        printf("%d, ", intArray[i]);
                }
                
                sum += abs(head - intArray[i]);
                head = intArray[i];
        }
        printf("\nFCFS - Total head movements = %d\n\n", sum);
}


int closestnext(int intArray[],int head){
        int furthest = 301;
        int closest = 0;
        for (int i = 0; i < INT_COUNT; i++){
                int current = intArray[i];
                if ( (abs(head - current) < furthest) && (head-current != 0 ) ){
                        furthest = abs(head - current);
                        closest = current;
                }

        }
        return closest;
}
int findindex(int intArray[],int num){
        for (int i = 0; i < INT_COUNT; i++){
                if (intArray[i] == num){
                        return i;
                }
        }
}

int sstf(int intArray[], int head){
        printf("SSTF DISK SCHEDULING ALGORITHM\n\n");
        int sum = 0;
        int intArray2[INT_COUNT];
        for (int i = 0; i < INT_COUNT; i++){
                intArray2[i] = intArray[i];
        }
        int starting = head;
        for (int i = 0; i < INT_COUNT; i++){
                if (i < 19){
                        printf("%d, ",starting);
                        sum = sum + (abs(starting - closestnext(intArray2,starting)));
                        int location = findindex(intArray2,starting);
                        intArray2[location] = 1000;
                        starting = closestnext(intArray2,starting);
                }
                else {
                        printf("%d",starting);
                }
        }
        printf("\n\nSSTF - Total head movements = %d \n\n",sum);
}

int sortingHelper(int intArray[]){
        int temp = 0;

	for (int i = 0; i < INT_COUNT; ++i) {
       	        for (int j = i + 1; j < INT_COUNT; ++j) {
                        if (intArray[i] > intArray[j]) {
                                temp = intArray[i];
                                intArray[i] = intArray[j];
                                intArray[j] = temp;
                        }
                }
        }
}

int scan(int intArray[], int head, char direction[]){


        int sum = 0;
        char right[] = "RIGHT";
        char left[] = "LEFT";
        int index = -1;

        printf("SCAN DISK SCHEDULING ALGORITHM\n\n");

        sortingHelper(intArray);

        int returningArray[INT_COUNT];

        for (int i = 0; i < INT_COUNT; i++) {
                if (intArray[i] == head)
                {
                        index = i;
                        break;
                }
        }

        printf("%d, ", head);
        if (strcmp(direction, right) == 0){
                for (int i = index + 1; i < INT_COUNT; i++){
                        //returningArray[i - index] = intArray[i]
                        sum += abs(head - intArray[i]);
                        printf("%d, ", intArray[i]);
                        head = intArray[i];
                }
                sum += 2*abs(299 - intArray[19]);
                for (int i = index - 1; i >= 0; i--){
                        sum += abs(head - intArray[i]);
                        if (i == 0) {
                                printf("%d\n", intArray[i]);
                        }
                        else {
                                printf("%d, ", intArray[i]);
                        }
                        
                        head = intArray[i]; 
                }
        }
        else if (strcmp(direction, left) == 0){
                for (int i = index - 1; i >= 0; i--){
                        //returningArray[i - index] = intArray[i]
                        sum += abs(head - intArray[i]);
                        printf("%d, ", intArray[i]);
                        head = intArray[i];
                }
                sum += 2*abs(intArray[0]);
                for (int i = index + 1; i < INT_COUNT; i++){
                        sum += abs(head - intArray[i]);
                        if (i == INT_COUNT - 1){
                                printf("%d\n", intArray[i]);
                        }
                        else {
                                printf("%d, ", intArray[i]);
                        }
                        
                        head = intArray[i]; 
                }
        } 
        printf("\nSCAN - Total head movements = %d\n\n", sum);
}

int cscan(int intArray[], int head, char direction[]){


        int sum = 0;
        char right[] = "RIGHT";
        char left[] = "LEFT";
        int index = -1;

        printf("C-SCAN DISK SCHEDULING ALGORITHM\n\n");

        sortingHelper(intArray);

        for (int i = 0; i < INT_COUNT; i++) {
                if (intArray[i] == head)
                {
                        index = i;
                        break;
                }
        }


        printf("%d, ", head);
        if (strcmp(direction, right) == 0){
                for (int i = index + 1; i < INT_COUNT; i++){
                        sum += abs(head - intArray[i]);
                        printf("%d, ", intArray[i]);
                        head = intArray[i];
                }
                sum += 2*(299 - intArray[19]);
                for (int i = 0; i <= index - 1; i++){
                        sum += abs(head - intArray[i]);
                        if (i == index - 1) {
                                printf("%d\n", intArray[i]);
                        }
                        else {
                                printf("%d, ", intArray[i]);
                        }
                        
                        head = intArray[i]; 
                }
                sum += 2*(intArray[0]);
        }
        else if (strcmp(direction, left) == 0){
                for (int i = index - 1; i >= 0; i--){
                        sum += abs(head - intArray[i]);
                        printf("%d, ", intArray[i]);
                        head = intArray[i];
                }
                sum += 2*(intArray[0]);
                for (int i = INT_COUNT - 1; i > index; i --){
                        sum += abs(head - intArray[i]);
                        if (i == index + 1){
                                printf("%d\n", intArray[i]);
                        }
                        else {
                                printf("%d, ", intArray[i]);
                        }
                        
                        head = intArray[i]; 
                }
                sum += 2*(299 - intArray[19]);
        } 
        printf("\nC-SCAN - Total head movements = %d\n\n", sum);
}

int look(int intArray[], int head, char direction[]){


        int sum = 0;
        char right[] = "RIGHT";
        char left[] = "LEFT";
        int index = -1;

        printf("LOOK DISK SCHEDULING ALGORITHM\n\n");

        sortingHelper(intArray);

        int returningArray[INT_COUNT];

        for (int i = 0; i < INT_COUNT; i++) {
                if (intArray[i] == head)
                {
                        index = i;
                        break;
                }
        }


        printf("%d, ", head);
        if (strcmp(direction, right) == 0){
                for (int i = index + 1; i < INT_COUNT; i++){
                        //returningArray[i - index] = intArray[i]
                        sum += abs(head - intArray[i]);
                        printf("%d, ", intArray[i]);
                        head = intArray[i];
                }
                for (int i = index - 1; i >= 0; i--){
                        sum += abs(head - intArray[i]);
                        if (i == 0) {
                                printf("%d\n", intArray[i]);
                        }
                        else {
                                printf("%d, ", intArray[i]);
                        }
                        head = intArray[i]; 
                }
        }
        else if (strcmp(direction, left) == 0){
                for (int i = index - 1; i >= 0; i--){
                        //returningArray[i - index] = intArray[i]
                        sum += abs(head - intArray[i]);
                        printf("%d, ", intArray[i]);
                        head = intArray[i];
                }
                for (int i = index + 1; i < INT_COUNT; i++){
                        sum += abs(head - intArray[i]);
                        if (i == INT_COUNT - 1){
                                printf("%d\n", intArray[i]);
                        }
                        else {
                                printf("%d, ", intArray[i]);
                        }
                        head = intArray[i]; 
                }
        } 

        printf("\nLOOK - Total head movements = %d\n\n", sum);
}

int clook(int intArray[], int head, char direction[]){


        int sum = 0;
        char right[] = "RIGHT";
        char left[] = "LEFT";
        int index = -1;

        printf("C-LOOK DISK SCHEDULING ALGORITHM\n\n");

        sortingHelper(intArray);

        int returningArray[INT_COUNT];

        for (int i = 0; i < INT_COUNT; i++) {
                if (intArray[i] == head)
                {
                        index = i;
                        break;
                }
        }

        printf("%d, ", head);
        if (strcmp(direction, right) == 0){
                for (int i = index + 1; i < INT_COUNT; i++){
                        //returningArray[i - index] = intArray[i]
                        sum += abs(head - intArray[i]);
                        printf("%d, ", intArray[i]);
                        head = intArray[i];
                }
                for (int i = 0; i <= index - 1; i++){
                        sum += abs(head - intArray[i]);
                        if (i == index - 1) {
                                printf("%d\n", intArray[i]);
                        }
                        else {
                                printf("%d, ", intArray[i]);
                        }
                        
                        head = intArray[i]; 
                }
        }
        else if (strcmp(direction, left) == 0){
                for (int i = index - 1; i >= 0; i--){
                        sum += abs(head - intArray[i]);
                        printf("%d, ", intArray[i]);
                        head = intArray[i];
                }
                for (int i = INT_COUNT - 1; i > index; i --){
                        sum += abs(head - intArray[i]);
                        if (i == index + 1){
                                printf("%d\n", intArray[i]);
                        }
                        else {
                                printf("%d, ", intArray[i]);
                        }
                        
                        head = intArray[i]; 
                }
        } 

        printf("\nC-LOOK - Total head movements = %d\n", sum);
}


int main(int argc, char *argv[]){
        get_bin();
        printf("Total requests = %d\n", INT_COUNT);
        printf("Initial Head Position: %d\n", atoi(argv[1]));
        printf("Direction of Head: %s\n\n", argv[2]);

        fcfs(intArray, atoi(argv[1]));
        sstf(intArray, atoi(argv[1]));
        scan(intArray, atoi(argv[1]), argv[2]);
        cscan(intArray, atoi(argv[1]), argv[2]);
        look(intArray, atoi(argv[1]), argv[2]);
        clook(intArray, atoi(argv[1]), argv[2]);
        
        return 0;
}
