#include"Cross.h"
int CrossOperate();			//ʮ������������� 
int MatrixCalculate();		//����������� 
int MultiMatrix();			//������������ 
int SingleMatrix();			//������������� 
int main(){
	int  n;
	while(1){
		printf("*****************************��ӭʹ��ϡ�����ʮ������**************************\n\n");
		printf("1. ����ʮ������	                2. ʮ���������		        3. ���ʮ������\n\n\n");
		printf("4. ��������	                5. �����ļ�                     6. �˳�ϵͳ\n\n");
		printf("*******************************************************************************\n");
		printf("��������Ҫʵ�ֵĲ���:");
		scanf("%d",&n);
		switch(n){
			case 1:system("cls");Initiate();system("pause");break;
			case 2:system("cls");CrossOperate();break;
			case 3:system("cls");PrintCross();system("pause");break;
			case 4:system("cls");MatrixCalculate();break;
			case 5:system("cls");Memory();system("pause");break;
			case 6:printf("�˳��ɹ�!\n");exit(0);break;
			default:printf("��������!\n");fflush(stdin);system("pause");
		} 
		system("cls");
	}
} 
int CrossOperate(){
	int  n;
	while(1){
		printf("*****************************��ӭʹ��ϡ�����ʮ������**************************\n\n");
		printf("1. ��ȡһ��	                2. ����һ��		        3. ����һ�� \n\n\n");
		printf("4. ɾ��һ��		        5. ������һ����			6. �˳�ϵͳ\n\n");
		printf("*******************************************************************************\n");
		printf("��������Ҫʵ�ֵĲ���:");
		scanf("%d",&n);
		switch(n){
			case 1:system("cls");GetValue();system("pause");break;
			case 2:system("cls");SetValue();system("pause");break;
			case 3:system("cls");InsertValue();system("pause");break;
			case 4:system("cls");DeleteValue();system("pause");break;
			case 5:return 0;break;
			case 6:printf("�˳��ɹ�!\n");exit(0);break;
			default:printf("��������!\n");fflush(stdin);system("pause");
		} 
		system("cls");
	}
} 
int MatrixCalculate(){
	int  n;
	while(1){
		printf("*****************************��ӭʹ��ϡ�����ʮ������**************************\n\n");
		printf("1.���������       						2. ����������\n\n\n");
		printf("3. ������һ����							4. �˳�ϵͳ\n\n");
		printf("*******************************************************************************\n");
		printf("��������Ҫʵ�ֵĲ���:");
		scanf("%d",&n);
		switch(n){
			case 1:system("cls");MultiMatrix();break;
			case 2:system("cls");SingleMatrix();break;
			case 3:return 0;break;
			case 4:printf("�˳��ɹ�!\n");exit(0);break;
			default:printf("��������!\n");fflush(stdin);system("pause");
		} 
		system("cls");
	}
} 
int MultiMatrix(){
	int  n;
	while(1){
		printf("*****************************��ӭʹ��ϡ�����ʮ������**************************\n\n");
		printf("1. ����ӷ�       		2. �������    			3. ����˷�    \n\n\n");
		printf("	    4. ������һ����			5. �˳�ϵͳ\n\n");
		printf("*******************************************************************************\n");
		printf("��������Ҫʵ�ֵĲ���:");
		scanf("%d",&n);
		switch(n){
			case 1:system("cls");MatrixAdd();system("pause");break;
			case 2:system("cls");MatrixSub();system("pause");break;
			case 3:system("cls");MatrixMul();system("pause");break;
			case 4:return 0;break;
			case 5:printf("�˳��ɹ�!\n");exit(0);break;
			default:printf("��������!\n");fflush(stdin);system("pause");
		} 
		system("cls");
	}
} 
int SingleMatrix(){
	int  n;
	while(1){
		printf("*****************************��ӭʹ��ϡ�����ʮ������**************************\n\n");
		printf("1. ��������			2. �����			3. ����ʽ   \n\n\n");
		printf("4. ��ֵ 		     	5. ������һ����			6. �˳�ϵͳ\n\n");
		printf("*******************************************************************************\n");
		printf("��������Ҫʵ�ֵĲ���:");
		scanf("%d",&n);
		switch(n){
			case 1:system("cls");Transpose();system("pause");break;
			case 2:system("cls");Inverse();system("pause");break;
			case 3:system("cls");Determinant();system("pause");break;
			case 4:system("cls");Maximun();system("pause");break;
			case 5:return 0;break;
			case 6:printf("�˳��ɹ�!\n");exit(0);break;
			default:printf("��������!\n");fflush(stdin);system("pause");
		} 
		system("cls");
	}
} 
