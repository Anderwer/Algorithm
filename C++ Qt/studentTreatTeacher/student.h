#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);
    void studentTreatTeacher();
    void studentTreatTeacher(QString what);
signals:
};

#endif // STUDENT_H
