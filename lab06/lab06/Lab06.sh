#!/bin/bash

#This is a comment line

<acmart.html grep "href"> tmpfile
#grep used to search for and print lines following a specific pattern

sed -r 's/.*(a href=")([^"]*).*/\2/' <tmpfile> links
sed -r 's/(.*)/http:\/\/ctan\.math\.utah\.edu\/ctan\/tex-archve\/macros\/latex\/contrib\/acmart\/\1/' <links> tmpfile
#sed used to search for and modify text

mv tmpfile links
#mv used to rename or move files
