//********************
//Matthew Aberegg
//Project 3
//CS 2401
//10/8/2015
//********************
#include "college.h"
#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

College::College(std::string s){
	name = s;
	head = NULL;
}


College::~College(){
	node * rmptr;
	while(head != NULL){
		rmptr = head;
		head = head->link();
		delete rmptr;
	}
}

College::College(const College& other){
	if(other.head == NULL){
		head = NULL;
	}
	else{
		node * sptr;
		node * dptr;
		head = new node(other.head->data());
		dptr = head;
		sptr = other.head->link();
		while(sptr != NULL){
			dptr->set_link(new node(sptr->data()));
			dptr = dptr->link();
			sptr = sptr->link();
		}
	}
}

College& College::operator =(const College& other){
	if(this == &other){
		return * this;
	}
	node * rmptr;
	while(head != NULL){
		rmptr = head;
		head = head->link();
		delete rmptr;
	}
	if(other.head != NULL){
		node * sptr;
		node * dptr;
		head = new node(other.head->data());
		dptr = head;
		sptr = other.head->link();
		while(sptr != NULL){
			dptr->set_link(new node(sptr->data()));
			dptr = dptr->link();
			sptr = sptr->link();
		}
	}
	return * this;
}

void College::add(course& c){
	node * previous;
	node * cursor;
	node * newnode;
	node * tmpptr;
	if(head == NULL){
		head = new node(c);
		head->set_link(NULL);
	}else if(head->data() > c){
		cursor = head->link();
		head->set_link(new node(c));
		newnode = head->link();
		newnode -> set_link(cursor);
		previous = head;
		head = newnode;
		head -> set_link(new node (previous -> data()));
		tmpptr = head -> link();
		tmpptr -> set_link(cursor);
		delete previous;
	} else if(head -> data() < c){
		cursor = head;
		while (cursor != NULL && cursor -> data() <= c){ 
			previous = cursor;
			cursor = cursor-> link();
		}	
		if (cursor == NULL){ 
			cursor = new node (c);
			cursor -> set_link(NULL);
			previous -> set_link(cursor);
		}
		else {
			tmpptr = new node (c);
			tmpptr -> set_link(cursor);
			previous -> set_link(tmpptr);
		}
	}
}

void College::remove(std::string coursename){
	node * previous;	
	node * cursor;
	if(coursename == head->data().get_course_number()){
		cursor = head;
		head = head->link();
		delete cursor;
	}
	else{
		previous = head;
		cursor = head->link();
		while(cursor != NULL && cursor->data().get_course_number() != coursename){
			previous = cursor;
			cursor = cursor->link();
		}
		if(cursor != NULL){
			previous->set_link(cursor->link());
			delete cursor;
}
}
}

void College::display(std::ostream& outs){
	node * ptr;
	ptr = head;
	while(ptr != NULL){
		outs << ptr->data().get_course_number();
		outs << ", ";
		outs << ptr->data().get_grade();
		outs << ", ";
		outs << ptr->data().get_hours();
		outs << "\n";
		ptr = ptr->link();
	}
	outs << "\n";
}


double College::hours(){
	node * ptr;
	ptr = head;
	double hours = 0;
	while(ptr != NULL){
	hours = hours + ptr->data().get_hours();
	ptr = ptr->link();
	}
return hours;
}

double College::gpa(){
	node * ptr;
	ptr = head;
	double sum = 0;
	while(ptr != NULL){
	sum = sum + (ptr->data().get_number_grade() * ptr->data().get_hours());
	ptr = ptr->link();
	}
	return (sum / hours());
} 

void College::save(std::ostream& outs){
	node * ptr;
	ptr = head;
	while(ptr != NULL){
		outs << ptr->data();
		ptr = ptr->link();
	}
}

void College::load(std::istream& ins){
	course tmp;
	ins >> tmp;
	node * ptr;
	ptr = new node;
	ptr -> set_data(tmp);
	ptr -> set_link(NULL);
	head = ptr;
  while (!ins.eof()){
    ins >> tmp;
		if(ins.eof())break;
		ptr -> set_link(new node);
		ptr = ptr -> link();
    ptr -> set_data(tmp);
		ptr -> set_link (NULL);
  }
}








