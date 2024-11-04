// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract Bank {
    // Mapping to store each customer's balance
    mapping(address => uint) private balances;

    // Event to log deposits
    event Deposit(address indexed customer, uint amount);
    
    // Event to log withdrawals
    event Withdrawal(address indexed customer, uint amount);

    // Function to deposit money into the account
    function deposit() external payable {
        require(msg.value > 0, "Deposit amount must be greater than zero.");
        balances[msg.sender] += msg.value;
        emit Deposit(msg.sender, msg.value);
    }

    // Function to withdraw money from the account
    function withdraw(uint amount) external {
        require(amount > 0, "Withdrawal amount must be greater than zero.");
        require(balances[msg.sender] >= amount, "Insufficient balance.");

        balances[msg.sender] -= amount;
        payable(msg.sender).transfer(amount);
        emit Withdrawal(msg.sender, amount);
    }

    // Function to check the balance of the account
    function getBalance() external view returns (uint) {
        return balances[msg.sender];
    }
}
