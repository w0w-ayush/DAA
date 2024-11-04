// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract StudentData {
    // Define a structure to hold student information
    struct Student {
        uint id;
        string name;
        uint age;
    }

    // Array to store the list of students
    Student[] public students;

    // Mapping to track if a student ID already exists
    mapping(uint => bool) private studentExists;

    // Event to emit when a student is added
    event StudentAdded(uint id, string name, uint age);

    // Function to add a new student
    function addStudent(uint _id, string memory _name, uint _age) public {
        // Check if the student ID already exists
        require(!studentExists[_id], "Student with this ID already exists.");

        // Create a new student and add it to the array
        students.push(Student(_id, _name, _age));
        studentExists[_id] = true;

        // Emit an event when a new student is added
        emit StudentAdded(_id, _name, _age);
    }

    // Function to retrieve a student by index
    function getStudent(uint index) public view returns (uint, string memory, uint) {
        require(index < students.length, "Invalid index.");
        Student memory student = students[index];
        return (student.id, student.name, student.age);
    }

    // Fallback function to handle unknown function calls or direct transfers
    fallback() external payable {
        revert("Invalid function call. Please use a valid function.");
    }

    // Receive function to accept Ether directly to the contract
    receive() external payable {}

    // Function to check the contract balance (if any Ether is sent)
    function getBalance() public view returns (uint) {
        return address(this).balance;
    }
}
