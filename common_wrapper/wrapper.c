#include <stdio.h>
#include <stdlib.h>

int main(){
    int choice;
    
    while(1){
        printf("........ CS509 Common Wrapper ........\n");
    printf("1. GEMM Assignment\n");
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
            system("gcc -o ../assignment_01/driver/main ../assignment_01/src/matrix.c ../assignment_01/driver/main.c");
        }
        else if(action==2){
            system("../assignment_01/driver/main ../assignment_01/tests/test1.txt 32");
        }
        else if(action==3){
            system("../assignment_01/driver/main ../assignment_01/tests/test2.txt 32");
        }
        else if(action==4){
            system("../assignment_01/driver/main ../assignment_01/tests/test3.txt 32");
        }
        else if(action==5){
            system("../assignment_01/driver/main ../assignment_01/tests/test4.txt 32");
        }
        else if(action==6){
            system("../assignment_01/driver/main ../assignment_01/tests/test1.txt 32");
            system("../assignment_01/driver/main ../assignment_01/tests/test2.txt 32");
            system("../assignment_01/driver/main ../assignment_01/tests/test3.txt 32");
            system("../assignment_01/driver/main ../assignment_01/tests/test4.txt 32");
        }
        else{
            printf("Invalid action\n");
        }
    }
    else{
        printf("Invalid input\n");
    }
    }

    printf("........ CS509 Common Wrapper ........\n");
    return 0;
}