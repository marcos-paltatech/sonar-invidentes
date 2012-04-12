#!/bin/bash
for i in *ps; do
	ps2pdf14 -dOptimize=true -sPAPERSIZE=a4 $i
done
