#!/bin/bash

function g++_k(){
    g++ -g -O2 -static -std=gnu++17 -I /home/naabzer/develop/liu/aps/aaps/api/ $1
}
