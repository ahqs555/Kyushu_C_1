#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#define MAX_LINE_SIZE 30

static int n = 0;//学生人数 


typedef struct//学生
{
    char name[20];
    int eigo;
    int koku;
    int su;	 
} stu;
static stu students[50];//学生配列 
stu inputStu()
{
	stu student;
	printf( "名前 : ");
	scanf("%s",&student.name);
	printf( "英語 : ");
	scanf("%d",&student.eigo);
	printf( "国語 : ");
	scanf("%d",&student.koku);
	printf( "数学 : ");
	scanf("%d",&student.su);
	return student;
}

void printStu( stu student )//学生情報出力関数
{
   printf( "名前 : %s\n",student.name);
   printf( "英語 : %d\n",student.eigo);
   printf( "国語 : %d\n",student.koku);
   printf( "数学 : %d\n",student.su);
}

stu input()
{
	stu temp;
	temp = inputStu();
	//printf("%d人目の成績は入力しました！\n",n+1);
	return temp;
}
int issame(char a[20],char b[20])//同じかどうが判断する関数null and different return 0,same return 1
{	
        if(a&&b){
        	if(strcmp(a,b)==0)
        {
			return 1;
		}
		else
		{
			return 0;
		}
		}
		else{
			return 0;
		}
}

int strtoint(char a[10])// intに変換 
{
	int temp;
	temp = atoi(a);
	return temp; 
	
}


void readcsv(char file_name[20])
{
	
	FILE *fp;
	fp = fopen(file_name,"r");
	
	char line[MAX_LINE_SIZE];
    char *p = NULL;
    char *temp[10];
    int oldn;
    
    while(fgets(line,MAX_LINE_SIZE,fp) != NULL) {
        
        int i = 1;
        p = strtok(line,",");
   		if(p)
		temp[0] = p; 
        
   		while(p)
		{
    		p=strtok(NULL,",");
			temp[i] = p;
			i = i+1;
	
		}
		strcpy(students[n].name, temp[0]);
		students[n]. eigo = strtoint(temp[1]);
		students[n]. koku = strtoint(temp[2]);
		students[n]. su = strtoint(temp[3]);
		n = n+1;  
    }
    
    fclose (fp);
    printf("%d人目の成績は入力しました！\n",n-oldn+1);
    		
}
float ave(int a[50])//平均値計算 
{		int i = 0;
		int sum = 0;
		for(i;i< n;i++){
			sum = a[i] + sum;
		}
		return sum/n;
}
int max(int a[50])//最大値計算 
{
	int i = 0;
	int max = 0;
	for(i;i<n;i++){
		if(max <= a[i]){
			max = a[i];
		} 
	}
	return max;
}

int min(int a[50])//最小値計算 
{
	int i = 0;
	int min = 100;
	for(i;i< n;i++){
		if(min >= a[i]){
			min = a[i];
		} 
	}
	return min;
}

float sta(int a[50])//標準偏差計算 
{
	int i;
	float temp;
	float sum = 0;
	temp = ave(a);
	for(i = 0;i<n;i++){
		
		sum = pow((temp-a[i]),2)+sum;	
	}
	return sqrt(sum/n);
} 

