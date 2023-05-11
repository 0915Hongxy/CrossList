#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
 

typedef struct{
	int den;
	int mol;
}DataType;

typedef struct OLNode
{
	int row, col;
	DataType value;
	struct OLNode *right, *down;  //ͬһ�С�ͬһ���е���һ������Ԫ�� 
}OLNode, *OLink;

typedef struct
{
	char name[10];					//ʮ����������� 
	OLink *row_head, *col_head;  //ָ��ָ���ָ�룬������������ 
	int m, n, len;  			//���������������������Ԫ�صĸ��� 
}CrossList; 

CrossList Cross[10];		//ʮ�������������ڴ��ʮ������ 
int last=0; 				//�������Ѿ���ŵ�ʮ��������� 

void Initiate();			//����ʮ������ 
void PrintCross();			//�����ӡʮ������ 
void PrintMatrix(int i);	//��ӡϡ����� 
void PrintMatrix2(int i);	//��ӡϡ����� 
void SetValue(); 			//��������λ��ֵ 
void GetValue();				//��ȡĳһ���ֵ 
void InsertValue(); 		//����ĳһ���ֵ 
void DeleteValue();			//ɾ��ĳһ���ֵ 
void MatrixAdd();			//����ӷ����� 
void MatrixSub();			//����������� 
void MatrixMul();			//����˷����� 
void Transpose();			//����ת�� 
void Memory();				//�����ļ� 
void Maximun();				//�������ֵ 
void Determinant();			//������ʽ 
DataType Determinant1(CrossList *cross);					//��ȫ������ʽ 
DataType Determinant2(int x,int y,CrossList *cross);		//��ֲ�����ʽ 
void Inverse();												//������� 
void Distribute(int m,int n);								//��ʮ���������ռ� 
int gcd(int a,int b);										//��������� 


