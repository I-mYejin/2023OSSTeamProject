#include <stdio.h>
#include <string.h>
typedef struct {
    char title[100]; //ex) OSS Lab11
    //char deadline[20]; //ex) 2023-05-08
    int year;
    int month;
    int days;
    char day[10]; // ex) Mon
    int hrs; //ex) 4(예상 소요 시간)
    int check; // ex) 0, 1(완료하면 1 입력받아서 √표시)
} ToDo;

//은다
int selectMenu();
int completeTodo(ToDo *t);
void saveData(ToDo *t, int count);
int loadData(ToDo *t);
int addTodo(ToDo *t); //일정 추가
int updateTodo(ToDo *t); //일정 수정: return addTodo()

//예진
int selectDataNo(ToDo *t, int count);
int addTodoByDay(ToDo *t[], int *index, int *count);
int deleteTodo(ToDo *t); //일정 삭제
void todoRead(ToDo t); //일정 리스트 출력
int listTodo(ToDo *t, int count);

//todo.c
int selectMenu(){
    int menu;
    printf("\n\n *** 1Jung *** \n");
    printf("0. 종료\n\n");
    printf("1. 일정 조회\n"); //일정 리스트 출력 + 일정완료 체크표시
    printf("2. 일정 추가\n");
    printf("3. 일정 수정\n");
    printf("4. 일정 삭제\n");
    printf("5. 파일 저장\n");
    printf("6. 파일 불러오기\n");
    printf("7. 일정 추가(요일별)\n");
    printf("8. 일정 완료\n");
    printf("Select Menu: ");
    scanf("%d", &menu);
    return menu;   
}

//일정 완료 기능
int completeTodo(ToDo *t){
  t->check = 1;
  return 1;
}

//일정 추가 기능
int addTodo(ToDo *t){
  int repeat;
  int repeatDeadlineYear;
  int repeatDeadlineMonth;
  int repeatDeadlineDays;
  int repeatDays;
  
  int firstrepeatDeadlineYear;
  int firstrepeatDeadlineMonth;
  int firstrepeatDeadlineDays;

  char repeatday[10];

//   int currentYear;
//   int currentMonth;
//   int currentDays;
  
  char title[100];
  int hrs;

  printf("1. 단순 추가 2. 반복 추가 >> ");
  scanf("%d", &repeat);
  if(repeat == 2){
    printf("반복 요일 (Mon, Tues, Wed, Thurs, Fri, Sat, Sun): ");
    scanf("%s", repeatday);
    printf("first date to add Todo (Year) >> ");
    scanf("%d", &firstrepeatDeadlineYear);
    printf("first date to add Todo (Month) >> ");
    scanf("%d", &firstrepeatDeadlineMonth);
    printf("first date to add Todo (Days) >> ");
    scanf("%d", &firstrepeatDeadlineDays);

    printf("last date to add Todo (Year) >> "); //반복 일정을 추가할 마지막 날짜
    scanf("%d", &repeatDeadlineYear);
    printf("last date to add Todo (Month) >> "); //반복 일정을 추가할 마지막 날짜
    scanf("%d", &repeatDeadlineMonth);
    printf("last date to add Todo (Days) >> "); //반복 일정을 추가할 마지막 날짜
    scanf("%d", &repeatDeadlineDays);
    
    printf("Title: ");
        getchar();
        scanf("%[^\ns]", title);
        getchar();
        // printf("Deadline(format: after * days): ");
        // scanf("%d", &repeatDays);
        printf("Estimated time to complete(hrs): ");
        scanf("%d", &hrs);
        printf("=> 새로운 반복 일정이 추가되었습니다!");
        return 1;


    while((firstrepeatDeadlineYear!= repeatDeadlineYear) && (firstrepeatDeadlineMonth!= repeatDeadlineMonth) && (firstrepeatDeadlineDays != repeatDeadlineDays)){
        strcpy(t->title,title);
        t->year = firstrepeatDeadlineYear;
        t->month = firstrepeatDeadlineMonth;
        t->days = firstrepeatDeadlineDays;
        strcpy(t->day,repeatday);
        t->hrs = hrs;
        printf("=> 새로운 반복 일정이 추가되었습니다!");
        firstrepeatDeadlineDays += 7;
        return 1;
    }
  }
  else{
    printf("Title: ");
    getchar();
    scanf("%[^\ns]", t->title);
    getchar();
    // printf("Deadline(format: 20XX-XX-XX): ");
    // scanf("%s", t->deadline);
    printf("Deadline 년 (ex) 2023): ");
    scanf("%d", &t->year);
    printf("Deadline 월(ex) 5): ");
    scanf("%d", &t->month);
    printf("Deadline 일(ex) 21): ");
    scanf("%d", &t->days);
    printf("요일(Mon, Tues, Wed, Thurs, Fri, Sat, Sun): ");
    scanf("%s", t->day);
    printf("Estimated time to complete(hrs): ");
    scanf("%d", &t->hrs);
    
    return 1;
  }
}
//미완성
void saveData(ToDo *t, int count){
    FILE *fp;
    char filename[20];
    printf("저장할 파일 이름: ");
    scanf("%s", filename);

    fp = fopen(filename, "wt");
    printf("\nNo Title Deadline Day Hours Finish\n");
    
    for(int i=0; i<count; i++){
        if(t[i].hrs == -1) continue;
        fprintf(fp, "%2d %s %d-%d-%d %s %d %d\n", i+1, t[i].title, t[i].year, t[i].month, t[i].days, t[i].day, t[i].hrs, t[i].check);
    }
    fclose(fp);
    printf("=> %s 파일에 저장됨! \n",filename);

}
//미완성
int loadData(ToDo *t){
    int i, count = 0;
    FILE *fp;
    char filename[20];
    printf("불러올 파일 이름: ");
    scanf("%s", filename);
    
    fp=fopen(filename, "rt");
    if(fp == NULL){
        printf("=> 파일 없음! \n");
        return 0;
    }
    for(i=0; i<100; i++){
        fscanf(fp, "%s", t[i].title);
        if(feof(fp)) break;
        //fscanf(fp, "%s", t[i].deadline);
        fscanf(fp, "%s", t[i].day);
        fscanf(fp, "%d", &t[i].hrs);
    }
    fclose(fp);
    printf("=> %s 파일 로딩 성공!\n", filename);
    return i; //총 몇개의 데이탄지 리턴

}

