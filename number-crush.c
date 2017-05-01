#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
/*----------------------------------------------------------------*/     
void setcolor(int);      
void gotoxy(int,int);   
void cursor_hide();
/*------------------------- Prototypes ----------------------------*/ 
int menu(int*,int*,int*);
int options(int*,int*,int*);
int structure_selecting_menu(int*,int*,int*,int*,int*,int*,int*,int*);
void how_to_play(void);
void select_the_frame_in_the_options(int,int);
void clean_the_frame_in_the_options(int,int); 
void clean_the_frame_in_the_selection_structers_menu(int,int);
void create_the_frame_in_the_selection_structers_menu(int,int);
void paint_the_frame_in_the_selection_structers_menu(int,int,int[5][5]);
void game_mode_selecting(int*);
void create_frame_in_the_mode_selecting(int);
void clean_frame_in_the_mode_selecting(int);
void frame_of_the_game(int,int,int*,int*,int*,int*,int*,int*,int*,int*,int*);
void create_the_first_numbers(int[20][20],int,int,int*,int*,int*,int*,int*,int*,int*,int*);
void colored_numbers(int[20][20],int,int);
void frame_1_cleaning(int,int,int[20][20]); 
void frame_2_selecting(int,int,int[20][20]);
void frame_3_changing(int,int,int[20][20]);
void swap_two_numbers(int,int,int[20][20],int,int);
void search_structure(int[20][20],int,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*);
void cleaner(int[20][20],int);
void slipper(int[20][20],int,int);
void new_numbers(int[20][20],int,int,int);
void clean_the_right_window(int);
void score_data(int,int,int,int,char[50],int);
/*---------------------- Global variables ------------------------*/  
   char nick[20][50],playedmode[20];                                //  main fonksiyonu recursive oldugundan dolayi, main fonksiyonunu her çagirdigimizda
   int matrixsize[20],numbersize[20],wonscore[20];                 //  oyun bilgileri sifirlaniyor.Bu yüzden global degisken bir çözüm olarak bulundu.
   int indis=-1;      // adres bilgilerinin tutulacagi indis
   int n=10,range=5; // eger kullanici ilk basta options kismindan matris boyutu ve sayi uzunluklarini girmezse, matris boyutu 10 ve sayi uzunluklari 5 olarak kabul ediliyor.Daha sonra kendi ayari sürekli oluyor.                                   
/*----------------------------------------------------------------*/ 