void Initiate(){
	int i;
	FILE *fp;
	OLNode node,*p=NULL,*q=NULL;
	char s[10]; 
	printf("������ʮ����������:");
	scanf("%s",s);
	for(i=0;i<last;i++){						//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s)==0){
			printf("��ʮ�������Ѵ���!\n");
			return ;
		}
	}
	strcpy(Cross[last].name,s);
	printf("������洢ϡ�������ļ���:");
	scanf("%s",s);
	if((fp=fopen(s,"rb"))==NULL){
		printf("���ܴ��ļ�!\n");
		return ; 								//���ļ��򲻿��Ĵ��� 
	}
	fread(&node,sizeof(OLNode),1,fp);			//��ȡϡ��������Ϣ 
	Cross[last].len=(int)node.value.den; 	
	Distribute(node.row,node.col);				//����ռ� 
	while(fread(&node,sizeof(OLNode),1,fp)) {
		q=(OLNode *)malloc(sizeof(OLNode));
		*q=node;		
		p=Cross[last].row_head[node.row-1];
		while(p->right!=NULL && p->right->col<q->col) 	//Ѱ�ҽ���λ�� �������뵽��Ӧ�ĵط� 
			p=p->right;										
		q->right=p->right;
		p->right=q;
		p=Cross[last].col_head[node.col-1];
		while(p->down!=NULL && p->down->row<q->row) 
			p=p->down;
		q->down=p->down;
		p->down=q;
	}
	PrintMatrix(last);
	last++;
	fclose(fp); 
	printf("�����ɹ�!\n");  
	
}
void SetValue(){
	int i,x,y,tem;
	DataType value;				
	char s[10]; 
	OLNode *p=NULL;
	printf("������ʮ����������:");
	scanf("%s",s);
	for(i=0;i<last;i++){						//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	} 
	printf("����������x y:"); 		
	scanf("%d%d",&x,&y);
	printf("������Ҫ���õ�ֵ:"); 
	value.mol=1;							
	scanf("%d/%d",&value.den,&value.mol);	
	if((tem=gcd(value.den,value.mol))!=1){	
		value.den=value.den/tem;
		value.mol=value.mol/tem;
	}
	p=Cross[i].row_head[x-1]->right;
	while(p!=NULL && p->col<y) 					//Ѱ������ 
		p=p->right;	
	if(p!=NULL && p->col==y) {					//�޸�����ֵ 
		p->value=value;
		printf("���óɹ�!\n");
	}
	else
		printf("��������ʮ����������!\n");
}
void GetValue(){
	int i,x,y;
	char s[10]; 
	OLNode *p=NULL;
	printf("������ʮ����������:");
	scanf("%s",s);
	for(i=0;i<last;i++){					//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	} 
	printf("����������x y:"); 		
	scanf("%d%d",&x,&y);
	p=Cross[i].row_head[x-1]->right;	
	while(p!=NULL && p->col<y) 				//������ 
		p=p->right;	
	if(p!=NULL && p->col==y){				//��ȡ����ֵ	
		if(p->value.mol==1)
			printf("����ֵ:%d\n",p->value.den);
		else 
			printf("����ֵ:%d/%d\n",p->value.den,p->value.mol);
	}
	else
		printf("��������ʮ����������!\n");
}
void InsertValue(){
	int i,x,y,flag,tem;
	DataType value;				
	char s[10]; 
	OLNode *p=NULL,*q=NULL;
	printf("������ʮ����������:");
	scanf("%s",s);
	for(i=0;i<last;i++){							//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	}  
	printf("����������x y:"); 		
	scanf("%d%d",&x,&y);
	printf("������Ҫ���õ�ֵ:"); 
	value.mol=1;							
	scanf("%d/%d",&value.den,&value.mol);	
	if((tem=gcd(value.den,value.mol))!=1){	
		value.den=value.den/tem;
		value.mol=value.mol/tem;
	}
	p=Cross[i].row_head[x-1];
	while(p->right!=NULL && p->right->col<y) 		//������ 
		p=p->right;	
	if(p->right!=NULL && p->right->col==y){			
		printf("��������ʮ�������Ѵ��ڣ����ܲ���!\n�Ƿ���Ҫ�޸�?\n1:��  2:��");
		scanf("%d",&flag);
		if(flag)  p->right->value=value; 
		return ;
	}
	q=(OLNode *)malloc(sizeof(OLNode));					//����һ�����	
	q->value=value;q->row=x;q->col=y;
	q->right=p->right;									//�в� 
	p->right=q;
	
	p=Cross[i].col_head[y-1];
	while(p->down!=NULL && p->down->row<x) 				//Ѱ������ 
		p=p->down;
	q->down=p->down;									//�в� 
	p->down=q;
	printf("����ɹ�!\n");						
}
void DeleteValue(){
	int i,x,y;							
	char s[10]; 
	OLNode *p=NULL,*q=NULL;		
	printf("������ʮ����������:");
	scanf("%s",s);
	for(i=0;i<last;i++){							//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	}  
	printf("����������x y:"); 		
	scanf("%d%d",&x,&y);
	p=Cross[i].row_head[x-1];
	while(p->right!=NULL && p->right->col<y) 		//������ 
		p=p->right;	
	if(p->right==NULL || p->right->col!=y){
		printf("��������ʮ���������ڣ��޷�ɾ��!\n");
		return ;
	}							
	q=p->right;					
	p->right=q->right;			//����ɾ������ 
	 
	p=Cross[i].col_head[y-1];
	while(p->down->row<x) 		//����ȷ��������������Կ��Բ����ж�Ϊ�� ������ 
		p=p->down;
	p->down=q->down;			//����ɾ������ 
	free(q);
	printf("ɾ���ɹ�!\n");		
}

void PrintMatrix(int i){					
	int j,k;
	OLNode *p=NULL;
	for(j=0;j<Cross[i].m;j++){					//�ӵ�һ�п�ʼ���� 
		p=Cross[i].row_head[j]->right;
		for(k=1;k<=Cross[i].n;k++){				//�ӵ�һ�п�ʼ���� 
			if(p!=NULL && k==p->col){			
				if(p->value.mol==1)														
					printf("%-5d",p->value.den);
				else 
					printf("%d/%-3d",p->value.den,p->value.mol);
				p=p->right;
			}
			else printf("%-5d",0);
		}
		printf("\n");
	}
}
void PrintMatrix2(int i){
	int j,k;
	OLNode *p=NULL;
	for(j=0;j<Cross[i].n;j++){					//�ӵ�һ�п�ʼ���� 
		p=Cross[i].col_head[j]->down;
		for(k=1;k<=Cross[i].m;k++){				//�ӵ�һ�п�ʼ���� 
			if(p!=NULL && k==p->col){		
				if(p->value.mol==1)														 
					printf("%-5d",p->value.den);
				else 
					printf("%d/%-3d",p->value.den,p->value.mol);
				p=p->right;
			}
			else printf("%-5d",0);
		}
		printf("\n");
	}
}

void PrintCross(){					
	int i,j,k;
	char s[10];
	OLNode *p=NULL;
	printf("������ʮ����������:");
	scanf("%s",s);
	for(i=0;i<last;i++){
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	}
	for(j=1;j<=6;j++){
		printf("%9d",j);
	}
	printf("\n");
	for(j=0;j<Cross[i].m;j++){					//�ӵ�һ�п�ʼ���� 
		p=Cross[i].row_head[j];
		printf("%d  ",j+1); 
		for(k=1;k<=Cross[i].n;k++){				//�ӵ�һ�п�ʼ���� 
			if(p->right!=NULL && k==p->right->col){			
				if(p->right->value.mol==1)														
					printf("--> %-5d",p->right->value.den);
				else 
					printf("--> %d/%-3d",p->right->value.den,p->right->value.mol);
				p=p->right;
			}
			else if(p->right==NULL){
				break;
			}
			else printf("---------");
		}
		printf("\n");
	}
}

void MatrixAdd(){								
	int i,j,x,len=0,tem;
	char s1[10],s2[10]; 
	OLNode *p=NULL,*q=NULL,*w=NULL,*u=NULL,*v=NULL;
	printf("������ʮ����������:");
	scanf("%s",s1);
	for(i=0;i<last;i++){						//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s1)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	}
	printf("������ʮ����������:");				
	scanf("%s",s2);
	for(j=0;j<last;j++){						//�ж������Ƿ���� 
		if(strcmp(Cross[j].name,s2)==0)
			break;	
	}
	if(j==last){
		printf("ʮ����������!\n");
		return ;
	} 
	if(Cross[i].m!=Cross[j].m || Cross[i].n!=Cross[j].n){		//�ж����������Ƿ������� 
		printf("����ʮ�����������!\n");
		return ;
	}
	printf("������洢��ʮ����������:");
	scanf("%s",Cross[last].name);
	for(x=0;x<last;x++){									//�ж������Ƿ���� 
		if(strcmp(Cross[x].name,Cross[last].name)==0){
			printf("��ʮ�������Ѵ���!\n");
			return ;
		}
	}
	Distribute(Cross[i].m,Cross[i].n);
	for(x=0;x<Cross[last].m;x++){					//�ӵ�һ�п�ʼ���� 
		u=Cross[last].row_head[x];
		p=Cross[i].row_head[x]->right;
		q=Cross[j].row_head[x]->right;
		while(p!=NULL && q!=NULL){					//������С���Ȳ���ʮ������ �ٽ�������ͬ������ٲ���	
			w=(OLNode *)malloc(sizeof(OLNode));	
			if(p->col<q->col){					
				*w=*p;
				p=p->right;
			}
			else if(p->col>q->col){
				*w=*q;
				q=q->right;
			}
			else {
				w->col=p->col;
				w->row=p->row;
				w->value.den=p->value.den*q->value.mol+q->value.den*p->value.mol;	
				w->value.mol=p->value.mol*q->value.mol;
				if((tem=gcd(w->value.den,w->value.mol))!=1){	
					w->value.den=w->value.den/tem;
					w->value.mol=w->value.mol/tem;
				}
				p=p->right;
				q=q->right;
			}
			len++;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
		}
		while(p!=NULL){									//��ʣ��Ĳ��� 
			w=(OLNode *)malloc(sizeof(OLNode));	
			*w=*p;
			p=p->right;
			len++;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
		}
			
		while(q!=NULL){									//��ʣ��Ĳ���
			w=(OLNode *)malloc(sizeof(OLNode));	
			*w=*q;
			q=q->right;
			len++;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
		}	
	}
	Cross[last].len=len;
	PrintMatrix(last);
	last++;
}
void MatrixSub(){								
	int i,j,x,len=0,tem;
	char s1[10],s2[10]; 
	OLNode *p=NULL,*q=NULL,*w=NULL,*u=NULL,*v=NULL;
	printf("������ʮ����������:");
	scanf("%s",s1);
	for(i=0;i<last;i++){							//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s1)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	}
	printf("������ʮ����������:");				
	scanf("%s",s2);
	for(j=0;j<last;j++){							//�ж������Ƿ���� 
		if(strcmp(Cross[j].name,s2)==0)
			break;	
	}
	if(j==last){
		printf("ʮ����������!\n");
		return ;
	} 
	if(Cross[i].m!=Cross[j].m || Cross[i].n!=Cross[j].n){	//�ж����������Ƿ������� 
		printf("����ʮ�����������!\n");
		return ;
	}
	printf("������洢��ʮ����������:");
	scanf("%s",Cross[last].name);
	for(x=0;x<last;x++){							//�ж������Ƿ���� 
		if(strcmp(Cross[x].name,Cross[last].name)==0){
			printf("��ʮ�������Ѵ���!\n");
			return ;
		}
	}
	Distribute(Cross[i].m,Cross[i].n);
	for(x=0;x<Cross[last].m;x++){					//�ӵ�һ�п�ʼ���� 
		u=Cross[last].row_head[x];
		p=Cross[i].row_head[x]->right;
		q=Cross[j].row_head[x]->right;
		while(p!=NULL && q!=NULL){					//������С���Ȳ���ʮ������ �ٽ�������ͬ������ٲ���	
			w=(OLNode *)malloc(sizeof(OLNode));	
			if(p->col<q->col){
				*w=*p;
				p=p->right;
			}
			else if(p->col>q->col){
				w->row=q->row;
				w->col=q->col;
				w->value.den=-q->value.den;
				w->value.mol=q->value.mol;
				q=q->right;
			}
			else {
				w->col=p->col;
				w->row=p->row;
				w->value.den=p->value.den*q->value.mol-q->value.den*p->value.mol;	
				w->value.mol=p->value.mol*q->value.mol;
				if((tem=gcd(w->value.den,w->value.mol))!=1){	
					w->value.den=w->value.den/tem;
					w->value.mol=w->value.mol/tem;
				}
				p=p->right;
				q=q->right;
			}
			len++;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
		}
		while(p!=NULL){									//��ʣ��Ĳ���
			w=(OLNode *)malloc(sizeof(OLNode));	
			*w=*p;
			p=p->right;
			len++;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
		}
			
		while(q!=NULL){									//��ʣ��Ĳ���
			w=(OLNode *)malloc(sizeof(OLNode));	
			w->row=q->row;
			w->col=q->col;
			w->value.den=-q->value.den;
			w->value.mol=q->value.mol;
			q=q->right;
			len++;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
		}	
	}
	Cross[last].len=len;
	PrintMatrix(last);
	last++;
}
void MatrixMul(){												
	int i,j,x,y,len=0,tem1,tem2,tem;
	DataType sum; 
	char s1[10],s2[10]; 
	OLNode *p=NULL,*q=NULL,*w=NULL,*u=NULL,*v=NULL;
	printf("������ʮ����������:");
	scanf("%s",s1);
	for(i=0;i<last;i++){							//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s1)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	}
	printf("������ʮ����������:");				
	scanf("%s",s2);
	for(j=0;j<last;j++){							//�ж������Ƿ���� 
		if(strcmp(Cross[j].name,s2)==0)
			break;	
	}
	if(j==last){
		printf("ʮ����������!\n");
		return ;
	} 
	if(Cross[i].m!=Cross[j].n){						//�ж����������Ƿ������� 
		printf("����ʮ�����������!\n");
		return ;
	}
	printf("������洢��ʮ����������:");
	scanf("%s",Cross[last].name);
	for(x=0;x<last;x++){							//�ж������Ƿ���� 
		if(strcmp(Cross[x].name,Cross[last].name)==0){
			printf("��ʮ�������Ѵ���!\n");
			return ;
		}
	}
	Distribute(Cross[i].m,Cross[j].n);
	for(x=0;x<Cross[last].m;x++){					//�ӵ�һ�п�ʼ���� 
		u=Cross[last].row_head[x];
		p=Cross[i].row_head[x]->right;
		for(y=0;y<Cross[last].n;y++){				//�ӵ�һ�п�ʼ 
			sum.den=0;
			sum.mol=1;
			q=Cross[j].col_head[y]->down;
			while(p!=NULL && q!=NULL){				//������ʮ�������ÿһ�� 
				if(p->col<q->row)
					p=p->right;
				else if(p->col>q->row)
					q=q->down;
				else{
					tem1=p->value.den*q->value.den;
					tem2=p->value.mol*q->value.mol;
					sum.den=sum.den*tem2+tem1*sum.mol;
					sum.mol=sum.mol*tem2;
					if((tem=gcd(sum.den,sum.mol))!=1){	
						sum.den=sum.den/tem;
						sum.mol=sum.mol/tem;
					}
					p=p->right;
					q=q->down;
				}
			} 
			if(sum.den!=0){
				len++;
				w=(OLNode *)malloc(sizeof(OLNode));
				w->row=x+1;
				w->col=y+1;
				w->value=sum;
				w->right=u->right;
				u->right=w;
				u=u->right;
				v=Cross[last].col_head[w->col-1];
				while(v->down!=NULL)
					v=v->down;
				w->down=v->down;
				v->down=w;
			}
		}	
	}
	Cross[last].len=len;
	PrintMatrix(last);
	last++;
}


void Transpose(){
	int i,j,max;
	char s[10];
	OLNode *p=NULL,*w,*u,*v;
	printf("������ʮ����������:");
	scanf("%s",s);
	for(i=0;i<last;i++){						//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	}
	printf("������洢��ʮ����������:");
	scanf("%s",Cross[last].name);
	for(j=0;j<last;j++){						//�ж������Ƿ���� 
		if(strcmp(Cross[j].name,Cross[last].name)==0){
			printf("��ʮ�������Ѵ���!\n");
			return ;
		}
	}
	Distribute(Cross[i].m,Cross[i].n);
	for(j=0;j<Cross[i].m;j++){
		u=Cross[last].row_head[j];
		p=Cross[i].col_head[j]->down;
		while(p!=NULL){								//���к��е��� 
			w=(OLNode *)malloc(sizeof(OLNode));
			w->row=p->col;
			w->col=p->row;
			w->value=p->value;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
			p=p->down;
		}
	}
	Cross[last].len=Cross[i].len;
	PrintMatrix(last);
	last++;
	
}

void Memory(){
	int i,j;
	FILE *fp;
	OLNode node,*p=NULL;
	char s[10]; 
	printf("������ʮ����������:");
	scanf("%s",s);
	for(i=0;i<last;i++){					//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	} 
	printf("������洢ϡ�������ļ���:");
	scanf("%s",s);
	if((fp=fopen(s,"wb"))==NULL){
		printf("���ܴ��ļ�!\n");
		return ; 				//���ļ��򲻿��Ĵ��� 
	}
	node.row=Cross[i].m;
	node.col=Cross[i].n;
	node.value.mol=1; 								
	node.value.den=Cross[i].len;
	fwrite(&node,sizeof(OLNode),1,fp);
	for(j=0;j<Cross[i].m;j++){					//�ӵ�һ�п�ʼ���� д���ļ� 
		p=Cross[i].row_head[j]->right;
		while(p!=NULL){
			fwrite(p,sizeof(OLNode),1,fp);
			p=p->right;
		}
	}
	fclose(fp);
	PrintMatrix(i);
	printf("�洢�ɹ�!\n");
}

void Maximun(){
	int i,j;
	DataType max,min;
	char s[10];
	OLNode *p=NULL;
	printf("������ʮ����������:");
	scanf("%s",s);
	for(i=0;i<last;i++){						//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	}
	for(j=0;j<Cross[i].m;j++){					//�ҵ���һ��ֵ 
		p=Cross[i].row_head[j]->right;
		if(p!=NULL)
			break;
	}
	max=p->value;
	min=max;
	for(j=0;j<Cross[i].m;j++){					//�ӵ�һ�п�ʼ����  �������Сֵ 
		p=Cross[i].row_head[j]->right;
		while(p!=NULL){										
			if(p->value.den/p->value.mol>max.den/max.mol)
				max=p->value;
			if(p->value.den/p->value.mol<min.den/min.mol)
				min=p->value;
			p=p->right;
		}
	}
	if(max.mol==1)														
		printf("max=%d ",max.den);
	else 
		printf("max=%d/%d",max.den,max.mol);
	if(min.mol==1)															
		printf("min=%d\n",min.den);
	else 
		printf("min=%d/%d\n",min.den,min.mol);
	 
}
void Determinant(){
	int i;
	DataType D;
	char s[10];			
	printf("������ʮ����������:");
	scanf("%s",s);
	for(i=0;i<last;i++){					//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	}
	if(Cross[i].m!=Cross[i].n){					//�ж������Ƿ��������ʽ 
		printf("�Ǿ��󣬲���������ʽ!\n");
		return ;
	}
	D=Determinant1(&Cross[i]);
	if(D.mol==1)
		printf("����ʽ:%d\n",D.den);
	else
		printf("����ʽ:%d/%d\n",D.den,D.mol);
}

void Inverse(){
	int i,j,k,len=0,tem;
	DataType D,sum;
	char s[10]; 
	OLNode *w=NULL,*u=NULL,*v=NULL;		
	printf("������ʮ����������:");
	scanf("%s",s);
	for(i=0;i<last;i++){				//�ж������Ƿ���� 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("ʮ����������!\n");
		return ;
	}
	if(Cross[i].m!=Cross[i].n){			//�ж������Ƿ��������ʽ 
		printf("�Ǿ��󣬲���������ʽ!\n");
		return ;
	}
	D=Determinant1(&Cross[i]);
	if(D.den==0){						//�ж������Ƿ��������� 
		printf("�þ���û�������!\n");
		return ;
	}
	printf("������洢��ʮ����������:");
	scanf("%s",Cross[last].name);
	for(j=0;j<last;j++){						//�ж������Ƿ���� 
		if(strcmp(Cross[j].name,Cross[last].name)==0){
			printf("��ʮ�������Ѵ���!\n");
			return ;
		}
	}
	Distribute(Cross[i].m,Cross[i].n);
	for(j=0;j<Cross[i].m;j++){
		u=Cross[last].row_head[j];
		for(k=1;k<=Cross[i].m;k++){				//�ӵ�һ�п�ʼ���� 
			sum=Determinant2(j,k,&Cross[i]);	//�������ÿһ�� ����ÿһ�����������ʮ������ 
			sum.den=sum.den*D.mol;
			sum.mol=sum.mol*D.den;
			if((tem=gcd(sum.den,sum.mol))!=1){	
				sum.den=sum.den/tem;
				sum.mol=sum.mol/tem;
			}
			if(sum.den!=0){
				w=(OLNode *)malloc(sizeof(OLNode));
				w->row=j+1;
				w->col=k;
				w->value=sum;
				len++;
				w->right=u->right;
				u->right=w;
				u=u->right;
				v=Cross[last].col_head[k-1];
				while(v->down!=NULL)
					v=v->down;
				w->down=v->down;
				v->down=w;
			}
		}
	}
	Cross[last].len=len;
	PrintMatrix(last);
	last++;
}

DataType Determinant1(CrossList *cross){		//���ý�������������ԭ�� 
	int j,k,tem1,tem2;
	DataType tem3,tem4;					
	DataType *a,*b;
	OLNode *p=NULL;
	a=(DataType *)malloc(sizeof(DataType)*cross->m);			
	b=(DataType *)malloc(sizeof(DataType)*cross->m);
	for(j=0;j<cross->m;j++){
		a[j].den=1;
		a[j].mol=1;
		b[j].den=1;
		b[j].mol=1;
	}
	for(j=0;j<cross->m;j++){
		p=cross->row_head[j]->right;
		for(k=1;k<=cross->m;k++){				//�ӵ�һ�п�ʼ���� 
			tem1=(k-j-1)%cross->m;				//Ѱ�ҵĹ��� 
			tem2=(k+j)%cross->m;
			if(tem1<0) 
				tem1=cross->m+tem1;
			if(p!=NULL && k==p->col){		
				a[tem1].den=a[tem1].den*p->value.den;				
				a[tem1].mol=a[tem1].mol*p->value.mol;
				b[tem1].den=b[tem1].den*p->value.den;
				b[tem1].mol=b[tem1].mol*p->value.mol;			
				p=p->right;
			}
			else{												
				a[tem1].den=0;
				b[tem2].den=0;
			}
		}
	}
	tem4.den=0;									
	tem4.mol=1;
	for(j=0;j<cross->m;j++){					//�������� 
		tem3.den=a[j].den*b[j].mol-b[j].den*a[j].mol;
		tem3.mol=a[j].mol*b[j].mol;
		tem4.den=tem3.den*tem4.mol+tem4.den*tem3.mol;
		tem4.mol=tem3.mol*tem4.mol;
	}
	free(a);
	free(b);
	return tem4;
}

DataType Determinant2(int x,int y,CrossList *cross){
	int j,k,m,n,tem1,tem2;	
	DataType tem3,tem4;				
	DataType *a,*b;
	OLNode *p=NULL;	 
	a=(DataType *)malloc(sizeof(DataType)*cross->m-1);		
	b=(DataType *)malloc(sizeof(DataType)*cross->m-1);
	for(j=0;j<cross->m-1;j++){
		a[j].den=1;
		a[j].mol=1;
		b[j].den=1;
		b[j].mol=1;
	}
	for(j=0;j<cross->m;j++){
		if(j==x)
			continue;
		else if(j>x)
			m=j-1;
		else
			m=j;
		p=cross->row_head[j]->right;
		for(k=1;k<=cross->m;k++){				//�ӵ�һ�п�ʼ���� 
			if(k==y)
				continue;
			else if(k>y)
				n=k-1;
			else
				n=k;
			tem1=(n-m-1)%cross->m;
			tem2=(n+m)%cross->m;
			if(tem1<0) 
				tem1=cross->m+tem1-1;
			if(p!=NULL && k==p->col){			
				a[tem1].den=a[tem1].den*p->value.den;					
				a[tem1].mol=a[tem1].mol*p->value.mol;
				b[tem2].den=b[tem2].den*p->value.den;
				b[tem2].mol=b[tem2].mol*p->value.mol;			
				p=p->right;
			}
			else{
				a[tem1].den=0;
				b[tem2].den=0;
			}
		}
	}
	tem4.den=0;										
	tem4.mol=1;
	for(j=0;j<cross->m-1;j++){
		tem3.den=a[j].den*b[j].mol-b[j].den*a[j].mol;
		tem3.mol=a[j].mol*b[j].mol;
		tem4.den=tem3.den*tem4.mol+tem4.den*tem3.mol;
		tem4.mol=tem3.mol*tem4.mol;
	}
	free(a);
	free(b);
	return tem4;
}
void Distribute(int m,int n){
	int i;
	Cross[last].m=m;
	Cross[last].n=n;
	Cross[last].row_head=(OLink *)malloc(sizeof(OLink)*Cross[last].m); 		//����ռ� 
	for(i=0;i<Cross[last].m;i++) {
		Cross[last].row_head[i]=(OLNode *)malloc(sizeof(OLNode));
		Cross[last].row_head[i]->right=NULL;
	}
	Cross[last].col_head=(OLink *)malloc(sizeof(OLink)*Cross[last].n); 
	for(i=0;i<Cross[last].n;i++) {
		Cross[last].col_head[i]=(OLNode *)malloc(sizeof(OLNode));
		Cross[last].col_head[i]->down=NULL;
	}
}
int gcd(int a,int b){			//��������� 
	if(b==0)
		return a;
	return gcd(b,a%b);
}
