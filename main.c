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

void doToday(ToDo t){
  printf("%s  %d\n", t.title, t.hrs);
}

//오늘 일정 리스트 출력 기능
void todoRead(ToDo t){
        printf("%s  %d-%d-%d  %s  %d \n", t.title, t.year, t.month, t.days, t.day, t.hrs);
}

void listTodoByDeadline(ToDo *t, int index) {
  for (int i = 0; i < index - 1; i++) {
    for (int j = 0; j < index - 1; j++) {
      if (strcmp(t[j].day, t[j + 1].day) > 0) {
        ToDo temp = t[j];
        t[j] = t[j + 1];
        t[j + 1] = temp;
      }
    }
  }

  // 데드라인 가장 최근인 순으로 일정 출력
  printf("\n[Today Deadline]\n");
  char currentDeadLine[10];
  strcpy(currentDeadLine, t[0].day);
  for (int i = 0; i < index; i++) {
    if (strcmp(t[i].day, currentDeadLine) != 0) {
      printf("\n[데드라인 %s]\n", t[i].day);
      strcpy(currentDeadLine, t[i].day);
    }
    todoRead(t[i]);
  }
  printf("\n");
}

void listTodoToday(ToDo *t, int index) {
  printf("====================\n");
  printf("\n[ Do Today ]\n");
  for (int i = 0; i < index; i++) {
    if (t[i].check == -1) continue;
    if (t[i].hrs == 0) {
      todoRead(t[i]);
    }
  }
  printf("\n");
}

void listTodo(ToDo *t, int index) {
  listTodoByDeadline(t, index);
  listTodoToday(t, index);
}

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
    }
  }