int main() {
   //static char nick[20][50],playedmode[20];                                //  main fonksiyonu recursive oldugundan dolayi, main fonksiyonunu her çagirdigimizda
   //static int matrixsize[20],numbersize[20],wonscore[20];                 //  oyun bilgileri sifirlaniyor.Bu yüzden global degisken bir çözüm olarak bulundu.
   //static int indis=-1;      // adres bilgilerinin tutulacagi indis
   //static int n=10,range=5; // eger kullanici ilk basta options kismindan matris boyutu ve sayi uzunluklarini girmezse, matris boyutu 10 ve sayi uzunluklari 5 olarak kabul ediliyor.Daha sonra kendi ayari sürekli oluyor.                            
	
	
	indis++;            // baslangiçta indis 0 oluyor ve oyun bilgilerinin tutulacagi adresi belirtiyor. Her yeni oyunda yeni adres için indis +1 artiyor.
	char name[50]; 
	int i,j,k,gameboard[20][20],rightleft=0,updown=0,score=0,ctrl,t,live=3,countdown=20,mode,exit=0,undoctrl;
	int temp,enter=1,switch_enter1=1,switch_enter2=0; // entera her basista enter'i 0 dan 1, 1 den 0 yapmak için.
	int e_selected=0,o_selected=0,c_selected=0,u_selected=0,f_selected=0,t_selected=0,l_selected=0,i_selected=0;
	
	menu(&n,&range,&exit); if (exit==1) goto cikis;   
	structure_selecting_menu(&e_selected,&o_selected,&c_selected,&u_selected,&f_selected,&t_selected,&l_selected,&i_selected);
	game_mode_selecting(&mode);
	frame_of_the_game(n,range,&e_selected,&o_selected,&c_selected,&u_selected,&f_selected,&t_selected,&l_selected,&i_selected,&mode);
	create_the_first_numbers(gameboard,n,range,&e_selected,&o_selected,&c_selected,&u_selected,&f_selected,&t_selected,&l_selected,&i_selected);
    

  i=n/2;j=n/2;k=0;                          // n/2 ile gameboard'umuzun ilk kordinatlari ortalardan seçilmis oluyor.
frame_2_selecting(j,i,gameboard);         // oyun ilk açildiginda serbest dolasim çerçevesi ekrana gösteriliyor.
while ( live!=0 && countdown!=0 ) {     
        
		undoctrl=score;
		int c = getch();
        if (c==27) break;    // esc tusuna basildigi anda relax mode ve diger modlardan çikmis oluyoruz.
        if (c==13) {        // bu kosula giris sadece enter tusuna basarak gerçeklesiyor.
		   
		if (enter==0) swap_two_numbers(j,i,gameboard,rightleft,updown);  // rightleft ve updown, yani sagadami soldami yukaridami asagidami. Bulundugumuz kordinata göre eski kordinattaki sayi ile yer degistiriyor.
		if (enter==0 && mode==2) { countdown--;setcolor(12);gotoxy(9*n/2+10,3);printf("%d ",countdown);setcolor(7); }  // geri sayim modundaysak, enter=0 için geri sayim degiskenimiz azaliyor ve ekranda bildiriliyor.
          
        if (enter==1) frame_3_changing(j,i,gameboard);    // sadece 2 sayiyi degistirme çerçevesi ekrana yazdiriliyor.
        if (enter==0) frame_2_selecting(j,i,gameboard);  // serbest dolasim çerçevesi ekrana yazdiriliyor.
         
		if (enter==0 && rightleft==1) frame_1_cleaning(j-1,i,gameboard);    //2 sayiyi degistirmek için entera bastiktan sonra,bulundugu konuma göre önceki çerçeve eski haline dönüyor.
		if (enter==0 && rightleft==-1) frame_1_cleaning(j+1,i,gameboard);
        if (enter==0 && updown==1) frame_1_cleaning(j,i-1,gameboard);
        if (enter==0 && updown==-1) frame_1_cleaning(j,i+1,gameboard);
        
        ctrl=1;
		while (enter==0 && ctrl!=score) {      // while döngüsüne giris enter tusuna bastiktan sonra gerçeklesiyor ve score degistikçe structer arama sürekli tekrarlaniyor.
		    ctrl=score;
		
		        search_structure(gameboard,n,&score,&e_selected,&o_selected,&c_selected,&u_selected,&f_selected,&t_selected,&l_selected,&i_selected,&live,&mode);
		        setcolor(15);gotoxy(5*n-1,3*n-2);printf("%d",score);
				    t=100;  
				    if (ctrl==score) t=0;        // kaydirma efekti verilsin diye slipper fonksiyonunda bekletme komutu var,while döngüsünden çikma zamani gelince son taramada ekran donmasin diye zaman 0 olarak kabul ediliyor.
				    slipper(gameboard,n,t);    
		            new_numbers(gameboard,n,range,t);   
		            clean_the_right_window(n);         // search_structer fonksiyonumuz sürekli saga ekrana büyük harflerle buldugu harfi yaziyor, bu fonksiyon onu temizlemekle görevli.
	            
	    }
	    if (enter==0) frame_2_selecting(j,i,gameboard);	  //  structer aramadan sonra, serbest seçim çerçevesi tekrar ekrana yazdiriliyor.
		   
		   
		if (undoctrl==score && enter==0 ) {    // eger en basta tanimlanan undoctrl skora esit degil ise,basarisiz hamle sonucu 2 sayi tekrar arasinda yer degistiriyor.
		    printf("\a");
			Sleep ( 300 );
			swap_two_numbers(j,i,gameboard,rightleft,updown);
	            if (rightleft==1) frame_1_cleaning(j-1,i,gameboard);     // bulundugu konuma göre eski konumdaki serbest seçim çerçevesi, eski halini geri aliyor.
		        if (rightleft==-1) frame_1_cleaning(j+1,i,gameboard);
                if (updown==1) frame_1_cleaning(j,i-1,gameboard);
                if (updown==-1) frame_1_cleaning(j,i+1,gameboard);
		            frame_2_selecting(j,i,gameboard);               // son konumumuzdaki serbest dolasim çerçevesi ekrana gösteriliyor.
		}
		   
		   temp=switch_enter1;                     
           switch_enter1=switch_enter2;
           switch_enter2=temp;
           enter=switch_enter1;          // enter 0 dan 1,1 den 0 oluyor.
        
		rightleft=0;             // entera basip tüm kontroller gerçeklestikten sonra saga,sola,yukari ve asagi 1den fazla gitmemizi sinirlayan kordinatlar sifirlaniyor.
		updown=0;
		}	
if(c=='d' || c=='D') {                                       // yön tuslari bulundugu kordinat 1 den büyük ve n den küçük oldugu sürece çalisiyor.Buda matristen çikmamizi engelliyor.
	if (j<n && enter==1) {                                  // her yön tuslarina bastigimizda bulundugumuz konumdaki çerçeve eski haline dönüyor. yeni kordinatimiz 1 artiyor ve yeni kordinatimiz 
		frame_1_cleaning(j,i,gameboard);                   // yeni serbest dolasim çerçevesine dönüstürülüyor. Diger tuslardaki mantikta ayni.
            j++;
		frame_2_selecting(j,i,gameboard);
	}
    if (j<n && enter==0 && (rightleft==-1 || rightleft==0) && updown==0) {   // Eger enter=0 dan sonra d ye basilirsa sayi degistirme çerçevesi 1 kereye mahsus olmak üzere saga tarafada yazdiriliyor ve 
    	if (rightleft==-1) frame_1_cleaning(j,i,gameboard);                 // rightleft degiskeni 1 oluyor, daha fazla saga gitmenin kosulu ise rightleft -1 veya 0 olmasi oldugu için, daha saga gidemiyoruz.
		j++;rightleft++;                                                   // ayni zamanda burada updownin 0 olmasi kosulu oldugu gibi yukari ve asagi içinde rightleft=0 olma kosulu var. Bu sebeple 1 kere saga gittikten
    	frame_3_changing(j,i,gameboard);                                  // veya 1 kere sola gittikten sonra yukari ve asagi gidemiyoruz. Diger tuslardaki mantikta ayni çalisiyor.
	}		
           }
if(c=='a' || c=='A') { 
	if (j>1 && enter==1 ) {
		frame_1_cleaning(j,i,gameboard);
            j--;
		frame_2_selecting(j,i,gameboard);
	}
		if (j>1 && enter==0 && (rightleft==1 || rightleft==0 ) && updown==0 ) {
    	if (rightleft==1) frame_1_cleaning(j,i,gameboard);
		j--;rightleft--;
    	frame_3_changing(j,i,gameboard);		
        }
}   
if(c=='w' || c=='W') {
	if (i>1 && enter==1 ) {
		frame_1_cleaning(j,i,gameboard);
            i--;
		frame_2_selecting(j,i,gameboard);
    }
        if (i>1 && enter==0 && (updown==1 || updown==0 ) && rightleft==0 ) {
    	if (updown==1) frame_1_cleaning(j,i,gameboard);
		i--;updown--;
    	frame_3_changing(j,i,gameboard);	
        }
}
if(c=='s' || c=='S') {
	if (i<n && enter==1 ) {
		frame_1_cleaning(j,i,gameboard);
            i++;
		frame_2_selecting(j,i,gameboard);
	}
		if (i<n && enter==0 && (updown==-1 || updown==0 ) && rightleft==0  ) {
    	if (updown==-1) frame_1_cleaning(j,i,gameboard);
		i++;updown++;
    	frame_3_changing(j,i,gameboard);	
        }
}

}   //while sonu
system("CLS");setcolor(7);
gotoxy(30,15);printf("GAME OVER");
gotoxy(30,30);
getch();
system("CLS");
cursor_hide(1);
printf("Enter your name : ");gets(name);
cursor_hide(0);
score_data(indis,n,range,mode,name,score);    // global olarak tanimlanan degiskenler burada kullaniliyor.indis her maine giriste 1 artiyor ve yeni bilgilerin saklanacagi adres belirlenmis oluyor.
getch();
main();                                      // oyun bittikten sonra main recursive olarak kendini tekrar çagiriyor ve yeni oyun bastan basliyor.

cikis:                                      // eger menü fonksiyonunun içinde exit konumunda iken entera basarsak,main recursive fonksiyonunu atlayarak goto ile komple tüm oyundan çikmis oluyoruz. 
system("CLS");setcolor(7);
gotoxy(30,15);printf("Thanks For Playing");
gotoxy(30,30);
	
}   //main sonu

  /*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
 /*-------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>   FUNCTIONS  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<---------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int menu(int *n,int *range,int *exit) {
howtoplay_cikisi:
system("CLS");
setcolor(11);
printf("\n\n");		    	
	printf("         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c    \n",177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,
	177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177);
	printf("         %c                                  ____     ____    __    %c          \n",177,177);
	printf("         %c  |%c    |  |     |  |%c      /|   |    %c   |       |  %c   %c       \n",177,92,92,92,92,177);
	printf("         %c  | %c   |  |     |  | %c    / |   | O  |   |       | O |  %c         \n",177,92,92,177);
	printf("         %c  |  %c  |  |     |  |  %c  /  |   |   <    |----   |__/   %c       \n",177,92,92,177);
	printf("         %c  |   %c |  |     |  |   %c/   |   | O  |   |       | %c    %c      \n",177,92,92,92,177);
	printf("         %c  |    %c|  |_____|  |        |   |____/   |____   |  %c   %c       \n",177,92,92,177);
	printf("         %c                                                         %c   \n",177,177);		    					
	printf("         %c                 _____    __             _____           %c   \n",177,177);	
	printf("         %c                |        |  %c   |    |  |        |    |  %c     \n",177,92,177);	
	printf("         %c                |        | O |  |    |  |        |    |  %c   \n",177,177);	
	printf("         %c                |        |__/   |    |  |-----   |----|  %c   \n",177,177);	
	printf("         %c                |        | %c    |    |        |  |    |  %c    \n",177,92,177);	
	printf("         %c                |_____   |  %c   |____|   _____|  |    |  %c     \n",177,92,177);				
	printf("         %c                                                         %c  \n",177,177);
	printf("         %c                                                         %c  \n",177,177);
	printf("         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c    \n",177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,
	177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177);
	printf("\n\n\n");
	setcolor(12);
	printf("                                  START GAME\n\n");
	printf("                                  OPTIONS\n\n");
	printf("                                  HOW TO PLAY ?\n\n");
	printf("                                  EXIT\n");
	setcolor(7);
	printf("\n\n\n\n                                                         Rights are not reserved %c",1);
	setcolor(9);
	int updown=1,enter=0,rightleft=1;
	gotoxy(30,20+2*updown);printf("%c",16);
	cursor_hide(0);     // yazi yazma imleci bu fonksiyon ile gizleniyor. 
	
	while (1) {        // sonsuz döngü
	int a=getch();	
	 	
	if(a=='w' || a=='W') {       // main içindeki yön tuslarinin mantigi ile ayni, updown 1-4 arasinda oldugu sürece yeni kordinatimiz ok simgesi ile ekranda gösterilip, eskisi siliniyor.
	 	if (updown>1) {
	 		updown--;
	 		gotoxy(30,20+2*updown);printf("%c",16);
	 		gotoxy(30,22+2*updown);printf("  ");
		    }}
	
	if(a=='s' || a=='S') { 
	    if (updown<4) {
	 		updown++;
            gotoxy(30,20+2*updown);printf("%c",16);
			gotoxy(30,18+2*updown);printf("  ");
			}}
		
	if(a==13 && updown==1) return 0;                                 
	if(a==13 && updown==2) return options(n,range,exit);
	if(a==13 && updown==3) { how_to_play(); goto howtoplay_cikisi; }   // menunun içinde bu fonksiyonu çagirdiktan sonra ve bu fonksiyondan tekrar çiktiktan sonra ana menünün en basina gelemiyoruz.how_to_play
	if(a==13 && updown==4) return (*exit=1);                          // fonksiyonunun içinde sikistigimiz için, goto çözüm olarak kullanildi.
}}     // menüden çikarken eger exit degerimiz 1 e esitse, main recursive oldugundan dolayi onu atlayabilmemizin tek yolu onun üstünden ziplamak. Goto çözüm olarak kullanildi.

int options(int *n,int *range,int *exit) 
{
	setcolor(7);
	system("CLS");	
    printf("\n\n                          Select Your Game Board Size     ");
		gotoxy(20,5);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(20,6);printf("%c     %c",179,179);
	    gotoxy(20,7);printf("%c 8x8 %c",179,179);
	    gotoxy(20,8);printf("%c     %c",179,179);
		gotoxy(20,9);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);
		
		gotoxy(35,5);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(35,6);printf("%c     %c",179,179);
	    gotoxy(35,7);printf("%c 9x9 %c",179,179);
	    gotoxy(35,8);printf("%c     %c",179,179);
		gotoxy(35,9);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);
		
		gotoxy(50,5);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(50,6);printf("%c     %c",179,179);
	    gotoxy(50,7);printf("%c10x10%c",179,179);
	    gotoxy(50,8);printf("%c     %c",179,179);
		gotoxy(50,9);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);
		
		gotoxy(20,15);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(20,16);printf("%c     %c",179,179);
	    gotoxy(20,17);printf("%c11x11%c",179,179);
	    gotoxy(20,18);printf("%c     %c",179,179);
		gotoxy(20,19);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);
		
		gotoxy(35,15);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(35,16);printf("%c     %c",179,179);
	    gotoxy(35,17);printf("%c12x12%c",179,179);
	    gotoxy(35,18);printf("%c     %c",179,179);
		gotoxy(35,19);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);
		
		gotoxy(50,15);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(50,16);printf("%c     %c",179,179);
	    gotoxy(50,17);printf("%c13x13%c",179,179);
	    gotoxy(50,18);printf("%c     %c",179,179);
		gotoxy(50,19);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);
		
printf("\n\n\n                       Select Your Range of The Numbers     ");

 		gotoxy(20,25);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(20,26);printf("%c     %c",179,179);
	    gotoxy(20,27);printf("%c  1  %c",179,179);
	    gotoxy(20,28);printf("%c     %c",179,179);
		gotoxy(20,29);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);
		
		gotoxy(35,25);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(35,26);printf("%c     %c",179,179);
	    gotoxy(35,27);printf("%c  2  %c",179,179);
	    gotoxy(35,28);printf("%c     %c",179,179);
		gotoxy(35,29);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);	
		
		gotoxy(50,25);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(50,26);printf("%c     %c",179,179);
	    gotoxy(50,27);printf("%c  3  %c",179,179);
	    gotoxy(50,28);printf("%c     %c",179,179);
		gotoxy(50,29);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);		
			
 		gotoxy(20,35);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(20,36);printf("%c     %c",179,179);
	    gotoxy(20,37);printf("%c  4  %c",179,179);
	    gotoxy(20,38);printf("%c     %c",179,179);
		gotoxy(20,39);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);
		
		gotoxy(35,35);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(35,36);printf("%c     %c",179,179);
	    gotoxy(35,37);printf("%c  5  %c",179,179);
	    gotoxy(35,38);printf("%c     %c",179,179);
		gotoxy(35,39);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);	
		
		gotoxy(50,35);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(50,36);printf("%c     %c",179,179);
	    gotoxy(50,37);printf("%c  6  %c",179,179);
	    gotoxy(50,38);printf("%c     %c",179,179);
		gotoxy(50,39);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);	
		
 		gotoxy(20,45);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(20,46);printf("%c     %c",179,179);
	    gotoxy(20,47);printf("%c  7  %c",179,179);
	    gotoxy(20,48);printf("%c     %c",179,179);
		gotoxy(20,49);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);
		
		gotoxy(35,45);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(35,46);printf("%c     %c",179,179);
	    gotoxy(35,47);printf("%c  8  %c",179,179);
	    gotoxy(35,48);printf("%c     %c",179,179);
		gotoxy(35,49);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);	
		
		gotoxy(50,45);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(50,46);printf("%c     %c",179,179);
	    gotoxy(50,47);printf("%c  9  %c",179,179);
	    gotoxy(50,48);printf("%c     %c",179,179);
		gotoxy(50,49);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);	
		
		setcolor(9);
		gotoxy(35,55);printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(35,56);printf("%c     %c",179,179);
	    gotoxy(35,57);printf("%c OK! %c",179,179);
	    gotoxy(35,58);printf("%c     %c",179,179);
		gotoxy(35,59);printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);		
		setcolor(7);	
		
		printf("\n\n--------------------------------------------------------------------------------\n\n");
		printf("Selected Game Board Size      :\n\n");
		printf("Selected Range of The Numbers :");	

       	
				 int c=1,rightleft=1,updown=1;
				 select_the_frame_in_the_options(rightleft,updown);   // options açildiktan sonra ilk (1,1) konumundaki çerçeve ekrana yazdiriliyor.
				 while(1) {
	
	  int c=getch();
	  	  if ((updown==6 && c==13) || c==8) { system ("CLS");return menu(n,range,exit); }     // eger konumumuz OK yazisinin üzerinde ve entera basarsak veya sadece backspace e basarsak,
	                                                                                         // optionstan çikip menu fonksiyonuna gitmis oluyoruz.
	
	if(c=='w' || c=='W') {                                                 // main fonksiyonun içindeki w-a-s-d ve enter mantigi ile ayni, bulundugumuz kordinatlar sinirlandirilmis bir biçimde,serbestçe 
		 if (updown>1) {                                                  // dolasmamizi sagliyor.Bulundugumuz konumu degistirince normal çerçeve yazdirilip ve yeni kordinata gelince seçim çerçevesi yazdiriliyor.
			clean_the_frame_in_the_options(rightleft,updown);
			updown--;
            select_the_frame_in_the_options(rightleft,updown);
		    }}
	
	if (c=='s' || c=='S')  { 
	    if (updown<5 || (updown <6 && rightleft==2)) {
			clean_the_frame_in_the_options(rightleft,updown);
			updown++;
            select_the_frame_in_the_options(rightleft,updown);

			}}

	if (c=='a' || c=='A')    {
	 	if (rightleft>1 && updown!=6) {
			clean_the_frame_in_the_options(rightleft,updown);
			rightleft--;
            select_the_frame_in_the_options(rightleft,updown);
		    }}
	
	if(c=='d' || c=='D') { 
	    if (rightleft<3 && updown!=6) {
			clean_the_frame_in_the_options(rightleft,updown);
			rightleft++;
          	select_the_frame_in_the_options(rightleft,updown);
			}}
	      	
	if(c==13)   { 

	
	   
	setcolor(12); 
	if (rightleft==1) {                         // bulundugumuz kordinata göre alt kisimda, bilgilendirme için seçilen özellikler yazdiriliyor.
	    switch(updown) {
	   	    case(1):*n=8;gotoxy(32,63);printf(" 8x8 ");break;
	   	    case(2):*n=11;gotoxy(32,63);printf("11x11");break;
	   	    case(3):*range=1;gotoxy(32,65);printf("  1");break;
		    case(4):*range=4;gotoxy(32,65);printf("  4");break;
		    case(5):*range=7;gotoxy(32,65);printf("  7");break;	
	   }
	}
	if (rightleft==2) {
	    switch(updown) {
	   	    case(1):*n=9;gotoxy(32,63);printf(" 9x9 ");break;
	   	    case(2):*n=12;gotoxy(32,63);printf("12x12");break;
	   	    case(3):*range=2;gotoxy(32,65);printf("  2");break;
		    case(4):*range=5;gotoxy(32,65);printf("  5");break;
		    case(5):*range=8;gotoxy(32,65);printf("  8");break;	
	   }
	}
	if (rightleft==3) {
	    switch(updown) {
	   	    case(1):*n=10;gotoxy(32,63);printf("10x10");break;
	   	    case(2):*n=13;gotoxy(32,63);printf("13x13");break;
	   	    case(3):*range=3;gotoxy(32,65);printf("  3");break;
		    case(4):*range=6;gotoxy(32,65);printf("  6");break;
		    case(5):*range=9;gotoxy(32,65);printf("  9");break;	
	   }
	}
   setcolor(7);

    }

  }
	
}

  void select_the_frame_in_the_options(rightleft,updown) 
  {
  	    gotoxy(5+15*rightleft,10*updown-5 );printf("%c%c%c%c%c%c%c",219,223,223,223,223,223,219);
	    gotoxy(5+15*rightleft,10*updown-4 );printf("%c     %c",221,222);
	    gotoxy(5+15*rightleft,10*updown-3 );printf("%c",221);                        //221-222 daha iyi
	    gotoxy(11+15*rightleft,10*updown-3);printf("%c",222);
		gotoxy(5+15*rightleft,10*updown-2 );printf("%c     %c",221,222);
		gotoxy(5+15*rightleft,10*updown-1 );printf("%c%c%c%c%c%c%c",219,220,220,220,220,220,219);
  	
  }
 void clean_the_frame_in_the_options(rightleft,updown)
 {
 	  	gotoxy(5+15*rightleft,10*updown-5 );printf("%c%c%c%c%c%c%c",218,196,196,196,196,196,191);
	    gotoxy(5+15*rightleft,10*updown-4 );printf("%c     %c",179,179);
	    gotoxy(5+15*rightleft,10*updown-3 );printf("%c",179);
	    gotoxy(11+15*rightleft,10*updown-3);printf("%c",179);
	    gotoxy(5+15*rightleft,10*updown-2 );printf("%c     %c",179,179);
		gotoxy(5+15*rightleft,10*updown-1 );printf("%c%c%c%c%c%c%c",192,196,196,196,196,196,217);
 		
 }
 
void how_to_play() 
{
   system("CLS");
   printf("\n                                   HOW TO PLAY ?\n\n");
   setcolor(12);printf(" 1)");setcolor(7);printf(" Your first aim is to find the structers and getting the best score.\n");
   setcolor(12);printf(" 2)");setcolor(7);printf(" You are able to choose the structers with your preference.\n");
   setcolor(12);printf(" 3)");setcolor(7);printf(" Also you are able to change the game board size and the range of the numbers in the options.\n");
   setcolor(12);printf(" 4)");setcolor(7);printf(" After selecting the structers, you have to choose a mode for playing.\n");
   setcolor(9 );printf("     a)");setcolor(7);printf(" Reiteration Mode: You have 3 lives, with a successfull move it fills.\n");
   setcolor(9 );printf("     b)");setcolor(7);printf(" Countdown Mode: You have 20 moves,after 20 moves the game is over.\n");
   setcolor(9 );printf("     c)");setcolor(7);printf(" Relax Mode: You can play as much as you want.\n");
   setcolor(12);printf(" 5)");setcolor(7);printf(" You are able to play with W-A-S-D and Enter.\n");
   setcolor(12);printf(" 6)");setcolor(7);printf(" When you press enter,you can stray just in symbol of plus(+).\n");
   setcolor(12);printf(" 7)");setcolor(7);printf(" If you see two same frame, they will be changed with enter.\n");
   
   
   getch();
   	
}

int structure_selecting_menu(int *e_selected,int *o_selected,int *c_selected,int *u_selected,int *f_selected,int *t_selected,int *l_selected,int *i_selected)						
{
				system("CLS");
				setcolor(7);
	
	                 printf("\n            Select the structers with Enter (Red means selected) ");	
						
		            gotoxy(10,5);printf("%c%c%c%c%c%c%c%c%c",219,223,223,223,223,223,223,223,219);  //E
					gotoxy(10,6);printf("%c %c%c%c%c%c %c",219,219,219,219,219,219,219);
			    	gotoxy(10,7);printf("%c %c     %c",219,219,219);
			    	gotoxy(10,8);printf("%c %c%c%c%c  %c",219,219,219,219,219,219,219);
			    	gotoxy(10,9);printf("%c %c     %c",219,219,219);
			    	gotoxy(10,10);printf("%c %c%c%c%c%c %c",219,219,219,219,219,219,219);
			    	gotoxy(10,11);printf("%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,219);
	       
	                gotoxy(26,5);printf("%c%c%c%c%c%c%c%c%c",219,223,223,223,223,223,223,223,219);  //O
					gotoxy(26,6);printf("%c %c%c%c%c%c %c",219,219,219,219,219,219,219,219);
			    	gotoxy(26,7);printf("%c %c   %c %c",219,219,219,219);
			    	gotoxy(26,8);printf("%c %c   %c %c",219,219,219,219);
			    	gotoxy(26,9);printf("%c %c   %c %c",219,219,219);
			    	gotoxy(26,10);printf("%c %c%c%c%c%c %c",219,219,219,219,219,219,219,219);
			    	gotoxy(26,11);printf("%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,219);
					
					gotoxy(42,5);printf("%c%c%c%c%c%c%c%c%c",219,223,223,223,223,223,223,223,219);  //C
					gotoxy(42,6);printf("%c %c%c%c%c%c %c",219,219,219,219,219,219,219,219);
			    	gotoxy(42,7);printf("%c %c     %c",219,219,219,219,219);
			    	gotoxy(42,8);printf("%c %c     %c",219,219,219,219,219);
			    	gotoxy(42,9);printf("%c %c     %c",219,219,219,219);
			    	gotoxy(42,10);printf("%c %c%c%c%c%c %c",219,219,219,219,219,219,219,219);
			    	gotoxy(42,11);printf("%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,219);
			    	
			    	gotoxy(58,5);printf("%c%c%c%c%c%c%c%c%c",219,223,223,223,223,223,223,223,219);  //U
					gotoxy(58,6);printf("%c %c   %c %c",219,219,219,219,219);
			    	gotoxy(58,7);printf("%c %c   %c %c",219,219,219,219);
			    	gotoxy(58,8);printf("%c %c   %c %c",219,219,219,219);
			    	gotoxy(58,9);printf("%c %c   %c %c",219,219,219);
			    	gotoxy(58,10);printf("%c %c%c%c%c%c %c",219,219,219,219,219,219,219,219);
			    	gotoxy(58,11);printf("%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,219);
			    	
			    	gotoxy(10,15);printf("%c%c%c%c%c%c%c%c%c",219,223,223,223,223,223,223,223,219);  //F
					gotoxy(10,16);printf("%c %c%c%c%c%c %c",219,219,219,219,219,219,219);
			    	gotoxy(10,17);printf("%c %c     %c",219,219,219);
			    	gotoxy(10,18);printf("%c %c%c%c%c  %c",219,219,219,219,219,219,219);
			    	gotoxy(10,19);printf("%c %c     %c",219,219,219);
			    	gotoxy(10,20);printf("%c %c     %c",219,219,219,219,219,219);
			    	gotoxy(10,21);printf("%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,219);
			    	
			    	gotoxy(26,15);printf("%c%c%c%c%c%c%c%c%c",219,223,223,223,223,223,223,223,219);
					gotoxy(26,16);printf("%c %c%c%c%c%c %c",219,219,219,219,219,219,219);
			    	gotoxy(26,17);printf("%c   %c   %c",219,219,219);
			    	gotoxy(26,18);printf("%c   %c   %c",219,219,219,219,219,219);
			    	gotoxy(26,19);printf("%c   %c   %c",219,219,219);
			    	gotoxy(26,20);printf("%c   %c   %c",219,219,219,219,219,219);
			    	gotoxy(26,21);printf("%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,219);
			    	
			    	gotoxy(42,15);printf("%c%c%c%c%c%c%c%c%c",219,223,223,223,223,223,223,223,219);  //C
					gotoxy(42,16);printf("%c %c     %c",219,219,219,219,219,219,219,219);
			    	gotoxy(42,17);printf("%c %c     %c",219,219,219,219,219);
			    	gotoxy(42,18);printf("%c %c     %c",219,219,219,219,219);
			    	gotoxy(42,19);printf("%c %c     %c",219,219,219,219);
			    	gotoxy(42,20);printf("%c %c%c%c%c%c %c",219,219,219,219,219,219,219,219);
			    	gotoxy(42,21);printf("%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,219);
			    	
			    	gotoxy(58,15);printf("%c%c%c%c%c%c%c%c%c",219,223,223,223,223,223,223,223,219);
					gotoxy(58,16);printf("%c  %c%c%c  %c",219,219,219,219,219);
			    	gotoxy(58,17);printf("%c   %c   %c",219,219,219);
			    	gotoxy(58,18);printf("%c   %c   %c",219,219,219,219,219,219);
			    	gotoxy(58,19);printf("%c   %c   %c",219,219,219);
			    	gotoxy(58,20);printf("%c  %c%c%c  %c",219,219,219,219,219);
			    	gotoxy(58,21);printf("%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,219);
			    	
			    	setcolor(9);
					gotoxy(58,25);printf("%c%c%c%c%c%c%c%c%c",219,223,223,223,223,223,223,223,219);
					gotoxy(58,26);printf("%c       %c",219,219);
			    	gotoxy(58,27);printf("%c       %c",219,219);
			    	gotoxy(58,28);printf("%c       %c",219,219);
			    	gotoxy(58,29);printf("%c       %c",219,219);
			    	gotoxy(58,30);printf("%c       %c",219,219);
			    	gotoxy(58,31);printf("%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,219);
			    	setcolor(7);
			    	gotoxy(60,28);printf("NEXT%c",26);
			    	

		  
		  
		  int rightleft=1,updown=1;
		  int ctrl[5][5]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   // bulundugumuz her kordinata göre bir kontrol var.Bulundugumuz kordinatta entera basinca eger deger 0 ise, oradaki rengi kirmizi yapip,
		                                                                       // kontrolü 1 yapiyor, eger bulundugumuz kordinattaki deger 1 ise, onu beyaz yapip kontrolü 0 yapiyor.
		  create_the_frame_in_the_selection_structers_menu(rightleft,updown);            // structure seçim menüsü açildiginda (1,1) konumundaki ilk çerçeve
		  int c=1;
		  while(c!=23) {
	
	
	  int c=getch();
	
	if(c=='w' || c=='W') {                                                                  // Oyunun diger w-a-s-d ve enter kontrolü ile ayni mantik. Ek olarak NEXT yazisinin üzerindeysek
		 if (updown>1) {                                                                   // sola ve daha fazla asagi gitmemizi engelleyen kontroller var.
			clean_the_frame_in_the_selection_structers_menu(rightleft,updown);
			updown--;
            create_the_frame_in_the_selection_structers_menu(rightleft,updown);
		    }}
	
	if (c=='s' || c=='S')  {                                                             
	    if (updown<2 ||  (rightleft==4 && updown<3 ) ) {                                  // eger en sagada isek updown 1 kez daha azalabilir.
			clean_the_frame_in_the_selection_structers_menu(rightleft,updown);
			updown++;
            create_the_frame_in_the_selection_structers_menu(rightleft,updown);

			}}

	if (c=='a' || c=='A')    {                                                         
	 	if (rightleft>1 && updown!=3) {                                                 // eger NEXT yazisinin üzerindeysek sola gidemeyiz.Çünkü updownimiz 3 olmus oluyor bu kordinat üzerinde.
			clean_the_frame_in_the_selection_structers_menu(rightleft,updown);
			rightleft--;
            create_the_frame_in_the_selection_structers_menu(rightleft,updown);
		    }}
	
	if(c=='d' || c=='D') { 
	    if (rightleft<4) {
			clean_the_frame_in_the_selection_structers_menu(rightleft,updown);
			rightleft++;
          	create_the_frame_in_the_selection_structers_menu(rightleft,updown);
			}}
	      	
	if(c==13)   {


		if ( rightleft==4 && updown==3) { system ("CLS");return 0; }   // eger enter tusuna basarken konumumuz next yazisinin üzerindeyse structure seçim menüsünden çikis saglaniyor. 
		   
		 
           
        if (ctrl[updown][rightleft]==0) {          // bulundugumuz kordinattaki ctrl 0 ise 1,1 ise 0 oluyor.
		ctrl[updown][rightleft]=1;
	}
        else {
		ctrl[updown][rightleft]=0;
		
	}
	paint_the_frame_in_the_selection_structers_menu(rightleft,updown,ctrl);       // ctrl ve konuma göre, structerin seçildigini ve iptal edildigini belirtmek için boyama gerçeklestiriliyor.
		
		if(ctrl[updown][rightleft]) {                        // eger structer seçilirse, structerlarin seçildigini belirten degiskenler 1 oluyor.
				if (updown==1) {
			switch (rightleft) {
				case(1):*e_selected=1;break;
				case(2):*o_selected=1;break;
				case(3):*c_selected=1;break;
				case(4):*u_selected=1;break;
				
			}
		}
		
		if (updown==2) {
			switch (rightleft) {
				case(1):*f_selected=1;break;
				case(2):*t_selected=1;break;
				case(3):*l_selected=1;break;
				case(4):*i_selected=1;break;
				
			}
		}
      } 
      else {
      		if (updown==1) {	                              // eger structerlar seçildikten sonra o structerdan vazgeçilirse, 1 olan structer seçim degiskenleri tekrar 0 oluyor.
				switch (rightleft) {
				case(1):*e_selected=0;break;
				case(2):*o_selected=0;break;
				case(3):*c_selected=0;break;
				case(4):*u_selected=0;break;
				
			}
		}
		
		if (updown==2) {
			switch (rightleft) {
				case(1):*f_selected=0;break;
				case(2):*t_selected=0;break;
				case(3):*l_selected=0;break;
				case(4):*i_selected=0;break;
				
			}
		}
      	
	  }
	     
    }   		  
}}


void clean_the_frame_in_the_selection_structers_menu(int rightleft,int updown)
{
		gotoxy(16*rightleft-7,10*updown-6);printf("           ");
		gotoxy(16*rightleft-7,10*updown-5);printf(" ");gotoxy(16*rightleft+3,10*updown-5);printf(" ");
		gotoxy(16*rightleft-7,10*updown-4);printf(" ");gotoxy(16*rightleft+3,10*updown-4);printf(" ");
		gotoxy(16*rightleft-7,10*updown-3);printf(" ");gotoxy(16*rightleft+3,10*updown-3);printf(" ");
		gotoxy(16*rightleft-7,10*updown-2);printf(" ");gotoxy(16*rightleft+3,10*updown-2);printf(" ");
		gotoxy(16*rightleft-7,10*updown-1);printf(" ");gotoxy(16*rightleft+3,10*updown-1);printf(" ");
		gotoxy(16*rightleft-7,10*updown  );printf(" ");gotoxy(16*rightleft+3,10*updown  );printf(" ");
		gotoxy(16*rightleft-7,10*updown+1);printf(" ");gotoxy(16*rightleft+3,10*updown+1);printf(" ");
		gotoxy(16*rightleft-7,10*updown+2);printf("           ");

}

void create_the_frame_in_the_selection_structers_menu(int rightleft,int updown) 
{
		gotoxy(16*rightleft-7,10*updown-6);printf("%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,191);
		gotoxy(16*rightleft-7,10*updown-5);printf("%c",179);gotoxy(16*rightleft+3,10*updown-5);printf("%c",179);
		gotoxy(16*rightleft-7,10*updown-4);printf("%c",179);gotoxy(16*rightleft+3,10*updown-4);printf("%c",179);
		gotoxy(16*rightleft-7,10*updown-3);printf("%c",179);gotoxy(16*rightleft+3,10*updown-3);printf("%c",179);
		gotoxy(16*rightleft-7,10*updown-2);printf("%c",179);gotoxy(16*rightleft+3,10*updown-2);printf("%c",179);
		gotoxy(16*rightleft-7,10*updown-1);printf("%c",179);gotoxy(16*rightleft+3,10*updown-1);printf("%c",179);
		gotoxy(16*rightleft-7,10*updown  );printf("%c",179);gotoxy(16*rightleft+3,10*updown  );printf("%c",179);
		gotoxy(16*rightleft-7,10*updown+1);printf("%c",179);gotoxy(16*rightleft+3,10*updown+1);printf("%c",179);
		gotoxy(16*rightleft-7,10*updown+2);printf("%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,217);
}

void paint_the_frame_in_the_selection_structers_menu(int rightleft,int updown,int ctrl[5][5])
{
	    if (ctrl[updown][rightleft]) setcolor(12);             // eger ctrl=1 ise çerçeveyi kirmiziya, degilse 0 a boyuyor.
	    else setcolor(7);
		gotoxy(16*rightleft-6,10*updown-5); printf("%c%c%c%c%c%c%c%c%c",219,223,223,223,223,223,223,223,219);  
		gotoxy(16*rightleft-6,10*updown-4); printf("%c",219);gotoxy(16*rightleft+2,10*updown-4); printf("%c",219);
		gotoxy(16*rightleft-6,10*updown-3); printf("%c",219);gotoxy(16*rightleft+2,10*updown-3); printf("%c",219);
		gotoxy(16*rightleft-6,10*updown-2); printf("%c",219);gotoxy(16*rightleft+2,10*updown-2); printf("%c",219);
		gotoxy(16*rightleft-6,10*updown-1); printf("%c",219);gotoxy(16*rightleft+2,10*updown-1); printf("%c",219);
		gotoxy(16*rightleft-6,10*updown  );printf("%c",219);gotoxy(16*rightleft+2,10*updown  ); printf("%c",219);
		gotoxy(16*rightleft-6,10*updown+1);printf("%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,219);
        setcolor(7);
}

void game_mode_selecting(int *mode) 
{
    gotoxy(27,6 );printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); 
	gotoxy(27,7 );printf("%c                      %c",219,219);
	gotoxy(27,8 );printf("%c   REITERATION MODE   %c",219,219);
	gotoxy(27,9 );printf("%c                      %c",219,219);
	gotoxy(27,10);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); 
	
	gotoxy(27,14);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); 
	gotoxy(27,15);printf("%c                      %c",219,219);
	gotoxy(27,16);printf("%c   COUNTDOWN   MODE   %c",219,219);
	gotoxy(27,17);printf("%c                      %c",219,219);
	gotoxy(27,18);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); 
	
	gotoxy(27,22);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); 
	gotoxy(27,23);printf("%c                      %c",219,219);
	gotoxy(27,24);printf("%c   RELAX       MODE   %c",219,219);
	gotoxy(27,25);printf("%c                      %c",219,219);
	gotoxy(27,26);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); 
			
			
		int c=1,updown=1;
		create_frame_in_the_mode_selecting(updown);    // ilk konumdaki çerçeve yazdiriliyor.
		while(1) {
	
	int c=getch();
	  
	
	if(c=='w' || c=='W') {
		 if (updown>1) {
			clean_frame_in_the_mode_selecting(updown);
			updown--;
            create_frame_in_the_mode_selecting(updown);
		    }}
	
	if (c=='s' || c=='S')  { 
	    if (updown<3 ) {
			clean_frame_in_the_mode_selecting(updown);
			updown++;
            create_frame_in_the_mode_selecting(updown);

			}}	
        if (c==13) break;
		}
	switch(updown) {                     //bulundugumuz konuma göre oyun modu seçiliyor.
		case(1):*mode=1;break;
		case(2):*mode=2;break;
	    case(3):*mode=3;break;
		
	}
		
}

void create_frame_in_the_mode_selecting(int updown)
{
	gotoxy(26,8*updown-3);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	gotoxy(26,8*updown-2);printf("%c",179);gotoxy(51,8*updown-2);printf("%c",179);
	gotoxy(26,8*updown-1);printf("%c",179);gotoxy(51,8*updown-1);printf("%c",179);
	gotoxy(26,8*updown  );printf("%c",179);gotoxy(51,8*updown  );printf("%c",179);
	gotoxy(26,8*updown+1);printf("%c",179);gotoxy(51,8*updown+1);printf("%c",179);
	gotoxy(26,8*updown+2);printf("%c",179);gotoxy(51,8*updown+2);printf("%c",179);
	gotoxy(26,8*updown+3);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
}
void clean_frame_in_the_mode_selecting(int updown)
{
	gotoxy(26,8*updown-3);printf("                          ");
	gotoxy(26,8*updown-2);printf(" ");gotoxy(51,8*updown-2);printf(" ");
	gotoxy(26,8*updown-1);printf(" ");gotoxy(51,8*updown-1);printf(" ");
	gotoxy(26,8*updown  );printf(" ");gotoxy(51,8*updown  );printf(" ");
	gotoxy(26,8*updown+1);printf(" ");gotoxy(51,8*updown+1);printf(" ");
	gotoxy(26,8*updown+2);printf(" ");gotoxy(51,8*updown+2);printf(" ");
	gotoxy(26,8*updown+3);printf("                          ");
	
}

void frame_of_the_game(int n,int range,int *e_selected,int *o_selected,int *c_selected,int *u_selected,int *f_selected,int *t_selected,int *l_selected,int *i_selected,int *mode) 
{
	system("CLS");
	int i,k=0;
                    

if (*mode==1) {                                                         // Mod yazilari ilk sola, asagidaysa yukari dogru yazdiriliyor.
	gotoxy(27,8 );printf("    REITERATION MODE");
    for (i=26;i>=16;i--) {
		Sleep ( 100 );
		gotoxy(i,8);printf("                        ");
		gotoxy(i+1,8);printf("    REITERATION MODE ");
	}
    }   
if (*mode==2) {
	gotoxy(27,16);printf("    COUNTDOWN   MODE");
 	for (i=26;i>=16;i--) {
		Sleep ( 100 );
		gotoxy(i,16);printf("                       ");
		gotoxy(i+1,16);printf("    COUNTDOWN   MODE ");
        }    
	for (i=16;i>=8;i--) {
		Sleep ( 100 );
		gotoxy(17,i  );printf("    COUNTDOWN   MODE");
		gotoxy(17,i+1);printf("                    ");
	}
	
	}
if (*mode==3) {
	gotoxy(27,24);printf("    RELAX       MODE");
	for (i=26;i>=16;i--) {
		Sleep ( 100 );
		gotoxy(i,24);printf("                       ");
		gotoxy(i+1,24);printf("    RELAX       MODE");
	}
	for (i=24;i>=8;i--) {
		Sleep ( 100 );
		gotoxy(17,i  );printf("    RELAX       MODE");
		gotoxy(17,i+1);printf("                     ");
	
	}
}
	Sleep ( 100 );
	gotoxy(40,8 );printf("is selected");
	Sleep ( 1000 );
	gotoxy(21,10 );printf("The Game Board Size      : %dx%d",n,n);
	Sleep ( 1000 );
	gotoxy(21,12);printf("The Range of The Numbers : %d",range);
	Sleep ( 1000 );
	gotoxy(21,14);printf("Selected Structers : ");
	    i=1;
		if (*e_selected==1) { Sleep ( 250 );gotoxy(40+2*i,  14);printf("E");        // tek tek tüm structerlar kontrol ediliyor. Seçilenler oyun baslarken yazdiriliyor.
	                          Sleep ( 250 );gotoxy(40+2*i+1,14);printf(",");i++;       }
		if (*o_selected==1) { Sleep ( 250 );gotoxy(40+2*i,  14);printf("O"); 
	                          Sleep ( 250 );gotoxy(40+2*i+1,14);printf(",");i++;       }   
		if (*c_selected==1) { Sleep ( 250 );gotoxy(40+2*i,  14);printf("C"); 
		                      Sleep ( 250 );gotoxy(40+2*i+1,14);printf(",");i++;       }
		if (*u_selected==1) { Sleep ( 250 );gotoxy(40+2*i,  14);printf("U"); 
		                      Sleep ( 250 );gotoxy(40+2*i+1,14);printf(",");i++;       }
		if (*f_selected==1) { Sleep ( 250 );gotoxy(40+2*i,  14);printf("F"); 
		                      Sleep ( 250 );gotoxy(40+2*i+1,14);printf(",");i++;       }
		if (*t_selected==1) { Sleep ( 250 );gotoxy(40+2*i,  14);printf("T"); 
		                      Sleep ( 250 );gotoxy(40+2*i+1,14);printf(",");i++;       }
		if (*l_selected==1) { Sleep ( 250 );gotoxy(40+2*i,  14);printf("L"); 
		                      Sleep ( 250 );gotoxy(40+2*i+1,14);printf(",");i++;       }
		if (*i_selected==1) { Sleep ( 250 );gotoxy(40+2*i,  14);printf("I");     
		                      Sleep ( 250 );gotoxy(40+2*i+1,14);printf(",");i++;       }
	   printf("\b ");
	
    
	for(i=1;i<=24;i++) {
	Sleep ( 125 );
	gotoxy(21,16);printf("THE GAME IS STARTING...");
	gotoxy(21+i,16);printf("                       ");
    }
	int j;
   Sleep ( 1000 );
   for (j=1;j<=5;j++) {                         // alttan baslayip üste dogru ekrana yazilmis yazilar siliniyor.
   	   for(i=1;i<=40;i++) {
   	   	    Sleep ( 15 );
			gotoxy(60-i,18-2*j);printf(" ");
		  }
   }

	           gotoxy(0,0);printf("%c",218);              // çerçevenin köseleri ve ortadaki Loading yazisi burada yaziliyor.
		       gotoxy(0,3*n+1);printf("%c",192);
		       gotoxy(4*n,0);printf("%c",191);
		       gotoxy(4*n,3*n+1);printf("%c",217);
		       gotoxy(2*n-4,n+n/2);printf("Loading...");
		    
			for(i=1;i<=3*n;i++) {                     // çerçevenin kenarlari burada olusturuluyor. i nin 5te biri kadar artan k da Loading yazisinin barini dolduruyor.
			    if (i%5==0) k++;
			    gotoxy(n+k,n+n/2-1);printf("%c",177);
			    Sleep( 50 );
			    gotoxy(0,i);printf("%c",179);
			    gotoxy(i,0);printf("%c",196);
			    gotoxy(4*n,3*n+1-i);printf("%c",179);
			    gotoxy(4*n-i,3*n+1);printf("%c",196);
			    }
		    for(i=3*n+1;i<=4*n-1;i++) {            // çerçeve tam kare gibi olmadigi için kalan bos kisimlar ve loading barinin dolmasina burada devam ediliyor.
			  	if ((i+3)%5==0) k++;
				gotoxy(n+k,n+n/2-1);printf("%c",177);
				Sleep( 50 );
				gotoxy(i,0);printf("%c",196);
			  	gotoxy(4*n-i,3*n+1);printf("%c",196);
			    }
			    gotoxy(4*n,3*n+1);printf("%c",193);
			for(i=4*n+1;i<=6*n;i++) {             // oyun bilgilerinin alacagi yan çerçeve burada olusturuluyor ve loading dolmaya devam ediyor.
			 	if ((i+3)%5==0) k++;
				gotoxy(n+k,n+n/2-1);printf("%c",177);
				Sleep( 50 );
				gotoxy(i,3*n+1);printf("%c",196);
			    }
			    gotoxy(6*n,3*n+1);printf("%c",217);
			for(i=1;i<=3*n-5;i++) { // score        // score yazisinin asagi inmesi ve yan çerçevenin saga kismi burada olusturuluyor.
			 	if ((i+3)%5==0) k++;
				gotoxy(n+k,n+n/2-1);printf("%c",177);
				Sleep( 50 );
				gotoxy(6*n,3*n+1-i);printf("%c",179);
			    gotoxy(5*n-2,i+1);printf("SCORE");   // score her yazildiginda , ondan önceki kordinatada bosluk yazisi yazdiriliyor. Böylece score kayiyormus gibi bir görüntü olusuyor.
			    gotoxy(5*n-2,i);printf("     ");
			  	}
			    gotoxy(n+k+1,n+n/2-1);printf("%c",177);
			for(i=3*n-4;i<=3*n+1;i++) {                            	
			    Sleep( 50 );
			    gotoxy(6*n,3*n+1-i);printf("%c",179);
                }
                gotoxy(6*n,0);printf("%c",191);
                gotoxy(6*n,3*n-5);printf("%c",180);
                gotoxy(6*n,4);printf("%c",180);
			    gotoxy(6*n,12);printf("%c",180);
			for(i=6*n-1;i>=4*n+1;i--) {            // saga çerçevenin son çizgileri burada çekiliyor.
			 	Sleep( 50 );
				gotoxy(i,0);printf("%c",196);
				gotoxy(i,3*n-5);printf("%c",196);
			    gotoxy(i,4);printf("%c",196);
				gotoxy(i,12);printf("%c",196);
				}
			    gotoxy(4*n,3*n-5);printf("%c",195);
			    gotoxy(4*n,0);printf("%c",194);
				gotoxy(4*n,4);printf("%c",195);	
                gotoxy(4*n,12);printf("%c",195);
			for (i=n;i<=3*n;i++) {		
			    gotoxy(i,n+n/2-1);printf(" "); // Loading yazisi burada siliniyor.
		        }
			    
			    
			gotoxy(9*n/2-2,2);                                   // çerçevenin saga üst kismina gidip sayi uzunluguna göre oyunun zorlugu yaziliyor.
			if (range==1) printf("Dif.  : Unplayable");	
			if (range==2 || range==3) printf("Dif.  : Easy");	
			if (range==4 || range==5 || range==6) printf("Dif.  : Medium");	
			if (range==7 || range==8) printf("Dif.  : Hard");	 
			if (range==9) printf("Dif.  : Expert");
				gotoxy(9*n/2-2,5);printf("Structure Points");
				
				
				gotoxy(9*n/2-1,7);printf("E=80     O=80");
				gotoxy(9*n/2-1,8);printf("C=70     U=70");
				gotoxy(9*n/2-1,9);printf("F=60     T=50");	
				gotoxy(9*n/2-1,10);printf("L=50     I=10");		    
			    
				gotoxy(2*n-4,n+n/2);printf("          ");
			    setcolor(15);
				gotoxy(5*n-1,3*n-2);printf("0");
			    
			    
			    if (*e_selected==1) { setcolor(10); gotoxy(9*n/2-1,7);printf("E");setcolor(7); }         // seçilen structerlarin yesil yanmasinin sebebi burasi.
			    if (*c_selected==1) { setcolor(10); gotoxy(9*n/2-1,8);printf("C");setcolor(7); }
			    if (*f_selected==1) { setcolor(10); gotoxy(9*n/2-1,9);printf("F");setcolor(7); }
			    if (*l_selected==1) { setcolor(10);gotoxy(9*n/2-1,10);printf("L");setcolor(7); }
			    if (*o_selected==1) { setcolor(10); gotoxy(9*n/2+8,7);printf("O");setcolor(7); }
			    if (*u_selected==1) { setcolor(10); gotoxy(9*n/2+8,8);printf("U");setcolor(7); }
			    if (*t_selected==1) { setcolor(10); gotoxy(9*n/2+8,9);printf("T");setcolor(7); }
			    if (*i_selected==1) { setcolor(10);gotoxy(9*n/2+8,10);printf("I");setcolor(7); }
			    
			gotoxy(9*n/2-2,1);                                         // çerçevenin saga üst kismina gidiliyor ve Oyun modu ne seçildiyse o yaziliyor.
			if (*mode==1) {
			    printf("Reiteration Mode"); 
			        gotoxy(9*n/2-2,3);printf("Lives : ");
			        setcolor(12);
			        gotoxy(9*n/2+6,3);printf("%c%c%c",3,3,3);
			        setcolor(7);
		    }
			
			if (*mode==2) {
			    printf("Countdown Mode");
			        gotoxy(9*n/2-2,3);printf("Left Move : ");
			        setcolor(12);
					gotoxy(9*n/2+10,3);
					printf("20");
					setcolor(7);
			
		    }
			if (*mode==3) {
			    printf("Relax Mode"); 
			        gotoxy(9*n/2-2,3);printf("Limitless");
		   }
}

void create_the_first_numbers(int gameboard[20][20],int n,int range,int *e_selected,int *o_selected,int *c_selected,int *u_selected,int *f_selected,int *t_selected,int *l_selected,int *i_selected)
{
int i,j,live=3,mode=3,score=0;   //buradaki live,mode ve score bilgileri geçiçi olarak tanimlandi. Çünkü kullaniciya matrisi sunmadan önce, seçtigi structerlari temizleyecegiz, yeni bir fonksiyon yerine,
srand(time(NULL));              // hazirda bulunan search_structer fonksiyonumuzu çagiracagiz, bizden istedigi degiskenler live,mode ve score indisi, fakat onlarin burada bir görevi yok.Degiskenlerin isimleri
  	for(i=1;i<=n;i++) {        // live,mode ve score dan farkli olarak seçilebilirdi, belirleyici olmasi açisindan ayni isimler kullanildi.
			for (j=1;j<=n;j++) {
		        gameboard[i][j]=rand()%range+1;  // kullanicinin seçtigi uzunluga göre rastgele atamalar burada yapiliyor.
                  
			}
	}
           int ctrl=1,t=0;
		while (ctrl!=score) {   // geçici score degiskenimiz mainin içinde oldugu için score degismeyene kadar structerlari temizleme islemi yapilacak.
		ctrl=score;
		
		search_structure(gameboard,n,&score,e_selected,o_selected,c_selected,u_selected,f_selected,t_selected,l_selected,i_selected,&live,&mode);
				for(i=1;i<=n;i++) {
			        for (j=1;j<=n;j++) {
			            if (gameboard[i][j]==0) gameboard[i][j]=rand()%range+1;  // structerlar temizlendikten yani bulunup 0 a esitlendikten sonra, yerlerine yeni sayilar ataniyor.
                   }
               }
		}
	    clean_the_right_window(n);  // search structer fonksiyonumuz saga çerçeveye buldugu structerlari yazdigi için, bu fonksiyonu en son orayi temizlemek için kullaniyoruz.
	for(i=1;i<=n;i++) {
		if (i%2==1) {
			for (j=1;j<=n;j++) {
				Sleep ( 10 );
			    colored_numbers(gameboard,i,j);
				gotoxy(4*j-3,3*i-2);printf("%c%c%c",218,196,191);
				gotoxy(4*j-3,3*i-1);printf("%c%d%c",179,gameboard[i][j],179);
                gotoxy(4*j-3,3*i  );printf("%c%c%c",192,196,217); 
	    	}}
        if (i%2==0) {                                                     // eger i mod 2 = 0 ise sagadan sola, i mod 2 = 1 ise soldan saga yazdirarak, farkli bir efekt katiyor.
        	for (j=n;j>=1;j--) {
				Sleep ( 10 );
			    colored_numbers(gameboard,i,j);
				gotoxy(4*j-3,3*i-2);printf("%c%c%c",218,196,191);
				gotoxy(4*j-3,3*i-1);printf("%c%d%c",179,gameboard[i][j],179);
                gotoxy(4*j-3,3*i  );printf("%c%c%c",192,196,217);	
		   }}
   
   
   }

}


void colored_numbers(int gameboard[20][20],int i,int j)    //gameboard üzerindeki sayiyi ve çerçevesini o sayiya göre boyuyor.
{
		switch (gameboard[i][j]) {
			case(0): setcolor(0);break;
			case(1): setcolor(9);break;
		    case(2): setcolor(10);break;
		    case(3): setcolor(11);break;
		    case(4): setcolor(12);break;
		    case(5): setcolor(13);break;
		    case(6): setcolor(14);break;
		    case(7): setcolor(7);break;
		    case(8): setcolor(3);break;
		    case(9): setcolor(5);break;
		}
}

void frame_1_cleaning(int j,int i,int gameboard[20][20])                //  sayinin dogal çerçevesi
{
	colored_numbers(gameboard,i,j);
	   gotoxy(4*j-3,3*i-2);printf("%c%c%c",218,196,191);
	   gotoxy(4*j-3,3*i-1);printf("%c%d%c",179,gameboard[i][j],179);
       gotoxy(4*j-3,3*i  );printf("%c%c%c",192,196,217);	
}
void frame_2_selecting(int j,int i,int gameboard[20][20])             //  serbest seçim çerçevesi, serbestçe dolasirken bu çerçeve kullaniliyor.
{
	
	colored_numbers(gameboard,i,j);
	   gotoxy(4*j-3,3*i-2);printf("%c%c%c",201,223,187);
	   gotoxy(4*j-3,3*i-1);printf("%c%d%c",221,gameboard[i][j],222);    //221-222 daha iyi
       gotoxy(4*j-3,3*i  );printf("%c%c%c",200,220,188);
}
void frame_3_changing(int j,int i,int gameboard[20][20])            // sadece 2 sayinin yerini degistirecegimiz zaman bu çerçeve kullaniliyor.
{
	colored_numbers(gameboard,i,j);
	   gotoxy(4*j-3,3*i-2);printf("%c%c%c",201,205,187);
	   gotoxy(4*j-3,3*i-1);printf("%c%d%c",186,gameboard[i][j],186);
       gotoxy(4*j-3,3*i  );printf("%c%c%c",200,205,188);
}

void swap_two_numbers(int j,int i,int gameboard[20][20],int rightleft, int updown)  // bulundugu konuma göre, önceki konumdaki sayi ile yerini degistiriyor.
{
    int temp;
    if (rightleft==1)  {
         	temp=gameboard[i][j-1];
         	gameboard[i][j-1]=gameboard[i][j];
         	gameboard[i][j]=temp;
	        } 
	if (rightleft==-1)  {
         	temp=gameboard[i][j+1];
         	gameboard[i][j+1]=gameboard[i][j];
         	gameboard[i][j]=temp;
	        } 
	if (updown==-1)  {
         	temp=gameboard[i+1][j];
         	gameboard[i+1][j]=gameboard[i][j];
         	gameboard[i][j]=temp;
	    } 
	if (updown==1)  {
         	temp=gameboard[i-1][j];
         	gameboard[i-1][j]=gameboard[i][j];
         	gameboard[i][j]=temp;
	    } 
}
void search_structure(int gameboard[20][20],int n,int *score,int *e_selected,int *o_selected,int *c_selected,int *u_selected,int *f_selected,int *t_selected,int *l_selected,int *i_selected,int *live,int *mode)
{
    setcolor(7);
    int a,b;                                                                                 // ilk basta tüm structerlar bulunmamis olarak kabul ediliyor, bunlarin kullanilmasinin sebebi, bir kere bir harf 
    int e_found=0,o_found=0,c_found=0,u_found=0,f_found=0,t_found=0,l_found=0,i_found=0;    // bulunduktan sonra ayni structerin içinde baska harfinde olmasi, onun puanini saymamak için bu degiskenler kullanildi.

    for (a=1;a<=n-2;a++) {
	    for (b=1;b<=n-2;b++){                                            
                                  // sadece structer seçim menüsünde seçilen structerlar aramaya katiliyor.                    
	/*E*/       if (*e_selected==1 && gameboard[a][b]==gameboard[a][b+1] && gameboard[a][b]==gameboard[a][b+2] && gameboard[a][b]==gameboard[a+1][b] && gameboard[a][b]==gameboard[a+1][b+1] && gameboard[a][b]==gameboard[a+2][b] && gameboard[a][b]==gameboard[a+2][b+1] && gameboard[a][b]==gameboard[a+2][b+2] ) { 
				    gameboard[a][b]=0;gameboard[a][b+1]=0;gameboard[a][b+2]=0;gameboard[a+1][b]=0;gameboard[a+1][b+1]=0;gameboard[a+2][b]=0;gameboard[a+2][b+1]=0;gameboard[a+2][b+2]=0;
		                *score=*score+80; e_found=1;
					    gotoxy(5*n-2,14);printf("%c%c%c%c ",219,219,219,219);
			    	    gotoxy(5*n-2,15);printf("%c    ",219);
			    	    gotoxy(5*n-2,16);printf("%c%c%c  ",219,219,219,219);
			    	    gotoxy(5*n-2,17);printf("%c    ",219);
			    	    gotoxy(5*n-2,18);printf("%c%c%c%c ",219,219,219,219);
			   }		
	/*O*/ 	    else if (*o_selected==1 && e_found==0 && gameboard[a][b]==gameboard[a][b+1] && gameboard[a][b]==gameboard[a][b+2] && gameboard[a][b]==gameboard[a+1][b] && gameboard[a][b]==gameboard[a+1][b+2] && gameboard[a][b]==gameboard[a+2][b] && gameboard[a][b]==gameboard[a+2][b+1] && gameboard[a][b]==gameboard[a+2][b+2] ) { 
			        gameboard[a][b]=0;gameboard[a][b+1]=0;gameboard[a][b+2]=0;gameboard[a+1][b]=0;gameboard[a+1][b+2]=0;gameboard[a+2][b]=0;gameboard[a+2][b+1]=0;gameboard[a+2][b+2]=0;
			            *score=*score+80; o_found=1;
					    gotoxy(5*n-2,14);printf("%c%c%c%c%c",219,219,219,219,219);
			    	    gotoxy(5*n-2,15);printf("%c   %c",219,219);
			    	    gotoxy(5*n-2,16);printf("%c   %c",219,219);
			    	    gotoxy(5*n-2,17);printf("%c   %c",219,219);
			    	    gotoxy(5*n-2,18);printf("%c%c%c%c%c",219,219,219,219,219);
			
		     	}
	/*C*/ 	    else if (*c_selected==1 && e_found==0 && o_found==0 && gameboard[a][b]==gameboard[a][b+1] && gameboard[a][b]==gameboard[a][b+2] && gameboard[a][b]==gameboard[a+1][b] && gameboard[a][b]==gameboard[a+2][b] && gameboard[a][b]==gameboard[a+2][b+1] && gameboard[a][b]==gameboard[a+2][b+2] ) { 
				    gameboard[a][b]=0;gameboard[a][b+1]=0;gameboard[a][b+2]=0;gameboard[a+1][b]=0;gameboard[a+2][b]=0;gameboard[a+2][b+1]=0;gameboard[a+2][b+2]=0;
		                *score=*score+70; c_found=1;
			            gotoxy(5*n-2,14);printf("%c%c%c%c",219,219,219,219);
			    	    gotoxy(5*n-2,15);printf("%c    ",219);
			    	    gotoxy(5*n-2,16);printf("%c    ",219);
			    	    gotoxy(5*n-2,17);printf("%c    ",219);
			    	    gotoxy(5*n-2,18);printf("%c%c%c%c",219,219,219,219);
			   }
	/*U*/   	else if (*u_selected==1 && e_found==0 && o_found==0 && c_found==0 && gameboard[a][b]==gameboard[a][b+2] && gameboard[a][b]==gameboard[a+1][b] && gameboard[a][b]==gameboard[a+1][b+2] && gameboard[a][b]==gameboard[a+2][b] && gameboard[a][b]==gameboard[a+2][b+1] && gameboard[a][b]==gameboard[a+2][b+2] ) { 
			        gameboard[a][b]=0;gameboard[a][b+2]=0;gameboard[a+1][b]=0;gameboard[a+1][b+2]=0;gameboard[a+2][b]=0;gameboard[a+2][b+1]=0;gameboard[a+2][b+2]=0;
			            *score=*score+70; u_found=1;
			            gotoxy(5*n-2,14);printf("%c   %c",219,219);
			            gotoxy(5*n-2,15);printf("%c   %c",219,219);
			    	    gotoxy(5*n-2,16);printf("%c   %c",219,219);
			    	    gotoxy(5*n-2,17);printf("%c   %c",219,219);
			    	    gotoxy(5*n-2,18);printf("%c%c%c%c%c",219,219,219,219,219);
			
			   }
	/*F*/ 	    else if (*f_selected==1 && e_found==0 && o_found==0 && c_found==0 && u_found==0 && gameboard[a][b]==gameboard[a][b+1] && gameboard[a][b]==gameboard[a][b+2] && gameboard[a][b]==gameboard[a+1][b] && gameboard[a][b]==gameboard[a+1][b+1] && gameboard[a][b]==gameboard[a+2][b] ) { 
				    gameboard[a][b]=0;gameboard[a][b+1]=0;gameboard[a][b+2]=0;gameboard[a+1][b]=0;gameboard[a+1][b+1]=0;gameboard[a+2][b]=0;
		                *score=*score+60; f_found=1;
			            gotoxy(5*n-2,14);printf("%c%c%c%c ",219,219,219,219);
			    	    gotoxy(5*n-2,15);printf("%c   ",219);
			    	    gotoxy(5*n-2,16);printf("%c%c%c  ",219,219,219);
			    	    gotoxy(5*n-2,17);printf("%c    ",219);
			            gotoxy(5*n-2,18);printf("%c    ",219);
			
			   }
	/*T*/ 	    else if (*t_selected==1 && e_found==0 && o_found==0 && c_found==0 && u_found==0 && f_found==0 && gameboard[a][b]==gameboard[a][b+1] && gameboard[a][b]==gameboard[a][b+2] && gameboard[a][b]==gameboard[a+1][b+1] && gameboard[a][b]==gameboard[a+2][b+1] ) { 
				    gameboard[a][b]=0;gameboard[a][b+1]=0;gameboard[a][b+2]=0;gameboard[a+1][b+1]=0;gameboard[a+2][b+1]=0;
		                *score=*score+50; t_found=1;
			            gotoxy(5*n-2,14);printf("%c%c%c%c%c",219,219,219,219,219,219);
			    	    gotoxy(5*n-2,15);printf("  %c  ",219);
			    	    gotoxy(5*n-2,16);printf("  %c  ",219);
			    	    gotoxy(5*n-2,17);printf("  %c  ",219);
			    	    gotoxy(5*n-2,18);printf("  %c  ",219);
			   }
	/*L*/ 	    else if (*l_selected==1 && e_found==0 && o_found==0 && c_found==0 && u_found==0 && f_found==0 && t_found==0 && gameboard[a][b]==gameboard[a+1][b] && gameboard[a][b]==gameboard[a+2][b] && gameboard[a][b]==gameboard[a+2][b+1] && gameboard[a][b]==gameboard[a+2][b+2] ) { 
			        gameboard[a][b]=0;gameboard[a+1][b]=0;gameboard[a+2][b]=0;gameboard[a+2][b+1]=0;gameboard[a+2][b+2]=0;
			            *score=*score+50; l_found=1;
		                gotoxy(5*n-2,14);printf("%c     ",219);
			    	    gotoxy(5*n-2,15);printf("%c     ",219);
			    	    gotoxy(5*n-2,16);printf("%c     ",219);
			    	    gotoxy(5*n-2,17);printf("%c     ",219);
			    	    gotoxy(5*n-2,18);printf("%c%c%c%c ",219,219,219,219);
		       }
	   }
	} 
			              // I harfinin ayri olarak aranmasinin sebebi, digerlerinden farkli olmasi, digerleri için 1 den n-2 ye kadar structerlari taramak yetiyordu
			             // fakat (n-2). sutunundan sonrada I harfi olabilir, bu yüzden bu structerin kontrolünü ayri olarak yapiyoruz.
	/*I*/       if (*i_selected==1 && e_found==0 && o_found==0 && c_found==0 && u_found==0 && f_found==0 && t_found==0 && l_found==0  )  {
				 
				    for (a=1;a<=n-2;a++) {
					    for (b=1;b<=n;b++) {
			                if (gameboard[a][b]==gameboard[a+1][b] && gameboard[a][b]==gameboard[a+2][b] ) {   
					            gameboard[a][b]=0;gameboard[a+1][b]=0;gameboard[a+2][b]=0;
		                        *score=*score+10;i_found=1;
					            gotoxy(5*n-2,14);printf(" %c%c%c ",219,219,219);
			    	            gotoxy(5*n-2,15);printf("  %c  ",219);
			    	            gotoxy(5*n-2,16);printf("  %c  ",219);
			    	            gotoxy(5*n-2,17);printf("  %c  ",219);
			    	            gotoxy(5*n-2,18);printf(" %c%c%c ",219,219,219);
			}
				}}}
	 
        if (*mode==1) {           // eger reiteration modunda oynuyorsak ve structerlardan en az birini bulduysak, canimiz tekrar fulleniyor.
		    if ( e_found==1 || o_found==1 || c_found==1 || u_found==1 || f_found==1 || t_found==1 || l_found==1 || i_found==1) {
          	    *live=4;   // 3 yerine 4 seçilmesinin sebebi : bu algoritma sürekli structer taradigi için bulamayana kadar devam edecek, son kez bulamadiginda tekrar buradan geçecek ve böylece 
		    }             // son geçiste if'in else kolunda 1 eksilerek 3 olmus olacak.
		    else {
		        *live=*live-1;
	        }
		        setcolor(12);
		        if (*live==3) { gotoxy(9*n/2+6,3);printf("%c%c%c",3,3,3); }
		        if (*live==2) { gotoxy(9*n/2+6,3);printf("%c%c ",3,3); }
		        if (*live==1) { gotoxy(9*n/2+6,3);printf("%c  ",3); }
		        setcolor(7);
	    }
}

