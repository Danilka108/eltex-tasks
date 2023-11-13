#!/bin/bash

sleep infinity &
p1=$!

sleep infinity &
p2=$!

sleep infinity &
p3=$!

kill $p1
echo "first process was killed"

kill $p2
echo "second process was killed"

kill $p3
echo "third process was killed"
