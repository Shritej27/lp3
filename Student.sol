//SPDX-License-Identifier: MIT

pragma solidity ^0.8.20;

contract StudentDetail
{
    struct Student
    {
        uint roll;
        string name;
        uint age;
        string department;
        uint marks;
    }

    Student[] public students;

    function addStudents(uint _roll,string memory _name,uint _age,string memory _department,uint _marks) public 
    {
        students.push(Student(_roll,_name,_age,_department,_marks));
    }

    function getStudent(uint index) public view returns(uint,string memory,uint, string memory,uint)
    {
        require(index < students.length ,"Invalid index");
        Student memory std = students[index];
        return (std.roll,std.name,std.age,std.department,std.marks);
    }

    function getStudentCount() public view returns(uint)
    {
        return students.length;
    }
}