#include<iostream>
class Employee
{
private:
    int salary;
public:
Employee(int x ){
    salary = x;
};
    void setsalary(int s){
        salary = s;
    };
    int getsalary(){
        return salary;
    }
};
int main(){
    Employee s1 (100);
}