int updateTodo(ToDo *t){
    return addTodo(t);
    }

int selectDataNo(ToDo *t, int count){
    int no;
    listTodo(t, count);
    printf("번호는?");
    scanf("%d", &no);
    return no;
}

// //일정 삭제 기능
// int deleteTodo(ToDo *t){
//     t->check = -1;
//     return 1;
// }


//일정 리스트 출력 기능
void todoRead(ToDo t){
    printf("%s  %d-%d-%d  %s  %d \n", t.title, t.year, t.month, t.days, t.day, t.hrs);
}

int listTodo(ToDo *t, int count){
    printf("\nNo    Title   Deadline    Day     Hours   Finish\n");
    printf("====================================================\n");
    for(int i=0; i<count; i++){
        if(t[i].check == -1) continue;
        printf("%2d    ", i+1);
        todoRead(t[i]);
        //일정완료 체크표시
        if(t[i].check == 1){ 
            printf("  √\n");
        } else {
            printf(" ");
        }
    }
    printf("\n");
    return 1;
}

//일정 추가 기능 (요일별로)
// void addTodoByDay(ToDo *t[], int *index, int *count) {
//   int dayMenu;
//   printf("요일을 선택하세요:\n");
//   printf("1. 월요일\n");
//   printf("2. 화요일\n");
//   printf("3. 수요일\n");
//   printf("4. 목요일\n");
//   printf("5. 금요일\n");
//   printf("6. 토요일\n");
//   printf("7. 일요일\n");
//   printf("Select Day: ");
//   scanf("%d", &dayMenu);

//   if (dayMenu < 1 || dayMenu > 7) {
//     printf("잘못된 선택입니다.\n");
//     return;
//   }
//     char day[10];
//   switch (dayMenu) {
//     case 1:
//       strcpy(day, "Mon");
//       break;
//     case 2:
//       strcpy(day, "Tue");
//       break;
//     case 3:
//       strcpy(day, "Wed");
//       break;
//     case 4:
//       strcpy(day, "Thu");
//       break;
//     case 5:
//       strcpy(day, "Fri");
//       break;
//     case 6:
//       strcpy(day, "Sat");
//       break;
//     case 7:
//       strcpy(day, "Sun");
//       break;
//   }

//   printf("Title: ");
//   scanf("%s", t[*index]->title);
//   printf("Deadline (format: 20XX-XX-XX): ");
//   scanf("%s", t[*index]->deadline);
//   strcpy(t[*index]->day, day);
//   printf("Estimated time to complete (hrs): ");
//   scanf("%d", &t[*index]->hrs);
//   t[*index]->check = 0;

//   printf("=> 새로운 일정이 추가되었습니다!\n");
//   (*index)++;
//   (*count)++;
// }

//main.c
int main(void) {
  ToDo t[100];
  int count = 0;
  int index = 0;
  int menu;

  while(1){
    menu = selectMenu();
    if(menu == 0) {
      printf("Bye!\n");
      break;
    }
    
    else if (menu == 1) { //일정 조회
      if(count > 0) {
        listTodo(t, index);
      }
    }
    
    else if(menu == 2){ //일정 추가
      count += 1;
      addTodo(&t[index++]);
      printf("=> 새로운 일정이 추가되었습니다!\n");

    }
    else if (menu == 3){ //일정 수정
      updateTodo(t);

    }
    else if (menu == 4){ //일정 삭제
      //int no = selectDataNo(t, index);
      // int deleteok;
      // printf("정말로 삭제하시겠습니까?(삭제:1)");
      // scanf("%d", &deleteok);
      // if (deleteok == 1){
      //   if (&t[no -1] == NULL) count--;
      // }
    }
            
    else if (menu == 5){ //파일 저장
      saveData(t, index);

    }
    else if(menu == 6){ //파일 불러오기
      loadData(t);
        
    }

    else if (menu == 7){ //요일별 일정 추가
      //addTodoByDay(t, &index, &count);
    }
    else if (menu == 8){ //완료 표시 기능
      int no = selectDataNo(t, index);
      int completeok;
      printf("완료하셨나요? (완료: 1, 취소: 0)");
      scanf("%d", &completeok);
      if(completeok == 1){
        completeTodo(&t[no-1]);
        printf("=> 일정 완료!\n");
      }
      else{
        printf("=> 취소됨! \n");
      }
      

    }

  }
}

