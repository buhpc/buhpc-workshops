#!/bin/bash

# Get the file name from the first argument
filename="$1"

# Define the range of nodes to copy to
nodes="buhpc-slice-02 buhpc-slice-03 buhpc-slice-04 buhpc-slice-05 buhpc-slice-06 buhpc-slice-07 buhpc-slice-08"

# Get the current directory
curdir=$(pwd)

# Loop through each node and copy the file
for node in $nodes; do
    echo "Copying file to $node..."
    ssh $node "mkdir -p $curdir; scp buhpc-slice-01:/$curdir/$filename $curdir/"
done
