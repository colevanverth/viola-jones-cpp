#!/bin/bash

make
rm -rf ../dataset/non_face_integral ../dataset/face_integral
mkdir ../dataset/non_face_integral ../dataset/face_integral
./integral_image.out ../dataset/non_face_edited ../dataset/non_face_integral
./integral_image.out ../dataset/face ../dataset/face_integral
make clean
