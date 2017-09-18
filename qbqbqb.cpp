#include"graph.h"
#include "windows.h"
int Dijkstra(Map& map, int path[], char a[20], char b[20], int num);
int Dijkstra_time(Map& map, int path[], char a[20], char b[20], int num);
void gotoxy(int x, int y);
void SetColor(int color);
void printmain();
void printFR();
void printwall(int a, int n);
void latest();
void jeol();
bool FindStation(Map& map, char start[]);
void Init(Map& map);
int main(){
   Map map;
   int path[MAX_STATION] = { 0 };
   int sel = 0;
   int stop_start;
   int stop_end;
   char start[20];
   char end[20];
   ////////////

   Init(map);

   //////////
   SetColor(3);

   while (sel != 4){
      system("cls");
      Init(map);

      stop_start = 1;
      stop_end = 1;
      printmain();
      sel = _getch();

      if (sel != 4){
         switch (sel)
         {
         case 49:{
            system("cls");
            printwall(4, 14);
            while (stop_start){
               gotoxy(25, 8);
               cout << "START STATION : ";
               fflush(stdin);
               cin >> start;
               if (FindStation(map, start)){
                  stop_start = 0;
                  break;
               }
               else{
                  gotoxy(25, 9);
                  cout << "!THERE IS NO STATION!";
                  Sleep(1000);
               }
               gotoxy(25, 9);
               cout << "                          ";
            }
            while (stop_end){
               gotoxy(25, 10);
               cout << " END STATION  : ";
               fflush(stdin);
               cin >> end;
               if (FindStation(map, end)){
                  stop_end = 0;
                  break;
               }
               else{
                  gotoxy(25, 11);
                  cout << "!THERE IS NO STATION!";
                  Sleep(1000);
               }
               gotoxy(25, 11);
               cout << "                          ";
            }
            if (!strcmp(start, end)){
               system("cls");
               gotoxy(20, 14);
               SetColor(12);
               cout << "CAN'T SAME START STATION AND END STATION" << endl;
               SetColor(3);
			   Sleep(1500);
               continue;
            }
            gotoxy(25, 13);
            SetColor(3);
            cout << " 1. Searching Shortest Path";
            gotoxy(25, 14);
            SetColor(3);
            cout << " 2. Searching Fastest Path";
            int flag111 = 1;
            while (flag111){
               int select = _getch();
               if (select == '1'){
                  Init(map);
                  Dijkstra(map, path, start, end, 1);
               }
               else if (select == '2'){
                  Init(map);
                  Dijkstra_time(map, path, start, end, 1);
               }
               else{
                  flag111 = 0;
                  continue;
               }
            }

            /*for (int i = 0; i >= 0; i++){
            gotoxy(25, 14);
            SetColor(2);
            cout << "ENTER KEY ▶ Searching Path";
            Sleep(300);
            gotoxy(25, 14);
            SetColor(3);
            cout << "ENTER KEY ▶ Searching Path ";
            Sleep(300);
            if (_kbhit())
            break;
            }*/

            break;
         }
         case 50:
            jeol();
            //즐찾 출력
            break;
         case 51:
            latest();
            //최근 검색
            break;
         default:
            cout << "잘못된 숫자를 입력하셨습니다." << endl;
            Sleep(2000);
            system("cls");
            break;
         }
      }
   }

   return 0;
}
void jeol(){
   system("cls");
   printFR();
   int c[10] = { 0, };
   int inttemp;
   char chartemp[20];
   char a[10][20] = { "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   " };
   char b[10][20] = { "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   " };
   Map map;
   int path[MAX_STATION] = { 0 };

   ifstream ifs("jeol.txt");
   //ofstream ofs;

   for (int i = 0; i< 10; i++){
      ifs >> a[i];
      ifs >> b[i];
      ifs >> c[i];
   }

   for (int i = 0; i < 10; i++){
      for (int j = 0; j < 9; j++){
         if (c[j] < c[j + 1]){

            strcpy_s(chartemp, a[j]);
            strcpy_s(a[j], a[j + 1]);
            strcpy_s(a[j + 1], chartemp);

            strcpy_s(chartemp, b[j]);
            strcpy_s(b[j], b[j + 1]);
            strcpy_s(b[j + 1], chartemp);

            inttemp = c[j];
            c[j] = c[j + 1];
            c[j + 1] = inttemp;
         }
      }
   }
   ifs.close();
   /*
   for (int i = 0; !ifs.eof(); i++){
   if (i > 9)
   {
   for (int j = 1; j < 10; j++){
   for (int k = 0; k < 20; k++){
   a[j - 1][k] = a[j][k];
   b[j - 1][k] = b[j][k];
   }
   }
   i--;
   ifs >> a[i];
   ifs >> b[i];
   }
   else{
   ifs >> a[i];
   ifs >> b[i];
   }

   }
   */
   ofstream ofs("jeol.txt");
   ofs << a[0] << " " << b[0] << " " << c[0];
   for (int i = 1; i < 10; i++){
      ofs << endl << a[i] << " " << b[i] << " " << c[i];
   }
   ofs.close();
   for (int i = 0; i < 10; i++){
      gotoxy(28, 8 + i);
      cout << (i + 1) << ". " << a[i] << " -> " << b[i] << endl;
   }

   cout << endl << "다시 보는 즐겨찾기 번호를 입력해주세요." << endl;
   int jeolnum;
   cin >> jeolnum;
   Init(map);
   Dijkstra(map, path, a[jeolnum - 1], b[jeolnum - 1], 0);
   Sleep(300);
}
void latest(){

   char a[10][20] = { "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   " };
   char b[10][20] = { "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   " };
   Map map;
   int path[MAX_STATION] = { 0 };

   ifstream ifs;
   ofstream ofs;
   ifs.open("latest.txt");

   for (int i = 0; !ifs.eof(); i++){
      if (i > 9)
      {
         for (int j = 1; j < 10; j++){
            for (int k = 0; k < 20; k++){
               a[j - 1][k] = a[j][k];
               b[j - 1][k] = b[j][k];
            }
         }
         i--;
         ifs >> a[i];
         ifs >> b[i];
      }
      else{
         ifs >> a[i];
         ifs >> b[i];
      }

   }
   ofs.open("latest.txt");

   for (int i = 0; i < 10; i++){
      ofs << endl << a[i] << " " << b[i];
   }
   ofs.close();

   for (int i = 0; i <10; i++){
      gotoxy(28, 8 + i);
      cout << (i+1) << ". " << a[i] << " ▷ " << b[i] << "              " << endl;
   }
   ifs.close();

   //cout << endl << "다시 보고 싶은 최근 검색 번호를 입력해주세요." << endl;
   int latestnum;
   cin >> latestnum;
   Init(map);
   Dijkstra(map, path, a[latestnum - 1], b[latestnum - 1], 1);
}
void printwall(int a, int n){
   gotoxy(6, a);
   cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
   for (int i = 1; i < n; i++){
      gotoxy(6, a + i);
      cout << "■                                                                ■" << endl;
   }
   gotoxy(6, a + n);
   cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
}
void printmain(){
   int a = 6;
   gotoxy(26, a - 3);
   cout << "*  S M A R T  S U B W A Y  *";
   gotoxy(6, a);
   cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
   gotoxy(6, a + 1);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 2);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 3);
   cout << "■                      1. Searching Path                         ■" << endl;
   gotoxy(6, a + 4);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 5);
   cout << "■                      2. Favorite                               ■" << endl;
   gotoxy(6, a + 6);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 7);
   cout << "■                      3. Recent Search                          ■" << endl;
   gotoxy(6, a + 8);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 9);
   cout << "■                      4. Exit                                   ■" << endl;
   gotoxy(6, a + 10);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 11);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 12);
   cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;

}
void printFR(){
   int a = 6;
   gotoxy(26, a - 3);
   cout << "*  S M A R T  S U B W A Y  *";
   gotoxy(6, a);
   cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
   gotoxy(6, a + 1);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 2);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 3);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 4);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 5);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 6);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 7);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 8);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 9);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 10);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 11);
   cout << "■                                                                ■" << endl;
   gotoxy(6, a + 12);
   cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;

}
void Init(Map& map){
   map.stn = new Station[MAX_STATION];
   //map.time = new int[MAX_STATION];
   map.visited = new bool[MAX_STATION];
   map.dist = new int[MAX_STATION];
   for (int i = 0; i < MAX_STATION; i++){
      map.visited[i] = false;
      map.dist[i] = 999;
   }

   int t1;
   int t2;
   int time;
   char stn1[100];
   char stn2[100];
   ifstream FILE("subway.txt");
   while (!FILE.eof()){
      Station* p = NULL;
      Station Temp;

      FILE >> t1;
      FILE >> t2;
      FILE >> time;
      FILE >> stn1;
      FILE >> stn2;
      t1 -= 1;
      t2 -= 1;

      map.stn[t1].stn_num = t1;
      map.stn[t1].stn_time = time;
      strcpy_s(map.stn[t1].stn_name, stn1);
      map.stn[t2].stn_num = t2;
      map.stn[t2].stn_time = time;
      strcpy_s(map.stn[t2].stn_name, stn2);
      if (t1 == 324 || t1 == 325 || t1 == 326 || t1 == 327 || t1 == 328 || t1 == 329){
         if (t1 + 1 == t2){
            p = &map.stn[t1];
            /////vertics 서로 연결
            while (p->next != NULL){
               p = p->next;
            }
            p->next = new Station(t2, time, stn2);
         }
         else{
            if (t1 == 329){
               p = &map.stn[t1];
               /////vertics 서로 연결
               while (p->next != NULL){
                  p = p->next;
               }
               p->next = new Station(t2, time, stn2);
            }
            else{
               p = &map.stn[t1];
               /////vertics 서로 연결
               while (p->next != NULL){
                  p = p->next;
               }
               p->next = new Station(t2, time, stn2);

               p = &map.stn[t2];
               while (p->next != NULL){
                  p = p->next;
               }
               p->next = new Station(t1, time, stn1);
            }
         }
      }
      else{
         p = &map.stn[t1];
         /////vertics 서로 연결
         while (p->next != NULL){
            p = p->next;
         }
         p->next = new Station(t2, time, stn2);

         p = &map.stn[t2];
         while (p->next != NULL){
            p = p->next;
         }
         p->next = new Station(t1, time, stn1);
      }
   }
}
int Dijkstra(Map& map, int path[], char a[20], char b[20], int num){
   Init(map);
   ofstream of;
   of.open("latest.txt", fstream::out | fstream::app);
   of << endl << a << " " << b;
   of.close();
   int cur_Vertics = 0;
   int count = 0;
   int jeol;
   int temp = 99;
   int count1;
   int print_transfer[200] = { 0 };
   int check_transfer[200] = { 0 };
   int transfer_index;
   int index;
   Station* p;
   int start_num;//출발하는 지하철 번호 변수
   for (int i = 0; i < MAX_STATION; i++){//출발역찾는 포문
      p = &map.stn[i];
      if (!strcmp(p->stn_name, a)){
         ////cout << i << " : " << p->stn_name << endl;
         cur_Vertics = p->stn_num;
         start_num = cur_Vertics;
         map.visited[cur_Vertics] = true;
         map.dist[cur_Vertics] = 0;
         break;
      }
   }
   while (1){
      // dist 배열중 가장 작은 벌택스 선택
      for (int i = 0; i < MAX_STATION; i++){
         if (!map.visited[i]){
            if (map.dist[i] <= temp){
               temp = map.dist[i];
               cur_Vertics = i;
            }
         }
      }
      //가장 작은 배열을 현재노드로 함
      p = &map.stn[cur_Vertics];
      map.visited[cur_Vertics] = true;
      ////cout << p->stn_num << ":" << p->stn_name << endl;
      for (; p->next != NULL; p = p->next){
         if (!map.visited[p->next->stn_num]){
            //cout << p->next->stn_name;
            if ((map.dist[p->next->stn_num] > map.dist[cur_Vertics] + 1)){
               map.dist[p->next->stn_num] = map.dist[cur_Vertics] + 1;
               path[p->next->stn_num] = cur_Vertics;//현재 버택스에 인접한 버택스의 경로 배열에 현재 포인터의 값대입
            }
            //if (!strcmp(p->stn_name, p->next->stn_name))count++;
            //경로 출력
            system("cls");
            if (!strcmp(p->next->stn_name, b)){
               //system("cls");
               //cout << endl;
               gotoxy(11, 7);
               SetColor(2);
               cout << "출발역";
               gotoxy(11, 8);
               cout << ": " << map.stn[start_num].stn_name;
               gotoxy(11, 10);
               cout << "도착역";
               gotoxy(11, 11);
               cout << ": " << p->next->stn_name;
               SetColor(3);
               temp = p->next->stn_num;
               count = 0;
               //cout << "경로 출력 : " << endl;
               gotoxy(6, 4);
               cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
               gotoxy(6, 5);
               cout << "■";
               gotoxy(41, 5);
               cout << "｜";
               gotoxy(72, 5);
               cout << "■";
               gotoxy(6, 6);
               cout << "■ ";
               gotoxy(41, 6);
               cout << "｜";
               gotoxy(72, 6);
               cout << "■";
               index = 0;
               transfer_index = 0;
               while (path[temp] != start_num){
                  /*if (path[temp] == 324 || path[temp] == 325){
                  if ()
                  }*/
                  if (strcmp(map.stn[path[temp]].stn_name, map.stn[path[path[temp]]].stn_name)){//현재 역이름과 다음에 나올 역이름 비교
                     gotoxy(6, count + 7);
                     cout << "■";
                     gotoxy(41, count + 7);
                     cout << "｜";
                     gotoxy(50, count + 7);
                     //cout << map.stn[path[temp]].stn_name;
                     gotoxy(72, count + 7);
                     cout << "■";
                     count++;//다르면 카운트 올리고 다르면 스킵
                     print_transfer[index++] = path[temp];

                  }
                  else{
                     check_transfer[transfer_index++] = path[path[temp]];
                     //gotoxy(44, count + 6);
                     //cout << "환승 ";
                  }
                  temp = path[temp];
               }
               if (count < 10){
                  count1 = 10;
                  for (int i = 0; i<count1 + 3; i++){
                     gotoxy(6, 7 + i);
                     cout << "■";
                     gotoxy(41, 7 + i);
                     cout << "｜";
                     gotoxy(72, 7 + i);
                     cout << "■";
                  }
               }
               else
                  count1 = count;
               gotoxy(6, count1 + 7);
               cout << "■";
               gotoxy(41, count1 + 7);
               cout << "｜";
               gotoxy(72, count1 + 7);
               cout << "■";
               gotoxy(6, count1 + 8);
               cout << "■ ";
               gotoxy(41, count1 + 8);
               cout << "｜";
               gotoxy(72, count1 + 8);
               cout << "■";
               gotoxy(6, count1 + 9);
               cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
               gotoxy(11, 13);
               cout << count + 1 << "개 역 지남" << endl;

               char c[10][20] = { "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   " };
               char d[10][20] = { "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   " };
               int e[10] = { 0, };

               ifstream ifs("jeol.txt");

               for (int i = 0; i < 10; i++){
                  ifs >> c[i];
                  ifs >> d[i];
                  ifs >> e[i];
               }
               ifs.close();
               for (int i = 0; i < 10; i++){
                  if (!strcmp(a, c[i]) && !strcmp(b, d[i])){
                     e[i]++;
                     break;
                  }
               }
               ofstream fout("jeol.txt");

               for (int i = 0; i < 10; i++){
                  fout << c[i] << " " << d[i] << " " << e[i] << endl;
               }
               fout.close();
               if (num == 1){
                  gotoxy(11, 15);
                  cout << "즐겨찾기에 추가하시겠습니까?";
                  gotoxy(11, 17);
                  cout << " 1 : yes    2 : no   ";
               }
               int flags = 1;
               for (int i = index - 1; i >= 0; i--){
                  gotoxy(50, 7 + (index - 1 - i));
                  for (int j = 0; j < transfer_index; j++){
                     if (check_transfer[j] == print_transfer[i]){
                        //SetColor(2);
                        Sleep(300);
                        SetColor(14);
                        cout /*<< check_transfer[j] << ":" << print_transfer[i] << " : " */ << map.stn[print_transfer[i]].stn_name << endl;
                        SetColor(3);
                        flags = 0;
                        break;
                     }
                  }
                  if (flags){
                     Sleep(300);
                     cout /*<< ":" << print_transfer[i] << " : "*/ << map.stn[print_transfer[i]].stn_name << endl;
                  }
                  flags = 1;
               }
               //for (int i = 0;i<=transfer_index;i++){

               //   cout << check_transfer[i] << " : " << map.stn[check_transfer[i]].stn_name << endl;
               //}

               fflush(stdin);
               if (num == 1){
                  gotoxy(35, 17);
                  cin >> jeol;
                  if (jeol == 1){
                     int notx = -1;
                     int favoriteflag = 0;
                     int leastfavorite = INT_MAX;
                     int leastnum = -1;
                     int countt = sizeof(c) / sizeof(c[0]);
                     for (int i = 0; i < countt; i++){
                        if (!strcmp(a, c[i]) && !strcmp(b, d[i])){
                           favoriteflag = 1;
                           break;
                        }
                     }

                     if (favoriteflag == 0){ //즐겨찾기에 존재X
                        for (int i = 0; i < countt; i++){
                           if (!strcmp(c[i], "X")){
                              notx = i; // X의 첫번째 위치 저장
                              break;
                           }
                        }

                        if (notx != -1){

                           strcpy_s(c[notx], a);
                           strcpy_s(d[notx], b);
                           e[notx] = 0;
                        }
                        else{ //이미 10개가 찼을 때
                           for (int i = 0; i < countt; i++){
                              if (e[i] < leastfavorite){
                                 leastfavorite = e[i];
                                 leastnum = i;
                              }
                           }
                           strcpy_s(c[leastnum], a);
                           strcpy_s(d[leastnum], b);
                           e[leastnum] = 0;

                        }
                        ofstream fout("jeol.txt");
                        for (int i = 0; i < countt; i++){
                           fout << c[i] << " " << d[i] << " " << e[i] << endl;
                        }
                        fout.close();
                        gotoxy(11, 20);
                        cout << "즐겨찾기에 성공적으로 추가하셨습니다.";
                     }
                     else if (favoriteflag == 1){
                        gotoxy(11, 20);
                        cout << "이미 즐겨찾기에 존재하는 항목입니다.";
                     }
                  }
                  else if (jeol == 2) {
                     system("cls");
                  }

               }
               else if (num == 0){
                  Sleep(5);
                  int cont;
                  gotoxy(11, 19);
                  cout << "계속 하시겠습니까? ( 1 : yes, 2 : no )" << endl;
                  return 0;
               }
               return 0;

            }

         }
      }
      temp = 999;
      // //cout << endl;
   }
   // //cout << endl;
}
int Dijkstra_time(Map& map, int path[], char a[20], char b[20], int num){
   Init(map);
   ofstream of;
   of.open("latest.txt", fstream::out | fstream::app);
   of << endl << a << " " << b;
   of.close();
   int cur_Vertics = 0;
   int count = 0;
   int count_time = 0;
   int jeol;
   int temp = 99;
   int count1;
   int print_transfer[200] = { 0 };
   int check_transfer[200] = { 0 };
   int transfer_index;
   int index;
   Station* p;
   int start_num;//출발하는 지하철 번호 변수

   for (int i = 0; i < MAX_STATION; i++){//출발역찾는 포문
      p = &map.stn[i];
      if (!strcmp(p->stn_name, a)){
         ////cout << i << " : " << p->stn_name << endl;
         cur_Vertics = p->stn_num;
         start_num = cur_Vertics;
         map.visited[cur_Vertics] = true;
         map.dist[cur_Vertics] = 0;
         break;
      }
   }
   while (1){
      // dist 배열중 가장 작은 벌택스 선택
      for (int i = 0; i < MAX_STATION; i++){
         if (!map.visited[i]){
            if (map.dist[i] <= temp){
               temp = map.dist[i];
               cur_Vertics = i;
            }
         }
      }
      //가장 작은 배열을 현재노드로 함
      p = &map.stn[cur_Vertics];
      map.visited[cur_Vertics] = true;
      ////cout << p->stn_num << ":" << p->stn_name << endl;
      for (; p->next != NULL; p = p->next){
         if (!map.visited[p->next->stn_num]){
            //cout << p->next->stn_name;
            if ((map.dist[p->next->stn_num] > map.dist[cur_Vertics] + p->stn_time)){
               map.dist[p->next->stn_num] = map.dist[cur_Vertics] + p->stn_time;
               path[p->next->stn_num] = cur_Vertics;//현재 버택스에 인접한 버택스의 경로 배열에 현재 포인터의 값대입
            }
            //if (!strcmp(p->stn_name, p->next->stn_name))count++;
            //경로 출력================================================================================================================================
            system("cls");
            if (!strcmp(p->next->stn_name, b)){
               //system("cls");
               //cout << endl;
               SetColor(2);
               gotoxy(11, 7);
               cout << "출발역";
               gotoxy(11, 8);
               cout << ": " << map.stn[start_num].stn_name;
               gotoxy(11, 10);
               cout << "도착역";
               gotoxy(11, 11);
               cout << ": " << p->next->stn_name;
               SetColor(3);
               temp = p->next->stn_num;
               count = 0;
               //cout << "경로 출력 : " << endl;
               gotoxy(6, 4);
               cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
               gotoxy(6, 5);
               cout << "■";
               gotoxy(41, 5);
               cout << "｜";
               gotoxy(72, 5);
               cout << "■";
               gotoxy(6, 6);
               cout << "■ ";
               gotoxy(41, 6);
               cout << "｜";
               gotoxy(72, 6);
               cout << "■";
               index = 0;
               transfer_index = 0;
               //예외처리==================================================================
               if (path[temp] == start_num){
                  count_time += map.stn[path[temp]].stn_time;
               }
               //예외처리==================================================================
               while (path[temp] != start_num){
                  if (strcmp(map.stn[path[temp]].stn_name, map.stn[path[path[temp]]].stn_name)){//현재 역이름과 다음에 나올 역이름 비교
                     gotoxy(6, count + 7);
                     cout << "■";
                     gotoxy(41, count + 7);
                     cout << "｜";
                     gotoxy(50, count + 7);
                     //cout << map.stn[path[temp]].stn_name;//다르면 카운트올리고 다르면 스킵.
                     gotoxy(72, count + 7);
                     cout << "■";
                     count++;
                     print_transfer[index++] = path[temp];
                     count_time += map.stn[path[temp]].stn_time;
                     //cout << map.stn[path[temp]].stn_time;
                  }
                  else{
                     check_transfer[transfer_index++] = path[path[temp]];
                     //gotoxy(44, count + 6);
                     //cout << "환승 ";
                  }
                  temp = path[temp];
               }
               if (count < 10){
                  count1 = 10;
                  for (int i = 0; i<count1 + 3; i++){
                     gotoxy(6, 7 + i);
                     cout << "■";
                     gotoxy(41, 7 + i);
                     cout << "｜";
                     gotoxy(72, 7 + i);
                     cout << "■";
                  }
               }
               else
                  count1 = count;
               gotoxy(6, count1 + 7);
               cout << "■";
               gotoxy(41, count1 + 7);
               cout << "｜";
               gotoxy(72, count1 + 7);
               cout << "■";
               gotoxy(6, count1 + 8);
               cout << "■ ";
               gotoxy(41, count1 + 8);
               cout << "｜";
               gotoxy(72, count1 + 8);
               cout << "■";
               gotoxy(6, count1 + 9);
               cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
               gotoxy(11, 13);
               cout << count_time << "분 걸림" << endl;

               char c[10][20] = { "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   " };
               char d[10][20] = { "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   ", "   X   " };
               int e[10] = { 0, };

               ifstream ifs("jeol.txt");

               for (int i = 0; i < 10; i++){
                  ifs >> c[i];
                  ifs >> d[i];
                  ifs >> e[i];
               }
               ifs.close();
               for (int i = 0; i < 10; i++){
                  if (!strcmp(a, c[i]) && !strcmp(b, d[i])){
                     e[i]++;
                     break;
                  }
               }
               ofstream fout("jeol.txt");

               for (int i = 0; i < 10; i++){
                  fout << c[i] << " " << d[i] << " " << e[i] << endl;
               }
               fout.close();
               if (num == 1){
                  gotoxy(11, 15);
                  cout << "즐겨찾기에 추가하시겠습니까?";
                  gotoxy(11, 17);
                  cout << " 1 : yes    2 : no   ";
               }
               int flags = 1;
               for (int i = index - 1; i >= 0; i--){
                  gotoxy(50, 7 + (index - 1 - i));
                  for (int j = 0; j < transfer_index; j++){
                     if (check_transfer[j] == print_transfer[i]){
                        //SetColor(2);
                        Sleep(300);
                        SetColor(14);
                        cout /*<< check_transfer[j] << ":" << print_transfer[i] << " : " */ << map.stn[print_transfer[i]].stn_name << endl;
                        SetColor(3);
                        flags = 0;
                        break;
                     }
                  }
                  if (flags){
                     Sleep(300);
                     cout /*<< ":" << print_transfer[i] << " : "*/ << map.stn[print_transfer[i]].stn_name << endl;
                  }
                  flags = 1;
               }
               //for (int i = 0;i<=transfer_index;i++){

               //   cout << check_transfer[i] << " : " << map.stn[check_transfer[i]].stn_name << endl;
               //}

               fflush(stdin);
               if (num == 1){
                  gotoxy(35, 17);
                  cin >> jeol;
                  if (jeol == 1){
                     int notx = -1;
                     int favoriteflag = 0;
                     int leastfavorite = INT_MAX;
                     int leastnum = -1;
                     int countt = sizeof(c) / sizeof(c[0]);
                     for (int i = 0; i < countt; i++){
                        if (!strcmp(a, c[i]) && !strcmp(b, d[i])){
                           favoriteflag = 1;
                           break;
                        }
                     }

                     if (favoriteflag == 0){ //즐겨찾기에 존재X
                        for (int i = 0; i < countt; i++){
                           if (!strcmp(c[i], "X")){
                              notx = i; // X의 첫번째 위치 저장
                              break;
                           }
                        }

                        if (notx != -1){

                           strcpy_s(c[notx], a);
                           strcpy_s(d[notx], b);
                           e[notx] = 0;
                        }
                        else{ //이미 10개가 찼을 때
                           for (int i = 0; i < countt; i++){
                              if (e[i] < leastfavorite){
                                 leastfavorite = e[i];
                                 leastnum = i;
                              }
                           }
                           strcpy_s(c[leastnum], a);
                           strcpy_s(d[leastnum], b);
                           e[leastnum] = 0;

                        }
                        ofstream fout("jeol.txt");
                        for (int i = 0; i < countt; i++){
                           fout << c[i] << " " << d[i] << " " << e[i] << endl;
                        }
                        fout.close();
                        gotoxy(11, 20);
                        cout << "즐겨찾기에 성공적으로 추가하셨습니다.";
                     }
                     else if (favoriteflag == 1){
                        gotoxy(11, 20);
                        cout << "이미 즐겨찾기에 존재하는 항목입니다.";
                     }
                  }
                  else if (jeol == 2) {
                     int cont;
					 gotoxy(11,23);
                     cout << "계속 하시겠습니까? ( 1 : yes, 2 : no )" ;
                     return 0;
                  }

               }
               else if (num == 0){
                  int cont;
                  //gotoxy(11, 100);
                  cout << "계속 하시겠습니까? ( 1 : yes, 2 : no )" << endl;

                  return 0;
               }
               return 0;

            }

         }
      }
      temp = 999;
      // //cout << endl;
   }
}
bool FindStation(Map& map, char start[]){

   Station* p;
   ///////
   for (int i = 0; i < MAX_STATION; i++){
      p = &map.stn[i];
      if (!strcmp(p->stn_name, start)){
         return 1;
      }
   }
   /////
   return 0;
}
void gotoxy(int x, int y)
{
   COORD Pos = { x, y };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void SetColor(int color)
{
   static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(std_output_handle, color);
}