void cleaner(int gameboard[20][20],int n )             // search_structer fonksiyonumuz, structerlari bulduktan sonra 0 a esitliyor, bu fonksiyonumuz ise 0 olan sayilari, direkt olarak siliyor.
{     
	int i,j;
	
	for (i=1;i<=n;i++) {
		for (j=1;j<=n;j++) {
			if (gameboard[i][j]==0) {
	            
				gotoxy(4*j-3,3*i-2);printf("   ");
	            gotoxy(4*j-3,3*i-1);printf("   ");
                gotoxy(4*j-3,3*i  );printf("   ");
			}
	    }
    }
				
}

void slipper(int gameboard[20][20],int n,int x)    
{
	int i,j,k,t,m;
	t=x;

        for (k=1;k<=3;k++){        // kaydirma 3 kere yapiliyor,çünkü structer boyutlarimiz 3 birim uzunlukta
		Sleep ( t );
	        for (i=n;i>=2;i--) {                               // matrisin altindan baslayip üste dogru kontrol ediliyor
		        for (j=1;j<=n;j++) {
			        if (gameboard[i][j]==0 && gameboard[i-1][j]!=0 ) {                  // eger deger 0 ise     // bir üstteki degerin 0 a esit olmadigini kontrol ediyoruz cunku cok fazla silinme olunca bekleme oluyor
		                
						gameboard[i][j]=gameboard[i-1][j];     // o deger üstteki eleman ile yer degistiriyor.
		                gameboard[i-1][j]=0;
		
		                    colored_numbers(gameboard,i,j);
							gotoxy(4*j-3,3*i-2);printf("%c%c%c",218,196,191);
	                        gotoxy(4*j-3,3*i-1);printf("%c%d%c",179,gameboard[i][j],179);
                            gotoxy(4*j-3,3*i  );printf("%c%c%c",192,196,217);              
	                }          
	            }       
			}  
	    cleaner(gameboard,n); // 1 kez kaydirma gerçeklestirildikten sonra 0 olan sayilarin üzerine cleaner fonksiyonu ile bosluk karakteri yaziliyor. Böylece orada hiçbirsey yokmus gibi gözüküyor.
	    }
			
}

