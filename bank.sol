//SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

contract Bank
{
    mapping(address => uint) public balance;

    function deposit() public payable
    {
        require(msg.value>0, "Amount must be > than 0");

        balance[msg.sender]+=msg.value;
    }

    function show() public view returns(uint)
    {
        return balance[msg.sender];
    }

    function withdraw(uint amount) public  
    {
        require(amount > 0, "Amount must be > than 0");
        require(amount <=  balance[msg.sender],"Insufficient balance");
        balance[msg.sender] -= amount;
        (bool success,) = payable(msg.sender).call{value:amount}("");
        require(success, "tranfer failed");
    }
}