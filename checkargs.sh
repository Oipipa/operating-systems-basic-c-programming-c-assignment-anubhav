#!/bin/bash

# Capture the command and expected output
program=$1
expected_output=$2

# Run the program and capture its output
output=$($program)

# Compare the output with the expected string
if [ "$output" == "$expected_output" ]; then
  exit 0
else
  exit 1
fi
