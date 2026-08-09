#include <stdio.h>
#include <stdlib.h>

int main(){
    int choice;

    while(1){
        printf("........ CS509 Common Wrapper ........\n");
        printf("1. GEMM Assignment\n");
        printf("2. Shortest Path Assignment\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        if(choice==0){
            return 0;
        }

        if(choice==1){
            printf("1. Compile\n");
            printf("2. Run test1\n");
            printf("3. Run test2\n");
            printf("4. Run test3\n");
            printf("5. Run test4\n");
            printf("6. Run all tests\n");
            printf("Select an option: ");
            int action;
            scanf("%d", &action);

            if(action==1){
                system("gcc -o ..\\assignment_01\\driver\\main.exe ..\\assignment_01\\src\\matrix.c ..\\assignment_01\\driver\\main.c");
            }
            else if(action==2){
                system("..\\assignment_01\\driver\\main.exe ..\\assignment_01\\tests\\test1.txt 32");
            }
            else if(action==3){
                system("..\\assignment_01\\driver\\main.exe ..\\assignment_01\\tests\\test2.txt 32");
            }
            else if(action==4){
                system("..\\assignment_01\\driver\\main.exe ..\\assignment_01\\tests\\test3.txt 32");
            }
            else if(action==5){
                system("..\\assignment_01\\driver\\main.exe ..\\assignment_01\\tests\\test4.txt 32");
            }
            else if(action==6){
                system("..\\assignment_01\\driver\\main.exe ..\\assignment_01\\tests\\test1.txt 32");
                system("..\\assignment_01\\driver\\main.exe ..\\assignment_01\\tests\\test2.txt 32");
                system("..\\assignment_01\\driver\\main.exe ..\\assignment_01\\tests\\test3.txt 32");
                system("..\\assignment_01\\driver\\main.exe ..\\assignment_01\\tests\\test4.txt 32");
            }
            else{
                printf("Invalid action\n");
            }
        }
        else if(choice==2){
            printf("1. Compile\n");
            printf("2. Run Bellman-Ford tests\n");
            printf("3. Run Floyd-Warshall tests\n");
            printf("Select an option: ");
            int action;
            scanf("%d", &action);

            if(action==1){
                system("g++ -std=c++17 -O2 -o ..\\assignment_02\\driver\\main.exe ..\\assignment_02\\src\\csr_bridge.cpp ..\\assignment_02\\src\\bellmanFord.cpp ..\\assignment_02\\src\\flloydWarshall.cpp ..\\assignment_02\\driver\\main.cpp");
            }
            else if(action==2){
                system("..\\assignment_02\\driver\\main.exe bf ..\\assignment_02\\tests\\bf_1.txt > ..\\assignment_02\\outputs\\bf_1_out.txt");
                system("..\\assignment_02\\driver\\main.exe bf ..\\assignment_02\\tests\\bf_10.txt > ..\\assignment_02\\outputs\\bf_10_out.txt");
                system("..\\assignment_02\\driver\\main.exe bf ..\\assignment_02\\tests\\bf_100.txt > ..\\assignment_02\\outputs\\bf_100_out.txt");
                system("..\\assignment_02\\driver\\main.exe bf ..\\assignment_02\\tests\\bf_10000.txt > ..\\assignment_02\\outputs\\bf_10000_out.txt");
                system("..\\assignment_02\\driver\\main.exe bf ..\\assignment_02\\tests\\bf_50000.txt > ..\\assignment_02\\outputs\\bf_50000_out.txt");
                system("..\\assignment_02\\driver\\main.exe bf ..\\assignment_02\\tests\\bf_100000.txt > ..\\assignment_02\\outputs\\bf_100000_out.txt");
            }
            else if(action==3){
                system("..\\assignment_02\\driver\\main.exe fw ..\\assignment_02\\tests\\fw_1.txt > ..\\assignment_02\\outputs\\fw_1_out.txt");
                system("..\\assignment_02\\driver\\main.exe fw ..\\assignment_02\\tests\\fw_10.txt > ..\\assignment_02\\outputs\\fw_10_out.txt");
                system("..\\assignment_02\\driver\\main.exe fw ..\\assignment_02\\tests\\fw_100.txt > ..\\assignment_02\\outputs\\fw_100_out.txt");
                system("..\\assignment_02\\driver\\main.exe fw ..\\assignment_02\\tests\\fw_500.txt > ..\\assignment_02\\outputs\\fw_500_out.txt");
                system("..\\assignment_02\\driver\\main.exe fw ..\\assignment_02\\tests\\fw_1000.txt > ..\\assignment_02\\outputs\\fw_1000_out.txt");
                system("..\\assignment_02\\driver\\main.exe fw ..\\assignment_02\\tests\\fw_2000.txt > ..\\assignment_02\\outputs\\fw_2000_out.txt");
            }
            else{
                printf("Invalid input\n");
            }
        }
        else{
            printf("Invalid input\n");
        }
    }

    printf("........ CS509 Common Wrapper ........\n");
    return 0;
}