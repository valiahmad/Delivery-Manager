// delivery manager.c
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
//#define getch() _getch()//-+-+-+-+-+-+-+-+IF YOU ARE COMPILING THIS ON VISUAL STUDIO PLEASE UNCOMMENT THIS
//#define getche() _getche()//-+-+-+-+-+-+-+-+IF YOU ARE COMPILING THIS ON VISUAL STUDIO PLEASE UNCOMMENT THIS
//#define clrscr() system("cls")//-+-+-+-+-+-+-+-+IF YOU ARE COMPILING THIS ON VISUAL STUDIO PLEASE UNCOMMENT THIS
#define MAX 100
double identities[MAX], phones[MAX], status[MAX];
int id_driver[MAX], id_order[MAX];
int place = 0, place_order = 0;
int total = 0, on_order = 0, finished_order = 0;
/////////////////////////////////////////////////
void managedelivery();
void manageOrder();
///////////////////////////////////////////////
void print() {
	int available_courier = 0;
	for (int i = 0; i < place; i++)
		if (status[i] == 1)
			available_courier++;
	printf("available couriers = %d", available_courier);
	printf("\ntotal couriers = %d", place);
	printf("\non-going orders = %d", on_order);
	printf("\nfinished orders = %d", finished_order);
}
void main_menu() {
	int option;
loop1:
	clrscr();
	print();
	printf("\n\n1)Couriers\n2)Orders\n3)Quit\n");
loop:
	option = getch() - 48;
	if (option < 1 || option >3)goto loop;
	switch (option)
	{
	case 1:managedelivery(); break;
	case 2: manageOrder(); break;
	case 3:return;
	default:
		break;
	}
	goto loop1;
}
int check(char string[]) {
	for (int i = 0; string[i] != '\r'; i++) {
		if (string[i] < 48 || string[i]>57)return 1;
	}
	return 0;
}
double insert() {
	char temp[MAX];
loop:
	for (int i = 0;; i++) {
		temp[i] = getche();
		if (temp[i] == '\r')break;
	}
	if (check(temp)) {
		printf("\nInvalid Information! Please Try Again!");
		goto loop;
	}
	else return atof(temp);
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////MANAGING DELIVERY
int search_del(double );
int empty() {
	if (place < MAX)return 0;
	else return 1;
}
void add(double id, double ph) {
	if (!empty()) {
		identities[place] = id;
		phones[place] = ph;
		status[place] = 1;
		place++;
		return;
	}
	else { printf("\nThere Is No Available Courier For New Order!"); getch(); return; }
}
int remove(double id) {
	int remov;
	remov = search_del(id);
	if (remov == -1) {
		printf("\nNot Found!");
		getch();
		return 1;
	}
	for (; remov < place; remov++) {
		identities[remov] = identities[remov + 1];
		phones[remov] = phones[remov + 1];
		status[remov] = status[remov + 1];
	}
	place--;
	return 0;
}
int search_del(double id) {
	if (empty()) {
		printf("\nIt's Empty!");
		getch();
		return -1;
	}
	for (int i = 0; i < place; i++)
		if (id == identities[i])return i;
	return -1;
}
int delivery_menu() {
	int option;
	printf("\n\n1)Add\n2)Remove\n3)Activate\n4)Deactivate\n5)Back\n");
loop:
	option = getch() - 48;
	if (option < 1 || option >5)goto loop;
	return option;
}
void managedelivery() {
	double temp1, temp2;
	int i;
loop:
	clrscr();
	print();
	switch (delivery_menu())
	{
	case 1:printf("\nID : "); temp1 = insert();
		printf("\nPhone : "); temp2 = insert();
		add(temp1, temp2);
		break;
	case 2:printf("\nID : "); temp1 = insert();
		if (!remove(temp1))printf("\nDone!");
		break;
	case 3:if (place < 1) { printf("\nThere Is No Delivery"); getch(); break; }printf("\nID : "); temp1 = insert();
		i = search_del(temp1); status[i] = 1;
		break;
	case 4:if (place < 1) { printf("There Is No Delivery"); getch(); break; }printf("\nID : "); temp1 = insert();
		i = search_del(temp1); status[i] = 0;
		break;
	case 5:return;
	default:
		break;
	}
	goto loop;
}
///////////////////////////////////////////////END MANAGING DELIVERY
///////////////////////////////////////////
//////////////////////////////////////////////MANAGING ORDER
int search_or(int);
int check_del();
int emptyo() {
	if (place_order < MAX)return 0;
	else return 1;
}
int create_id(int mode) {
	if (check_del()) {
		printf("\nThere Is No Delivery!");
		getch();
		return -1;
	}
	int rand_id;
	int rand_del;
	switch (mode)
	{
	case 1:for (int i = 0;; i++) {
		rand_id = rand();
		if (i > 30)rand_id += 10000;
		if (rand_id > 10000 && rand_id < 100000)break;
	}
		  return rand_id;
	case 2:for (int i = 0;; i++) {
		rand_del = rand() % place;
		if (status[rand_del] == 1)break;
	}
		  return rand_del;
	default:
		break;
	}
}
void addOrder() {
	if (!emptyo()) {
		id_order[place_order] = create_id(1);
		if (id_order[place_order] == -1)return;
		id_driver[place_order] = create_id(2);
		status[id_driver[place_order]] = 0;
		printf("Id of delivery is : %10.0lf  Id of order is : %d", identities[id_driver[place_order]],
			id_order[place_order]);
		getch();
		place_order++;
		on_order++;
	}
	else printf("\nOrder Is Full!");
}
int removeOrder(int id_Order) {
	int remov;
	remov = search_or(id_Order);
	if (remov == -1) {
		return 1;
	}
	status[id_driver[remov]] = 1;
	for (; remov < place_order; remov++) {
		id_driver[remov] = id_driver[remov + 1];
		id_order[remov] = id_order[remov + 1];
	}
	place_order--;
	on_order--;
	finished_order++;
	return 0;
}
int search_or(int id_Order) {
	if (emptyo()) {
		return -1;
	}
	for (int i = 0; i < place_order; i++)
		if (id_Order == id_order[i])return i;
	return -1;
}
void list() {
	if (place_order < 1) {
		printf("\nList Is Empty!");
		getch();
		return;
	}
	for (int i = 0; i < place_order; i++)
		printf("\nOrder %d)\nCourier ID : %10.0lf\nID : %d\n", i + 1, identities[id_driver[i]], id_order[i]);
	getch();
}
int order_menu() {
	int option;
	printf("\n\n1)Start\n2)Stop\n3)List\n4)Back\n");
loop:
	option = getch() - 48;
	if (option < 1 || option >4)goto loop;
	return option;
}
int check_del() {
	for (int i = 0; i < place; i++)
		if (status[i] == 1)return 0;
	return 1;
}
void manageOrder() {
	int temp;
loop:
	clrscr();
	print();
	switch (order_menu())
	{
	case 1:addOrder();
		break;
	case 2:printf("\nID of Order : "); temp = insert();
		if (!removeOrder(temp))printf("\nDone!");
		break;
	case 3:list();
		break;
	case 4:
		return;
	default:
		break;
	}
	goto loop;
}
////////////////////////////////////////////END MANAGING ORDER


int main()
{
	main_menu();
	return 0;
}