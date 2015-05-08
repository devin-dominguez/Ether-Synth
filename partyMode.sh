#!/bin/bash
pd -nogui -open "pd-patch/main.pd" &
PID=$! 
./bin/hackNight &&
kill $PID