void output(){
	int i;
	int eigo[50],koku[50],su[50];
	for(i = 0;i< n;i++){
	  	eigo[i] = students[i].eigo;
	  	koku[i] = students[i].koku;
	  	su[i] = students[i].su;
	}
	printf("---成績一覧---\n");
	printf("登録者数:%d人\n",n);
	printf("             英語     国語     数学     合計\n");
	printf("    平均: %5.1f点  %5.1f点  %5.1f点  %5.1f点\n",ave(eigo),ave(koku),ave(su),ave(eigo)+ave(koku)+ave(su));
	printf("  最高点: %5d点  %5d点  %5d点  %5d点\n",max(eigo),max(koku),max(su),max(eigo)+max(koku)+max(su));
	printf("  最低点: %5d点  %5d点  %5d点  %5d点\n",min(eigo),min(koku),min(su),min(eigo)+min(koku)+min(su));
	printf("標準偏差:   %5.2f    %5.2f    %5.2f    %5.2f\n",sta(eigo),sta(koku),sta(su),sta(eigo)+sta(koku)+sta(su));
}
void opfile(char fname[20],char cmd[10])//ファイルに出力 
{
	FILE *fp;
	int i,d;
	
	fp =  fopen(fname,"w");
	if(fp==NULL)
	{
		printf("File cannot open!");
		exit(0);
	}
	if(cmd){
		if(issame(cmd,"-u")){
				for(i=0;i<n;i++){
					fprintf(fp,"%s\n",students[i].name);
		
				}
				fclose(fp);
				printf("出力成功!\n");
		}
		else if(issame(cmd,"-e")){
			fprintf(fp,"---英語の成績---\n");
    		fprintf(fp,"名前  点数\n");
			for(i=0;i<n;i++){
					fprintf(fp,"%s,%d\n",students[i].name,students[i].eigo);
					
				}
				fclose(fp);
				printf("出力成功!\n");
		}
		else if(issame(cmd,"-l")){
			fprintf(fp,"---国語の成績---\n");
    		fprintf(fp,"名前  点数\n");
				for(i=0;i<n;i++){
					fprintf(fp,"%s,%d\n",students[i].name,students[i].koku);
		
				}
				fclose(fp);
				printf("出力成功!\n");
		}
		else if(issame(cmd,"-m")){
			fprintf(fp,"---数学の成績---\n");
    		fprintf(fp,"名前  点数\n");
			for(i=0;i<n;i++){
					fprintf(fp,"%s,%d\n",students[i].name,students[i].su);
		
				}
				fclose(fp);
				printf("出力成功!\n");
		}
		else if(issame(cmd,"only_o")){
				for(i=0;i<n;i++){
					fprintf(fp,"%s,%d,%d,%d\n",students[i].name,students[i].eigo,students[i].koku,students[i].su);
		
				}
				fclose(fp);
				printf("出力成功!\n");
		}
		else{
			printf("コマンドエラー！\n");
		}
		
	}	
} 


