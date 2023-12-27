#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 필요 상수 정의
#define WIDTH 512
#define HEIGHT 512
#define CON 20

// 필요 전역 변수 선언
unsigned char* img = NULL;
unsigned char* modified_img = NULL;
char *name = NULL;
char *path_in = NULL;
char *path_out = NULL;
int choice = 0;

// 필요 함수 선언
void file_input(void);
void file_output(int);
void memory_free(void);
void rot_90(void);
void rot_180(void);
void rot_270(void);
void symmetry(void);
void v_symmetry(void);
void choose(void);
void finish(void);

int main(void){
    choose(); // 1~5 선택 및 파일 입력
    file_output(choice); // 결과물 출력
    memory_free(); // 포인터 메모리 할당 해제
    finish(); // 프로그램 종료까지 대기
    return 0;
}

void file_input(void){
    img = (unsigned char*)malloc(sizeof(unsigned char)*WIDTH*HEIGHT);
    name = (char *)malloc(CON*sizeof(char));
    path_in = (char *)malloc(CON*sizeof(char));
    
    if(img == NULL || name == NULL || path_in == NULL){
        printf("ERROR OCCURED\n");
        return;
    }

    FILE* file_in = NULL;
    printf("enter file name without file extension: ");
    scanf("%s",name);
    
    strcpy(path_in, ".\\img\\");
    strcat(path_in,name);
    strcat(path_in,".img");

    file_in = fopen(path_in,"rb");
    fread(img, sizeof(unsigned char), WIDTH*HEIGHT, file_in);
    fclose(file_in);
    printf("file_input done!\n");
}
void file_output(int c){
    FILE* file_out = NULL;
    path_out = (char *)malloc(CON*sizeof(char));
    strcpy(path_out, ".\\out\\");
    strcat(path_out,name);
    // 경우에 따른 파일명 지정
    switch (c) {
        case 1:
            strcat(path_out, "_rot_90");
            break;
        case 2:
            strcat(path_out, "_rot_180");
            break;
        case 3:
            strcat(path_out, "_rot_270");
            break;
        case 4:
            strcat(path_out, "_symmetry");
            break;
        case 5:
            strcat(path_out, "_v_symmetry");
            break;   
        default:
            printf("Wrong Number. Program End.\n");
            break;
    }
    strcat(path_out,".img");
    file_out = fopen(path_out,"wb");
    fwrite(modified_img, sizeof(unsigned char), WIDTH*HEIGHT, file_out);
    fclose(file_out);
    printf("file_output done!\n");
}
void memory_free(void){
    free(img);
    free(name);
    free(modified_img);
    free(path_in);
    free(path_out);
    printf("memory_free done!\n");
    
}
void rot_90(void){
    modified_img = (unsigned char*)malloc(sizeof(unsigned char)*WIDTH*HEIGHT);
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            *(modified_img+i*HEIGHT+j) = *(img+i+WIDTH*(HEIGHT-(1+j)));
        }
    }
}
void rot_180(void){
    modified_img = (unsigned char*)malloc(sizeof(unsigned char)*WIDTH*HEIGHT);
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            *(modified_img+i*HEIGHT+j) = *(img+WIDTH*(HEIGHT-(1+i))-j);
        }
    }
}
void rot_270(void){
    modified_img = (unsigned char*)malloc(sizeof(unsigned char)*WIDTH*HEIGHT);
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            *(modified_img+i*HEIGHT+j) = *(img+WIDTH*(j+1)-(i+1));
        }
    }
}
void symmetry(void){
    modified_img = (unsigned char*)malloc(sizeof(unsigned char)*WIDTH*HEIGHT);
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            *(modified_img+i*HEIGHT+j) = *(img+(WIDTH-(1+j))+HEIGHT*i);
        }
    }
}
void v_symmetry(void){
    modified_img = (unsigned char*)malloc(sizeof(unsigned char)*WIDTH*HEIGHT);
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            *(modified_img+i*HEIGHT+j) = *(img+HEIGHT*(HEIGHT-(1+i))+j);
        }
    }
}
void choose(void) {
    printf("1. rotate 90 deg\t2. rotate 180 deg\t3. rotate 270 deg\t4. symmetry\t5. vertical symmetry\n");
    printf("choose the number: ");
    scanf("%d",&choice);
    
    switch (choice) {
        case 1:
            file_input();
            rot_90();
            break;
        case 2:
            file_input();
            rot_180();
            break;
        case 3:
            file_input();
            rot_270();
            break;
        case 4:
            file_input();
            symmetry();
            break;
        case 5:
            file_input();
            v_symmetry();
            break;   
        default:
            printf("Wrong Number. Program End.\n");
            break;
    }
}
void finish(void){
   printf("Press any key to exit...\n");
    fflush(stdout); // 출력 버퍼를 즉시 비우기 위해 사용
    while (getchar() == '\n'){} // 아무 입력이 있을 때까지 대기
    printf("Program exited.\n");
}