void new_numbers(int gameboard[20][20],int n,int range,int x)   // kaydirma islemi bittikten sonra üstte kalan 0 lar için yeni degerler ataniyor
{
	srand(time(NULL));
	int i,j,t;
	t=x;
	    for (i=1;i<=3;i++) {
		Sleep ( t );                                    
		    for (j=1;j<=n;j++) {
			    if (gameboard[i][j]==0) {
		            gameboard[i][j]=rand()%range+1;
                    colored_numbers(gameboard,i,j);
				        gotoxy(4*j-3,3*i-2);printf("%c%c%c",218,196,191);
				        gotoxy(4*j-3,3*i-1);printf("%c%d%c",179,gameboard[i][j],179);
                        gotoxy(4*j-3,3*i  );printf("%c%c%c",192,196,217);	
	        
			    }
		    }
	    } 	
}

void clean_the_right_window(int n)    // search_structer fonksiyonu structerlari bulduktan sonra saga kisma onlarin büyük harflerini yazmakla görevli, bu ise structerlar bulunduktan sonra onlari silmekle görevli.
{			
	gotoxy(5*n-2,14);printf("     ");
	gotoxy(5*n-2,15);printf("     ");
	gotoxy(5*n-2,16);printf("     ");
	gotoxy(5*n-2,17);printf("     ");
	gotoxy(5*n-2,18);printf("     ");
}