int main()
{

		
	
	while(1)
	{
		
		

		char cmd[50];	
    	char *icmd[10];
    	char *p;
    	int i = 1;
		int j; 
		
		
		printf("q:終了\nh:ヘルプ\n");
		
		fflush(stdin);
		gets(cmd); 
		p=strtok(cmd," ");
    	if(p)
		icmd[0] = p; 

        
    	while(p)
		{
    		p=strtok(NULL," ");
			icmd[i] = p;
			i = i+1;
		}	
		
		if(issame(icmd[0],"q"))// 終了かどうか判断する 
		{
			break;	
		}
		if(issame(icmd[0],"h"))// ヘルプ
		{
			printf("iコマンド　試験結果の入力\n");
			printf("oコマンド　集計結果の表示\n");
			printf("oコマンドのオプション\n");
			printf("	-u:登録されている生徒の名前の一覧の表示\n");
			printf("	-n name:指定した生徒の成績を表示\n");
			printf("	-e:英語の成績の表示（点数の高い順）\n");
			printf("	-l:国語の成績の表示（点数の高い順）\n");
			printf("	-m:数学の成績の表示（点数の高い順）\n");
			printf("	-f file_name:結果の出力\n");			
		}
		if(issame(icmd[0],"i"))//入力コマンド 
		{
			if(icmd[1])
			{
				if(issame(icmd[1],"-f"))//ファイルから入力 
				{
					readcsv(icmd[2]);
				}
				else// 省力入力 
				{
					strcpy(students[n].name, icmd[1]);
					students[n]. eigo = strtoint(icmd[2]);
					students[n]. koku = strtoint(icmd[3]);
					students[n]. su = strtoint(icmd[4]);
					printf("%d人目の成績は入力しました！\n",n+1);
					n = n+1;
				}
				
 
			} 
			else//普通入力    
			{
				printf("%d人目の成績は入力してください！\n",n+1);
				students[n] = input();
				n = n+1;
			}
			
			
		}
	  	if(issame(icmd[0],"o"))
		  {	
		  int flag = 0;
		  int cmdflag = 1;
	
		  	for(i = 0;i< 10;i++)//oコマンドの前処理 
			  {

		  		if(icmd[i] == NULL)
		  		break;
		  		if(issame(icmd[i],"-f")){
		  			flag = i;
				  }

				if(issame(icmd[i],"-u")||issame(icmd[i],"-n")||issame(icmd[i],"-e")||issame(icmd[i],"-l")||issame(icmd[i],"-m")){
					cmdflag = i;
				}	
			  }	
			  	
		  	//o -uコマンド 
			if(issame(icmd[cmdflag],"-u")){
				printf("登録学生一覧\n");
				for(i = 0;i< n;i++){
					printf("%s\n",students[i].name);
				}
				if(flag != 0){
					opfile(icmd[flag+1],icmd[cmdflag]);
				}
				
				
			}
			//o -nコマンド 
			else if(issame(icmd[cmdflag],"-n")){
			
				for(i = 0;i< n;i++){
					if(issame(icmd[cmdflag+1],students[i].name)){
						printf("    名前　　　 英語    国語    数学    合計\n");
						printf("%8s    %5d点 %5d点 %5d点 %5d点\n",students[i].name,students[i].eigo,students[i].koku,students[i].su,students[i].eigo+students[i].koku+students[i].su);
						
					} 
				}
				if(flag != 0){
						FILE *fp;
						int i,d;
						char fname[20];
						strcpy(fname,icmd[flag+1]);
						 
						
	
						fp =  fopen(fname,"w");
						if(fp==NULL)
						{
							printf("File cannot open!");
							exit(0);
						}
						for(i = 0;i< n;i++){
						if(issame(icmd[cmdflag+1],students[i].name)){
						fprintf(fp,"%s,%d,%d,%d\n",students[i].name,students[i].eigo,students[i].koku,students[i].su);
						}
						} 
						fclose(fp);
						printf("出力成功!\n");
				}
					
						
				}
			//o -eコマンド 
			else if(issame(icmd[cmdflag],"-e")){
				stu cpstudents[50];
				for(i = 0;i< n;i++){
					cpstudents[i] = students[i];
				}
				for (i = 0; i < n - 1; i++) {
        			for (j = 0; j < n - 1 - i; j++) {
            			if (students[j].eigo < students[j+1].eigo) {      
                				stu temp = students[j+1];        
               					students[j+1] = students[j];
                				students[j] = temp;
            				}
        				}
    				}
    			printf("---英語の成績---\n");
    			printf("    名前      点数\n");
    			for(i = 0;i< n;i++){
    				printf("%8s   %5d点\n",students[i].name,students[i].eigo);
				}
				if(flag != 0){
					opfile(icmd[flag+1],icmd[cmdflag]);
				}
			}
			//o -lコマンド
			else if(issame(icmd[cmdflag],"-l")){
				stu cpstudents[50];
				for(i = 0;i< n;i++){
					cpstudents[i] = students[i];
				}
				for (i = 0; i < n - 1; i++) {
        			for (j = 0; j < n - 1 - i; j++) {
            			if (students[j].koku < students[j+1].koku) {      
                				stu temp = students[j+1];        
               					students[j+1] = students[j];
                				students[j] = temp;
            				}
        				}
    				}
    			printf("---国語の成績---\n");
    			printf("    名前      点数\n");
    			for(i = 0;i< n;i++){
    				printf("%8s   %5d点\n",students[i].name,students[i].koku);
				}
				if(flag != 0){
					opfile(icmd[flag+1],icmd[cmdflag]);
				}
			}
			//o -mコマンド
			else if(issame(icmd[cmdflag],"-m")){

				for (i = 0; i < n - 1; i++) {
        			for (j = 0; j < n - 1 - i; j++) {
            			if (students[j].su < students[j+1].su) {      
                				stu temp = students[j+1];        
               					students[j+1] = students[j];
                				students[j] = temp;
            				}
        				}
    				}
    			printf("---数学の成績---\n");
    			printf("    名前      点数\n");
    			for(i = 0;i< n;i++){
    				printf("%8s   %5d点\n",students[i].name,students[i].su);
				}
				if(flag != 0){
					opfile(icmd[flag+1],icmd[cmdflag]);
				}
			}			
			else//o コマンド
			{
		  	output();
		  	if(flag != 0){
		  		char tempcmd[] = "only_o";
				opfile(icmd[flag+1],tempcmd);
			}
			}
		   
	}
		
	}	

	printf("プログラム終了！\n");
	
	return 0;  
 
}
