#include "student.h"
#include<QDebug>
Student::Student(QObject *parent)
    : QObject{parent}
{}

void Student::studentTreatTeacher()
{
    qDebug()<<"Student treat teacher\n";
}
void Student::studentTreatTeacher(QString what)
{
    qDebug()<< "Student treat teacher with "<< what << "\n";
}