void score_data(int indis,int n,int range,int mode,char name[50],int score)   // oynanan oyun bilgilerinin tutulacagi fonksiyon
{
   
   
   
   
   
   int i=0;
   while (name[i]!='\0') {                   // girilen ismi, indisimizdeki yere göre yeni matrise kopyaliyoruz.
   	  nick[indis][i]=name[i];
   	  i++;
   }
   matrixsize[indis]=n;
   numbersize[indis]=range;
   wonscore[indis]=score;
   playedmode[indis]=mode; 
   
   system("CLS");
   for (i=indis;i>=0;i--) {                                   // son oynanan oyundan ilk oynanan oyuna kadar, oyun bilgilerini ekrana yazdiriyor.
   	    printf("Name                 : %s \n",nick[i]);
   	    printf("Game Board Size      : %dx%d \n",matrixsize[i],matrixsize[i]);
   	    printf("Range of the Numbers : %d \n",numbersize[i]);
   	    printf("Score                : ");setcolor(12);printf("%d\n",wonscore[i]);setcolor(7);
   	    printf("Difficulty           : ");
   	    	if (numbersize[i]==1) printf("Unplayable\n");	
			else if (numbersize[i]==2 || numbersize[i]==3) printf("Easy\n");	
			else if (numbersize[i]==4 || numbersize[i]==5 || numbersize[i]==6) printf("Medium\n");	
			else if (numbersize[i]==7 || numbersize[i]==8) printf("Hard\n");	 
			else if (numbersize[i]==9) printf("Expert\n");
		printf("Played Game Mode     : ");
		if      (playedmode[i]==1) printf("Reiteration Mode\n");
   	    else if (playedmode[i]==2) printf("Countdown Mode\n");
   	    else if (playedmode[i]==3) printf("Relax Mode\n");
   	    printf("-----------------------------------------\n");   
   }
}

void setcolor(int ForgC)
{
    WORD wColor = ( ForgC & 0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
    return;
}
	
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;  
    if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}

void cursor_hide(int visible)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursoInfo;
	CursoInfo.dwSize = 1;
	CursoInfo.bVisible = visible;
	SetConsoleCursorInfo(hConsole, &CursoInfo);
}
