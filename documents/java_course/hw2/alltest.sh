#!/bin/bash
javac *.java

echo "normal run test:"
java AggregatorServer 4321 9876 &
java ContentServer http://localhost:4321 content.txt &
sleep 1
java GETClient http://localhost:9876 > temp.txt &
sleep 1
java compare temp.txt content.txt
./kill.sh

sleep 1

echo "multiclient run test:"
java AggregatorServer 4321 9876 &
java ContentServer http://localhost:4321 content.txt &
sleep 1
java GETClient http://localhost:9876 > temp.txt &
java GETClient http://localhost:9876 > temp.txt &
java GETClient http://localhost:9876 > temp.txt &
java GETClient http://localhost:9876 > temp.txt &
java GETClient http://localhost:9876 > temp.txt &
sleep 1
java compare temp.txt content.txt
./kill.sh