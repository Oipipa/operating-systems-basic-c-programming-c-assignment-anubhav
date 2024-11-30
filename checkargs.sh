#!/bin/bash

# Capture the command and expected output
program=$1
expected_output=$2

# Extract the number of arguments from the expected_output
# The expected_output contains the phrase "You provided n arguments."
# Use sed to extract n
n_args=$(echo "$expected_output" | sed -n 's/.*You provided \([0-9]\+\) arguments.*/\1/p')

# If n_args is empty, default to 0
if [[ -z "$n_args" ]]; then
  n_args=0
fi

# Create an array of dummy arguments
args=()
for ((i=0; i<n_args; i++)); do
  args+=("dummy$i")
done

# Run the program with the arguments and capture its output
output=$("$program" "${args[@]}")

# Compare the output with the expected string
if [ "$output" == "$expected_output" ]; then
  exit 0
else
  exit 1
fi
