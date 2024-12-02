#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


struct boooks{
int id;
char bookName[50];
char autherName[50];
char date[12];
}b;

struct student{
int id;
char sName[50];
char sClass[50];
int sRoll;
char bookName[50];
char date[12];
}s;

FILE *fp;

int main(){

    int ch;

    while(1){
        system("cls");
        printf("Library Management System\n");
        printf("1. Add Books\n");
        printf("2. View Books\n");
        printf("3. Remove Books\n");
        printf("4. Issue Books\n");
        printf("5. View Issue Books\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

      switch (ch) {
    case 0:
        exit(0);

    case 1:
        addBooks();
        break;

    case 2:
        viewBookList();
        break;

    case 3:
        removeBook();
        break;

    case 4:
        issueBook();
        break;

    case 5:
        viewIssueBookList();
        break;

    default:
        printf("Invalid Choice");

}
printf("\n\n Press any key to continue: ");
getch();

}

return 0;
}
void addBooks(){
char myDate[12];
time_t t = time(NULL);
struct tm tm = *localtime(&t);
sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
strcpy(b.date, myDate);

fp = fopen("books.txt", "ab");

printf("Enter Book id: ");
scanf("%d", &b.id);

printf("Enter Book Name: ");
fflush(stdin);
gets(b.bookName);

printf("Enter Auther Name: ");
fflush(stdin);
gets(b.autherName);

printf("Book Added Succesfully");

fwrite(&b, sizeof(b), 1, fp);
fclose(fp);
}

void viewBookList(){
    system("cls");
    printf("Available Book\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");
    fp = fopen("books.txt", "rb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.autherName, b.date);
    }
fclose(fp);
}

void removeBook(){
int id, f=0;
system("cls");
printf("Remove Book\n\n");
printf("Enter id to remove Book");
scanf("%d", &id);

FILE *ft;

fp = fopen("books.txt", "rb");
ft = fopen("tmp.txt", "wb");

while(fread(&b, sizeof(b), 1, fp) == 1){
    if (id==b.id){
        f=1;

    }else{
        fwrite(&b, sizeof(b), 1, ft);
    }

}
if (f==1){
    printf("\n\n Book Deleted Successful");
}
else{
    printf("\n\n  Not found book");
}
fclose(fp);
fclose(ft);

remove("books.txt");
rename("tmp.txt", "books.txt");
}

void issueBook(){
char myDate[12];
time_t t = time(NULL);
struct tm tm = *localtime(&t);
sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
strcpy(s.date, myDate);
    int f = 0;
    system("cls");
    printf("Book Issue");
    printf("Enter Book Id U want");
    scanf("%d", &s.id);

    fp = fopen("books.txt", "rb");

    while(fread(&b, sizeof(b), 1, fp) == 1) {
        if(b.id == s.id){
            strcpy(s.bookName, b.bookName);
            f = 1;
            break;
        }
    }
    if (f==0){
        printf("No Book found this id");
        return;
    }
    fp = fopen("issue.txt", "ab");
    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter Student Class: ");
    fflush(stdin);
    gets(s.sClass);

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}

void viewIssueBookList(){
    system("cls");
    printf("Issue Book List\n");
    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "S.id", "Name", "Class", "Roll", "Date");
    fp = fopen("Issue.txt", "rb");

    while(fread(&s, sizeof(s), 1, fp) == 1){
           printf("%-10d %-30s %-20s %-10s %-30s %s\n\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }
fclose(fp);



}


